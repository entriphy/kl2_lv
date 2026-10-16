#include "vtusr/ao/aoVU1pkt.h"
#include "harada/h_vpm2.h"
#include "nakano/route.h"
#include "okanoyo/okio.h"
#include "vtusr/ao/aoParticle.h"
#include "vtusr/vtwavemain.h"

AoParam **param __attribute__((aligned(16)));
AoParam *p_param __attribute__((aligned(16)));
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

static void sort_obj(aoWaveStruct *s) {
    s32 i;
    OBJWORK *klonoa = GameGbl.klonoa;
    s32 michinori = GetMichinori(&klonoa->rtw) >> 12;

    if (
        (vtWaveGlobal.vision == KL2_VISION(1, 0) && ((michinori < 630) || (michinori > 2324 && michinori < 2654) || (michinori > 3447 && michinori < 3771) || (michinori > 5520 && michinori < 5835)))
        ||
        (vtWaveGlobal.vision == KL2_VISION(1, 2) && ((michinori < 469) || (michinori > 1296 && michinori < 1360) || (michinori > 1151 && michinori < 1241) || (michinori > 7072 && michinori < 8037)))
       )
    {
        for (i = 0; i < s->n_obj; i++) {
            param[i]->dist = calc_dist_vu0(param[i]->pos, GameGbl.cam.posi);
        }
        combsort(0, s->n_obj - 1);
    }
}

// https://decomp.me/scratch/Uj3c4
static void combsort(s32 first, s32 last) {
    s32 i;
    s32 j;
    s32 gap = last - first;
    u8 changed = 1;

    if (gap > 0) {
        while (changed || gap > 1) {
            if (gap != 1) {
                int x = 10; int y = 13;
                if ((gap = gap * x / y) == 10 || gap == 9) gap = 11;
            }

            changed = 0; // unused?
            for (i = first, j = first + gap; j <= last; i++, j++) {
                if (param[i]->dist < param[j]->dist) {
                    AoParam *tmp = param[i];
                    param[i] = param[j];
                    param[j] = tmp;
                }
            }
        }
    }
}

s32 SetParam(vtDataPtr *vtdata) {
    s32 n_obj;
    s32 i;
    s32 status;

    data.total_ptcl = *((u32 *)vtdata->spray_data_buf)++; // clangd thinks this is illegal lol
    n_obj = *((u32 *)vtdata->spray_data_buf)++;
    data.n_far = n_obj * 0.3f;
    data.n_mid = n_obj * 0.6f;

    param = NULL;
    p_param = NULL;
    param = getBuff(1, n_obj * sizeof(AoParam *), NULL, &status);
    if (status == -1) {
        printf("ao param alloc fail\n");
        return -1;
    }
    p_param = getBuff(1, n_obj * sizeof(AoParam), NULL, &status);
    if (status == -1) {
        printf("ao p_param alloc fail\n");
        return -1;
    }

    memcpy(p_param, vtdata->spray_data_buf, n_obj * sizeof(AoParam));
    for (i = 0; i < n_obj; i++) {
        param[i] = &p_param[i];
    }
    h_vp_init((VPCLIP *)&data.ao_cvpm, GameGbl.cam.scr_z, 0.0f, 65536.0f, -512.0f, 0.0f, -1024.0f, 1);
    data.cam_scr_z = GameGbl.cam.scr_z;
    return n_obj;
}

static s32 calc_dist_vu0(sceVu0FVECTOR v0, sceVu0FVECTOR v1) {
    sceVu0FVECTOR ret;

    __asm__ volatile(
        "lqc2    $vf4, 0x0(%0)\n"
        "lqc2    $vf5, 0x0(%1)\n"
        "vsub.xz $vf6, $vf4, $vf5\n"
        "vmul.xz $vf7, $vf6, $vf6\n"
        "vaddz.x $vf8, $vf7, $vf7\n"
        "sqc2    $vf8, 0x0(%2)\n"
    : : "r" (v0), "r" (v1), "r" (ret));

    return ret[0];
}