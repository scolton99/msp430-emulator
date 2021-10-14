add_subdirectory(cpu)
add_subdirectory(mem)
add_subdirectory(peripheral)

add_library(dev_test INTERFACE)
target_link_libraries(dev_test INTERFACE msp430_lib
                                         -Wl,--whole-archive cpu_test
                                         mem_test
                                         -Wl,--no-whole-archive)

