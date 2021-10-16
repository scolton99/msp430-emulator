//
// Created by scolton on 10/11/21.
//

#ifndef MSP430_EMULATOR_DECODE_H
#define MSP430_EMULATOR_DECODE_H

#include "prog/isa/instruction.h"

namespace MSP430 {
  void fill_instruction_and_ext(Package*,
                                msp430_addr_t& addr,
                                msp430_word_t& extension_word,
                                msp430_word_t& raw_instruction,
                                bool           increment = false);
  InstructionWidth next_instruction_width(msp430_word_t ext_word, msp430_word_t raw_instruction);

  template<typename msp430_size_t>
  Instruction<msp430_size_t>* instruction_decode(Package*, msp430_addr_t);
}

#endif //MSP430_EMULATOR_DECODE_H
