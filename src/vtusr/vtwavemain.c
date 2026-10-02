#include "vtusr/vtwavemain.h"
#include "nakano/main.h"

vtWaveStruct vtWaveGlobal;

void vtInitWave(vtDataPtr *data) {
    s32 i;

    vtWaveGlobal.vision = GameGbl.vision;
    vtWaveGlobal.count = 0;
    vtWaveGlobal.pause = 1;
    vtWaveGlobal.movie_flag = '\0';

    for (i = 0; i < 8; i++) {
        if (data->movie_data_buf[i] != NULL) {
            vtWaveGlobal.movie_flag = 1;
            vtWaveGlobal.tarostruct[i] = taroMovieInit(data->movie_data_buf[i], 0x3480, i);
        } else {
            vtWaveGlobal.tarostruct[i] = NULL;
        }
    }

    if (data->wave_data_buf != NULL) {
        vtWaveGlobal.wave_flag = 1;
        vtWaveGlobal.kitstruct = kitWaveInit(data);
    } else {
        vtWaveGlobal.wave_flag = 0;
    }

    if (data->spray_data_buf != NULL) {
        vtWaveGlobal.aostruct = aoWaveInit(data);
        vtWaveGlobal.splash_flag = 1;
    } else {
        vtWaveGlobal.splash_flag = 0;
    }

    FlushCache(WRITEBACK_DCACHE);
}

void vtExecMovieDecode(s32 movieNo) {
    u128 *packet = (u128 *)p1_packet;

    if (vtWaveGlobal.tarostruct[movieNo] == NULL || vtWaveGlobal.movie_flag != 1) {
        return;
    }

    if (vtWaveGlobal.pause == 0) {
        taroExecMovieDecode(movieNo);
    }
    packet = vtIPU_mkDmaTagOfSendTexVIF(packet, vtWaveGlobal.tarostruct[movieNo]->movie.cscBuff[vtWaveGlobal.tarostruct[movieNo]->movie.currentBufNo], &vtWaveGlobal.tarostruct[movieNo]->movie);
    p1_packet = (qword *)packet;

    if (((u32)p1_packet & 0xFFFFFFF) > (((u32)p1_packet_top + 0x100000) & 0xFFFFFFF)) {
        printf("(vtExecMovieDecode) WARNING: OT overflow\n");
    }
}

void vtExecWaveBase() {
    u128 *packet = (u128 *)p1_packet;

    vtWaveGlobal.fr = GameGbl.fr;
    vtWaveGlobal.pause = GameGbl.pause_flag;
    vtWaveGlobal.count += vtWaveGlobal.pause ^ 1;
    vtWaveGlobal.odev = GameGbl.inter;
    sceVu0CopyVector(vtWaveGlobal.cam_posi, GameGbl.cam.posi);
    sceVu0CopyVector(vtWaveGlobal.cam_rot,  GameGbl.cam.ang);
    if (vtWaveGlobal.wave_flag == 1) {
        packet = kitExecWave(packet);
        p1_packet = (qword *)packet;
    }
}

void vtExecWaveEff() {
    u128 *packet = (u128 *)p1_packet;
    if (vtWaveGlobal.splash_flag) {
        packet = aoExecWave(packet);
        p1_packet = (qword *)packet;
    }
}

void vtEndWave() {
    // Empty function
}