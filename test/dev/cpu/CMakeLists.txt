add_library(cpu_test register_test.cpp)
target_link_libraries(cpu_test -Wl,--no-whole-archive msp430_lib gtest)