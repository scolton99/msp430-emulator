//
// Created by scolton on 10/12/21.
//

#ifndef MSP430_EMULATOR_TEST_UTILS_H
#define MSP430_EMULATOR_TEST_UTILS_H

#include <gtest/gtest.h>

#define EXPECT_THROW_MSG(st,typ,msg) EXPECT_THROW({                        \
                                       try {                               \
                                         st;                               \
                                       } catch (const typ& e) {            \
                                         EXPECT_STREQ(e.what(), msg);      \
                                         throw e;                          \
                                       } catch (const std::exception& e) { \
                                         throw e;                          \
                                       }                                   \
                                     }, typ)

#endif //MSP430_EMULATOR_TEST_UTILS_H
