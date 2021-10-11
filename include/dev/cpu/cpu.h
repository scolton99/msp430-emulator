//
// Created by scolton on 10/8/21.
//

#ifndef MSP430_EMULATOR_CPU_H
#define MSP430_EMULATOR_CPU_H

namespace MSP430 {
  typedef struct {
    int value;
  } register_t;

  class CPU {
  public:
    const register_t r0;
    const register_t r1;
    const register_t r2;
    const register_t r3;
    const register_t r4;
    const register_t r5;
    const register_t r6;
    const register_t r7;
    const register_t r8;
    const register_t r9;
    const register_t r10;
    const register_t r11;
    const register_t r12;
    const register_t r13;
    const register_t r14;
    const register_t r15;

    void tick();
  };
}

#endif //MSP430_EMULATOR_CPU_H
