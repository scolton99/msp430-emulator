add_library(integration_tests pipeline_test.cpp)
target_link_libraries(integration_tests -Wl,--no-whole-archive msp430_lib gtest)