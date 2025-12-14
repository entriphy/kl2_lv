#ifndef __KZ_BIOS_H
#define __KZ_BIOS_H

#include "common.h"

typedef struct { // 0x10
    /* 0x0 */ u8 r0;
    /* 0x1 */ u8 g0;
    /* 0x2 */ u8 b0;
    /* 0x3 */ u8 a0;
    /* 0x4 */ f32 q0;
    /* 0x8 */ u16 x0;
    /* 0xa */ u16 y0;
    /* 0xc */ u32 z0;
} GS_GPOS;

typedef struct { // 0x60
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 pad;
    /* 0x30 */ u64 tag1;
    /* 0x38 */ u64 tag1_regs;
    /* 0x40 */ GS_GPOS p[2];
} GS_LINE;

typedef struct { // 0x60
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ u8 r0;
    /* 0x31 */ u8 g0;
    /* 0x32 */ u8 b0;
    /* 0x33 */ u8 a0;
    /* 0x34 */ f32 q0;
    /* 0x38 */ u16 u0;
    /* 0x3a */ u16 v0;
    /* 0x3c */ u32 pad0;
    /* 0x40 */ u16 x0;
    /* 0x42 */ u16 y0;
    /* 0x44 */ u32 z0;
    /* 0x48 */ u16 u1;
    /* 0x4a */ u16 v1;
    /* 0x4c */ u32 pad1;
    /* 0x50 */ u16 x1;
    /* 0x52 */ u16 y1;
    /* 0x54 */ u32 z1;
    /* 0x58 */ u64 pad;
} GS_SPRT_UV;

typedef struct { // 0x80
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ u8 r0;
    /* 0x31 */ u8 g0;
    /* 0x32 */ u8 b0;
    /* 0x33 */ u8 a0;
    /* 0x34 */ f32 q0;
    /* 0x38 */ u16 u0;
    /* 0x3a */ u16 v0;
    /* 0x3c */ u32 pad0;
    /* 0x40 */ u16 x0;
    /* 0x42 */ u16 y0;
    /* 0x44 */ u32 z0;
    /* 0x48 */ u16 u1;
    /* 0x4a */ u16 v1;
    /* 0x4c */ u32 pad1;
    /* 0x50 */ u16 x1;
    /* 0x52 */ u16 y1;
    /* 0x54 */ u32 z1;
    /* 0x58 */ u16 u2;
    /* 0x5a */ u16 v2;
    /* 0x5c */ u32 pad2;
    /* 0x60 */ u16 x2;
    /* 0x62 */ u16 y2;
    /* 0x64 */ u32 z2;
    /* 0x68 */ u16 u3;
    /* 0x6a */ u16 v3;
    /* 0x6c */ u32 pad3;
    /* 0x70 */ u16 x3;
    /* 0x72 */ u16 y3;
    /* 0x74 */ u32 z3;
    /* 0x78 */ u64 pad4;
} GS_POLY_FT4_UV;

typedef struct { // 0x50
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u8 r0;
    /* 0x29 */ u8 g0;
    /* 0x2a */ u8 b0;
    /* 0x2b */ u8 a0;
    /* 0x2c */ f32 q0;
    /* 0x30 */ u16 x0;
    /* 0x32 */ u16 y0;
    /* 0x34 */ u32 z0;
    /* 0x38 */ u16 x1;
    /* 0x3a */ u16 y1;
    /* 0x3c */ u32 z1;
    /* 0x40 */ u16 x2;
    /* 0x42 */ u16 y2;
    /* 0x44 */ u32 z2;
    /* 0x48 */ u16 x3;
    /* 0x4a */ u16 y3;
    /* 0x4c */ u32 z3;
} GS_POLY_F4;

