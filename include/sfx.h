#ifndef __KL2_SFX_H
#define __KL2_SFX_H

#include "common.h"
#include "kit.h"

#define DECADDR0 ((sceVu0FMATRIX *)0x70000000)
#define DECADDR1 ((sceVu0FMATRIX *)0x70001000)
#define DECADDR2 ((sceVu0FMATRIX *)0x70002000)
#define DECADDR3 ((sceVu0FMATRIX *)0x70003000)
#define ALIGN(x) (u32 *)(((u32)x + 0xF) & ~0xF)
#define ALIGN_ALT(x, y) (u32 *)(((u32)x + y + 0xF) & ~0xF)

typedef struct tagCOORD { // 0xb0
    /* 0x00 */ sceVu0FVECTOR Rot;
    /* 0x10 */ sceVu0FVECTOR Trans;
    /* 0x20 */ sceVu0FMATRIX Mtx;
    /* 0x60 */ sceVu0FMATRIX MtxSav;
    /* 0xa0 */ f32 WipCnt;
    /* 0xa4 */ struct tagCOORD *Super;
    /* 0xa8 */ s32 Flag;
} COORD;

typedef struct { // 0x40
    /* 0x00 */ sceVu0FMATRIX Matrix;
} SCOORD;

typedef struct { // 0x70
    /* 0x00 */ sceVu0FVECTOR Trans;
    /* 0x10 */ sceVu0FVECTOR Rot;
    /* 0x20 */ sceVu0FMATRIX CameraMtx;
    /* 0x60 */ f32 *pTra;
} COORD_C;

typedef struct { // 0x20
    /* 0x00 */ s16 joint_id[4];
    /* 0x08 */ u16 vert_n;
    /* 0x0a */ u16 norm_n;
    /* 0x0c */ u16 vert_vif;
    /* 0x0e */ u16 norm_vif;
    /* 0x10 */ u32 *vert_ofs;
    /* 0x14 */ u32 *v_wt_adrs;
    /* 0x18 */ u32 *norm_ofs;
    /* 0x1c */ u32 *n_wt_adrs;
} TYPE_JOINT_BLK;

typedef struct { // 0x20
    /* 0x00 */ sceVu0FVECTOR vert;
    /* 0x10 */ sceVu0FVECTOR wt;
} TYPE_VERTEX;

typedef struct { // 0x10
    /* 0x0 */ f32 wt[4];
} TYPE_WEIGHT;

typedef struct { // 0x10
    /* 0x0 */ f32 vx;
    /* 0x4 */ f32 vy;
    /* 0x8 */ f32 vz;
    /* 0xc */ f32 pad;
} TYPE_VECTOR;

typedef struct { // 0x20
    /* 0x00 */ sceVu0FVECTOR norm;
    /* 0x10 */ sceVu0FVECTOR wt;
} TYPE_NORMAL;

typedef struct { // 0x8
    /* 0x0 */ u64 uv;
} TYPE_UV2;

typedef struct { // 0x8
    /* 0x0 */ u16 n0;
    /* 0x2 */ u16 t0;
    /* 0x4 */ u16 p0;
    /* 0x6 */ u16 num;
} TYPE_STRIP;

typedef struct { // 0x10
    /* 0x0 */ u16 id;
    /* 0x2 */ u16 parts_num;
    /* 0x4 */ u16 vif_pnt_fix;
    /* 0x6 */ u16 vif_pnt_skin;
    /* 0x8 */ f32 scale;
    /* 0xc */ u32 pad;
} TYPE_SFX_HEADER;

typedef struct { // 0x10
    /* 0x0 */ u16 id;
    /* 0x2 */ u16 parts_num;
    /* 0x4 */ u16 vif_pnt_fix;
    /* 0x6 */ u16 vif_pnt_skin;
    /* 0x8 */ f32 scale;
    /* 0xc */ u16 frame_st;
    /* 0xe */ u16 frame_en;
} TYPE_SFZ_HEADER;

