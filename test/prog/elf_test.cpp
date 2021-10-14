//
// Created by scolton on 10/11/21.
//

#include <cstring>
#include <elf.h>
#include <gtest/gtest.h>
#include <unordered_set>
#include "prog/elf.h"
#include "../test_utils.h"

TEST(ProgTest, ELFFillMissing) {
  ELF::ELFObject elf;

  EXPECT_THROW_MSG(ELF::ELFObject::fill(&elf, "data/non-existent.out"),
                   std::runtime_error,
                   "File does not exist");
}

TEST(ProgTest, ELFFillSimple) {
  ELF::ELFObject elf;
  ELF::ELFObject::fill(&elf, "data/simple.out");

  EXPECT_EQ(elf.elf_header.e_phoff, 63680);
  EXPECT_EQ(elf.elf_header.e_machine, EM_MSP430);
  EXPECT_EQ(elf.elf_header.e_flags, 0);
  EXPECT_EQ(elf.elf_header.e_ehsize, 52);
  EXPECT_EQ(elf.elf_header.e_phentsize, 32);
  EXPECT_EQ(elf.elf_header.e_phnum, 4);
  EXPECT_EQ(elf.elf_header.e_ident[EI_CLASS], ELFCLASS32);
  EXPECT_EQ(elf.elf_header.e_ident[EI_DATA], ELFDATA2LSB);
  EXPECT_EQ(elf.elf_header.e_type, ET_EXEC);
  EXPECT_EQ(elf.elf_header.e_entry, 0x4000);
}

TEST(ProgTest, ELFFillComplex) {
  ELF::ELFObject elf;
  ELF::ELFObject::fill(&elf, "data/complex.out");

  EXPECT_EQ(elf.elf_header.e_phoff, 47980);
  EXPECT_EQ(elf.elf_header.e_machine, EM_MSP430);
  EXPECT_EQ(elf.elf_header.e_flags, 0);
  EXPECT_EQ(elf.elf_header.e_ehsize, 52);
  EXPECT_EQ(elf.elf_header.e_phentsize, 32);
  EXPECT_EQ(elf.elf_header.e_phnum, 7);
  EXPECT_EQ(elf.elf_header.e_ident[EI_CLASS], ELFCLASS32);
  EXPECT_EQ(elf.elf_header.e_ident[EI_DATA], ELFDATA2LSB);
  EXPECT_EQ(elf.elf_header.e_type, ET_EXEC);
  EXPECT_EQ(elf.elf_header.e_entry, 0x51A0);

  Elf32_Phdr& p = elf.program_headers[1];
  EXPECT_EQ(p.p_type, PT_LOAD);
  EXPECT_EQ(p.p_offset, 64);
  EXPECT_EQ(p.p_vaddr, 7168);
  EXPECT_EQ(p.p_memsz, 24);
  EXPECT_EQ(p.p_flags, PF_W | PF_R);
  EXPECT_EQ(p.p_align, 2);

  const std::vector<char>& data = elf.content[0];
  EXPECT_EQ(data.size(), 10);
  EXPECT_EQ(strncmp(&data[0], "\000\001\002\003\004\005\006\007\008\009\n", 10), true);
}

TEST(ProgTest, ELFFillMalformed) {
  ELF::ELFObject elf;

  EXPECT_THROW_MSG(ELF::ELFObject::fill(&elf, "data/malformed.out"),
                   std::runtime_error,
                   "Size of section in file image is less than intended memory size!");
}