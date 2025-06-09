#ifndef __KL2_COMMON_H
#define __KL2_COMMON_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include_asm.h"

#include <libdma.h>
#include <libvu0.h>
#include <libgraph.h>
#include <sifdev.h>

#ifndef __KL2_TYPES
#define __KL2_TYPES

typedef unsigned char u8;
typedef volatile u8 vu8;
typedef signed char s8;
typedef volatile s8 vs8;

typedef unsigned short u16;
typedef volatile u16 vu16;
typedef signed short s16;
typedef volatile s16 vs16;

typedef unsigned int u32;
typedef volatile u32 vu32;
typedef signed int s32;
typedef volatile s32 vs32;

typedef unsigned long long u64;
typedef volatile u64 vu64;
typedef signed long long s64;
typedef volatile s64 vs64;

typedef float f32;
typedef volatile float vf32;
typedef double f64;

#ifdef KL2_128_STUB
typedef unsigned int u128[4];
typedef volatile u128 vu128;
typedef signed int s128[4];
typedef volatile s128 vs128;
#else
typedef unsigned int u128 __attribute__((mode(TI)));
typedef volatile u128 vu128 __attribute__((mode(TI)));
typedef signed int s128 __attribute__((mode(TI)));
typedef volatile s128 vs128 __attribute__((mode(TI)));
#endif

#define PAD_TRG_UP(kpd) (kpd.trg & 0x1000)
#define PAD_TRG_DOWN(kpd) (kpd.trg & 0x4000)
#define PAD_TRG_LEFT(kpd) (kpd.trg & 0x8000)
#define PAD_TRG_RIGHT(kpd) (kpd.trg & 0x2000)
#define PAD_TRG_TRIANG(kpd) (kpd.trg & 0x10)
#define PAD_TRG_CROSS(kpd) (kpd.trg & 0x40)
#define PAD_TRG_SQUARE(kpd) (kpd.trg & 0x80)
#define PAD_TRG_CIRCLE(kpd) (kpd.trg & 0x20)
#define PAD_TRG_L1(kpd) (kpd.trg & 0x4)
#define PAD_TRG_L2(kpd) (kpd.trg & 0x1)
#define PAD_TRG_R1(kpd) (kpd.trg & 0x8)
#define PAD_TRG_R2(kpd) (kpd.trg & 0x2)
#define PAD_TRG_START(kpd) (kpd.trg & 0x800)
#define PAD_TRG_SELECT(kpd) (kpd.trg & 0x100)

#define PAD_REP_UP(kpd) (kpd.rep & 0x1000)
#define PAD_REP_DOWN(kpd) (kpd.rep & 0x4000)
#define PAD_REP_LEFT(kpd) (kpd.rep & 0x8000)
#define PAD_REP_RIGHT(kpd) (kpd.rep & 0x2000)

#define PAD_LVL_UP(kpd) (kpd.lvl & 0x1000)
#define PAD_LVL_DOWN(kpd) (kpd.lvl & 0x4000)
#define PAD_LVL_LEFT(kpd) (kpd.lvl & 0x8000)
#define PAD_LVL_RIGHT(kpd) (kpd.lvl & 0x2000)
#define PAD_LVL_TRIANG(kpd) (kpd.lvl & 0x10)
#define PAD_LVL_CROSS(kpd) (kpd.lvl & 0x40)
#define PAD_LVL_SQUARE(kpd) (kpd.lvl & 0x80)
#define PAD_LVL_CIRCLE(kpd) (kpd.lvl & 0x20)
#define PAD_LVL_L1(kpd) (kpd.lvl & 0x4)
#define PAD_LVL_L2(kpd) (kpd.lvl & 0x1)
#define PAD_LVL_R1(kpd) (kpd.lvl & 0x8)
#define PAD_LVL_R2(kpd) (kpd.lvl & 0x2)
#define PAD_LVL_START(kpd) (kpd.lvl & 0x800)
#define PAD_LVL_SELECT(kpd) (kpd.lvl & 0x100)

