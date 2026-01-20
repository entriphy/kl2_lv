#ifndef __VT_FIRE_MAIN_H
#define __VT_FIRE_MAIN_H

#include "common.h"
#include <libipu.h>

// TODO: move?
typedef struct { // 0x88
	/* 0x00 */ s32 type;
	/* 0x04 */ u32 bsDataSize;
	/* 0x08 */ u16 width;
	/* 0x0a */ u16 height;
	/* 0x0c */ u32 nframes;
	/* 0x10 */ u32 frame_cnt;
	/* 0x14 */ u8 thVal0;
	/* 0x15 */ u8 thVal1;
	/* 0x16 */ s16 incnum;
	/* 0x18 */ u32 mbx;
	/* 0x1c */ u32 mby;
	/* 0x20 */ u32 texbp;
	/* 0x24 */ u32 texbw;
	/* 0x28 */ u32 tw;
	/* 0x2c */ u32 th;
	/* 0x30 */ u32 cbp;
	/* 0x34 */ u32 cpsm;
	/* 0x38 */ u32 csm;
	/* 0x3c */ u32 csa;
	/* 0x40 */ u32 cld;
	/* 0x44 */ u8 *gsClut;
	/* 0x48 */ u16 *ipuClut;
	/* 0x4c */ u16 killFg;
	/* 0x50 */ u32 *top;
	/* 0x54 */ u8 *bsData;
	/* 0x58 */ u32 bsData1Addr;
	/* 0x5c */ u32 bsData1Size;
	/* 0x60 */ u128 *bsTags;
	/* 0x64 */ u128 *dmaTags[2];
	/* 0x6c */ sceIpuRGB32 *cscBuff[2];
	/* 0x74 */ sceIpuRAW16 *idctBuff[2];
	/* 0x7c */ sceIpuINDX4 *vqBuff[2];
	/* 0x84 */ s32 currentBufNo;
} vtIDEC_MOVIE;

// TODO: move?
typedef struct { // 0x190
	/* 0x000 */ vtIDEC_MOVIE movie;
	/* 0x088 */ char name[256];
	/* 0x188 */ u32 vram_addr;
} taroMovieStruct;

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

typedef struct { // 0x1c
	/* 0x00 */ u32 vision;
	/* 0x04 */ u8 fire_flag;
	/* 0x05 */ u8 pause;
	/* 0x08 */ u32 fr;
	/* 0x0c */ u32 odev;
	/* 0x10 */ u32 count;
	/* 0x14 */ kitFireStruct *kitstruct;
	/* 0x18 */ taroMovieStruct *tarostruct;
} vtFireStruct;

typedef struct { // 0x70
	/* 0x00 */ u_int vision;
	/* 0x04 */ u_char wave_flag;
	/* 0x05 */ u_char movie_flag;
	/* 0x06 */ u_char splash_flag;
	/* 0x07 */ u_char pause;
	/* 0x08 */ u_int fr;
	/* 0x0c */ u_int odev;
	/* 0x10 */ u_int count;
	/* 0x20 */ sceVu0FVECTOR cam_posi;
	/* 0x30 */ sceVu0FVECTOR cam_rot;
	/* 0x40 */ kitWaveStruct *kitstruct;
	/* 0x44 */ taroMovieStruct *tarostruct[8];
	/* 0x64 */ aoWaveStruct *aostruct;
} vtWaveStruct;

#endif