#ifndef __KIT_FIREVU_H
#define __KIT_FIREVU_H

#include "common.h"

extern void kitInitVu1Dma(u128 *p);
extern u128* kitEndVu1Vertex();
extern u128* kitFireGsInitPacket(u128 *p);
extern u128* kitFireEndPacket(u128 *p);
extern u128* kitVu1Initialize(u128 *p, sceVu0FMATRIX m);
extern u128* kitVu1LoadProg(u128 *p, u32 prog_top, u32 size);
extern void kitPushVu1VertexF(f32 v0, f32 v1, f32 v2, f32 v3);
extern void kitPushVu1VertexI(u32 v0, u32 v1, u32 v2, u32 v3);

#endif