//
// Created by scolton on 10/10/21.
//

#include <cstdint>
#include <vector>
#include "dev/mem/memory_map.h"

#define MAPPING_CHARS(a,x) mapping->get_bytes(mapping->offset(a), x)
#define INTERP(s,t) *(reinterpret_cast<t*>(&chars[s]))

uint32_t MSP430::MemoryMapping::get_length() const {
  return this->length;
}

MSP430::msp430_addr_t MSP430::MemoryMapping::offset(MSP430::msp430_addr_t raw_addr) const {
  return raw_addr - this->start;
}

MSP430::MemoryMapping* MSP430::MemoryMapper::get_relevant_mapping(MSP430::msp430_addr_t addr) {
  for (auto & mapping : this->mappings) {
    msp430_addr_t start = mapping.first;
    msp430_addr_t end   = mapping.first + mapping.second.get_length();

    if (start <= addr && end > addr)
      return &(mapping.second);
  }

  throw std::runtime_error("Couldn't find mapping for address");
}

std::vector<MSP430::msp430_byte_t> MSP430::MemoryMapper::fix_endianness(MSP430::msp430_address_word_t value, uint8_t size) {
  std::vector<msp430_byte_t> result;
  result.resize(size);

  for (int i = 0; i < size; ++i)
    result[i] = (value >> (8 * i)) & 0xFF;

  return result;
}

std::vector<MSP430::msp430_byte_t> MSP430::MemoryMapping::get_bytes(msp430_addr_t addr, uint8_t result_length) {
  std::vector<msp430_byte_t> result;
  result.resize(result_length);

  msp430_addr_t cur_addr = addr + this->dev_start;
  for (msp430_byte_t& i: result)
    i = this->dev->get(cur_addr++);

  return result;
}

void MSP430::MemoryMapping::write_bytes(msp430_addr_t addr, const std::vector<msp430_byte_t>& bytes) {
  for (const msp430_byte_t& byte: bytes)
    this->dev->set(addr++, byte);
}

MSP430::msp430_byte_t MSP430::MemoryMapper::get_byte(MSP430::msp430_addr_t addr) {
  MSP430::MemoryMapping* mapping = this->get_relevant_mapping(addr);

  std::vector<msp430_byte_t> chars = MAPPING_CHARS(addr, 1);
  int8_t result = INTERP(0, int8_t) | (INTERP(1, int8_t) << 8);

  return result;
}

MSP430::msp430_word_t MSP430::MemoryMapper::get_word(MSP430::msp430_addr_t addr) {
  MSP430::MemoryMapping* mapping = this->get_relevant_mapping(addr);

  std::vector<msp430_byte_t> chars = MAPPING_CHARS(addr, 2);
  msp430_word_t result = INTERP(0, int8_t) | (INTERP(1, int8_t) << 8);

  return result;
}

MSP430::msp430_address_word_t MSP430::MemoryMapper::get_address_word(MSP430::msp430_addr_t addr) {
  MSP430::MemoryMapping* mapping = this->get_relevant_mapping(addr);

  std::vector<msp430_byte_t> chars = MAPPING_CHARS(addr, 4);
  int32_t results = INTERP(0, uint8_t) |
                   (INTERP(1, uint8_t) << 8 ) |
                   (INTERP(2, uint8_t) << 16) |
                   (INTERP(3, uint8_t) << 24);

  return results & ((0xF << 4) | 0xFFFF);
}

void MSP430::MemoryMapper::set_byte(MSP430::msp430_addr_t addr, msp430_byte_t value) {
  MSP430::MemoryMapping* mapping = this->get_relevant_mapping(addr);

  std::vector<msp430_byte_t> to_write = fix_endianness(value, 1);
  mapping->write_bytes(addr, to_write);
}

void MSP430::MemoryMapper::set_word(msp430_addr_t addr, msp430_word_t value) {
  MSP430::MemoryMapping* mapping
}