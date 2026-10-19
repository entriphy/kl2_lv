#include "vtusr/kit/kitfiremain.h"
#include "vtusr/kit/kitfirevu.h"
#include "kit.h"
#include "okanoyo/okio.h"
#include "vtusr/taro/taro_movie.h"
#include "vtusr/vtfiremain.h"
#include "vtusr/vtwavemain.h"

#define kitrand() (kitfirestructGBL->rand_table[kitfirestructGBL->rand_num = kitfirestructGBL->rand_num < 0x7F ? kitfirestructGBL->rand_num + 1 : 0])

extern u32 kitFireMicroProg __attribute__((section(".vutext")));
extern u32 kitFireMicroProgEnd __attribute__((section(".vutext")));

kitFireStruct *kitfirestructGBL_spr = SPR_MEM;
kitFireStruct *kitfirestructGBL;

kitFireStruct* kitInitFire() {
    char tmp;
    s32 status;
    kitFireStruct *env = getBuff(1, sizeof(kitFireStruct), &tmp, &status);

    KL2_DEBUG_PRINT(("Alloc %xByte (%xKByte)\n", sizeof(kitFireStruct), sizeof(kitFireStruct) / 1024));
    kitfirestructGBL = env;
    kitClearFire();
    kitMakeRandtable();
    kitVu0ViewClipMatrix(kitfirestructGBL->view_clip, 640.0f, 480.0f, 512.0f, 200.0f, 3000.0f);
    FlushCache(WRITEBACK_DCACHE);
    return env;
}

void kitClearFire() {
    if (vtFireGlobal.fire_flag) {
        kitfirestructGBL->f_num = 0;
    }
}

s32 kitSetFire(sceVu0FVECTOR vec, sceVu0FVECTOR size, f32 particle) {
    kitFireParam *param;
    s32 i;
    s32 var_v0;

    if (!vtFireGlobal.fire_flag) {
        return -1;
    }

    param = &kitfirestructGBL->param[kitfirestructGBL->f_num];
    sceVu0CopyVector(param->center, vec);
    param->center[3] = 1.0f;
    param->fire_size[0] = size[0] * 50.0f;
    param->fire_size[1] = size[1] * -75.0f;
    param->fire_size[2] = size[2] * 50.0f;
    param->fire_size[3] = 1.0f;
    param->bbox[0][0] = param->center[0] + param->fire_size[0] * 1.2f;
    param->bbox[0][1] = param->center[1];
    param->bbox[0][2] = param->center[2] + param->fire_size[2] * 1.2f;
    param->bbox[0][3] = 1.0f;
    param->bbox[1][0] = param->center[0] - param->fire_size[0] * 1.2f;
    param->bbox[1][1] = param->center[1];
    param->bbox[1][2] = param->center[2] + param->fire_size[2] * 1.2f;
    param->bbox[1][3] = 1.0f;
    param->bbox[2][0] = param->center[0] + param->fire_size[0] * 1.2f;
    param->bbox[2][1] = param->center[1];
    param->bbox[2][2] = param->center[2] - param->fire_size[2] * 1.2f;
    param->bbox[2][3] = 1.0f;
    param->bbox[3][0] = param->center[0] - param->fire_size[0] * 1.2f;
    param->bbox[3][1] = param->center[1];
    param->bbox[3][2] = param->center[2] + param->fire_size[2] * 1.2f;
    param->bbox[3][3] = 1.0f;
    param->bbox[4][0] = param->center[0] + param->fire_size[0] * 1.2f;
    param->bbox[4][1] = param->center[1] + param->fire_size[1] * 1.2f;
    param->bbox[4][2] = param->center[2] + param->fire_size[2] * 1.2f;
    param->bbox[4][3] = 1.0f;
    param->bbox[5][0] = param->center[0] - param->fire_size[0] * 1.2f;
    param->bbox[5][1] = param->center[1] + param->fire_size[1] * 1.2f;
    param->bbox[5][2] = param->center[2] + param->fire_size[2] * 1.2f;
    param->bbox[5][3] = 1.0f;
    param->bbox[6][0] = param->center[0] + param->fire_size[0] * 1.2f;
    param->bbox[6][1] = param->center[1] + param->fire_size[1] * 1.2f;
    param->bbox[6][2] = param->center[2] - param->fire_size[2] * 1.2f;
    param->bbox[6][3] = 1.0f;
    param->bbox[7][0] = param->center[0] - param->fire_size[0] * 1.2f;
    param->bbox[7][1] = param->center[1] + param->fire_size[1] * 1.2f;
    param->bbox[7][2] = param->center[2] - param->fire_size[2] * 1.2f;
    param->bbox[7][3] = 1.0f;

    particle = particle > 1.0f ? 1.0f : particle;
    param->particle_max = particle * 10.0f;
    for (i = 0; i < param->particle_max * 4; i++) {
        kitSetParticleVelocity(param, i, 1);
    }
    
    for (i = 0; i < 10; i++) {
        param->turn[0][i] = i;
        param->turn[1][i] = i;
        param->turn[2][i] = i;
        param->turn[3][i] = i;
    }

    var_v0 = kitfirestructGBL->f_num;
    kitfirestructGBL->f_num++;
    return var_v0;
}

