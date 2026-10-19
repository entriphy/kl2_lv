#include "vtusr/kit/kitwavevuprog.h"
#include "kit.h"
#include "vtusr/kit/kitwavemain.h"
#include "vtusr/taro/taromoviemain.h"
#include "vtusr/vtwavemain.h"
#include <libgraph.h>

#define KIT_PI 3.1415f

// TODO: change this to kitWaveMicroProg
extern u32 kitFireMicroProgEnd __attribute__((section(".vutext")));
extern u32 kitWaveMicroProgEnd __attribute__((section(".vutext")));

void kitInitWaveTable(u128 *table) {
    kitDMAPACKET *tmp = (kitDMAPACKET *)table;
    s32 i;
    f32 sin_val = 0.024542969f;
    
    for (i = 0; i < 256; i++) {
        tmp->fl[0] = sinf(sin_val * i + (0.01f - rand() * 4.656612873e-10f * 0.01f)) * 1.5f;
        tmp->fl[1] = cosf(sin_val * i + (0.01f - rand() * 4.656612873e-10f * 0.01f)) * 1.5f;
        tmp->fl[2] = (sinf(sin_val * (i + 1)) * 1.5f) - sinf(sin_val * i) * 1.5f;
        tmp->fl[3] = (cosf(sin_val * (i + 1)) * 1.5f) - cosf(sin_val * i) * 1.5f;
        tmp++;
    }
}

// https://decomp.me/scratch/3zNrn
#ifndef NON_MATCHING
INCLUDE_ASM("asm/nonmatchings/vtusr/kit/kitwavevuprog", kitMovieAddTex);
#else
u128* kitMovieAddTex(/* a0 4 */ u128 *packet, /* s2 18 */ kitWaveParam *param) {
    /* s4 20 */ kitDMAPACKET *tmp = (kitDMAPACKET *)packet;
    /* s3 19 */ sceGsTex0 tex0 = *(sceGsTex0 *)&vtWaveGlobal.kitstruct->tex0[1];
    /* s5 21 */ taroMovieStruct *ptarostruct = vtWaveGlobal.tarostruct[6];

    if (!vtWaveGlobal.pause) {
        // do {} while (0);
        // var_v1->kitstruct->tex_ajust_x -= param->multitexspeedx;
        // *(volatile kitWaveStruct *)&vtWaveGlobal.kitstruct;
        vtWaveGlobal.kitstruct->tex_ajust_x -= param->multitexspeedx;
        vtWaveGlobal.kitstruct->tex_ajust_x %= (u32)pow(2.0, ptarostruct->movie.tw) << 4;
        vtWaveGlobal.kitstruct->tex_ajust_z -= param->multitexspeedz;
        vtWaveGlobal.kitstruct->tex_ajust_z %= (u32)pow(2.0, ptarostruct->movie.th) << 4;
    }

    tmp->ul[0] = DMAcnt | 23;
    tmp->ui[2] = SCE_VIF1_SET_NOP(0);
    tmp->ui[3] = SCE_VIF1_SET_DIRECT(23, 0);
    tmp++;

    tmp->ul[0] = SCE_GIF_SET_TAG(
        21,
        SCE_GS_TRUE,
        SCE_GS_TRUE,
        SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_FALSE),
        SCE_GIF_PACKED,
        1
    );
    tmp->ul[1] = SCE_GIF_PACKED_AD;
    tmp++;

    tmp->ad.addr = SCE_GS_FRAME_1;
    tmp->ad.data = SCE_GS_SET_FRAME(ptarostruct->movie.texbp >> 5, ptarostruct->movie.texbw, SCE_GS_PSMCT32, 0xF0000000);
    tmp++;
    tmp->ad.addr = SCE_GS_XYOFFSET_1;
    tmp->ad.data = SCE_GS_SET_XYOFFSET(GS_X_COORD(0), GS_Y_COORD(0));
    tmp++;
    tmp->ad.addr = SCE_GS_SCISSOR_1;
    tmp->ad.data = SCE_GS_SET_SCISSOR(0, (u32)pow(2.0, ptarostruct->movie.tw) - 1, 0, (u32)pow(2.0, ptarostruct->movie.th) - 1);
    tmp++;
    tmp->ad.addr = SCE_GS_TEST_1;
    tmp->ad.data = SCE_GS_SET_TEST(SCE_GS_FALSE, 0, 0, 0, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZALWAYS);
    tmp++;
    tmp->ad.addr = SCE_GS_ZBUF_1;
    tmp->ad.data = SCE_GS_SET_ZBUF(0x8C, SCE_GS_PSMCT16S, 1);
    tmp++;
    tmp->ad.addr = SCE_GS_TEX0_1;
    tmp->ad.data = vtWaveGlobal.kitstruct->tex0[1];
    tmp++;
    tmp->ad.addr = SCE_GS_TEXFLUSH;
    tmp->ad.data = 0;
    tmp++;
    tmp->ad.addr = SCE_GS_TEX1_1;
    tmp->ad.data = SCE_GS_SET_TEX1(0, 0, SCE_GS_LINEAR, SCE_GS_LINEAR, 0, 0, 0);
    tmp++;
    tmp->ad.addr = SCE_GS_CLAMP_1;
    tmp->ad.data = SCE_GS_SET_CLAMP(SCE_GS_REPEAT, SCE_GS_REPEAT, 0, 0, 0, 0);
    tmp++;
    tmp->ad.addr = SCE_GS_ALPHA_1;
    tmp->ad.data = SCE_GS_SET_ALPHA(SCE_GS_BLEND_RGB_SRC, SCE_GS_BLEND_RGB_DST, SCE_GS_BLEND_ALPHA_SRC, SCE_GS_BLEND_RGB_DST, 0x00);
    tmp++;
    tmp->ad.addr = SCE_GS_FBA_1;
    tmp->ad.data = SCE_GS_SET_FBA(0x00);
    tmp++;
    tmp->ad.addr = SCE_GS_RGBAQ;
    tmp->ad.data = SCE_GS_SET_RGBAQ(0x80, 0x80, 0x80, 0x80, 0x00);
    tmp++;
    tmp->ad.addr = SCE_GS_UV;
    tmp->ad.data = SCE_GS_SET_UV(
        ((u32)pow(2.0, ptarostruct->movie.tw) << 4) + 8 + vtWaveGlobal.kitstruct->tex_ajust_x,
        ((u32)pow(2.0, ptarostruct->movie.th) << 4) + 8 + vtWaveGlobal.kitstruct->tex_ajust_z
    );
    tmp++;
    tmp->ad.addr = SCE_GS_XYZ3;
    tmp->ad.data = SCE_GS_SET_XYZ(GS_X_COORD(0), GS_Y_COORD(0), 0);
    tmp++;
    tmp->ad.addr = SCE_GS_UV;
    tmp->ad.data = SCE_GS_SET_UV(
        ((u32)pow(2.0, ptarostruct->movie.tw) << 4) + ((u32)pow(2.0, tex0.TW) << 4) + 8 + vtWaveGlobal.kitstruct->tex_ajust_x,
        ((u32)pow(2.0, ptarostruct->movie.th) << 4) + ((u32)pow(2.0, tex0.TH) << 4) + 8 + vtWaveGlobal.kitstruct->tex_ajust_z
    );
    tmp++;
    tmp->ad.addr = SCE_GS_XYZ2;
    tmp->ad.data = SCE_GS_SET_XYZ(((u32)pow(2.0, ptarostruct->movie.tw) + (GS_X_COORD(0) >> 4)) << 4, ((u32)pow(2.0, ptarostruct->movie.th) + (GS_Y_COORD(0) >> 4)) << 4, 0);
    tmp++;
    tmp->ad.addr = SCE_GS_TEST_1;
    tmp->ad.data = SCE_GS_SET_TEST(SCE_GS_FALSE, 0, 0, 0, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZGREATER);
    tmp++;
    tmp->ad.addr = SCE_GS_FRAME_1;
    tmp->ad.data = SCE_GS_SET_FRAME(vtWaveGlobal.fr & 1 ? 0x00 : 0x46, 10, SCE_GS_PSMCT32, 0xF0000000);
    tmp++;
    tmp->ad.addr = SCE_GS_XYOFFSET_1;
    tmp->ad.data = SCE_GS_SET_XYOFFSET(GS_X_COORD(0), !(vtWaveGlobal.odev & 1) ? GS_Y_COORD(0) + 8 : GS_Y_COORD(0));
    tmp++;
    tmp->ad.addr = SCE_GS_SCISSOR_1;
    tmp->ad.data = SCE_GS_SET_SCISSOR(0, SCR_WIDTH - 1, 0, SCR_HEIGHT - 1);
    tmp++;
    tmp->ad.addr = SCE_GS_ZBUF_1;
    tmp->ad.data = SCE_GS_SET_ZBUF(0x8C, SCE_GS_PSMCT16S, 0);
    tmp++;
    tmp->ad.addr = SCE_GS_TEXFLUSH;
    tmp->ad.data = 0;
    tmp++;

    return (u128 *)tmp;
}
#endif

