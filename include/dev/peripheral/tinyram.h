//
// Created by scolton on 10/12/21.
//

#ifndef MSP430_EMULATOR_TINYRAM_H
#define MSP430_EMULATOR_TINYRAM_H

#include "dev/mem/mem.h"

namespace MSP430 {
  class TinyRAM : public MemoryProvider {
  private:
    std::vector<msp430_byte_t> memory;
  public:
    TinyRAM();
    msp430_byte_t get(msp430_addr_t)                override;
    void          set(msp430_addr_t, msp430_byte_t) override;
  };
}

#endif //MSP430_EMULATOR_TINYRAM_H