u128* kitExecFireMovieSend(u128 *packet) {
    if (vtFireGlobal.fr & 0x2 && !vtFireGlobal.pause) {
        vtIPU_decode(&vtFireGlobal.tarostruct->movie);
        vtIPU_syncDecode(&vtFireGlobal.tarostruct->movie);
    }
    return vtIPU_mkDmaTagOfSendTexVIF(packet, vtFireGlobal.tarostruct->movie.cscBuff[vtFireGlobal.tarostruct->movie.currentBufNo], &vtFireGlobal.tarostruct->movie);
}

u128* kitDrawFire(u128 *packet_in) {
    kitDMAPACKET *packet = (kitDMAPACKET *)packet_in;
    f32 inner[2];
    f32 alpha_re[4];
    u8 base_alpha[5];
    u8 turn[50];
    static u8 alpha[8] = {};
    sceVu0FVECTOR inner_vecf_baseplate[3] = {
        { 0.0f, 1.0f, 0.0f, 1.0f },
        { 0.7071f, 0.0f, 0.7071f, 1.0f},
        { 0.7071f, 0.0f, -0.7071f, 1.0f }
    };
    f32 inner_baseplate[3];
    sceVu0FVECTOR view_vec = { 0.0f, 0.0f, 1.0f, 1.0f };
    kitFireParam *param;
    s32 i;

    FlushCache(WRITEBACK_DCACHE);
    sceVu0CopyMatrix(kitfirestructGBL->world_view, GameGbl.wvm);
    sceVu0InversMatrix(kitfirestructGBL->view_world, GameGbl.wvm);
    sceVu0CopyMatrix(kitfirestructGBL->world_screen, GameGbl.wsm);
    sceVu0MulMatrix(kitfirestructGBL->world_clip, kitfirestructGBL->view_clip, kitfirestructGBL->world_view);
    sceVu0CopyVector(kitfirestructGBL->camera_pos, GameGbl.cam.posi);
    kitfirestructGBL->camera_pos[3] = 1.0f;
    sceVu0ApplyMatrix(kitfirestructGBL->camera_pos_v, kitfirestructGBL->world_view, kitfirestructGBL->camera_pos);

    if (!kitfirestructGBL->pause) {
        alpha[(u32)(kitrand() * 4.0f) + 4] = (u32)(kitrand() * 8.0f);
    }

    packet = (kitDMAPACKET *)kitVu1Initialize((u128 *)packet, kitfirestructGBL->world_screen);
    packet = (kitDMAPACKET *)kitVu1LoadProg((u128 *)packet, (u32)&kitFireMicroProg, ((u32)&kitFireMicroProgEnd + 0x8 - (u32)&kitFireMicroProg) >> 4);
    packet = (kitDMAPACKET *)kitFireGsInitPacket((u128 *)packet);
    kitSetBaseVec(kitfirestructGBL);
    kitSetInversBaseVec(kitfirestructGBL);

    for (i = 0; i < 3; i++) {
        sceVu0ApplyMatrix(inner_vecf_baseplate[i], kitfirestructGBL->world_view, inner_vecf_baseplate[i]);
        sceVu0SubVector(inner_vecf_baseplate[i], inner_vecf_baseplate[i], kitfirestructGBL->center_w2v);
        inner_baseplate[i] = kitVu0InnerProduct(view_vec, inner_vecf_baseplate[i]);
    }

    inner_baseplate[0] = inner_baseplate[0] > 0.0f ? inner_baseplate[0] : -inner_baseplate[0];
    if (inner_baseplate[0] < 0.25) {
        alpha_re[0] = inner_baseplate[0] * -inner_baseplate[1];
        alpha_re[1] = inner_baseplate[0] * -inner_baseplate[2];
        alpha_re[2] = inner_baseplate[0] * inner_baseplate[1];
        alpha_re[3] = inner_baseplate[0] * inner_baseplate[2];
    } else {
        alpha_re[0] = inner_baseplate[0] * ((inner_baseplate[0] - 0.25) - inner_baseplate[1]);
        alpha_re[1] = inner_baseplate[0] * ((inner_baseplate[0] - 0.25) - inner_baseplate[2]);
        alpha_re[2] = inner_baseplate[0] * ((inner_baseplate[0] - 0.25) + inner_baseplate[1]);
        alpha_re[3] = inner_baseplate[0] * ((inner_baseplate[1] - 0.25) + inner_baseplate[2]);
    }

    for (i = 0; i < 4; i++) {
        // freaky ah ternary
        alpha_re[i] = alpha_re[i] > 0.0f ? alpha_re[0] < 1.0f ? alpha_re[i] : 1.0f : 0.0f;
        base_alpha[i + 1] = alpha_re[i] * 128.0f + 0.0f;
    }

    base_alpha[0] = (base_alpha[1] + base_alpha[2] + base_alpha[3] + base_alpha[4]) / 4;
    kitFireZSort(kitfirestructGBL, turn, kitfirestructGBL->f_num);
    kitInitVu1Dma((u128 *)packet);

    for (i = 0; i < kitfirestructGBL->f_num; i++) {
        if (turn[i] != 0xFF) {
            param = &kitfirestructGBL->param[turn[i]];
            kitCalcInnerVal(param, inner);
            kitSetPlateBase(param, base_alpha, 0);
            kitSetPlateBase(param, base_alpha, 1);
            kitSetPlateBase(param, base_alpha, 2);
            kitSetPlateBase(param, base_alpha, 3);
            alpha[0] = alpha[2] = abs(inner[1] * 128.0f);
            alpha[1] = alpha[3] = abs(inner[0] * 128.0f);

            if (inner[0] >= 0.0f && inner[1] >= 0.0f) {
                kitSetParticle(param, 0);
                kitSetPlate(param, alpha, 0);
                kitSetPlate(param, alpha, 1);
                kitSetParticle(param, 1);
                kitSetParticle(param, 3);
                kitSetPlate(param, alpha, 2);
                kitSetPlate(param, alpha, 3);
                kitSetParticle(param, 2);
            } else if (inner[0] <= 0.0f && inner[1] >= 0.0f) {
                kitSetParticle(param, 1);
                kitSetPlate(param, alpha, 1);
                kitSetPlate(param, alpha, 2);
                kitSetParticle(param, 0);
                kitSetParticle(param, 2);
                kitSetPlate(param, alpha, 0);
                kitSetPlate(param, alpha, 3);
                kitSetParticle(param, 3);
            } else if (inner[0] <= 0.0f && inner[1] <= 0.0f) {
                kitSetParticle(param, 2);
                kitSetPlate(param, alpha, 2);
                kitSetPlate(param, alpha, 3);
                kitSetParticle(param, 1);
                kitSetParticle(param, 3);
                kitSetPlate(param, alpha, 0);
                kitSetPlate(param, alpha, 1);
                kitSetParticle(param, 0);
            } else {
                kitSetParticle(param, 3);
                kitSetPlate(param, alpha, 0);
                kitSetPlate(param, alpha, 3);
                kitSetParticle(param, 0);
                kitSetParticle(param, 2);
                kitSetPlate(param, alpha, 1);
                kitSetPlate(param, alpha, 2);
                kitSetParticle(param, 1);
            }
        }
    }

    packet = (kitDMAPACKET *)kitEndVu1Vertex();
    packet = (kitDMAPACKET *)kitFireEndPacket((u128 *)packet);
    return (u128 *)packet;
}

