#ifndef __KZ_CVAR_H
#define __KZ_CVAR_H

#include "common.h"
#include "kazuya/bios.h"

extern KZ_MC_INFO kzMcInfo;
extern KZ_MC_INFO *mci;
extern kPadDATA *kpd0;
extern kPadDATA *kpd1;
extern s32 wm_jobcnt;
extern s32 wm_jobcnt_current;
extern s32 wm_jobcnt_next0;
extern s32 wm_jobcnt_next1;
extern s32 wm_jobcnt_sub;
extern s32 wm_jobcnt_ret;
extern s32 td_jobcnt;
extern s32 td_jobcnt_current;
extern s32 td_jobcnt_next0;
extern s32 td_jobcnt_next1;
extern s32 td_jobcnt_sub;
extern s32 td_jobcnt_ret;
extern s32 fade_count;
extern s32 fade_mode;
extern s32 vision_count;
extern s32 pause_return;
extern s32 pause_interval;
extern s32 cloud_flag;

#endif