typedef struct { // 0x70
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u8 r0;
    /* 0x29 */ u8 g0;
    /* 0x2a */ u8 b0;
    /* 0x2b */ u8 a0;
    /* 0x2c */ f32 q0;
    /* 0x30 */ u16 x0;
    /* 0x32 */ u16 y0;
    /* 0x34 */ u32 z0;
    /* 0x38 */ u8 r1;
    /* 0x39 */ u8 g1;
    /* 0x3a */ u8 b1;
    /* 0x3b */ u8 a1;
    /* 0x3c */ f32 q1;
    /* 0x40 */ u16 x1;
    /* 0x42 */ u16 y1;
    /* 0x44 */ u32 z1;
    /* 0x48 */ u8 r2;
    /* 0x49 */ u8 g2;
    /* 0x4a */ u8 b2;
    /* 0x4b */ u8 a2;
    /* 0x4c */ f32 q2;
    /* 0x50 */ u16 x2;
    /* 0x52 */ u16 y2;
    /* 0x54 */ u32 z2;
    /* 0x58 */ u8 r3;
    /* 0x59 */ u8 g3;
    /* 0x5a */ u8 b3;
    /* 0x5b */ u8 a3;
    /* 0x5c */ f32 q3;
    /* 0x60 */ u16 x3;
    /* 0x62 */ u16 y3;
    /* 0x64 */ u32 z3;
    /* 0x68 */ u64 pad;
} GS_POLY_G4;

typedef struct { // 0x90
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ u16 u0;
    /* 0x32 */ u16 v0;
    /* 0x34 */ u32 pad0;
    /* 0x38 */ u8 r0;
    /* 0x39 */ u8 g0;
    /* 0x3a */ u8 b0;
    /* 0x3b */ u8 a0;
    /* 0x3c */ f32 q0;
    /* 0x40 */ u16 x0;
    /* 0x42 */ u16 y0;
    /* 0x44 */ u32 z0;
    /* 0x48 */ u16 u1;
    /* 0x4a */ u16 v1;
    /* 0x4c */ u32 pad1;
    /* 0x50 */ u8 r1;
    /* 0x51 */ u8 g1;
    /* 0x52 */ u8 b1;
    /* 0x53 */ u8 a1;
    /* 0x54 */ f32 q1;
    /* 0x58 */ u16 x1;
    /* 0x5a */ u16 y1;
    /* 0x5c */ u32 z1;
    /* 0x60 */ u16 u2;
    /* 0x62 */ u16 v2;
    /* 0x64 */ u32 pad2;
    /* 0x68 */ u8 r2;
    /* 0x69 */ u8 g2;
    /* 0x6a */ u8 b2;
    /* 0x6b */ u8 a2;
    /* 0x6c */ f32 q2;
    /* 0x70 */ u16 x2;
    /* 0x72 */ u16 y2;
    /* 0x74 */ u32 z2;
    /* 0x78 */ u16 u3;
    /* 0x7a */ u16 v3;
    /* 0x7c */ u32 pad3;
    /* 0x80 */ u8 r3;
    /* 0x81 */ u8 g3;
    /* 0x82 */ u8 b3;
    /* 0x83 */ u8 a3;
    /* 0x84 */ f32 q3;
    /* 0x88 */ u16 x3;
    /* 0x8a */ u16 y3;
    /* 0x8c */ u32 z3;
} GS_POLY_GT4_UV;

typedef struct { // 0x50
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u8 r0;
    /* 0x29 */ u8 g0;
    /* 0x2a */ u8 b0;
    /* 0x2b */ u8 a0;
    /* 0x2c */ f32 q0;
    /* 0x30 */ u16 x0;
    /* 0x32 */ u16 y0;
    /* 0x34 */ u32 z0;
    /* 0x38 */ u16 x1;
    /* 0x3a */ u16 y1;
    /* 0x3c */ u32 z1;
    /* 0x40 */ u16 x2;
    /* 0x42 */ u16 y2;
    /* 0x44 */ u32 z2;
    /* 0x48 */ u64 pad;
} GS_POLY_F3;

typedef struct { // 0x30
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 alpha;
    /* 0x28 */ u64 addr;
} GS_ALPHA;

typedef struct { // 0x30
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 clamp;
    /* 0x28 */ u64 addr;
} GS_CLAMP;

typedef struct { // 0x30
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 fba;
    /* 0x28 */ u64 addr;
} GS_FBA;

typedef struct { // 0x30
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 frame;
    /* 0x28 */ u64 addr;
} GS_FRAME;

typedef struct { // 0x30
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 pabe;
    /* 0x28 */ u64 addr;
} GS_PABE;

typedef struct { // 0x30
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 test;
    /* 0x28 */ u64 addr;
} GS_TEST;

typedef struct { // 0x30
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 tex1;
    /* 0x28 */ u64 addr;
} GS_TEX1;

