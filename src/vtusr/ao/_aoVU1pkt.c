#include "vtusr/ao/aoVU1pkt.h"
#include "harada/h_vpm2.h"
#include "nakano/route.h"
#include "vtusr/ao/aoParticle.h"
#include "vtusr/vtwavemain.h"

AoParam **param;
AoParam *p_param;
AoData data;

static u32* set_common_data(u32 *bp, aoWaveStruct *s);
static u32* set_particle(u32 *bp, u32 n, aoWaveStruct *s);
static void increment_ptcl(u32 n, aoWaveStruct *s);
static void check_timing(u32 n, aoWaveStruct *s);
static void sort_obj(aoWaveStruct *s);
static void combsort(s32 first, s32 last);
static int calc_dist_vu0(sceVu0FVECTOR v0, sceVu0FVECTOR v1);

// TODO: remove
extern f32 kitGetWaveHeight(sceVu0FVECTOR *vec);

u128* DrawParticle(u128 *buf, aoWaveStruct *s) {
    u32 pkt_size;
    u32 *pkt_size_pos;
    u32 *bp = (u32 *)buf;
    u32 i;

    if (data.cam_scr_z != GameGbl.cam.scr_z) {
        h_vp_init((VPCLIP *)&data.ao_cvpm, GameGbl.cam.scr_z, 0.0f, 65536.0f, -512.0f, 0.0f, -1024.0f, 1);
    }
    data.cam_scr_z = GameGbl.cam.scr_z;
    sort_obj(s);

    *bp++ = DMAcnt | 16;
    *bp++ = 0;
    *bp++ = SCE_VIF1_SET_FLUSH(0);
    *bp++ = SCE_VIF1_SET_STCYCL(4, 4, 0);
    *bp++ = SCE_VIF1_SET_STMASK(0);
    *bp++ = 0;
    *bp++ = SCE_VIF1_SET_STMOD(0, 0);

    bp = set_common_data(bp, s);
    vtWaveGlobal.count -= 42;
    kitSetCounterParam(vtWaveGlobal.kitstruct, 0);

    *bp++ = DMAref | s->micro_prog_size;
    *bp++ = (u32)&Ao_particle_start;
    *bp++ = 0;
    *bp++ = 0;
    pkt_size_pos = bp++;
    *bp++ = 0;
    *bp++ = SCE_VIF1_SET_MSCAL(0x00, 0);
    *bp++ = SCE_VIF1_SET_BASE(13, 0);
    *bp++ = SCE_VIF1_SET_OFFSET(0x1FA, 0);
    *bp++ = SCE_VIF1_SET_FLUSHE(0);
    *bp++ = 0;
    *bp++ = 0;

    for (i = s->start_obj; i < s->n_obj; i++) {
        if (h_vpo_vclip(&cvpm, param[i]->pos, GameGbl.wvm)) {
            param[i]->sw = 0;
            param[i]->fr = param[i]->end_fr;
            param[i]->color[3] = 0.0f;
        } else {
            if (param[i]->sw == 1) {
                increment_ptcl(i, s);
            } else {
                check_timing(i, s);
            }
        }
        bp = set_particle(bp, i, s);
    }

    pkt_size = (((s32)(bp - pkt_size_pos) - 1) >> 2) & 0xFF;
    *pkt_size_pos = DMAcnt | pkt_size;
    vtWaveGlobal.count += 42;
    kitSetCounterParam(vtWaveGlobal.kitstruct, 0);
    return (u128 *)bp;
}

static u32* set_common_data(u32 *bp, aoWaveStruct *s) {
    u32 i;
    u32 j;
    f32 *fp;
    u32 *bp2;
    sceGsTex0 tex0 = s->ao_tex0;

    *bp++ = SCE_VIF1_SET_UNPACK(0x00, 15, VIF_UNPACK_V4_32, 0);
    bp2 = bp + 0x10;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            *bp++ = *(u32 *)&GameGbl.wsm[i][j];
            *bp2++ = *(u32 *)&s->local_clip[i][j];
        }
    }

    bp = bp2;
    fp = (f32 *)bp;
    fp[0] = 0.82f;
    fp[1] = 0.88f;
    fp[2] = 0.89f;

    fp[4] = 0.72f;
    fp[5] = 0.80f;
    fp[6] = 0.76f;

    fp[8] = 0.67f;
    fp[9] = 0.68f;
    fp[10] = 0.69f;

    fp[12] = 0.70f;
    fp[13] = 2823.1233f;
    fp[14] = 1.00f;

    if (vtWaveGlobal.vision == KL2_VISION(1, 0)) {
        fp[3] = 0.02f;
        fp[7] = 0.024f;
        fp[11] = 0.028f;
        fp[15] = 0.038f;
    } else if (vtWaveGlobal.vision == KL2_VISION(1, 2)) {
        fp[3] = 0.0045f;
        fp[7] = 0.0065f;
        fp[11] = 0.0085f;
        fp[15] = 0.0105f;
    }

    bp += 16;
    tex0.TFX = 0;
    tex0.TCC = 1;
    tex0.CSA = 5;
    *bp++ = *(u64 *)&tex0;
    *bp++ = *(u64 *)&tex0 >> 32;
    *bp++ = 0;
    *bp++ = 0;
    *bp++ = 1;
    *bp++ = 0x102B4000;
    *bp++ = 6;
    *bp++ = 0;
    *bp++ = data.total_ptcl | 0x8000;
    *bp++ = 0x502b4000;
    *bp++ = 0x42412;
    *bp++ = 0;

    return bp;
    
}

