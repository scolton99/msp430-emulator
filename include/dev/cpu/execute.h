//
// Created by scolton on 10/11/21.
//

#ifndef MSP430_EMULATOR_EXECUTE_H
#define MSP430_EMULATOR_EXECUTE_H

#include "dev/model/package.h"
#include "prog/isa/visitor.h"
#include "prog/isa/instruction_fwd.h"

namespace MSP430 {
  template <typename msp430_size_t>
  class InstructionExecutionVisitor : public InstructionVisitor<msp430_size_t> {
  public:
    explicit InstructionExecutionVisitor(Package* p) : InstructionVisitor<msp430_size_t>(p) { }

    void visit(ADDInstruction<msp430_size_t>&   instr) override;
    void visit(ADDCInstruction<msp430_size_t>&  instr) override;
    void visit(ANDInstruction<msp430_size_t>&   instr) override;
    void visit(BICInstruction<msp430_size_t>&   instr) override;
    void visit(BITInstruction<msp430_size_t>&   instr) override;
    void visit(BISInstruction<msp430_size_t>&   instr) override;
    void visit(CMPInstruction<msp430_size_t>&   instr) override;
    void visit(DADDInstruction<msp430_size_t>&  instr) override;
    void visit(MOVInstruction<msp430_size_t>&   instr) override;
    void visit(SUBInstruction<msp430_size_t>&   instr) override;
    void visit(SUBCInstruction<msp430_size_t>&  instr) override;
    void visit(XORInstruction<msp430_size_t>&   instr) override;
    void visit(CALLInstruction<msp430_size_t>&  instr) override;
    void visit(PUSHInstruction<msp430_size_t>&  instr) override;
    void visit(RETIInstruction<msp430_size_t>&  instr) override;
    void visit(RRAInstruction<msp430_size_t>&   instr) override;
    void visit(RRCInstruction<msp430_size_t>&   instr) override;
    void visit(SWPBInstruction<msp430_size_t>&  instr) override;
    void visit(SXTInstruction<msp430_size_t>&   instr) override;
    void visit(JCInstruction<msp430_size_t>&    instr) override;
    void visit(JEQInstruction<msp430_size_t>&   instr) override;
    void visit(JGEInstruction<msp430_size_t>&   instr) override;
    void visit(JLInstruction<msp430_size_t>&    instr) override;
    void visit(JMPInstruction<msp430_size_t>&   instr) override;
    void visit(JNCInstruction<msp430_size_t>&   instr) override;
    void visit(JNInstruction<msp430_size_t>&    instr) override;
    void visit(JNEInstruction<msp430_size_t>&   instr) override;
    void visit(POPMInstruction<msp430_size_t>&  instr) override;
    void visit(PUSHMInstruction<msp430_size_t>& instr) override;
    void visit(RLAMInstruction<msp430_size_t>&  instr) override;
    void visit(RRAMInstruction<msp430_size_t>&  instr) override;
    void visit(RRCMInstruction<msp430_size_t>&  instr) override;
    void visit(RRUMInstruction<msp430_size_t>&  instr) override;
    void visit(RRUXInstruction<msp430_size_t>&  instr) override;
    void visit(ADDAInstruction<msp430_size_t>&  instr) override;
    void visit(CMPAInstruction<msp430_size_t>&  instr) override;
    void visit(MOVAInstruction<msp430_size_t>&  instr) override;
    void visit(SUBAInstruction<msp430_size_t>&  instr) override;
  };
}

#endif //MSP430_EMULATOR_EXECUTE_H
