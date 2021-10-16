//
// Created by scolton on 10/15/21.
//

#include "prog/isa/utils.h"
#include "prog/isa/format_jump.h"
#include "types.h"

template <typename msp430_size_t>
MSP430::InstructionJumpFormat<msp430_size_t>::InstructionJumpFormat(msp430_word_t base_instr) {
  this->opcode    = (base_instr >> 13) & 0x7;
  this->condition = (base_instr >> 10) & 0x7;
  this->offset    = (base_instr)       & 0x3FF;
}

template <typename msp430_size_t>
bool MSP430::InstructionJumpFormat<msp430_size_t>::has_extension_word() {
  return false;
}

template <typename msp430_size_t>
int MSP430::InstructionJumpFormat<msp430_size_t>::extra_words() {
  return 0;
}

template <typename msp430_size_t>
bool MSP430::InstructionJumpFormat<msp430_size_t>::is_extended() {
  return false;
}

template<typename msp430_size_t>
int MSP430::InstructionJumpFormat<msp430_size_t>::get_execution_time() {
  // TODO: impl
  return 0;
}

template class MSP430::InstructionJumpFormat<MSP430::msp430_byte_t>;
template class MSP430::InstructionJumpFormat<MSP430::msp430_word_t>;
template class MSP430::InstructionJumpFormat<MSP430::msp430_addr_word_t>;
