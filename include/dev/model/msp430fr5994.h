//
// Created by scolton on 10/8/21.
//

#ifndef MSP430_EMULATOR_MSP430FR5994_H
#define MSP430_EMULATOR_MSP430FR5994_H

#include "dev/peripheral/tinyram.h"
#include "package.h"

#define MSP430FR5994_TINYRAM_START 0xA
#define MSP430FR5994_TINYRAM_SIZE  22

namespace MSP430 {
  class MSP430FR5994 : public Package {
  private:
    TinyRAM tiny_ram;
  public:
    MSP430FR5994() : Package(new CPUX(this)) { }
    void init() override;
  };
}

#endif //MSP430_EMULATOR_MSP430FR5994_H
