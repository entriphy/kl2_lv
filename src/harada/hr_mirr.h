#ifndef __HR_MIRR_H
#define __HR_MIRR_H

#include "common.h"
#include "harada/h_vpm2.h"

typedef struct {
    vpmINFO infoA;
    vpmINFO infoB;
    u32 *addrA;
    u32 *addrB;
    s32 flag;
    s32 pad0;
} V1100MIR;

typedef struct { // 0x14
    /* 0x00 */ u32 addr;
    /* 0x04 */ u32 count;
    /* 0x08 */ f32 rx;
    /* 0x0c */ f32 ry;
    /* 0x10 */ f32 len;
} K2M_HEADF;

typedef struct { // 0x10
    /* 0x0 */ u32 addr;
    /* 0x4 */ u32 count;
    /* 0x8 */ u32 poly;
    /* 0xc */ u32 addr2;
} K2M_HEADC;

typedef struct { // 0xc
    /* 0x0 */ f32 rx;
    /* 0x4 */ f32 ry;
    /* 0x8 */ f32 len;
} K2M_HC2;

typedef struct { // 0x24
    /* 0x00 */ sceVu0FVECTOR *norm;
    /* 0x04 */ sceVu0FVECTOR *center;
    /* 0x08 */ sceVu0FVECTOR *vert;
    /* 0x0c */ f32 rx;
    /* 0x10 */ f32 ry;
    /* 0x14 */ f32 cx;
    /* 0x18 */ f32 cy;
    /* 0x1c */ f32 clen;
    /* 0x20 */ u32 count;
} HFMIR;

typedef struct { // 0x2d0
    /* 0x000 */ sceVu0FVECTOR mpos;
#ifdef KL2_VER_RETAIL
    /* 0x010 */ sceVu0FVECTOR mang;
#endif
    /* 0x020 */ sceVu0FMATRIX wsm;
    /* 0x060 */ sceVu0FMATRIX wvm;
    /* 0x0a0 */ sceVu0FMATRIX vsm;
    /* 0x0e0 */ sceVu0FVECTOR smax;
    /* 0x0f0 */ sceVu0FVECTOR smin;
    /* 0x100 */ sceVu0FVECTOR vn;
    /* 0x110 */ sceVu0FVECTOR cent;
    /* 0x120 */ sceVu0FVECTOR dlt;
    /* 0x130 */ VPCLIP vc;
    /* 0x1e0 */ VPCLIP vco;
    /* 0x290 */ u64 xyofs;
    /* 0x298 */ f32 dx;
    /* 0x29c */ f32 dy;
    /* 0x2a0 */ u32 posmode;
    /* 0x2a4 */ void *mir;
    /* 0x2a8 */ u32 type;
    /* 0x2ac */ f32 rx;
    /* 0x2b0 */ f32 ry;
    /* 0x2b4 */ f32 scalex;
    /* 0x2b8 */ f32 scaley;
    /* 0x2bc */ s32 count;
    /* 0x2c0 */ f32 vsmSx;
    /* 0x2c4 */ f32 vsmSy;
    /* 0x2c8 */ s32 vsmFg;
    /* 0x2cc */ s32 flag;
} HFMIRC;

typedef struct { // 0x30
    /* 0x00 */ sceVu0FVECTOR *norm;
    /* 0x04 */ sceVu0FVECTOR *center;
    /* 0x08 */ sceVu0FVECTOR *vert;
    /* 0x0c */ s16 *dst;
    /* 0x10 */ K2M_HC2 *hc2;
    /* 0x14 */ f32 rx;
    /* 0x18 */ f32 ry;
    /* 0x1c */ f32 cx;
    /* 0x20 */ f32 cy;
    /* 0x24 */ u32 poly;
    /* 0x28 */ u32 count;
    /* 0x2c */ u32 men;
} HCMIR;

typedef struct { // 0x10
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
    /* 0x8 */ s32 z;
    /* 0xc */ s32 w;
} QWIV;

typedef struct { // 0x10
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
    /* 0xc */ f32 w;
} QWFV;

extern s32 hfmircnt;
extern s32 hcmircnt;
extern s32 hrmirflush;
extern s32 hroldflush;
extern HFMIR hfmirbuf[4];
extern HCMIR hcmirbuf[1];
extern HFMIRC hfmcam;
extern u8 *hfm_addr;
extern u8 *hcm_addr;
extern u32 hfm_size;
extern u32 hcm_size;
extern f32 *hfm_scale;
extern f32 *hcm_scale;
extern V1100MIR *hrm1100;

extern void hr_mir_set();
extern s32 hr_check_mir();
extern f32 hr_rot_pai(f32 r);
extern s32 hr_mir_cmpx(const void *t0, const void *t1);
extern s32 hr_mir_cmpy(const void *t0, const void *t1);
extern s32 hr_mir_cmpz(const void *t0, const void *t1);
extern s32 hr_mir_cmpxf(QWFV *v0, QWFV *v1);
extern s32 hr_mir_cmpyf(QWFV *v0, QWFV *v1);
extern s32 hr_mir_cmpzf(QWFV *v0, QWFV *v1);
extern u32 hr_mirsys_ver(u8 *addr);
extern f32* hr_fmirver1_scale(HFMIR *fmir);
extern f32* hr_cmirver1_scale(HCMIR *cmir);
extern void hr_make_dum(sceVu0FVECTOR *cent, s16 *dst, u32 men, sceVu0FVECTOR *v, u32 count, s32 d);
extern void hr_mir_work();
extern s32 func_0010DB60(s32 vision);
extern vpmINFO* func_0010DBC0();

#endif
