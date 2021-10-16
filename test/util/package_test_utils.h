//
// Created by scolton on 10/15/21.
//

#ifndef MSP430_EMULATOR_PACKAGE_TEST_UTILS_H
#define MSP430_EMULATOR_PACKAGE_TEST_UTILS_H

#include "dev/model/package.h"
#include "mem_test_utils.h"

namespace Testing {
  class MockPackage : public MSP430::Package {
  public:
    MockPackage() : MSP430::Package(new MSP430::CPUX(this)) { }
    ~MockPackage() override = default;
    void init() override {
      auto* mp = new MockProvider;
      MSP430::MemoryMapping mapping {mp, 0x4000, 0xC000, 0x0};

      this->memory.add_mapping(mapping);
    }
  };
}

#endif //MSP430_EMULATOR_PACKAGE_TEST_UTILS_H
