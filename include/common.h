#ifndef __KL2_COMMON_H
#define __KL2_COMMON_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include_asm.h"

#include <eekernel.h>
#include <eestruct.h>
#include <libdma.h>
#include <libvu0.h>
#include <libgraph.h>
#include <sifdev.h>
#include <libcdvd.h>

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

#define PAD_UP (0x1000)
#define PAD_DOWN (0x4000)
#define PAD_LEFT (0x8000)
#define PAD_RIGHT (0x2000)
#define PAD_TRIANG (0x10)
#define PAD_CROSS (0x40)
#define PAD_SQUARE (0x80)
#define PAD_CIRCLE (0x20)
#define PAD_L1 (0x4)
#define PAD_L2 (0x1)
#define PAD_R1 (0x8)
#define PAD_R2 (0x2)
#define PAD_START (0x800)
#define PAD_SELECT (0x100)

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
#define COPYVEC(v0, v1) (v0[0] = v1[0], v0[1] = v1[1], v0[2] = v1[2], v0[3] = v1[3])
#define SETDVEC(v0, x, y) (v0.vx = x, v0.vy = y)
#define COPYDVEC(v0, v1) (v0.vx = v1.vx, v0.vy = v1.vy)
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
#define KL2_3PI2 (3.0f * KL2_PI / 2.0f)
#define KL2_PI2 (KL2_PI / 2.0f)
#define KL2_PI3 (KL2_PI / 3.0f)
#define KL2_PI4 (KL2_PI / 4.0f)
#define KL2_PI180 (KL2_PI / 180.0f)

#define KL2_PI_CLAMP(f) ({if (f < -KL2_PI) { f += KL2_2PI; } else if (f > KL2_PI) { f -= KL2_2PI; }})
#define KL2_PI_CLAMP_W(f) ({while (f < -KL2_PI) { f += KL2_2PI; } while (f > KL2_PI) { f -= KL2_2PI; }})

#ifdef KL2_DEBUG
#define KL2_DEBUG_PRINT(args) printf args
#else
#define KL2_DEBUG_PRINT(args) ((void *)0)
#endif

#ifndef KL2_VER_TRIAL
#define KL2_VER_RETAIL
#endif

#ifdef KL2_VER_TRIAL
#define KL2_VER_COND(t, r) t
#define KL2_VER_TRIAL_ONLY(arg) arg
#define KL2_VER_RETAIL_ONLY(arg) ((void *)0)
#else
#define KL2_VER_COND(t, r) r
#define KL2_VER_TRIAL_ONLY(arg) ((void *)0)
#define KL2_VER_RETAIL_ONLY(arg) arg
#endif

#define KL2_FHM_ADDR(ptr, i) ((void *)((u32)ptr + ((u32 *)ptr)[i + 1]))

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

#endif // __KL2_TYPES

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
#ifdef KL2_VER_RETAIL
    /* 0x074 */ s32 jmp_cnt;
#endif
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
#ifdef KL2_VER_TRIAL
                s32 kage_flag;
	            f32 jumpspd_limit;
#endif
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
#ifdef KL2_VER_RETAIL
    /* 0x0d0 */ s32 wahoo_cnt;
    /* 0x0d4 */ s32 wahoo_timer;
#endif
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
#ifdef KL2_VER_RETAIL
    /* 0x120 */ s32 se_id9;
    /* 0x124 */ s32 dai_se_cnt;
    /* 0x128 */ s32 yuka_hit_old;
    /* 0x12c */ s32 b_act_rflag;
    /* 0x130 */ f32 b_act_rot;
    /* 0x134 */ f32 motcnt;
    /* 0x138 */ f32 motcnt_end;
    /* 0x13c */ s32 motstop_flag;
    /* 0x140 */ s32 mot_actno;
#else
                s32 dai_se_cnt;
                s32 jyouge;
	            f32 motcnt;
	            s32 b_act_rflag;
	            f32 b_act_rot;
