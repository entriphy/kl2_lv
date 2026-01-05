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

typedef struct { // 0x24
    /* 0x00 */ u16 gx;
    /* 0x02 */ u16 gy;
    /* 0x04 */ u16 gz;
    /* 0x06 */ u16 pad0;
    /* 0x08 */ u32 xzcnt;
    /* 0x0c */ u32 addr;
    /* 0x10 */ u32 ylen;
    /* 0x14 */ u16 y;
    /* 0x16 */ u16 cnt;
    /* 0x18 */ u32 gouk;
    /* 0x1c */ u32 qwc;
    /* 0x20 */ u32 daddr;
} HR_HPDEB;

extern MAPVWORK mapvw;
extern HRSCRST hrmapst;
extern HRSCRST hrbgst;
extern u32 *hrd_pack;
extern u32 *hrg_pack;
extern u32 *hrf_pack;
extern u32 *hrse_pack;
extern s32 hr_abeoff;
extern s32 hr_objtype;
extern u32 *hr_mt_addr;
extern vpmINFO hr_mtexi;
extern s32 hr_resKeep;
extern s32 hr_resTmp;
extern s16 hr_resFg;
extern s16 hr_resSV;
extern u32 *hr_obcdata;
extern u32 *hr_obcvpf;
extern VPOINFO *hr_obcvpo;

extern void hr_cold_start();
extern void hr_hpmk_init(u32 *top);
extern u32* func_001028E0(u32 *top);
extern u32* hr_hpmk_blk(u16 gx, u16 gy, u16 gz, u32 *top);
extern u32* hr_hpmk(f32 x, f32 y, f32 z, u32 *top);
extern u32* hr_hpmk_deb(f32 x, f32 y, f32 z, u32 *top, HR_HPDEB *hpd);
extern void hr_stage_no(char *name, s32 fg);
extern s32 hr_check_dmy(qword *addr);
extern void hrPtSeLoad();
extern void hrStageDataLoad(s32 fg);
extern void hr_set_defMVC();
extern void func_00103E00(u32 *param_1);
extern void MapConfFileRead();
extern void hrDataLoad();
extern void hrAreaInit();
extern void hrAreaEnd();
extern void hrStageEnd();
extern void hr_set_vpmfog(vpmINFO *info);
extern s32* hr_get_draw2();
extern void hr_scrst_init(HRSCRST *st);
extern void hr_scrst_set(HRSCRST *st, s16 s, s16 t);
extern void hr_scrst_work(HRSCRST *st);
extern void hrInitWork();
extern void hrInitWorkDeb();
extern void hrMainWork();
extern void hrMainDraw();
extern void hr_retry_set();
extern void hr_restart_clear();
extern void hr_restart_Tmpclear();
extern void hr_restart_keep();
extern void hr_restart_set(s32 id);
extern s32 hr_restart_check(s32 id);

#endif