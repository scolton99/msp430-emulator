//
// Created by scolton on 10/15/21.
//

#ifndef MSP430_EMULATOR_FORMAT_CALLA_H
#define MSP430_EMULATOR_FORMAT_CALLA_H

#include "instruction.h"

namespace MSP430 {
  template <typename msp430_size_t>
  class InstructionCALLAFormat : public Instruction<msp430_size_t> {
  protected:
    unsigned opcode:12;
    unsigned rdst_ext:4;

    explicit InstructionCALLAFormat(msp430_word_t base_instr);
  public:
    bool has_extension_word() override;
    int  extra_words()        override;
    int  get_execution_time() override;
    bool is_extended()        override;
  };
}

#endif //MSP430_EMULATOR_FORMAT_CALLA_H