#endif
    /* 0x144 */ s32 kasokuLvL;
    /* 0x148 */ f32 kasokuTime;
    /* 0x14c */ f32 kasokuMTime;
    /* 0x150 */ f32 center_time;
#ifdef KL2_VER_RETAIL
    /* 0x154 */ s32 rupu_cnt;
    /* 0x158 */ s32 dead_cnt;
    /* 0x15c */ s32 hima_cnt;
    /* 0x160 */ s32 taiho_bun;
    /* 0x164 */ s32 area_cnt;
    /* 0x168 */ s32 kage_flag;
    /* 0x16c */ f32 jumpspd_limit;
    /* 0x170 */ s32 rakka_cnt;
#endif
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

typedef struct { // 0x4
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 a;
} KZCOLOR;

typedef struct { // 0x4
    /* 0x0 */ s16 vx;
    /* 0x2 */ s16 vy;
} DVECTOR;

typedef struct { // 0x10
    /* 0x0 */ u64 tex0;
    /* 0x8 */ DVECTOR uv;
    /* 0xc */ DVECTOR wh;
} GIM_FORM;

typedef enum {
    GIM_PLTA01,
    GIM_PLTA02,
    GIM_PLTA03,
    GIM_PLTA04,
    GIM_PLTA05,
    GIM_PLTA06,
    GIM_PLTA07,
    GIM_PLTA08,
    GIM_PLTA09,
    GIM_PLTA10,
    GIM_PLTA11,
    GIM_PLTA12,
    GIM_PLTB01,
    GIM_PLTB02,
    GIM_PLTB03,
    GIM_PLTB04,
    GIM_PLTB05,
    GIM_PLTB06,
    GIM_PLTB07,
    GIM_PLTB08,
    GIM_PLTB09,
    GIM_PLTC01,
    GIM_PLTC02,
    GIM_PLTC03,
    GIM_PLTC04,
    GIM_PLTC05,
    GIM_PLTC06,
    GIM_PLTC07,
    GIM_PLTC08,
    GIM_PLTC09,
    GIM_PLTD01,
    GIM_PLTD02,
    GIM_PLTD03,
    GIM_PLTD04,
    GIM_PLTD05,
    GIM_PLTD06,
    GIM_PLTD07,
    GIM_PLTD08,
    GIM_PLTD09,
    GIM_PLTE01,
    GIM_PLTE02,
    GIM_PLTE03,
    GIM_PLTE04,
    GIM_PLTE05,
    GIM_PLTE06,
    GIM_PLTE07,
    GIM_PLTE08,
    GIM_PLTE09,
    GIM_PLTF01,
    GIM_PLTF02,
    GIM_PLTF03,
    GIM_PLTF04,
    GIM_PLTF05,
    GIM_PLTF06,
    GIM_PLTF07,
    GIM_PLTF08,
    GIM_PLTF09,
    GIM_SEL0000,
    GIM_SEL0001,
    GIM_SEL0002,
    GIM_SEL0003,
    GIM_SEL0005,
    GIM_SEL0006,
    GIM_SEL0007,
    GIM_SEL0008,
    GIM_SEL0010,
    GIM_SEL0016,
    GIM_SEL0019,
    GIM_SEL0020,
    GIM_SEL0100,
    GIM_SEL0101,
    GIM_SEL0102,
    GIM_SEL0103,
    GIM_SEL0104,
    GIM_SEL0105,
    GIM_SEL0106,
    GIM_SEL0107,
    GIM_SEL0111,
    GIM_SEL0112,
    GIM_SEL0113,
    GIM_SEL0114,
    GIM_SEL0115,
    GIM_SEL0400,
    GIM_SEL0401,
    GIM_HANE01,
    GIM_ZANKI,
    GIM_LOGO,
    GIM_PBYNAM,
    GIM_CHR_SLASH,
    GIM_MOM0007,
    GIM_MOM0008,
    GIM_MOM0009,
    GIM_MOM0010,
    GIM_KUMO1,
    GIM_KUMO2,
    GIM_NUM
} GIM;