#define pPAD_TRG_UP(kpd) (kpd->trg & 0x1000)
#define pPAD_TRG_DOWN(kpd) (kpd->trg & 0x4000)
#define pPAD_TRG_LEFT(kpd) (kpd->trg & 0x8000)
#define pPAD_TRG_RIGHT(kpd) (kpd->trg & 0x2000)
#define pPAD_TRG_TRIANG(kpd) (kpd->trg & 0x10)
#define pPAD_TRG_CROSS(kpd) (kpd->trg & 0x40)
#define pPAD_TRG_SQUARE(kpd) (kpd->trg & 0x80)
#define pPAD_TRG_CIRCLE(kpd) (kpd->trg & 0x20)
#define pPAD_TRG_L1(kpd) (kpd->trg & 0x4)
#define pPAD_TRG_L2(kpd) (kpd->trg & 0x1)
#define pPAD_TRG_R1(kpd) (kpd->trg & 0x8)
#define pPAD_TRG_R2(kpd) (kpd->trg & 0x2)
#define pPAD_TRG_START(kpd) (kpd->trg & 0x800)
#define pPAD_TRG_SELECT(kpd) (kpd->trg & 0x100)

#define pPAD_REP_UP(kpd) (kpd->rep & 0x1000)
#define pPAD_REP_DOWN(kpd) (kpd->rep & 0x4000)
#define pPAD_REP_LEFT(kpd) (kpd->rep & 0x8000)
#define pPAD_REP_RIGHT(kpd) (kpd->rep & 0x2000)

#define pPAD_LVL_UP(kpd) (kpd->lvl & 0x1000)
#define pPAD_LVL_DOWN(kpd) (kpd->lvl & 0x4000)
#define pPAD_LVL_LEFT(kpd) (kpd->lvl & 0x8000)
#define pPAD_LVL_RIGHT(kpd) (kpd->lvl & 0x2000)
#define pPAD_LVL_TRIANG(kpd) (kpd->lvl & 0x10)
#define pPAD_LVL_CROSS(kpd) (kpd->lvl & 0x40)
#define pPAD_LVL_SQUARE(kpd) (kpd->lvl & 0x80)
#define pPAD_LVL_CIRCLE(kpd) (kpd->lvl & 0x20)
#define pPAD_LVL_L1(kpd) (kpd->lvl & 0x4)
#define pPAD_LVL_L2(kpd) (kpd->lvl & 0x1)
#define pPAD_LVL_R1(kpd) (kpd->lvl & 0x8)
#define pPAD_LVL_R2(kpd) (kpd->lvl & 0x2)
#define pPAD_LVL_START(kpd) (kpd->lvl & 0x800)
#define pPAD_LVL_SELECT(kpd) (kpd->lvl & 0x100)

#define SCR_WIDTH       640
#define SCR_HEIGHT      224 // Field scan
#define SCR_HEIGHT_PROG 240 // Progressive scan

#define GS_X_COORD(x) ((2048 - (SCR_WIDTH  / 2) + x) << 4)
#define GS_Y_COORD(y) ((2048 - (SCR_HEIGHT / 2) + y) << 4)

#define SETVEC(vec, x, y, z, w) (vec[0] = x, vec[1] = y, vec[2] = z, vec[3] = w)
#define SETVEC_XYZ(vec, x, y, z) (vec[0] = x, vec[1] = y, vec[2] = z)
#define SETVEC_XY(vec, x, y) (vec[0] = x, vec[1] = y)
#define SPR_MEM ((void *)0x70000000)
#define SPR_MEM_IDX(i) ((void *)(0x70000000 + (i) * 0x10))
#define SPR_SRC(x) ((void *)((u32)x | 0x80000000))
#define SPR_SEND SPR_SRC(SPR_MEM)
#define UNCACHED(p) ((void *)((u32)p | 0x20000000))

#define ARR_COUNT(arr) (sizeof(arr) / sizeof(arr[0]))
#define ARR_COUNT_SIGNED(arr) ((s32)ARR_COUNT(arr))

#define KL2_VISION(vision, area) (vision << 8 | area)
#define KL2_VAG(splt, prog, bank, grp, unk, flag, bendh, bendl) ((u64)(splt) | (u64)(prog) << 8 | (u64)(bank) << 15 | (u64)(grp) << 16 | (u64)(unk) << 20 | (u64)(flag) << 24 | (u64)(bendh) << 32 | (u64)(bendl) << 44)

#define KL2_PI  (3.141592f)
#define KL2_2PI (2.0f * KL2_PI)
#define KL2_3PI (3.0f * KL2_PI)
#define KL2_PI2 (KL2_PI / 2.0f)
#define KL2_PI3 (KL2_PI / 3.0f)

