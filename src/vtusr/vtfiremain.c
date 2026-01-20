#include "vtusr/vtfiremain.h"
#include "nakano/main.h"

/* data 34d1e0 */ vtFireStruct vtFireGlobal;
/* data 34d200 */ u16 ipuClut[16];
/* data 34d220 */ u8 gsClut[16][4];

// TODO: remove
extern vtWaveStruct vtWaveGlobal;

void vtInitFire(/* a0 4 */ s32 flag) {
    /* t0 8 */ s32 i;
    /* a1 5 */ u32 r;
    /* a3 7 */ u32 g;
    u32 b;
    /* a2 6 */ u32 a;

    vtFireGlobal.vision = GameGbl.vision;
    vtFireGlobal.count = 0;
    vtFireGlobal.pause = 1;

    for (i = 0; i < 16; i++) {
        r = ((i << 8) - i) >> 4;
        g = r;
        b = 0;
        a = (i << 7) >> 4;
        gsClut[i][0] = r;
        gsClut[i][1] = g;
        gsClut[i][2] = b;
        gsClut[i][3] = a;

        r = r >> 3 & 0x1F;
        g = g >> 3 & 0x1F;
        b = b >> 3 & 0x1F;
        a = a >> 7 & 0x1;
        ipuClut[i] = r | g << 5 | b << 10 | a << 15;
    }

    vtIPU_initVQ(&vtFireGlobal.tarostruct->movie, ipuClut, gsClut, 0, 0, 0, 5, 1);
    vtFireGlobal.kitstruct->tex0 = SCE_GS_SET_TEX0(
        vtFireGlobal.tarostruct->movie.texbp,
        vtFireGlobal.tarostruct->movie.texbw,
        20,
        vtFireGlobal.tarostruct->movie.tw,
        vtFireGlobal.tarostruct->movie.th,
        1,
        SCE_GS_MODULATE,
        vtFireGlobal.tarostruct->movie.cbp,
        vtFireGlobal.tarostruct->movie.cpsm,
        vtFireGlobal.tarostruct->movie.csm,
        vtFireGlobal.tarostruct->movie.csa,
        vtFireGlobal.tarostruct->movie.cld
    );

    FlushCache(WRITEBACK_DCACHE);
}

void vtExecFire() {
    u128 *packet = (u128 *)p1_packet;
    
    if (!vtFireGlobal.fire_flag) {
        return;
    }

    vtFireGlobal.tarostruct = vtWaveGlobal
}