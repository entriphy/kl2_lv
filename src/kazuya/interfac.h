#ifndef __KZ_INTERFAC_H
#define __KZ_INTERFAC_H

#include "common.h"

extern void kzLoadCommonGms();
extern void kzReturnTitle();
extern s32 kzCheckGenju();
extern void kzReturnGenju();
extern s32 kzCheckTheater();
extern void kzReturnTheater();
extern s32 kzGetScene();
extern void kzGameMainCL();
extern void kzGameMainWM();
extern void kzGameMainTD();
extern void kzInitNowload();
extern void kzDrawNowload();
extern void kzVisionStartOn();
extern void kzPauseOn();

#endif