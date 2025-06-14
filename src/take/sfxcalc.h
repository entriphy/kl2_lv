#ifndef __TAKE_SFXCALC_H
#define __TAKE_SFXCALC_H

#include "common.h"
#include "sfx.h"

extern void SfxFixCalc(SFXOBJ *pObj, PARTS *pParts, u128 *pVertexI, u128 *pColorI, u128 *pSpecUVI);
extern void SfxSkinCalc(SFXOBJ *pObj, PARTS *pParts, u128 *pVertexI, u128 *pColorI, u128 *pSpecUVI);
extern void SfxMimeCalc(SFXOBJ *pObj, PARTS *pParts, u128 *pVertexI, u128 *pColorI, u128 *pSpecUVI);

#endif