// Line 539
inline f32 kitVu0InnerProduct(sceVu0FVECTOR v0, sceVu0FVECTOR v1) {
    f32 ret;

    __asm__ volatile(
        "lqc2       $vf4, 0x0(%1)\n"
        "lqc2       $vf5, 0x0(%2)\n"
        "vmul.xyz   $vf5, $vf4, $vf5\n"
        "vaddy.x    $vf5, $vf5, $vf5y\n"
        "vaddz.x    $vf5, $vf5, $vf5z\n"
        "qmfc2.ni   $2, $vf5\n"
        "mtc1       $2, %0\n"
    : "=f" (ret)
    : "r" (v0), "r" (v1)
    : "$2"
    );

    return ret;
}

void kitSetPlate(kitFireParam *param, u8 *alpha, s32 num) {
    switch (num) {
        case 0:
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[num + 4]);
            kitPushVu1VertexF(0.5f, 0.8f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1], param->center[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[num + 4]);
            kitPushVu1VertexF(1.0f, 0.8f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0] + param->fire_size[0], param->center[1], param->center[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[num]);
            kitPushVu1VertexF(0.5f, 0.0f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1] + param->fire_size[1], param->center[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[num]);
            kitPushVu1VertexF(1.0f, 0.0f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0] + param->fire_size[0], param->center[1] + param->fire_size[1], param->center[2], 1.0f);
            break;
        case 1:
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[num + 4]);
            kitPushVu1VertexF(0.5f, 0.8f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1], param->center[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[num + 4]);
            kitPushVu1VertexF(1.0f, 0.8f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1], param->center[2] + param->fire_size[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[num]);
            kitPushVu1VertexF(0.5f, 0.0f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1] + param->fire_size[1], param->center[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[num]);
            kitPushVu1VertexF(1.0f, 0.0f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1] + param->fire_size[1], param->center[2] + param->fire_size[2], 1.0f);
            break;
        case 2:
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[num + 4]);
            kitPushVu1VertexF(0.5f, 0.8f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1], param->center[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[num + 4]);
            kitPushVu1VertexF(0.0f, 0.8f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0] - param->fire_size[0], param->center[1], param->center[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[num]);
            kitPushVu1VertexF(0.5f, 0.0f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1] + param->fire_size[1], param->center[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[num]);
            kitPushVu1VertexF(0.0f, 0.0f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0] - param->fire_size[0], param->center[1] + param->fire_size[1], param->center[2], 1.0f);
            break;
        case 3:
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[num + 4]);
            kitPushVu1VertexF(0.5f, 0.8f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1], param->center[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[num + 4]);
            kitPushVu1VertexF(0.0f, 0.8f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1], param->center[2] - param->fire_size[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[num]);
            kitPushVu1VertexF(0.5f, 0.0f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1] + param->fire_size[1], param->center[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[num]);
            kitPushVu1VertexF(0.0f, 0.0f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1] + param->fire_size[1], param->center[2] - param->fire_size[2], 1.0f);
            break;
    }
}

