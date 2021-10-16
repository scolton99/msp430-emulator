//
// Created by scolton on 10/12/21.
//

#include "dev/mem/mem.h"
#include "dev/model/msp430fr5994.h"

void MSP430::MSP430FR5994::init() {
  MSP430::MemoryMapping tiny_ram_mapping {&(this->tiny_ram),
                                          MSP430FR5994_TINYRAM_START,
                                          MSP430FR5994_TINYRAM_SIZE,
                                          0x0};

  this->memory.add_mapping(tiny_ram_mapping);
}