include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(util)

add_subdirectory(integration)
add_subdirectory(unit)

enable_testing()
include(GoogleTest)

add_executable(msp430_test main.cpp)
target_link_libraries(msp430_test msp430_lib
                                  -Wl,--whole-archive unit_tests
                                  integration_tests
                                  -Wl,--no-whole-archive)

gtest_discover_tests(msp430_test)