typedef struct { // 0x28
    /* 0x00 */ s16 pbp;
    /* 0x02 */ s16 cbp;
    /* 0x04 */ s32 flag;
    /* 0x08 */ u64 tex0;
    /* 0x10 */ s32 px;
    /* 0x14 */ s32 py;
    /* 0x18 */ s32 cx;
    /* 0x1c */ s32 cy;
    /* 0x20 */ s32 w;
    /* 0x24 */ s32 h;
} GIMINFO;

typedef struct { // 0x10
    /* 0x0 */ u16 bp;
    /* 0x2 */ u8 bw;
    /* 0x3 */ u8 psm;
    /* 0x4 */ u32 pad0;
    /* 0x8 */ u16 x;
    /* 0xa */ u16 y;
    /* 0xc */ u16 w;
    /* 0xe */ u16 h;
} GIMHEADER;

typedef struct { // 0x30
    /* 0x00 */ u16 type;
    /* 0x02 */ u16 texture_id;
    /* 0x04 */ u16 strip_num;
    /* 0x06 */ u16 strip_blk;
    /* 0x08 */ u16 uv_num;
    /* 0x0a */ u16 jblock_num;
    /* 0x0c */ u16 vert_num;
    /* 0x0e */ u16 norm_num;
    /* 0x10 */ TYPE_STRIP *strip_adrs;
    /* 0x14 */ TYPE_UV2 *uv_adrs;
    /* 0x18 */ TYPE_VECTOR *vert_adrs;
    /* 0x1c */ TYPE_VECTOR *norm_adrs;
    /* 0x20 */ TYPE_JOINT_BLK *jblock_adrs;
    /* 0x24 */ u32 pad1;
    /* 0x28 */ sceGsTex0 gs_tex0;
} TYPE_PARTS_TBL;

typedef struct { // 0x30
    /* 0x00 */ u16 type;
    /* 0x02 */ u16 texture_id;
    /* 0x04 */ u16 strip_num;
    /* 0x06 */ u16 strip_blk;
    /* 0x08 */ u16 uv_num;
    /* 0x0a */ u16 p0;
    /* 0x0c */ u16 vert_num;
    /* 0x0e */ u16 norm_num;
    /* 0x10 */ TYPE_STRIP *strip_adrs;
    /* 0x14 */ TYPE_UV2 *uv_adrs;
    /* 0x18 */ TYPE_VECTOR *vert_adrs;
    /* 0x1c */ TYPE_VECTOR *norm_adrs;
    /* 0x20 */ u32 pad0;
    /* 0x24 */ u32 pad1;
    /* 0x28 */ sceGsTex0 gs_tex0;
} TYPE_PARTS_TBL2;

typedef struct { // 0x20
    /* 0x00 */ u16 parts_id;
    /* 0x02 */ u16 parts_size;
    /* 0x04 */ u16 vert_num;
    /* 0x06 */ u16 norm_num;
    /* 0x08 */ u32 *vert_adrs;
    /* 0x0c */ u32 *norm_adrs;
    /* 0x10 */ u16 *key_adrs;
    /* 0x14 */ u32 key_frame;
    /* 0x18 */ u32 pad0;
    /* 0x1c */ u32 pad1;
} TYPE_SFZ_TBL;

typedef struct { // 0x60
    /* 0x00 */ s16 PartsNum;
    /* 0x02 */ s16 FlameNum;
    /* 0x04 */ s16 RotOutNum;
    /* 0x06 */ s16 TraOutNum;
    /* 0x08 */ s8 ActName[8];
    /* 0x10 */ s32 pad0;
    /* 0x14 */ s32 MimeAddrs;
    /* 0x18 */ s32 CompressFlag;
    /* 0x1c */ s32 TexAddrs;
    /* 0x20 */ u128 TraOutFlag;
    /* 0x30 */ f32 Xoffset;
    /* 0x34 */ f32 Yoffset;
    /* 0x38 */ f32 Zoffset;
    /* 0x3c */ f32 Scale;
    /* 0x40 */ u32 RotAddrs;
    /* 0x44 */ u32 TraAddrs;
    /* 0x48 */ s16 stopflag;
    /* 0x4a */ s16 sync;
    /* 0x4c */ s16 incnt;
    /* 0x4e */ s16 outcnt;
    /* 0x50 */ s16 inmode;
    /* 0x52 */ s16 outmode;
    /* 0x58 */ s64 OnFlag;
} ACT_HEADER;

