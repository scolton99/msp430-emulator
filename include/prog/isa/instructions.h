//
// Created by scolton on 10/15/21.
//

#ifndef MSP430_EMULATOR_INSTRUCTIONS_H
#define MSP430_EMULATOR_INSTRUCTIONS_H

#include "format_i.h"
#include "format_ii.h"
#include "format_address.h"
#include "format_rxxm.h"
#include "format_pushm_popm.h"
#include "format_jump.h"
#include "format_calla.h"

namespace MSP430 {
  template <typename msp430_size_t>
  class ADDInstruction : public InstructionFormatI<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit ADDInstruction(msp430_word_t base_instr,
                            msp430_word_t ext_word = 0) :
        InstructionFormatI<msp430_size_t>(base_instr, ext_word) { }

    ADDInstruction(uint8_t rsrc,
                   uint8_t as,
                   uint8_t ad,
                   uint8_t rdst,
                   msp430_word_t ext_word = 0) : InstructionFormatI<msp430_size_t>(rsrc, as, ad, rdst, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class ADDCInstruction : public InstructionFormatI<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit ADDCInstruction(msp430_word_t base_instr,
                             msp430_word_t ext_word = 0) :
        InstructionFormatI<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class ANDInstruction : public InstructionFormatI<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit ANDInstruction(msp430_word_t base_instr,
                            msp430_word_t ext_word = 0) :
        InstructionFormatI<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class BICInstruction : public InstructionFormatI<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit BICInstruction(msp430_word_t base_instr,
                            msp430_word_t ext_word = 0) :
        InstructionFormatI<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class BITInstruction : public InstructionFormatI<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit BITInstruction(msp430_word_t base_instr,
                            msp430_word_t ext_word = 0) :
        InstructionFormatI<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class BISInstruction : public InstructionFormatI<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit BISInstruction(msp430_word_t base_instr,
                            msp430_word_t ext_word = 0) :
        InstructionFormatI<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class CMPInstruction : public InstructionFormatI<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit CMPInstruction(msp430_word_t base_instr,
                            msp430_word_t ext_word = 0) :
        InstructionFormatI<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class DADDInstruction : public InstructionFormatI<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit DADDInstruction(msp430_word_t base_instr,
                             msp430_word_t ext_word = 0) :
        InstructionFormatI<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class MOVInstruction : public InstructionFormatI<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit MOVInstruction(msp430_word_t base_instr,
                            msp430_word_t ext_word = 0) :
        InstructionFormatI<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class SUBInstruction : public InstructionFormatI<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit SUBInstruction(msp430_word_t base_instr,
                            msp430_word_t ext_word = 0) :
        InstructionFormatI<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class SUBCInstruction : public InstructionFormatI<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit SUBCInstruction(msp430_word_t base_instr,
                             msp430_word_t ext_word = 0) :
        InstructionFormatI<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class XORInstruction : public InstructionFormatI<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit XORInstruction(msp430_word_t base_instr,
                            msp430_word_t ext_word = 0) :
        InstructionFormatI<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class CALLInstruction : public InstructionFormatII<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit CALLInstruction(msp430_word_t base_instr,
                             msp430_word_t ext_word = 0) :
        InstructionFormatII<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class PUSHInstruction : public InstructionFormatII<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit PUSHInstruction(msp430_word_t base_instr,
                             msp430_word_t ext_word = 0) :
        InstructionFormatII<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class RETIInstruction : public InstructionFormatII<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit RETIInstruction(msp430_word_t base_instr,
                             msp430_word_t ext_word = 0) :
        InstructionFormatII<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class RRAInstruction : public InstructionFormatII<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit RRAInstruction(msp430_word_t base_instr,
                            msp430_word_t ext_word = 0) :
        InstructionFormatII<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class RRCInstruction : public InstructionFormatII<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit RRCInstruction(msp430_word_t base_instr,
                            msp430_word_t ext_word = 0) :
        InstructionFormatII<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class SWPBInstruction : public InstructionFormatII<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit SWPBInstruction(msp430_word_t base_instr,
                             msp430_word_t ext_word = 0) :
        InstructionFormatII<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class SXTInstruction : public InstructionFormatII<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit SXTInstruction(msp430_word_t base_instr,
                            msp430_word_t ext_word = 0) :
        InstructionFormatII<msp430_size_t>(base_instr, ext_word) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    };
  };

  template <typename msp430_size_t>
  class JCInstruction : public InstructionJumpFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit JCInstruction(msp430_word_t base_instr) :
        InstructionJumpFormat<msp430_size_t>(base_instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };

  template <typename msp430_size_t>
  class JEQInstruction : public InstructionJumpFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit JEQInstruction(msp430_word_t base_instr) :
        InstructionJumpFormat<msp430_size_t>(base_instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };

  template <typename msp430_size_t>
  class JGEInstruction : public InstructionJumpFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit JGEInstruction(msp430_word_t base_instr) :
        InstructionJumpFormat<msp430_size_t>(base_instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };

  template <typename msp430_size_t>
  class JLInstruction : public InstructionJumpFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit JLInstruction(msp430_word_t base_instr) :
        InstructionJumpFormat<msp430_size_t>(base_instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };

  template <typename msp430_size_t>
  class JMPInstruction : public InstructionJumpFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit JMPInstruction(msp430_word_t base_instr) :
        InstructionJumpFormat<msp430_size_t>(base_instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };

  template <typename msp430_size_t>
  class JNCInstruction : public InstructionJumpFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit JNCInstruction(msp430_word_t base_instr) :
        InstructionJumpFormat<msp430_size_t>(base_instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };

  template <typename msp430_size_t>
  class JNInstruction : public InstructionJumpFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit JNInstruction(msp430_word_t base_instr) :
        InstructionJumpFormat<msp430_size_t>(base_instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };

  template <typename msp430_size_t>
  class JNEInstruction : public InstructionJumpFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit JNEInstruction(msp430_word_t base_instr) :
        InstructionJumpFormat<msp430_size_t>(base_instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };

  template <typename msp430_size_t>
  class POPMInstruction : public InstructionPushmPopmFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit POPMInstruction(msp430_word_t instr) :
        InstructionPushmPopmFormat<msp430_size_t>(instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };

  template <typename msp430_size_t>
  class PUSHMInstruction : public InstructionPushmPopmFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit PUSHMInstruction(msp430_word_t instr) :
        InstructionPushmPopmFormat<msp430_size_t>(instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };

  template <typename msp430_size_t>
  class RLAMInstruction : public InstructionRXXMFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit RLAMInstruction(msp430_word_t instr) :
        InstructionRXXMFormat<msp430_size_t>(instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };

  template <typename msp430_size_t>
  class RRAMInstruction : public InstructionRXXMFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit RRAMInstruction(msp430_word_t instr) :
        InstructionRXXMFormat<msp430_size_t>(instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };

  template <typename msp430_size_t>
  class RRCMInstruction : public InstructionRXXMFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit RRCMInstruction(msp430_word_t instr) :
        InstructionRXXMFormat<msp430_size_t>(instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };

  template <typename msp430_size_t>
  class RRUMInstruction : public InstructionRXXMFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit RRUMInstruction(msp430_word_t instr) :
        InstructionRXXMFormat<msp430_size_t>(instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };

  template <typename msp430_size_t>
  class CALLAInstruction : public InstructionCALLAFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit CALLAInstruction(msp430_word_t instr) :
        InstructionCALLAFormat<msp430_size_t>(instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };

  template <typename msp430_size_t>
  class ADDAInstruction : public InstructionAddressFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit ADDAInstruction(msp430_word_t instr) :
        InstructionAddressFormat<msp430_size_t>(instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };

  template <typename msp430_size_t>
  class CMPAInstruction : public InstructionAddressFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit CMPAInstruction(msp430_word_t instr) :
        InstructionAddressFormat<msp430_size_t>(instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };

  template <typename msp430_size_t>
  class MOVAInstruction : public InstructionAddressFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit MOVAInstruction(msp430_word_t instr) :
        InstructionAddressFormat<msp430_size_t>(instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };

  template <typename msp430_size_t>
  class SUBAInstruction : public InstructionAddressFormat<msp430_size_t> {
    friend class InstructionExecutionVisitor<msp430_size_t>;

  public:
    explicit SUBAInstruction(msp430_word_t instr) :
        InstructionAddressFormat<msp430_size_t>(instr) { }

    void accept(InstructionVisitor<msp430_size_t>& visitor) override {
      visitor.visit(*this);
    }
  };
}

#endif //MSP430_EMULATOR_INSTRUCTIONS_H