u128* kitWaveSetTexEnv(u128 *packet, kitWaveParam *param) {
    kitDMAPACKET *tmp = (kitDMAPACKET *)packet;

    tmp->ul[0] = DMAcnt | 7;
    tmp->ui[2] = SCE_VIF1_SET_NOP(0);
    tmp->ui[3] = SCE_VIF1_SET_DIRECT(7, 0);
    tmp++;

    tmp->ul[0] = SCE_GIF_SET_TAG(6, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1);
    tmp->ul[1] = SCE_GIF_PACKED_AD;
    tmp++;

    tmp->ad.addr = SCE_GS_TEXFLUSH;
    tmp->ad.data = 0;
    tmp++;
    tmp->ad.addr = SCE_GS_TEX1_1;
    tmp->ad.data = SCE_GS_SET_TEX1(0, 0, SCE_GS_LINEAR, SCE_GS_LINEAR, 0, 0, 0);
    tmp++;
    tmp->ad.addr = SCE_GS_CLAMP_1;
    tmp->ad.data = SCE_GS_SET_CLAMP(SCE_GS_REPEAT, SCE_GS_REPEAT, 0, 0, 0, 0);
    tmp++;
    tmp->ad.addr = SCE_GS_ALPHA_1;
    tmp->ad.data = SCE_GS_SET_ALPHA(SCE_GS_BLEND_RGB_SRC, SCE_GS_BLEND_RGB_DST, SCE_GS_BLEND_ALPHA_SRC, SCE_GS_BLEND_RGB_DST, 0x00);
    tmp++;
    tmp->ad.addr = SCE_GS_FBA_1;
    tmp->ad.data = SCE_GS_SET_FBA(0x00);
    tmp++;
    tmp->ad.addr = SCE_GS_FOGCOL;
    tmp->ad.data = SCE_GS_SET_FOGCOL(param->fogcol[0] * 255.0f, param->fogcol[1] * 255.0f, param->fogcol[2] * 255.0f);
    tmp++;

    return (u128 *)tmp;
}

u128* kitWaveSetMatrix(u128 *packet, u128 *m1, u128 *m2, u128 *m3) {
    kitDMAPACKET *tmp = (kitDMAPACKET *)packet;

    tmp->ul[0] = DMAcnt | 1;
    tmp->ui[2] = SCE_VIF1_SET_FLUSH(0);
    tmp->ui[3] = SCE_VIF1_SET_NOP(0);
    tmp++;
    tmp->ui[0] = SCE_VIF1_SET_STMOD(0, 0);
    tmp->ui[1] = SCE_VIF1_SET_NOP(0);
    tmp->ui[2] = SCE_VIF1_SET_STMASK(0);
    tmp->ui[3] = SCE_VIF1_SET_NOP(0);
    tmp++;

    tmp->ul[0] = DMAcnt | 12;
    tmp->ui[2] = SCE_VIF1_SET_STCYCL(4, 4, 0);
    tmp->ui[3] = SCE_VIF1_SET_UNPACK(0x00, 12, VIF_UNPACK_V4_32, 0);
    tmp++;
    tmp->ul128 = m1[0]; tmp++;
    tmp->ul128 = m1[1]; tmp++;
    tmp->ul128 = m1[2]; tmp++;
    tmp->ul128 = m1[3]; tmp++;
    tmp->ul128 = m2[0]; tmp++;
    tmp->ul128 = m2[1]; tmp++;
    tmp->ul128 = m2[2]; tmp++;
    tmp->ul128 = m2[3]; tmp++;
    tmp->ul128 = m3[0]; tmp++;
    tmp->ul128 = m3[1]; tmp++;
    tmp->ul128 = m3[2]; tmp++;
    tmp->ul128 = m3[3]; tmp++;
    
    return (u128 *)tmp;
}

