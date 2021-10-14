//
// Created by scolton on 10/12/21.
//

#include "dev/peripheral/tinyram/tinyram.h"

MSP430::TinyRAM::TinyRAM() {
  this->memory.resize(22);
}

msp430_byte_t MSP430::TinyRAM::get(msp430_addr_t addr) {
  if (addr > this->memory.size())
    throw std::runtime_error("Address exceeds TinyRAM size");

  return this->memory[addr];
}

void MSP430::TinyRAM::set(msp430_addr_t addr, msp430_byte_t value) {
  if (addr > this->memory.size())
    throw std::runtime_error("Address exceeds TinyRAM size");

  this->memory[addr] = value;
}