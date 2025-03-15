#include "harada/hr_main.h"
#include "hoshino/h_util.h"

MAPVWORK mapvw = {};
HRSCRST hrmapst = {};
HRSCRST hrbgst = {};
u32 *hrd_pack = NULL;
u32 *hrg_pack = NULL;
u32 *hrf_pack = NULL;
#ifndef KL2_VER_TRIAL
u32 *hrse_pack = NULL;
#endif
s32 hr_abeoff = 0;
s32 hr_objtype = 0;
u32 *hr_mt_addr = NULL;
vpmINFO hr_mtexi = {};
s32 hr_resKeep = 0;
s32 hr_resTmp = 0;
#ifndef KL2_VER_TRIAL
s16 hr_resFg = 0;
s16 hr_resSV = 0;
#endif
u32 *hr_obcdata = NULL;
u32 *hr_obcvpf = NULL;
VPOINFO *hr_obcvpo = NULL;

#ifdef KL2_VER_TRIAL
#define HR_PACK_MAX 4
#else
#define HR_PACK_MAX 6
#endif

extern s32 hrpt_sbgm; // TODO: remove
extern u16 hrpt_deb; // TODO: remove

void hr_cold_start() {
    hr_pflag_init();
    hr_pt_fclear();
    hrpt_deb = 0;
    hr_abeoff = 0;
#ifndef KL2_VER_TRIAL
    hrpt_sbgm = 0;
#endif
}

INCLUDE_ASM("harada/hr_main", hr_hpmk_init);

u32* hr_hpmk_blk(u16 gx, u16 gy, u16 gz, u32 *top) {
    HR_HPXZ *hxz;
    u32 xzcnt;
    u32 i;
    u32 cnt;
    u32 *dw;
    HR_HPYL *hyl;

    xzcnt = top[7];

    for (i = 0, hxz = (HR_HPXZ *)top + 4; i < xzcnt; i++, hxz++) {
        if (hxz->z > gz) {
            return NULL;
        }
        if (hxz->z >= gz) {
            if (hxz->x > gx) {
                return NULL;
            }
            if (hxz->x == gx) {
                break;
            }
        }
    }

    cnt = 0;
    if (i == xzcnt) {
        return NULL;
    }

    dw = top + (hxz->addr >> 2);
    xzcnt = *dw++;
    for (i = 0, hyl = (HR_HPYL *)dw; i < xzcnt; i++, hyl++) {
        if (hyl->y > gy) {
            return NULL;
        }
        if (hyl->y + hyl->cnt > gy) {
            break;
        }
        cnt += hyl->cnt;
    }

    if (i == xzcnt) {
        return NULL;
    }

    return dw + xzcnt + (cnt + (gy - hyl->y)) * 2;
}

u32* hr_hpmk(f32 x, f32 y, f32 z, u32 *top) {
    HR_HPMK *hp;
    u16 gx;
    u16 gy;
    u16 gz; // ?
    f32 f;

    hp = (HR_HPMK *)top;

    f = (x - hp->xs) / hp->gsize;
    if (f < 0.0f || f > hp->gcntx) {
        return NULL;
    }
    gx = f;

    f = (y - hp->ys) / hp->gsizey;
    if (f < 0.0f || f > hp->gcnty) {
        return NULL;
    }
    gy = f;

    f = (z - hp->zs) / hp->gsize;
    if (f < 0.0f || f > hp->gcntz) {
        return NULL;
    }
    gz = f;

    return hr_hpmk_blk(gx, gy, gz, top);
}

INCLUDE_ASM("harada/hr_main", hr_hpmk_deb);

void hr_stage_no(char *name, s32 fg) {
    char *hex[16] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"};

    strcat(name, hex[(GameGbl.vision / 0x0A00) % 10]);
    strcat(name, hex[(GameGbl.vision / 0x0100) % 10]);
    if (fg == 0) {
        strcat(name, hex[GameGbl.vision >> 4 & 0xF]);
        strcat(name, hex[GameGbl.vision & 0xF]);
    }
}

s32 hr_check_dmy(qword *addr) {
    if ((*addr)[0] == 0x6D6D7564 && (*addr)[1] == 0x363179) { // "dummy16"
        return 1;
    } else {
        return 0;
    }
}

INCLUDE_ASM("harada/hr_main", hr_decode_st11);

INCLUDE_ASM("harada/hr_main", hrStageDecode);

void hrStageDataLoad(s32 fg) {
#ifdef KL2_VER_TRIAL
    char Name[128];
#endif
    s32 num;
    u32 *buff;

#ifndef KL2_VER_TRIAL
    hrse_pack = (u32 *)-1;
#endif
    hrf_pack = (u32 *)-1;
    hrg_pack = (u32 *)-1;
    hrd_pack = (u32 *)-1;
    // ppwaku.gms = (u32 *)-1;
#ifndef KL2_VER_TRIAL
    hrpt_gms = (u32 *)-1;
    hr_retry_set();
#else
    hr_pflag_initSt();
    hr_restart_clear();

    strcpy(Name, "host0:../../../../main/image/data1/st");
    hr_stage_no(Name, 1);
    strcat(Name, "/03_harada.bin");
#endif

    hrd_pack = (u32 *)hGetDataAddr(3);
    if (hrd_pack == NULL) {
        hrd_pack = (u32 *)-1;
    }
    if ((s32)hrd_pack == -1) {
        KL2_DEBUG_PRINT(("No hrData !!!!\n"));
        return;
    }
    KL2_DEBUG_PRINT(("hrData %x %d ==== Read\n", hrd_pack, *hrd_pack));

    num = *hrd_pack;
    if (num > HR_PACK_MAX) {
        num = HR_PACK_MAX;
    }

    switch (num) {
#ifndef KL2_VER_TRIAL
        case 6:
            hrpt_gms = GetFHMAddress(hrd_pack, 5);
            if (hr_check_dmy((qword *)hrpt_gms)) {
                hrpt_gms = (u32 *)-1;
            }
        case 5:
            hrse_pack = GetFHMAddress(hrd_pack, 4);
            if (hr_check_dmy((qword *)hrse_pack)) {
                hrse_pack = (u32 *)-1;
            }
#endif
        case 4:
            hrf_pack = GetFHMAddress(hrd_pack, 3);
            if (hr_check_dmy((qword *)hrf_pack)) {
                hrf_pack = (u32 *)-1;
            }
        case 3:
            hrg_pack = GetFHMAddress(hrd_pack, 2);
            if (hr_check_dmy((qword *)hrg_pack)) {
                hrg_pack = (u32 *)-1;
            }
            num = 2;
        case 2:
            buff = GetFHMAddress(hrd_pack, 1);
            if (!hr_check_dmy((qword *)buff)) {
                // ppwaku.gms = buff;
            }
            num = 1;
        case 1:
            hrd_pack = GetFHMAddress(hrd_pack, 0);
            hrStageDecode();
            KL2_DEBUG_PRINT(("hrData %x %x ==== OK\n", (u32)hrd_pack, (u32)hrg_pack));
            break;
        default:
            KL2_DEBUG_PRINT(("hrData %s Error !!!!!!!\n", Name));
            hrd_pack = (u32 *)-1;
            break;
    }
}