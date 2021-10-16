add_library(peripheral_test tinyram.cpp)
target_link_libraries(peripheral_test -Wl,--no-whole-archive msp430_lib gtest)