typedef struct { // 0x30
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 texa;
    /* 0x28 */ u64 addr;
} GS_TEXA;

typedef struct { // 0x30
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 texflush;
    /* 0x28 */ u64 addr;
} GS_TEXFLUSH;

typedef struct { // 0x30
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 xyoffset;
    /* 0x28 */ u64 addr;
} GS_XYOFFSET;

typedef struct { // 0x30
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 zbuf;
    /* 0x28 */ u64 addr;
} GS_ZBUF;

// idk
typedef struct { // 0x80
    /* 0x00 */ u64 DMAtag;
    /* 0x08 */ u64 DMApad;
    /* 0x10 */ u64 GIFtag;
    /* 0x18 */ u64 GIFtag_regs;
    /* 0x20 */ u64 bitbltbuf;
    /* 0x28 */ u64 bitbltbuf_addr;
    /* 0x30 */ u64 trxpos;
    /* 0x38 */ u64 trxpos_addr;
    /* 0x40 */ u64 trxreg;
    /* 0x48 */ u64 trxreg_addr;
    /* 0x50 */ u64 trxdir;
    /* 0x58 */ u64 trxdir_addr;
    /* 0x60 */ u64 hwreg;
    /* 0x68 */ u64 hwreg_addr;
    /* 0x70 */ u64 texflush;
    /* 0x78 */ u64 texflush_addr;
} GS_DRAWPIXEL;

typedef struct { // 0x50
    /* 0x00 */ qword DMAtag;
    /* 0x10 */ qword VIFtag0;
    /* 0x20 */ sceVu0FVECTOR foga;
    /* 0x30 */ qword VIFtag1;
    /* 0x40 */ sceVu0FVECTOR fogb;
} KVM_FOGDIST;

typedef struct { // 0x40
    /* 0x00 */ qword DMAtag;
    /* 0x10 */ qword VIFtag;
    /* 0x20 */ qword GIFtag;
    /* 0x30 */ u64 fogcol;
    /* 0x38 */ u64 GSreg;
} KGS_FOGCOL;

enum STG_MODE {
#ifdef KL2_VER_TRIAL
    STG_MODE_GAME,
    STG_MODE_BOSS,
    STG_MODE_ETC,
    STG_MODE_NUM,
#else
    STG_MODE_GAME,
    STG_MODE_BOSS,
    STG_MODE_SROLL,
    STG_MODE_SELECT,
    STG_MODE_OTHER,
    STG_MODE_NUM,
#endif
};

typedef struct { // 0x1a
    /* 0x00 */ s16 name[10];
    /* 0x14 */ s8 pad;
    /* 0x15 */ s8 sound;
    /* 0x16 */ DVECTOR adjust;
} KZ_MC_INFO;

typedef enum {
    OBJECT_STD_KLONOA_WM,
    OBJECT_STD_KLONOA_VO,
    OBJECT_STD_MOMMET,
    OBJECT_STD_MMD_00,
    OBJECT_STD_MMD_01,
    OBJECT_STD_MMD_02,
    OBJECT_STD_MMD_03,
    OBJECT_STD_MMD_04,
    OBJECT_STD_MMD_05,
    OBJECT_STD_MMD_06,
    OBJECT_STD_MMD_07,
    OBJECT_STD_MMD_08,
    OBJECT_STD_MMD_09,
    OBJECT_STD_MMD_10,
    OBJECT_STD_MMD_11,
    OBJECT_STD_MMD_12,
    OBJECT_STD_MMD_13,
    OBJECT_STD_MMD_14,
    OBJECT_STD_MMD_15,
    OBJECT_STD_NUM,
} OBJECT_STD;

typedef enum {
	WM_JOB_NONE = -1,
	WM_JOB_IDLE,
	WM_JOB_MAIN,
	WM_JOB_MAIN_MAIN,
	WM_JOB_STATUS,
	WM_JOB_STATUS_MAIN,
	WM_JOB_MOMTOP,
	WM_JOB_MOMTOP_MAIN,
	WM_JOB_VISIONOVER,
	WM_JOB_VISIONOVER_MAIN,
	WM_JOB_NUM,
} WM_JOB;

