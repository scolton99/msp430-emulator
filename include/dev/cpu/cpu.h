//
// Created by scolton on 10/8/21.
//

#ifndef MSP430_EMULATOR_CPU_H
#define MSP430_EMULATOR_CPU_H

#include "register.h"

namespace MSP430 {
  class Package;

  class ICPU {
    template <typename msp430_size_t>
    friend class InstructionFormatI;

    friend class InstructionFormatII;
  protected:
    virtual IRegister* resolve_register(uint8_t) = 0;
  public:
    virtual void tick() = 0;
    virtual MSP430::IRegister* get_pc() = 0;
    virtual MSP430::IRegister* get_sr() = 0;
    virtual MSP430::IRegister* get_sp() = 0;
  };

  class CPUX : public ICPU {
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
    CPUX(Package*);
    ~CPUX();
    void tick() override;
    MSP430::IRegister* get_pc() override;
    MSP430::IRegister* get_sr() override;
    MSP430::IRegister* get_sp() override;
  };
}

#endif //MSP430_EMULATOR_CPU_H