#define KL2_PI_CLAMP(f) ({if (f < -KL2_PI) { f += KL2_2PI; } else if (f > KL2_PI) { f -= KL2_2PI; }})

#ifdef KL2_DEBUG
#define KL2_DEBUG_PRINT(args) printf args
#else
#define KL2_DEBUG_PRINT(args) ((void *)0)
#endif

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} FVECTOR;

typedef struct {
    FVECTOR m[4];
} FMATRIX;

typedef struct {
    s32	x;
    s32	y;
    s32	z;
    s32	w;
} IVECTOR;

typedef struct {
    s16	x;
    s16	y;
    s16	z;
    s16	w;
} SVECTOR;

typedef union { // 0x10
    u128 u_u128;
    u64  u_u64[2];
    s64  u_s64[2];
    u32  u_u32[4];
    s32  u_s32[4];
    u16  u_u16[8];
    s16  u_s16[8];
    u8   u_u8[16];
    s8   u_s8[16];
    f32  u_f32[4];
} qword_uni;

typedef union { // 0x8
    u64 u_u64;
    u32 u_u32[2];
    u16 u_u16[4];
    s64 u_s64;
    s32 u_s32[2];
    s16 u_s16[4];
    f32 u_f32[2];
} long_uni;

typedef struct {
    SVECTOR vec;
    IVECTOR posi;
    u16 co;
    u16 DUMMY;
} ROUTE;

typedef struct {
    s32 cnt;
    ROUTE *rtp;
    s16 plc;
    s16 rtn;
    s32 mcn;
} RT_WRK;

typedef struct {
    sceVu0FVECTOR posi;
    sceVu0FVECTOR ang;
    f32 scr_z;
    s32 mode;
} CAM_WORK;

typedef struct {
    u32 cnt;
    u32 status;
    u32 lvl;
    u8 r3h;
    u8 r3v;
    u8 l3h;
    u8 l3v;
    u32 lvl2;
    u16 trg;
    u16 trgbuf;
    u16 rep;
    u16 reptimer;
    u32 looks;
} kPadDATA;

typedef struct {
    s32 outtime;
    s32 intime;
    s32 next_vision;
    s32 rtn;
    s32 mcn;
    s32 imuki;
    s32 omuki;
    u16 flag;
    s16 fdata;
} nkWIPE_WRK;

typedef struct OBJWORK {
    void (*pers)(struct OBJWORK *); // 0x00
    void (*draw)(struct OBJWORK *); // 0x04
    void (*drmir)(struct OBJWORK *); // 0x08
#ifndef KL2_VER_TRIAL
    void (*drmiref)(struct OBJWORK *); // 0x0C
#endif
    void (*dreff)(struct OBJWORK *); // 0x10
    void *prim; // 0x14
    void *work; // 0x18
    s16 stat0; // 0x1C
    s16 stat1; // 0x1E
    s16 prty; // 0x20
    s16 hitram; // 0x22
    s16 bun0; // 0x24
    s16 bun1; // 0x26
    s16 pad0; // 0x28
    s16 pad1; // 0x2A
    s16 live; // 0x2C
    s16 stat; // 0x2E
    sceVu0FVECTOR posi; // 0x30
    sceVu0FVECTOR spd; // 0x40
    sceVu0FVECTOR muki; // 0x50
    sceVu0FVECTOR ang; // 0x60
    sceVu0FVECTOR rot; // 0x70
    RT_WRK rtw; // 0x80
    s32 reg0; // 0x90
    s32 reg1; // 0x94
    s32 reg2; // 0x98
    s32 reg3; // 0x9C
    s32 reg4; // 0xA0
    s32 reg5; // 0xA4
    s32 reg6; // 0xA8
    s32 reg7; // 0xAC
    f32 freg0; // 0xB0
    f32 freg1; // 0xB4
    f32 freg2; // 0xB8
    f32 freg3; // 0xBC
    f32 freg4; // 0xC0
    f32 freg5; // 0xC4
    f32 freg6; // 0xC8
    f32 freg7; // 0xCC
    s64 htblid; // 0xD0
    s64 dummy; // 0xD8
    s16 option; // 0xE0
    s16 sflag; // 0xE2
    u32 *hpo; // 0xE4
    u32 *gimmick; // 0xE8
    s32 *_hOp; // 0xEC
} OBJWORK;

