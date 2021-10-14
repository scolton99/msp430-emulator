add_subdirectory(cpu)
add_subdirectory(mem)

add_library(dev INTERFACE model/package.cpp)
target_link_libraries(dev INTERFACE cpu mem)