void kitSetPlateBase(kitFireParam *param, u8 *alpha, s32 num) {
    switch (num) {
        case 0:
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[0]);
            kitPushVu1VertexF(0.5f, 0.8f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1], param->center[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, (alpha[1] + alpha[2]) * 0.5f);
            kitPushVu1VertexF(1.0f, 0.8f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0] + param->fire_size[0] * 1.2f, param->center[1], param->center[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, (alpha[1] + alpha[4]) * 0.5f);
            kitPushVu1VertexF(0.5f, 0.0f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1], param->center[2] + param->fire_size[2] * 1.2f, 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[1]);
            kitPushVu1VertexF(1.0f, 0.0f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0] + param->fire_size[0] * 1.2f, param->center[1], param->center[2] + param->fire_size[2] * 1.2f, 1.0f);
            break;
        case 1:
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[0]);
            kitPushVu1VertexF(0.5f, 0.8f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1], param->center[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, (alpha[1] + alpha[2]) * 0.5f);
            kitPushVu1VertexF(1.0f, 0.8f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0] + param->fire_size[0] * 1.2f, param->center[1], param->center[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, (alpha[2] + alpha[3]) * 0.5f);
            kitPushVu1VertexF(0.5f, 0.0f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1], param->center[2] - param->fire_size[2] * 1.2f, 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[2]);
            kitPushVu1VertexF(1.0f, 0.0f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0] + param->fire_size[0] * 1.2f, param->center[1], param->center[2] - param->fire_size[2] * 1.2f, 1.0f);
            break;
        case 2:
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[0]);
            kitPushVu1VertexF(0.5f, 0.8f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1], param->center[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, (alpha[3] + alpha[4]) * 0.5f);
            kitPushVu1VertexF(0.0f, 0.8f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0] - param->fire_size[0] * 1.2f, param->center[1], param->center[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, (alpha[2] + alpha[3]) * 0.5f);
            kitPushVu1VertexF(0.5f, 0.0f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1], param->center[2] - param->fire_size[2] * 1.2f, 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[3]);
            kitPushVu1VertexF(0.0f, 0.0f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0] - param->fire_size[0] * 1.2f, param->center[1], param->center[2] - param->fire_size[2] * 1.2f, 1.0f);
            break;
        case 3:
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[0]);
            kitPushVu1VertexF(0.5f, 0.8f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1], param->center[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, (alpha[3] + alpha[4]) * 0.5f);
            kitPushVu1VertexF(0.0f, 0.8f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0] - param->fire_size[0] * 1.2f, param->center[1], param->center[2], 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, (alpha[4] + alpha[1]) * 0.5f);
            kitPushVu1VertexF(0.5f, 0.0f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0], param->center[1], param->center[2] + param->fire_size[2] * 1.2f, 1.0f);
            kitPushVu1VertexI(0x80, 0x80, 0x80, alpha[4]);
            kitPushVu1VertexF(0.0f, 0.0f, 1.0f, 1.0f);
            kitPushVu1VertexF(param->center[0] - param->fire_size[0] * 1.2f, param->center[1], param->center[2] + param->fire_size[2] * 1.2f, 1.0f);
            break;
    }
}

