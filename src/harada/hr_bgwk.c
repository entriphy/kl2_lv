#include "harada/hr_bgwk.h"
#include "harada/h_vpm2.h"

BGWK *hrbgbuff = NULL;
s32 hrcntbg = 0;
s32 hrcntdrawbg = 0;
mINFO hrbgi[6] = {};
u32 *hrbgbin[6] = {};

// TODO: delete once hr_main.c is implemented
u32 DELETE_1[] = {0, 0};
u32 DELETE_2;

void hr_bg_onoff(s32 no, s32 fg) {
    BGWK *bg;

    bg = hrbgbuff;
    if ((s32)bg != -1 && no < hrcntbg) {
        hrbgbuff[no].fg = fg;
    }
}

void hr_bginit() {
    BGWK *bg;
    mINFO *info;
    s32 i;

    hrbgbuff = (BGWK *)getBuff(1, sizeof(BGWK) * 6, "hrbgbuff", &i);
    if ((s32)hrbgbuff == -1) {
        // "☆☆☆☆BG cansel\n"
        KL2_DEBUG_PRINT(("\x81\x99\x81\x99\x81\x99\x81\x99""BG cansel\n"));
        hrcntbg = 0;
    } else {
        for (i = 0, bg = hrbgbuff, info = hrbgi; i < hrcntbg; i++, bg++, info++) {
            bg->fg = 1;
            bg->info = info;
            bg->rx = bg->ry = 0;
        }

        if (i != 6) {
            for (i = 6 - i; --i != -1; bg++) {
                bg->fg = 0;
            }
        }

        if (hrcntbg != 0) {
            hr_anmVPA_initBG();
        }
    }
}

static f32 get_bg_rot(s32 rot) {
    if (rot == 0) {
        return 0.0f;
    } else if (rot <= 0x8000) {
        return (f32)rot * KL2_PI * (1.0f / 32768.0f);
    } else {
        return (f32)(rot - 0x10000) * KL2_PI * (1.0f / 32768.0f);
    }
}

static void hr_bg_workclipM() {
    BGWK *bg;
    s32 i;
    sceVu0FMATRIX m;
    sceVu0FVECTOR v;
    u32 j;
    u32 max;
    u32 *list;
    mINFO *info; // ?

    h_vp_init(&cvbg, GameGbl.cam.scr_z, 1.0f, 65536.0f, 1024.0f, 1024.0f, 1024.0f, 0.0f);
    v[0] = v[1] = v[2] = 0.0f;
    v[3] = 1.0f;
    sceVu0UnitMatrix(m);
    sceVu0RotMatrixY(m, m, GameGbl.cam.ang[1]);
    sceVu0RotMatrixX(m, m, GameGbl.cam.ang[0]);
    sceVu0RotMatrixZ(m, m, GameGbl.cam.ang[2]);
    sceVu0TransMatrix(m, m, v);

    for (i = 0, bg = hrbgbuff; i < 6; i++, bg++) {
        if (bg->fg != 0) {
            hrcntdrawbg++;
            sceVu0UnitMatrix(bg->m0);
            if (bg->ry != 0) {
                sceVu0RotMatrixY(bg->m0, bg->m0, get_bg_rot(bg->ry));
            }
            if (bg->rx != 0) {
                sceVu0RotMatrixX(bg->m0, bg->m0, get_bg_rot(bg->rx));
            }
            sceVu0MulMatrix(bg->m, m, bg->m0);

            info = bg->info;
            max = info->vpm_block_num;
            if (max > 128) {
                max = 128;
            }
            info->block_list[0] = max;
            list = info->block_list + 1;
            for (j = 0; j < max; j++) {
                *list++ = j;
            }
        }
    }
}

void hr_bg_workclip() {
    hrcntdrawbg = 0;
    if (hrcntbg != 0) {
        if (GameGbl.pause_flag == 0) {
            hr_anmVPA_workBG();
        }
        hr_bg_workclipM();
    }
}
