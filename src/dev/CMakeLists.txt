add_subdirectory(cpu)
add_subdirectory(mem)
add_subdirectory(model)
add_subdirectory(peripheral)

add_library(dev INTERFACE)
target_link_libraries(dev INTERFACE cpu mem model peripheral)