add_subdirectory(dev)
add_subdirectory(prog)

add_library(unit_tests INTERFACE)
target_link_libraries(unit_tests INTERFACE -Wl,--whole-archive dev_test prog_test -Wl,--no-whole-archive)