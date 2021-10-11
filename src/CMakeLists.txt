add_subdirectory(dev)
add_subdirectory(prog)

add_executable(emulator main.cpp ../include/dev/model/package.h ../include/dev/mem/memory_map.h dev/mem/memory_map.cpp)
target_link_libraries(emulator LINK_PUBLIC elf)