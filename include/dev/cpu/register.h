//
// Created by scolton on 10/11/21.
//

#ifndef MSP430_EMULATOR_REGISTER_H
#define MSP430_EMULATOR_REGISTER_H

#include <cstdint>
#include <unordered_map>

namespace MSP430 {
  class IRegister {
  public:
    virtual unsigned int get_value(uint8_t, uint8_t) = 0;
    virtual void         set_value(uint32_t)         = 0;
    virtual ~IRegister()                             = default;
  };

//  class Register : public IRegister {
//  protected:
//    uint16_t value;
//  };

  class RegisterX : public IRegister {
  public:
    ~RegisterX() override = default;
  protected:
    static uint32_t get_truncator(uint8_t);
    unsigned int value:20;
    RegisterX() : value(0) { }
  };

  class GPRegisterX : public RegisterX {
  public:
    GPRegisterX() = default;
    uint32_t get_value(uint8_t, uint8_t) override;
    void     set_value(uint32_t)         override;
  };

  class SRRegisterX : public RegisterX {
  private:
    uint8_t  bit(uint8_t);
    void     set_bit(uint8_t, uint8_t);
    void     clr_bit(uint8_t);
  public:
    SRRegisterX() = default;
    uint32_t get_value(uint8_t, uint8_t) override;
    void     set_value(uint32_t)         override;
    uint8_t  V();
    uint8_t  SCG0();
    uint8_t  SCG1();
    uint8_t  OSCOFF();
    uint8_t  CPUOFF();
    uint8_t  GIE();
    uint8_t  N();
    uint8_t  Z();
    uint8_t  C();
    void     setV(uint8_t = 1);
    void     clrV();
    void     setSCG0(uint8_t = 1);
    void     clrSCG0();
    void     setSCG1(uint8_t = 1);
    void     clrSCG1();
    void     setOSCOFF(uint8_t = 1);
    void     clrOSCOFF();
    void     setCPUOFF(uint8_t = 1);
    void     clrCPUOFF();
    void     setGIE(uint8_t = 1);
    void     clrGIE();
    void     setN(uint8_t = 1);
    void     clrN();
    void     setZ(uint8_t = 1);
    void     clrZ();
    void     setC(uint8_t = 1);
    void     clrC();
  };

  class CG2RegisterX : public RegisterX {
  public:
    CG2RegisterX() = default;
    uint32_t get_value(uint8_t, uint8_t) override;
    void     set_value(uint32_t)         override;
  };
}

#endif //MSP430_EMULATOR_REGISTER_H
