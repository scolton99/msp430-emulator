//
// Created by scolton on 10/15/21.
//

#ifndef MSP430_EMULATOR_CPU_TEST_UTILS_H
#define MSP430_EMULATOR_CPU_TEST_UTILS_H

#include <gtest/gtest.h>
#include "package_test_utils.h"
#include "types.h"

namespace Testing {
  class CPUXTest : public ::testing::Test {
  protected:
    MSP430::Package* package;
    MSP430::msp430_addr_t default_pc = 0x4000;

    void putw(MSP430::msp430_addr_t addr, MSP430::msp430_word_t word) {
      this->package->get_memory()->set_word(addr, word);
    }

    void SetUp() override {
      this->package = new MockPackage();
      package->init();

      package->get_cpu()->get_pc()->set_value(default_pc, sizeof(MSP430::msp430_addr_t));
    };

    ~CPUXTest() override {
      delete package;
    }
  };
}

#endif //MSP430_EMULATOR_CPU_TEST_UTILS_H