u128* kitWaveSetVu1Data(u128 *packet, kitWaveParam *param) {
   s32 i;
    kitDMAPACKET *tmp = (kitDMAPACKET *)packet;
    taroMovieStruct *ptarostruct = vtWaveGlobal.tarostruct[6];
    f32 radius1 = vtWaveGlobal.kitstruct->radiusx;
    f32 radius2 = vtWaveGlobal.kitstruct->radiusz;
    f32 countx = vtWaveGlobal.kitstruct->countx;
    f32 countz = vtWaveGlobal.kitstruct->countz;
    f32 *tex_scroll_x = &vtWaveGlobal.kitstruct->tex_scroll_x[vtWaveGlobal.kitstruct->current];
    f32 *tex_scroll_z = &vtWaveGlobal.kitstruct->tex_scroll_z[vtWaveGlobal.kitstruct->current];
    
    if (!vtWaveGlobal.pause) {
        *tex_scroll_x -= param->basetexspeedx;
        *tex_scroll_z -= param->basetexspeedz;
        *tex_scroll_x = *tex_scroll_x > 1.0f ? *tex_scroll_x - 1.0f : *tex_scroll_x;
        *tex_scroll_x = *tex_scroll_x < 0.0f ? *tex_scroll_x + 1.0f : *tex_scroll_x;
        *tex_scroll_z = *tex_scroll_z > 1.0f ? *tex_scroll_z - 1.0f : *tex_scroll_z;
        *tex_scroll_z = *tex_scroll_z < 0.0f ? *tex_scroll_z + 1.0f : *tex_scroll_z;
    }

    tmp->ul[0] = DMAcnt | 25;
    tmp->ui[2] = SCE_VIF1_SET_NOP(0);
    tmp->ui[3] = SCE_VIF1_SET_UNPACK(0x0C, 25, VIF_UNPACK_V4_32, 0);
    tmp++;
    for (i = 1; i < 8; i++) {
        tmp->fl[0] = 0.1f / i;
        tmp->fl[1] = 0.0f;
        tmp->fl[2] = 0.1f / i;
        tmp->fl[3] = 0.1f / i / 2;
        tmp++;
    }
    tmp->ui[0] = 19;
    tmp->fl[3] = 256.0f;
    tmp++;
    tmp->ui[0] = 43;
    tmp->fl[3] = 1536.0f;
    tmp++;
    tmp->ui[0] = 79;
    tmp->fl[3] = 2048.0f;
    tmp++;
    tmp->fl[3] = 8192.0f;
    tmp++;
    tmp->fl[0] = -param->texajust;
    tmp->fl[1] = -param->texajust;
    tmp->fl[2] = 1.0f;
    tmp->fl[3] = 1.0f;
    tmp++;
    tmp->fl[2] = 0.796875;
    tmp->fl[3] = -216.75f;
    tmp++;
    tmp->fl[0] = radius1 * 2.0f * param->height * 2.0f;
    tmp->fl[1] = 1.0f / (tmp->fl[0] * tmp->fl[0]);
    tmp->fl[2] = -(f32)param->headtexval;
    tmp->fl[3] = 128.0f;
    tmp++;
    tmp->fl[0] = param->height;
    tmp->fl[1] = KIT_PI * 2.0f;
    tmp->fl[2] = 1.0f / (KIT_PI * 2.0f);
    tmp->fl[3] = KIT_PI / 2.0f;
    tmp++;
    tmp->fl[0] = 1608.0f;
    tmp->fl[1] = 1886.0f;
    tmp->fl[2] = 2488.0f;
    tmp->fl[3] = 2230.0f;
    tmp++;
    tmp->ui[0] = 512;
    tmp++;
    tmp->ui[0] = 704;
    tmp->fl[1] = param->meshsizex;
    tmp->fl[2] = param->meshsizez;
    tmp->fl[3] = 0.0f;
    tmp++;
    tmp->fl[0] = radius2;
    tmp->fl[1] = param->intervalx;
    tmp->fl[2] = radius1;
    tmp->fl[3] = param->intervalz;
    tmp++;
    tmp->ui[0] = param->lod;
    tmp->ui[1] = vtWaveGlobal.kitstruct->x_mesh;
    tmp->ui[2] = vtWaveGlobal.kitstruct->z_mesh;
    tmp->ui[3] = 0x8000;
    tmp++;
    tmp->fl[0] = 0.0f;
    tmp->fl[1] = KIT_PI * 2.0f;
    tmp->fl[2] = 1.0f / (KIT_PI * 2.0f);
    tmp->fl[3] = -256.0f;
    tmp++;
    tmp->fl[0] = countx;
    tmp->fl[1] = countz;
    tmp++;
    tmp->fl[0] = vtWaveGlobal.kitstruct->cbase[0];
    tmp->fl[1] = 0.0f;
    tmp->fl[2] = vtWaveGlobal.kitstruct->cbase[2];
    tmp->fl[3] = 1.0f;
    tmp++;
    tmp->fl[0] = 0.0f;
    tmp->fl[1] = 1.0f / (param->ajust_h_near - param->ajust_h_far);
    tmp->fl[2] = param->ajust_h_far;
    if (!param->heightajust) {
        tmp->fl[3] = 0.0f;
    } else {
        tmp->fl[3] = param->ajust_h_val;
    }
    tmp++;
    tmp->fl[0] = *tex_scroll_x;
    tmp->fl[1] = *tex_scroll_z;
    tmp->fl[2] = 0.0f;
    tmp->fl[3] = 0.0f;
    tmp++;

    tmp->ul[0] = DMAcnt | 7;
    tmp->ui[2] = SCE_VIF1_SET_NOP(0);
    tmp->ui[3] = SCE_VIF1_SET_UNPACK(0x200, 7, VIF_UNPACK_V4_32, 0);
    tmp++;
    tmp->ul[0] = SCE_GIF_SET_TAG(5, SCE_GS_FALSE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1);
    tmp->ul[1] = SCE_GIF_PACKED_AD;
    tmp++;
    switch (param->basetex) {
        case 2:
            tmp->ad.addr = SCE_GS_TEX0_1;
            tmp->ad.data = SCE_GS_SET_TEX0(ptarostruct->movie.texbp, ptarostruct->movie.texbw, SCE_GS_PSMCT32, ptarostruct->movie.tw, ptarostruct->movie.th, SCE_GS_TRUE, SCE_GS_MODULATE, 0, 0, 0, 0, 0);
            break;
        case 1:
            tmp->ad.addr = SCE_GS_TEX0_1;
            tmp->ad.data = vtWaveGlobal.kitstruct->tex0[2];
            break;
        case 0:
            tmp->ad.addr = SCE_GS_RGBAQ;
            tmp->ad.data = SCE_GS_SET_RGBAQ(0x00, 0x00, 0x00, 0x00, 0x00);
            break;
    }
    tmp++;
    tmp->ad.addr = SCE_GS_TEXFLUSH;
    tmp->ad.data = 0;
    tmp++;
    tmp->ad.addr = SCE_GS_TEST_1;
    tmp->ad.data = SCE_GS_SET_TEST(SCE_GS_FALSE, 0, 0, 0, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZGREATER);
    tmp++;
    tmp->ad.addr = SCE_GS_ALPHA_1;
    tmp->ad.data = SCE_GS_SET_ALPHA(SCE_GS_BLEND_RGB_SRC, SCE_GS_BLEND_RGB_DST, SCE_GS_BLEND_ALPHA_FIX, SCE_GS_BLEND_RGB_DST, (u32)(param->alphablend * 128.0f));
    tmp++;
    tmp->ad.addr = SCE_GS_CLAMP_1;
    tmp->ad.data = kitGetMovieClamp(param->basetexarea);
    tmp++;
    tmp->ul[0] = SCE_GIF_SET_TAG(
        0,
        1 - param->headtex,
        SCE_GS_TRUE,
        SCE_GS_SET_PRIM(param->prim, SCE_GS_TRUE, param->basetex ? SCE_GS_TRUE : SCE_GS_FALSE, param->fog, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE),
        SCE_GIF_PACKED,
        3
    );
    tmp->ul[1] = SCE_GS_ST | SCE_GS_RGBAQ << 4 | SCE_GS_XYZF2 << 8;
    tmp++;
    
    tmp->ul[0] = DMAcnt | 7;
    tmp->ui[2] = SCE_VIF1_SET_NOP(0);
    tmp->ui[3] = SCE_VIF1_SET_UNPACK(0x213, 7, VIF_UNPACK_V4_32, 0);
    tmp++;
    tmp->ul[0] = SCE_GIF_SET_TAG(5, SCE_GS_FALSE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1);
    tmp->ul[1] = SCE_GIF_PACKED_AD;
    tmp++;
    tmp->ad.addr = SCE_GS_TEX0_1;
    tmp->ad.data = vtWaveGlobal.kitstruct->tex0[0];
    tmp++;
    tmp->ad.addr = SCE_GS_TEXFLUSH;
    tmp->ad.data = 0;
    tmp++;
    tmp->ad.addr = SCE_GS_TEST_1;
    tmp->ad.data = SCE_GS_SET_TEST(SCE_GS_FALSE, 0, 0, 0, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZGEQUAL);
    tmp++;
    tmp->ad.addr = SCE_GS_ALPHA_1;
    tmp->ad.data = SCE_GS_SET_ALPHA(SCE_GS_BLEND_RGB_SRC, SCE_GS_BLEND_RGB_DST, SCE_GS_BLEND_ALPHA_SRC, SCE_GS_BLEND_RGB_DST, 0);
    tmp++;
    tmp->ad.addr = SCE_GS_CLAMP_1;
    tmp->ad.data = SCE_GS_SET_CLAMP(SCE_GS_REPEAT, SCE_GS_REPEAT, 0, 0, 0, 0);
    tmp++;
    tmp->ul[0] = SCE_GIF_SET_TAG(
        0,
        SCE_GS_TRUE,
        SCE_GS_TRUE,
        SCE_GS_SET_PRIM(param->prim, SCE_GS_TRUE, SCE_GS_TRUE, param->fog, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE),
        SCE_GIF_PACKED,
        3
    );
    tmp->ul[1] = SCE_GS_ST | SCE_GS_RGBAQ << 4 | SCE_GS_XYZF2 << 8;
    tmp++;

    tmp->ul[0] = DMAcnt | 7;
    tmp->ui[2] = SCE_VIF1_SET_NOP(0);
    tmp->ui[3] = SCE_VIF1_SET_UNPACK(0x2C0, 7, VIF_UNPACK_V4_32, 0);
    tmp++;
    tmp->ul[0] = SCE_GIF_SET_TAG(5, SCE_GS_FALSE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1);
    tmp->ul[1] = SCE_GIF_PACKED_AD;
    tmp++;
    switch (param->basetex) {
        case 2:
            tmp->ad.addr = SCE_GS_TEX0_1;
            tmp->ad.data = SCE_GS_SET_TEX0(ptarostruct->movie.texbp, ptarostruct->movie.texbw, SCE_GS_PSMCT32, ptarostruct->movie.tw, ptarostruct->movie.th, SCE_GS_TRUE, SCE_GS_MODULATE, 0, 0, 0, 0, 0);
            break;
        case 1:
            tmp->ad.addr = SCE_GS_TEX0_1;
            tmp->ad.data = vtWaveGlobal.kitstruct->tex0[2];
            break;
        case 0:
            tmp->ad.addr = SCE_GS_RGBAQ;
            tmp->ad.data = SCE_GS_SET_RGBAQ(0x00, 0x00, 0x00, 0x00, 0x00);
            break;
    }
    tmp++;
    tmp->ad.addr = SCE_GS_TEXFLUSH;
    tmp->ad.data = 0;
    tmp++;
    tmp->ad.addr = SCE_GS_TEST_1;
    tmp->ad.data = SCE_GS_SET_TEST(SCE_GS_FALSE, 0, 0, 0, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZGREATER);
    tmp++;
    tmp->ad.addr = SCE_GS_ALPHA_1;
    tmp->ad.data = SCE_GS_SET_ALPHA(SCE_GS_BLEND_RGB_SRC, SCE_GS_BLEND_RGB_DST, SCE_GS_BLEND_ALPHA_FIX, SCE_GS_BLEND_RGB_DST, (u32)(param->alphablend * 128.0f));
    tmp++;
    tmp->ad.addr = SCE_GS_CLAMP_1;
    tmp->ad.data = kitGetMovieClamp(param->basetexarea);
    tmp++;
    tmp->ul[0] = SCE_GIF_SET_TAG(
        0,
        1 - param->headtex,
        SCE_GS_TRUE,
        SCE_GS_SET_PRIM(param->prim, SCE_GS_TRUE, param->basetex ? SCE_GS_TRUE : SCE_GS_FALSE, param->fog, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE),
        SCE_GIF_PACKED,
        3
    );
    tmp->ul[1] = SCE_GS_ST | SCE_GS_RGBAQ << 4 | SCE_GS_XYZF2 << 8;
    tmp++;

    tmp->ul[0] = DMAcnt | 7;
    tmp->ui[2] = SCE_VIF1_SET_NOP(0);
    tmp->ui[3] = SCE_VIF1_SET_UNPACK(0x2D3, 7, VIF_UNPACK_V4_32, 0);
    tmp++;
    tmp->ul[0] = SCE_GIF_SET_TAG(5, SCE_GS_FALSE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1);
    tmp->ul[1] = SCE_GIF_PACKED_AD;
    tmp++;
    tmp->ad.addr = SCE_GS_TEX0_1;
    tmp->ad.data = vtWaveGlobal.kitstruct->tex0[0];
    tmp++;
    tmp->ad.addr = SCE_GS_TEXFLUSH;
    tmp->ad.data = 0;
    tmp++;
    tmp->ad.addr = SCE_GS_TEST_1;
    tmp->ad.data = SCE_GS_SET_TEST(SCE_GS_FALSE, 0, 0, 0, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZGEQUAL);
    tmp++;
    tmp->ad.addr = SCE_GS_ALPHA_1;
    tmp->ad.data = SCE_GS_SET_ALPHA(SCE_GS_BLEND_RGB_SRC, SCE_GS_BLEND_RGB_DST, SCE_GS_BLEND_ALPHA_SRC, SCE_GS_BLEND_RGB_DST, 0);
    tmp++;
    tmp->ad.addr = SCE_GS_CLAMP_1;
    tmp->ad.data = SCE_GS_SET_CLAMP(SCE_GS_REPEAT, SCE_GS_REPEAT, 0, 0, 0, 0);
    tmp++;
    tmp->ul[0] = SCE_GIF_SET_TAG(
        0,
        SCE_GS_TRUE,
        SCE_GS_TRUE,
        SCE_GS_SET_PRIM(param->prim, SCE_GS_TRUE, SCE_GS_TRUE, param->fog, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE),
        SCE_GIF_PACKED,
        3
    );
    tmp->ul[1] = SCE_GS_ST | SCE_GS_RGBAQ << 4 | SCE_GS_XYZF2 << 8;
    tmp++;

    return (u128 *)tmp;
}

