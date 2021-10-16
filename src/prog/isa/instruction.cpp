//
// Created by scolton on 10/15/21.
//

#include "prog/isa/instruction.h"
#include "prog/isa/format_address.h"
#include "types.h"

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
bool MSP430::Instruction<msp430_size_t>::is_addr_instruction(MSP430::Instruction<msp430_size_t>* instr) {
  return dynamic_cast<MSP430::InstructionAddressFormat<msp430_size_t>*>(instr) != nullptr;
}

template<typename msp430_size_t>
MSP430::msp430_addr_t MSP430::Instruction<msp430_size_t>::calc_idx_sym_abs_addr(MSP430::ICPU* cpu,
                                                                                IRegister*    rsrc,
                                                                                bool          extended,
                                                                                bool          absolute,
                                                                                uint8_t       ext_src_msn) {
  msp430_addr_t base = rsrc->get_value(0b01, sizeof(msp430_addr_t));
  int32_t       offset;
  msp430_addr_t src_addr;

  if (!extended && base >= 0x10000) {
    offset   = absolute ? cpu->read_word_and_inc_pc() : cpu->word_sxt_32(cpu->read_word_and_inc_pc());
    src_addr = (unsigned) (((signed) base) + offset) & 0xFFFFF;
  } else if (!extended && base <= 0xFFFF) {
    offset   = absolute ? cpu->read_word_and_inc_pc() : cpu->word_sxt_32(cpu->read_word_and_inc_pc());
    src_addr = (unsigned) (((signed) base) + offset) & 0xFFFF;
  } else if (extended) {
    offset = cpu->addr_word_sxt_32(cpu->read_word_and_inc_pc() | (ext_src_msn << 16));
    src_addr = (base + offset) & 0xFFFFF;
  } else {
    throw std::runtime_error("Invalid instruction combo for IDX/SYM/ABS");
  }

  return src_addr;
}

template <typename msp430_size_t>
msp430_size_t MSP430::Instruction<msp430_size_t>::get_op_value(Package*       package,
                                                               AddressingMode mode,
                                                               uint8_t        r,
                                                               uint8_t        as,
                                                               uint8_t        op_msn,
                                                               bool           extended) {
  ICPU*         cpu       = package->get_cpu();
  MemoryMapper* mem       = package->get_memory();
  uint8_t       addr_size = sizeof(msp430_addr_t);

  msp430_size_t value;

  switch (mode) {
    case REGISTER:
      value = cpu->resolve_register(r)->get_value(as, sizeof(msp430_size_t));
      break;
    case INDEXED: {
      value = mem->get<msp430_size_t>(calc_idx_sym_abs_addr(cpu,
                                                            cpu->resolve_register(r),
                                                            extended,
                                                            false,
                                                            op_msn));
      break;
    }
    case SYMBOLIC:
      value = mem->get<msp430_size_t>(calc_idx_sym_abs_addr(cpu,
                                                            cpu->get_pc(),
                                                            extended,
                                                            false,
                                                            op_msn));
      break;
    case ABSOLUTE:
      value = mem->get<msp430_size_t>(calc_idx_sym_abs_addr(cpu,
                                                            cpu->get_sr(),
                                                            extended,
                                                            true,
                                                            op_msn));
      break;
    case INDIRECT_REGISTER:
      value = mem->get<msp430_size_t>(cpu->resolve_register(r)->get_value(as, addr_size));
      break;
    case INDIRECT_AUTOINCREMENT: {
      IRegister* reg = cpu->resolve_register(r);
      value          = mem->get<msp430_size_t>(reg->get_value(as, addr_size));
      reg->set_value(reg->get_value(as, addr_size) + sizeof(msp430_size_t), addr_size);
      break;
    }
    case IMMEDIATE: {
      IRegister* reg = cpu->get_pc();
      value          = mem->get<msp430_size_t>(reg->get_value(as, addr_size));
      reg->set_value(reg->get_value(as, addr_size) + 2, addr_size);
      break;
    }
  }

  return value;
}

template<typename msp430_size_t>
void MSP430::Instruction<msp430_size_t>::set_op_value(MSP430::Package* package, MSP430::AddressingMode mode, uint8_t r,
                                                      uint8_t as, uint8_t op_msn, bool extended, msp430_size_t value) {
  ICPU* cpu         = package->get_cpu();
  MemoryMapper* mem = package->get_memory();
  msp430_addr_t dest_addr;

  switch (mode) {
    case REGISTER:
      cpu->resolve_register(r)->set_value(value, sizeof(msp430_size_t));
      break;
    case INDEXED:
      dest_addr = calc_idx_sym_abs_addr(cpu,
                                        cpu->resolve_register(r),
                                        extended,
                                        as,
                                        op_msn);
      mem->set<msp430_size_t>(dest_addr, value);
      break;
    case SYMBOLIC:
      dest_addr = calc_idx_sym_abs_addr(cpu,
                                        cpu->get_pc(),
                                        extended,
                                        as,
                                        op_msn);
      mem->set<msp430_size_t>(dest_addr, value);
      break;
    case ABSOLUTE:
      dest_addr = calc_idx_sym_abs_addr(cpu,
                                        cpu->get_sr(),
                                        extended,
                                        as,
                                        op_msn);
      mem->set<msp430_size_t>(dest_addr, value);
    default:
      throw std::runtime_error("Invalid destination addressing mode");
  }
}

template class MSP430::Instruction<MSP430::msp430_byte_t>;
template class MSP430::Instruction<MSP430::msp430_word_t>;
template class MSP430::Instruction<MSP430::msp430_addr_word_t>;