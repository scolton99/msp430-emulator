cmake_minimum_required(VERSION 3.0)
project(msp430_emulator)

set(CMAKE_CXX_STANDARD 14)

include_directories(include lib)

add_compile_options(-Wall -pedantic -std=gnu++14)

add_subdirectory(src)
add_subdirectory(test)
