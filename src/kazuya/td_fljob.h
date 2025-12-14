#ifndef __KZ_TDFLJOB_H
#define __KZ_TDFLJOB_H

#include "common.h"

extern void kzTD_Set_PlateStr_FN(s32 sel_no);
extern void kzTD_Draw_Common_Fil(s32 file_no);
extern void kzTD_Job_1st_MCCheck();
extern void kzTD_Job_Fil_MakeSel();
extern void kzTD_Job_Fil_MakeConf();
extern void kzTD_Job_Fil_LoadFileSel();
extern void kzTD_Job_Fil_LoadDataSel();
extern void kzTD_Job_Fil_SaveDataSel();
extern void kzTD_Job_Fil_SaveConf();

#endif