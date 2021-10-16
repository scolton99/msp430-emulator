//
// Created by scolton on 10/15/21.
//

#include <gtest/gtest.h>
#include "dev/cpu/cpu.h"
#include "cpu_test_utils.h"

namespace Testing {
  TEST_F(CPUXTest, ReadAndPCIncrement) {
    MSP430::msp430_word_t write_word = 0xABCD;

    putw(default_pc, write_word);
    MSP430::msp430_word_t word = package->get_cpu()->read_word_and_inc_pc();
    ASSERT_EQ(word, write_word);
    ASSERT_EQ(package->get_cpu()->get_pc()->get_value(0x0, sizeof(MSP430::msp430_addr_t)), default_pc + 0x2);
  }

  TEST_F(CPUXTest, AddrWordSXT32) {
    int32_t extended = package->get_cpu()->addr_word_sxt_32(0xE8000);
    ASSERT_EQ(extended, 0xFFFE8000);
  }

  TEST_F(CPUXTest, WordSXT32) {
    int32_t extended = package->get_cpu()->word_sxt_32(0xC0FE);
    ASSERT_EQ(extended, 0xFFFFC0FE);
  }

  TEST_F(CPUXTest, GetPC) {
    ASSERT_EQ(package->get_cpu()->resolve_register(0), package->get_cpu()->get_pc());
  }

  TEST_F(CPUXTest, GetSR) {
    ASSERT_EQ(package->get_cpu()->resolve_register(2), package->get_cpu()->get_sr());
  }

  TEST_F(CPUXTest, GetSP) {
    ASSERT_EQ(package->get_cpu()->resolve_register(1), package->get_cpu()->get_sp());
  }
}
