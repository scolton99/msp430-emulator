//
// Created by scolton on 10/15/21.
//

#ifndef MSP430_EMULATOR_FORMAT_II_H
#define MSP430_EMULATOR_FORMAT_II_H

#include "instruction.h"

namespace MSP430 {
  template <typename msp430_size_t>
  class InstructionFormatII : public Instruction<msp430_size_t> {
  protected:
//    uint16_t opcode : 9;
//    uint8_t  bw     : 1;
    uint8_t  ad     : 2;
    uint8_t  rdst   : 4;

    ExtensionWord opt_ext_word;

    explicit InstructionFormatII(msp430_word_t base_instr,
                                 msp430_word_t opt_ext = 0);
  public:
    bool has_extension_word() override;
    int  extra_words()        override;
    int  get_execution_time() override;
    bool is_extended()        override;
  };
}

#endif //MSP430_EMULATOR_FORMAT_II_H