typedef struct { // 0x18
    /* 0x00 */ u16 Coord;
    /* 0x02 */ u16 PartsNum;
    /* 0x04 */ u16 FrameNum;
    /* 0x06 */ u16 Pad;
    /* 0x08 */ f32 Xoffset;
    /* 0x0c */ f32 Yoffset;
    /* 0x10 */ f32 Zoffset;
    /* 0x14 */ f32 Scale;
} ACX_HEADER;

typedef struct { // 0x90
    /* 0x00 */ s8 name[16];
    /* 0x10 */ s8 outline[64];
    /* 0x50 */ s8 spectype[64];
} SFXENV;

typedef struct { // 0x18
    /* 0x00 */ s16 mot;
    /* 0x02 */ s16 stopflag;
    /* 0x04 */ s16 sync;
    /* 0x06 */ s16 incnt;
    /* 0x08 */ s16 outcnt;
    /* 0x0a */ s16 inmode;
    /* 0x0c */ s16 outmode;
    /* 0x10 */ u64 onflag;
} ACTTBL;

typedef struct { // 0x38
    /* 0x00 */ f32 MotionCnt;
    /* 0x04 */ f32 MotionEndCnt;
    /* 0x08 */ f32 CntSpeed;
    /* 0x0c */ f32 Weight;
    /* 0x10 */ f32 TargetWeight;
    /* 0x14 */ f32 InCnt;
    /* 0x18 */ f32 OutCnt;
    /* 0x20 */ u64 OnFlag;
    /* 0x28 */ s8 *pAct;
    /* 0x2c */ s16 StopFlag;
    /* 0x2e */ s16 Type;
    /* 0x30 */ s16 SyncFlag;
    /* 0x32 */ s16 InMode;
    /* 0x34 */ s16 OutMode;
} MBLOCK;

typedef struct { // 0x218
    /* 0x000 */ u8 *ActAdrs;
    /* 0x004 */ f32 SubScale;
    /* 0x008 */ s16 ActNum;
    /* 0x00a */ s16 ActNumMax;
    /* 0x00c */ COORD *pBaseCoord;
    /* 0x010 */ COORD *pCoord;
    /* 0x014 */ u8 *pInf;
    /* 0x018 */ u8 *pItr;
    /* 0x01c */ u8 *pItrW;
    /* 0x020 */ s16 CoordNum;
    /* 0x022 */ s16 BaseIndex;
    /* 0x024 */ s16 BaseMixIndex;
    /* 0x026 */ s16 IpIndex;
    /* 0x028 */ s16 IpMixIndex;
    /* 0x02c */ f32 IpWeight[64];
    /* 0x12c */ ACTTBL *pActtbl;
    /* 0x130 */ MBLOCK Mb[4];
    /* 0x210 */ s16 EndFlag;
} MOTION;

typedef struct { // 0x160
    /* 0x000 */ qword_uni GsEnv[16];
    /* 0x100 */ sceGsTex0 gs_tex0;
    /* 0x108 */ s32 *jblock_adrs;
    /* 0x10c */ s32 *sfx_adrs;
    /* 0x110 */ s32 *vert_adrs;
    /* 0x114 */ s32 *norm_adrs;
    /* 0x118 */ s32 *vert_adrs_mime0;
    /* 0x11c */ s32 *norm_adrs_mime0;
    /* 0x120 */ s32 *vert_adrs_mime1;
    /* 0x124 */ s32 *norm_adrs_mime1;
    /* 0x128 */ s32 *uv_adrs;
    /* 0x12c */ s32 *prim_adrs;
    /* 0x130 */ s32 *vert_wt_adrs;
    /* 0x134 */ s32 *norm_wt_adrs;
    /* 0x138 */ f32 MimeWeight;
    /* 0x13c */ u32 *GmsAdr;
    /* 0x140 */ u16 type;
    /* 0x142 */ u16 jblock_num;
    /* 0x144 */ u16 vert_num;
    /* 0x146 */ u16 norm_num;
    /* 0x148 */ u16 uv_num;
    /* 0x14a */ u16 prim_num;
    /* 0x14c */ u16 prim_blk;
    /* 0x14e */ u16 coord_id;
    /* 0x150 */ s16 GsEnvInd;
    /* 0x152 */ s16 SpecType;
    /* 0x154 */ s16 OutLine;
} PARTS;