// TODO: move
typedef enum {
    TD_JOB_NONE = -1,
    TD_JOB_IDLE,
    TD_JOB_1ST_MCCHECK,
    TD_JOB_1ST_MCCHECK_MAIN,
    TD_JOB_1ST_MCCHECK_END,
    TD_JOB_1ST_LOGO,
    TD_JOB_1ST_LOGO_MAIN,
    TD_JOB_1ST_LOGO_END,
    TD_JOB_PUP_WAIT,
    TD_JOB_PUP_WAIT_MAIN,
    TD_JOB_PUP_WAIT_END,
    TD_JOB_TTL_MENU,
    TD_JOB_TTL_MENU_MAIN,
    TD_JOB_TTL_MENU_END,
    TD_JOB_FIL_MAKESEL,
    TD_JOB_FIL_MAKESEL_MAIN,
    TD_JOB_FIL_MAKESEL_END,
    TD_JOB_FIL_MAKECONF,
    TD_JOB_FIL_MAKECONF_MAIN,
    TD_JOB_FIL_MAKECONF_END,
    TD_JOB_FIL_LOADFILESEL,
    TD_JOB_FIL_LOADFILESEL_MAIN,
    TD_JOB_FIL_LOADFILESEL_END,
    TD_JOB_FIL_LOADDATASEL,
    TD_JOB_FIL_LOADDATASEL_MAIN,
    TD_JOB_FIL_LOADDATASEL_END,
    TD_JOB_FIL_SAVEDATASEL,
    TD_JOB_FIL_SAVEDATASEL_MAIN,
    TD_JOB_FIL_SAVEDATASEL_END,
    TD_JOB_FIL_SAVECONF,
    TD_JOB_FIL_SAVECONF_MAIN,
    TD_JOB_FIL_SAVECONF_END,
    TD_JOB_NAM_ENTRY,
    TD_JOB_NAM_ENTRY_MAIN,
    TD_JOB_NAM_ENTRY_CONFIRM,
    TD_JOB_NAM_ENTRY_WARNING,
    TD_JOB_NAM_ENTRY_END,
    TD_JOB_OPT_TOP,
    TD_JOB_OPT_TOP_MAIN,
    TD_JOB_OPT_TOP_END,
    TD_JOB_OPT_PAD,
    TD_JOB_OPT_PAD_MAIN,
    TD_JOB_OPT_PAD_END,
    TD_JOB_OPT_SOUND,
    TD_JOB_OPT_SOUND_MAIN,
    TD_JOB_OPT_SOUND_END,
    TD_JOB_OPT_ADJUST,
    TD_JOB_OPT_ADJUST_MAIN,
    TD_JOB_OPT_ADJUST_END,
    TD_JOB_WMP_ENTER,
    TD_JOB_WMP_MAIN,
    TD_JOB_WMP_MAIN_MAIN,
    TD_JOB_WMP_MAIN_END,
    TD_JOB_WMP_STATUS,
    TD_JOB_WMP_STATUS_MAIN,
    TD_JOB_WMP_STATUS_END,
    TD_JOB_WMP_MENU,
    TD_JOB_WMP_MENU_MAIN,
    TD_JOB_WMP_MENU_END,
    TD_JOB_GAM_PAUSE,
    TD_JOB_GAM_PAUSE_MAIN,
    TD_JOB_GAM_PAUSE_END,
    TD_JOB_GAM_VISIONSTART,
    TD_JOB_GAM_VISIONSTART_MAIN,
    TD_JOB_GAM_VISIONSTART_END,
    TD_JOB_GAM_VISIONOVER,
    TD_JOB_GAM_VISIONOVER_MAIN,
    TD_JOB_GAM_VISIONOVER_END,
    TD_JOB_MOM_TOP,
    TD_JOB_MOM_TOP_MAIN,
    TD_JOB_MOM_TOP_END,
    TD_JOB_MOM_GENJU,
    TD_JOB_MOM_GENJU_MAIN,
    TD_JOB_MOM_GENJU_END,
    TD_JOB_MOM_PAUSE,
    TD_JOB_MOM_PAUSE_MAIN,
    TD_JOB_MOM_PAUSE_END,
    TD_JOB_MOM_PUPPETTOP,
    TD_JOB_MOM_PUPPETTOP_MAIN,
    TD_JOB_MOM_PUPPETTOP_END,
    TD_JOB_MOM_PUPPETGROUP,
    TD_JOB_MOM_PUPPETGROUP_MAIN,
    TD_JOB_MOM_PUPPETGROUP_END,
    TD_JOB_MOM_CONCERT,
    TD_JOB_MOM_CONCERT_MAIN,
    TD_JOB_MOM_CONCERT_END,
    TD_JOB_MOM_GALLERY,
    TD_JOB_MOM_GALLERY_MAIN,
    TD_JOB_MOM_GALLERY_END,
    TD_JOB_NUM,
} TD_JOB;

