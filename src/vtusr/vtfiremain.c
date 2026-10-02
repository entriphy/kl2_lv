#include "vtusr/vtfiremain.h"
#include "vtusr/vtwavemain.h"
#include "nakano/main.h"

vtFireStruct vtFireGlobal;
u16 ipuClut[16];
u8 gsClut[16][4];

void vtInitFire(s32 flag) {
    s32 i;
    u32 r;
    u32 g;
    u32 b;
    u32 a;

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

    vtFireGlobal.tarostruct = vtWaveGlobal.tarostruct[7];
    if (vtFireGlobal.tarostruct == NULL) {
        printf(KL2_VER_COND("There is No Fire Movie File\n", "Warning : This vision has No Fire Movie File\n"));
    }
    
    vtFireGlobal.fr = GameGbl.fr;
    vtFireGlobal.pause = vtFireGlobal.kitstruct->pause = GameGbl.pause_flag;
    vtFireGlobal.count += vtFireGlobal.pause ^ 1;
    vtFireGlobal.odev = GameGbl.inter;
    
    if (vtFireGlobal.fire_flag == 1) {
        vtIPU_decode(&vtFireGlobal.tarostruct->movie);
        vtIPU_syncDecode(&vtFireGlobal.tarostruct->movie);
        vtIPU_VQ(&vtFireGlobal.tarostruct->movie);
        vtIPU_Sync(0, 20);
        p1_packet = (qword *)vtIPU_mkPacketForVQ(packet, &vtFireGlobal.tarostruct->movie, 0);
    }
}