typedef struct { // 0x18
    /* 0x00 */ u64 IdFlag;
    /* 0x08 */ s16 *pVmime;
    /* 0x0c */ s16 VmimeInd;
    /* 0x10 */ f32 VmimeCnt;
    /* 0x14 */ f32 VmimeCntSpeed;
} MIME;

typedef struct SFXOBJ { // 0xa0
    /* 0x00 */ sceVu0FVECTOR ScaleVector;
    /* 0x10 */ MOTION *pMot;
    /* 0x14 */ sceVu0FMATRIX *pLightColor;
    /* 0x18 */ sceVu0FMATRIX *pNormalLight;
    /* 0x1c */ s32 PartsNum;
    /* 0x20 */ s32 *GmsAdrs;
    /* 0x24 */ s32 *SubGmsAdrs;
#ifdef KL2_VER_TRIAL
               s32 *RgbGmsAdrs;
#endif
    /* 0x28 */ s32 *MimeAdrs;
    /* 0x2c */ s32 *SvxAdrs;
    /* 0x30 */ s32 *SvxWorkAdrs;
    /* 0x34 */ SFXENV *EnvAdrs;
#ifdef KL2_VER_RETAIL
    /* 0x38 */ s16 GmsNum;
#endif
    /* 0x3c */ f32 scale;
    /* 0x40 */ PARTS *pParts;
    /* 0x44 */ struct SFXOBJ *pObjSub;
    /* 0x48 */ struct SFXOBJ *pObjTop;
    /* 0x4c */ f32 ClutWeight;
    /* 0x50 */ u32 Flag;
    /* 0x54 */ u32 Condition;
    /* 0x58 */ s16 Pause;
    /* 0x5a */ s16 GmsTransType;
    /* 0x5c */ kitOutlineObjEnv LineEnv;
    /* 0x64 */ MIME *pMime;
    /* 0x68 */ s16 OutLineFlag;
    /* 0x6c */ f32 ClipOffset;
    /* 0x70 */ f32 ClipZone;
    /* 0x74 */ s16 ClipFlag;
    /* 0x76 */ s16 Id;
    /* 0x78 */ u16 ClutNum0;
    /* 0x7a */ u16 ClutNum1;
    /* 0x7c */ u16 Cbp;
    /* 0x7e */ u16 NonActFlag;
    /* 0x80 */ u16 MotionSyncFlag;
    /* 0x84 */ s32 ShadowType;
    /* 0x88 */ f32 ShadowSize;
    /* 0x8c */ f32 ShadowOffset;
    /* 0x90 */ f32 ShadowRange;
    /* 0x94 */ s16 ObjNum;
#ifdef KL2_VER_RETAIL
    /* 0x96 */ s16 DrawWorkCnt;
#endif
    /* 0x98 */ s32 OutFlag;
    /* 0x9c */ s32 actNum;
} SFXOBJ;

typedef struct tCOORD {
    sceVu0FVECTOR Rot;
    sceVu0FVECTOR Trans;
    sceVu0FMATRIX LcMtx;
    sceVu0FMATRIX LwMtx;
    sceVu0FMATRIX LsMtx;
    sceVu0FMATRIX LvMtx;
    sceVu0FMATRIX LcLightMtx;
    struct tCOORD *Super;
    s32 Flag;
} tCOORD;

typedef struct { // 0x1a0
	/* 0x000 */ tCOORD Base;
	/* 0x170 */ sceVu0FMATRIX *pNormalLight;
	/* 0x174 */ sceVu0FMATRIX *pLightColor;
	/* 0x178 */ f32 Scale;
	/* 0x17c */ s32 Size;
	/* 0x180 */ s32 Fuku;
	/* 0x184 */ s32 OutLine;
	/* 0x188 */ SFXOBJ *pSfx;
	/* 0x18c */ MOTION *pMot;
	/* 0x190 */ s32 ret;
} tOBJECT;

// what
typedef tOBJECT HOT;
typedef tCOORD COLD;

#endif