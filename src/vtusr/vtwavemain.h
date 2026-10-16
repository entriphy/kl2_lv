#ifndef __VT_WAVE_MAIN_H
#define __VT_WAVE_MAIN_H

#include "common.h"
#include "vtusr/vtutil.h"
#include "vtusr/kit/kitwavemain.h"
#include "vtusr/taro/taromoviemain.h"
#include "vtusr/ao/aoVU1pkt.h"

typedef struct { // 0x70
    /* 0x00 */ u32 vision;
    /* 0x04 */ u8 wave_flag;
    /* 0x05 */ u8 movie_flag;
    /* 0x06 */ u8 splash_flag;
    /* 0x07 */ u8 pause;
    /* 0x08 */ u32 fr;
    /* 0x0c */ u32 odev;
    /* 0x10 */ u32 count;
    /* 0x20 */ sceVu0FVECTOR cam_posi;
    /* 0x30 */ sceVu0FVECTOR cam_rot;
    /* 0x40 */ kitWaveStruct *kitstruct;
    /* 0x44 */ taroMovieStruct *tarostruct[8];
    /* 0x64 */ aoWaveStruct *aostruct;
} vtWaveStruct;

extern vtWaveStruct vtWaveGlobal;

extern void vtInitWave(vtDataPtr *data);
extern void vtExecMovieDecode(s32 movieNo);
extern void vtExecWaveBase();
extern void vtExecWaveEff();
extern void vtEndWave();

#endif