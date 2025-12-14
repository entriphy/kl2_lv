#ifndef __KZ_TDNEJOB_H
#define __KZ_TDNEJOB_H

#include "common.h"

extern DVECTOR GIMBASE_NAM_ENTRY;
extern DVECTOR GIMBASE_NAM_PANEL;
extern DVECTOR GIMBASE_NAM_CRSS;
extern DVECTOR GIMBASE_NAM_CRSL;
extern DVECTOR GIMBASE_NAM_CRSB;
extern DVECTOR CHRBASE_NAM_UPPER;
extern DVECTOR CHRBASE_NAM_LOWER;
extern DVECTOR STRBASE_NAM_FUNC;
extern s32 chrrot_count;
extern s32 chrmag_count;
extern s32 usepage;
extern s32 nextpage;
extern s32 stpjob_count;
extern s16 *name_array;
extern s32 crsB_H;

extern void kzTD_Job_Nam_Entry();

#endif