typedef enum {
    STR_DUMMY,
    STR_COMMON_00,
    STR_COMMON_01,
    STR_TITLE_00,
    STR_TITLE_01,
    STR_OPTION_00,
    STR_OPTION_01,
    STR_OPTION_02,
    STR_OPTION_03,
    STR_OPTION_04,
    STR_OPTION_05,
    STR_OPTION_06,
    STR_OPTION_07,
    STR_MAP_00,
    STR_MAP_01,
    STR_MAP_02,
    STR_MAP_03,
    STR_PAUSE_00,
    STR_PAUSE_01,
    STR_OVER_00,
    STR_OVER_01,
    STR_ETC_09,
    STR_ETC_10,
    STR_ETC_11,
    STR_ETC_12,
    STR_ETC_28,
    STR_ETC_29,
    STR_ETC_13,
    STR_ETC_14,
    STR_ETC_15,
    STR_ETC_17,
    STR_ETC_33,
    STR_WINDOW_00,
    STR_WINDOW_01,
    STR_WINDOW_02,
    STR_WINDOW_03,
    STR_WINDOW_04,
    STR_WINDOW_05,
    STR_WINDOW_06,
    STR_WINDOW_07,
    STR_WINDOW_08,
    STR_WINDOW_09,
    STR_WINDOW_10,
    STR_WINDOW_11,
    STR_WINDOW_12,
    STR_WINDOW_13,
    STR_WINDOW_14,
    STR_WINDOW_15,
    STR_WINDOW_16,
    STR_WINDOW_17,
    STR_WINDOW_18,
    STR_WINDOW_19,
    STR_WINDOW_20,
    STR_WINDOW_21,
    STR_WINDOW_22,
    STR_WINDOW_23,
    STR_WINDOW_24,
    STR_WINDOW_25,
    STR_WINDOW_26,
    STR_WINDOW_27,
    STR_WINDOW_28,
    STR_WINDOW_29,
    STR_WINDOW_30,
    STR_WINDOW_31,
    STR_WINDOW_32,
    STR_WINDOW_33,
    STR_MOMMET_10,
    STR_MOMMET_11,
    STR_MOMMET_12,
    STR_MOMMET_00,
    STR_MOMMET_01,
    STR_MOMMET_02,
    STR_MOMMET_03,
    STR_MOMMET_04,
    STR_BOSS_00,
    STR_BOSS_01,
    STR_BOSS_02,
    STR_BOSS_03,
    STR_BOSS_04,
    STR_BOSS_05,
    STR_CHIMEI_00,
    STR_CHIMEI_01,
    STR_CHIMEI_02,
    STR_CHIMEI_03,
    STR_CHIMEI_04,
    STR_CHIMEI_05,
    STR_CHIMEI_06,
    STR_CHIMEI_07,
    STR_CHIMEI_08,
    STR_CHIMEI_09,
    STR_CHIMEI_10,
    STR_CHIMEI_11,
    STR_CHIMEI_12,
    STR_CHIMEI_13,
    STR_CHIMEI_14,
    STR_CHIMEI_15,
    STR_CHIMEI_16,
    STR_CHIMEI_17,
    STR_CHIMEI_18,
    STR_CHIMEI_19,
    STR_CHIMEI_20,
    STR_CHIMEI_21,
    STR_CHIMEI_22,
    STR_CHIMEI_23,
    STR_CHIMEI_24,
    STR_CHIMEI_25,
    STR_OVERLAP_00,
    STR_OVERLAP_10,
    STR_OVERLAP_01,
    STR_OVERLAP_11,
    STR_OVERLAP_05,
    STR_OVERLAP_06,
    STR_PUPPET_00,
    STR_PUPPET_01,
    STR_PUPPET_02,
    STR_PUPPET_03,
    STR_PUPPET_04,
    STR_PUPPET_05,
    STR_PUPPET_06,
    STR_PUPPET_07,
    STR_PUPPET_08,
    STR_PUPPET_09,
    STR_PUPPET_10,
    STR_PUPPET_11,
    STR_PUPPET_12,
    STR_PUPPET_13,
    STR_PUPPET_14,
    STR_PUPPET_15,
    STR_PUPPET_16,
    STR_PUPPET_17,
    STR_PUPPET_18,
    STR_PUPPET_19,
    STR_PUPPET_20,
    STR_PUPPET_21,
    STR_PUPPET_22,
    STR_PUPPET_23,
    STR_PUPPET_24,
    STR_PUPPET_25,
    STR_PUPPET_26,
    STR_PUPPET_27,
    STR_PUPPET_28,
    STR_PUPPET_29,
    STR_PUPPET_30,
    STR_PUPPET_31,
    STR_PUPPET_32,
    STR_PUPPET_33,
    STR_PUPPET_34,
    STR_PUPPET_35,
    STR_PUPPET_36,
    STR_PUPPET_37,
    STR_PUPPET_38,
    STR_PUPPET_39,
    STR_PUPPET_41,
    STR_PUPPET_42,
    STR_PUPPET_43,
    STR_PUPPET_44,
    STR_PUPPET_45,
    STR_PUPPET_46,
    STR_PUPPET_47,
    STR_PUPPET_48,
    STR_PUPPET_49,
    STR_PUPPET_51,
    STR_PUPPET_52,
    STR_PUPPET_53,
    STR_PUPPET_54,
    STR_PUPPET_55,
    STR_PUPPET_56,
    STR_PUPPET_57,
    STR_PUPPET_58,
    STR_PUPPET_59,
    STR_PUPPET_60,
    STR_PUPPET_61,
    STR_PUPPET_62,
    STR_PUPPET_63,
    STR_PUPPET_64,
    STR_PUPPET_65,
    STR_PUPPET_66,
    STR_SYSTEM_00,
    STR_FILE_00,
    STR_OPTION_08,
    STR_PAUSE_02,
    STR_KWORKS_00,
    STR_KWORKS_01,
    STR_MOMTOP_00,
    STR_MOMTOP_01,
    STR_MOMTOP_02,
    STR_MOMTOP_03,
    STR_ETC_01,
    STR_ETC_02,
    STR_ETC_03,
    STR_ETC_05,
    STR_ETC_06,
    STR_ETC_07,
    STR_ETC_08,
    STR_ETC_16,
    STR_ETC_21,
    STR_ETC_25,
    STR_ETC_26,
    STR_ETC_30,
    STR_ETC_31,
    STR_ETC_32,
    STR_ETC_34,
    STR_STAGE_00,
    STR_STAGE_01,
    STR_STAGE_02,
    STR_STAGE_03,
    STR_STAGE_04,
    STR_STAGE_05,
    STR_STAGE_06,
    STR_STAGE_07,
    STR_STAGE_08,
    STR_STAGE_09,
    STR_STAGE_10,
    STR_STAGE_11,
    STR_STAGE_12,
    STR_STAGE_13,
    STR_STAGE_14,
    STR_STAGE_15,
    STR_STAGE_16,
    STR_STAGE_17,
    STR_STAGE_18,
    STR_STAGE_19,
    STR_STAGE_20,
    STR_STAGE_21,
    STR_STAGE_22,
    STR_STAGE_23,
    STR_STAGE_24,
    STR_STAGE_25,
    STR_CLEAR_OPENING,
    STR_CLEAR_STG_01,
    STR_CLEAR_PPT_BG1,
    STR_CLEAR_STG_02,
    STR_CLEAR_BOSS_1,
    STR_CLEAR_PPT_BG2,
    STR_CLEAR_PPT_JOY,
    STR_CLEAR_STG_04,
    STR_CLEAR_STG_05,
    STR_CLEAR_BOSS_2,
    STR_CLEAR_PPT_BG3,
    STR_CLEAR_PPT_BOR,
    STR_CLEAR_STG_06,
    STR_CLEAR_STG_07,
    STR_CLEAR_BOSS_3,
    STR_CLEAR_STG_08,
    STR_CLEAR_PPT_BG4,
    STR_CLEAR_STG_09,
    STR_CLEAR_STG_10,
    STR_CLEAR_STG_11,
    STR_CLEAR_BOSS_4,
    STR_CLEAR_PPT_BG5,
    STR_CLEAR_STG_12,
    STR_CLEAR_STG_13,
    STR_CLEAR_STG_14,
    STR_CLEAR_BOSS_5,
    STR_CLEAR_STG_15,
    STR_CLEAR_STG_16,
    STR_CLEAR_STG_17,
    STR_CLEAR_BOSS_6,
    STR_CLEAR_ALL,
    STR_DATA_00,
    STR_DATA_01,
    STR_DATA_02,
    STR_DATA_03,
    STR_OPTION_09,
    STR_KWORKS_02,
    STR_BGM_00,
    STR_BGM_01,
    STR_BGM_02,
    STR_BGM_03,
    STR_BGM_04,
    STR_BGM_05,
    STR_BGM_06,
    STR_BGM_07,
    STR_BGM_08,
    STR_BGM_09,
    STR_BGM_10,
    STR_BGM_11,
    STR_BGM_12,
    STR_BGM_13,
    STR_BGM_14,
    STR_BGM_15,
    STR_BGM_16,
    STR_BGM_17,
    STR_BGM_18,
    STR_BGM_19,
    STR_BGM_20,
    STR_BGM_21,
    STR_BGM_22,
    STR_BGM_23,
    STR_BGM_24,
    STR_BGM_25,
    STR_BGM_26,
    STR_BGM_27,
    STR_BGM_28,
    STR_BGM_29,
    STR_BGM_30,
    STR_BGM_31,
    STR_BGM_32,
    STR_BGM_33,
    STR_BGM_34,
    STR_BGM_35,
    STR_BGM_36,
    STR_BGM_37,
    STR_BGM_38,
    STR_BGM_39,
    STR_BGM_40,
    STR_BGM_41,
    STR_BGM_42,
    STR_BGM_43,
    STR_BGM_44,
    STR_BGM_45,
    STR_BGM_46,
    STR_BGM_47,
    STR_BGM_48,
    STR_BGM_49,
    STR_BGM_50,
    STR_BGM_51,
    STR_BGM_52,
    STR_BGM_53,
    STR_BGM_54,
    STR_BGM_55,
    STR_BGM_56,
    STR_BGM_57,
    STR_GDM_00,
    STR_GDM_01,
    STR_DATA_04,
    STR_DATA_05,
    STR_DATA_06,
    STR_DATA_07,
    STR_NAME_F0,
    STR_NAME_F1,
    STR_NAME_F2,
    STR_NAME_F3,
    STR_NAME_F4,
    STR_NAME_P0,
    STR_NAME_P1,
    STR_NAME_P2,
} STR;

