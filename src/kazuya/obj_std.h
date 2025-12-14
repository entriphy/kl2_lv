#ifndef __KZ_OBJSTD_H
#define __KZ_OBJSTD_H

#include "common.h"

typedef struct { // 0x18
    /* 0x00 */ u8 outline;
    /* 0x04 */ s32 obj_no;
    /* 0x08 */ s32 act_no;
    /* 0x0c */ sceVu0FVECTOR *pos;
    /* 0x10 */ sceVu0FVECTOR *rot;
    /* 0x14 */ sceVu0FVECTOR *scale;
} OBJ_STD_INFO;

extern OBJ_STD_INFO *StdObjects[];

extern void kzOST_Init_Light();
extern void kzOST_Draw(OBJWORK *objw);
extern void kzOST_Init(OBJWORK *objw);
extern void kzOST_Main(OBJWORK *objw);
extern void kzOST_Entry(OBJWORK *objw);
extern void kzOST_Setup(s32 obj_no);

#endif