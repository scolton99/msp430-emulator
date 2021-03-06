//
// Created by scolton on 10/10/21.
//

#include <stdexcept>
#include "dev/cpu/cpu.h"
#include "dev/cpu/decode.h"

MSP430::IRegister* MSP430::CPUX::resolve_register(uint8_t reg_num) {
  switch(reg_num) {
    case 0:
      return r0;
    case 1:
      return r1;
    case 2:
      return r2;
    case 3:
      return r3;
    case 4:
      return r4;
    case 5:
      return r5;
    case 6:
      return r6;
    case 7:
      return r7;
    case 8:
      return r8;
    case 9:
      return r9;
    case 10:
      return r10;
    case 11:
      return r11;
    case 12:
      return r12;
    case 13:
      return r13;
    case 14:
      return r14;
    case 15:
      return r15;
    default:
      throw std::runtime_error("Invalid register");
  }
}

MSP430::CPUX::CPUX(Package* package) : r0 (new GPRegisterX()),
                                       r1 (new GPRegisterX()),
                                       r2 (new SRRegisterX()),
                                       r3 (new CG2RegisterX()),
                                       r4 (new GPRegisterX()),
                                       r5 (new GPRegisterX()),
                                       r6 (new GPRegisterX()),
                                       r7 (new GPRegisterX()),
                                       r8 (new GPRegisterX()),
                                       r9 (new GPRegisterX()),
                                       r10(new GPRegisterX()),
                                       r11(new GPRegisterX()),
                                       r12(new GPRegisterX()),
                                       r13(new GPRegisterX()),
                                       r14(new GPRegisterX()),
                                       r15(new GPRegisterX()),
                                       package(package) {

}

MSP430::CPUX::~CPUX() {
  delete r0;
  delete r1;
  delete r2;
  delete r3;
  delete r4;
  delete r5;
  delete r6;
  delete r7;
  delete r8;
  delete r9;
  delete r10;
  delete r11;
  delete r12;
  delete r13;
  delete r14;
  delete r15;
}

MSP430::IRegister* MSP430::CPUX::get_pc() {
  return this->r0;
}

MSP430::IRegister* MSP430::CPUX::get_sp() {
  return this->r1;
}

MSP430::IRegister* MSP430::CPUX::get_sr() {
  return this->r2;
}

void MSP430::CPUX::tick() {
  static int instruction_ticks_remaining = 0;

  if (instruction_ticks_remaining == 0) {
    msp430_addr_t instr_addr = this->get_pc()->get_value(0, sizeof(msp430_addr_t));

    msp430_word_t ext_word, raw_instr;
    fill_instruction_and_ext(this->package, instr_addr, ext_word, raw_instr);

    InstructionWidth width = next_instruction_width(ext_word, raw_instr);

    switch (width) {
      case BYTE: {
        InstructionExecutionVisitor<msp430_byte_t> visitor(this->package);
        MSP430::Instruction<msp430_byte_t>*        instruction = instruction_decode<msp430_byte_t>(this->package,
                                                                                                   instr_addr);

        instruction_ticks_remaining = instruction->get_execution_time();
        instruction->accept(visitor);
        break;
      }
      case WORD: {
        InstructionExecutionVisitor<msp430_word_t> visitor(this->package);
        MSP430::Instruction<msp430_word_t>*        instruction = instruction_decode<msp430_word_t>(this->package,
                                                                                                   instr_addr);

        instruction_ticks_remaining = instruction->get_execution_time();
        instruction->accept(visitor);
        break;
      }
      case ADDRESS_WORD: {
        InstructionExecutionVisitor<msp430_addr_word_t> visitor(this->package);
        MSP430::Instruction<msp430_addr_word_t>*        instruction = instruction_decode<msp430_addr_word_t>(this->package,
                                                                                                             instr_addr);

        instruction_ticks_remaining = instruction->get_execution_time();
        instruction->accept(visitor);
        break;
      }
    }
  } else {
    --instruction_ticks_remaining;
  }
}

MSP430::msp430_word_t MSP430::CPUX::read_word_and_inc_pc() {
  msp430_addr_t pc   = this->get_pc()->get_value(0, 0x4);
  msp430_word_t word = this->package->get_memory()->get_word(pc);

  this->get_pc()->set_value(pc + 0x2, sizeof(msp430_addr_t));

  return word;
}


int32_t MSP430::CPUX::addr_word_sxt_32(msp430_addr_word_t addr_word) {
  auto ret = static_cast<int32_t>(addr_word);

  if (ret & 0x00080000)
    ret |= (signed) 0xFFF80000;

  return ret;
}

int32_t MSP430::CPUX::word_sxt_32(msp430_word_t word) {
  auto ret = static_cast<int16_t>(word);

  if (ret & 0x8000)
    ret |= (signed) 0xFFFF8000;

  return ret;
}