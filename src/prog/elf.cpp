//
// Created by scolton on 10/9/21.
//

#include <algorithm>
#include <istream>
#include <fstream>
#include <string>
#include <elf.h>
#include "prog/elf.h"

#define PTR_SZ_PAIR(obj, param) reinterpret_cast<char *>(&(obj.param)), sizeof(obj.param)

void ELF::ELFObject::fill(ELF::ELFObject* elf, const std::string& filename) {
  std::ifstream file(filename, std::ios::binary | std::ios::in);

  if (!file.is_open())
    throw std::runtime_error("File does not exist");

  Elf32_Ehdr elf_header;
  file.read(PTR_SZ_PAIR(elf_header, e_ident));
  file.read(PTR_SZ_PAIR(elf_header, e_type));
  file.read(PTR_SZ_PAIR(elf_header, e_machine));
  file.read(PTR_SZ_PAIR(elf_header, e_version));
  file.read(PTR_SZ_PAIR(elf_header, e_entry));
  file.read(PTR_SZ_PAIR(elf_header, e_phoff));
  file.read(PTR_SZ_PAIR(elf_header, e_shoff));
  file.read(PTR_SZ_PAIR(elf_header, e_flags));
  file.read(PTR_SZ_PAIR(elf_header, e_ehsize));
  file.read(PTR_SZ_PAIR(elf_header, e_phentsize));
  file.read(PTR_SZ_PAIR(elf_header, e_phnum));
  file.read(PTR_SZ_PAIR(elf_header, e_shentsize));
  file.read(PTR_SZ_PAIR(elf_header, e_shnum));
  file.read(PTR_SZ_PAIR(elf_header, e_shstrndx));

  elf->elf_header = elf_header;

  file.seekg(elf_header.e_phoff);

  std::vector<Elf32_Phdr> program_headers;
  program_headers.resize(elf_header.e_phnum);

  std::vector<std::vector<char>> content;
  content.resize(elf_header.e_phnum);

  for (int i = 0; i < elf_header.e_phnum; ++i) {
    Elf32_Phdr program_header;

    file.read(PTR_SZ_PAIR(program_header, p_type));
    file.read(PTR_SZ_PAIR(program_header, p_offset));
    file.read(PTR_SZ_PAIR(program_header, p_vaddr));
    file.read(PTR_SZ_PAIR(program_header, p_paddr));
    file.read(PTR_SZ_PAIR(program_header, p_filesz));
    file.read(PTR_SZ_PAIR(program_header, p_memsz));
    file.read(PTR_SZ_PAIR(program_header, p_flags));
    file.read(PTR_SZ_PAIR(program_header, p_align));

    program_headers[i] = program_header;

    if (program_header.p_memsz < program_header.p_filesz)
      throw std::runtime_error("Size of section in file image is less than intended memory size!");

    std::ios::pos_type snapback = file.tellg();

    std::vector<char> section_content;
    section_content.resize(program_header.p_memsz);
    file.seekg(program_header.p_offset);
    file.read(&section_content[0], program_header.p_filesz);

    content[i] = section_content;

    file.seekg(snapback);
  }

  elf->program_headers = program_headers;
  elf->content         = content;
}