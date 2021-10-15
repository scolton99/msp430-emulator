//
// Created by scolton on 10/13/21.
//

#ifndef MSP430_EMULATOR_INSTRUCTION_FWD_H
#define MSP430_EMULATOR_INSTRUCTION_FWD_H

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

  /* MSP430X Instructions */
  template <typename msp430_size_t>
  class POPMInstruction;

  template <typename msp430_size_t>
  class PUSHMInstruction;

  template <typename msp430_size_t>
  class RLAMInstruction;

  template <typename msp430_size_t>
  class RRAMInstruction;

  template <typename msp430_size_t>
  class RRCMInstruction;

  template <typename msp430_size_t>
  class RRUMInstruction;

  template <typename msp430_size_t>
  class RRUXInstruction;

  /* MSP430X Address Instructions */
  template <typename msp430_size_t>
  class ADDAInstruction;

  template <typename msp430_size_t>
  class CALLAInstruction;

  template <typename msp430_size_t>
  class CMPAInstruction;

  template <typename msp430_size_t>
  class MOVAInstruction;

  template <typename msp430_size_t>
  class SUBAInstruction;
}

#endif //MSP430_EMULATOR_INSTRUCTION_FWD_H