void kitSetParticle(kitFireParam *param, s32 num_base) {
    sceVu0FVECTOR point[10];
    u8 alpha;
    s32 i;
    s32 j;
    f32 z_val[10];
    s32 num = num_base;
    u8 color;
    s32 life;
    s32 life_max_div_4;
    s32 sort_sw;
    s32 sort_cnt;

    for (i = 0; i < param->particle_max; i++, num += 4) {
        param->life[num] += kitfirestructGBL->pause ^ 1;
        if (param->life[num] > param->life_max[num]) {
            kitSetParticleVelocity(param, num, 0);
        }
        point[i][0] = param->start[num][0] + param->p_vec[num][0] * param->life[num];
        point[i][1] = param->start[num][1] + param->p_vec[num][1] * param->life[num];
        point[i][2] = param->start[num][2] + param->p_vec[num][2] * param->life[num];
        point[i][3] = 1.0f;
        z_val[i] = point[i][0] * kitfirestructGBL->basevec_w2v[0][2] + point[i][1] * kitfirestructGBL->basevec_w2v[1][2] + point[i][2] * kitfirestructGBL->basevec_w2v[2][2];
    }
    
    sort_cnt = param->lod;
    while (sort_cnt >= 2) {
        sort_sw = 0;
        for (i = 0; i < sort_cnt - 1; i++) {
            j = i + 1;
            if (z_val[param->turn[num_base][i]] < z_val[param->turn[num_base][j]]) {
                u8 var_v0 = param->turn[num_base][i];
                param->turn[num_base][i] = param->turn[num_base][j];
                param->turn[num_base][j] = var_v0;
                sort_sw = j;
            }
        }
        sort_cnt = sort_sw;
    }

    for (i = 0; i < param->lod; i++) {
        life = param->life[param->turn[num_base][i] * 4 + num_base];
        life_max_div_4 = param->life_max[param->turn[num_base][i] * 4 + num_base] / 4.0f;
        switch (life / life_max_div_4) {
            case 0:
                alpha = ((f32)life / (f32)life_max_div_4) * 48.0f;
                color = 0x80;
                break;
            case 1:
                alpha = ((f32)(life_max_div_4 * 2 - life) / (f32)life_max_div_4) * 48.0f;
                color = 0x80;
                break;
            case 2:
                alpha = ((f32)(life_max_div_4 * -2 + life) / (f32)((life_max_div_4 * 1.5))) * 48.0f;
                color = 0x20;
                break;
            default:
                alpha = ((f32)(life_max_div_4 * 4 - life + 5) / (f32)(life_max_div_4 * 1.5)) * 48.0f;
                color = 0x20;
                break;
        }

        kitPushVu1VertexI(color, color, color, alpha);
        kitPushVu1VertexF(0.0f, 0.0f, 1.0f, 1.0f);
        kitPushVu1VertexF(
            (point[param->turn[num_base][i]][0] + kitfirestructGBL->basevec_v2w_p[0][0]) - kitfirestructGBL->basevec_v2w_p[1][0],
            (point[param->turn[num_base][i]][1] + kitfirestructGBL->basevec_v2w_p[0][1]) - kitfirestructGBL->basevec_v2w_p[1][1],
            (point[param->turn[num_base][i]][2] + kitfirestructGBL->basevec_v2w_p[0][2]) - kitfirestructGBL->basevec_v2w_p[1][2],
            1.0f
        );

        kitPushVu1VertexI(color, color, color, alpha);
        kitPushVu1VertexF(0.0f, 1.0f, 1.0f, 1.0f);
        kitPushVu1VertexF(
            (point[param->turn[num_base][i]][0] + kitfirestructGBL->basevec_v2w_p[0][0]) + kitfirestructGBL->basevec_v2w_p[1][0],
            (point[param->turn[num_base][i]][1] + kitfirestructGBL->basevec_v2w_p[0][1]) + kitfirestructGBL->basevec_v2w_p[1][1],
            (point[param->turn[num_base][i]][2] + kitfirestructGBL->basevec_v2w_p[0][2]) + kitfirestructGBL->basevec_v2w_p[1][2],
            1.0f
        );

        kitPushVu1VertexI(color, color, color, alpha);
        kitPushVu1VertexF(1.0f, 0.0f, 1.0f, 1.0f);
        kitPushVu1VertexF(
            (point[param->turn[num_base][i]][0] - kitfirestructGBL->basevec_v2w_p[0][0]) - kitfirestructGBL->basevec_v2w_p[1][0],
            (point[param->turn[num_base][i]][1] - kitfirestructGBL->basevec_v2w_p[0][1]) - kitfirestructGBL->basevec_v2w_p[1][1],
            (point[param->turn[num_base][i]][2] - kitfirestructGBL->basevec_v2w_p[0][2]) - kitfirestructGBL->basevec_v2w_p[1][2],
            1.0f
        );

        kitPushVu1VertexI(color, color, color, alpha);
        kitPushVu1VertexF(1.0f, 1.0f, 1.0f, 1.0f);
        kitPushVu1VertexF(
            (point[param->turn[num_base][i]][0] - kitfirestructGBL->basevec_v2w_p[0][0]) + kitfirestructGBL->basevec_v2w_p[1][0],
            (point[param->turn[num_base][i]][1] - kitfirestructGBL->basevec_v2w_p[0][1]) + kitfirestructGBL->basevec_v2w_p[1][1],
            (point[param->turn[num_base][i]][2] - kitfirestructGBL->basevec_v2w_p[0][2]) + kitfirestructGBL->basevec_v2w_p[1][2],
            1.0f
        );
    }
}

void kitSetParticleVelocity(kitFireParam *param, s32 num, s32 init) {
    sceVu0FVECTOR point;
    s32 generator_val;
    sceVu0FVECTOR outside_vec;
    sceVu0FVECTOR generator;

    // generator_val = num % 4;
    generator_val = num - (num / 4 * 4);
    switch (generator_val) {
        case 0:
            outside_vec[0] = 1.0f;
            outside_vec[1] = 0.0f;
            outside_vec[2] = 1.0f;
            outside_vec[3] = 0.0f;
            break;
        case 1:
            outside_vec[0] = -1.0f;
            outside_vec[1] = 0.0f;
            outside_vec[2] = 1.0f;
            outside_vec[3] = 0.0f;
            break;
        case 2:
            outside_vec[0] = -1.0f;
            outside_vec[1] = 0.0f;
            outside_vec[2] = -1.0f;
            outside_vec[3] = 0.0f;
            break;
        case 3:
            outside_vec[0] = 1.0f;
            outside_vec[1] = 0.0f;
            outside_vec[2] = -1.0f;
            outside_vec[3] = 0.0f;
            break;
    }

    generator_val = kitrand() * 4.0f;
    switch (generator_val) {
        case 0:
            generator[0] = param->fire_size[0] * 0.6f;
            generator[1] = param->fire_size[1] * -0.2f;
            generator[2] = param->fire_size[2] * 0.6f;
            generator[3] = 0.0f;
            param->p_vec[num][0] = (kitrand() * param->fire_size[0] / 50.0f) * 0.5f * -outside_vec[0];
            param->p_vec[num][1] = ((kitrand() * 0.5f + 0.5f) * param->fire_size[1] / 75.0f) * 2.25f;
            param->p_vec[num][2] = (kitrand() * param->fire_size[2] / 50.0f) * 0.5f * -outside_vec[2];
            param->p_vec[num][3] = 0.0f;
            break;
        case 1:
            generator[0] = param->fire_size[0] * 0.2f;
            generator[1] = param->fire_size[1] * -0.2f;
            generator[2] = param->fire_size[2] * 0.2f;
            generator[3] = 0.0f;
            param->p_vec[num][0] = ((kitrand() * 0.5f - 0.5f) * param->fire_size[0] / 50.0f) * 0.5f;
            param->p_vec[num][1] = ((kitrand() * 0.5f + 0.5f) * param->fire_size[1] / 75.0f) * 2.25f;
            param->p_vec[num][2] = ((kitrand() * 0.5f - 0.5f) * param->fire_size[2] / 50.0f) * 0.5f;
            param->p_vec[num][3] = 0.0f;
            break;
        case 2:
            generator[0] = param->fire_size[0] * 0.2f;
            generator[1] = param->fire_size[1] * -0.2f;
            generator[2] = param->fire_size[2] * 0.6f;
            generator[3] = 0.0f;
            param->p_vec[num][0] = (kitrand() * param->fire_size[0] / 50.0f) * 0.5f * outside_vec[0];
            param->p_vec[num][1] = ((kitrand() * 0.5f + 0.5f) * param->fire_size[1] / 75.0f) * 2.25f;
            param->p_vec[num][2] = (kitrand() * param->fire_size[2] / 50.0f) * 0.5f * -outside_vec[2];
            param->p_vec[num][3] = 0.0f;
            break;
        case 3:
            generator[0] = param->fire_size[0] * 0.6f;
            generator[1] = param->fire_size[1] * -0.2f;
            generator[2] = param->fire_size[2] * 0.2f;
            generator[3] = 0.0f;
            param->p_vec[num][0] = (kitrand() * param->fire_size[0] / 50.0f) * 0.5f * -outside_vec[0];
            param->p_vec[num][1] = ((kitrand() * 0.5f + 0.5f) * param->fire_size[1] / 75.0f) * 2.25f;
            param->p_vec[num][2] = (kitrand() * param->fire_size[2] / 50.0f) * 0.5f * outside_vec[2];
            param->p_vec[num][3] = 0.0f;
            break;
    }

    point[0] = outside_vec[0] * generator[0];
    point[1] = outside_vec[1] * generator[1];
    point[2] = outside_vec[2] * generator[2];
    point[3] = 0.0f;
    sceVu0AddVector(param->start[num], param->center, point);
    
    param->life_max[num] = param->fire_size[1] * 1.2f / param->p_vec[num][1];
    if (!init) {
        param->life[num] = 0;
    } else {
        param->life[num] = param->life_max[num] * kitrand();
    }
}

