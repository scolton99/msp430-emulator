//
// Created by scolton on 10/10/21.
//

#include <iostream>
#include <vector>
#include "dev/mem/mem.h"

MSP430::MemoryMapping* MSP430::MemoryMapper::get_relevant_mapping(MSP430::msp430_addr_t addr) {
  for (auto & mapping : this->mappings) {
    msp430_addr_t start = mapping.first;
    msp430_addr_t end   = mapping.first + mapping.second.length;

    if (start <= addr && end > addr)
      return &(mapping.second);
  }

  throw std::runtime_error("Couldn't find mapping for address");
}

template<typename msp430_size_t>
std::vector<MSP430::msp430_byte_t> MSP430::MemoryMapper::fix_endianness(msp430_size_t value) {
  std::vector<msp430_byte_t> result;
  result.resize(sizeof(value));

  for (size_t i = 0; i < sizeof(value); ++i)
    result[i] = (value >> (8 * i)) & 0xFF;

  return result;
}

template<typename msp430_size_t>
msp430_size_t MSP430::MemoryMapper::unfix_endianness(const msp430_bytes& value) {
  msp430_size_t result = 0;

  for (size_t i = 0; i < value.size(); ++i)
    result |= value[i] << (8 * i);

  return result;
}

MSP430::msp430_addr_t MSP430::MemoryMapper::canonical_dev_address(MemoryMapping& mapping, msp430_addr_t offset) {
  return mapping.dev_start + offset;
}

MSP430::msp430_addr_t MSP430::MemoryMapper::convert_to_offset(MemoryMapping& mapping, msp430_addr_t package_addr) {
  return package_addr - mapping.package_start;
}

MSP430::msp430_bytes MSP430::MemoryMapper::read_bytes(MemoryMapping& mapping, msp430_addr_t offset, msp430_addr_t length) {
  std::vector<msp430_byte_t> result;
  result.resize(length);

  msp430_addr_t cur_addr = canonical_dev_address(mapping, offset);
  for (msp430_byte_t& i: result)
    i = mapping.dev->get(cur_addr++);

  return result;
}

void MSP430::MemoryMapper::write_bytes(MemoryMapping& mapping, msp430_addr_t offset, const msp430_bytes& bytes) {
  msp430_addr_t cur_addr = canonical_dev_address(mapping, offset);

  for (const msp430_byte_t& byte: bytes)
    mapping.dev->set(cur_addr++, byte);
}

bool MSP430::MemoryMapper::validate_address_word(msp430_addr_word_t value) {
  return (value & ~(0xFFFFF)) == 0;
}

template<typename msp430_size_t>
msp430_size_t MSP430::MemoryMapper::get(msp430_addr_t addr) {
  MSP430::MemoryMapping* mapping = get_relevant_mapping(addr);
  msp430_addr_t offset = convert_to_offset(*mapping, addr);

  msp430_bytes chars = read_bytes(*mapping, offset, sizeof(msp430_size_t));

  return unfix_endianness<msp430_size_t>(chars);
}

MSP430::msp430_byte_t MSP430::MemoryMapper::get_byte(MSP430::msp430_addr_t addr) {
  return get<msp430_byte_t>(addr);
}

MSP430::msp430_word_t MSP430::MemoryMapper::get_word(MSP430::msp430_addr_t addr) {
  return get<msp430_word_t>(addr);
}

MSP430::msp430_addr_word_t MSP430::MemoryMapper::get_address_word(MSP430::msp430_addr_t addr) {
  auto result = get<msp430_addr_word_t>(addr);

  if (!validate_address_word(result))
    std::wcout << "Address word had non-zero values in upper 12 MSBs, truncating" << std::endl;

  return result & 0xFFFFF;
}

template<typename msp430_size_t>
void MSP430::MemoryMapper::set(msp430_addr_t addr, msp430_size_t value) {
  MSP430::MemoryMapping* mapping = this->get_relevant_mapping(addr);
  msp430_addr_t offset = convert_to_offset(*mapping, addr);

  write_bytes(*mapping, offset, fix_endianness(value));
}

void MSP430::MemoryMapper::set_byte(MSP430::msp430_addr_t addr, msp430_byte_t value) {
  set(addr, value);
}

void MSP430::MemoryMapper::set_word(msp430_addr_t addr, msp430_word_t value) {
  set(addr, value);
}

void MSP430::MemoryMapper::set_address_word(msp430_addr_t addr, msp430_addr_word_t value) {
  if (!validate_address_word(value))
    std::wcout << "Address word had non-zero values in upper 12 MSBs, truncating" << std::endl;

  set(addr, value & 0xFFFFF);
}

bool MSP430::MemoryMapper::overlap(msp430_addr_t start1, msp430_addr_t length1, msp430_addr_t start2, msp430_addr_t length2) {
  msp430_addr_t end1 = start1 + length1, end2 = start2 + length2;
  return start2 < end1 && end2 > start1;
}

void MSP430::MemoryMapper::add_mapping(MemoryMapping mapping) {
  for (const auto &pair: mappings) {
    MemoryMapping ext_mapping = pair.second;

    if (overlap(mapping.package_start, mapping.length, ext_mapping.package_start, ext_mapping.length))
      throw std::runtime_error("Refusing to add overlapping mapping");
  }

  this->mappings.insert(std::make_pair(mapping.package_start, mapping));
}
