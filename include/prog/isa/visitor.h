//
// Created by scolton on 10/13/21.
//

#ifndef MSP430_EMULATOR_VISITOR_H
#define MSP430_EMULATOR_VISITOR_H

#include "dev/model/package.h"

namespace MSP430 {
  /* Format I Instructions */
  template <typename msp430_size_t>
  class ADDInstruction;

  template <typename msp430_size_t>
  class ADDCInstruction;

  template <typename msp430_size_t>
  class ANDInstruction;

  template <typename msp430_size_t>
  class BICInstruction;

  template <typename msp430_size_t>
  class BITInstruction;

  template <typename msp430_size_t>
  class BISInstruction;

  template <typename msp430_size_t>
  class CMPInstruction;

  template <typename msp430_size_t>
  class DADDInstruction;

  template <typename msp430_size_t>
  class MOVInstruction;

  template <typename msp430_size_t>
  class SUBInstruction;

  template <typename msp430_size_t>
  class SUBCInstruction;

  template <typename msp430_size_t>
  class XORInstruction;

  /* Format II Instructions */
  template <typename msp430_size_t>
  class CALLInstruction;

  template <typename msp430_size_t>
  class PUSHInstruction;

  template <typename msp430_size_t>
  class RETIInstruction;

  template <typename msp430_size_t>
  class RRAInstruction;

  template <typename msp430_size_t>
  class RRCInstruction;

  template <typename msp430_size_t>
  class SWPBInstruction;

  template <typename msp430_size_t>
  class SXTInstruction;

  /* Jump Instructions */
  template <typename msp430_size_t>
  class JCInstruction;

  template <typename msp430_size_t>
  class JEQInstruction;

  template <typename msp430_size_t>
  class JGEInstruction;

  template <typename msp430_size_t>
  class JLInstruction;

  template <typename msp430_size_t>
  class JMPInstruction;

  template <typename msp430_size_t>
  class JNCInstruction;

  template <typename msp430_size_t>
  class JNInstruction;

  template <typename msp430_size_t>
  class JNEInstruction;

  /* MSP430X PUSHM/POPM Instructions */
  template <typename msp430_size_t>
  class POPMInstruction;

  template <typename msp430_size_t>
  class PUSHMInstruction;

  /* MSP430X RRXM Instructions */
  template <typename msp430_size_t>
  class RLAMInstruction;

  template <typename msp430_size_t>
  class RRAMInstruction;

  template <typename msp430_size_t>
  class RRCMInstruction;

  template <typename msp430_size_t>
  class RRUMInstruction;

  /* MSP430X CALLA Instruction */
  template <typename msp430_size_t>
  class CALLAInstruction;

  /* MSP430X Address Instructions */
  template <typename msp430_size_t>
  class ADDAInstruction;

  template <typename msp430_size_t>
  class CMPAInstruction;

  template <typename msp430_size_t>
  class MOVAInstruction;

  template <typename msp430_size_t>
  class SUBAInstruction;

  template <typename msp430_size_t>
  class InstructionVisitor {
  public:
    InstructionVisitor() = default;
    virtual ~InstructionVisitor() = default;

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
    virtual void visit(CALLAInstruction<msp430_size_t>&) = 0;
    virtual void visit(ADDAInstruction<msp430_size_t>&)  = 0;
    virtual void visit(CMPAInstruction<msp430_size_t>&)  = 0;
    virtual void visit(MOVAInstruction<msp430_size_t>&)  = 0;
    virtual void visit(SUBAInstruction<msp430_size_t>&)  = 0;
  };
}

#endif //MSP430_EMULATOR_VISITOR_H
