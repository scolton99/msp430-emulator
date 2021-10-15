//
// Created by scolton on 10/13/21.
//

#include "dev/model/package.h"
#include "dev/mem/memory_map.h"
#include "dev/cpu/decode.h"

MSP430::InstructionWidth MSP430::next_instruction_width(msp430_word_t ext_word, msp430_word_t raw_instruction) {
  return OpcodeWidthHolder(raw_instruction, ext_word).get_width();
}

void MSP430::fill_instruction_and_ext(Package*       package,
                                      msp430_addr_t& addr_orig,
                                      msp430_word_t& extension_word,
                                      msp430_word_t& raw_instruction,
                                      bool           increment) {
  msp430_addr_t addr = addr_orig;
  MemoryMapper* mem  = package->get_memory();

  extension_word  = 0x0;
  raw_instruction = mem->get_word(addr);

  msp430_byte_t identifier = raw_instruction >> 8;
  if (identifier >= 0x18 && identifier <= 0x1F) {
    addr += 2;
    extension_word  = raw_instruction;
    raw_instruction = mem->get_word(addr);
  }

  if (increment)
    addr_orig = addr;
}