void kitMakeRandtable() {
    s32 i;

    for (i = 0; i < 128; i++) {
        // The float is 0x30000000
        // Surely they didn't manually write the value in?
        // Can't get it to match even when introducing a u32 + f32 var...
        // kitfirestructGBL->rand_table[i] = rand() * 4.656612873e-10f;
        kitfirestructGBL->rand_table[i] = rand() * 4.656612873e-10f;
    }
}

void kitFireZSort(kitFireStruct *kitfirestruct, u8 *turn, s32 max) {
    s32 i;
    s32 j;

    for (i = 0; i < max; i++) {
        sceVu0ApplyMatrix(kitfirestruct->param[i].center_v, kitfirestruct->world_view, kitfirestruct->param[i].center);
        kitfirestruct->param[i].lod_f = (kitfirestruct->param[i].center_v[2] - 200.0f) * 0.00055555555f;
        kitfirestruct->param[i].lod_f = kitfirestruct->param[i].lod_f > 1.0f ? 1.0f : kitfirestruct->param[i].lod_f < 0.0f ? 0.0f : kitfirestruct->param[i].lod_f;
        kitfirestruct->param[i].lod = (1.0f - kitfirestruct->param[i].lod_f) * (kitfirestruct->param[i].particle_max);
        turn[i] = i;
    }

    for (i = 0; i < max; i++) {
        for (j = 0; j < max - i - 1; j++) {
            if (kitfirestruct->param[turn[j]].center_v[2] < kitfirestruct->param[turn[j + 1]].center_v[2]) {
                u8 tmp = turn[j];
                turn[j] = turn[j + 1];
                turn[j + 1] = tmp;
            }
        }
    }

    for (i = 0; i < max; i++) {
        if (kitVu0ClipBBox(kitfirestruct->world_clip, kitfirestruct->param[turn[i]].bbox) == 1) {
            turn[i] = 0xFF;
        }
    }
}

void kitSetBaseVec(kitFireStruct *kitfirestruct) {
    SETVEC(kitfirestruct->center_w2v, 0.0f, 0.0f, 0.0f, 1.0f);
    sceVu0ApplyMatrix(kitfirestruct->center_w2v, kitfirestruct->world_view, kitfirestruct->center_w2v);

    SETVEC(kitfirestruct->basevec_w2v[0], 1.0f, 0.0f, 0.0f, 1.0f);
    SETVEC(kitfirestruct->basevec_w2v[1], 0.0f, 1.0f, 0.0f, 1.0f);
    SETVEC(kitfirestruct->basevec_w2v[2], 0.0f, 0.0f, 1.0f, 1.0f);
    sceVu0ApplyMatrix(kitfirestruct->basevec_w2v[0], kitfirestruct->world_view, kitfirestruct->basevec_w2v[0]);
    sceVu0ApplyMatrix(kitfirestruct->basevec_w2v[1], kitfirestruct->world_view, kitfirestruct->basevec_w2v[1]);
    sceVu0ApplyMatrix(kitfirestruct->basevec_w2v[2], kitfirestruct->world_view, kitfirestruct->basevec_w2v[2]);
    sceVu0SubVector(kitfirestruct->basevec_w2v[0], kitfirestruct->basevec_w2v[0], kitfirestruct->center_w2v);
    sceVu0SubVector(kitfirestruct->basevec_w2v[1], kitfirestruct->basevec_w2v[1], kitfirestruct->center_w2v);
    sceVu0SubVector(kitfirestruct->basevec_w2v[2], kitfirestruct->basevec_w2v[2], kitfirestruct->center_w2v);
}

