add_subdirectory(cpu)
add_subdirectory(mem)

add_library(dev INTERFACE)
target_link_libraries(dev INTERFACE cpu mem model peripheral)