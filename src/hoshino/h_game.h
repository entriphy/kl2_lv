#ifndef __H_GAME_H
#define __H_GAME_H

#include "common.h"
#include "hoshino/h_str.h"

typedef enum {
    DEAD_DAMAGE,
    DEAD_FALL,
    DEAD_DROWN,
    DEAD_CHOKE,
    DEAD_BURN
} DEAD;

typedef struct { // 0x10
    /* 0x0 */ s32 bgmNo;
    /* 0x4 */ s32 bgmCh;
    /* 0x8 */ f32 fadeIn;
    /* 0xc */ f32 fadeOut;
} BGMAREA;

typedef enum {
    BGMMODE_TOP,
    BGMMODE_START,
    BGMMODE_GAME,
    BGMMODE_END,
} BGMMODE;

typedef struct { // 0x3c
	/* 0x00 */ BGMMODE BGMmode;
	/* 0x04 */ s32 BGMppt;
	/* 0x08 */ s32 BGMpptcnt;
	/* 0x0c */ s32 BGMid;
	/* 0x10 */ s32 BGMchgreq;
	/* 0x14 */ s32 BGMchgid;
	/* 0x18 */ s32 BGMchgmode;
	/* 0x1c */ s32 nextVision;
	/* 0x20 */ s32 areaTime;
	/* 0x24 */ s32 resFlag;
	/* 0x28 */ s32 resBGM;
	/* 0x2c */ s32 resVision;
	/* 0x30 */ f32 resEVol;
	/* 0x34 */ s32 deadFlag;
	/* 0x38 */ s32 deadCnt;
} hGAMEDATA;

extern hGAMEDATA GameData;
extern hGAMEDATA *gD;

extern void hInitGame();
extern void hExitGame();
extern void hInitStage0();
extern void hInitStage1();
extern void hExitStage();
extern s32  hGameAreaStart(s32 flag);
extern s32  hGameAreaEnd(s32 next);
extern void hGameMain();
extern void hPushRestart();
extern void hPopRestart();
extern void hKlonoaDead(s32 vision, s32 frame, DEAD pattern);
extern s32  hGameBgmGetID();
extern BGM  hGameBgmGetNo();
extern s32  hGameBgmGetCh();
extern void hGameBgmChange();
extern s32  hGameBgmComp(s32 v0, s32 id0, s32 v1, s32 id1);

#endif