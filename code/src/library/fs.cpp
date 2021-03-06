// fs.cpp: File System

#include "sfs/fs.h"

#include <algorithm>

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <string>

// Debug file system -----------------------------------------------------------

void FileSystem::debug(Disk *disk) {
    Block block;
    // Read SuperBlock
    disk->read(0, block.Data);

    printf("SuperBlock:\n");
    if (block.Super.MagicNumber == MAGIC_NUMBER)
        printf("    magic number is valid\n");
    else
        printf("    magic number is invalid\n");

    printf("    %u blocks\n"         , block.Super.Blocks);
    printf("    %u inode blocks\n"   , block.Super.InodeBlocks);
    printf("    %u inodes\n"         , block.Super.Inodes);

    // Read Inode blocks

    // save the number of inode blocks
    uint32_t inode_blocks_count = block.Super.InodeBlocks;
    Block indirect_block;
    for (unsigned int i = 0; i < inode_blocks_count; i++) {
        // reuse the block on stack
        disk->read(i + 1, block.Data);
        for (unsigned int j = 0; j < INODES_PER_BLOCK; j++) {
            if (!block.Inodes[j].Valid)
                continue;

            std::string direct;     // string to store direct blocks
            std::string indirect;   // string to store indirect blocks
            uint32_t indirect_block_number;
            for (unsigned int k = 0; k < POINTERS_PER_INODE; k++) {
                if (block.Inodes[j].Direct[k] != 0) {
                    direct += " ";
                    direct += std::to_string(block.Inodes[j].Direct[k]);
                }
            }
            indirect_block_number = block.Inodes[j].Indirect;
            if (indirect_block_number != 0) {
                disk->read(indirect_block_number, indirect_block.Data);
                for (unsigned int l = 0; l < POINTERS_PER_BLOCK; l++) {
                    if (indirect_block.Pointers[l] != 0) {
                        indirect += " ";
                        indirect += std::to_string(indirect_block.Pointers[l]);
                    }
                }
            }
            printf("Inode %u:\n", j);
            printf("    size: %u bytes\n", block.Inodes[j].Size);
            printf("    direct blocks:%s\n", direct.c_str());
            if (indirect.length() > 0) {
                printf("    indirect block: %u\n", indirect_block_number);
                printf("    indirect data blocks:%s\n", indirect.c_str());
            }
        }
    }
}

// Format file system ----------------------------------------------------------

bool FileSystem::format(Disk *disk) {
    // Check if mounted
    if (disk->mounted()) return false;

    // Write SuperBlock
    Block block;
    memset(block.Data, 0, disk->BLOCK_SIZE);
    block.Super.MagicNumber = MAGIC_NUMBER;
    block.Super.Blocks = disk->size();
    // set the number of inode blocks
    block.Super.InodeBlocks = (size_t)(((float)disk->size() * 0.1) + 0.5);
    block.Super.Inodes = INODES_PER_BLOCK * block.Super.InodeBlocks;
    disk->write(0, block.Data);

    // Clear all other blocks
    char clear[BUFSIZ] = { 0 };
    for (size_t i = 1; i < block.Super.Blocks; i++) {
        disk->write(i, clear);
    }

    return true;
}

// Mount file system -----------------------------------------------------------

bool FileSystem::mount(Disk* disk) {
    // Make user disk isn't mounted
    if (disk->mounted())
        return false;
    // Read SuperBlock
    Block block;
    disk->read(0, block.Data);
    // make sure inodes counts match
    if (block.Super.Inodes != block.Super.InodeBlocks * INODES_PER_BLOCK)
        return false;
    // check magic number
    if (block.Super.MagicNumber != MAGIC_NUMBER)
        return false;
    // make sure there are blocks
    if (block.Super.Blocks < 0)
        return false;
    // check inode proportion
    if (block.Super.InodeBlocks != ceil(.1 * block.Super.Blocks))
        return false;
    disk->mount();

    // Copy metadata
    num_blocks = block.Super.Blocks;
    num_inode_blocks = block.Super.InodeBlocks;
    num_inodes = block.Super.Inodes;
    this->disk = disk;

    // Allocate free block bitmap
    free_bitmap = std::vector<int>(num_blocks, 1);
    //set all blocks to free initially, 1 indicates true for free blocks
    for (uint32_t i = 0; i < num_blocks; i++)
        free_bitmap[i] = 1;
    // SuperBlock is not free
    free_bitmap[0] = 0;
    // inode blocks are not free
    for (unsigned int i = 0; i < num_inode_blocks; i++)
        free_bitmap[1 + i] = 0;

    for (uint32_t inode_block = 0; inode_block < num_inode_blocks; inode_block++) {
        Block b;
        disk->read(1 + inode_block, b.Data);
        // reads each inode
        for (uint32_t inode = 0; inode < INODES_PER_BLOCK; inode++) {
            // if it's not valid, it has no blocks
            if (!b.Inodes[inode].Valid)
                continue;

            uint32_t n_blocks = (uint32_t)ceil(b.Inodes[inode].Size / (double)disk->BLOCK_SIZE);
            // read all direct blocks
            for (uint32_t pointer = 0; pointer < POINTERS_PER_INODE && pointer < n_blocks; pointer++) {
                free_bitmap[b.Inodes[inode].Direct[pointer]] = 0;
            }

            //read indirect block if necessary
            if (n_blocks > POINTERS_PER_INODE) {
                Block indirect;
                disk->read(b.Inodes[inode].Indirect, indirect.Data);
                free_bitmap[b.Inodes[inode].Indirect] = 0;
                for (uint32_t pointer = 0; pointer < n_blocks - POINTERS_PER_INODE; pointer++) {
                    free_bitmap[indirect.Pointers[pointer]] = 0;
                }
            }
        }
    }

    return true;
}