typedef enum {
    MOM_MODE_NORMAL,
    MOM_MODE_GENJU,
    MOM_MODE_THEATER,
    MOM_MODE_NUM
} MOM_MODE;

typedef enum {
    CLOUD_NONE,
    CLOUD_NORMAL,
    CLOUD_LIGHT,
    CLOUD_NUM
} CLOUD;

typedef enum {
    SELECT_WIN_YESNO,
    SELECT_TTL_MENU,
    SELECT_FIL_MAKESEL,
    SELECT_FIL_CONFIRM,
    SELECT_FIL_FILESEL,
    SELECT_FIL_DATASEL,
    SELECT_OPT_TOP,
    SELECT_OPT_PAD,
    SELECT_OPT_SOUND0,
    SELECT_OPT_SOUND1,
    SELECT_ETC_PADEXP0,
    SELECT_ETC_PADEXP1,
    SELECT_ETC_PADEXP2,
    SELECT_ETC_PADEXP3,
    SELECT_ETC_PADEXP4,
    SELECT_ETC_PADEXP5,
    SELECT_ETC_PADEXP6,
    SELECT_WMP_STATUS,
    SELECT_WMP_MENU,
    SELECT_GAM_PAUSE,
    SELECT_MOM_PAUSE,
    SELECT_GAM_VOVER,
    SELECT_MOM_TOP,
    SELECT_MOM_GENJU,
    SELECT_PUP_TOP,
    SELECT_PUP_GROUP00,
    SELECT_PUP_GROUP01,
    SELECT_PUP_GROUP02,
    SELECT_PUP_GROUP03,
    SELECT_PUP_GROUP04,
    SELECT_PUP_GROUP05,
    SELECT_PUP_GROUP06,
    SELECT_PUP_GROUP07,
    SELECT_PUP_GROUP08,
    SELECT_PUP_GROUP09,
    SELECT_PUP_GROUP10,
    SELECT_PUP_GROUP11,
    SELECT_PUP_GROUP12,
    SELECT_PUP_GROUP13,
    SELECT_PUP_GROUP14,
    SELECT_PUP_GROUP15,
    SELECT_PUP_GROUP16,
    SELECT_PUP_GROUP17,
    SELECT_PUP_GROUP18,
    SELECT_PUP_GROUP19,
    SELECT_PUP_GROUP20,
    SELECT_PUP_GROUP21,
    SELECT_PUP_GROUP22,
    SELECT_PUP_GROUP23,
    SELECT_PUP_GROUP24,
    SELECT_TRI_TTLMENU,
    SELECT_NUM
} SELECT;

typedef enum {
    SL_STATUS_IN,
    SL_STATUS_OUT,
    SL_STATUS_OUT_END,
    SL_STATUS_WAIT,
    SL_STATUS_NUM
} SL_STATUS;

typedef enum {
    FD_MODE_OUT = -1,
    FD_MODE_STOP,
    FD_MODE_IN,
    FD_MODE_NUM
} FD_MODE;

typedef enum {
    WINDOW_MEM_00,
    WINDOW_MEM_01,
    WINDOW_MEM_02,
    WINDOW_MEM_03,
    WINDOW_MEM_04,
    WINDOW_MEM_05,
    WINDOW_MEM_06,
    WINDOW_MEM_07,
    WINDOW_MEM_08,
    WINDOW_MEM_09,
    WINDOW_MEM_10,
    WINDOW_MEM_11,
    WINDOW_MEM_12,
    WINDOW_MEM_13,
    WINDOW_MEM_14,
    WINDOW_MEM_15,
    WINDOW_MEM_16,
    WINDOW_MEM_17,
    WINDOW_MEM_18,
    WINDOW_MEM_19,
    WINDOW_ETC_00,
    WINDOW_ETC_01,
    WINDOW_ETC_02,
    WINDOW_ETC_03,
    WINDOW_ETC_04,
    WINDOW_ETC_05,
    WINDOW_NUM
} WINDOW;

