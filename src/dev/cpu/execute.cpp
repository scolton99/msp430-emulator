//
// Created by scolton on 10/15/21.
//

#include "dev/cpu/execute.h"
#include "prog/isa/instructions.h"
#include "types.h"

template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::ADDInstruction<msp430_size_t>& instr) {
  msp430_size_t src = instr.get_src_value(this->package);
  msp430_size_t dst = instr.get_dst_value(this->package);

  instr.set_dst_value(this->package, src + dst);
}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::ADDCInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::ANDInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::BICInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::BITInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::BISInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::CMPInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::DADDInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::MOVInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::SUBInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::SUBCInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::XORInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::CALLInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::PUSHInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::RETIInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::RRAInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::RRCInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::SWPBInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::SXTInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::JCInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::JEQInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::JGEInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::JLInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::JMPInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::JNCInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::JNInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::JNEInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::POPMInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::PUSHMInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::RLAMInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::RRAMInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::RRCMInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::RRUMInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::CALLAInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::ADDAInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::CMPAInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::MOVAInstruction<msp430_size_t>& instr) {

}


template <typename msp430_size_t>
void MSP430::InstructionExecutionVisitor<msp430_size_t>::visit(MSP430::SUBAInstruction<msp430_size_t>& instr) {

}

template class MSP430::InstructionExecutionVisitor<MSP430::msp430_byte_t>;
template class MSP430::InstructionExecutionVisitor<MSP430::msp430_word_t>;
template class MSP430::InstructionExecutionVisitor<MSP430::msp430_addr_word_t>;