//
// Created by scolton on 10/13/21.
//

#include <cstdint>
#include "prog/isa/instruction.h"

template <typename msp430_size_t>
MSP430::AddressingMode MSP430::Instruction<msp430_size_t>::resolve_dst_addr_mode(uint8_t ad, uint8_t rdst) {
  switch (ad) {
    case 0b0:
      return REGISTER;
    case 0b1:
      switch (rdst) {
        case 0x0:
          return SYMBOLIC;
        case 0x2:
          return ABSOLUTE;
        default:
          return INDEXED;
      }
    default:
      throw std::runtime_error("Invalid value for ad");
  }
}

template <typename msp430_size_t>
MSP430::InstructionFormatI<msp430_size_t>::InstructionFormatI(msp430_word_t base_instr,
                                                              msp430_word_t opt_ext) :
                                                             opt_ext_word(opt_ext) {
  this->opcode = (base_instr >> 12) & 0xF;
  this->rsrc   = (base_instr >> 8)  & 0xF;
  this->ad     = (base_instr >> 7)  & 0x1;
  this->bw     = (base_instr >> 6)  & 0x1;
  this->as     = (base_instr >> 4)  & 0x3;
  this->rdst   = (base_instr)       & 0xF;
}

template <typename msp430_size_t>
bool MSP430::InstructionFormatI<msp430_size_t>::has_extension_word() {
  return this->opt_ext_word;
}

template <typename msp430_size_t>
int MSP430::InstructionFormatI<msp430_size_t>::extra_words() {
  int extra_src_word = this->as == 0b01 || (this->as == 0b11 && this->rsrc == 0x0);
  int extra_dst_word = this->ad == 0b1;

  return extra_src_word + extra_dst_word;
}

template <typename msp430_size_t>
MSP430::AddressingMode MSP430::InstructionFormatI<msp430_size_t>::get_src_addr_mode() const {
  switch (this->as) {
    case 0b00:
      return REGISTER;
    case 0b01:
      switch (this->rsrc) {
        case 0x0:
          return SYMBOLIC;
        case 0x2:
          return ABSOLUTE;
        default:
          return INDEXED;
      }
    case 0b10:
      return INDIRECT_REGISTER;
    case 0b11:
      return this->rsrc == 0x0 ? IMMEDIATE : INDIRECT_AUTOINCREMENT;
  }
}

template <typename msp430_size_t>
MSP430::AddressingMode MSP430::InstructionFormatI<msp430_size_t>::get_dst_addr_mode() const {
  return resolve_dst_addr_mode(this->ad, this->rdst);
}

template <typename msp430_size_t>
msp430_size_t MSP430::InstructionFormatI<msp430_size_t>::get_src_value(Package* package) {
  ICPU* cpu = package->get_cpu();
  msp430_size_t value;

  switch (this->get_src_addr_mode()) {
    case REGISTER:
      value = cpu->resolve_register(this->rsrc)->get_value(this->as);
      break;
    case INDEXED:
      uint8_t addr_size = sizeof(msp430_addr_t);
      msp430_addr_t base = cpu->resolve_register(this->rsrc)->get_value(0, addr_size);
      msp430_addr_word_t

      msp430_addr_word_t src_addr = calc_indexed_addr(, )

      return 0;
    case SYMBOLIC:
      return 0;
    case ABSOLUTE:
      return 0;
    case INDIRECT_REGISTER:
      return 0;
    case INDIRECT_AUTOINCREMENT:
      return 0;
    case IMMEDIATE:
      return 0;
  }
}

MSP430::InstructionFormatII::InstructionFormatII(msp430_word_t base_instr,
                                                 msp430_word_t opt_ext) :
                                                 opt_ext_word(opt_ext) {
  this->opcode = (base_instr >> 7) & 0x1FF;
  this->bw     = (base_instr >> 6) & 0x1;
  this->ad     = (base_instr >> 4) & 0x3;
  this->rdst   = (base_instr)      & 0xF;
}

bool MSP430::InstructionFormatII::has_extension_word() {
  return !!this->opt_ext_word;
}

int MSP430::InstructionFormatII::extra_words() {
  return this->ad == 0b01 || (this->ad == 0b11 && this->rdst == 0x0);
}

MSP430::InstructionJumpFormat::InstructionJumpFormat(msp430_word_t base_instr) {
  this->opcode    = (base_instr >> 13) & 0x7;
  this->condition = (base_instr >> 10) & 0x7;
  this->offset    = (base_instr)       & 0x3FF;
}

bool MSP430::InstructionJumpFormat::has_extension_word() {
  return false;
}

int MSP430::InstructionJumpFormat::extra_words() {
  return 0;
}
