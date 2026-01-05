#ifndef __HR_PREAM_H
#define __HR_PREAM_H

#include "common.h"
#include "harada/hr_prm.h"

extern s32 (*HrPtMotTbl[KL2_VER_COND(8, 10)])(HR_CALL *ca, HR_PSYS *ps);
extern s32 (*HrPtSndTbl[KL2_VER_COND(14, 17)])(HR_CALL *ca, HR_PSYS *ps);

extern void hr_set_motion(HR_CALL *ca, s32 noth);
extern s32 pt_se_changer(s32 id);
extern s32 pt_motlp_secall(HR_CALL *ca);

#endif