void kitSetInversBaseVec(kitFireStruct *kitfirestruct) {
    SETVEC(kitfirestruct->center_v2w, 0.0f, 0.0f, 0.0f, 1.0f);
    sceVu0ApplyMatrix(kitfirestruct->center_v2w, kitfirestruct->view_world, kitfirestruct->center_v2w);

    SETVEC(kitfirestruct->basevec_v2w[0], 1.0f, 0.0f, 0.0f, 1.0f);
    SETVEC(kitfirestruct->basevec_v2w[1], 0.0f, 1.0f, 0.0f, 1.0f);
    SETVEC(kitfirestruct->basevec_v2w[2], 0.0f, 0.0f, 1.0f, 1.0f);
    sceVu0ApplyMatrix(kitfirestruct->basevec_v2w[0], kitfirestruct->view_world, kitfirestruct->basevec_v2w[0]);
    sceVu0ApplyMatrix(kitfirestruct->basevec_v2w[1], kitfirestruct->view_world, kitfirestruct->basevec_v2w[1]);
    sceVu0ApplyMatrix(kitfirestruct->basevec_v2w[2], kitfirestruct->view_world, kitfirestruct->basevec_v2w[2]);
    sceVu0SubVector(kitfirestruct->basevec_v2w[0], kitfirestruct->basevec_v2w[0], kitfirestruct->center_v2w);
    sceVu0SubVector(kitfirestruct->basevec_v2w[1], kitfirestruct->basevec_v2w[1], kitfirestruct->center_v2w);
    sceVu0SubVector(kitfirestruct->basevec_v2w[2], kitfirestruct->basevec_v2w[2], kitfirestruct->center_v2w);
    kitfirestruct->basevec_v2w_p[0][0] = kitfirestruct->basevec_v2w[0][0] * 10.0f;
    kitfirestruct->basevec_v2w_p[0][1] = kitfirestruct->basevec_v2w[0][1] * 10.0f;
    kitfirestruct->basevec_v2w_p[0][2] = kitfirestruct->basevec_v2w[0][2] * 10.0f;
    kitfirestruct->basevec_v2w_p[0][3] = 1.0f;
    kitfirestruct->basevec_v2w_p[1][0] = kitfirestruct->basevec_v2w[1][0] * 10.0f;
    kitfirestruct->basevec_v2w_p[1][1] = kitfirestruct->basevec_v2w[1][1] * 10.0f;
    kitfirestruct->basevec_v2w_p[1][2] = kitfirestruct->basevec_v2w[1][2] * 10.0f;
    kitfirestruct->basevec_v2w_p[1][3] = 1.0f;
}

void kitCalcInnerVal(kitFireParam *param, sceVu0FVECTOR inner) {
    sceVu0FVECTOR inner_vec[2];
    sceVu0FVECTOR cp_vec;

    sceVu0Normalize(cp_vec, param->center_v);
    sceVu0ApplyMatrix(cp_vec, kitfirestructGBL->view_world, cp_vec);
    inner_vec[0][0] = 1.0f;
    inner_vec[0][1] = 0.0f;
    inner_vec[0][2] = 0.0f;
    inner_vec[0][3] = 1.0f;
    inner_vec[1][0] = 0.0f;
    inner_vec[1][1] = 0.0f;
    inner_vec[1][2] = 1.0f;
    inner_vec[1][3] = 1.0f;
    inner[0] = kitVu0InnerProduct(cp_vec, inner_vec[0]);
    inner[1] = kitVu0InnerProduct(cp_vec, inner_vec[1]);
}

void kitVu0ViewClipMatrix(sceVu0FMATRIX vc, f32 scrw, f32 scrh, f32 scrz, f32 zmin, f32 zmax) {
    sceVu0UnitMatrix(vc);
    vc[0][0] = (scrz + scrz) / scrw;
    vc[1][1] = (scrz + scrz) / scrh;
    vc[2][2] = (zmax + zmin) / (zmax - zmin);
    vc[3][2] = (zmax * -2.0f * zmin) / (zmax - zmin);
    vc[2][3] = 1.0f;
    vc[3][3] = 0.0f;
}

s32 kitVu0ClipBBox(sceVu0FMATRIX lc, sceVu0FVECTOR *v) {
    s32 ret;

    __asm__ volatile(
        "lqc2         $vf4, 0x00(%1)\n"
        "lqc2         $vf5, 0x10(%1)\n"
        "lqc2         $vf6, 0x20(%1)\n"
        "lqc2         $vf7, 0x30(%1)\n"
        "li           %0, 63\n"
        "li           $8, 8\n"
    "loop_clip_all:\n"
        "lqc2         $vf8, 0x00(%2)\n"
        "addi         %2, %2, 0x10\n"
        "vmulax.xyzw  ACC, $vf4, $vf8x\n"
        "vmadday.xyzw ACC, $vf5, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6, $vf8z\n"
        "vmaddw.xyzw  $vf9, $vf7, $vf8w\n"
        "vclipw.xyz   $vf9, $vf9w\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "cfc2.ni     $3, $vi18\n"
        "and         %0, %0, $3\n"
        "beqz        %0, end_clip_all\n"
        "addi        $8, $8, -1\n"
        "bne         $0, $8, loop_clip_all\n"
        "addi        %0, $0, 1\n"
    "end_clip_all:"
    : "=r" (ret)
    : "r" (lc), "r" (v)
    : "$2" // hmm
    );
    
    return ret;
}

