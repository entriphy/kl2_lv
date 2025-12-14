#ifndef __KZ_STRING_H
#define __KZ_STRING_H

#include "common.h"

extern GIM_FORM **FontTables[];
extern s16 *Strings[];

extern void kzSTR_Draw(DVECTOR *sxy, u32 sz, KZCOLOR *col, s32 str_no);
extern void kzSTR_Draw_Eff(DVECTOR *sxy, u32 sz, KZCOLOR *col, s32 str_no);
extern void kzNUM_Draw(DVECTOR *sxy, u32 sz,  KZCOLOR *col, s32 font, s32 figure, u32 num);
extern void kzNUM_Draw_Eff(DVECTOR *sxy, u32 sz,  KZCOLOR *col, s32 font, s32 figure, u32 num);
extern void kzCHR_Draw_Direct(DVECTOR *sxy, u32 sz, KZCOLOR *col, s32 font_no, s16 code);
extern s16* kzCHR_Get_StringPtr(s32 str_no);
extern s16 kzCHR_Get_Indirect(s32 str_no, s16 idx);
extern void kzSTR_Draw_Direct(DVECTOR *sxy, u32 sz, KZCOLOR *col, s16 *str);
extern void kzSTR_Draw_Direct_Eff(DVECTOR *sxy, u32 sz, KZCOLOR *col, s16 *str);

#endif