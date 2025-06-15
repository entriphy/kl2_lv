#ifndef __NK_OBJFUNC_H
#define __NK_OBJFUNC_H

#include "common.h"

extern void (*ObjJTbl[])(OBJWORK *objw);

extern void InitObjWork(OBJWORK *objw);
extern void InitAllObjWork(OBJWORK *objwork, s32 n_objw);
extern OBJWORK* SearchOBJWORK(OBJWORK *objwork, s32 n_objw);
extern void SortObjWork(OBJWORK *objwork, s32 n_objw);
extern s32 ObjFunc(OBJWORK *objwork);

#endif