typedef enum {
    PF_SELTITLE_GMS,
    PF_SELLOGO_GMS,
    PF_KUMO1_GMS,
    PF_KUMO2_GMS
} PF;

typedef enum {
    FD_STATUS_IN_END,
    FD_STATUS_OUT_END,
    FD_STATUS_HALF,
    FD_STATUS_NUM
} FD_STATUS;

typedef enum {
    GROUND_WIN_STD,
    GROUND_OPT_SCREXPLAIN,
    GROUND_OPT_HELPINFO,
    GROUND_OPT_ADJUST,
    GROUND_NAM_ENTRY,
    GROUND_MOM_PLYDISP,
    GROUND_MOM_PLYCTRL,
    GROUND_WMP_PLACE,
    GROUND_MOM_MESSAGE,
    GROUND_NUM
} GROUND;

typedef enum {
    FONT_NS,
    FONT_NM,
    FONT_JS,
    FONT_JM,
    FONT_JN,
    FONT_JH,
    FONT_NUM
} FONT;

typedef enum {
    WN_STATUS_00,
    WN_STATUS_01,
    WN_STATUS_02,
    WN_STATUS_03,
    WN_STATUS_04,
    WN_STATUS_05,
    WN_STATUS_06,
    WN_STATUS_07,
    WN_STATUS_08,
    WN_STATUS_09,
    WN_STATUS_10,
    WN_STATUS_11,
    WN_STATUS_12,
    WN_STATUS_13,
    WN_STATUS_14,
    WN_STATUS_15,
    WN_STATUS_WAIT,
    WN_STATUS_NUM
} WN_STATUS;

typedef enum {
    FORM_LONG,
    FORM_PADEXP,
    FORM_NARROW,
    FORM_NARROW_EX,
    FORM_NARROWx2_EX,
    FORM_NORMAL,
    FORM_NARROWx2,
    FORM_VERYLONG,
    FORM_NUM
} FORM;

typedef enum {
    PL_STATUS_IN,
    PL_STATUS_IN_END,
    PL_STATUS_OUT,
    PL_STATUS_OUT_END,
    PL_STATUS_UP,
    PL_STATUS_UP_END,
    PL_STATUS_DOWN,
    PL_STATUS_DOWN_END,
    PL_STATUS_NUM
} PL_STATUS;

typedef enum {
    SEL_IS,
    SEL_ISNOT,
    ALL_ARE,
    ALL_ARENOT
} CHECK_MODE;

typedef struct { // 0x18
    /* 0x00 */ u8 disp_flag;
    /* 0x01 */ u8 sel_flag;
    /* 0x02 */ u8 pop_flag;
    /* 0x03 */ u8 status;
    /* 0x04 */ u8 form_no;
    /* 0x08 */ KZCOLOR *fcol;
    /* 0x0c */ void (*dp_func)(void *arg, s32 idx);
    /* 0x10 */ void (*dc_func)(void *arg, s32 idx);
    /* 0x14 */ void *dc_para;
} PLATE_INFO;

typedef struct { // 0x30
    /* 0x00 */ DVECTOR base;
    /* 0x04 */ DVECTOR mark_L;
    /* 0x08 */ DVECTOR mark_R;
    /* 0x0c */ s8 num_plate_all;
    /* 0x0d */ s8 num_plate_vert;
    /* 0x0e */ s8 num_plate_hori;
    /* 0x0f */ s8 num_row;
    /* 0x10 */ s8 idx_page;
    /* 0x11 */ s8 idx_plate;
    /* 0x12 */ s8 lst_page;
    /* 0x13 */ s8 lst_plate;
    /* 0x14 */ s16 io_count;
    /* 0x16 */ s16 pop_count;
    /* 0x18 */ s16 sway_count;
    /* 0x1a */ s16 mark_count;
    /* 0x1c */ s16 *line_offset;
    /* 0x20 */ s16 *row_offset;
    /* 0x24 */ s16 *delay;
    /* 0x28 */ PLATE_INFO **plates;
    /* 0x2c */ void (*dm_func)(void *arg);
} SELECT_INFO;

