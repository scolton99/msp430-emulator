//
// Created by scolton on 10/8/21.
//

#ifndef MSP430_EMULATOR_INSTRUCTION_H
#define MSP430_EMULATOR_INSTRUCTION_H

#include "dev/cpu/execute.h"
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
    FORMAT_CALLA,
    FORMAT_EXTENDED_ADDRESS
  };

  enum InstructionWidth {
    BYTE,
    WORD,
    ADDRESS_WORD
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

  class ExtensionWord {
  private:
    msp430_word_t word;
  public:
    explicit ExtensionWord(msp430_word_t);
    uint8_t get_zc();
    uint8_t get_rpt(Package*);
    uint8_t get_al();
    uint8_t get_src_msn();
    uint8_t get_dst_msn();
    bool    is_present();
  };

  class OpcodeWidthHolder {
  private:
    unsigned int bw:1;
    unsigned int al:1;

  public:
    OpcodeWidthHolder(msp430_word_t opcode, msp430_word_t ext);
    InstructionWidth get_width() const;

  private:
    static InstructionFormat opcode_to_format(msp430_word_t opcode, msp430_word_t ext);
  };

  template <typename msp430_size_t>
  class Instruction {
  protected:
    static AddressingMode resolve_dst_addr_mode(uint8_t ad, uint8_t rdst);
    static msp430_addr_t calc_indexed_addr(msp430_addr_word_t base, msp430_word_t offset);
  public:
    virtual void accept(InstructionVisitor<msp430_size_t>&) = 0;
    virtual bool has_extension_word()                       = 0;
    virtual int  extra_words()                              = 0;
    virtual int  get_execution_time()                       = 0;
    virtual bool is_extended()                              = 0;
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

    ExtensionWord opt_ext_word;

    explicit InstructionFormatI(msp430_word_t base_instr,
                                msp430_word_t opt_ext = 0);
  public:
    bool has_extension_word() override;
    int  extra_words()        override;
    int  get_execution_time() override;
    bool is_extended()        override;

    AddressingMode get_src_addr_mode() const;
    AddressingMode get_dst_addr_mode() const;

    msp430_size_t get_src_value(Package* package); // not idempotent
    msp430_size_t get_dst_value();                 // idempotent
    void set_src_value(Package* package, msp430_size_t value);
    void set_dst_value(Package* package, msp430_size_t value);
  };

  template <typename msp430_size_t>
  class InstructionFormatII : public Instruction<msp430_size_t> {
  protected:
    uint16_t opcode:9;
    uint8_t bw:1;
    uint8_t ad:2;
    uint8_t rdst:4;

    ExtensionWord opt_ext_word;

    explicit InstructionFormatII(msp430_word_t base_instr,
                                 msp430_word_t opt_ext = 0);
  public:
    bool has_extension_word() override;
    int  extra_words()        override;
    int  get_execution_time() override;
    bool is_extended()        override;
  };

  template <typename msp430_size_t>
  class InstructionJumpFormat : public Instruction<msp430_size_t> {
  protected:
    int opcode:3;
    int condition:3;
    signed int offset:10;

    explicit InstructionJumpFormat(msp430_word_t base_instr);
  public:
    bool has_extension_word() override;
    int  extra_words()        override;
    int  get_execution_time() override;
    bool is_extended()        override;
  };

  template <typename msp430_size_t>
  class InstructionPushmPopmFormat : public Instruction<msp430_size_t> {
  protected:
    unsigned n1:4;
    unsigned rdst:4;

    explicit InstructionPushmPopmFormat(msp430_word_t base_instr);
  public:
    bool has_extension_word() override;
    int  extra_words()        override;
    int  get_execution_time() override;
    bool is_extended()        override;
  };

  template <typename msp430_size_t>
  class InstructionRXXMFormat : public Instruction<msp430_size_t> {
  protected:
    unsigned n1:2;
    unsigned rdst:4;

    explicit InstructionRXXMFormat(msp430_word_t base_instr);
  public:
    bool has_extension_word() override;
    int  extra_words()        override;
    int  get_execution_time() override;
    bool is_extended()        override;
  };

  template <typename msp430_size_t>
  class InstructionCALLAFormat : public Instruction<msp430_size_t> {
  protected:
    unsigned opcode:12;
    unsigned rdst_ext:4;

    explicit InstructionCALLAFormat(msp430_word_t base_instr);
  public:
    bool has_extension_word() override;
    int  extra_words()        override;
    int  get_execution_time() override;
    bool is_extended()        override;
  };

  template <typename msp430_size_t>
  class InstructionAddressFormat : public Instruction<msp430_size_t> {
  protected:
    unsigned src_ext:4;
    unsigned id:4;
    unsigned dst_ext:4;

    explicit InstructionAddressFormat(msp430_word_t base_instr);
  public:
    bool has_extension_word() override;
    int  extra_words()        override;
    int  get_execution_time() override;
    bool is_extended()        override;
  };

  template <typename msp430_size_t>
  class ADDInstruction : public InstructionFormatI<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    ADDInstruction(msp430_word_t base_instr,
                   msp430_word_t ext_word = 0) :
                   InstructionFormatI<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };
}

