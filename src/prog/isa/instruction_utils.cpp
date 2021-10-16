//
// Created by scolton on 10/14/21.
//

#include "prog/isa/utils.h"
#include "types.h"

MSP430::ExtensionWord::ExtensionWord(msp430_word_t word) {
  this->word = word;
}

uint8_t MSP430::ExtensionWord::get_al() {
  return (this->word >> 6) & 0b1;
}

uint8_t MSP430::ExtensionWord::get_rpt(Package* package) {
  uint8_t use_reg = (this->word >> 7) & 0b1;
  uint8_t n1rn    = (this->word) & 0xF;

  return use_reg ? package->get_cpu()->resolve_register(n1rn)->get_value(0x0, 0x1) & 0xF : n1rn;
}

uint8_t MSP430::ExtensionWord::get_zc() {
  return (this->word >> 8) & 0b1;
}

uint8_t MSP430::ExtensionWord::get_src_msn() {
  return (this->word >> 7) & 0xF;
}

uint8_t MSP430::ExtensionWord::get_dst_msn() {
  return (this->word) & 0xF;
}

bool MSP430::ExtensionWord::is_present() {
  return this->word;
}

MSP430::OpcodeWidthHolder::OpcodeWidthHolder(MSP430::msp430_word_t opcode, MSP430::msp430_word_t ext) {
  MSP430::InstructionFormat format = opcode_to_format(opcode, ext);

  /*
   *  AL | BW | R
   *  0    0    X
   *  0    1    ADDRESS WORD
   *  1    0    WORD
   *  1    1    BYTE
   */
  switch (format) {
    case FORMAT_I:
    case FORMAT_I_EXTENDED:
    case FORMAT_II:
    case FORMAT_II_EXTENDED:
      this->bw = (opcode >> 6) & 0b1;
      this->al = ext ? (ext >> 6) & 0b1 : 0b1;
      break;
    case FORMAT_PUSHM_POPM:
      this->al = (opcode >> 8) & 0b1;
      this->bw = 0b1;
      break;
    case FORMAT_RXXM:
      this->al = (opcode >> 4) & 0b1;
      this->bw = 0b1;
      break;
    case FORMAT_CALLA:
    case FORMAT_EXTENDED_ADDRESS:
      this->al = 0;
      this->bw = 0b1;
      break;
    case FORMAT_JUMP:
      throw std::runtime_error("Jump instructions do not have operand widths");
  }
}

MSP430::InstructionWidth MSP430::OpcodeWidthHolder::get_width() const {
  unsigned al_bw = ((unsigned) this->al << 1) | (unsigned) this->bw;

  switch (al_bw) {
    case 0b00:
      throw std::runtime_error("Invalid combination of A/L and B/W");
    case 0b01:
      return ADDRESS_WORD;
    case 0b10:
      return WORD;
    case 0b11:
      return BYTE;
    default:
      throw std::runtime_error("Shouldn't be possible");
  }
}

MSP430::InstructionFormat MSP430::OpcodeWidthHolder::opcode_to_format(msp430_word_t opcode, msp430_word_t ext) {
  /* !!! FORMAT I !!!
   * - MOV(X):  4xxx
   * - ADD(X):  5xxx
   * - ADDC(X): 6xxx
   * - SUB(X):  8xxx
   * - SUBC(X): 7xxx
   * - CMP(X):  9xxx
   * - DADD(X): Axxx
   * - BIT(X):  Bxxx
   * - BIC(X):  Cxxx
   * - BIS(X):  Dxxx
   * - XOR(X):  Exxx
   * - AND(X):  Fxxx
   *
   * !!! FORMAT II !!!
   * - RRC(X):  1000 | 1040
   * - SWPB(X): 1080        <- w/o ext: word, w/ ext: depends
   * - RRA(X):  1040 | 1140
   * - SXT(X):  1180
   * - PUSH(X): 1200 | 1240
   * - CALL:    1280
   * - RETI:    1300
   * - CALLA:   1340
   * - POPM:    14xx
   * - PUSHM:   14xx
   * - RRCM:    0xxx
   * - RRUM:    0xxx
   * - RRAM:    0xxx
   * - RLAM:    0xxx
   *
   * !!! JUMP !!!
   * - 20xx -> 3Cxx
   *
   * !!! ALWAYS ADDRESS WORD !!!
   * - ADDA, SUBA, CMPA, MOVA
   * - ^0000xxxx[^0100|0101]xxxx$
   */
  if (!(opcode & 0xF000)) {
    uint8_t instr_id = (opcode & 0x00F0) >> 4;
    return (instr_id & 0b1110) == 0b0100 ? FORMAT_RXXM : FORMAT_EXTENDED_ADDRESS;
  }

  if (opcode >= 0x2000 && opcode < 0x4000)
    return FORMAT_JUMP;

  if (opcode >= 0x4000 && opcode <= 0xFFFF)
    return ext ? FORMAT_I_EXTENDED : FORMAT_I;

  if ((opcode & 0xFF00) == 0x1300) {
    uint16_t instr_id    = (opcode >> 6) & 0x3FF;
    uint16_t instr_extra = (opcode >> 4) & 0x3;

    // RETI
    if (instr_id == 0x04C) {
      if (opcode != 0x1300)
        throw std::runtime_error("Invalid opcode (RETI)");

      return FORMAT_II;
    }

    if ((instr_id & 0x3) == 0x3 || (((instr_id) & 0x3) == 0b10 && instr_extra == 0b10))
      throw std::runtime_error("Invalid opcode");

    return FORMAT_CALLA;
  }

  if ((opcode & 0xFF00) == 0x1400) {
    return FORMAT_PUSHM_POPM;
  }

  if (opcode >= 0x1000 && opcode < 0x1300) {
    if (opcode >= 0x12C0 && opcode < 0x1300)
      throw std::runtime_error("CALL cannot be a byte instruction");

    if (opcode >= 0x10C0 && opcode < 0x1100)
      throw std::runtime_error("SWPB cannot be a byte instruction");

    if (opcode >= 0x11C0 && opcode < 0x1200)
      throw std::runtime_error("SXT cannot be a byte instruction");

    return ext ? FORMAT_II_EXTENDED : FORMAT_II;
  }

  throw std::runtime_error("Invalid opcode");
}
