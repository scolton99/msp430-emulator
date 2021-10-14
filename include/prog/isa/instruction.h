//
// Created by scolton on 10/8/21.
//

#ifndef MSP430_EMULATOR_INSTRUCTION_H
#define MSP430_EMULATOR_INSTRUCTION_H

#include "dev/model/package.h"
#include "visitor.h"

namespace MSP430 {
  enum InstructionFormat {
    FORMAT_I,
    FORMAT_II,
    FORMAT_JUMP,
    FORMAT_I_EXTENDED,
    FORMAT_II_EXTENDED,
    FORMAT_PUSHM_POPM,
    FORMAT_RXXM,
    FORMAT_BRA,
    FORMAT_CALLA,
    FORMAT_EXTENDED_ADDRESS
  };

  enum InstructionWidth {
    BYTE,
    WORD,
    ADDRESS_WORD
  };

  class OpcodeWidthHolder {
  private:
    unsigned int bw:1;
    unsigned int al:1;

  public:
    OpcodeWidthHolder(msp430_word_t opcode, msp430_word_t ext);
    InstructionWidth get_width();

  private:
    static InstructionFormat opcode_to_format(msp430_word_t opcode);
  };

  enum AddressingMode {
    REGISTER,
    INDEXED,
    SYMBOLIC,
    ABSOLUTE,
    INDIRECT_REGISTER,
    INDIRECT_AUTOINCREMENT,
    IMMEDIATE
  };

  template <typename msp430_size_t> class Instruction {
  protected:
    static AddressingMode resolve_dst_addr_mode(uint8_t ad, uint8_t rdst);
  public:
    virtual void accept(InstructionVisitor&) = 0;
    virtual bool has_extension_word()        = 0;
    virtual int  extra_words()               = 0;
    virtual int  get_execution_time()        = 0;
  };

  template <typename msp430_size_t>
  class InstructionFormatI : public Instruction<msp430_size_t> {
  protected:
    uint8_t opcode:4;
    uint8_t rsrc:4;
    uint8_t ad:1;
    uint8_t bw:1;
    uint8_t as:2;
    uint8_t rdst:4;

    msp430_word_t opt_ext_word;

    InstructionFormatI(msp430_word_t base_instr,
                       msp430_word_t opt_ext = 0);

    static msp430_word_t         calc_indexed_addr(msp430_addr_word_t base, msp430_addr_word_t offset);
  public:
    bool has_extension_word() override;
    int  extra_words()        override;
    int  get_execution_time() override;

    AddressingMode get_src_addr_mode() const;
    AddressingMode get_dst_addr_mode() const;

    msp430_size_t get_src_value(Package* package); // not idempotent
    msp430_size_t get_dst_value();                 // idempotent
    void set_src_value(Package* package, msp430_size_t value);
    void set_dst_value(Package* package, msp430_size_t value);
  };

  class InstructionFormatII : public Instruction {
  protected:
    uint16_t opcode:9;
    uint8_t bw:1;
    uint8_t ad:2;
    uint8_t rdst:4;

    msp430_word_t opt_ext_word;

    InstructionFormatII(msp430_word_t base_instr,
                        msp430_word_t opt_ext = 0);
  public:
    bool has_extension_word() override;
    int  extra_words()        override;
    int  get_execution_time() override;
  };

  class InstructionJumpFormat : public Instruction {
  protected:
    int opcode:3;
    int condition:3;
    signed int offset:10;

    InstructionJumpFormat(msp430_word_t base_instr);
  public:
    bool has_extension_word() override;
    int  extra_words()        override;
    int  get_execution_time() override;
  };

  template <typename msp430_size_t>
  class ADDInstruction : public InstructionFormatI<msp430_size_t> {
    friend class InstructionExecutionVisitor;

  public:
    friend Instruction* instruction_decode(Package*, msp430_addr_t);

    ADDInstruction(msp430_word_t base_instr, msp430_word_t ext_word = 0) : InstructionFormatI(base_instr, ext_word) { }

    void accept(InstructionVisitor& visitor) override {
      visitor.visit(*this);
    };
  };
}

#endif //MSP430_EMULATOR_INSTRUCTION_H
