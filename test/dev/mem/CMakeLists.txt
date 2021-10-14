add_library(mem_test memory_map_test.cpp memory_map_test.h)
target_link_libraries(mem_test -Wl,--no-whole-archive msp430_lib gtest)