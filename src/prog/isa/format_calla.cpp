//
// Created by scolton on 10/15/21.
//

#include "prog/isa/format_calla.h"
#include "types.h"

template<typename msp430_size_t>
MSP430::InstructionCALLAFormat<msp430_size_t>::InstructionCALLAFormat(msp430_word_t base_instr) :
                                                                      rdst_ext(base_instr & 0xF) { }

template<typename msp430_size_t>
bool MSP430::InstructionCALLAFormat<msp430_size_t>::has_extension_word() {
  return false;
}

template<typename msp430_size_t>
int MSP430::InstructionCALLAFormat<msp430_size_t>::extra_words() {
  // TODO: impl
  return 0;
}

template<typename msp430_size_t>
int MSP430::InstructionCALLAFormat<msp430_size_t>::get_execution_time() {
  // TODO: impl
  return 0;
}

template<typename msp430_size_t>
bool MSP430::InstructionCALLAFormat<msp430_size_t>::is_extended() {
  return true;
}

template class MSP430::InstructionCALLAFormat<MSP430::msp430_byte_t>;
template class MSP430::InstructionCALLAFormat<MSP430::msp430_word_t>;
template class MSP430::InstructionCALLAFormat<MSP430::msp430_addr_word_t>;
