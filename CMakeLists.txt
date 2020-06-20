cmake_minimum_required(VERSION 3.5)

project(allocator VERSION 0.0.1)

set(SOURCE main.cpp)
set(HEADERS hard.h myallocator.h mylist.h)

add_executable(alloc ${SOURCE} ${HEADERS})

set_target_properties(alloc PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wextra;-Wpedantic;-Wall"
)