//
// Created by scolton on 10/12/21.
//

#ifndef MSP430_EMULATOR_MEMORY_MAP_TEST_H
#define MSP430_EMULATOR_MEMORY_MAP_TEST_H

#include <vector>
#include "dev/mem/mem.h"

class MockProvider : public MSP430::MemoryProvider {
private:
  std::vector<MSP430::msp430_byte_t> memory;
public:
  MockProvider();
  MSP430::msp430_byte_t get(MSP430::msp430_addr_t)                        override;
  void                  set(MSP430::msp430_addr_t, MSP430::msp430_byte_t) override;
};

#endif //MSP430_EMULATOR_MEMORY_MAP_TEST_H
