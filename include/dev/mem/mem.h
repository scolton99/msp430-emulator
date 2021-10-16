//
// Created by scolton on 10/10/21.
//

#ifndef MSP430_EMULATOR_MEM_H
#define MSP430_EMULATOR_MEM_H

#include <cstdint>
#include <map>
#include <vector>
#include "types.h"

namespace MSP430 {
  /**
   * Represents any entity that can provide the concept of random-access memory.
   *
   * This involves the ability to set a byte at an address and to be able to read
   * that byte back later.
   *
   * No addresses are guaranteed to be supported by the underlying "device".
   */
  class MemoryProvider {
  public:
    virtual msp430_byte_t get(msp430_addr_t)                = 0;
    virtual void          set(msp430_addr_t, msp430_byte_t) = 0;
  };

  /**
   * Represents a mapping between a set of addresses in the package's address space and some addresses in a device's address space.
   */
  struct MemoryMapping {
    /** The device to which these package-space addresses are mapped. */
    MemoryProvider* const dev;

    /** The starting address in package address space. */
    const msp430_addr_t   package_start;

    /** The length of the mapping, in bytes. */
    const uint32_t        length;

    /** The starting address of the mapping in device space. */
    const msp430_addr_t   dev_start;
  };

  template <typename msp430_size_t>
  class Instruction;

  class MemoryMapper {
    friend class Instruction<msp430_byte_t>;
    friend class Instruction<msp430_word_t>;
    friend class Instruction<msp430_addr_word_t>;

  private:
    std::map<msp430_addr_t, MemoryMapping> mappings;

  public:
    msp430_byte_t         get_byte(msp430_addr_t addr);
    msp430_word_t         get_word(msp430_addr_t addr);
    msp430_addr_word_t    get_address_word(msp430_addr_t addr);
    void                  set_byte(msp430_addr_t addr, msp430_byte_t value);
    void                  set_word(msp430_addr_t addr, msp430_word_t value);
    void                  set_address_word(msp430_addr_t addr, msp430_addr_word_t value);
    void                  add_mapping(MemoryMapping mapping);

  private:
    template<typename msp430_size_t>
    static msp430_size_t              unfix_endianness(const msp430_bytes&);

    template<typename msp430_size_t>
    static std::vector<msp430_byte_t> fix_endianness(msp430_size_t);

    static msp430_addr_t              convert_to_offset(MemoryMapping&, msp430_addr_t package_addr);
    static msp430_addr_t              canonical_dev_address(MemoryMapping&, msp430_addr_t offset);
    static bool                       validate_address_word(msp430_addr_word_t value);
    static bool                       overlap(msp430_addr_t, msp430_addr_t, msp430_addr_t, msp430_addr_t);
    static void                       write_bytes(MemoryMapping&, msp430_addr_t offset, const msp430_bytes&);
    static msp430_bytes               read_bytes(MemoryMapping&, msp430_addr_t offset, msp430_addr_t length);
    MemoryMapping*                    get_relevant_mapping(msp430_addr_t addr);

    template<typename msp430_size_t>
    msp430_size_t                     get(msp430_addr_t);

    template<typename msp430_size_t>
    void                              set(msp430_addr_t, msp430_size_t);
  };
}

#endif //MSP430_EMULATOR_MEM_H