// Create inode ----------------------------------------------------------------

ssize_t FileSystem::create() {
    // Locate free inode in inode table
    int ind = -1;
    for (uint32_t inode_block = 0; inode_block < num_inode_blocks; inode_block++) {
        Block b;
        disk->read(1 + inode_block, b.Data);
        // reads each inode
        for (uint32_t inode = 0; inode < INODES_PER_BLOCK; inode++) {
            // if it's not valid, it's free to be written
            if (!b.Inodes[inode].Valid) {
                ind = inode + INODES_PER_BLOCK * inode_block;
                break;
            }
        }
        if (ind != -1)
            break;
    }
    // Record inode if found
    if (ind == -1)
        return -1;

    Inode i;
    i.Valid = true;
    i.Size = 0;
    for (unsigned int j = 0; j < POINTERS_PER_INODE; j++)
        i.Direct[j] = 0;
    i.Indirect = 0;
    save_inode(ind, &i);

    return ind;
}

// Remove inode ----------------------------------------------------------------

bool FileSystem::remove(size_t inode_number) {
    Inode node;
    // Load inode information
    if (!load_inode(inode_number, &node)) return false;
    if (node.Valid == 0) return false;

    // Free direct blocks
    for (unsigned int i = 0; i < POINTERS_PER_INODE; i++) {
        if (node.Direct[i] != 0) {
            free_bitmap[node.Direct[i]] = 1;
            node.Direct[i] = 0;
        }
    }
    // Free indirect blocks
    if (node.Indirect != 0) {
        free_bitmap[node.Indirect] = 1;
        Block b;
        disk->read(node.Indirect, b.Data);
        // Free blocks pointed to indirectly
        for (unsigned int i = 0; i < POINTERS_PER_BLOCK; i++) {
            if (b.Pointers[i] != 0) {
                free_bitmap[b.Pointers[i]] = 1;
            }
        }
    }
    // Clear inode in inode table
    node.Indirect = 0;
    node.Valid = 0;
    node.Size = 0;
    if (!save_inode(inode_number, &node))
        return false;
    return true;
}

// Inode stat ------------------------------------------------------------------

ssize_t FileSystem::stat(size_t inode_number) {
    // Load inode information
    Inode i;
    if (!load_inode(inode_number, &i) || !i.Valid)
        return -1;
    return i.Size;
}

// Read from inode -------------------------------------------------------------

ssize_t FileSystem::read(size_t inode_number, char* data, size_t length, size_t offset) {
    // Load inode information
    Inode inode;
    if (!load_inode(inode_number, &inode) || offset > inode.Size) return -1;
    // Adjust length
    length = std::min(length, inode.Size - offset);

    uint32_t start_block = offset / disk->BLOCK_SIZE;
    // Read block and copy to data; use memcpy
    // Get indirect block number if it will need it
    Block indirect;
    if ((offset + length) / disk->BLOCK_SIZE > POINTERS_PER_INODE) {
        // make sure direct block is allocated
        if (inode.Indirect == 0) return -1;
        disk->read(inode.Indirect, indirect.Data);
    }

    size_t read = 0;
    for (uint32_t block_num = start_block; read < length; block_num++) {
        // figure out which block we're reading
        size_t block_to_read;
        if (block_num < POINTERS_PER_INODE)
            block_to_read = inode.Direct[block_num];
        else
            block_to_read = indirect.Pointers[block_num - POINTERS_PER_INODE];

        //make sure block is allocated
        if (block_to_read == 0) return -1;

        //get the block -- from either direct or indirect
        Block b;
        disk->read(block_to_read, b.Data);
        size_t read_offset;
        size_t read_length;

        // if it's the first block read, have to start from an offset
        // and read either until the end of the block, or the whole request
        if (read == 0) {
            read_offset = offset % disk->BLOCK_SIZE;
            read_length = std::min(disk->BLOCK_SIZE - read_offset, length);
        } else {
            // otherwise, start from the beginning, and read
            // either the whole block or the rest of the request
            read_offset = 0;
            read_length = std::min(disk->BLOCK_SIZE - 0, length - read);
        }
        memcpy(data + read, b.Data + read_offset, read_length);
        read += read_length;
    }
    return read;
}

