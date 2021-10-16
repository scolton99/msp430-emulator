//
// Created by scolton on 10/15/21.
//

#ifndef MSP430_EMULATOR_UTILS_H
#define MSP430_EMULATOR_UTILS_H

#include "dev/model/package.h"
#include "types.h"

namespace MSP430 {
  enum InstructionFormat {
    FORMAT_I,
    FORMAT_II,
    FORMAT_JUMP,
    FORMAT_I_EXTENDED,
    FORMAT_II_EXTENDED,
    FORMAT_PUSHM_POPM,
    FORMAT_RXXM,
    FORMAT_CALLA,
    FORMAT_EXTENDED_ADDRESS
  };

  enum InstructionWidth {
    BYTE,
    WORD,
    ADDRESS_WORD
  };

  enum AddressingMode {
    REGISTER,
    INDEXED,
    SYMBOLIC,
    ABSOLUTE,
    INDIRECT_REGISTER,
    INDIRECT_AUTOINCREMENT,
    IMMEDIATE
  };

  class ExtensionWord {
  private:
    msp430_word_t word;
  public:
    explicit ExtensionWord(msp430_word_t);
    uint8_t get_zc();
    uint8_t get_rpt(Package*);
    uint8_t get_al();
    uint8_t get_src_msn();
    uint8_t get_dst_msn();
    bool    is_present();
  };

  class OpcodeWidthHolder {
  private:
    unsigned int bw:1;
    unsigned int al:1;

  public:
    OpcodeWidthHolder(msp430_word_t opcode, msp430_word_t ext);
    InstructionWidth get_width() const;

  private:
    static InstructionFormat opcode_to_format(msp430_word_t opcode, msp430_word_t ext);
  };
}

#endif //MSP430_EMULATOR_UTILS_H
