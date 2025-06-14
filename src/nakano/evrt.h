#ifndef __NK_EVRT_H
#define __NK_EVRT_H

#include "common.h"

extern s32 nkInitEvRt(u32 *adr);
extern ROUTE* GetEvRtAdrs(s32 rtn);
extern s32 GetEvRtNo(ROUTE *rtp);
extern void DrawEvRt();

#endif