template <typename msp430_size_t>
MSP430::AddressingMode MSP430::Instruction<msp430_size_t>::resolve_dst_addr_mode(uint8_t ad, uint8_t rdst) {
  switch (ad) {
    case 0b0:
      return REGISTER;
    case 0b1:
      switch (rdst) {
        case 0x0:
          return SYMBOLIC;
        case 0x2:
          return ABSOLUTE;
        default:
          return INDEXED;
      }
    default:
      throw std::runtime_error("Invalid value for ad");
  }
}

template<typename msp430_size_t>
MSP430::msp430_addr_t MSP430::Instruction<msp430_size_t>::calc_indexed_addr(msp430_addr_word_t base,
                                                                            msp430_word_t offset) {
  if (base > 0xFFFF) {
    auto signed_offset = static_cast<int16_t>(offset & 0xFFFF);
    return (msp430_addr_t)(base + signed_offset) & 0xFFFF;
  } else {
    int32_t signed_offset = static_cast<int16_t>(offset);
    return (msp430_word_t)(base + signed_offset) & 0xFFFFF;
  }
}

template <typename msp430_size_t>
MSP430::InstructionFormatI<msp430_size_t>::InstructionFormatI(msp430_word_t base_instr,
                                                              msp430_word_t opt_ext) :
                                                              opt_ext_word(ExtensionWord(opt_ext)) {
  this->opcode = (base_instr >> 12) & 0xF;
  this->rsrc   = (base_instr >> 8)  & 0xF;
  this->ad     = (base_instr >> 7)  & 0x1;
  this->bw     = (base_instr >> 6)  & 0x1;
  this->as     = (base_instr >> 4)  & 0x3;
  this->rdst   = (base_instr)       & 0xF;
}

template <typename msp430_size_t>
bool MSP430::InstructionFormatI<msp430_size_t>::has_extension_word() {
  return this->opt_ext_word.is_present();
}

template <typename msp430_size_t>
int MSP430::InstructionFormatI<msp430_size_t>::extra_words() {
  int extra_src_word = this->as == 0b01 || (this->as == 0b11 && this->rsrc == 0x0);
  int extra_dst_word = this->ad == 0b1;

  return extra_src_word + extra_dst_word;
}

template <typename msp430_size_t>
bool MSP430::InstructionFormatI<msp430_size_t>::is_extended() {
  return this->has_extension_word();
}

template <typename msp430_size_t>
MSP430::AddressingMode MSP430::InstructionFormatI<msp430_size_t>::get_src_addr_mode() const {
  switch (this->as) {
    case 0b00:
      return REGISTER;
    case 0b01:
      switch (this->rsrc) {
        case 0x0:
          return SYMBOLIC;
        case 0x2:
          return ABSOLUTE;
        default:
          return INDEXED;
      }
    case 0b10:
      return INDIRECT_REGISTER;
    case 0b11:
      return this->rsrc == 0x0 ? IMMEDIATE : INDIRECT_AUTOINCREMENT;
  }
}