// Allocate free block --------------------------------------------------------------
ssize_t FileSystem::allocate_free_block() {
    int block = -1;
    for (unsigned int i = 0; i < num_blocks; i++) {
        if (free_bitmap[i]) {
            free_bitmap[i] = 0;
            block = i;
            break;
        }
    }
    // need to zero data block if we're allocating one
    if (block != -1) {
        char data[disk->BLOCK_SIZE];
        memset(data, 0, disk->BLOCK_SIZE);
        disk->write(block, (char*)data);
    }
    return block;
}

// Write to inode --------------------------------------------------------------

ssize_t FileSystem::write(size_t inode_number, char* data, size_t length, size_t offset) {
    // Load inode
    Inode inode;
    if (!load_inode(inode_number, &inode) || offset > inode.Size) return -1;

    size_t MAX_FILE_SIZE = disk->BLOCK_SIZE * (POINTERS_PER_INODE * POINTERS_PER_BLOCK);
    // Adjust length
    length = std::min(length, MAX_FILE_SIZE - offset);

    uint32_t start_block = offset / disk->BLOCK_SIZE;
    Block indirect;
    bool read_indirect = false;

    bool modified_inode = false;
    bool modified_indirect = false;

    // Write block and copy data
    size_t written = 0;
    for (uint32_t block_num = start_block;
        written < length && block_num < POINTERS_PER_INODE + POINTERS_PER_BLOCK;
        block_num++) {

        // figure out which block we're reading
        size_t block_to_write;
        if (block_num < POINTERS_PER_INODE) {
            // Allocate block if necessary
            if (inode.Direct[block_num] == 0) {
                ssize_t allocated_block = allocate_free_block();
                if (allocated_block == -1)
                    break;

                inode.Direct[block_num] = allocated_block;
                modified_inode = true;
            }
            block_to_write = inode.Direct[block_num];
        }
        else { // Indirect block
            // Allocate indirect block if necessary
            if (inode.Indirect == 0) {
                ssize_t allocated_block = allocate_free_block();
                if (allocated_block == -1)
                    return written;

                inode.Indirect = allocated_block;
                modified_indirect = true;
            }

            // Read indirect block if hasn't been read yet
            if (!read_indirect) {
                disk->read(inode.Indirect, indirect.Data);
                read_indirect = true;
            }

            // Allocate block if necessary
            if (indirect.Pointers[block_num - POINTERS_PER_INODE] == 0) {
                ssize_t allocated_block = allocate_free_block();
                if (allocated_block == -1)
                    break;

                indirect.Pointers[block_num - POINTERS_PER_INODE] = allocated_block;
                modified_indirect = true;
            }
            block_to_write = indirect.Pointers[block_num - POINTERS_PER_INODE];
        }

        //get the block -- from either direct or indirect
        size_t write_offset;
        size_t write_length;

        // if it's the first block written, have to start from an offset
        // and write either until the end of the block, or the whole request
        if (written == 0) {
            write_offset = offset % disk->BLOCK_SIZE;
            write_length = std::min(disk->BLOCK_SIZE - write_offset, length);
        }
        else {
            // otherwise, start from the beginning, and write
            // either the whole block or the rest of the request
            write_offset = 0;
            write_length = std::min(disk->BLOCK_SIZE - 0, length - written);
        }

        char write_buffer[disk->BLOCK_SIZE];

        // if we're not writing the whole block, need to copy what's there
        if (write_length < disk->BLOCK_SIZE) {
            disk->read(block_to_write, (char*)write_buffer);
        }

        // copy into buffer
        memcpy(write_buffer + write_offset, data + written, write_length);
        disk->write(block_to_write, (char*)write_buffer);
        written += write_length;
    }

    // update inode size
    uint32_t new_size = std::max((size_t)inode.Size, written + offset);
    if (new_size != inode.Size) {
        inode.Size = new_size;
        modified_inode = true;
    }

    // save inode and indirect if necessary
    if (modified_inode)
        save_inode(inode_number, &inode);

    if (modified_indirect)
        disk->write(inode.Indirect, indirect.Data);

    return written;
}

// Load inode --------------------------------------------------------------
bool FileSystem::load_inode(size_t inode_number, Inode* node) {
    size_t block_number = 1 + (inode_number / INODES_PER_BLOCK);
    size_t inode_offset = inode_number % INODES_PER_BLOCK;
    if (inode_number >= num_inodes) 
        return false;

    Block block;
    disk->read(block_number, block.Data);
    *node = block.Inodes[inode_offset];
    return true;
}

// Save inode --------------------------------------------------------------
bool FileSystem::save_inode(size_t inode_number, Inode* node) {
    size_t block_number = 1 + inode_number / INODES_PER_BLOCK;
    size_t inode_offset = inode_number % INODES_PER_BLOCK;
    if (inode_number >= num_inodes)
        return false;

    Block block;
    disk->read(block_number, block.Data);
    block.Inodes[inode_offset] = *node;
    disk->write(block_number, block.Data);
    return true;
}
