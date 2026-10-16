#ifndef __VT_UTIL_H
#define __VT_UTIL_H

#include "common.h"

typedef struct { // 0x50
    /* 0x00 */ void *movie_data_buf[8];
    /* 0x20 */ void *wave_data_buf;
    /* 0x24 */ void *spray_data_buf;
    /* 0x28 */ sceGsTex0 tex0[4];
} vtDataPtr;

extern u128* vtFileRead(char *name);
extern void* vtGetBuf64(u32 size);

#endif