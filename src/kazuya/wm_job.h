#ifndef __KZ_WM_JOB_H
#define __KZ_WM_JOB_H

#include "common.h"

extern void (*kzWorldMapJobTbl[])();

extern void kzWM_Step_Job(s32 add);
extern void kzWM_Back_Job(s32 sub);
extern void kzWM_Change_Job();
extern void kzWM_Call_Job();
extern void kzWM_Return_Job();
extern void kzWM_Init_All();
extern void kzWM_Job_Idle();
extern void kzWM_Job_Main();
extern void kzWM_Job_Status();
extern void kzWM_Job_MomTop();
extern void kzWM_Job_VisionOver();

#endif