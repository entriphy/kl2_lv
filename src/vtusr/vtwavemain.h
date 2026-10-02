#ifndef __VT_WAVE_MAIN_H
#define __VT_WAVE_MAIN_H

#include "common.h"
#include "vtusr/vtfiremain.h"

extern vtWaveStruct vtWaveGlobal;

extern void vtInitWave(vtDataPtr *data);
extern void vtExecMovieDecode(s32 movieNo);
extern void vtExecWaveBase();
extern void vtExecWaveEff();
extern void vtEndWave();

#endif