//
// Created by scolton on 10/15/21.
//

#ifndef MSP430_EMULATOR_FORMAT_I_H
#define MSP430_EMULATOR_FORMAT_I_H

#include "instruction.h"

namespace MSP430 {
  template <typename msp430_size_t>
  class InstructionFormatI : public Instruction<msp430_size_t> {
  protected:
    uint8_t rsrc : 4;
    uint8_t as   : 2;
    uint8_t ad   : 1;
    uint8_t rdst : 4;

    ExtensionWord opt_ext_word;
    explicit InstructionFormatI(msp430_word_t base_instr,
                                msp430_word_t opt_ext = 0);

    InstructionFormatI(uint8_t rsrc,
                       uint8_t as,
                       uint8_t ad,
                       uint8_t rdst,
                       msp430_word_t opt_ext) :
        rsrc(rsrc),
        as(as),
        ad(ad),
        rdst(rdst),
        opt_ext_word(ExtensionWord(opt_ext)) {
    }

  public:
    bool has_extension_word() override;
    int  extra_words()        override;
    int  get_execution_time() override;
    bool is_extended()        override;

    msp430_size_t get_src_value(Package*);
    msp430_size_t get_dst_value(Package*);
    void          set_dst_value(Package*, msp430_size_t);

    AddressingMode get_src_addr_mode() const;
    AddressingMode get_dst_addr_mode() const;
  };
}

#endif //MSP430_EMULATOR_FORMAT_I_H
