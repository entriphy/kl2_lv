#ifndef __H_TEST_SE_H
#define __H_TEST_SE_H

#include "common.h"

typedef struct { // 0x18
    /* 0x00 */ char name[16];
    /* 0x10 */ s32 prog;
    /* 0x14 */ s32 splt;
} SEINFO;

extern s32  TestKeyon(s32 prog, s32 splt, s32 eff);
extern s32  TestKeyonInv(s32 prog, s32 splt, s32 eff);
extern void hTestSEBankSet();
extern void hTestSE();
extern void hTestSEInit();

#endif
