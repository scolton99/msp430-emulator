//
// Created by scolton on 10/8/21.
//

#ifndef MSP430_EMULATOR_INSTRUCTION_H
#define MSP430_EMULATOR_INSTRUCTION_H

#include "dev/cpu/execute.h"
#include "dev/model/package.h"
#include "utils.h"
#include "visitor.h"

namespace MSP430 {
  template <typename msp430_size_t>
  class Instruction {
  protected:
    static AddressingMode resolve_dst_addr_mode(uint8_t ad, uint8_t rdst);
    static bool           is_addr_instruction(Instruction<msp430_size_t>*);
    static msp430_addr_t  calc_idx_sym_abs_addr(ICPU*      cpu,
                                                IRegister* rsrc,
                                                bool       extended,
                                                bool       absolute,
                                                uint8_t    ext_src_msn);
    static msp430_size_t get_op_value(Package*       package,
                                      AddressingMode mode,
                                      uint8_t        r,
                                      uint8_t        as,
                                      uint8_t        op_msn,
                                      bool           extended); // not idempotent for src, idempotent for dest

    static void          set_op_value(Package*       package,
                                      AddressingMode mode,
                                      uint8_t        r,
                                      uint8_t        as,
                                      uint8_t        op_msn,
                                      bool           extended,
                                      msp430_size_t  value);
  public:
    virtual void accept(InstructionVisitor<msp430_size_t>&) = 0;
    virtual bool has_extension_word()                       = 0;
    virtual int  extra_words()                              = 0;
    virtual int  get_execution_time()                       = 0;
    virtual bool is_extended()                              = 0;
  };
}

#endif //MSP430_EMULATOR_INSTRUCTION_H