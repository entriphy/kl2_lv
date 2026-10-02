#ifndef __AO_ENV_H
#define __AO_ENV_H

#include "common.h"
#include "vtusr/vtfiremain.h"

extern u128* setSprayEnv(u128 *pkt, aoWaveStruct *aoStruct);
extern u128* endSprayEnv(u128 *pkt);

#endif