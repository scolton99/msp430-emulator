//
// Created by scolton on 10/15/21.
//

#ifndef MSP430_EMULATOR_FORMAT_RXXM_H
#define MSP430_EMULATOR_FORMAT_RXXM_H

#include "instruction.h"

namespace MSP430 {
  template <typename msp430_size_t>
  class InstructionRXXMFormat : public Instruction<msp430_size_t> {
  protected:
    unsigned n1:2;
    unsigned rdst:4;

    explicit InstructionRXXMFormat(msp430_word_t base_instr);
  public:
    bool has_extension_word() override;
    int  extra_words()        override;
    int  get_execution_time() override;
    bool is_extended()        override;
  };
}

#endif //MSP430_EMULATOR_FORMAT_RXXM_H
