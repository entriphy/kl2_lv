#ifndef __H_STR_H
#define __H_STR_H

#include "common.h"

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