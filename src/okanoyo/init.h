#ifndef __OK_INIT_H
#define __OK_INIT_H

#include "common.h"

typedef struct { // 0x140
    /* 0x000 */ sceVu0FVECTOR pos;
    /* 0x010 */ s32 flag;
    /* 0x014 */ s32 rno;
    /* 0x018 */ s32 mcn;
    /* 0x01c */ f32 ypos;
    /* 0x020 */ char *zoutflgBufp[24];
    /* 0x080 */ s32 *ioutflgBufp[24];
    /* 0x0e0 */ s32 okitemKeyflag;
    /* 0x0e4 */ s32 okitemKeyusedflag;
    /* 0x0e8 */ s32 okitemSwitchflag;
    /* 0x0ec */ s32 okitemKeyID;
    /* 0x0f0 */ s32 OkSTGBuf[64];
    /* 0x1f0 */ s32 vision;
    /* 0x1f4 */ s32 klodir;
    /* 0x1f8 */ s32 klomode;
    /* 0x1fc */ s32 OkDPcnt;
    /* 0x200 */ s32 OkEXcnt;
    /* 0x204 */ s32 OkDPStcnt;
    /* 0x208 */ s32 OkExId;
} RESTARTDATA;

extern void OkSaveforReStart(s32 rno, s32 mcn, f32 ypos, s32 bun1, s32 dir);

#endif
