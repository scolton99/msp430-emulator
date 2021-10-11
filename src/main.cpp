#include "prog/elf.h"

int main() {
  ELF::ELFObject obj;

  ELF::ELFObject::fill(&obj, "simple.out");
  return 0;
}
