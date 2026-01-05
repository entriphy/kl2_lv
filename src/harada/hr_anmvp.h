#ifndef __HR_ANMVP_H
#define __HR_ANMVP_H

#include "common.h"

typedef struct { // 0x50
    /* 0x00 */ qword foga;
    /* 0x10 */ qword fogb;
    /* 0x20 */ qword max;
    /* 0x30 */ qword min;
    /* 0x40 */ qword spot;
} ATR_LIGHTP;

typedef struct { // 0x90
    /* 0x00 */ qword dmatag;
    /* 0x10 */ qword vif0;
    /* 0x20 */ qword tag;
    /* 0x30 */ ATR_LIGHTP light0;
    /* 0x80 */ qword mscal;
} ATR_AVPSINT0;

typedef struct { // 0xe0
    /* 0x00 */ qword dmatag;
    /* 0x10 */ qword vif0;
    /* 0x20 */ qword tag;
    /* 0x30 */ ATR_LIGHTP light0;
    /* 0x80 */ ATR_LIGHTP light1;
    /* 0xd0 */ qword mscal;
} ATR_AVPSINT2;

typedef struct { // 0x20
    /* 0x00 */ qword dmatag;
    /* 0x10 */ qword mscal;
} ATR_AVPSINT2Z;


extern s32 (*hrAnmVpmTbl[])(HRANMV *, s32);
extern HRANMV hravbuf[1];
extern s32 hravcnt;
extern s32 hrmapoff;
extern HRAVL hrvlight[2];

extern u32 hr_float2int(f32 f);
extern void hr_anmVPM_allinit();
extern void hr_anmVPM_set(HRANMVS *avs);
extern void hr_set_anmVPMtbl(HRANMVS *avs);
extern void hr_anmVPM_work();
extern void hr_set_vlight(HRAVL *vlight, f32 x, f32 y, f32 z, f32 r, f32 g, f32 b, f32 n, f32 f);
extern void hr_set_vlightMini(HRAVL *vlight, f32 r, f32 g, f32 b);

#endif

