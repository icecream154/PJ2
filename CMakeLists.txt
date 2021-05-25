cmake_minimum_required(VERSION 3.19)
project(PJ2)

set(CMAKE_CXX_STANDARD 14)

include_directories(code/include)
include_directories(code/include/sfs)

add_executable(PJ2
        code/include/sfs/disk.h
        code/include/sfs/fs.h
        code/src/library/disk.cpp
        code/src/library/fs.cpp
        code/src/shell/sfssh.cpp)
