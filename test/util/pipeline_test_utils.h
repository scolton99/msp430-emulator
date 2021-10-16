//
// Created by scolton on 10/15/21.
//

#ifndef MSP430_EMULATOR_PIPELINE_TEST_UTILS_H
#define MSP430_EMULATOR_PIPELINE_TEST_UTILS_H

#include "dev/cpu/cpu.h"
#include "dev/cpu/execute.h"
#include "dev/model/package.h"
#include "prog/isa/instruction.h"
#include "mem_test_utils.h"
#include "package_test_utils.h"
#include "types.h"

#define AS_REG 0b00
#define AS_IDX_SYM_BS 0b01
#define AS_IND 0b10
#define AS_INC_IMM 0b11

#define AD_REG 0b0
#define AD_IDX_SYM_ABS 0b1

#define R4 0x4000
#define R5 0x4002
#define R6 0xAB
#define R7 0x89
#define R8 0xABCD
#define R9 0x89FF

#define REG(n) this->package->get_cpu()->resolve_register(n)->get_value(0, 4)

#define PUTB(ad,v) this->package->get_memory()->set_byte(ad, v)
#define GETB(ad) this->package->get_memory()->get_byte(ad)

#define PUTW(ad,v) this->package->get_memory()->set_word(ad, v)
#define GETW(ad) this->package->get_memory()->get_word(ad)

#define PUTAW(ad,v) this->package->get_memory()->set_addr_word(ad, v)
#define GETAW(ad) this->package->get_memory()->get_addr_word(ad)

namespace Testing {
  class PipelineTest : public ::testing::Test {
  protected:
    MockPackage* package;
    MSP430::InstructionExecutionVisitor<MSP430::msp430_byte_t>*      byte_visitor;
    MSP430::InstructionExecutionVisitor<MSP430::msp430_word_t>*      word_visitor;
    MSP430::InstructionExecutionVisitor<MSP430::msp430_addr_word_t>* addr_word_visitor;

    MSP430::msp430_addr_t PC_ORIG = 0x4000;
    MSP430::msp430_addr_t PC_2_ADDR = 0x4002;

    PipelineTest() : package(nullptr),
                     byte_visitor(nullptr),
                     word_visitor(nullptr),
                     addr_word_visitor(nullptr) { }

    void SetUp() override {
      this->package = new MockPackage();
      this->package->init();

      byte_visitor      = new MSP430::InstructionExecutionVisitor<MSP430::msp430_byte_t>(this->package);
      word_visitor      = new MSP430::InstructionExecutionVisitor<MSP430::msp430_word_t>(this->package);
      addr_word_visitor = new MSP430::InstructionExecutionVisitor<MSP430::msp430_addr_word_t>(this->package);

      this->package->get_cpu()->get_pc()->set_value(0x4000, 0x4);

      /* Addresses */
      this->package->get_cpu()->resolve_register(0x4)->set_value(R4, 0x4);
      this->package->get_cpu()->resolve_register(0x5)->set_value(R5, 0x4);

      /* Bytes */
      this->package->get_cpu()->resolve_register(0x6)->set_value(R6, 0x1);
      this->package->get_cpu()->resolve_register(0x7)->set_value(R7, 0x1);

      /* Words */
      this->package->get_cpu()->resolve_register(0x8)->set_value(R8, 0x2);
      this->package->get_cpu()->resolve_register(0x9)->set_value(R9, 0x2);
    }

    ~PipelineTest() override {
      delete package;
      delete byte_visitor;
      delete word_visitor;
      delete addr_word_visitor;
    }
  };
}

#endif //MSP430_EMULATOR_PIPELINE_TEST_UTILS_H
