#ifndef __AO_VU1_PKT_H
#define __AO_VU1_PKT_H

#include "common.h"
#include "vtusr/vtutil.h"

typedef struct { // 0xb0
    /* 0x00 */ sceVu0FMATRIX view_clip;
    /* 0x40 */ sceVu0FMATRIX local_clip;
    /* 0x80 */ sceGsTex0 ao_tex0;
    /* 0x88 */ f32 ao_ptcl_size;
    /* 0x8c */ f32 growth[2];
    /* 0x94 */ f32 ao_tail;
    /* 0x98 */ s32 n_obj;
    /* 0x9c */ u32 start_obj;
    /* 0xa0 */ u32 mid;
    /* 0xa4 */ u32 far;
    /* 0xa8 */ u32 micro_prog_size;
} aoWaveStruct;

typedef struct { // 0xb0
    /* 0x00 */ sceVu0FVECTOR cmin;
    /* 0x10 */ sceVu0FVECTOR cmax;
    /* 0x20 */ sceVu0FVECTOR hmin;
    /* 0x30 */ sceVu0FVECTOR hmax;
    /* 0x40 */ sceVu0FVECTOR hami;
    /* 0x50 */ sceVu0FVECTOR zmax;
    /* 0x60 */ sceVu0FVECTOR zmin;
    /* 0x70 */ sceVu0FVECTOR xmax;
    /* 0x80 */ sceVu0FVECTOR xmin;
    /* 0x90 */ sceVu0FVECTOR ymax;
    /* 0xa0 */ sceVu0FVECTOR ymin;
} AoVPclip;

typedef struct { // 0x50
    /* 0x00 */ sceVu0FVECTOR pos;
    /* 0x10 */ sceVu0FVECTOR color;
    /* 0x20 */ f32 scale;
    /* 0x24 */ f32 width;
    /* 0x28 */ f32 height;
    /* 0x2c */ f32 size;
    /* 0x30 */ f32 time;
    /* 0x34 */ s32 dist;
    /* 0x38 */ s32 pre_height;
    /* 0x3c */ s32 fr;
    /* 0x40 */ s32 start_fr;
    /* 0x44 */ s32 end_fr;
    /* 0x48 */ u8 sw;
    /* 0x49 */ u8 n_ptcl;
    /* 0x4a */ u8 ptcl;
} AoParam;

typedef struct { // 0xc0
    /* 0x00 */ u8 total_ptcl;
    /* 0x01 */ u8 n_mid;
    /* 0x02 */ u8 n_far;
    /* 0x04 */ f32 cam_scr_z;
    /* 0x10 */ AoVPclip ao_cvpm;
} AoData;

extern u128* DrawParticle(u128 *buf, aoWaveStruct *s);
extern s32 SetParam(vtDataPtr *vtdata);

#endif