template <typename msp430_size_t>
MSP430::AddressingMode MSP430::InstructionFormatI<msp430_size_t>::get_dst_addr_mode() const {
  return resolve_dst_addr_mode(this->ad, this->rdst);
}

template <typename msp430_size_t>
msp430_size_t MSP430::InstructionFormatI<msp430_size_t>::get_src_value(Package* package) {
  ICPU*         cpu = package->get_cpu();
  MemoryMapper* mem = package->get_memory();

  msp430_size_t value;

  switch (this->get_src_addr_mode()) {
    case REGISTER:
      value = cpu->resolve_register(this->rsrc)->get_value(this->as, sizeof(msp430_size_t));
      break;
    case INDEXED:
      uint8_t addr_size = sizeof(msp430_addr_t);
      msp430_addr_t      base   = cpu->resolve_register(this->rsrc)->get_value(0, addr_size);
      msp430_addr_word_t offset;
      if (this->has_extension_word()) {
        offset =
      } else {
        offset = mem->get_word(cpu->get_pc()->get_value(0, sizeof(msp430_addr_word_t)));
      }


      msp430_addr_word_t src_addr = calc_indexed_addr(, )

      return 0;
    case SYMBOLIC:
      return 0;
    case ABSOLUTE:
      return 0;
    case INDIRECT_REGISTER:
      return 0;
    case INDIRECT_AUTOINCREMENT:
      return 0;
    case IMMEDIATE:
      return 0;
  }
}

template<typename msp430_size_t>
int MSP430::InstructionFormatI<msp430_size_t>::get_execution_time() {
  return 0;
}

template<typename msp430_size_t>
msp430_size_t MSP430::InstructionFormatI<msp430_size_t>::get_dst_value() {
  return nullptr;
}

template<typename msp430_size_t>
void MSP430::InstructionFormatI<msp430_size_t>::set_src_value(MSP430::Package *package, msp430_size_t value) {

}

template<typename msp430_size_t>
void MSP430::InstructionFormatI<msp430_size_t>::set_dst_value(MSP430::Package *package, msp430_size_t value) {

}

template <typename msp430_size_t>
MSP430::InstructionFormatII<msp430_size_t>::InstructionFormatII(msp430_word_t base_instr,
                                                                msp430_word_t opt_ext) :
                                                                opt_ext_word(ExtensionWord(opt_ext)) {
  this->opcode = (base_instr >> 7) & 0x1FF;
  this->bw     = (base_instr >> 6) & 0x1;
  this->ad     = (base_instr >> 4) & 0x3;
  this->rdst   = (base_instr)      & 0xF;
}

template <typename msp430_size_t>
bool MSP430::InstructionFormatII<msp430_size_t>::has_extension_word() {
  return !!this->opt_ext_word;
}

template <typename msp430_size_t>
int MSP430::InstructionFormatII<msp430_size_t>::extra_words() {
  return this->ad == 0b01 || (this->ad == 0b11 && this->rdst == 0x0);
}

template <typename msp430_size_t>
bool MSP430::InstructionFormatII<msp430_size_t>::is_extended() {
  return this->has_extension_word();
}

template<typename msp430_size_t>
int MSP430::InstructionFormatII<msp430_size_t>::get_execution_time() {
  // TODO: impl
  return 0;
}

template <typename msp430_size_t>
MSP430::InstructionJumpFormat<msp430_size_t>::InstructionJumpFormat(msp430_word_t base_instr) {
  this->opcode    = (base_instr >> 13) & 0x7;
  this->condition = (base_instr >> 10) & 0x7;
  this->offset    = (base_instr)       & 0x3FF;
}

template <typename msp430_size_t>
bool MSP430::InstructionJumpFormat<msp430_size_t>::has_extension_word() {
  return false;
}

