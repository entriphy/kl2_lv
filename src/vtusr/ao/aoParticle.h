#ifndef __AO_PARTICLE_H
#define __AO_PARTICLE_H

#include "common.h"
#include "vtusr/vtfiremain.h"

extern aoWaveStruct* aoWaveInit(vtDataPtr *vtdata);
extern u128* aoExecWave(u128 *pkt);
extern void aoWaveEnd();
extern u32 Ao_particle_start __attribute__((section(".vudata")));
extern u32 Ao_particle_end __attribute__((section(".vudata")));

#endif