typedef struct {
    /* 0x000 */ RT_WRK rtw;
    /* 0x010 */ void (*Main)(/* ??? */);
    /* 0x014 */ s32 miexspd;
    /* 0x018 */ s32 tumspd;
    /* 0x01c */ s32 gimspd;
    /* 0x020 */ u32 bun_buf;
    /* 0x024 */ u32 Muki;
    /* 0x028 */ u32 buki_muki;
    /* 0x02c */ u32 timer;
    /* 0x030 */ u32 timer2;
    /* 0x034 */ s32 yarare_bun;
    /* 0x038 */ s32 tenmetu;
    /* 0x03c */ u32 Muki_buf;
    /* 0x040 */ u32 door_muki;
    /* 0x044 */ s32 total_rakka_time;
    /* 0x048 */ s32 count;
    /* 0x04c */ s32 muki2;
    /* 0x050 */ s32 michinori;
    /* 0x054 */ s32 michispd;
    /* 0x058 */ s32 mispd_buf;
    /* 0x05c */ s32 mispd;
    /* 0x060 */ s32 spflag;
    /* 0x064 */ s32 spflag2;
    /* 0x068 */ s32 da_muteki;
    /* 0x06c */ s32 noyukatime;
    /* 0x070 */ OBJWORK* mochifuku;
    /* 0x074 */ s32 jmp_cnt;
    /* 0x078 */ f32 saka;
    /* 0x07c */ f32 yarare_yposi;
    /* 0x080 */ u32 f_phcode;
    /* 0x084 */ s32 lvl;
    /* 0x088 */ s32 trg;
    /* 0x08c */ s32 ex_lvl;
    /* 0x090 */ s32 ex_trg;
    /* 0x094 */ f32 sjump_flag;
    /* 0x098 */ f32 sjump_yspd;
    /* 0x09c */ f32 tenjo_hosei;
    /* 0x0a0 */ s32 retflag;
    /* 0x0a4 */ s32 left_move;
    /* 0x0a8 */ s32 right_move;
    /* 0x0ac */ s32 up_move;
    /* 0x0b0 */ s32 down_move;
    /* 0x0b4 */ u32 gimm_flag;
    /* 0x0b8 */ OBJWORK *norigimm;
    /* 0x0bc */ OBJWORK *movebox;
    /* 0x0c0 */ s32 yuka_hit;
    /* 0x0c4 */ s32 yuka_hit_buf;
    /* 0x0c8 */ s32 ottoto;
    /* 0x0cc */ s32 rakka_flag;
    /* 0x0d0 */ s32 wahoo_cnt;
    /* 0x0d4 */ s32 wahoo_timer;
    /* 0x0d8 */ OBJWORK *okuyuka;
    /* 0x0dc */ s32 con;
    /* 0x0e0 */ s32 b_action;
    /* 0x0e4 */ s32 b_act_time;
    /* 0x0f0 */ sceVu0FVECTOR Scale;
    /* 0x100 */ s32 se_id;
    /* 0x104 */ s32 se_id2;
    /* 0x108 */ s32 se_id3;
    /* 0x10c */ s32 se_id4;
    /* 0x110 */ s32 se_id5;
    /* 0x114 */ s32 se_id6;
    /* 0x118 */ s32 se_id7;
    /* 0x11c */ s32 se_id8;
    /* 0x120 */ s32 se_id9;
    /* 0x124 */ s32 dai_se_cnt;
    /* 0x128 */ s32 yuka_hit_old;
    /* 0x12c */ s32 b_act_rflag;
    /* 0x130 */ f32 b_act_rot;
    /* 0x134 */ f32 motcnt;
    /* 0x138 */ f32 motcnt_end;
    /* 0x13c */ s32 motstop_flag;
    /* 0x140 */ s32 mot_actno;
    /* 0x144 */ s32 kasokuLvL;
    /* 0x148 */ f32 kasokuTime;
    /* 0x14c */ f32 kasokuMTime;
    /* 0x150 */ f32 center_time;
    /* 0x154 */ s32 rupu_cnt;
    /* 0x158 */ s32 dead_cnt;
    /* 0x15c */ s32 hima_cnt;
    /* 0x160 */ s32 taiho_bun;
    /* 0x164 */ s32 area_cnt;
    /* 0x168 */ s32 kage_flag;
    /* 0x16c */ f32 jumpspd_limit;
    /* 0x170 */ s32 rakka_cnt;
    /* 0x180 */ sceVu0FVECTOR slant;
} HERO_WORK;

