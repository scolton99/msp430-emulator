//
// Created by scolton on 10/14/21.
//

#ifndef MSP430_EMULATOR_TYPES_H
#define MSP430_EMULATOR_TYPES_H

#include <cstdint>
#include <vector>

namespace MSP430 {
  typedef uint32_t msp430_addr_t;

  typedef uint32_t msp430_addr_word_t;
  typedef uint16_t msp430_word_t;
  typedef uint8_t  msp430_byte_t;

  typedef std::vector<msp430_byte_t> msp430_bytes;
}

#endif //MSP430_EMULATOR_TYPES_H
