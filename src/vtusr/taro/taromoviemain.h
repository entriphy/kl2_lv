#ifndef __TARO_MOVIEMAIN_H
#define __TARO_MOVIEMAIN_H

#include "common.h"
#include "taro_movie.h"

typedef struct { // 0x190
    /* 0x000 */ vtIDEC_MOVIE movie;
    /* 0x088 */ char name[256];
    /* 0x188 */ u32 vram_addr;
} taroMovieStruct;

extern taroMovieStruct* taroMovieInit(void *moviebuff, u32 vram_addr, s32 movieNo);
extern taroMovieStruct* taroMovieClone(taroMovieStruct *oenv, u32 vram_addr);
extern void taroExecMovieDecode(s32 movieNo);
extern void taroTerminateMovieDecode();

#endif