typedef struct { // 0xc
    /* 0x0 */ DVECTOR base;
    /* 0x4 */ DVECTOR wh;
    /* 0x8 */ GIM_FORM **parts;
} GROUND_INFO;

typedef struct { // 0x18
    /* 0x00 */ u8 status;
    /* 0x01 */ u8 send_flag;
    /* 0x02 */ s8 grnd_no;
    /* 0x04 */ DVECTOR str_offset;
    /* 0x08 */ s32 str_no;
    /* 0x0c */ KZCOLOR fcol;
    /* 0x10 */ DVECTOR sel_offset;
    /* 0x14 */ s32 sel_no;
} WINDOW_INFO;

typedef union { // 0x10
    /* 0x0 */ u128 ul128;
    /* 0x0 */ u64 ul64[2];
    /* 0x0 */ u32 ul32[4];
    /* 0x0 */ sceVu0IVECTOR vect;
} kzQWdata;

typedef struct { // 0xc
	/* 0x0 */ kzQWdata *buf;
	/* 0x4 */ u32 size;
	/* 0x8 */ u32 *pBase;
} kzGifPacket;

extern void kz_Set_Line(DVECTOR *sxy0, DVECTOR *sxy1, u32 sz, KZCOLOR *col);
extern void kz_Set_SprtUV(DVECTOR *sxy, u32 sz, DVECTOR *swh, DVECTOR *uv, KZCOLOR *col);
extern void kz_Set_SprtUV_Eff(DVECTOR *sxy, u32 sz, DVECTOR *swh, DVECTOR *uv, KZCOLOR *col);
extern void kz_Set_TileF4(DVECTOR *sxy, u32 sz, DVECTOR *swh, KZCOLOR *col);
extern void kz_Set_TileG4(DVECTOR *sxy, u32 sz, DVECTOR *swh, KZCOLOR *col0, KZCOLOR *col1, KZCOLOR *col2, KZCOLOR *col3);
extern void kz_Set_TileFT4UV(DVECTOR *sxy, u32 sz, DVECTOR *swh, DVECTOR *uv, DVECTOR *twh, KZCOLOR *col);
extern void kz_Set_TileGT4UV(DVECTOR *sxy, u32 sz, DVECTOR *swh, DVECTOR *uv, DVECTOR *twh, KZCOLOR *col0, KZCOLOR *col1, KZCOLOR *col2, KZCOLOR *col3);
extern void kz_Set_PolyF3(sceVu0IVECTOR *crd0, sceVu0IVECTOR *crd1, sceVu0IVECTOR *crd2, KZCOLOR *col);
extern void kz_Set_PolyF4(sceVu0IVECTOR *crd0, sceVu0IVECTOR *crd1, sceVu0IVECTOR *crd2, sceVu0IVECTOR *crd3, KZCOLOR *col);
extern void kz_Set_PolyG4(sceVu0IVECTOR *crd0, sceVu0IVECTOR *crd1, sceVu0IVECTOR *crd2, sceVu0IVECTOR *crd3, KZCOLOR *col0, KZCOLOR *col1, KZCOLOR *col2, KZCOLOR *col3);
extern void kz_Set_PolyFT4UV(sceVu0IVECTOR *crd0, sceVu0IVECTOR *crd1, sceVu0IVECTOR *crd2, sceVu0IVECTOR *crd3, DVECTOR *uv0, DVECTOR *uv1, DVECTOR *uv2, DVECTOR *uv3, KZCOLOR *col);
extern void kz_Set_PolyFT4UV_NC(sceVu0IVECTOR *crd0, sceVu0IVECTOR *crd1, sceVu0IVECTOR *crd2, sceVu0IVECTOR *crd3, DVECTOR *uv0, DVECTOR *uv1, DVECTOR *uv2, DVECTOR *uv3, KZCOLOR *col);
extern void kz_Set_PolyGT4UV(sceVu0IVECTOR *crd0, sceVu0IVECTOR *crd1, sceVu0IVECTOR *crd2, sceVu0IVECTOR *crd3, DVECTOR *uv0, DVECTOR *uv1, DVECTOR *uv2, DVECTOR *uv3, KZCOLOR *col0, KZCOLOR *col1, KZCOLOR *col2, KZCOLOR *col3);
extern void kz_Set_Alpha(u32 ctxt, u64 A, u64 B, u64 C, u64 D, u64 FIX);
extern void kz_Set_Clamp(u32 ctxt, u64 WMS, u64 WMT, u64 MINU, u64 MAXU, u64 MINV, u64 MAXV);
extern void kz_Set_Fba(u32 ctxt, u64 FBA);
extern void kz_Set_Frame(u32 ctxt, u64 FBP, u64 FBW, u64 PSM, u64 FBMSK);
extern void kz_Set_Pabe(u64 PABE);
extern void kz_Set_Test(u32 ctxt, u64 ATE, u64 ATST, u64 AREF, u64 AFAIL, u64 DATE, u64 DATM, u64 ZTE, u64 ZTST);
extern void kz_Set_Tex0(u64 TBP0, u64 TBW, u64 PSM, u64 TW, u64 TH, u64 TCC, u64 TFX, u64 CBP, u64 CPSM, u64 CSM, u64 CSA, u64 CLD);
extern void kz_Set_Tex0_Imd(u64 tex0);
extern void kz_Set_Tex1(u32 ctxt, u64 LCM, u64 MXL, u64 MMAG, u64 MMIN, u64 MTBA, u64 L, u64 K);
extern void kz_Set_Texa(u64 TA0, u64 AEM, u64 TA1);
extern void kz_Set_Texflush();
extern void kz_Set_Xyoffset(u32 ctxt, u64 OFX, u64 OFY);
extern void kz_Set_Zbuf(u32 ctxt, u64 ZBP, u64 PSM, u64 ZMSK);
extern void kz_Set_DrawPixel(u64 DBP, u64 DSAX, u64 DSAY, KZCOLOR *col0, KZCOLOR *col1);
extern void kz_Set_FogDist(s32 near, s32 far);
extern void kz_Set_FogCol(sceVu0IVECTOR col);
extern void kz_Set_Box(DVECTOR *sxy, u32 sz, DVECTOR *swh, s32 thick, KZCOLOR *col);
extern void kz_Set_Box_VGrad(DVECTOR *sxy, u32 sz, DVECTOR *swh, s32 thick, KZCOLOR *col0,KZCOLOR *col1);
extern void kz_Set_Box_HGrad(DVECTOR *sxy, u32 sz, DVECTOR *swh, s32 thick, KZCOLOR *col0, KZCOLOR *col1);
extern s32 kz_Get_KazuyaStageNo();
extern s32 kz_Get_Cont_NormalStageNo();
extern s32 kz_Get_Cont_BossStageNo();
extern s32 kz_Get_StageNo();
extern s32 kz_Get_AreaNo();
extern s32 kz_Get_StageMode();
extern void kz_Draw_Cloud(s32 mode);
extern void kz_Draw_Cloud_Core();
extern void kz_Init_McInfo(KZ_MC_INFO *ptr);

// extern s32 kz_Get_RetryVision();
// extern s32 kz_Check_Clear_CurrentStage();
// extern s32 kz_Get_PlaceStrNo();
// extern s32 kz_Check_GenjuTotalTime();
// extern s32 kz_Get_FinishedDolls();
// extern s32 kz_Get_YumeCompleteStages();
// extern void kz_Set_KL2System_Light(s32 light_no);
// extern BGM_LIST_INFO* kz_Get_Ptr_BgmListInfo();
// extern BGM_INFO* kz_Get_Ptr_BgmInfo(s32 index);
// extern s32 kz_Get_BgmIndex_Prev();
// extern s32 kz_Get_BgmIndex_Next();
// extern s32 kz_Get_BgmNameStr(s32 index);
// extern void kz_Init_SoundEffect(s32 se_no);
// extern void kz_KeyOn_SoundEffect(s32 se_no);
// extern void kz_Load_CompGms(s32 gms_no);
// extern f32 kz_Get_Coef_Intpl(s32 iNow, s32 iStart, s32 iEnd);
// extern void kz_Intpl_Color(f32 coef, KZCOLOR *dst, KZCOLOR *src0, KZCOLOR *src1);

extern void kz_Write_Buffer(u32 *buf, s32 size, char *name);

#endif