//
// Created by scolton on 10/15/21.
//

#include "prog/isa/utils.h"
#include "prog/isa/format_i.h"
#include "types.h"

template <typename msp430_size_t>
MSP430::InstructionFormatI<msp430_size_t>::InstructionFormatI(msp430_word_t base_instr,
                                                              msp430_word_t opt_ext) :
    opt_ext_word(ExtensionWord(opt_ext)) {
  this->rsrc   = (base_instr >> 8)  & 0xF;
  this->ad     = (base_instr >> 7)  & 0x1;
  this->as     = (base_instr >> 4)  & 0x3;
  this->rdst   = (base_instr)       & 0xF;
}

template <typename msp430_size_t>
bool MSP430::InstructionFormatI<msp430_size_t>::has_extension_word() {
  return this->opt_ext_word.is_present();
}

template <typename msp430_size_t>
int MSP430::InstructionFormatI<msp430_size_t>::extra_words() {
  int extra_src_word = this->as == 0b01 || (this->as == 0b11 && this->rsrc == 0x0);
  int extra_dst_word = this->ad == 0b1;

  return extra_src_word + extra_dst_word;
}

template <typename msp430_size_t>
bool MSP430::InstructionFormatI<msp430_size_t>::is_extended() {
  return this->has_extension_word();
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
  return this->resolve_dst_addr_mode(this->ad, this->rdst);
}

template<typename msp430_size_t>
int MSP430::InstructionFormatI<msp430_size_t>::get_execution_time() {
  return 0;
}

template<typename msp430_size_t>
msp430_size_t MSP430::InstructionFormatI<msp430_size_t>::get_src_value(Package* package) {
  return this->get_op_value(package,
                            this->get_src_addr_mode(),
                            this->rsrc,
                            this->as,
                            this->opt_ext_word.get_src_msn(),
                            this->is_extended());;
}

template<typename msp430_size_t>
msp430_size_t MSP430::InstructionFormatI<msp430_size_t>::get_dst_value(Package* package) {
  msp430_size_t value =  this->get_op_value(package,
                                            this->get_dst_addr_mode(),
                                            this->rdst,
                                            this->as,
                                            this->opt_ext_word.get_dst_msn(),
                                            this->is_extended());

  // We haven't finished the instruction yet! So we need to rewind so that this destination can be safely
  // saved to in the case that the offset/address was saved relative to the PC
  msp430_addr_t rewound = package->get_cpu()->get_pc()->get_value(0x0, sizeof(msp430_addr_t)) - 0x2;
  switch (this->get_dst_addr_mode()) {
    case SYMBOLIC:
    case ABSOLUTE:
    case INDEXED:
      package->get_cpu()->get_pc()->set_value(rewound, sizeof(msp430_addr_t));
      break;
    default:
      break;
  }

  return value;
}

template<typename msp430_size_t>
void MSP430::InstructionFormatI<msp430_size_t>::set_dst_value(Package* package, msp430_size_t value) {
  this->set_op_value(package,
                     this->get_dst_addr_mode(),
                     this->rdst,
                     this->as,
                     this->opt_ext_word.get_dst_msn(),
                     this->is_extended(),
                     value);
}

template class MSP430::InstructionFormatI<MSP430::msp430_byte_t>;
template class MSP430::InstructionFormatI<MSP430::msp430_word_t>;
template class MSP430::InstructionFormatI<MSP430::msp430_addr_word_t>;