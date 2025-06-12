#ifndef __H_STR_H
#define __H_STR_H

#include "common.h"
#include "hoshino/h_sound.h"

typedef struct {
    s32 start;
    s32 chsize;
    s32 chnum;
} BGMTABLE;

typedef struct {
    s32 top;
    s32 nsector;
} PPTTABLE;

typedef struct {
    s32 lsn;
    s32 sectors;
} KLTABLE; // ?

#ifdef KL2_VER_TRIAL
typedef enum {
    BGM_NO = -1,
	BGM040,
	BGM058,
	BGM000,
	BGM001,
	BGM060,
	BGM009,
	BGM045,
	BGM036,
	BGM_MAXNUM
} BGM;
#else
typedef enum {
    BGMNO = -1,
    BGM000,
    BGM001,
    BGM002,
    BGM003,
    BGM004,
    BGM005,
    BGM006,
    BGM007,
    BGM008,
    BGM009,
    BGM010,
    BGM011,
    BGM012,
    BGM071,
    BGM013,
    BGM014,
    BGM015,
    BGM016,
    BGM017,
    BGM018,
    BGM019,
    BGM020,
    BGM021,
    BGM022,
    BGM078,
    BGM023,
    BGM077,
    BGM024,
    BGM025,
    BGM026,
    BGM027,
    BGM028,
    BGM029,
    BGM030,
    BGM031,
    BGM032,
    BGM033,
    BGM034,
    BGM035,
    BGM036,
    BGM037,
    BGM038,
    BGM039,
    BGM040,
    BGM062,
    BGM041,
    BGM042,
    BGM043,
    BGM044,
    BGM045,
    BGM046,
    BGM047,
    BGM048,
    BGM050,
    BGM052,
    BGM053,
    BGM054,
    BGM060,
    BGM055,
    BGM056,
    BGM057,
    BGM058,
    BGM059,
    BGM070,
    BGM061,
    BGM075,
    BGM076,
    BGM063,
    BGM064,
    BGM065,
    BGM066,
    BGM067,
    BGM068,
    BGM069,
    BGM072,
    BGM073,
    BGM074,
    BGM079,
    BGM080,
    BGM081,
    BGM082,
    BGM083,
    BGM049,
    BGM084,
    BGM085,
    BGM086,
} BGM;
#endif

typedef struct {
    /* 0x00 */ sceCdlFILE Fp;
    /* 0x20 */ s32 Command;
    /* 0x24 */ BGM bgmNo;
    /* 0x28 */ s32 bgmCh;
    /* 0x2c */ s32 bgmChMax;
#ifdef KL2_VER_RETAIL
    /* 0x30 */ s32 bgmLength;
    /* 0x34 */ s32 bgmSkipSize;
#endif
    /* 0x38 */ s32 bgmNo2;
    /* 0x3c */ f32 bgmVol;
    /* 0x40 */ s32 bgmMute;
    /* 0x44 */ s32 fadeFlag;
    /* 0x48 */ s32 fadeCnt;
    /* 0x4c */ s32 fadeMax;
    /* 0x50 */ BGM nextNo;
    /* 0x54 */ s32 nextCh;
    /* 0x58 */ s32 nextFrame;
    /* 0x5c */ f32 nextVol;
    /* 0x60 */ s32 spWk0;
#ifdef KL2_VER_RETAIL
    /* 0x64 */ s32 iopPoint;
#endif
    /* 0x68 */ s32 iopNext;
    /* 0x6c */ s32 iopID;
    /* 0x70 */ s32 iopAddr[KL2_VER_COND(3, 2)];
    /* 0x78 */ s32 iopOK[2];
    /* 0x80 */ s32 iopFineTop[2];
    /* 0x88 */ s32 iopFine[2];
    /* 0x90 */ s32 cdReq;
    /* 0x94 */ s32 cdTop;
    /* 0x98 */ s32 cdCur;
    /* 0x9c */ s32 cdSectors;
    /* 0xa0 */ s32 cdRemain;
} hBGMDATA;

typedef struct {
    /* 0x000 */ sceCdlFILE file;
    /* 0x020 */ s32 reqNum;
#ifdef KL2_VER_RETAIL
    /* 0x024 */ u32 reqID;
#endif
    f32 reqVol[4];
    s32 listLoad;
    s32 listPlay;
    s32 listPlayIdx;
    s32 listNum[8];
    s32 *listTbl[8];
    s32 pptMute;
    f32 pptVol[4];
    s32 pptPlay[4];
    s32 pptSize[4];
    s32 pptStop[4];
#ifdef KL2_VER_RETAIL
    s32 pptID[4];
#endif
    s32 iopID;
    s32 iopBfID[4];
    s32 iopNext[4];
    s32 iopAddr[4][2];
    s32 eeID;
    s32 eeAddr[4];
    s32 eeOffset[4];
    s32 eeStat[4];
} hPPTDATA;

