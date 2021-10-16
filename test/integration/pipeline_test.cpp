//
// Created by scolton on 10/15/21.
//
    
#include <gtest/gtest.h>
#include "pipeline_test_utils.h"
#include "prog/isa/instructions.h"

using namespace MSP430;

namespace Testing {
  TEST_F(PipelineTest, AddRegRegByte) {
    ADDInstruction<msp430_byte_t> byteExtWord(6, AS_REG, AD_REG, 9);
    byteExtWord.accept(*byte_visitor);

    EXPECT_EQ(REG(6), 0xAB);
    EXPECT_EQ(REG(9), 0xAA);

    ADDInstruction<msp430_byte_t> wordExtByte(8, AS_REG, AD_REG, 7);
    wordExtByte.accept(*byte_visitor);

    EXPECT_EQ(REG(8), 0xABCD);
    EXPECT_EQ(REG(7), 0x56);
  }

  TEST_F(PipelineTest, AddRegRegWord) {
    ADDInstruction<msp430_word_t> instr(8, AS_REG, AD_REG, 9);
    instr.accept(*word_visitor);

    EXPECT_EQ(REG(8), R8);
    EXPECT_EQ(REG(9), (R8 + R9) & 0xFFFF);
  }

  TEST_F(PipelineTest, AddRegIdxByte) {
    PUTW(PC_ORIG, 0x20);
    PUTW(REG(5) + 0x20, 0x0707);
    ADDInstruction<msp430_byte_t> instr(9, AS_REG, AD_IDX_SYM_ABS, 5);
    instr.accept(*byte_visitor);

    EXPECT_EQ(GETB(REG(5) + 0x20), (REG(9) + 0x07) & 0xFF);
  }

  TEST_F(PipelineTest, AddRegIdxWord) {
    PUTW(PC_ORIG, 0x10);
    PUTW(REG(4) + 0x10, 0x0080);
    ADDInstruction<msp430_word_t> instr(8, AS_REG, AD_IDX_SYM_ABS, 4);
    instr.accept(*word_visitor);

    EXPECT_EQ(GETW(REG(4) + 0x10), REG(8) + 0x0080);
  }

  TEST_F(PipelineTest, AddRegSymByte) {
    PUTW(PC_ORIG, 0x1000);
    PUTW(PC_ORIG + 0x1000, 0x3B);

    ADDInstruction<msp430_byte_t> instr(6, AS_REG, AD_IDX_SYM_ABS, 0);
    instr.accept(*byte_visitor);

    EXPECT_EQ(REG(0), PC_ORIG + 0x2);
    EXPECT_EQ(GETB(REG(0) - 0x2 + 0x1000), (0x3B + REG(6)) & 0xFF);
  }

  TEST_F(PipelineTest, AddRegSymWord) {
    
  }

  TEST_F(PipelineTest, AddRegAbsByte) {
    
  }

  TEST_F(PipelineTest, AddRegAbsWord) {
    
  }

  TEST_F(PipelineTest, AddIdxRegByte) {
    
  }

  TEST_F(PipelineTest, AddIdxRegWord) {
    
  }

  TEST_F(PipelineTest, AddIdxIdxByte) {
    
  }

  TEST_F(PipelineTest, AddIdxIdxWord) {
    
  }

  TEST_F(PipelineTest, AddIdxSymByte) {
    
  }

  TEST_F(PipelineTest, AddIdxSymWord) {
    
  }

  TEST_F(PipelineTest, AddIdxAbsByte) {
    
  }

  TEST_F(PipelineTest, AddIdxAbsWord) {
    
  }

  TEST_F(PipelineTest, AddSymRegByte) {
    
  }

  TEST_F(PipelineTest, AddSymRegWord) {
    
  }

  TEST_F(PipelineTest, AddSymIdxByte) {
    
  }

  TEST_F(PipelineTest, AddSymIdxWord) {
    
  }

  TEST_F(PipelineTest, AddSymSymByte) {
    
  }

  TEST_F(PipelineTest, AddSymSymWord) {
    
  }

  TEST_F(PipelineTest, AddSymAbsByte) {
    
  }

  TEST_F(PipelineTest, AddSymAbsWord) {
    
  }

  TEST_F(PipelineTest, AddAbsRegByte) {
    
  }

  TEST_F(PipelineTest, AddAbsRegWord) {
    
  }

  TEST_F(PipelineTest, AddAbsIdxByte) {
    
  }

  TEST_F(PipelineTest, AddAbsIdxWord) {
    
  }

  TEST_F(PipelineTest, AddAbsSymByte) {
    
  }

  TEST_F(PipelineTest, AddAbsSymWord) {
    
  }

  TEST_F(PipelineTest, AddAbsAbsByte) {
    
  }

  TEST_F(PipelineTest, AddAbsAbsWord) {
    
  }

  TEST_F(PipelineTest, AddIndRegByte) {
    
  }

  TEST_F(PipelineTest, AddIndRegWord) {
    
  }

  TEST_F(PipelineTest, AddIndIdxByte) {
    
  }

  TEST_F(PipelineTest, AddIndIdxWord) {
    
  }

  TEST_F(PipelineTest, AddIndSymByte) {
    
  }

