#ifndef __KZ_TDJOB_H
#define __KZ_TDJOB_H

#include "common.h"

extern s32 first_enter;
extern s32 after_puppet_dst;
extern s32 offset_X;
extern s32 offset_Y;
extern DVECTOR GIMBASE_1ST_LOGO;
extern DVECTOR GIMBASE_TTL_WAIT;
extern DVECTOR GIMBASE_TTL_LOGO;
extern DVECTOR STRBASE_OPT_SCREXPLAIN;
extern DVECTOR STRBASE_OPT_CURRENT;
extern DVECTOR STRBASE_OPT_PAD;
extern DVECTOR STRBASE_OPT_SOUND;
extern DVECTOR GIMBASE_PAD_CONTROLER;
extern DVECTOR STRBASE_PAD_TYPE;
extern DVECTOR STRBASE_PAD_RU;
extern DVECTOR STRBASE_PAD_RD;
extern DVECTOR STRBASE_PAD_RL;
extern DVECTOR STRBASE_PAD_RR;
extern DVECTOR STRBASE_PAD_ACTION;
extern DVECTOR GIMBASE_SND_MONO;
extern DVECTOR GIMBASE_SND_STEREO;
extern DVECTOR GIMBASE_SND_5P1CH;
extern DVECTOR STRBASE_SND_MODE;
extern DVECTOR GIMBASE_ADJ_SQUARE;
extern DVECTOR GIMSIZE_ADJ_SQUARE;
extern DVECTOR GIMBASE_ADJ_TRIANGLE;
extern DVECTOR STRBASE_ADJ_SCREXPLAIN;
extern DVECTOR GIMBASE_WMP_MENU;
extern DVECTOR GIMBASE_WMP_STATUS;
extern DVECTOR STRBASE_WMP_PLACE;
extern DVECTOR GIMBASE_GAM_PSPLACE;
extern DVECTOR GIMBASE_GAM_PAUSE;
extern DVECTOR GIMBASE_GAM_VISION_S;
extern DVECTOR GIMBASE_GAM_START;
extern DVECTOR GIMBASE_GAM_STGNAME;
extern DVECTOR GIMBASE_GAM_STGINTRO;
extern DVECTOR GIMBASE_GAM_VISION_O;
extern DVECTOR GIMBASE_GAM_OVER;
extern KZCOLOR GCOL_ADJ_SQUARE;
extern KZCOLOR GCOL_ADJ_TRIANG;
extern void (*kzTwoDmsnJobTbl[])();

extern void kzTD_Step_Job(s32 add);
extern void kzTD_Back_Job(s32 sub);
extern void kzTD_Change_Job();
extern void kzTD_Call_Job();
extern void kzTD_Return_Job();
extern void kzTD_Draw_Common_Ttl();
extern void kzTD_Init_All();
extern void kzTD_Job_Idle();
extern void kzTD_Job_1st_Logo();
extern void kzTD_Job_Pup_Wait();
extern void kzTD_Job_Ttl_Menu();
extern void kzTD_Job_Opt_Top();
extern void kzTD_Job_Opt_Pad();
extern void kzTD_Job_Opt_Sound();
extern void kzTD_Job_Opt_Adjust();
extern void kzTD_Job_Wmp_Enter();
extern void kzTD_Job_Wmp_Main();
extern void kzTD_Job_Wmp_Status();
extern void kzTD_Job_Wmp_Menu();
extern void kzTD_Job_Gam_Pause();
extern void kzTD_Job_Gam_VisionStart();
extern void kzTD_Job_Gam_VisionOver();



#endif