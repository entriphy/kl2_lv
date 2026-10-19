#ifndef __KIT_WAVEVUPROG_H
#define __KIT_WAVEVUPROG_H

#include "common.h"
#include "vtusr/kit/kitwavemain.h"

extern void kitInitWaveTable(u128 *table);
extern u128* kitMovieAddTex(u128 *packet, kitWaveParam *param);
extern u128* kitWaveSetTexEnv(u128 *packet, kitWaveParam *param);
extern u128* kitWaveSetMatrix(u128 *packet, u128 *m1, u128 *m2, u128 *m3);
extern u128* kitWaveSetVu1Data(u128 *packet, kitWaveParam *param);
extern u128* kitWaveSetWaveTable(u128 *packet, u128 *table);
extern u128* kitWaveSetMicroProg(u128 *packet);
extern void kitMakeLocalMatrix(kitWaveScreenEnv *env);
extern void sceVu0RotCameraMatrix(sceVu0FMATRIX m, sceVu0FVECTOR p, sceVu0FVECTOR zd, sceVu0FVECTOR yd, sceVu0FVECTOR rot);
extern void kitScreenEnvInitialize(kitWaveScreenEnv *env, kitWaveParam *param);
extern u128* kitDrawGrid(u128 *packet, kitWaveScreenEnv *screenenv);
extern u128* kitMovieDraw(u128 *tmp, u32 offx, u32 offy, u32 lx, u32 ly, s32 movieNo);
extern void kitDrawMeshClip(kitWaveScreenEnv *screenenv, kitWaveParam *param);
extern u128* kitTexDraw(u128 *tmp, u32 offx, u32 offy, u32 lx, u32 ly, u64 tex0, u32 u, u32 v, u32 abe, u64 alpha, u64 color);
extern void kitMakeLocalMatrixInv(kitWaveScreenEnv *env);
extern void kitSetCounterParam(kitWaveStruct *env, s32 num);
extern u128* kitDrawWaveHeight(u128 *packet, sceVu0FVECTOR *vec, s32 num);
extern s32 kitGetWaveDrawFlag(s32 num);
extern s32 kitWaveDrawEnable(s32 num);
extern s32 kitWaveDrawDisable(s32 num);
extern u64 kitGetMovieClamp(s32 num);
extern void kitCalcWaveHeight(sceVu0FVECTOR *vec_new, sceVu0FVECTOR *vec_org, s32 num);
extern f32 kitGetWaveHeight(sceVu0FVECTOR *vec);

#endif