typedef enum {
    PTOPENING,
    PT0100_S2,
    PT0100_S0,
    PT0100_S1,
    PT0104_S0,
    PT0104_S1,
    PT4001_S0,
    PT0204_S0,
    PT0207_S0,
    PT2100_S0,
    PT2100_S1,
#ifdef KL2_VER_RETAIL
    PT2100_S2,
#endif
    PT4001_S1,
    PT4002_S0,
    PT0400_S1,
    PT0403_S0,
    PT040A_S0,
    PT040A_S1,
    PT040B_S0,
    PT040B_S1,
    PT040B_S2,
    PT0500_S0,
    PT0505_S2,
    PT0505_S0,
    PT0505_S1,
    PT4002_S1,
    PT4002_S2,
#ifdef KL2_VER_RETAIL
    PT2201_S0,
#endif
    PT4001_S2,
    PTXXXX_S0,
    PT0605_S0,
    PT0605_S1,
    PT0609_S0,
    PT0706_S0,
    PT20XX_S0,
    PT20XX_S1,
    PT08XX_S0,
#ifdef KL2_VER_RETAIL
    PT0805_S0,
#endif
    PT0706_S1,
    PT4001_S3,
    PT09XX_S0,
    PT09XX_S1,
#ifdef KL2_VER_RETAIL
    PT0908_S1,
#endif
    PT1000_S0,
    PT1004_S0,
    PT1100_S0,
    PT1111_S0,
    PT20XX_S2,
    PT20XX_S3,
    PT20XX_S4,
    PT4001_S4,
    PT1200_S0,
    PT1207_S0,
    PT1207_S1,
    PT1207_S2,
    PT1304_S0,
    PT1207_S3,
    PT13XX_S0,
    PT13XX_S1,
    PT13XX_S2,
    PT14XX_S0,
    PT14XX_S1,
    PT20XX_S5,
    PT20XX_S6,
    PT20XX_S7,
    PT1502_S0,
    PT1507_S0,
    PT1507_S1,
    PT1500_S0,
    PT1502_S2,
    PT1502_S1,
    PT16XX_S0,
    PT16XX_S1,
    PT17XX_S0,
    PT2XXX_S0,
#ifdef KL2_VER_RETAIL
    PT2701_S0,
#endif
    PT2XXX_S1,
    PT2XXX_S2,
    PT2XXX_S3,
    PTENDING,
    PTMOME_S0,
    PTMOME_S1,
    PTMOME_S2,
    PTMOME_S3,
    PTMOME_S4,
    PTMOME_S5,
    PTTITLE,
#ifdef KL2_VER_RETAIL
    PT0102_S0,
    PT1805_S0,
    PT1908_S0,
#endif
    PTSCENE_NUM
} PT;

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

