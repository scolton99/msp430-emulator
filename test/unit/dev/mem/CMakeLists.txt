add_library(mem_test mem_test.cpp)
target_link_libraries(mem_test -Wl,--no-whole-archive msp430_lib gtest)