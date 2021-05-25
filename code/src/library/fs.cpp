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

    // Read Superblock
    disk->read(0, block.Data);

    printf("SuperBlock:\n");
    if (block.Super.MagicNumber == MAGIC_NUMBER) {
        printf("    magic number is valid\n");
    } else {
        printf("    magic number is invalid\n");
    }
    printf("    %u blocks\n"         , block.Super.Blocks);
    printf("    %u inode blocks\n"   , block.Super.InodeBlocks);
    printf("    %u inodes\n"         , block.Super.Inodes);

    // Read Inode blocks
    Block indirect_block;
    for (unsigned int i = 0; i < block.Super.InodeBlocks; i++) {
        disk->read(i + 1, block.Data);
        for (unsigned int j = 0; j < INODES_PER_BLOCK; j++) {
            if (!block.Inodes[j].Valid) {
                continue;
            }
            std::string direct;
            std::string indirect;
            uint32_t indirect_block_number;
            for (unsigned int k = 0; k < POINTERS_PER_INODE; k++) {
                if (block.Inodes[j].Direct[k] != 0) {
                    direct += " ";
                    direct += std::to_string(block.Inodes[j].Direct[k]);
                }
            }
            indirect_block_number = block.Inodes[i].Indirect;
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
    // Write superblock

    // Clear all other blocks
    return true;
}

// Mount file system -----------------------------------------------------------

bool FileSystem::mount(Disk *disk) {
    // Read superblock

    // Set device and mount

    // Copy metadata

    // Allocate free block bitmap

    return true;
}

// Create inode ----------------------------------------------------------------

ssize_t FileSystem::create() {
    // Locate free inode in inode table

    // Record inode if found
    return 0;
}

// Remove inode ----------------------------------------------------------------

bool FileSystem::remove(size_t inumber) {
    // Load inode information

    // Free direct blocks

    // Free indirect blocks

    // Clear inode in inode table
    return true;
}

// Inode stat ------------------------------------------------------------------

ssize_t FileSystem::stat(size_t inumber) {
    // Load inode information
    return 0;
}

// Read from inode -------------------------------------------------------------

ssize_t FileSystem::read(size_t inumber, char *data, size_t length, size_t offset) {
    // Load inode information

    // Adjust length

    // Read block and copy to data
    return 0;
}

// Write to inode --------------------------------------------------------------

ssize_t FileSystem::write(size_t inumber, char *data, size_t length, size_t offset) {
    // Load inode
    
    // Write block and copy to data
    return 0;
}