#define DMArefe (0<<28)
#define DMAcnt  (1<<28)
#define DMAnext (2<<28)
#define DMAref  (3<<28)
#define DMArefs (4<<28)
#define DMAcall (5<<28)
#define DMAret  (6<<28)
#define DMAend  (7<<28)

#define SCE_GS_FALSE (0)
#define SCE_GS_TRUE  (1)
#define SCE_GS_ALPHA_NEVER		(0)
#define SCE_GS_ALPHA_ALWAYS		(1)
#define SCE_GS_ALPHA_LESS		(2)
#define SCE_GS_ALPHA_LEQUAL		(3)
#define SCE_GS_ALPHA_EQUAL		(4)
#define SCE_GS_ALPHA_GEQUAL		(5)
#define SCE_GS_ALPHA_GREATER	(6)
#define SCE_GS_ALPHA_NOTEQUAL	(7)
#define	SCE_GS_AFAIL_KEEP		(0)
#define	SCE_GS_AFAIL_FB_ONLY	(1)
#define SCE_GS_AFAIL_ZB_ONLY	(2)
#define SCE_GS_AFAIL_RGB_ONLY	(3)
#define SCE_GS_BLEND_RGB_SRC (0)
#define SCE_GS_BLEND_RGB_DST (1)
#define SCE_GS_BLEND_RGB_0   (2)
#define SCE_GS_BLEND_ALPHA_SRC (0)
#define SCE_GS_BLEND_ALPHA_DST (1)
#define SCE_GS_BLEND_ALPHA_FIX (2)
#define SCE_GS_REPEAT (0)
#define SCE_GS_CLAMP  (1)
#define SCE_GS_REGION_CLAMP  (2)
#define SCE_GS_REGION_REPEAT (3)

#endif // __KL2_COMMON_H