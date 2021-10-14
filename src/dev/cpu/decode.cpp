//
// Created by scolton on 10/13/21.
//

#include "dev/model/package.h"
#include "dev/mem/memory_map.h"
#include "dev/cpu/decode.h"

MSP430::OpcodeWidthHolder::OpcodeWidthHolder(MSP430::msp430_word_t opcode, MSP430::msp430_word_t ext) {

}

MSP430::InstructionFormat MSP430::OpcodeWidthHolder::opcode_to_format(msp430_word_t opcode) {
    /* !!! FORMAT I !!!
     * MOV(X):  4xxx
     * ADD(X):  5xxx
     * ADDC(X): 6xxx
     * SUB(X):  8xxx
     * SUBC(X): 7xxx
     * CMP(X):  9xxx
     * DADD(X): Axxx
     * BIT(X):  Bxxx
     * BIC(X):  Cxxx
     * BIS(X):  Dxxx
     * XOR(X):  Exxx
     * AND(X):  Fxxx
     *
     * !!! FORMAT II !!!
     * RRC(X):  1000 | 1040
     * RRA(X):  1040 | 1140
     * PUSH(X): 1200 | 1240
     * SWPB(X): 1080        <- w/o ext: word, w/ ext: depends
     * CALL:    1340
     * RETI:    1300
     * SXT(X):  1180
     * POPM:    14xx
     * PUSHM:   14xx
     * RRCM:    0xxx
     * RRUM:    0xxx
     * RRAM:    0xxx
     * RLAM:    0xxx
     * CALLA:   1340
     *
     * !!! JUMP !!!
     * 20xx -> 3Cxx
     *
     * !!! ALWAYS ADDRESS WORD !!!
     * ADDA, SUBA, CMPA, MOVA
     * ^0000xxxx[^0100|0101]xxxx$
     */
    if (!(opcode & 0xF000) || (opcode > 0x1400 && opcode < 0x1500)) {
      return FORMAT_EXTENDED;
    }

    if (opcode >= 0x2000 && opcode < 0x4000) {
      return FORMAT_JUMP;
    }


  }
}

MSP430::InstructionWidth MSP430::next_instruction_width(msp430_word_t ext_word, msp430_word_t raw_instruction) {

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
        return nullptr;
      case 0b0001:
        return nullptr;
      case 0b0010:
        return nullptr;
      case 0b0011:
        return nullptr;
      case 0b0100:
      case 0b0101: {
        MSP430::msp430_byte_t w = !!(raw_instruction & 0b10000);
        switch (x_instr_sub_id) {
          case 0b00:
            return nullptr;
          case 0b01:
            return nullptr;
          case 0b10:
            return nullptr;
          case 0b11:
            return nullptr;
          default:
            throw std::runtime_error("Shouldn't be possible");
        }
      }
      case 0b0110:
        return nullptr;
      case 0b0111:
        return nullptr;
      case 0b1000:
        return nullptr;
      case 0b1001:
        return nullptr;
      case 0b1010:
        return nullptr;
      case 0b1011:
        return nullptr;
      case 0b1100:
        return nullptr;
      case 0b1101:
        return nullptr;
      case 0b1110:
        return nullptr;
      case 0b1111:
        return nullptr;
      default:
        throw std::runtime_error("Should be impossible");
    }
  } else if (short_code == 0x1) {

  } else if (opcode >= 0x10 && opcode < 0x14) {
    MSP430::msp430_byte_t opcode_x_10 = (raw_instruction >> 4) & 0xFFC;
    switch (opcode_x_10) {
      case 0x100:
        return nullptr;
      case 0x104:
        return nullptr;
      case 0x108:
        return nullptr;
      case 0x110:
        return nullptr;
      case 0x114:
        return nullptr;
      case 0x118:
        return nullptr;
      case 0x120:
        return nullptr;
      case 0x124:
        return nullptr;
      case 0x128:
        return nullptr;
      case 0x130:
        return nullptr;
      case 0x134:
        return nullptr;
      default:
        throw std::domain_error("Invalid instruction 10xx code");
    }
  } else if (opcode == 0x14) {
    MSP430::msp430_byte_t push_pop_id = (raw_instruction >> 8) & 0x3;
    switch (push_pop_id) {
      case 0b00:
        return nullptr;
      case 0b01:
        return nullptr;
      case 0b10:
        return nullptr;
      case 0b11:
        return nullptr;
      default:
        throw std::runtime_error("Should be impossible");
    }
  } else if (opcode == 0x18) {

  } else if (opcode == 0x1C) {

  } else if (opcode == 0x20) {

  } else if (opcode == 0x24) {

  } else if (opcode == 0x28) {

  } else if (opcode == 0x2C) {

  } else if (opcode == 0x30) {

  } else if (opcode == 0x34) {

  } else if (opcode == 0x38) {

  } else if (opcode == 0x3C) {

  } else if (short_code == 0x40) {

  } else if (short_code == 0x50) {
    return new MSP430::ADDInstruction<msp430_size_t>(raw_instruction, extension_word);
  } else if (short_code == 0x60) {

  } else if (short_code == 0x70) {

  } else if (short_code == 0x80) {

  } else if (short_code == 0x90) {

  } else if (short_code == 0xA0) {

  } else if (short_code == 0xB0) {

  } else if (short_code == 0xC0) {

  } else if (short_code == 0xD0) {

  } else if (short_code == 0xE0) {

  } else if (short_code == 0xF0) {

  } else {
    throw std::domain_error("Invalid opcode");
  }
}

MSP430::msp430_addr_t truncate_address(MSP430::msp430_addr_t addr) {
  return addr & 0xFFFFF;
}

template <typename msp430_size_t>
MSP430::Instruction<msp430_size_t>* MSP430::instruction_decode(Package* package, msp430_addr_t loc) {
  MemoryMapper* mem = package->get_memory();

  msp430_word_t extension_word = 0x0;
  msp430_word_t raw_instruction = mem->get_word(loc);
  loc += 2;

  msp430_byte_t identifier = raw_instruction >> 8;
  if (identifier >= 0x18 && identifier <= 0x1F) {
    extension_word = raw_instruction;
    raw_instruction = mem->get_word(loc);
    loc += 2;
  }


  package->get_cpu()->get_pc()->set_value(truncate_address(loc));

  return process_opcode(extension_word, raw_instruction);
}