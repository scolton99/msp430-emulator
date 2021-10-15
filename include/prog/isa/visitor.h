//
// Created by scolton on 10/13/21.
//

#ifndef MSP430_EMULATOR_VISITOR_H
#define MSP430_EMULATOR_VISITOR_H

#include "dev/model/package.h"
#include "instruction_fwd.h"

namespace MSP430 {
  template <typename msp430_size_t>
  class InstructionVisitor {
  private:
    Package* package;
  public:
    explicit InstructionVisitor(Package* package) : package(package) { }

    virtual void visit(ADDInstruction<msp430_size_t>&)   = 0;
    virtual void visit(ADDCInstruction<msp430_size_t>&)  = 0;
    virtual void visit(ANDInstruction<msp430_size_t>&)   = 0;
    virtual void visit(BICInstruction<msp430_size_t>&)   = 0;
    virtual void visit(BITInstruction<msp430_size_t>&)   = 0;
    virtual void visit(BISInstruction<msp430_size_t>&)   = 0;
    virtual void visit(CMPInstruction<msp430_size_t>&)   = 0;
    virtual void visit(DADDInstruction<msp430_size_t>&)  = 0;
    virtual void visit(MOVInstruction<msp430_size_t>&)   = 0;
    virtual void visit(SUBInstruction<msp430_size_t>&)   = 0;
    virtual void visit(SUBCInstruction<msp430_size_t>&)  = 0;
    virtual void visit(XORInstruction<msp430_size_t>&)   = 0;
    virtual void visit(CALLInstruction<msp430_size_t>&)  = 0;
    virtual void visit(PUSHInstruction<msp430_size_t>&)  = 0;
    virtual void visit(RETIInstruction<msp430_size_t>&)  = 0;
    virtual void visit(RRAInstruction<msp430_size_t>&)   = 0;
    virtual void visit(RRCInstruction<msp430_size_t>&)   = 0;
    virtual void visit(SWPBInstruction<msp430_size_t>&)  = 0;
    virtual void visit(SXTInstruction<msp430_size_t>&)   = 0;
    virtual void visit(JCInstruction<msp430_size_t>&)    = 0;
    virtual void visit(JEQInstruction<msp430_size_t>&)   = 0;
    virtual void visit(JGEInstruction<msp430_size_t>&)   = 0;
    virtual void visit(JLInstruction<msp430_size_t>&)    = 0;
    virtual void visit(JMPInstruction<msp430_size_t>&)   = 0;
    virtual void visit(JNCInstruction<msp430_size_t>&)   = 0;
    virtual void visit(JNInstruction<msp430_size_t>&)    = 0;
    virtual void visit(JNEInstruction<msp430_size_t>&)   = 0;
    virtual void visit(POPMInstruction<msp430_size_t>&)  = 0;
    virtual void visit(PUSHMInstruction<msp430_size_t>&) = 0;
    virtual void visit(RLAMInstruction<msp430_size_t>&)  = 0;
    virtual void visit(RRAMInstruction<msp430_size_t>&)  = 0;
    virtual void visit(RRCMInstruction<msp430_size_t>&)  = 0;
    virtual void visit(RRUMInstruction<msp430_size_t>&)  = 0;
    virtual void visit(RRUXInstruction<msp430_size_t>&)  = 0;
    virtual void visit(ADDAInstruction<msp430_size_t>&)  = 0;
    virtual void visit(CMPAInstruction<msp430_size_t>&)  = 0;
    virtual void visit(MOVAInstruction<msp430_size_t>&)  = 0;
    virtual void visit(SUBAInstruction<msp430_size_t>&)  = 0;
  };
}

#endif //MSP430_EMULATOR_VISITOR_H
