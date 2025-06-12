#ifndef __KIT_OUTLINEFUNC_H
#define __KIT_OUTLINEFUNC_H

#include "common.h"
#include "kit.h"

extern u128* kitOutlineAllInit(u128 *packet, kitOutlineDrawEnv *pOutlineEnv, u32 fr, u32 odev);
extern u128* kitOutlineExecution(u128 *packet, kitOutlineDrawEnv *pOutlineEnv);
extern u128* kitOutlinePreRoutine(u128 *packet, kitOutlineDrawEnv *pOutlineEnv, kitOutlineObjEnv *objenv);
extern void kitOutlineColorDefine(kitOutlineDrawEnv *pOutlineEnv, kitOutlineObjEnv *objenv);
extern kitInitEffectBufAllPacket* kitInitEffectBufAll(kitInitEffectBufAllPacket *packet);
extern void kitPacketDump(u128 *buf, u32 size);

#endif
