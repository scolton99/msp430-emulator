//
// Created by scolton on 10/11/21.
//

#include "dev/cpu/register.h"

uint32_t MSP430::RegisterX::get_truncator(uint8_t size) {
  uint32_t truncator = 0;
  for (int i = 0; i < size; ++i)
    truncator |= 0xFF << (8 * i);

  if (size > 2)
    truncator &= 0xFFFFF;

  return truncator;
}

uint32_t MSP430::GPRegisterX::get_value(uint8_t, uint8_t size) {
  return this->value & get_truncator(size);
}

void MSP430::GPRegisterX::set_value(uint32_t value) {
  this->value = value & 0xFFFFF;
}

uint8_t MSP430::SRRegisterX::bit(uint8_t bit) {
  return !!(this->value & (0b1u << bit));
}

void MSP430::SRRegisterX::set_bit(uint8_t bit, uint8_t value = 1) {
  if (value != 0)
    this->value |= ((value & 0b1) << bit);
  else
    this->clr_bit(bit);
}

void MSP430::SRRegisterX::clr_bit(uint8_t bit) {
  this->value &= ~(0b1 << bit);
}

uint32_t MSP430::SRRegisterX::get_value(uint8_t as, uint8_t size) {
  uint32_t value;
  switch (as) {
    case 0b00:
      value = this->value;
      break;
    case 0b01:
      value = 0x0;
      break;
    case 0b10:
      value = 0x4;
      break;
    case 0b11:
      value = 0x8;
      break;
    default:
      throw std::runtime_error("Invalid As value for SP/CG1");
  }
  return value & get_truncator(size);
}

void MSP430::SRRegisterX::set_value(uint32_t value) {
  this->value = value;
}

uint8_t MSP430::SRRegisterX::V() {
  return this->bit(8);
}

uint8_t MSP430::SRRegisterX::SCG1() {
  return this->bit(7);
}

uint8_t MSP430::SRRegisterX::SCG0() {
  return this->bit(6);
}

uint8_t MSP430::SRRegisterX::OSCOFF() {
  return this->bit(5);
}

uint8_t MSP430::SRRegisterX::CPUOFF() {
  return this->bit(4);
}

uint8_t MSP430::SRRegisterX::GIE() {
  return this->bit(3);
}

uint8_t MSP430::SRRegisterX::N() {
  return this->bit(2);
}

uint8_t MSP430::SRRegisterX::Z() {
  return this->bit(1);
}

uint8_t MSP430::SRRegisterX::C() {
  return this->bit(0);
}

void MSP430::SRRegisterX::setV(uint8_t value) {
  this->set_bit(8, value);
}

void MSP430::SRRegisterX::clrV() {
  this->clr_bit(8);
}

void MSP430::SRRegisterX::setSCG1(uint8_t value) {
  this->set_bit(7, value);
}

void MSP430::SRRegisterX::clrSCG1() {
  this->clr_bit(7);
}

void MSP430::SRRegisterX::setSCG0(uint8_t value) {
  this->set_bit(6, value);
}

void MSP430::SRRegisterX::clrSCG0() {
  this->clr_bit(6);
}

void MSP430::SRRegisterX::setOSCOFF(uint8_t value) {
  this->set_bit(5, value);
}

void MSP430::SRRegisterX::clrOSCOFF() {
  this->clr_bit(5);
}

void MSP430::SRRegisterX::setCPUOFF(uint8_t value) {
  this->set_bit(4, value);
}

void MSP430::SRRegisterX::clrCPUOFF() {
  this->clr_bit(4);
}

void MSP430::SRRegisterX::setGIE(uint8_t value) {
  this->set_bit(3, value);
}

void MSP430::SRRegisterX::clrGIE() {
  this->clr_bit(3);
}

void MSP430::SRRegisterX::setN(uint8_t value) {
  this->set_bit(2, value);
}

void MSP430::SRRegisterX::clrN() {
  this->clr_bit(2);
}

void MSP430::SRRegisterX::setZ(uint8_t value) {
  this->set_bit(1, value);
}

void MSP430::SRRegisterX::clrZ() {
  this->clr_bit(1);
}

void MSP430::SRRegisterX::setC(uint8_t value) {
  this->set_bit(0, value);
}

void MSP430::SRRegisterX::clrC() {
  this->clr_bit(0);
}

uint32_t MSP430::CG2RegisterX::get_value(uint8_t as, uint8_t size) {
  uint32_t value;
  switch (as) {
    case 0b00:
      value = 0x0;
      break;
    case 0b01:
      value = 0x1;
      break;
    case 0b10:
      value = 0x2;
      break;
    case 0b11:
      value = 0xFFFFF;
      break;
    default:
      throw std::runtime_error("Invalid value for As in CG register");
  }
  return value & get_truncator(size);
}

void MSP430::CG2RegisterX::set_value(uint32_t) {
  throw std::runtime_error("Can't set CG2 value");
}