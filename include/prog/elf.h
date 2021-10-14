//
// Created by scolton on 10/9/21.
//

#ifndef MSP430_EMULATOR_ELF_H
#define MSP430_EMULATOR_ELF_H

#include <vector>
#include <string>
#include <elf.h>

namespace ELF {
  class ELFObject {
  public:
    Elf32_Ehdr                     elf_header;
    std::vector<Elf32_Phdr>        program_headers;
    std::vector<std::vector<char>> content;
    static void fill(ELFObject* elf, const std::string& filename);
  };
}

#endif //MSP430_EMULATOR_ELF_H
