#ifndef TAKE_MOTSYS2_H
#define TAKE_MOTSYS2_H

#include "common.h"
#include "sfx.h"

extern void GetSfxWorldMatrix(SFXOBJ *pObj);
extern void SetActCnt(SFXOBJ *pObj, f32 Cnt);
extern void SetActSpeed(SFXOBJ *pObj, f32 Speed);
extern void WorldIpMotion(SFXOBJ *pObj);

#endif