u128* kitWaveSetWaveTable(u128 *packet, u128 *table) {
    kitDMAPACKET *tmp = (kitDMAPACKET *)packet;

    tmp->ul[0] = DMAref | 0x80 | (u64)table << 32;
    tmp->ui[2] = SCE_VIF1_SET_NOP(0);
    tmp->ui[3] = SCE_VIF1_SET_UNPACK(0x50, 0x80, VIF_UNPACK_V4_32, 0);
    tmp++;
    table += 0x80;
    tmp->ul[0] = DMAref | 0x80 | (u64)table << 32;
    tmp->ui[2] = SCE_VIF1_SET_NOP(0);
    tmp->ui[3] = SCE_VIF1_SET_UNPACK(0xD0, 0x80, VIF_UNPACK_V4_32, 0);
    tmp++;

    return (u128 *)tmp;
}

u128* kitWaveSetMicroProg(u128 *packet) {
    kitDMAPACKET *tmp = (kitDMAPACKET *)packet;
    u32 size = ((u32)&kitWaveMicroProgEnd - (u32)&kitFireMicroProgEnd);
    size = (size / 16) + 1;

    tmp->ul[0] = DMAref | size | (u64)&kitFireMicroProgEnd << 32;
    tmp->ui[2] = SCE_VIF1_SET_NOP(0);
    tmp->ui[3] = SCE_VIF1_SET_FLUSH(0);
    tmp++;
    tmp->ul[0] = DMAcnt | 0;
    tmp->ui[2] = SCE_VIF1_SET_MSCALF(0, 0);
    tmp->ui[3] = SCE_VIF1_SET_FLUSH(0);
    tmp++;

    return (u128 *)tmp;
}