  TEST_F(PipelineTest, AddIndSymWord) {
    
  }

  TEST_F(PipelineTest, AddIndAbsByte) {
    
  }

  TEST_F(PipelineTest, AddIndAbsWord) {
    
  }

  TEST_F(PipelineTest, AddIncRegByte) {
    
  }

  TEST_F(PipelineTest, AddIncRegWord) {
    
  }

  TEST_F(PipelineTest, AddIncIdxByte) {
    
  }

  TEST_F(PipelineTest, AddIncIdxWord) {
    
  }

  TEST_F(PipelineTest, AddIncSymByte) {
    
  }

  TEST_F(PipelineTest, AddIncSymWord) {
    
  }

  TEST_F(PipelineTest, AddIncAbsByte) {
    
  }

  TEST_F(PipelineTest, AddIncAbsWord) {
    
  }

  TEST_F(PipelineTest, AddImmRegByte) {
    
  }

  TEST_F(PipelineTest, AddImmRegWord) {
    
  }

  TEST_F(PipelineTest, AddImmIdxByte) {
    
  }

  TEST_F(PipelineTest, AddImmIdxWord) {
    
  }

  TEST_F(PipelineTest, AddImmSymByte) {
    
  }

  TEST_F(PipelineTest, AddImmSymWord) {
    
  }

  TEST_F(PipelineTest, AddImmAbsByte) {
    
  }

  TEST_F(PipelineTest, AddImmAbsWord) {
    
  }

  TEST_F(PipelineTest, XAddIdxRegByte) {
    
  }

  TEST_F(PipelineTest, XAddIdxRegWord) {
    
  }

  TEST_F(PipelineTest, XAddIdxRegAddressWord) {
    
  }

  TEST_F(PipelineTest, XAddIdxIdxByte) {
    
  }

  TEST_F(PipelineTest, XAddIdxIdxWord) {
    
  }

  TEST_F(PipelineTest, XAddIdxIdxAddressWord) {
    
  }

  TEST_F(PipelineTest, XAddIdxSymByte) {
    
  }

  TEST_F(PipelineTest, XAddIdxSymWord) {
    
  }

  TEST_F(PipelineTest, XAddIdxSymAddressWord) {
    
  }

  TEST_F(PipelineTest, XAddIdxAbsByte) {
    
  }

  TEST_F(PipelineTest, XAddIdxAbsWord) {
    
  }

  TEST_F(PipelineTest, XAddIdxAbsAddressWord) {
    
  }

  TEST_F(PipelineTest, XAddIdxImmByte) {
    
  }

  TEST_F(PipelineTest, XAddIdxImmWord) {
    
  }

  TEST_F(PipelineTest, XAddIdxImmAddressWord) {
    
  }

  TEST_F(PipelineTest, XAddSymRegByte) {
    
  }

  TEST_F(PipelineTest, XAddSymRegWord) {
    
  }

  TEST_F(PipelineTest, XAddSymRegAddressWord) {
    
  }

  TEST_F(PipelineTest, XAddSymIdxByte) {
    
  }

  TEST_F(PipelineTest, XAddSymIdxWord) {
    
  }

  TEST_F(PipelineTest, XAddSymIdxAddressWord) {
    
  }

  TEST_F(PipelineTest, XAddSymSymByte) {
    
  }

  TEST_F(PipelineTest, XAddSymSymWord) {
    
  }

  TEST_F(PipelineTest, XAddSymSymAddressWord) {
    
  }

  TEST_F(PipelineTest, XAddSymAbsByte) {
    
  }

  TEST_F(PipelineTest, XAddSymAbsWord) {
    
  }

  TEST_F(PipelineTest, XAddSymAbsAddressWord) {
    
  }

  TEST_F(PipelineTest, XAddSymImmByte) {
    
  }

  TEST_F(PipelineTest, XAddSymImmWord) {
    
  }

  TEST_F(PipelineTest, XAddSymImmAddressWord) {
    
  }

  TEST_F(PipelineTest, XAddAbsRegByte) {
    
  }

  TEST_F(PipelineTest, XAddAbsRegWord) {
    
  }

  TEST_F(PipelineTest, XAddAbsRegAddressWord) {
    
  }

  TEST_F(PipelineTest, XAddAbsIdxByte) {
    
  }

  TEST_F(PipelineTest, XAddAbsIdxWord) {
    
  }

  TEST_F(PipelineTest, XAddAbsIdxAddressWord) {
    
  }

  TEST_F(PipelineTest, XAddAbsSymByte) {
    
  }

  TEST_F(PipelineTest, XAddAbsSymWord) {
    
  }

  TEST_F(PipelineTest, XAddAbsSymAddressWord) {
    
  }

  TEST_F(PipelineTest, XAddAbsAbsByte) {
    
  }

  TEST_F(PipelineTest, XAddAbsAbsWord) {
    
  }

  TEST_F(PipelineTest, XAddAbsAbsAddressWord) {
    
  }

  TEST_F(PipelineTest, XAddAbsImmByte) {
    
  }

  TEST_F(PipelineTest, XAddAbsImmWord) {
    
  }

  TEST_F(PipelineTest, XAddAbsImmAddressWord) {
    
  }


}