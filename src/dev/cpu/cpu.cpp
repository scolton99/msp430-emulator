//
// Created by scolton on 10/10/21.
//

#include "dev/cpu/cpu.h"
#include "dev/cpu/decode.h"
#include "dev/cpu/execute.h"
#include "prog/isa/instruction.h"

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
  static InstructionExecutionVisitor visitor(this->package);

  if (instruction_ticks_remaining == 0) {
    MSP430::msp430_addr_t instr_addr = this->get_pc()->get_value(0, sizeof(msp430_addr_t));

    MSP430::Instruction* instruction = instruction_decode(this->package, instr_addr);
    instruction_ticks_remaining      = instruction->get_execution_time();

    instruction->accept(visitor);
  } else {
    --instruction_ticks_remaining;
  }
}