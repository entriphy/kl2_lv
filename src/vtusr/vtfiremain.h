#ifndef __VT_FIRE_MAIN_H
#define __VT_FIRE_MAIN_H

#include "common.h"
#include <libipu.h>
#include "kit/kitfiremain.h"
#include "taro/taromoviemain.h"

typedef struct { // 0x1c
    /* 0x00 */ u32 vision;
    /* 0x04 */ u8 fire_flag;
    /* 0x05 */ u8 pause;
    /* 0x08 */ u32 fr;
    /* 0x0c */ u32 odev;
    /* 0x10 */ u32 count;
    /* 0x14 */ kitFireStruct *kitstruct;
    /* 0x18 */ taroMovieStruct *tarostruct;
} vtFireStruct;

extern void vtInitFire(s32 flag);
extern void vtExecFire();

extern vtFireStruct vtFireGlobal;

#endif