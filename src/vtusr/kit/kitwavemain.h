#ifndef __KIT_WAVEMAIN_H
#define __KIT_WAVEMAIN_H

#include "common.h"
#include "vtusr/vtutil.h"

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

extern kitWaveStruct* kitWaveInit(vtDataPtr *data);
extern u128* kitExecWave(u128 *tmp);

#endif