add_subdirectory(dev)
add_subdirectory(prog)

add_library(msp430_lib INTERFACE)
target_link_libraries(msp430_lib INTERFACE dev prog)

add_executable(msp430_emulator main.cpp ../test/main.cpp ../include/dev/peripheral/tinyram/tinyram.h ../include/prog/isa/instruction_fwd.h ../include/prog/isa/visitor.h ../include/types.h)
target_link_libraries(msp430_emulator msp430_lib)