cmake_minimum_required(VERSION 3.0)
project(msp430_emulator)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
add_subdirectory(src)

#add_executable(msp430_emulator src/main.cpp include/dev/peripheral/adc/signals.h include/dev/asm/instruction.h include/dev/mem/segment.h include/dev/cpu/cpu.h include/dev/model/msp430fr5994.h include/prog/elf.h src/prog/elf.cpp)
