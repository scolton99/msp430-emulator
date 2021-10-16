//
// Created by scolton on 10/15/21.
//

#ifndef MSP430_EMULATOR_FORMAT_ADDRESS_H
#define MSP430_EMULATOR_FORMAT_ADDRESS_H

#include "instruction.h"

namespace MSP430 {
  template <typename msp430_size_t>
  class InstructionAddressFormat : public Instruction<msp430_size_t> {
  protected:
    unsigned src_ext:4;
    unsigned id:4;
    unsigned dst_ext:4;

    explicit InstructionAddressFormat(msp430_word_t base_instr);
  public:
    bool has_extension_word() override;
    int  extra_words()        override;
    int  get_execution_time() override;
    bool is_extended()        override;
  };
}

#endif //MSP430_EMULATOR_FORMAT_ADDRESS_H
