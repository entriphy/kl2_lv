#ifndef __TAKE_SFXINMAC_H
#define __TAKE_SFXINMAC_H

#include "common.h"

inline void DmaSync_Mac(sceDmaChan *DmaChan) {
    while (*(vs32 *)(&DmaChan->chcr) & D_CHCR_STR_M);
}

inline void DmaSend_Mac(sceDmaChan *DmaChan, u128 *Addr) {
    DmaChan->tadr = (sceDmaTag *)Addr;
    DmaChan->qwc = 0;
    DmaChan->chcr.MOD = 1;
    DmaChan->chcr.STR = 1;
}

#endif