void kitMakeLocalMatrix(kitWaveScreenEnv *env) {
    sceVu0FMATRIX work;

    sceVu0MulMatrix(work, env->world_view, env->local_world);
    sceVu0CopyMatrix(env->local_view, work);
    sceVu0CopyMatrix(env->view_screen, GameGbl.vsm);
    sceVu0MulMatrix(env->local_screen, GameGbl.vsm, work);
}

void sceVu0RotCameraMatrix(sceVu0FMATRIX m, sceVu0FVECTOR p, sceVu0FVECTOR zd, sceVu0FVECTOR yd, sceVu0FVECTOR rot) {
    sceVu0FMATRIX work;
    sceVu0FVECTOR direction;
    sceVu0FVECTOR vertical;
    sceVu0FVECTOR position;

    sceVu0UnitMatrix(work);
    sceVu0RotMatrixX(work, work, rot[0]);
    sceVu0RotMatrixY(work, work, rot[1]);
    sceVu0RotMatrixZ(work, work, rot[2]);
    sceVu0ApplyMatrix(direction, work, zd);
    sceVu0ApplyMatrix(vertical, work, yd);
    sceVu0ApplyMatrix(position, work, p);
    sceVu0CameraMatrix(m, position, direction, vertical);
}

void kitScreenEnvInitialize(kitWaveScreenEnv *env, kitWaveParam *param) {
    sceVu0FMATRIX work;
    sceVu0FMATRIX work2;
    sceVu0FVECTOR work_light0;
    sceVu0FVECTOR work_light1;
    sceVu0FVECTOR work_light2;

    COPY128(env->obj_trans, param->trans);
    COPY128(env->obj_rot, param->rot);
    sceVu0UnitMatrix(work);
    sceVu0RotMatrix(env->local_world, work, env->obj_rot);
    SETVEC(env->light_rot, 0.0f, 0.0f, 0.0f, 0.0f);
    sceVu0UnitMatrix(work2);
    sceVu0RotMatrixX(work2, work2, env->light_rot[0]);
    sceVu0RotMatrixY(work2, work2, env->light_rot[1]);
    sceVu0RotMatrixZ(work2, work2, env->light_rot[2]);
    COPY128(env->light0, param->light0);
    COPY128(env->light1, param->light1);
    COPY128(env->light2, param->light2);
    sceVu0ApplyMatrix(work_light0, work2, env->light0);
    sceVu0ApplyMatrix(work_light1, work2, env->light1);
    sceVu0ApplyMatrix(work_light2, work2, env->light2);
    sceVu0NormalLightMatrix(env->normal_light, work_light0, work_light1, work_light2);
    env->normal_light[3][3] = 1.0f;
    COPY128(env->color0, param->color0);
    COPY128(env->color1, param->color1);
    COPY128(env->color2, param->color2);
    COPY128(env->ambient, param->ambient);
    sceVu0LightColorMatrix(env->light_color, env->color0, env->color1, env->color2, env->ambient);
    sceVu0MulMatrix(env->local_light, env->normal_light, env->local_world);
    sceVu0TransMatrix(env->local_world, env->local_world, env->obj_trans);
    sceVu0CopyMatrix(env->view_screen, GameGbl.vsm);
}

u128* kitDrawGrid(u128 *packet, kitWaveScreenEnv *screenenv) {
    kitDMAPACKET *tmp = (kitDMAPACKET *)packet;
    sceVu0FVECTOR rr;
    sceVu0FVECTOR gg;
    sceVu0FVECTOR bb;
    sceVu0FVECTOR orgg;
    sceVu0IVECTOR r;
    sceVu0IVECTOR g;
    sceVu0IVECTOR b;
    sceVu0IVECTOR org;
    sceVu0FMATRIX m1;
    sceVu0FMATRIX m2;

    sceVu0UnitMatrix(m1);
    sceVu0UnitMatrix(m2);

    sceVu0TransMatrix(m1, m1, screenenv->obj_trans);
    sceVu0MulMatrix(m1, screenenv->world_view, m1);
    sceVu0MulMatrix(m1, GameGbl.vsm, m1);

    SETVEC(orgg, 0.0f, 0.0f, 0.0f, 1.0f);
    SETVEC(rr, 300.0f, 0.0f, 0.0f, 1.0f);
    SETVEC(gg, 0.0f, 300.0f, 0.0f, 1.0f);
    SETVEC(bb, 0.0f, 0.0f, 300.0f, 1.0f);

    tmp->ul[0] = DMAcnt | 10;
    tmp->ui[2] = SCE_VIF1_SET_FLUSH(0);
    tmp->ui[3] = SCE_VIF1_SET_DIRECT(10, 0);
    tmp++;

    sceVu0ApplyMatrix(orgg, m1, orgg);
    sceVu0ApplyMatrix(rr, m1, rr);
    sceVu0ApplyMatrix(gg, m1, gg);
    sceVu0ApplyMatrix(bb, m1, bb);

    orgg[3] = 1.0f / orgg[3];
    rr[3] = 1.0f / rr[3];
    gg[3] = 1.0f / gg[3];
    bb[3] = 1.0f / bb[3];

    orgg[0] *= orgg[3];
    orgg[1] *= orgg[3];
    orgg[2] *= orgg[3];
    rr[0] *= rr[3];
    rr[1] *= rr[3];
    rr[2] *= rr[3];
    gg[0] *= gg[3];
    gg[1] *= gg[3];
    gg[2] *= gg[3];
    bb[0] *= bb[3];
    bb[1] *= bb[3];
    bb[2] *= bb[3];

    sceVu0FTOI4Vector(org, orgg);
    org[2] >>= 4;
    sceVu0FTOI4Vector(r, rr);
    r[2] >>= 4;
    sceVu0FTOI4Vector(g, gg);
    g[2] >>= 4;
    sceVu0FTOI4Vector(b, bb);
    b[2] >>= 4;

    tmp->ul[0] = SCE_GIF_SET_TAG(
        9,
        SCE_GS_TRUE,
        SCE_GS_TRUE,
        SCE_GS_SET_PRIM(SCE_GS_PRIM_LINE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE),
        SCE_GIF_PACKED,
        1
    );
    tmp->ul[1] = SCE_GIF_PACKED_AD;
    tmp++;

    tmp->ad.addr = SCE_GS_RGBAQ;
    tmp->ad.data = SCE_GS_SET_RGBAQ(0xFF, 0x00, 0x00, 0x00, 0x00);
    tmp++;
    tmp->ad.addr = SCE_GS_XYZ3;
    tmp->ad.data = SCE_GS_SET_XYZ(org[0], org[1], org[2]);
    tmp++;
    tmp->ad.addr = SCE_GS_XYZ2;
    tmp->ad.data = SCE_GS_SET_XYZ(r[0], r[1], r[2]);
    tmp++;
    tmp->ad.addr = SCE_GS_RGBAQ;
    tmp->ad.data = SCE_GS_SET_RGBAQ(0x00, 0xFF, 0x00, 0x00, 0x00);
    tmp++;
    tmp->ad.addr = SCE_GS_XYZ3;
    tmp->ad.data = SCE_GS_SET_XYZ(org[0], org[1], org[2]);
    tmp++;
    tmp->ad.addr = SCE_GS_XYZ2;
    tmp->ad.data = SCE_GS_SET_XYZ(g[0], g[1], g[2]);
    tmp++;
    tmp->ad.addr = SCE_GS_RGBAQ;
    tmp->ad.data = SCE_GS_SET_RGBAQ(0x00, 0x00, 0xFF, 0x00, 0x00);
    tmp++;
    tmp->ad.addr = SCE_GS_XYZ3;
    tmp->ad.data = SCE_GS_SET_XYZ(org[0], org[1], org[2]);
    tmp++;
    tmp->ad.addr = SCE_GS_XYZ2;
    tmp->ad.data = SCE_GS_SET_XYZ(b[0], b[1], b[2]);
    tmp++;

    return (u128 *)tmp;
}

