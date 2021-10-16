//
// Created by scolton on 10/15/21.
//

#include "prog/isa/utils.h"
#include "prog/isa/format_ii.h"
#include "types.h"

template <typename msp430_size_t>
MSP430::InstructionFormatII<msp430_size_t>::InstructionFormatII(msp430_word_t base_instr,
                                                                msp430_word_t opt_ext) :
    opt_ext_word(ExtensionWord(opt_ext)) {
  this->opcode = (base_instr >> 7) & 0x1FF;
  this->bw     = (base_instr >> 6) & 0x1;
  this->ad     = (base_instr >> 4) & 0x3;
  this->rdst   = (base_instr)      & 0xF;
}

template <typename msp430_size_t>
bool MSP430::InstructionFormatII<msp430_size_t>::has_extension_word() {
  return this->opt_ext_word.is_present();
}

template <typename msp430_size_t>
int MSP430::InstructionFormatII<msp430_size_t>::extra_words() {
  return this->ad == 0b01 || (this->ad == 0b11 && this->rdst == 0x0);
}

template <typename msp430_size_t>
bool MSP430::InstructionFormatII<msp430_size_t>::is_extended() {
  return this->has_extension_word();
}

template<typename msp430_size_t>
int MSP430::InstructionFormatII<msp430_size_t>::get_execution_time() {
  // TODO: impl
  return 0;
}

template class MSP430::InstructionFormatII<MSP430::msp430_byte_t>;
template class MSP430::InstructionFormatII<MSP430::msp430_word_t>;
template class MSP430::InstructionFormatII<MSP430::msp430_addr_word_t>;