#ifndef __NK_GAME_H
#define __NK_GAME_H

#include "common.h"

extern OBJWORK ObjWorkBuff[128];
extern s32 (*GameFuncTbl[3])();
extern s16 obj_id[129];
extern qword *nkDstAdr;

extern void _nkGetMapBuf();
extern void nkInitPS2();

#endif
