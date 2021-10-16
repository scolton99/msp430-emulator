//
// Created by scolton on 10/12/21.
//

#include <gtest/gtest.h>
#include "dev/cpu/register.h"
#include "test_utils.h"

TEST(RegisterTest, GPRegisterXTest) {
  MSP430::GPRegisterX reg;

  reg.set_value(0x32, 0x4);
  EXPECT_EQ(reg.get_value(0x0, 0x4), 0x32);

  reg.set_value(INT32_MAX, 0x4);
  EXPECT_EQ(reg.get_value(0x0, 0x4), 0xFFFFF);
}

TEST(RegisterTest, SRRegisterXTest) {
  MSP430::SRRegisterX reg;

  reg.set_value(0b101010101u, 0x4);

  EXPECT_EQ(reg.V(), 1);
  EXPECT_EQ(reg.SCG1(), 0);
  EXPECT_EQ(reg.SCG0(), 1);
  EXPECT_EQ(reg.OSCOFF(), 0);
  EXPECT_EQ(reg.CPUOFF(), 1);
  EXPECT_EQ(reg.GIE(), 0);
  EXPECT_EQ(reg.N(), 1);
  EXPECT_EQ(reg.Z(), 0);
  EXPECT_EQ(reg.C(), 1);

  EXPECT_THROW_MSG(reg.get_value(0b100, 0x4),
                   std::runtime_error,
                   "Invalid As value for SP/CG1");

  reg.clrV();
  reg.setSCG1();
  reg.clrSCG0();
  reg.setOSCOFF();
  reg.clrCPUOFF();
  reg.setGIE();
  reg.clrN();
  reg.setZ();
  reg.clrC();

  EXPECT_EQ(reg.get_value(0b00, 0x4), 0b010101010);

  reg.setV();
  EXPECT_EQ(reg.V(), 1);

  reg.clrSCG1();
  EXPECT_EQ(reg.SCG1(), 0);

  reg.setSCG0();
  EXPECT_EQ(reg.SCG0(), 1);

  reg.clrOSCOFF();
  EXPECT_EQ(reg.OSCOFF(), 0);

  reg.setCPUOFF();
  EXPECT_EQ(reg.CPUOFF(), 1);

  reg.clrGIE();
  EXPECT_EQ(reg.GIE(), 0);

  reg.setN();
  EXPECT_EQ(reg.N(), 1);

  reg.clrZ();
  EXPECT_EQ(reg.Z(), 0);

  reg.setC();
  EXPECT_EQ(reg.C(), 1);

  reg.setV(0);
  reg.setSCG0(0);
  reg.setCPUOFF(0);
  reg.setN(0);
  reg.setC(0);

  EXPECT_EQ(reg.get_value(0b00, 0x4), 0);
}

TEST(RegisterTest, CG1RegisterXTest) {
  MSP430::SRRegisterX reg;

  reg.set_value(0xABCD, 0x2);

  EXPECT_EQ(reg.get_value(0b00, 0x4), 0xABCD);
  EXPECT_EQ(reg.get_value(0b01, 0x4), 0);
  EXPECT_EQ(reg.get_value(0b10, 0x4), 0x4);
  EXPECT_EQ(reg.get_value(0b11, 0x4), 0x8);
}

TEST(RegisterTest, CG2RegisterXTest) {
  MSP430::CG2RegisterX reg;

  EXPECT_THROW_MSG(reg.set_value(0x1234, 0x2),
                   std::runtime_error,
                   "Can't set CG2 value");
  EXPECT_THROW_MSG(reg.get_value(0b100, 0x4),
                   std::runtime_error,
                   "Invalid value for As in CG register");

  EXPECT_EQ(reg.get_value(0b00, 0x4), 0);
  EXPECT_EQ(reg.get_value(0b01, 0x4), 0x1);
  EXPECT_EQ(reg.get_value(0b10, 0x4), 0x2);
  EXPECT_EQ(reg.get_value(0b11, 0x4), 0xFFFFF);
}