u128* kitMovieDraw(u128 *tmp, u32 offx, u32 offy, u32 lx, u32 ly, s32 movieNo) {
    kitADDR_DATA *draw_packet = (kitADDR_DATA *)tmp;
    kitDMAPACKET *tmp2 = (kitDMAPACKET *)tmp;

    if (vtWaveGlobal.tarostruct[movieNo] == NULL) {
        return tmp;
    }

    tmp2->ul[0] = DMAcnt | 11;
    tmp2->ui[2] = SCE_VIF1_SET_FLUSH(0);
    tmp2->ui[3] = SCE_VIF1_SET_DIRECT(11, 0);
    draw_packet++;

    draw_packet->data = SCE_GIF_SET_TAG(
        10,
        SCE_GS_TRUE,
        SCE_GS_TRUE,
        SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_FALSE),
        SCE_GIF_PACKED,
        1
    );
    draw_packet->addr = SCE_GIF_PACKED_AD;
    draw_packet++;

    draw_packet->addr = SCE_GS_TEST_1;
    draw_packet->data = SCE_GS_SET_TEST(SCE_GS_FALSE, 0, 0, 0, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZALWAYS);
    draw_packet++;
    draw_packet->addr = SCE_GS_TEX0_1;
    draw_packet->data = SCE_GS_SET_TEX0(
        vtWaveGlobal.tarostruct[movieNo]->movie.texbp,
        vtWaveGlobal.tarostruct[movieNo]->movie.texbw,
        SCE_GS_PSMCT32,
        vtWaveGlobal.tarostruct[movieNo]->movie.tw,
        vtWaveGlobal.tarostruct[movieNo]->movie.th,
        SCE_GS_TRUE,
        SCE_GS_TRUE,
        0x0000,
        0,
        0,
        0,
        0
    );
    draw_packet++;
    draw_packet->addr = SCE_GS_TEXFLUSH;
    draw_packet->data = 0;
    draw_packet++;
    draw_packet->addr = SCE_GS_TEX1_1;
    draw_packet->data = SCE_GS_SET_TEX1(0, 0, SCE_GS_LINEAR, SCE_GS_LINEAR, 0, 0, 0);
    draw_packet++;
    draw_packet->addr = SCE_GS_CLAMP_1;
    draw_packet->data = SCE_GS_SET_CLAMP(SCE_GS_REPEAT, SCE_GS_REPEAT, 0, 0, 0, 0);
    draw_packet++;
    draw_packet->addr = SCE_GS_UV;
    draw_packet->data = SCE_GS_SET_UV(8, 8);
    draw_packet++;
    draw_packet->addr = SCE_GS_XYZ3;
    draw_packet->data = SCE_GS_SET_XYZ(offx, offy, 0xFFFFFF);
    draw_packet++;
    draw_packet->addr = SCE_GS_UV;
    draw_packet->data = SCE_GS_SET_UV((u32)pow(2.0, vtWaveGlobal.tarostruct[movieNo]->movie.tw) * 16 + 8, (u32)pow(2.0, vtWaveGlobal.tarostruct[movieNo]->movie.th) * 16 + 8);
    draw_packet++;
    draw_packet->addr = SCE_GS_XYZ2;
    draw_packet->data = SCE_GS_SET_XYZ(offx + lx, offy + ly, 0xFFFFFF);
    draw_packet++;
    draw_packet->addr = SCE_GS_TEST_1;
    draw_packet->data = SCE_GS_SET_TEST(SCE_GS_FALSE, 0, 0, 0, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZGREATER);
    draw_packet++;

    return (u128 *)draw_packet;
}

void kitDrawMeshClip(kitWaveScreenEnv *screenenv, kitWaveParam *param) {
    s32 i;
    s32 j;
    sceVu0FMATRIX m2;
    f32 x_mesh_min;
    f32 x_mesh_max;
    f32 z_mesh_min;
    f32 z_mesh_max;
    f32 x;
    sceVu0FVECTOR v_tmp[2];
    sceVu0FVECTOR v_max;
    sceVu0FVECTOR v_min;
    sceVu0FVECTOR cmax;
    sceVu0FVECTOR cmin;
    sceVu0FVECTOR cbbox[8];

    v_tmp[0][0] = param->planesizex;
    v_tmp[0][1] = 0.0f;
    v_tmp[0][2] = param->planesizez;
    v_tmp[0][3] = 1.0f; // IMPORTANT: this has be here to load 1.0 into a register early
    v_tmp[1][0] = -param->planesizex;
    v_tmp[1][1] = 0.0f;
    v_tmp[1][2] = -param->planesizez;
    v_tmp[0][3] = 1.0f;
    v_tmp[1][3] = 1.0f;
    
    v_max[0] = v_tmp[1][0] < v_tmp[0][0] ? v_tmp[0][0] : v_tmp[1][0];
    v_max[2] = v_tmp[0][2] > v_tmp[1][2] ? v_tmp[0][2] : v_tmp[1][2];
    v_min[0] = v_tmp[0][0] < v_tmp[1][0] ? v_tmp[0][0] : v_tmp[1][0];
    v_min[2] = v_tmp[0][2] < v_tmp[1][2] ? v_tmp[0][2] : v_tmp[1][2];

    sceVu0UnitMatrix(m2);

    cbbox[0][0] = 1000.0f;
    cbbox[0][1] = 1000.0f;
    cbbox[0][2] = 800.0f;
    cbbox[0][3] = 1.0f;
    cbbox[1][0] = -1000.0f;
    cbbox[1][1] = 1000.0f;
    cbbox[1][2] = 800.0f;
    cbbox[1][3] = 1.0f;
    cbbox[2][0] = -1000.0f;
    cbbox[2][1] = -1000.0f;
    cbbox[2][2] = 800.0f;
    cbbox[2][3] = 1.0f;
    cbbox[3][0] = 1000.0f;
    cbbox[3][1] = -1000.0f;
    cbbox[3][2] = 800.0f;
    cbbox[3][3] = 1.0f;
    cbbox[4][0] = 4000.0f;
    cbbox[4][1] = 4000.0f;
    cbbox[4][2] = 20000.0f;
    cbbox[4][3] = 1.0f;
    cbbox[5][0] = -4000.0f;
    cbbox[5][1] = 4000.0f;
    cbbox[5][2] = 20000.0f;
    cbbox[5][3] = 1.0f;
    cbbox[6][0] = -4000.0f;
    cbbox[6][1] = -4000.0f;
    cbbox[6][2] = 20000.0f;
    cbbox[6][3] = 1.0f;
    cbbox[7][0] = 4000.0f;
    cbbox[7][1] = -4000.0f;
    cbbox[7][2] = 20000.0f;
    cbbox[7][3] = 1.0f;

    for (i = 0; i < 8; i++) {
        sceVu0ApplyMatrix(cbbox[i], screenenv->view_local, cbbox[i]);
        cbbox[i][3] = 1.0f;
    }

    COPY128(cmax, cbbox[0]);
    COPY128(cmin, cbbox[0]);
    for (i = 1; i < 8; i++) {
        for (j = 0; j < 3; j += 2) {
            cmax[j] = cmax[j] > cbbox[i][j] ? cmax[j] : cbbox[i][j];
            cmin[j] = cmin[j] < cbbox[i][j] ? cmin[j] : cbbox[i][j];
        }
    }

    cmax[1] = cmin[1] = 0.0f;
    cmax[3] = cmin[3] = 1.0f;
    cmin[0] = cmin[0] < v_min[0] ? v_min[0] : cmin[0];
    cmin[2] = cmin[2] < v_min[2] ? v_min[2] : cmin[2];
    cmax[0] = cmax[0] > v_max[0] ? v_max[0] : cmax[0];
    cmax[2] = cmax[2] > v_max[2] ? v_max[2] : cmax[2];
    if (cmin[0] > cmax[0]) cmin[0] = cmax[0];
    if (cmin[2] > cmax[2]) cmin[2] = cmax[2];

    x_mesh_min = cmin[0] / (param->meshsizex * 0.1f);
    z_mesh_min = cmin[2] / (param->meshsizez * 0.1f);
    x_mesh_max = cmax[0] / (param->meshsizex * 0.1f);
    z_mesh_max = cmax[2] / (param->meshsizez * 0.1f);

    vtWaveGlobal.kitstruct->z_mesh = (s32)(x_mesh_max - x_mesh_min) + 10;
    vtWaveGlobal.kitstruct->x_mesh = (s32)(z_mesh_max - z_mesh_min) + 10;
    vtWaveGlobal.kitstruct->cbase[0] = (f32)((s32)x_mesh_min - 5) * 0.1f;
    vtWaveGlobal.kitstruct->cbase[2] = (f32)((s32)z_mesh_min - 5) * 0.1f;
}

