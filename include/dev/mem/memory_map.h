//
// Created by scolton on 10/10/21.
//

#ifndef MSP430_EMULATOR_MEMORY_MAP_H
#define MSP430_EMULATOR_MEMORY_MAP_H

#include <cstdint>
#include <map>
#include <vector>

namespace MSP430 {
  typedef uint32_t msp430_addr_t;

  typedef uint32_t msp430_address_word_t;
  typedef uint16_t msp430_word_t;
  typedef uint8_t  msp430_byte_t;

  enum MemActionDirection {
    READ,
    WRITE
  };

  class MemoryProvider {
  public:
    virtual char get(msp430_addr_t)                = 0;
    virtual void set(msp430_addr_t, msp430_byte_t) = 0;
  };

  class MemoryMapping {
  private:
    const msp430_addr_t   start;
    const uint32_t        length;
    MemoryProvider* const dev;
    const msp430_addr_t   dev_start;
  public:
    MemoryMapping(msp430_addr_t   start,
                  uint32_t        length,
                  MemoryProvider* dev,
                  msp430_addr_t   dev_start) :
                  start(start),
                  length(length),
                  dev(dev),
                  dev_start(dev_start) { }
    uint32_t get_length() const;
    msp430_addr_t offset(msp430_addr_t) const;
    std::vector<msp430_byte_t> get_bytes(msp430_addr_t dev_addr, uint8_t length);
    void write_bytes(msp430_addr_t addr, const std::vector<msp430_byte_t>& bytes);
  };

  class MemoryMapper {
  private:
    std::map<msp430_addr_t, MemoryMapping> mappings;
    MemoryMapping*    get_relevant_mapping(msp430_addr_t addr);
    static std::vector<msp430_byte_t> fix_endianness(msp430_address_word_t value, uint8_t size);
  public:
    msp430_byte_t         get_byte(msp430_addr_t addr);
    msp430_word_t         get_word(msp430_addr_t addr);
    msp430_address_word_t get_address_word(msp430_addr_t addr);
    void                  set_byte(msp430_addr_t addr, msp430_byte_t value);
    void                  set_word(msp430_addr_t addr, msp430_word_t value);
    void                  set_address_word(msp430_addr_t addr, msp430_address_word_t value);
    void                  add_mapping(MemoryMapping mapping);
    void                  remove_mapping(msp430_addr_t start);
  };
}

#endif //MSP430_EMULATOR_MEMORY_MAP_H