u128* kitClutMovieDraw(u128 *tmp, u32 offx, u32 offy, u32 lx, u32 ly, s32 movieNo, u64 tex0, u64 tex_clut) {
    kitADDR_DATA *draw_packet = (kitADDR_DATA *)tmp;
    kitDMAPACKET *tmp2 = (kitDMAPACKET *)tmp;

    if (vtWaveGlobal.tarostruct[movieNo] == NULL) {
        return tmp;
    }

    tmp2->ul[0] = DMAcnt | 19;
    tmp2->ui[2] = SCE_VIF1_SET_FLUSH(0);
    tmp2->ui[3] = SCE_VIF1_SET_DIRECT(19, 0);
    draw_packet++;

    draw_packet->data = SCE_GIF_SET_TAG(
        18,
        SCE_GS_TRUE,
        SCE_GS_TRUE,
        SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_FALSE),
        SCE_GIF_PACKED,
        1
    );
    draw_packet->addr = SCE_GIF_PACKED_AD;
    draw_packet++;

    draw_packet->addr = SCE_GS_TEST_1;
    draw_packet->data = SCE_GS_SET_TEST_1(SCE_GS_FALSE, 0, 0, 0, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZALWAYS);
    draw_packet++;
    draw_packet->addr = SCE_GS_TEX0_1;
    draw_packet->data = tex0;
    draw_packet++;
    draw_packet->addr = SCE_GS_TEXFLUSH;
    draw_packet->data = 0;
    draw_packet++;
    draw_packet->addr = SCE_GS_TEX1_1;
    draw_packet->data = SCE_GS_SET_TEX1_2(0, 0, SCE_GS_LINEAR, SCE_GS_LINEAR, 0, 0, 0);
    draw_packet++;
    draw_packet->addr = SCE_GS_CLAMP_1;
    draw_packet->data = SCE_GS_SET_CLAMP_1(SCE_GS_REPEAT, SCE_GS_REPEAT, 0, 0, 0, 0);
    draw_packet++;
    draw_packet->addr = SCE_GS_UV;
    draw_packet->data = SCE_GS_SET_UV(8, 8);
    draw_packet++;
    draw_packet->addr = SCE_GS_XYZ3;
    draw_packet->data = SCE_GS_SET_XYZ3(offx, offy, 0xFFFFFF);
    draw_packet++;
    draw_packet->addr = SCE_GS_UV;
    draw_packet->data = SCE_GS_SET_UV(((u32)pow(2, vtWaveGlobal.tarostruct[movieNo]->movie.tw) << 4) + 8, ((u32)pow(2, vtWaveGlobal.tarostruct[movieNo]->movie.th) << 4) + 8);
    draw_packet++;
    draw_packet->addr = SCE_GS_XYZ2;
    draw_packet->data = SCE_GS_SET_XYZ2(offx + lx, offy + ly, 0xFFFFFF);
    draw_packet++;
    draw_packet->addr = SCE_GS_TEX0_1;
    draw_packet->data = SCE_GS_SET_TEX0(tex_clut, 1, SCE_GS_PSMCT32, 3, 1, SCE_GS_TRUE, SCE_GS_DECAL, 0, 0, 0, 0, 0);
    draw_packet++;
    draw_packet->addr = SCE_GS_TEXFLUSH;
    draw_packet->data = 0;
    draw_packet++;
    draw_packet->addr = SCE_GS_TEX1_1;
    draw_packet->data = SCE_GS_SET_TEX1_2(0, 0, SCE_GS_NEAREST, SCE_GS_NEAREST, 0, 0, 0);
    draw_packet++;
    draw_packet->addr = SCE_GS_CLAMP_1;
    draw_packet->data = SCE_GS_SET_CLAMP_1(SCE_GS_REPEAT, SCE_GS_REPEAT, 0, 0, 0, 0);
    draw_packet++;
    draw_packet->addr = SCE_GS_UV;
    draw_packet->data = SCE_GS_SET_UV(0, 0);
    draw_packet++;
    draw_packet->addr = SCE_GS_XYZ3;
    draw_packet->data = SCE_GS_SET_XYZ3(offx, offy + ly, 0xFFFFFF);
    draw_packet++;
    draw_packet->addr = SCE_GS_UV;
    draw_packet->data = SCE_GS_SET_UV(0x80, 0x20);
    draw_packet++;
    draw_packet->addr = SCE_GS_XYZ2;
    draw_packet->data = SCE_GS_SET_XYZ2(offx + 0x400, offy + ly + 0x200, 0xFFFFFF);
    draw_packet++;
    draw_packet->addr = SCE_GS_TEST_1;
    draw_packet->data = SCE_GS_SET_TEST_1(SCE_GS_FALSE, 0, 0, 0, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZGREATER);
    draw_packet++;

    return (u128 *)draw_packet;
}