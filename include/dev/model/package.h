//
// Created by scolton on 10/10/21.
//

#ifndef MSP430_EMULATOR_PACKAGE_H
#define MSP430_EMULATOR_PACKAGE_H

#include "dev/mem/memory_map.h"
#include "dev/cpu/cpu.h"

namespace MSP430 {
  class Package {
  protected:
    const ICPU* cpu;
    const MemoryMapper memory;
    explicit Package(ICPU* cpu) : cpu(cpu) { }
  public:
    virtual void init() = 0;
    ICPU* get_cpu();
    MemoryMapper* get_memory();
  };
}

#endif //MSP430_EMULATOR_PACKAGE_H
