#ifndef __H_FILE_H
#define __H_FILE_H

#include "common.h"

extern s32  hGameDataSize(s32 mode);
extern void hGameRead(s32 mode, void *buff);
extern void hSysDataRead(void *buff);
extern s32  hGameReadOK();
extern s32  hGetDataAddr(s32 i);
extern s32  hGetSysDataAddr(s32 i);

#endif