#define DEV_MODEL_MSP430FR5994

#include "dev/model/package.h"
#include "dev/model/msp430fr5994.h"
#include "prog/bin.h"

MSP430::Package* get_device() {
  #ifdef DEV_MODEL_MSP430FR5994
    return new MSP430::MSP430FR5994();
  #else
    throw std::runtime_error("Invalid device specified");
  #endif
}

int main() {
  volatile MSP430::Package* device = get_device();
  return 0;
}