u128* kitTexDraw(u128 *tmp, u32 offx, u32 offy, u32 lx, u32 ly, u64 tex0, u32 u, u32 v, u32 abe, u64 alpha, u64 color) {
    kitDMAPACKET *tmp2 = (kitDMAPACKET *)tmp;

    tmp2->ul[0] = DMAcnt | 13;
    tmp2->ui[2] = SCE_VIF1_SET_FLUSH(0);
    tmp2->ui[3] = SCE_VIF1_SET_DIRECT(13, 0);
    tmp2++;
    
    tmp2->ul[0] = SCE_GIF_SET_TAG(
        12,
        SCE_GS_TRUE,
        SCE_GS_TRUE,
        SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_FALSE) | abe << GS_PRIM_ABE_O,
        SCE_GIF_PACKED,
        1
    );
    tmp2->ul[1] = SCE_GIF_PACKED_AD;
    tmp2++;

    tmp2->ad.addr = SCE_GS_TEST_1;
    tmp2->ad.data = SCE_GS_SET_TEST(SCE_GS_FALSE, 0, 0, 0, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZALWAYS);
    tmp2++;
    tmp2->ad.addr = SCE_GS_TEX0_1;
    tmp2->ad.data = tex0;
    tmp2++;
    tmp2->ad.addr = SCE_GS_RGBAQ;
    tmp2->ad.data = color;
    tmp2++;
    tmp2->ad.addr = SCE_GS_ALPHA_1;
    tmp2->ad.data = alpha;
    tmp2++;
    tmp2->ad.addr = SCE_GS_TEXFLUSH;
    tmp2->ad.data = 0;
    tmp2++;
    tmp2->ad.addr = SCE_GS_TEX1_1;
    tmp2->ad.data = SCE_GS_SET_TEX1(0, 0, SCE_GS_LINEAR, SCE_GS_LINEAR, 0, 0, 0);
    tmp2++;
    tmp2->ad.addr = SCE_GS_CLAMP_1;
    tmp2->ad.data = SCE_GS_SET_CLAMP(SCE_GS_REPEAT, SCE_GS_REPEAT, 0, 0, 0, 0);
    tmp2++;
    tmp2->ad.addr = SCE_GS_UV;
    tmp2->ad.data = SCE_GS_SET_UV(8, 8);
    tmp2++;
    tmp2->ad.addr = SCE_GS_XYZ3;
    tmp2->ad.data = SCE_GS_SET_XYZ(offx, offy, 0xFFFFFF);
    tmp2++;
    tmp2->ad.addr = SCE_GS_UV;
    tmp2->ad.data = SCE_GS_SET_UV(u * 16 + 8, v * 16 + 8);
    tmp2++;
    tmp2->ad.addr = SCE_GS_XYZ2;
    tmp2->ad.data = SCE_GS_SET_XYZ(offx + lx, offy + ly, 0xFFFFFF);
    tmp2++;
    tmp2->ad.addr = SCE_GS_TEST_1;
    tmp2->ad.data = SCE_GS_SET_TEST(SCE_GS_FALSE, 0, 0, 0, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZGREATER);
    tmp2++;

    return (u128 *)tmp2;
}

void kitMakeLocalMatrixInv(kitWaveScreenEnv *env) {
    sceVu0InversMatrix(env->view_world, env->world_view);
    sceVu0InversMatrix(env->world_local, env->local_world);
    sceVu0InversMatrix(env->view_local, env->local_view);
}

void kitSetCounterParam(kitWaveStruct *env, s32 num) {
    kitWaveParam *var_s2;
    if (!vtWaveGlobal.wave_flag) {
        return;
    }

    if (num > vtWaveGlobal.kitstruct->param_num) {
        return;
    }
    
    env->current = num;
    env->countx = (f32)vtWaveGlobal.count / vtWaveGlobal.kitstruct->param[num]->speedx + 1000.0f;
    env->countz = (f32)vtWaveGlobal.count / vtWaveGlobal.kitstruct->param[num]->speedz + 1000.0f;
    var_s2 = vtWaveGlobal.kitstruct->param[num]; // idk
    env->radiusx = sinf((f32)vtWaveGlobal.count / 60.0f) * 2.0f * vtWaveGlobal.kitstruct->param[num]->random * 2.0f + var_s2->radiusx;
    env->radiusz = vtWaveGlobal.kitstruct->param[num]->radiusz;
}

u128* kitDrawWaveHeight(u128 *packet, sceVu0FVECTOR *vec, s32 num) {
    kitDMAPACKET *tmp = (kitDMAPACKET *)packet;
    sceVu0FMATRIX m1;
    sceVu0FVECTOR v;
    sceVu0IVECTOR vi;

    sceVu0UnitMatrix(m1);
    sceVu0CopyMatrix(m1, vtWaveGlobal.kitstruct->screenenv[num].local_screen);

    tmp->ul[0] = DMAcnt | 4;
    tmp->ui[2] = SCE_VIF1_SET_FLUSH(0);
    tmp->ui[3] = SCE_VIF1_SET_DIRECT(4, 0);
    tmp++;

    sceVu0ApplyMatrix(v, m1, *vec);
    v[3] = 1.0f / v[3];
    v[0] *= v[3];
    v[1] *= v[3];
    v[2] *= v[3];
    sceVu0FTOI4Vector(vi, v);
    vi[2] >>= 4;

    tmp->ul[0] = SCE_GIF_SET_TAG(
        3,
        SCE_GS_TRUE,
        SCE_GS_TRUE,
        SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE),
        SCE_GIF_PACKED,
        1
    );
    tmp->ul[1] = SCE_GIF_PACKED_AD;
    tmp++;

    tmp->ad.addr = SCE_GS_RGBAQ;
    tmp->ad.data = SCE_GS_SET_RGBAQ(0xFF, 0x00, 0x00, 0x00, 0x00);
    tmp++;
    tmp->ad.addr = SCE_GS_XYZ3;
    tmp->ad.data = SCE_GS_SET_XYZ(vi[0], vi[1], vi[2]);
    tmp++;
    tmp->ad.addr = SCE_GS_XYZ2;
    tmp->ad.data = SCE_GS_SET_XYZ(vi[0] + 32, vi[1] + 32, vi[2]);
    tmp++;

    return (u128 *)tmp;
}

