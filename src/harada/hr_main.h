#ifndef __HR_MAIN_H
#define __HR_MAIN_H

#include "common.h"

typedef struct { // 0x4
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 b;
    /* 0x2 */ u8 g;
    /* 0x3 */ u8 a;
} CVECTOR;

// TODO: maybe move this?
typedef struct { // 0x30
#ifndef KL2_VER_TRIAL
    /* 0x00 */ s32 ids;
    /* 0x04 */ s32 idv;
    /* 0x08 */ s16 map_spds;
    /* 0x0a */ s16 map_spdt;
    /* 0x0c */ s16 bg_spds;
    /* 0x0e */ s16 bg_spdt;
#endif
	/* 0x10 */ qword fog_col;
	/* 0x20 */ s32 fog_near;
	/* 0x24 */ s32 fog_far;
	/* 0x28 */ CVECTOR bgt;
	/* 0x2c */ CVECTOR bgu;
} MAPVWORK;

typedef struct { // 0x10
    /* 0x0 */ f32 s;
    /* 0x4 */ f32 spds;
    /* 0x8 */ f32 t;
    /* 0xc */ f32 spdt;
} HRSCRST;

typedef struct { // 0x10
    /* 0x00 */ u32 ntag;
    /* 0x04 */ qword *dmatag;
    /* 0x08 */ u32 *data_top;
    /* 0x0c */ u32 pad0;
} VPOINFO;

typedef struct { // 0x1c
    /* 0x00 */ f32 xs;
    /* 0x04 */ f32 ys;
    /* 0x08 */ f32 zs;
    /* 0x0c */ u16 gcntx;
    /* 0x0e */ u16 gcnty;
    /* 0x10 */ u16 gcntz;
    /* 0x12 */ u16 pad0;
    /* 0x14 */ u32 gsize;
    /* 0x18 */ u32 gsizey;
} HR_HPMK;

typedef struct { // 0x8
    /* 0x0 */ u16 z;
    /* 0x2 */ u16 x;
    /* 0x4 */ u32 addr;
} HR_HPXZ;

typedef struct { // 0x4
    /* 0x0 */ u16 y;
    /* 0x2 */ u16 cnt;
} HR_HPYL;

#endif