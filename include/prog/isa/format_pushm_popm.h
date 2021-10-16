//
// Created by scolton on 10/15/21.
//

#ifndef MSP430_EMULATOR_FORMAT_PUSHM_POPM_H
#define MSP430_EMULATOR_FORMAT_PUSHM_POPM_H

#include "instruction.h"

namespace MSP430 {
  template <typename msp430_size_t>
  class InstructionPushmPopmFormat : public Instruction<msp430_size_t> {
  protected:
    unsigned n1:4;
    unsigned rdst:4;

    explicit InstructionPushmPopmFormat(msp430_word_t base_instr);
  public:
    bool has_extension_word() override;
    int  extra_words()        override;
    int  get_execution_time() override;
    bool is_extended()        override;
  };
}

#endif //MSP430_EMULATOR_FORMAT_PUSHM_POPM_H
