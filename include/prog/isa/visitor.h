//
// Created by scolton on 10/13/21.
//

#ifndef MSP430_EMULATOR_VISITOR_H
#define MSP430_EMULATOR_VISITOR_H

#include "dev/model/package.h"
#include "instruction_fwd.h"

namespace MSP430 {
  class InstructionVisitor {
  private:
    Package* package;
  public:
    explicit InstructionVisitor(Package* package) : package(package) { }

    virtual void visit(ADDInstruction&)   = 0;
    virtual void visit(ADDCInstruction&)  = 0;
    virtual void visit(ANDInstruction&)   = 0;
    virtual void visit(BICInstruction&)   = 0;
    virtual void visit(BITInstruction&)   = 0;
    virtual void visit(BISInstruction&)   = 0;
    virtual void visit(CMPInstruction&)   = 0;
    virtual void visit(DADDInstruction&)  = 0;
    virtual void visit(MOVInstruction&)   = 0;
    virtual void visit(SUBInstruction&)   = 0;
    virtual void visit(SUBCInstruction&)  = 0;
    virtual void visit(XORInstruction&)   = 0;
    virtual void visit(CALLInstruction&)  = 0;
    virtual void visit(PUSHInstruction&)  = 0;
    virtual void visit(RETIInstruction&)  = 0;
    virtual void visit(RRAInstruction&)   = 0;
    virtual void visit(RRCInstruction&)   = 0;
    virtual void visit(SWPBInstruction&)  = 0;
    virtual void visit(SXTInstruction&)   = 0;
    virtual void visit(JCInstruction&)    = 0;
    virtual void visit(JEQInstruction&)   = 0;
    virtual void visit(JGEInstruction&)   = 0;
    virtual void visit(JLInstruction&)    = 0;
    virtual void visit(JMPInstruction&)   = 0;
    virtual void visit(JNCInstruction&)   = 0;
    virtual void visit(JNInstruction&)    = 0;
    virtual void visit(JNEInstruction&)   = 0;
    virtual void visit(POPMInstruction&)  = 0;
    virtual void visit(PUSHMInstruction&) = 0;
    virtual void visit(RLAMInstruction&)  = 0;
    virtual void visit(RRAMInstruction&)  = 0;
    virtual void visit(RRCMInstruction&)  = 0;
    virtual void visit(RRUMInstruction&)  = 0;
    virtual void visit(RRUXInstruction&)  = 0;
    virtual void visit(ADDAInstruction&)  = 0;
    virtual void visit(CMPAInstruction&)  = 0;
    virtual void visit(MOVAInstruction&)  = 0;
    virtual void visit(SUBAInstruction&)  = 0;
  };
}

#endif //MSP430_EMULATOR_VISITOR_H
