#ifndef __VT_FIRE_MAIN_H
#define __VT_FIRE_MAIN_H

#include "common.h"
#include <libipu.h>
#include "taro/taro_movie.h"
#include "taro/taromoviemain.h"

typedef struct { // 0x50
    /* 0x00 */ void *movie_data_buf[8];
    /* 0x20 */ void *wave_data_buf;
    /* 0x24 */ void *spray_data_buf;
    /* 0x28 */ sceGsTex0 tex0[4];
} vtDataPtr;

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

typedef struct { // 0x420
	/* 0x000 */ sceVu0FVECTOR camera_p;
	/* 0x010 */ sceVu0FVECTOR camera_zd;
	/* 0x020 */ sceVu0FVECTOR camera_yd;
	/* 0x030 */ sceVu0FVECTOR camera_rot;
	/* 0x040 */ sceVu0FVECTOR light0;
	/* 0x050 */ sceVu0FVECTOR light1;
	/* 0x060 */ sceVu0FVECTOR light2;
	/* 0x070 */ sceVu0FVECTOR light_rot;
	/* 0x080 */ sceVu0FVECTOR color0;
	/* 0x090 */ sceVu0FVECTOR color1;
	/* 0x0a0 */ sceVu0FVECTOR color2;
	/* 0x0b0 */ sceVu0FVECTOR ambient;
	/* 0x0c0 */ sceVu0FVECTOR obj_trans;
	/* 0x0d0 */ sceVu0FVECTOR obj_rot;
	/* 0x0e0 */ sceVu0FMATRIX local_world;
	/* 0x120 */ sceVu0FMATRIX world_view;
	/* 0x160 */ sceVu0FMATRIX view_screen;
	/* 0x1a0 */ sceVu0FMATRIX normal_light;
	/* 0x1e0 */ sceVu0FMATRIX local_color;
	/* 0x220 */ sceVu0FMATRIX local_screen;
	/* 0x260 */ sceVu0FMATRIX local_light;
	/* 0x2a0 */ sceVu0FMATRIX light_color;
	/* 0x2e0 */ sceVu0FMATRIX local_view;
	/* 0x320 */ sceVu0FMATRIX screen_local;
	/* 0x360 */ sceVu0FMATRIX view_world;
	/* 0x3a0 */ sceVu0FMATRIX world_local;
	/* 0x3e0 */ sceVu0FMATRIX view_local;
} kitWaveScreenEnv;

typedef struct { // 0x110
	/* 0x000 */ sceVu0FVECTOR trans;
	/* 0x010 */ sceVu0FVECTOR rot;
	/* 0x020 */ sceVu0FVECTOR light0;
	/* 0x030 */ sceVu0FVECTOR light1;
	/* 0x040 */ sceVu0FVECTOR light2;
	/* 0x050 */ sceVu0FVECTOR color0;
	/* 0x060 */ sceVu0FVECTOR color1;
	/* 0x070 */ sceVu0FVECTOR color2;
	/* 0x080 */ sceVu0FVECTOR ambient;
	/* 0x090 */ sceVu0FVECTOR fogcol;
	/* 0x0a0 */ u8 draw_enable;
	/* 0x0a1 */ u8 prim;
	/* 0x0a2 */ u8 lod;
	/* 0x0a3 */ u8 mmesh;
	/* 0x0a4 */ u8 basetex;
	/* 0x0a5 */ u8 fog;
	/* 0x0a6 */ u8 multitex;
	/* 0x0a7 */ u8 headtex;
	/* 0x0a8 */ u8 headtexval;
	/* 0x0a9 */ u8 heightajust;
	/* 0x0aa */ u8 basetexarea;
	/* 0x0ac */ f32 planesizex;
	/* 0x0b0 */ f32 planesizez;
	/* 0x0b4 */ f32 meshsizex;
	/* 0x0b8 */ f32 meshsizez;
	/* 0x0bc */ f32 height;
	/* 0x0c0 */ f32 intervalx;
	/* 0x0c4 */ f32 intervalz;
	/* 0x0c8 */ f32 radiusx;
	/* 0x0cc */ f32 radiusz;
	/* 0x0d0 */ f32 texajust;
	/* 0x0d4 */ f32 speedx;
	/* 0x0d8 */ f32 speedz;
	/* 0x0dc */ f32 shear;
	/* 0x0e0 */ f32 basetexspeedx;
	/* 0x0e4 */ f32 basetexspeedz;
	/* 0x0e8 */ f32 multitexspeedx;
	/* 0x0ec */ f32 multitexspeedz;
	/* 0x0f0 */ f32 random;
	/* 0x0f4 */ f32 ajust_h_far;
	/* 0x0f8 */ f32 ajust_h_near;
	/* 0x0fc */ f32 ajust_h_val;
	/* 0x100 */ f32 alphablend;
} kitWaveParam;

typedef struct { // 0x63c0
	/* 0x0000 */ kitWaveScreenEnv screenenv[20];
	/* 0x5280 */ kitWaveParam *param[20];
	/* 0x52d0 */ u128 table[256];
	/* 0x62d0 */ sceVu0FVECTOR cbase;
	/* 0x62e0 */ u32 x_mesh;
	/* 0x62e4 */ u32 z_mesh;
	/* 0x62e8 */ s32 tex_ajust_x;
	/* 0x62ec */ s32 tex_ajust_z;
	/* 0x62f0 */ f32 tex_scroll_x[20];
	/* 0x6340 */ f32 tex_scroll_z[20];
	/* 0x6390 */ u32 param_num;
	/* 0x6394 */ u32 current;
	/* 0x6398 */ u64 tex0[3];
	/* 0x63b0 */ f32 countx;
	/* 0x63b4 */ f32 countz;
	/* 0x63b8 */ f32 radiusx;
	/* 0x63bc */ f32 radiusz;
} kitWaveStruct;

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

typedef struct { // 0x70
	/* 0x00 */ u32 vision;
	/* 0x04 */ u8 wave_flag;
	/* 0x05 */ u8 movie_flag;
	/* 0x06 */ u8 splash_flag;
	/* 0x07 */ u8 pause;
	/* 0x08 */ u32 fr;
	/* 0x0c */ u32 odev;
	/* 0x10 */ u32 count;
	/* 0x20 */ sceVu0FVECTOR cam_posi;
	/* 0x30 */ sceVu0FVECTOR cam_rot;
	/* 0x40 */ kitWaveStruct *kitstruct;
	/* 0x44 */ taroMovieStruct *tarostruct[8];
	/* 0x64 */ aoWaveStruct *aostruct;
} vtWaveStruct;

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

extern void vtInitFire(s32 flag);
extern void vtExecFire();

#endif