#ifndef __KZ_TDMHJOB_H
#define __KZ_TDMHJOB_H

#include "common.h"

extern s32 mommet_mode;
extern s32 puppet_group_no;
extern DVECTOR STRBASE_MOM_MESSAGE;
extern DVECTOR STRBASE_MOM_PUPPETTOP;
extern DVECTOR STRBASE_MOM_GENJU;
extern DVECTOR GIMBASE_MOM_PLYREW;
extern DVECTOR GIMBASE_MOM_PLYSTP;
extern DVECTOR GIMBASE_MOM_PLYFWD;
extern DVECTOR STRBASE_MOM_PLYTUNE;
extern DVECTOR NUMBASE_MOM_PLYTUNE;
extern KZCOLOR GCOL_MOM_PLYNML;
extern KZCOLOR GCOL_MOM_PLYPRS;

extern void kzTD_Job_Mom_Top();
extern void kzTD_Job_Mom_Genju();
extern void kzTD_Job_Mom_Pause();
extern void kzTD_Job_Mom_PuppetTop();
extern void kzTD_Job_Mom_PuppetGroup();
extern void kzTD_Job_Mom_Concert();
extern void kzTD_Job_Mom_Gallery();

#endif