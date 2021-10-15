//
// Created by scolton on 10/11/21.
//

#ifndef MSP430_EMULATOR_DECODE_H
#define MSP430_EMULATOR_DECODE_H

#include "prog/isa/instruction.h"

namespace MSP430 {
  void fill_instruction_and_ext(Package*,
                                msp430_addr_t& addr,
                                msp430_word_t& extension_word,
                                msp430_word_t& raw_instruction,
                                bool           increment = false);
  InstructionWidth next_instruction_width(msp430_word_t ext_word, msp430_word_t raw_instruction);

  template<typename msp430_size_t>
  Instruction<msp430_size_t>* instruction_decode(Package*, msp430_addr_t);
}

template<typename msp430_size_t>
MSP430::Instruction<msp430_size_t>* process_opcode(MSP430::msp430_word_t extension_word,
                                                   MSP430::msp430_word_t raw_instruction) {
  MSP430::msp430_byte_t opcode         = (raw_instruction >> 8) & 0xFC;
  MSP430::msp430_byte_t short_code     = (opcode >> 4) & 0xF;
  MSP430::msp430_byte_t x_instr_id     = (raw_instruction >> 4) & 0xF;
  MSP430::msp430_byte_t x_instr_sub_id = (raw_instruction >> 8) & 0x3;

  if (short_code == 0x00) {
    switch (x_instr_id) {
      case 0b0000:
      case 0b0001:
      case 0b0010:
      case 0b0011:
      case 0b0110:
      case 0b0111:
      case 0b1000:
      case 0b1100:
        return new MSP430::MOVAInstruction<msp430_size_t>(raw_instruction, extension_word);
      case 0b0100:
      case 0b0101: {
        switch (x_instr_sub_id) {
          case 0b00:
            return new MSP430::RRCMInstruction<msp430_size_t>(raw_instruction, extension_word);
          case 0b01:
            return new MSP430::RRAMInstruction<msp430_size_t>(raw_instruction, extension_word);
          case 0b10:
            return new MSP430::RLAMInstruction<msp430_size_t>(raw_instruction, extension_word);
          case 0b11:
            return new MSP430::RRUMInstruction<msp430_size_t>(raw_instruction, extension_word);
          default:
            throw std::runtime_error("Shouldn't be possible");
        }
      }
      case 0b1001:
      case 0b1101:
        return new MSP430::CMPAInstruction<msp430_size_t>(raw_instruction, extension_word);
      case 0b1010:
      case 0b1110:
        return new MSP430::ADDAInstruction<msp430_size_t>(raw_instruction, extension_word);
      case 0b1011:
      case 0b1111:
        return new MSP430::SUBAInstruction<msp430_size_t>(raw_instruction, extension_word);
      default:
        throw std::runtime_error("Should be impossible");
    }
  } else if (opcode >= 0x10 && opcode < 0x14) {
    uint32_t opcode_x_10 = (raw_instruction >> 4) & 0xFFC;
    switch (opcode_x_10) {
      case 0x100:
      case 0x104:
        return new MSP430::RRCInstruction<msp430_size_t>(raw_instruction, extension_word);
      case 0x108:
        return new MSP430::SWPBInstruction<msp430_size_t>(raw_instruction, extension_word);
      case 0x110:
      case 0x114:
        return new MSP430::RRAInstruction<msp430_size_t>(raw_instruction, extension_word);
      case 0x118:
        return new MSP430::SXTInstruction<msp430_size_t>(raw_instruction, extension_word);
      case 0x120:
      case 0x124:
        return new MSP430::PUSHInstruction<msp430_size_t>(raw_instruction, extension_word);
      case 0x128:
        return new MSP430::CALLInstruction<msp430_size_t>(raw_instruction, extension_word);
      case 0x130:
        return new MSP430::RETIInstruction<msp430_size_t>(raw_instruction, extension_word);
      case 0x134:
        return new MSP430::CALLAInstruction<msp430_size_t>(raw_instruction, extension_word);
      default:
        throw std::domain_error("Invalid instruction 10xx code");
    }
  } else if (raw_instruction >= 0x1400 && raw_instruction < 0x1800) {
    MSP430::msp430_byte_t pushm_popm_id = (raw_instruction >> 8) & 0x3;
    switch (pushm_popm_id) {
      case 0b00:
      case 0b01:
        return new MSP430::PUSHMInstruction<msp430_size_t>(raw_instruction, extension_word);
      case 0b10:
      case 0b11:
        return new MSP430::POPMInstruction<msp430_size_t>(raw_instruction, extension_word);
      default:
        throw std::runtime_error("Should be impossible");
    }
  } else if (opcode == 0x18 || opcode == 0x1C) {
    throw std::runtime_error("Extension word should already be handled");
  } else if (opcode == 0x20) {
    return new MSP430::JNEInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (opcode == 0x24) {
    return new MSP430::JEQInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (opcode == 0x28) {
    return new MSP430::JNCInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (opcode == 0x2C) {
    return new MSP430::JCInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (opcode == 0x30) {
    return new MSP430::JNInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (opcode == 0x34) {
    return new MSP430::JGEInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (opcode == 0x38) {
    return new MSP430::JLInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (opcode == 0x3C) {
    return new MSP430::JMPInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (short_code == 0x40) {
    return new MSP430::MOVInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (short_code == 0x50) {
    return new MSP430::ADDInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (short_code == 0x60) {
    return new MSP430::ADDCInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (short_code == 0x70) {
    return new MSP430::SUBCInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (short_code == 0x80) {
    return new MSP430::SUBInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (short_code == 0x90) {
    return new MSP430::CMPInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (short_code == 0xA0) {
    return new MSP430::DADDInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (short_code == 0xB0) {
    return new MSP430::BITInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (short_code == 0xC0) {
    return new MSP430::BICInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (short_code == 0xD0) {
    return new MSP430::BISInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (short_code == 0xE0) {
    return new MSP430::XORInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (short_code == 0xF0) {
    return new MSP430::ANDInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else {
    throw std::domain_error("Invalid opcode");
  }
}

MSP430::msp430_addr_t truncate_address(MSP430::msp430_addr_t addr) {
  return addr & 0xFFFFF;
}

template <typename msp430_size_t>
MSP430::Instruction<msp430_size_t>* MSP430::instruction_decode(Package* package, msp430_addr_t loc) {
  msp430_word_t extension_word = 0x0, raw_instruction;
  fill_instruction_and_ext(package, loc, extension_word, raw_instruction, true);

  package->get_cpu()->get_pc()->set_value(truncate_address(loc));

  return process_opcode<msp430_size_t>(extension_word, raw_instruction);
}

#endif //MSP430_EMULATOR_DECODE_H