typedef struct {
    /* 0x000 */ s32 mode;
    /* 0x004 */ s32 vision;
    /* 0x008 */ s32 flag;
    /* 0x00c */ u32 fr;
    /* 0x010 */ sceGsDBuffDc db;
    /* 0x340 */ s32 inter;
    /* 0x344 */ s32 pause_flag;
    /* 0x348 */ s32 non_pause_flag;
    /* 0x34c */ s32 pause_flag2;
    /* 0x350 */ s32 route_max;
    /* 0x354 */ s32 init_vision;
    /* 0x358 */ s32 st_rtn;
    /* 0x35c */ s32 st_mcn;
    /* 0x360 */ s32 st_muki;
    /* 0x364 */ f32 st_height;
    /* 0x368 */ s32 st_flag;
    /* 0x36c */ s32 st_klomode;
    /* 0x370 */ s32 Re_st_rtn;
    /* 0x374 */ s32 Re_st_mcn;
    /* 0x368 */ s32 Re_st_vision;
    /* 0x37c */ s32 Re_st_klomode;
    /* 0x380 */ s32 Re_st_muki;
    /* 0x384 */ f32 Re_st_height;
#ifndef KL2_VER_TRIAL
    /* 0x388 */ s32 Re_st_zanki_count;
#else
                u128 *print_buf;
#endif
    /* 0x38c */ OBJWORK *klonoa;
    /* 0x390 */ OBJWORK *kazd;
    /* 0x394 */ s32 *dataBuff;
    /* 0x398 */ s32 playdemo_time;
    /* 0x39c */ s32 playdemo_flag;
    /* 0x3a0 */ kPadDATA kpd[2];
    /* 0x3e0 */ nkWIPE_WRK wipe;
    /* 0x400 */ s32 kloLife[2];
    /* 0x408 */ s32 kloZanki[2];
    /* 0x410 */ f32 reverse_cnt;
#ifndef KL2_VER_TRIAL
    /* 0x414 */ s32 stage_flag;
#else
                s32 us_trial_timer;
#endif
    /* 0x418 */ s32 filter_type;
    /* 0x41c */ f32 filter_cnt;
    /* 0x420 */ s32 filter_prty;
    /* 0x424 */ s32 area_max;
#ifndef KL2_VER_TRIAL
    /* 0x428 */ f32 gus_timer;
    /* 0x42c */ f32 gus_cnt;
    /* 0x430 */ s32 popuka_flag;
    /* 0x434 */ s32 time_atack_cnt;
    /* 0x438 */ s32 k_atck_button;
    /* 0x43c */ s32 k_jump_button;
    /* 0x440 */ s32 vs_clear_cnt;
    /* 0x444 */ s32 time_atack_best;
    /* 0x448 */ f32 fcnt0;
    /* 0x44c */ f32 fcnt1;
    /* 0x450 */ f32 fcnt2;
    /* 0x454 */ s32 area_cnt;
    /* 0x458 */ f32 retry_posy;
    /* 0x45c */ s32 retry_bun1;
    /* 0x460 */ s32 retry_muki;
    /* 0x464 */ s32 tokurom_cnt;
#endif
    /* 0x470 */ sceVu0FMATRIX wsm;
    /* 0x4b0 */ sceVu0FMATRIX wvm;
    /* 0x4f0 */ sceVu0FMATRIX vsm;
    /* 0x530 */ sceVu0FMATRIX d_wsm;
    /* 0x570 */ sceVu0FMATRIX d_wvm;
    /* 0x5b0 */ sceVu0FMATRIX d_vsm;
    /* 0x5f0 */ CAM_WORK cam;
#ifndef KL2_VER_TRIAL
    /* 0x620 */ CAM_WORK d_cam;
#endif
} GAME_WORK;

