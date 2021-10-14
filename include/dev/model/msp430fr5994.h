//
// Created by scolton on 10/8/21.
//

#ifdef DEV_MODEL_MSP430FR5994

#ifndef MSP430_EMULATOR_MSP430FR5994_H
#define MSP430_EMULATOR_MSP430FR5994_H

#include "package.h"
#include "dev/peripheral/tinyram/tinyram.h"

#define MSP430FR5994_TINYRAM_START 0xA;
#define MSP430FR5994_TINYRAM_SIZE  22;

namespace MSP430 {
  class MSP430FR5994 : public Package {
  private:
    TinyRAM tiny_ram;
  public:
    MSP430FR5994() : Package(new CPUX()) { }
    void init() override;
  };
}

#endif //MSP430_EMULATOR_MSP430FR5994_H

#endif
