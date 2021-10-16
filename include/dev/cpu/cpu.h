//
// Created by scolton on 10/8/21.
//

#ifndef MSP430_EMULATOR_CPU_H
#define MSP430_EMULATOR_CPU_H

#include "register.h"
#include "types.h"

namespace Testing {
  class CPUXTest;
}

namespace MSP430 {
  class Package;

  template <typename msp430_size_t>
  class Instruction;

  class ICPU {
  public:
    virtual void tick() = 0;
    virtual MSP430::IRegister* get_pc()                             = 0;
    virtual MSP430::IRegister* get_sr()                             = 0;
    virtual MSP430::IRegister* get_sp()                             = 0;
    virtual msp430_word_t      read_word_and_inc_pc()               = 0;
    virtual int32_t            addr_word_sxt_32(msp430_addr_word_t) = 0;
    virtual int32_t            word_sxt_32(msp430_word_t)           = 0;
    virtual IRegister*         resolve_register(uint8_t)            = 0;
  };

  class CPUX : public ICPU {
    friend class Testing::CPUXTest;
  private:
    RegisterX* r0 ;
    RegisterX* r1 ;
    RegisterX* r2 ;
    RegisterX* r3 ;
    RegisterX* r4 ;
    RegisterX* r5 ;
    RegisterX* r6 ;
    RegisterX* r7 ;
    RegisterX* r8 ;
    RegisterX* r9 ;
    RegisterX* r10;
    RegisterX* r11;
    RegisterX* r12;
    RegisterX* r13;
    RegisterX* r14;
    RegisterX* r15;
    Package*   package;
  protected:
    IRegister* resolve_register(uint8_t) override;
  public:
    explicit CPUX(Package*);
    ~CPUX();
    void tick() override;
    MSP430::IRegister* get_pc()                             override;
    MSP430::IRegister* get_sr()                             override;
    MSP430::IRegister* get_sp()                             override;
    msp430_word_t      read_word_and_inc_pc()               override;
    int32_t            addr_word_sxt_32(msp430_addr_word_t) override;
    int32_t            word_sxt_32(msp430_word_t)           override;
  };
}

#endif //MSP430_EMULATOR_CPU_H
