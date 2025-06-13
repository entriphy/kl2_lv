#ifndef __HR_PCAM_H
#define __HR_PCAM_H

#include "common.h"

typedef struct { // 0x50
    /* 0x00 */ sceVu0FVECTOR p;
    /* 0x10 */ sceVu0FVECTOR spd;
    /* 0x20 */ sceVu0FVECTOR acc;
    /* 0x30 */ sceVu0FVECTOR moku;
    /* 0x40 */ s32 flag;
    /* 0x44 */ s32 time;
    /* 0x48 */ s32 pad0;
    /* 0x4c */ s32 pad1;
} PCAMSC;

typedef struct { // 0x20
    /* 0x00 */ f32 p;
    /* 0x04 */ f32 spd;
    /* 0x08 */ f32 acc;
    /* 0x0c */ f32 moku;
    /* 0x10 */ s32 flag;
    /* 0x14 */ s32 time;
    /* 0x18 */ s32 pad0;
    /* 0x1c */ s32 pad1;
} PCAMSL;

typedef struct { // 0xd0
    /* 0x00 */ sceVu0FVECTOR v;
    /* 0x10 */ sceVu0FMATRIX hm;
    /* 0x50 */ sceVu0FVECTOR hv;
    /* 0x60 */ PCAMSC r;
    /* 0xb0 */ sceVu0FVECTOR rr;
    /* 0xc0 */ sceVu0FMATRIX *hdmk;
    /* 0xc4 */ sceVu0FVECTOR *hdv;
    /* 0xc8 */ s32 flag;
    /* 0xcc */ s32 pad0;
} PCAMSM;

typedef struct { // 0x310
    /* 0x000 */ PCAMSC wp;
    /* 0x050 */ PCAMSC wi;
    /* 0x0a0 */ PCAMSC wa;
    /* 0x0f0 */ sceVu0FVECTOR pos;
    /* 0x100 */ sceVu0FVECTOR ang;
    /* 0x110 */ sceVu0FVECTOR inte;
    /* 0x120 */ PCAMSM mp;
    /* 0x1f0 */ PCAMSM mi;
    /* 0x2c0 */ PCAMSL proj;
    /* 0x2e0 */ PCAMSL len;
    /* 0x300 */ s32 flag;
    /* 0x304 */ s32 bmax;
    /* 0x308 */ s32 bnow;
    /* 0x30c */ f32 *bptr;
} PCAMS;

typedef struct { // 0x20
    /* 0x00 */ s32 p;
    /* 0x04 */ s32 spd;
    /* 0x08 */ s32 acc;
    /* 0x0c */ s32 moku;
    /* 0x10 */ s32 flag;
    /* 0x14 */ s32 time;
    /* 0x18 */ u32 *addr;
    /* 0x1c */ s32 pad0;
} PCAMSR;

extern void hr_pcam_pr2inte(sceVu0FVECTOR pos, sceVu0FVECTOR ang, sceVu0FVECTOR inte, f32 len);
extern void hr_pcam_pi2rot(sceVu0FVECTOR pos, sceVu0FVECTOR inte, sceVu0FVECTOR ang);
extern void hr_pcam_cinit(PCAMSC *pcc);
extern void hr_pcam_ang_init();
extern void hr_pcam_set_pos(f32 x, f32 y, f32 z);
extern void hr_pcam_set_inte(f32 x, f32 y, f32 z);
extern void hr_pcam_init(sceVu0FVECTOR pos, sceVu0FVECTOR ang, f32 proj);
extern void hr_pcam_mhold(PCAMSC *pcc, PCAMSM *pcm, sceVu0FMATRIX *m, s32 fg);
extern void hr_pcam_vhold(PCAMSC *pcc, PCAMSM *pcm, sceVu0FVECTOR *v, s32 fg);
extern void hr_setEnvelopeMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1, sceVu0FMATRIX m2[4], sceVu0FMATRIX m3);
extern void hr_Envelope1vert(sceVu0FVECTOR *v, sceVu0FVECTOR *w, sceVu0FVECTOR *vo);
extern void hr_pcam_spdacc(PCAMSC *pcc);
extern void hr_pcam_spdclr(PCAMSC *pcc);
extern void hr_pcam_set_mode(s32 mode);
extern void hr_pcam_set_beta(s32 *addr);
extern void hr_pcam_ang2wa();
extern void hr_pcam_pi2len();
extern void hr_pcam_anglen();
extern void hr_pcam_set_ang(f32 x, f32 y, f32 z, s32 fg);
extern void hr_pcam_gyakusan(sceVu0FVECTOR *pi, PCAMSC *pcc, PCAMSM *pcm);
extern void hr_pcam_calc();
extern s32 hr_pcam_tmv_end(s32 no);
extern void hr_pcam_pos_tmv(s32 id, f32 x, f32 y, f32 z, s32 time, u8 c0, u8 c1);
extern void hr_pcam_inte_tmv(s32 id, f32 x, f32 y, f32 z, s32 time, u8 c0, u8 c1);
extern void hr_pcam_ang_tmv(s32 id, f32 x, f32 y, f32 z, s32 time, u8 c0, u8 c1);
extern void hr_pcam_work_mae();
extern void hr_pcam_work();

#endif
