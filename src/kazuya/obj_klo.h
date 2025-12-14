#ifndef __KZ_OBJKLO_H
#define __KZ_OBJKLO_H

#include "common.h"

extern void kzOKL_Init_Light();
extern void kzOKL_Init_RTV_Buffer(RT_WRK *rtw, s16 rtn);
extern void kzOKL_Renew_RTV_Buffer(RT_WRK *rtw);
extern void kzOKL_Get_Rot(OBJWORK *objw);
extern void kzOKL_Draw(OBJWORK *objw);
extern void kzOKL_Init(OBJWORK *objw);
extern void kzOKL_Main(OBJWORK *objw);
extern void kzOKL_Entry(OBJWORK *objw);
extern void kzOKL_Setup();

#endif