#ifdef KL2_VER_RETAIL
typedef struct {
    sceCdlFILE files[4];
    s32 field_0x80;
    s32 field_0x84;
    s32 field_0x88;
    s32 field_0x8C;
    s32 field_0x90;
    s32 field_0x94;
    s32 field_0x98;
    s32 field_0x9C;
    s32 field_0xA0;
    s32 field_0xA4;
    s32 field_0xA8;
    s32 AC3stat;
    s32 field_0xB0;
    s32 field_0xB4[2];
    s32 field_0xBC;
    s32 field_0xC0;
    s32 field_0xC4;
    s32 field_0xC8[2];
    s32 field_0xD0[2];
    s32 field_0xD8;
    s32 field_0xDC;
    s32 field_0xE0;
    s32 field_0xE4;
    s32 field_0xE8;
    s32 field_0xEC;
} hAC3DATA; // ?
#endif

typedef struct {
    s32 eeCnt;
    s32 Command;
#ifdef KL2_VER_RETAIL
    SND_MODE BGMstereo;
    s32 BGMlength;
    s32 BGMskipsize;
#endif
    s32 BGMvol;
    s8 BGMch;
    s8 BGMchmax;
    s8 BGMok[2];
    s32 BGMfinetop[2];
    s32 BGMfine[2];
    s32 PPTvol[4];
    s32 PPTsize[4];
    s8 PPTstop[4];
    s32 work0;
    s32 idk;
} STRINFO;

typedef struct {
    /* 0x00 */ s32 BGMnext;
#ifdef KL2_VER_RETAIL
    /* 0x04 */ s32 BGMpoint;
#endif
    /* 0x08 */ s32 PPTnext[4];
#ifdef KL2_VER_RETAIL
    /* 0x18 */ s32 AC3stat;
#endif
} STRINFO2;

extern hBGMDATA *bD;
extern hPPTDATA *pD;
#ifdef KL2_VER_RETAIL
extern hAC3DATA *aD;
#endif

extern s32  hBgmGetPlaySize();
extern f32  hBgmGetDefVol(BGM no);
extern s32  hBgmGetLoopSize(BGM no);
extern s32  hBgmGetLoopLSN();
extern void hBgmPlay(BGM no, s32 ch);
extern void hBgmPlayLast10sec(BGM no, s32 ch);
extern void hBgmFadeIn(BGM no, s32 ch, s32 frame);
extern void hBgmFadeOut(s32 frame);
extern void hBgmFadeNext(s32 frame, BGM nextno, s32 nextch, s32 nextframe, f32 nextvol);
extern void hBgmPause();
extern void hBgmSetVol(f32 vol);
extern void hBgmMute();
extern void hBgmSetCh(s32 ch);
extern void hBgmChangeChX(s32 ch);
extern void hBgmWorkClear();
extern void hBgmReset();
extern void hBgmStop();
extern void hBgmFadeNextClear();
extern void hBgmRead();
extern void hBgmRemain();
extern void hBgmMain();
extern s32  hBgmGetMaxCh(BGM no);
extern s32  hBgmGetStat();
extern BGM  hBgmGetPlayNo();
extern s32  hBgmGetPlayCh();
extern void hBgmChangeID(s32 id, s32 mode);
extern void hPptWorkClear();
extern void hPptStop(s32 id);
extern void hPptReset();
extern void hPptPause();
extern s32  hPptReq();
extern void hPptKick();
extern s32  hPptGetFrame(s32 no);
extern void hPptSetList(s32 *p);
extern s32  hPptCheckList();
extern s32  hPptGetListNo();
extern void hPptMain();
extern void hStrInfo();
extern void hStrInit();
extern void hStr_0016f4d8();
extern void hStr_0016f5c8(s32 ac3);
extern s32  hStr_0016f680();
extern s32  hStr_0016f690();
extern void hStr_0016f6a8(s32 ac3);
extern void hStr_0016f6e8();
extern void hStr_0016f718(s32 param_1);
extern void hStr_0016f730();
extern void hStr_0016f770();
extern void hStr_0016f7b0();
extern void hStr_0016f7e8();
extern void hStrMain();

#endif