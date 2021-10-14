//
// Created by scolton on 10/13/21.
//

#include "dev/cpu/cpu.h"
#include "dev/model/package.h"

MSP430::ICPU* MSP430::Package::get_cpu() {
  return this->cpu;
}

MSP430::MemoryMapper* MSP430::Package::get_memory() {
  return &(this->memory);
}