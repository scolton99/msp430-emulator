//
// Created by scolton on 10/11/21.
//

#ifndef MSP430_EMULATOR_EXECUTE_H
#define MSP430_EMULATOR_EXECUTE_H

#include "prog/isa/instruction.h"

namespace MSP430 {
  class InstructionExecutionVisitor : public InstructionVisitor {
  public:
    InstructionExecutionVisitor(Package* p) : InstructionVisitor(p) { }

    void visit(ADDInstruction&   instr) override;
    void visit(ADDCInstruction&  instr) override;
    void visit(ANDInstruction&   instr) override;
    void visit(BICInstruction&   instr) override;
    void visit(BITInstruction&   instr) override;
    void visit(BISInstruction&   instr) override;
    void visit(CMPInstruction&   instr) override;
    void visit(DADDInstruction&  instr) override;
    void visit(MOVInstruction&   instr) override;
    void visit(SUBInstruction&   instr) override;
    void visit(SUBCInstruction&  instr) override;
    void visit(XORInstruction&   instr) override;
    void visit(CALLInstruction&  instr) override;
    void visit(PUSHInstruction&  instr) override;
    void visit(RETIInstruction&  instr) override;
    void visit(RRAInstruction&   instr) override;
    void visit(RRCInstruction&   instr) override;
    void visit(SWPBInstruction&  instr) override;
    void visit(SXTInstruction&   instr) override;
    void visit(JCInstruction&    instr) override;
    void visit(JEQInstruction&   instr) override;
    void visit(JGEInstruction&   instr) override;
    void visit(JLInstruction&    instr) override;
    void visit(JMPInstruction&   instr) override;
    void visit(JNCInstruction&   instr) override;
    void visit(JNInstruction&    instr) override;
    void visit(JNEInstruction&   instr) override;
    void visit(POPMInstruction&  instr) override;
    void visit(PUSHMInstruction& instr) override;
    void visit(RLAMInstruction&  instr) override;
    void visit(RRAMInstruction&  instr) override;
    void visit(RRCMInstruction&  instr) override;
    void visit(RRUMInstruction&  instr) override;
    void visit(RRUXInstruction&  instr) override;
    void visit(ADDAInstruction&  instr) override;
    void visit(CMPAInstruction&  instr) override;
    void visit(MOVAInstruction&  instr) override;
    void visit(SUBAInstruction&  instr) override;
  };
}

#endif //MSP430_EMULATOR_EXECUTE_H