template <typename msp430_size_t>
int MSP430::InstructionJumpFormat<msp430_size_t>::extra_words() {
  return 0;
}

template <typename msp430_size_t>
bool MSP430::InstructionJumpFormat<msp430_size_t>::is_extended() {
  return false;
}

template<typename msp430_size_t>
int MSP430::InstructionJumpFormat<msp430_size_t>::get_execution_time() {
  // TODO: impl
  return 0;
}

template <typename msp430_size_t>
MSP430::InstructionPushmPopmFormat<msp430_size_t>::InstructionPushmPopmFormat(msp430_word_t base_instr) {
  this->n1   = (base_instr >> 4) & 0xF;
  this->rdst = (base_instr)      & 0xF;
}

template<typename msp430_size_t>
bool MSP430::InstructionPushmPopmFormat<msp430_size_t>::has_extension_word() {
  return false;
}

template<typename msp430_size_t>
int MSP430::InstructionPushmPopmFormat<msp430_size_t>::extra_words() {
  return 0;
}

template<typename msp430_size_t>
int MSP430::InstructionPushmPopmFormat<msp430_size_t>::get_execution_time() {
  // TODO: impl
  return 0;
}

template<typename msp430_size_t>
bool MSP430::InstructionPushmPopmFormat<msp430_size_t>::is_extended() {
  return true;
}

template<typename msp430_size_t>
MSP430::InstructionRXXMFormat<msp430_size_t>::InstructionRXXMFormat(msp430_word_t base_instr) {
  this->n1   = (base_instr >> 10) & 0x3;
  this->rdst = (base_instr)       & 0xF;
}

template<typename msp430_size_t>
bool MSP430::InstructionRXXMFormat<msp430_size_t>::has_extension_word() {
  return false;
}

template<typename msp430_size_t>
int MSP430::InstructionRXXMFormat<msp430_size_t>::extra_words() {
  return 0;
}

template<typename msp430_size_t>
int MSP430::InstructionRXXMFormat<msp430_size_t>::get_execution_time() {
  // TODO: impl
  return 0;
}

template<typename msp430_size_t>
bool MSP430::InstructionRXXMFormat<msp430_size_t>::is_extended() {
  return true;
}

template<typename msp430_size_t>
MSP430::InstructionCALLAFormat<msp430_size_t>::InstructionCALLAFormat(msp430_word_t base_instr) {
  this->rdst_ext = base_instr & 0xF;
}

template<typename msp430_size_t>
bool MSP430::InstructionCALLAFormat<msp430_size_t>::has_extension_word() {
  return false;
}

template<typename msp430_size_t>
int MSP430::InstructionCALLAFormat<msp430_size_t>::extra_words() {
  // TODO: impl
  return 0;
}

template<typename msp430_size_t>
int MSP430::InstructionCALLAFormat<msp430_size_t>::get_execution_time() {
  // TODO: impl
  return 0;
}

template<typename msp430_size_t>
bool MSP430::InstructionCALLAFormat<msp430_size_t>::is_extended() {
  return true;
}

template<typename msp430_size_t>
MSP430::InstructionAddressFormat<msp430_size_t>::InstructionAddressFormat(msp430_word_t base_instr) {
  this->dst_ext = (base_instr)      & 0xF;
  this->id      = (base_instr >> 4) & 0xF;
  this->src_ext = (base_instr >> 8) & 0xF;
}

template<typename msp430_size_t>
bool MSP430::InstructionAddressFormat<msp430_size_t>::has_extension_word() {
  return false;
}

template<typename msp430_size_t>
int MSP430::InstructionAddressFormat<msp430_size_t>::extra_words() {
  return 0;
}

template<typename msp430_size_t>
int MSP430::InstructionAddressFormat<msp430_size_t>::get_execution_time() {
  // TODO: impl
  return 0;
}

template<typename msp430_size_t>
bool MSP430::InstructionAddressFormat<msp430_size_t>::is_extended() {
  return true;
}

#endif //MSP430_EMULATOR_INSTRUCTION_H
