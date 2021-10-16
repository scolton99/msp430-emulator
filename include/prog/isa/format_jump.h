//
// Created by scolton on 10/15/21.
//

#ifndef MSP430_EMULATOR_FORMAT_JUMP_H
#define MSP430_EMULATOR_FORMAT_JUMP_H

#include "instruction.h"

namespace MSP430 {
  template <typename msp430_size_t>
  class InstructionJumpFormat : public Instruction<msp430_size_t> {
  protected:
    int opcode:3;
    int condition:3;
    signed int offset:10;

    explicit InstructionJumpFormat(msp430_word_t base_instr);
  public:
    bool has_extension_word() override;
    int  extra_words()        override;
    int  get_execution_time() override;
    bool is_extended()        override;
  };
}

#endif //MSP430_EMULATOR_FORMAT_JUMP_H
