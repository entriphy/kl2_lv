#include "vtusr/ao/aoParticle.h"
#include "okanoyo/okio.h"
#include "vtusr/ao/aoEnv.h"
#include "vtusr/vtwavemain.h"

static void aoVu0ViewClipMatrix(sceVu0FMATRIX vc, f32 scrw, f32 scrh, f32 scrz, f32 zmin, f32 zmax);

aoWaveStruct* aoWaveInit(vtDataPtr *vtdata) {
    aoWaveStruct *s;
    s32 status;

    s = getBuff(1, sizeof(aoWaveStruct), NULL, &status);
    if (status == -1) {
        printf("ao struct alloc fail\n");
        return NULL;
    }

    memset(s, 0, sizeof(aoWaveStruct));
    if (vtWaveGlobal.vision == KL2_VISION(1, 0)) {
        s->n_obj = SetParam(vtdata);
        s->start_obj = 0;
        s->far = s->n_obj * 0.65f;
        s->mid = s->n_obj * 0.55f;
        s->ao_ptcl_size = 3000.0f;
        s->ao_tail = 40.0f;
        s->growth[0] = 63000.0f;
        s->growth[1] = 3000.0f;
    } else if (vtWaveGlobal.vision == KL2_VISION(1, 2)) {
        s->n_obj = SetParam(vtdata);
        s->start_obj = 3;
        s->far = s->n_obj * 0.78f;
        s->mid = s->n_obj * 0.63f;
        s->ao_ptcl_size = 7400.0f;
        s->ao_tail = 50.0f;
        s->growth[0] = 50000.0f;
        s->growth[1] = 3400.0f;
    }

    if (s->n_obj != -1) {
        aoVu0ViewClipMatrix(s->view_clip, 768.0f, 2160.0f, 512.0f, 0.1f, 65535.0f);
        s->ao_tex0 = vtdata->tex0[3];
        s->micro_prog_size = ((u32)&Ao_particle_end - (u32)&Ao_particle_start) / 0x10 + 1;
    } else {
        return NULL;
    }

    return s;
}

u128* aoExecWave(u128 *pkt) {
    sceVu0MulMatrix(vtWaveGlobal.aostruct->local_clip, vtWaveGlobal.aostruct->view_clip, GameGbl.wvm);
    pkt = setSprayEnv(pkt, vtWaveGlobal.aostruct);
    pkt = DrawParticle(pkt, vtWaveGlobal.aostruct);
    return pkt;
}

void aoWaveEnd() {
    // Empty function
}

static void aoVu0ViewClipMatrix(sceVu0FMATRIX vc, f32 scrw, f32 scrh, f32 scrz, f32 zmin, f32 zmax) {
    f32 zsub = zmax - zmin;
    __asm__ volatile(
        "vmul.xyzw  $vf4, $vf0, $vf0\n"
        "vmr32.xyzw $vf5, $vf0\n"
        "vmr32.xyzw $vf6, $vf5\n"
        "vmr32.xyzw $vf7, $vf5\n"
        "sqc2       $vf7, 0x00(%0)\n"
        "sqc2       $vf6, 0x10(%0)\n"
        "sqc2       $vf5, 0x20(%0)\n"
        "sqc2       $vf4, 0x30(%0)\n"
    : : "r" (vc));

    vc[0][0] = scrz * 2 / scrw;
    vc[1][1] = scrz * 2 / scrh;
    vc[2][2] = (zmax + zmin) / zsub;
    vc[3][2] = (zmax * -2.0f * zmin) / zsub;
    vc[2][3] = 1.0f;
    vc[3][3] = 0.0f;
}