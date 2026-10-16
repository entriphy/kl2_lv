#ifndef __KIT_FIREMAIN_H
#define __KIT_FIREMAIN_H

#include "common.h"

typedef struct { // 0x730
    /* 0x000 */ sceVu0FVECTOR center;
    /* 0x010 */ sceVu0FVECTOR center_v;
    /* 0x020 */ sceVu0FVECTOR bbox[8];
    /* 0x0a0 */ sceVu0FVECTOR start[40];
    /* 0x320 */ sceVu0FVECTOR p_vec[40];
    /* 0x5a0 */ sceVu0FVECTOR fire_size;
    /* 0x5b0 */ u32 life[40];
    /* 0x650 */ u32 life_max[40];
    /* 0x6f0 */ f32 lod_f;
    /* 0x6f4 */ u32 lod;
    /* 0x6f8 */ u32 particle_max;
    /* 0x6fc */ u8 turn[4][10];
} kitFireParam;

typedef struct { // 0x16bb0
    /* 0x00000 */ sceVu0FMATRIX world_view;
    /* 0x00040 */ sceVu0FMATRIX view_world;
    /* 0x00080 */ sceVu0FMATRIX world_screen;
    /* 0x000c0 */ sceVu0FMATRIX view_clip;
    /* 0x00100 */ sceVu0FMATRIX world_clip;
    /* 0x00140 */ sceVu0FVECTOR camera_pos;
    /* 0x00150 */ sceVu0FVECTOR camera_pos_v;
    /* 0x00160 */ sceVu0FVECTOR center_w2v;
    /* 0x00170 */ sceVu0FVECTOR center_v2w;
    /* 0x00180 */ sceVu0FVECTOR basevec_w2v[3];
    /* 0x001b0 */ sceVu0FVECTOR basevec_w2s[3];
    /* 0x001e0 */ sceVu0FVECTOR basevec_v2w[3];
    /* 0x00210 */ sceVu0FVECTOR basevec_v2w_p[2];
    /* 0x00230 */ kitFireParam param[50];
    /* 0x16990 */ f32 rand_table[128];
    /* 0x16b90 */ u64 tex0;
    /* 0x16b98 */ s32 f_num;
    /* 0x16b9c */ u8 base_alpha[5];
    /* 0x16ba1 */ u8 rand_num;
    /* 0x16ba2 */ u8 pause;
} kitFireStruct;

extern kitFireStruct *kitfirestructGBL;

extern kitFireStruct* kitInitFire();
extern void kitClearFire();
extern s32 kitSetFire(sceVu0FVECTOR vec, sceVu0FVECTOR size, f32 particle);
extern u128* kitExecFireMovieSend(u128 *packet);
extern u128* kitDrawFire(u128 *packet_in);
extern void kitSetPlate(kitFireParam *param, u8 *alpha, s32 num);
extern void kitSetPlateBase(kitFireParam *param, u8 *alpha, s32 num);
extern void kitSetParticle(kitFireParam *param, s32 num_base);
extern void kitSetParticleVelocity(kitFireParam *param, s32 num, s32 init);
extern void kitMakeRandtable();
extern void kitFireZSort(kitFireStruct *kitfirestruct, u8 *turn, s32 max);
extern void kitSetBaseVec(kitFireStruct *kitfirestruct);
extern void kitSetInversBaseVec(kitFireStruct *kitfirestruct);
extern void kitCalcInnerVal(kitFireParam *param, sceVu0FVECTOR inner);
extern void kitVu0ViewClipMatrix(sceVu0FMATRIX vc, f32 scrw, f32 scrh, f32 scrz, f32 zmin, f32 zmax);
extern s32 kitVu0ClipBBox(sceVu0FMATRIX lc, sceVu0FVECTOR *v);
extern u128* kitClutMovieDraw(u128 *tmp, u32 offx, u32 offy, u32 lx, u32 ly, s32 movieNo, u64 tex0, u64 tex_clut);
extern f32 kitVu0InnerProduct(sceVu0FVECTOR v0, sceVu0FVECTOR v1);

#endif