s32 kitGetWaveDrawFlag(s32 num) {
    if (!vtWaveGlobal.wave_flag) {
        return -1;
    } else if (num < vtWaveGlobal.kitstruct->param_num) {
        return vtWaveGlobal.kitstruct->param[num]->draw_enable;
    } else {
        return -1;
    }
}

s32 kitWaveDrawEnable(s32 num) {
    if (!vtWaveGlobal.wave_flag) {
        return -1;
    } else if (num >= vtWaveGlobal.kitstruct->param_num) {
        return -1;
    } else {
        vtWaveGlobal.kitstruct->param[num]->draw_enable = 1;
        return 1;
    }
}

s32 kitWaveDrawDisable(s32 num) {
    if (!vtWaveGlobal.wave_flag) {
        return -1;
    } else if (num >= vtWaveGlobal.kitstruct->param_num) {
        return -1;
    } else {
        vtWaveGlobal.kitstruct->param[num]->draw_enable = 0;
        return 1;
    }
}

u64 kitGetMovieClamp(s32 num) {
    taroMovieStruct *ptarostruct = vtWaveGlobal.tarostruct[6];

    switch (num) {
        case 1:
            return SCE_GS_SET_CLAMP(SCE_GS_REGION_REPEAT, SCE_GS_REPEAT,        pow(2.0, ptarostruct->movie.tw - 1) - 1.0, 0, 0, 0);
        case 2:
            return SCE_GS_SET_CLAMP(SCE_GS_REGION_REPEAT, SCE_GS_REPEAT,        pow(2.0, ptarostruct->movie.tw - 1) - 1.0, pow(2.0, ptarostruct->movie.tw - 1), 0, 0);
        case 3:
            return SCE_GS_SET_CLAMP(SCE_GS_REGION_REPEAT, SCE_GS_REGION_REPEAT, pow(2.0, ptarostruct->movie.tw - 1) - 1.0, 0, pow(2.0, ptarostruct->movie.th - 1) - 1.0, 0);
        case 4:
            return SCE_GS_SET_CLAMP(SCE_GS_REGION_REPEAT, SCE_GS_REGION_REPEAT, pow(2.0, ptarostruct->movie.tw - 1) - 1.0, 0, pow(2.0, ptarostruct->movie.th - 1) - 1.0, pow(2.0, ptarostruct->movie.th - 1));
        case 5:
            return SCE_GS_SET_CLAMP(SCE_GS_REGION_REPEAT, SCE_GS_REGION_REPEAT, pow(2.0, ptarostruct->movie.tw - 1) - 1.0, pow(2.0, ptarostruct->movie.tw - 1), pow(2.0, ptarostruct->movie.th - 1) - 1.0, 0);
        case 6:
            return SCE_GS_SET_CLAMP(SCE_GS_REGION_REPEAT, SCE_GS_REGION_REPEAT, pow(2.0, ptarostruct->movie.tw - 1) - 1.0, pow(2.0, ptarostruct->movie.tw - 1), pow(2.0, ptarostruct->movie.th - 1) - 1.0, pow(2.0, ptarostruct->movie.th - 1));
        case 0:
        default:
            return SCE_GS_SET_CLAMP(SCE_GS_REPEAT, SCE_GS_REPEAT, 0, 0, 0, 0);
    }
}

void kitCalcWaveHeight(sceVu0FVECTOR *vec_new, sceVu0FVECTOR *vec_org, s32 num) {
    f32 cos_val;
    f32 sin_val;
    sceVu0FVECTOR vec_l;

    sceVu0ApplyMatrix(*vec_new, vtWaveGlobal.kitstruct->screenenv[num].world_local, *vec_org);
    sceVu0ApplyMatrix(vec_l, vtWaveGlobal.kitstruct->screenenv[num].world_local, *vec_org);

    (*vec_new)[0] = (*vec_new)[0] * vtWaveGlobal.kitstruct->param[num]->intervalx + vtWaveGlobal.kitstruct->countx;
    (*vec_new)[1] = 0.0f;
    (*vec_new)[2] = (*vec_new)[2] * vtWaveGlobal.kitstruct->param[num]->intervalz + vtWaveGlobal.kitstruct->countz;
    (*vec_new)[3] = 1.0f;

    cos_val = cosf((*vec_new)[0]) * vtWaveGlobal.kitstruct->radiusx;
    sin_val = sinf((*vec_new)[0]) * vtWaveGlobal.kitstruct->radiusz;
    (*vec_new)[0] = vec_l[0] - sin_val;
    (*vec_new)[1] = cos_val;

    cos_val = cosf((*vec_new)[2]) * vtWaveGlobal.kitstruct->radiusx;
    sin_val = sinf((*vec_new)[2]) * vtWaveGlobal.kitstruct->radiusz;
    (*vec_new)[1] += cos_val;
    (*vec_new)[2] = vec_l[2] - sin_val;
    (*vec_new)[2] = vtWaveGlobal.kitstruct->param[num]->height * (*vec_new)[2];
}

f32 kitGetWaveHeight(sceVu0FVECTOR *vec) {
    sceVu0FVECTOR vec_out;
    sceVu0FVECTOR *vec_org;
    s32 num;
    sceVu0FVECTOR vec_l;
    f32 sin_val;
    f32 cos_val;

    if (!vtWaveGlobal.wave_flag) {
        return 0.0f;
    }

    num = vtWaveGlobal.kitstruct->current;
    sceVu0ApplyMatrix(vec_out, vtWaveGlobal.kitstruct->screenenv[num].world_local, *vec);
    sceVu0ApplyMatrix(vec_l, vtWaveGlobal.kitstruct->screenenv[num].world_local, *vec);

    vec_out[0] = vec_out[0] * vtWaveGlobal.kitstruct->param[num]->intervalx + vtWaveGlobal.kitstruct->countx;
    vec_out[1] = 0.0f;
    vec_out[2] = vec_out[2] * vtWaveGlobal.kitstruct->param[num]->intervalz + vtWaveGlobal.kitstruct->countz;
    vec_out[3] = 1.0f;

    cos_val = cosf(vec_out[0]) * vtWaveGlobal.kitstruct->radiusx;
    sin_val = sinf(vec_out[0]) * vtWaveGlobal.kitstruct->radiusz;
    vec_out[0] = vec_l[0] - sin_val;
    vec_out[1] = cos_val;

    cos_val = cosf(vec_out[2]) * vtWaveGlobal.kitstruct->radiusx;
    sin_val = sinf(vec_out[2]) * vtWaveGlobal.kitstruct->radiusz;
    vec_out[1] += cos_val;
    vec_out[2] = vec_l[2] - sin_val;
    vec_out[2] = vtWaveGlobal.kitstruct->param[num]->height * vec_out[2];
    
    sceVu0ApplyMatrix(vec_out, vtWaveGlobal.kitstruct->screenenv[vtWaveGlobal.kitstruct->current].local_world, vec_out);
    return vec_out[1];
}