typedef struct { // 0x50
    /* 0x00 */ u32 irqc;
    /* 0x04 */ u32 drawhc;
    /* 0x08 */ u32 proc_hcnt;
    /* 0x0c */ s32 cp;
    /* 0x10 */ u32 *cotf;
    /* 0x14 */ u32 *cot;
    /* 0x18 */ u32 *cotb;
    /* 0x1c */ u32 *cpkt;
    /* 0x20 */ u32 *sysbuf;
    /* 0x24 */ u32 *sysbufbase;
    /* 0x28 */ s32 nmode;
    /* 0x2c */ s32 nsmode;
    /* 0x30 */ s32 fmode;
    /* 0x34 */ s32 smode;
    /* 0x38 */ u32 modorg;
    /* 0x3c */ u32 modorgend;
    /* 0x40 */ OBJWORK *objwork;
    /* 0x44 */ s32 n_objw;
#ifndef KL2_VER_TRIAL
    /* 0x48 */ s32 Language;
    /* 0x4C */ s32 TVSystem;
#endif
} SYSGBL;

typedef struct { // 0x2050
    /* 0x0000 */ u32 block_list[2049];
    /* 0x2004 */ qword *block_head_ptr;
    /* 0x2008 */ u32 *clip_head_ptr;
    /* 0x200c */ u32 *vpm_data_top;
    /* 0x2010 */ u32 vpm_zone_num;
    /* 0x2014 */ u32 vpm_block_num;
    /* 0x2018 */ s32 course_level;
    /* 0x201c */ s32 fog_near;
    /* 0x2020 */ s32 fog_far;
    /* 0x2030 */ qword fog_col;
    /* 0x2040 */ s32 pixel_intpl;
    /* 0x2044 */ u8 *data_buff;
    /* 0x2048 */ u8 *hm_buff;
} vpmINFO;

typedef struct { // 0x240
	/* 0x000 */ u32 block_list[128];
	/* 0x200 */ u32 drawb_num;
	/* 0x204 */ qword *block_head_ptr;
	/* 0x208 */ u32 *clip_head_ptr;
	/* 0x20c */ u32 *vpm_data_top;
	/* 0x210 */ u32 vpm_zone_num;
	/* 0x214 */ u32 vpm_block_num;
	/* 0x218 */ s32 fog_near;
	/* 0x21c */ s32 fog_far;
	/* 0x220 */ qword fog_col;
	/* 0x230 */ s32 pixel_intpl;
	/* 0x234 */ u8 *data_buff;
} mINFO;

typedef struct HRANMV { // 0x40
    /* 0x00 */ sceVu0FVECTOR pos;
    /* 0x10 */ vpmINFO *info;
    /* 0x14 */ void (*prog)(struct HRANMV *);
    /* 0x18 */ u32 flag;
    /* 0x1c */ s32 drawno;
    /* 0x20 */ s32 work0;
    /* 0x24 */ s32 work1;
    /* 0x28 */ s32 work2;
    /* 0x2c */ s32 work3;
    /* 0x30 */ f32 fwk0;
    /* 0x34 */ f32 fwk1;
    /* 0x38 */ f32 fwk2;
    /* 0x3c */ f32 fwk3;
} HRANMV;

typedef struct { // 0x10
    /* 0x0 */ void (*prog)(HRANMV *);
    /* 0x4 */ void (*init)(HRANMV *);
    /* 0x8 */ s32 drawno;
    /* 0xc */ vpmINFO *info;
} HRANMVS;

typedef struct { // 0x30
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0c */ f32 r;
    /* 0x10 */ f32 g;
    /* 0x14 */ f32 b;
    /* 0x18 */ f32 n;
    /* 0x1c */ f32 f;
    /* 0x20 */ f32 ri;
    /* 0x24 */ f32 gi;
    /* 0x28 */ f32 bi;
    /* 0x2c */ f32 pad0;
} HRAVL;

typedef enum {
    HRAV_WAVE,
    HRAV_SINT,
    HRAV_SINT2,
    HRAV_SINTD,
    HRAV_SINT2D,
} HRAV;

typedef struct {
    s32 (**func)();
    s32 mod;
} FUNCTBL;

// From nakano/main.h
extern GAME_WORK GameGbl;
extern SYSGBL SysGbl;
extern sceDmaChan *DmaChVIF0;
extern sceDmaChan *DmaChVIF1;
extern sceDmaChan *DmaChGIF;
extern sceDmaChan *DmaChfromIPU;
extern sceDmaChan *DmaChtoIPU;
extern sceDmaChan *DmaChfromSPR;
extern sceDmaChan *DmaChtoSPR;

#endif // __KL2_TYPES

#endif // __KL2_COMMON_H