static u32* set_particle(u32 *bp, u32 n, aoWaveStruct *s) {
    f32 *fp;
    s32 i;

    *bp++ = SCE_VIF1_SET_UNPACK(0x8000, 7, VIF_UNPACK_V4_32, 0);

    fp = (f32 *)bp;
    fp[0] = param[n]->pos[0];
    fp[1] = param[n]->pos[1];
    fp[2] = param[n]->pos[2];
    if (n < data.n_far) {
        fp[3] = 0;
    } else if (n < data.n_mid) {
        fp[3] = 1.0f;
    } else {
        fp[3] = -1.0f;
    }
    fp[4] = fp[5] = param[n]->scale;
    fp[6] = s->growth[0];
    fp[7] = s->growth[1];
    fp[8] = param[n]->color[0];
    fp[9] = param[n]->color[1];
    fp[10] = param[n]->color[2];
    fp[11] = param[n]->color[3];
    fp[12] = 70.0f;
    fp[13] = 50.0f;
    fp[14] = 45.0f;
    fp[15] = param[n]->time;
    fp[16] = 3.8f;
    fp[17] = s->ao_tail;
    fp[18] = 3.0f;
    fp[19] = param[n]->height;
    fp[20] = 0.25f;
    fp[21] = param[n]->ptcl;
    fp[22] = param[n]->fr - s->ao_tail;
    fp[23] = 0.5f;
    fp[24] = 2.7f;
    fp[25] = param[n]->width;
    fp[26] = 0.0f;
    fp[27] = 3.4f;

    bp += 28;
    *bp++ = SCE_VIF1_SET_MSCALF(0x07, 0);
    for (i = (u32)bp >> 2 & 3; i > 0; i--) {
        *bp++ = 0;
    }

    return bp;
}

static void increment_ptcl(u32 n, aoWaveStruct *s) {
    s32 count = s->n_obj - n;
    f32 val;

    if (param[n]->fr < param[n]->end_fr) {
        if (vtWaveGlobal.pause) {
            return;
        }

        param[n]->fr++;
        param[n]->scale = s->ao_ptcl_size * param[n]->size + s->ao_ptcl_size;
        val = count * 4;
        param[n]->color[0] = param[n]->color[1] = param[n]->color[2] = 200.0f - val;
        param[n]->color[3] = 120.0f - val * 0.4f;

        if (SysGbl.proc_hcnt > 230) {
            if (n < s->far) {
                param[n]->color[3] -= 8.0f;
                param[n]->ptcl -= 3;
            } else {
                param[n]->color[3] -= 5.0f;
            }
        } else if (SysGbl.proc_hcnt > 185) {
            if (n < s->mid) {
                param[n]->color[3] -= 5.0f;
                param[n]->ptcl -= 2;
            } else {
                param[n]->color[3] -= 2.0f;
            }
        } else if (SysGbl.proc_hcnt > 180) {
            param[n]->color[3] -= 1.0f;
        }

        if (param[n]->ptcl < 3) {
            param[n]->ptcl = 3;
        }
    } else {
        param[n]->sw = 0;
        param[n]->fr = param[n]->end_fr;
        param[n]->color[3] = 0.0f;
    }
}

static void check_timing(u32 n, aoWaveStruct *s) {
    s32 height;
    sceVu0FVECTOR v = { param[n]->pos[0], 0.0f, param[n]->pos[2], 1.0f };

    height = kitGetWaveHeight(&v);
    if (height > 350) {
        if (height < param[n]->pre_height) {
            param[n]->sw = 1;
            param[n]->fr = param[n]->start_fr;
            param[n]->ptcl = param[n]->n_ptcl - ((s->n_obj - n) >> 2);
        }
    } else  {
        param[n]->fr = param[n]->end_fr;
    }
    param[n]->pre_height = height;
}

static void sort_obj(/* s2 18 */ aoWaveStruct *s) {
    /* s1 17 */ s32 i;
    /* a0 4 */ OBJWORK *klonoa = GameGbl.klonoa;
    /* a0 4 */ s32 michinori = GetMichinori(&klonoa->rtw) >> 12;

    if (vtWaveGlobal.vision == KL2_VISION(1, 0) || vtWaveGlobal.vision == KL2_VISION(1, 2)) {
        for (i = 0; i < s->n_obj; i++) {
            param[i]->dist = calc_dist_vu0(param[i]->pos, GameGbl.cam.posi);
        }
        combsort(0, s->n_obj - 1);
    }
}

static void combsort(/* a0 4 */ s32 first, /* a1 5 */ s32 last) {
    /* t4 12 */ s32 i;
    /* t0 8 */ s32 j;
    /* t3 11 */ s32 gap = last - first;
    /* t7 15 */ u8 changed;

    
}

// /* 001edae8 0000019c */ int SetParam(/* s0 16 */ vtDataPtr *vtdata) {
// 	/* s1 17 */ int n_obj;
// 	/* a0 4 */ int i;
// 	/* 0x0(sp) */ int status;
// }

// /* 001edc88 00000030 */ static int calc_dist_vu0(/* a0 4 */ float *v0, /* a1 5 */ float *v1) {
// 	/* 0x0(sp) */ VECTOR ret;
// }