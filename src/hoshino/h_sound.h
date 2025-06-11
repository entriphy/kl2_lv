#ifndef __H_SOUND_H
#define __H_SOUND_H

#include "common.h"

typedef enum {
    SNDCMD_KEYON,
    SNDCMD_KEYOFF,
    SNDCMD_KEYOFFALL,
    SNDCMD_PITCH,
#ifdef KL2_VER_RETAIL
    SNDCMD_PALPITCH,
#endif
    SNDCMD_VOL,
    SNDCMD_MVOL,
    SNDCMD_MVOLALL,
    SNDCMD_EFFECT,
    SNDCMD_EVOL
} SNDCMD;

typedef enum {
    SND_MODE_MONAURAL,
    SND_MODE_STEREO,
    SND_MODE_5P1CH,
    SND_MODE_NUM,
} SND_MODE;

// typedef struct {
//     SND_MODE Stereo;
//     s32 iopBankAddr;
//     s32 stageBank;
//     s16 stageTblNum;
//     s16 stageTbl[1024];
//     u8 *Pk;
//     s32 PkNum;
//     s32 PkMax;
//     s32 fadeFlag;
//     f32 fadeCnt;
//     f32 fadeMax;
//     s32 ObjList;
//     s32 VoiceStat[2];
//     s32 KeyonV[2];
//     s32 Mute;
//     s32 MVol;
//     f32 log10Volume;
//     f32 dBfader;
//     f32 bgmMVol;
//     f32 seMVol;
//     s32 seObjID;
//     s32 seLock;
//     f32 effVol;
//     f32 effVolBak;
//     s32 effIdx;
//     s32 effChange;
//     s32 effMode;
//     s32 effDepth;
//     s32 effDelay;
//     s32 effFeed;
//     s32 effMix;
//     f32 pptMVol;
//     f32 pptFadeCnt;
//     s32 pptFade;
//     s32 envNum;
//     s32 envObj[16];
//     s32 envFade[16];
//     s32 envFadeCnt[16];
//     s32 envFadeMax[16];
//     f32 envFadeVol0[16];
//     f32 envFadeVol1[16];
//     s32 TitleDelayCnt;
// } hSNDDATA;

typedef struct { // 0x8c8
	/* 0x000 */ SND_MODE Stereo;
	/* 0x004 */ s32 iopBankAddr;
	/* 0x008 */ s32 stageBank;
	/* 0x00c */ s16 stageTblNum;
	/* 0x00e */ s16 stageTbl[1024];
	/* 0x810 */ u8  *Pk;
	/* 0x814 */ s32 PkNum;
	/* 0x818 */ s32 PkMax;
	/* 0x81c */ s32 fadeFlag;
	/* 0x820 */ f32 fadeCnt;
	/* 0x824 */ f32 fadeMax;
	/* 0x828 */ s32 ObjList;
	/* 0x82c */ s32 VoiceStat[2];
	/* 0x834 */ s32 KeyonV[2];
	/* 0x83c */ s32 Mute;
	/* 0x840 */ s32 MVol;
	/* 0x844 */ f32 log10Volume;
	/* 0x848 */ f32 dBfader;
	/* 0x84c */ f32 bgmMVol;
	/* 0x850 */ f32 seMVol;
	/* 0x854 */ s32 seObjID;
	/* 0x858 */ f32 effVol;
	/* 0x85c */ f32 effVolBak;
#ifndef KL2_VER_TRIAL
                s32 effIdx;
#endif
	/* 0x860 */ s32 effChange;
	/* 0x864 */ s32 effMode;
	/* 0x868 */ s32 effDepth;
	/* 0x86c */ s32 effDelay;
	/* 0x870 */ s32 effFeed;
	/* 0x874 */ s32 effMix;
	/* 0x878 */ f32 pptMVol;
	/* 0x87c */ f32 pptFadeCnt;
	/* 0x880 */ s32 pptFade;
	/* 0x884 */ s32 envNum;
	/* 0x888 */ s32 envObj[16];
#ifndef KL2_VER_TRIAL
                s32 envFade[16];
                s32 envFadeCnt[16];
                s32 envFadeMax[16];
                f32 envFadeVol0[16];
                f32 envFadeVol1[16];
                s32 TitleDelayCnt;
#endif
} hSNDDATA;

typedef struct {
    s32 efx;
    f32 vol;
    s32 delay;
    s32 feed;
    s32 dry;
#ifdef KL2_VER_RETAIL
    f32 vol_ppt;
#endif
    f32 workf0;
#ifdef KL2_VER_TRIAL
	f32 workf1;
#endif
    s32 worki0;
    s32 worki1;
} EFXSE;

extern s32  JamGetHdSize(s32 hdaddr);
extern s32  JamGetBdSize(s32 hdaddr);
extern void hSndPkEffect();
extern void hSndPkSetMVol(s32 voll, s32 volr);
extern void hSndPkSetEVol(s32 vol);
extern void hSndPkSetVol(s32 voice, f32 vollf, f32 volrf);
extern void hSndPkSetPitch(s32 voice, s32 pitch);
extern void hSndPkSetPalPitch(s32 voice);
extern void hSndPkKeyOn(s32 voice, s32 flag, s32 bank, s32 prog, s32 splt, f32 vollf, f32 volrf);
extern void hSndPkKeyOff(s32 voice);
extern void hSndPkKeyOffAll();
extern s32  hSndPkGetSize();
extern void hSndReset();
extern void hSndFadeOutAll(s32 frame);
extern void hSndMute();
extern void hSndFadeInAll(s32 frame);
extern void hSndSetMVol(f32 vol);
extern s32  hSndFader(f32 vol);
extern f32  hSndFader2(f32 vol);
extern void hSndMain();
extern void hSndInit();
extern void hSndBankSet(s32 packaddr, s32 id);
extern void hSndBankSetMain();
extern void hSndBankSetStage();
extern void hSndEffSetArea();
extern void hSndEffSetVolIdx(s32 idx);
extern void hSndEffSetVol_PPTstart();
extern void hSndEffSetVol_PPTend();
extern void hSndEffSetVol(KL2_VER_COND(s32, f32) vol);
extern void hSndSetStereo(SND_MODE i);

extern u8 SndPacket[0x400];
extern u8 SndTempBuff[0x100000];

extern hSNDDATA *sD;

#endif
