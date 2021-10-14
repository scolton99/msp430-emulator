//
// Created by scolton on 10/12/21.
//

#include <gtest/gtest.h>
#include "dev/mem/memory_map.h"
#include "memory_map_test.h"
#include "../../test_utils.h"

#define TEST_MEMORY_SIZE_BYTES 1024

MockProvider::MockProvider() {
  this->memory.resize(TEST_MEMORY_SIZE_BYTES);
}

MSP430::msp430_byte_t MockProvider::get(MSP430::msp430_addr_t addr) {
  return this->memory[addr];
}

void MockProvider::set(MSP430::msp430_addr_t addr, MSP430::msp430_byte_t value) {
  this->memory[addr] = value;
}

void read_bytes(MSP430::MemoryMapper& mapper, MSP430::msp430_addr_t package_addr, MSP430::msp430_bytes& into) {
  MSP430::msp430_addr_t cur_addr = package_addr;
  for (MSP430::msp430_byte_t& byte: into)
    byte = mapper.get_byte(cur_addr++);
}

void write_bytes(MSP430::MemoryMapper& mapper, MSP430::msp430_addr_t package_addr, const MSP430::msp430_bytes& data) {
  MSP430::msp430_addr_t cur_addr = package_addr;
  for (const MSP430::msp430_byte_t& byte: data)
    mapper.set_byte(cur_addr++, byte);
}

void write_and_read_back_bytes(MSP430::MemoryMapping& mapping, MSP430::msp430_addr_t package_addr, const MSP430::msp430_bytes& data) {
  MSP430::MemoryMapper mapper;
  mapper.add_mapping(mapping);

  write_bytes(mapper, package_addr, data);

  MSP430::msp430_bytes readback;
  readback.resize(data.size());

  read_bytes(mapper, package_addr, readback);

  EXPECT_EQ(readback, data);

  MSP430::msp430_addr_t offset = package_addr - mapping.package_start;
  for (int i = 0; i < data.size(); ++i) {
    MSP430::msp430_byte_t byte = mapping.dev->get(offset + mapping.dev_start + i);
    EXPECT_EQ(byte, data[i]);
  }
}

TEST(MemTest, DevOffsetTest) {
  MSP430::msp430_addr_t start = 0x8000;

  MockProvider          mp;
  MSP430::MemoryMapping mm {&mp, start, 0x100, 0x200};
  MSP430::msp430_bytes  bytes {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  write_and_read_back_bytes(mm, start, bytes);
}

TEST(MemTest, OffsetTest) {
  MSP430::msp430_addr_t start = 0x4000;
  MSP430::msp430_addr_t space = 0x4;

  MockProvider          mp;
  MSP430::MemoryMapping mm = {&mp, start, 0x80, 0x0};
  MSP430::msp430_bytes  bytes {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x21, 0x0};

  write_and_read_back_bytes(mm, start + space, bytes);
}

TEST(MemTest, AddressWordTruncationMemoryMapperTest) {
  MSP430::msp430_addr_t addr      = 0x4000;
  MSP430::msp430_addr_t dev_start = 0x200;

  MockProvider          mp;
  MSP430::MemoryMapping mm {&mp, addr, 0x100, dev_start};
  MSP430::MemoryMapper  mapper;

  MSP430::msp430_addr_t value          = 0xFFFFFF;
  MSP430::msp430_addr_t expected_value = 0xFFFFF;

  mapper.add_mapping(mm);
  mapper.set_address_word(addr, value);

  EXPECT_EQ(mapper.get_address_word(addr), expected_value);

  MSP430::msp430_bytes expected_bytes {0xFF, 0xFF, 0x0F, 0x00};

  MSP430::msp430_bytes actual_bytes;
  actual_bytes.resize(4);

  read_bytes(mapper, addr, actual_bytes);

  EXPECT_EQ(expected_bytes, actual_bytes);

  for (int i = 0; i < sizeof(MSP430::msp430_addr_word_t); ++i)
    EXPECT_EQ(mp.get(dev_start + i), expected_bytes[i]);

  MSP430::msp430_addr_t read_start = addr + sizeof(MSP430::msp430_addr_word_t);
  write_bytes(mapper, read_start, {0xFF, 0xFF, 0xFF, 0xFF});

  EXPECT_EQ(mapper.get_address_word(read_start), 0xFFFFF);
}

TEST(MemTest, ForbidOverlappingPackageMappings) {
  MockProvider          mp;
  MSP430::MemoryMapping mm1 {&mp, 0x4000, 0x100, 0x0};
  MSP430::MemoryMapping mm2 {&mp, 0x4080, 0x100, 0x100};
  MSP430::MemoryMapper  mapper;

  mapper.add_mapping(mm1);

  EXPECT_THROW_MSG(mapper.add_mapping(mm2), std::runtime_error, "Refusing to add overlapping mapping");
}

TEST(MemTest, OverlappingDevMappings) {
  MockProvider          mp;
  MSP430::MemoryMapping mm1 {&mp, 0x4000, 0x100, 0x0};
  MSP430::MemoryMapping mm2 {&mp, 0x4100, 0x100, 0x0};
  MSP430::MemoryMapper  mapper;

  mapper.add_mapping(mm1);
  mapper.add_mapping(mm2);

  MSP430::msp430_bytes bytes {0x12, 0x34, 0x56, 0x78, 0x9A};

  write_bytes(mapper, 0x4000, bytes);

  MSP430::msp430_bytes readback1, readback2;
  readback1.resize(bytes.size());
  readback2.resize(bytes.size());

  read_bytes(mapper, 0x4000, readback1);
  read_bytes(mapper, 0x4100, readback2);

  EXPECT_EQ(bytes, readback1);
  EXPECT_EQ(bytes, readback2);

  mapper.set_word(0x4020, 0xABCD);
  EXPECT_EQ(mapper.get_word(0x4120), 0xABCD);
}

TEST(MemTest, InvalidPackageAddress) {
  MockProvider          mp;
  MSP430::MemoryMapping mm {&mp, 0x4000, 0x800, 0x0};
  MSP430::MemoryMapper  mapper;

  mapper.add_mapping(mm);

  EXPECT_THROW_MSG(mapper.get_byte(0x5000), std::runtime_error, "Couldn't find mapping for address");
}

TEST(MemTest, UnfixEndiannessInvalidSize) {

}