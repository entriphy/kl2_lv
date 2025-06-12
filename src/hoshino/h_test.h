#ifndef __H_TEST_H
#define __H_TEST_H

#include "common.h"

extern s32 TestSkip;
extern s32 TestMode;
extern s32 TestWork;
extern s32 (*hTestFuncTbl[])();

extern void hTestInit();
extern void hTestBGM();
extern void hTestPPT();
extern void hTestAC3();
extern void hTestConfig();
extern void hTestMov();
extern void hTestMain();

#endif