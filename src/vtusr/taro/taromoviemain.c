#include "vtusr/taro/taromoviemain.h"
#include "vtusr/taro/taro_movie.h"
#include "vtusr/vtutil.h"
#include "vtusr/vtwavemain.h"

taroMovieStruct* taroMovieInit(void *moviebuff, u32 vram_addr, s32 movieNo) {
    u32 len;
    u128 *bsTags;
    u128 *dmaTag[2] = {};
    sceIpuRGB32 *cscBuff[2] = {};
    taroMovieStruct *env = NULL;

    if (moviebuff == NULL) {
        return NULL;
    }

    if (movieNo >= 8 && vtWaveGlobal.tarostruct[movieNo - 8] == NULL) {
        return NULL;
    }

    env = vtGetBuf64(sizeof(taroMovieStruct));
    memset(env, 0, sizeof(taroMovieStruct));
    if (movieNo >= 8) {
        vtCpMovieStruct(&env->movie, &vtWaveGlobal.tarostruct[movieNo - 8]->movie, vram_addr);
    }

    switch (vtIPU_setBsdata(&env->movie, moviebuff)) {
        case 0:
            break;
        case -1:
            KL2_DEBUG_PRINT(("ERROR: MOVIE DATA IS UNKNOWN FORMAT TYPE.\n"));
            Exit(EXIT_SUCCESS); // ok man
        case 1:
        default:
            env->vram_addr = env->movie.texbp == 0 ? vram_addr : env->movie.texbp;
            vtIPU_init(&env->movie, env->vram_addr);

            len = env->movie.type == 1 ? vtIPU_getBsTags_buflen(&env->movie) : 11;
            bsTags = vtGetBuf64(len << 4);
            dmaTag[0] = vtGetBuf64(100 * 0x100);
            dmaTag[1] = vtGetBuf64(100 * 0x100);

            len = sizeof(sceIpuRGB32) * (env->movie.width >> 4)  * (env->movie.height >> 4);
            cscBuff[0] = vtGetBuf64(len);
            cscBuff[1] = vtGetBuf64(len);

            vtIPU_setWorkBuff(&env->movie, bsTags, dmaTag[0], dmaTag[1], cscBuff[0], cscBuff[1]);
            vtIPU_mkDmaTagToIPU(&env->movie);
            vtIPU_mkDmaTagOfSendTexVIF(env->movie.dmaTags[0], env->movie.cscBuff[0], &env->movie);
            vtIPU_mkDmaTagOfSendTexVIF(env->movie.dmaTags[1], env->movie.cscBuff[1], &env->movie);

            len = sizeof(sceIpuINDX4) * env->movie.mbx * env->movie.mby;
            env->movie.vqBuff[0] = vtGetBuf64(len);
            env->movie.vqBuff[1] = vtGetBuf64(len);
            break;
    }

    FlushCache(WRITEBACK_DCACHE);
    return env;

}

taroMovieStruct* taroMovieClone(taroMovieStruct *oenv, u32 vram_addr) {
    taroMovieStruct *env = vtGetBuf64(sizeof(taroMovieStruct));
    memset(env, 0, sizeof(taroMovieStruct));
    vtCpMovieStruct(&env->movie, &oenv->movie, vram_addr);
    FlushCache(WRITEBACK_DCACHE);
    return env;
}

void taroExecMovieDecode(s32 movieNo) {
    taroMovieStruct *ptarostruct = vtWaveGlobal.tarostruct[movieNo];
    if (ptarostruct == NULL) {
        return;
    }
    if ((vtWaveGlobal.count == 0 || (vtWaveGlobal.count & 1) == movieNo % 2)) {
        vtIPU_decode(&ptarostruct->movie);
        vtIPU_syncDecode(&ptarostruct->movie);
    }
}

void taroTerminateMovieDecode() {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (vtWaveGlobal.tarostruct[i] != NULL) {
            vtIPU_killDecode(&vtWaveGlobal.tarostruct[i]->movie);
        }
    }
}