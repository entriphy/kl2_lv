#ifndef __HR_BGWK_H
#define __HR_BGWK_H

#include "common.h"

typedef struct { // 0x90
    /* 0x00 */ sceVu0FMATRIX m;
    /* 0x40 */ sceVu0FMATRIX m0;
    /* 0x80 */ mINFO *info;
    /* 0x84 */ s32 rx;
    /* 0x88 */ s32 ry;
    /* 0x8c */ s32 fg;
} BGWK;

#endif