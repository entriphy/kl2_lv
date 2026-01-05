#include "harada/hr_obcon.h"
#include "harada/hr_obcon1.h"
#include "harada/hr_obcon2.h"
#include "harada/hr_obcon3.h"
#include "harada/hr_obcon4.h"
#include "harada/hr_mapdr.h"
#include "harada/hr_pall.h"
#include "harada/hr_pflag.h"
#include "harada/hr_tobc.h"
#include "harada/hr_vpa.h"
#include "hoshino/h_event.h"
#include "hoshino/h_util.h"
#include "nakano/dma.h"
#include "nakano/objfunc.h"
#include "nakano/route.h"
#include "okanoyo/okio.h"

static HR_RTC rt0701bill[2] = {
    { 1, 0x01560000, 0x019F0000, 0 },
    { 3, 0x01040000, 0x01580000, 0 },
};

static HR_RTC rt0701syaw[2] = {
    { 1, 0x02220000, 0x02DC0000, 0 },
    { 3, 0x01E00000, 0x02300000, 0 },
};

static HR_RTC rt0701brg[2] = {
    { 1, 0x01FD0000, 0x02600000, 0 },
    { 3, 0x01B30000, 0x02180000, 0 },
};

static HR_RTC rt0704tow[4] = {
    { 1, 0x000E0000, 0x00280000, 0 },
    { 2, 0x00380000, 0x015A0000, 0 },
    { 3, 0x00500000, 0x006C0000, 0 },
    { 4, 0x00500000, 0x006C0000, 0 },
};

static HR_RTC rt0206iwa[2] = {
    { 0, 0x005D0000, 0x008B0000, 0 },
    { 1, 0x00300000, 0x00598000, 0 },
};

static HR_RTC rt1402ashi0[2] = {
    { 0, 0x05500000, 0x07000000, 0 },
    { 0, 0x03800000, 0x07000000, 0 },
};

static HR_RTC rt1402ashi1[2] = {
    { 0, 0x05680000, 0x07000000, 0 },
    { 0, 0x03800000, 0x00000000, 0 },
};

static HR_RTC rt1402ashi2[2] = {
    { 0, 0x05800000, 0x07000000, 0 },
    { 0, 0x03800000, 0x07000000, 0 },
};

static HR_RTC rt1404ashi0[3] = {
    { 0, 0x03000000, 0x04000000, 0 },
    { 0, 0x01800000, 0x02000000, 0 },
    { 0, 0x02700000, 0x04000000, 0 },
};

static HR_RTC rt1404ashi1[3] = {
    { 0, 0x03180000, 0x04000000, 0 },
    { 0, 0x01800000, 0x02000000, 0 },
    { 0, 0x02700000, 0x04000000, 0 },
};

static HR_OBJ hr_objtable[19] = {
    {
        -125.06559753417969f, -315.8927917480469f, -3494.921630859375f,
        0.0f, 0.0f, 0.0f,
        1, 0,
        2, rt0701bill, 1, 3, 0
    },
    {
        -2634.080078125f, 187.56480407714844f, -1082.193603515625f,
        0.0f, 0.0f, 0.0f,
        2, 1,
        2, rt0701syaw, 4, 1, 1
    },
    {
        -2864.159912109375f, -67.23519897460938f, -2537.377685546875f,
        0.0f, 0.0f, 0.0f,
        0, 2,
        2, rt0701brg, 2, 1, 2
    },
    {
        2703.4384765625f, -1170.233642578125f, -736.74560546875f,
        0.0f, 0.0f, 0.0f,
        1, 3,
        4, rt0704tow, 1, 3, 3
    },
    {
        2364.6015625f, -1170.233642578125f, -877.0960083007812f,
        0.0f, 0.0f, 0.0f,
        2, 4,
        4, rt0704tow, 2, 3, 4
    },
    {
        2224.251220703125f, -1170.233642578125f, -1215.9327392578125f,
        0.0f, 0.0f, 0.0f,
        3, 5,
        4, rt0704tow, 4, 3, 5
    },
    {
        2364.6015625f, -1170.233642578125f, -1554.7679443359375f,
        0.0f, 0.0f, 0.0f,
        4, 6,
        4, rt0704tow, 8, 3, 6
    },
    {
        2703.4384765625f, -1170.233642578125f, -1695.1199951171875f,
        0.0f, 0.0f, 0.0f,
        5, 7,
        4, rt0704tow, 16, 3, 7
    },
    {
        3042.275146484375f, -1170.233642578125f, -1554.7679443359375f,
        0.0f, 0.0f, 0.0f,
        6, 8,
        4, rt0704tow, 32, 3, 8
    },
    {
        3182.62548828125f, -1170.233642578125f, -1215.9327392578125f,
        0.0f, 0.0f, 0.0f,
        7, 9,
        4, rt0704tow, 64, 3, 9
    },
    {
        3042.275146484375f, -1170.233642578125f, -877.0960083007812f,
        0.0f, 0.0f, 0.0f,
        8, 10,
        4, rt0704tow, 128, 3, 10
    },
    {
        2699.60009765625f, -1238.2591552734375f, -1207.4000244140625f,
        0.0f, 0.0f, 0.0f,
        9, 11,
        4, rt0704tow, 256, 3, 11
    },
    {
        2699.60009765625f, -1238.2591552734375f, -1207.4000244140625f,
        0.0f, 0.0f, 0.0f,
        0, 12,
        4, rt0704tow, 512, 3, 12
    },
    {
        297.1903991699219f, -549.1840209960938f, 159.6208038330078f,
        0.0f, 0.0f, 0.0f,
        0, 13,
        2, rt0206iwa, 1, 7, 0
    },
    {
        8912.8740234375f, 961.0656127929688f, 3342.656005859375f,
        0.0f, 0.0f, 0.0f,
        0, 14,
        2, rt1402ashi0, 0, 14, 0
    },
    {
        11394.5068359375f, 1081.283203125f, 3127.760009765625f,
        0.0f, 0.0f, 0.0f,
        1, 15,
        2, rt1402ashi1, 0, 14, 1
    },
    {
        13909.58203125f, 1166.3759765625f, 3007.7919921875f,
        0.0f, 0.0f, 0.0f,
        2, 16,
        2, rt1402ashi2, 0, 14, 2
    },
    {
        3131.05908203125f, 2102.384033203125f, -1938.1055908203125f,
        0.0f, 0.0f, 0.0f,
        4, 17,
        3, rt1404ashi0, 0, 14, 3
    },
    {
        5097.548828125f, 2190.927978515625f, -2098.587158203125f,
        0.0f, 0.0f, 0.0f,
        5, 18,
        3, rt1404ashi1, 0, 14, 4
    },
};

static HR_HOBJ hr_hobjtable[19] = {
    {
        -156.96640014648438f, -503.85760498046875f, -3458.67041015625f,
        0.0f, 0.0f, 0.0f,
        63, 2,
    },
    {
        -2629.263916015625f, 133.9936065673828f, -1063.366455078125f,
        0.0f, 0.0f, 0.0f,
        65, 2,
    },
    {
        -2740.49609375f, -190.81280517578125f, -2573.08154296875f,
        0.0f, 0.0f, 0.0f,
        64, 2,
    },
    {
        2703.4384765625f, -1200.3536376953125f, -736.74560546875f,
        0.0f, 0.0f, 0.0f,
        66, 2,
    },
    {
        2364.6015625f, -1200.3536376953125f, -877.0960083007812f,
        0.0f, 0.785398006439209f, 0.0f,
        66, 2,
    },
    {
        2224.251220703125f, -1200.3536376953125f, -1215.9327392578125f,
        0.0f, 1.570796012878418f, 0.0f,
        66, 2,
    },
    {
        2364.6015625f, -1200.3536376953125f, -1554.7679443359375f,
        0.0f, 2.356194019317627f, 0.0f,
        66, 2,
    },
    {
        2703.4384765625f, -1200.3536376953125f, -1695.1199951171875f,
        0.0f, 3.141592025756836f, 0.0f,
        66, 2,
    },
    {
        3042.275146484375f, -1200.3536376953125f, -1554.7679443359375f,
        0.0f, -2.356194019317627f, 0.0f,
        66, 2,
    },
    {
        3182.62548828125f, -1200.3536376953125f, -1215.9327392578125f,
        0.0f, -1.570796012878418f, 0.0f,
        66, 2,
    },
    {
        3042.275146484375f, -1200.3536376953125f, -877.0960083007812f,
        0.0f, -0.785398006439209f, 0.0f,
        66, 2,
    },
    {
        2699.60009765625f, -1238.2591552734375f, -1207.4000244140625f,
        0.0f, 0.0f, 0.0f,
        67, 2,
    },
    {
        2699.60009765625f, -1238.2591552734375f, -1207.4000244140625f,
        0.0f, 0.0f, 0.0f,
        68, 2,
    },
    {
        297.1903991699219f, -549.1840209960938f, 159.6208038330078f,
        0.0f, 0.0f, 0.0f,
        74, 2,
    },
    {
        8906.2255859375f, 849.760009765625f, 3318.9599609375f,
        0.0f, 0.0f, 0.0f,
        89, 2,
    },
    {
        11362.345703125f, 968.0592041015625f, 3152.47998046875f,
        0.0f, 0.0f, 0.0f,
        90, 2,
    },
    {
        13893.953125f, 1066.204833984375f, 2992.06396484375f,
        0.0f, 0.0f, 0.0f,
        91, 2,
    },
    {
        3131.05908203125f, 2102.384033203125f, -1938.1055908203125f,
        0.0f, 0.0f, 0.0f,
        92, 2,
    },
    {
        5097.548828125f, 2193.535888671875f, -2098.587158203125f,
        0.0f, 0.0f, 0.0f,
        93, 2,
    },
};

static s32 hr_me_0701[] = { 3, 0, 1, 2 };
static s32 hr_me_0704[] = { 10, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
static s32 hr_me_1402[] = { 3, 14, 15, 16 };
static s32 hr_me_1404[] = { 2, 17, 18 };
static s32 hr_sw_0402[] = { 1, 0, 2, 0 };

s32 hr_route_clipM(HR_RTC *hrtc, s32 count, s32 no, s32 mc) {
    s32 i;

    for (i = 0; i < count; i++, hrtc++) {
        if (no == hrtc->no && mc >= hrtc->min && mc <= hrtc->max) {
            return i + 1;
        }
    }

    return 0;
}

static s32 hr_route_clip(HR_OBJ *obj) {
    OBJWORK *kw;

    kw = GameGbl.klonoa;
    return hr_route_clipM(obj->rtcaddr, obj->rtc, GetMichiNo(kw->rtw.rtp), kw->rtw.mcn);
}

OBJWORK* hr_get_obcon(s16 stat1) {
    OBJWORK *objw = SearchOBJWORK(SysGbl.objwork, SysGbl.n_objw);
    if (objw != NULL) {
        objw->stat0 = 5;
        objw->stat1 = stat1;
        objw->bun0 = 0;
        objw->dreff = NULL;
        objw->drmir = NULL;
        objw->draw = NULL;
    }
    return objw;
}

void hr_comm_drawVPO(sceVu0FMATRIX m, VPOINFO *info, s32 objno) {
    sceVu0FMATRIX sm;

    if (info != NULL) {
        sceVu0MulMatrix(sm, GameGbl.wsm, m);
        hrDrawVpoi(sm, info, objno);
    }
}

static void hr_mapexpl_draw(OBJWORK *objw) {
    HR_OBJW *ow;
    s32 i;

    for (i = 0, ow = (HR_OBJW *)objw->work; i < objw->reg0; i++, ow++) {
        switch (ow->drawno) {
            case DMAPEXPL_VPO:
                hr_comm_drawVPO(ow->m, ow->info, ow->objno);
                break;
            case DMAPEXPL_VPOMOT:
                if (KL2_VER_COND(1, !(ow->hh->flag & 1))) {
                    hr_to_modeldraw(ow->hobj);
                } else {
                    KL2_VER_RETAIL_ONLY(hr_to_modeldrawRL(ow->hobj, ow->hh->reg));
                }
                hr_comm_drawVPO(ow->m, ow->info, ow->objno);
                break;
            case DMAPEXPL_VPOS:
                if (!(ow->obj->extra & 2)) {
                    if (KL2_VER_COND(1, !(ow->hh->flag & 1))) {
                        hr_to_modeldraw(ow->hobj);
                    } else {
                        KL2_VER_RETAIL_ONLY(hr_to_modeldrawRL(ow->hobj, ow->hh->reg));
                    }
                }
                hr_comm_drawVPO(ow->m, ow->info, ow->objno);
                break;
            case DMAPEXPL_MOT:
                if (KL2_VER_COND(1, !(ow->hh->flag & 1))) {
                    hr_to_modeldraw(ow->hobj);
                } else {
                    KL2_VER_RETAIL_ONLY(hr_to_modeldrawRL(ow->hobj, ow->hh->reg));
                }
                break;
        }
    }
}

static s32 hr_mapexpl_getmem(OBJWORK *objw, s32 count) {
    objw->work = getmem(count * sizeof(HR_OBJW));
    if ((s32)objw->work == -1) {
        objw->stat0 = 0;
        return 0;
    } else {
        KL2_VER_RETAIL_ONLY(memset(objw->work, 0, count * sizeof(HR_OBJW)));
        objw->reg0 = count;
        objw->draw = hr_mapexpl_draw;
        return 1;
    }
}

static void hr_mapexpl_set(HR_OBJW *ow, s32 no) {
    sceVu0FVECTOR v;
    HR_OBJ *ho;

    ho = ow->obj = &hr_objtable[no];
    ow->hh = &hr_hobjtable[no];
    ow->hobj = NULL;
    ow->objno = 0;
    ow->bun0 = 0;
    ow->drawno = 0;

    if ((s32)hr_obcvpo == -1) {
        ow->info = NULL;
    } else {
        ow->info = &hr_obcvpo[ow->obj->fhmno];
    }

    v[0] = ow->obj->rx;
    v[1] = ow->obj->ry;
    v[2] = ow->obj->rz;
    v[3] = 1.0f;
    sceVu0UnitMatrix(ow->m);
    sceVu0RotMatrix(ow->m, ow->m, v);
    v[0] = ow->obj->px;
    v[1] = ow->obj->py;
    v[2] = ow->obj->pz;
    sceVu0TransMatrix(ow->m, ow->m, v);

    if (hr_restart_check(ho->res)) {
        if (ho->extra & 4) {
            ow->bun0 = 3;
        } else {
            ow->bun0 = 2;
            ow->objno++;
        }
    }
}

s32* hr_init_obconM(s32 id, s32 *tbl) {
    OBJWORK *objw;
    HR_OBJW *ow;
    s32 i;
    s32 max;

    objw = (OBJWORK *)hr_get_obcon(id);
    if (objw == NULL) {
        return NULL;
    }

    switch (id) {
        case 0:
            max = *tbl++;
            if (hr_mapexpl_getmem(objw, max)) {
                ow = (HR_OBJW *)objw->work;
                for (i = 0; i < max; i++, ow++, tbl++) {
                    hr_mapexpl_set(ow, *tbl);
                }
            }
            break;
        case 1:
            hr_swtrg_getset(objw, tbl);
            break;
        case 2:
            if (hrpt_deb != 0) {
                hr_gpt_getset(objw, tbl);
            }
            break;
        case 4:
            if (hr_ptmini_getset(objw) == 0) {
                objw->stat0 = 0;
            }
            break;
        case 5:
            if (hr_pnt_getset(objw)) {
                KL2_VER_RETAIL_ONLY(objw->prty = 0xFF);
            } else {
                objw->stat0 = 0;
                objw = NULL;
            }
            break;
        case 3:
            hr_ptefc_set(objw);
            if (objw->stat0 == 0) {
                objw = NULL;
            }
            break;
        case 6:
            hr_obcex_getset(objw, (s32)tbl);
            break;
        default:
            objw->stat0 = 0;
            KL2_VER_RETAIL_ONLY(objw = NULL);
            break;
    }

    return (s32 *)objw;
}

static s32 hr_check_obcd(s32 data, s32 vpo) {
    s32 fg;

    fg = 0;
    if (vpo != 0) {
        if ((s32)hr_obcvpo == -1) {
            return 0;
        }
        fg++;
    }

    return fg;
}

void hr_init_obcon() {
    s32 var = 0;

    switch (GameGbl.vision) {
        case 0x0100:
            if (!hr_pflag_check(PT0100_S1)) {
                hr_init_obconM(HR_GPUPPET, hr_psw_0100);
            }
            hr_init_obconM(6, (s32 *)0x200);
            break;
#ifdef KL2_VER_RETAIL
        case 0x0102:
            if (!hr_pflag_check(PT0102_S0)) {
                hr_init_obconM(HR_GPUPPET, hr_psw_0102);
            }
            break;
#endif
        case 0x0104:
            if (!hr_pflag_check(PT0104_S0)) {
                hr_init_obconM(HR_GPUPPET, hr_psw_0104);
            }
            break;
        case 0x0400:
            if (!hr_pflag_check(PT0400_S1)) {
                hr_init_obconM(HR_GPUPPET, hr_psw_0400);
            }
            break;
#ifdef KL2_VER_RETAIL
        case 0x040A:
            if (!hr_pflag_check(PT040A_S0)) {
                var++;
            } else if (!hr_pflag_check(PT040A_S1)) {
                var++;
            }
            if (var) {
                hr_gpt_resReg1((OBJWORK *)hr_init_obconM(HR_GPUPPET, hr_psw_040a), hr_respt040a, 2);
            }
            break;
#endif
        case 0x040B:
#ifdef KL2_VER_TRIAL
            if (!hr_pflag_check(PT040B_S0)) {
                hr_init_obconM(2, hr_psw_040b);
            }
#else
            if (!hr_pflag_check(PT040B_S0)) {
                var++;
            } else if (!hr_pflag_check(PT040B_S1) && !hr_pflag_check(PT040B_S2)) {
                var++;
            }
            if (var) {
                hr_gpt_resReg1((OBJWORK *)hr_init_obconM(HR_GPUPPET, hr_psw_040b), hr_respt040b, 3);
            }
#endif
            break;
#ifdef KL2_VER_RETAIL
        case 0x0505:
            if (!hr_pflag_check(PT0505_S0) && !hr_pflag_check(PT0505_S1)) {
                hr_init_obconM(HR_GPUPPET, hr_psw_0505);
            }
            break;
#endif
#ifdef KL2_VER_RETAIL
        case 0x0605:
            if (!hr_pflag_check(PT0605_S1)) {
                hr_init_obconM(HR_GPUPPET, hr_psw_0605);
            }
            break;
#endif
        case 0x0701:
            if (hr_check_obcd(1, 1)) {
                hr_init_obconM(HR_MAPEXPL, hr_me_0701);
            }
            break;
        case 0x0704:
            if (hr_check_obcd(1, 1)) {
                hr_init_obconM(HR_MAPEXPL, hr_me_0704);
            }
            break;
#ifdef KL2_VER_RETAIL
        case 0x0801:
            if (!hr_pflag_check(PT08XX_S0)) {
                hr_init_obconM(HR_GPUPPET, hr_psw_0801);
            }
            break;
#endif
#ifdef KL2_VER_RETAIL
        case 0x0805:
            if (!hr_pflag_check(PT0805_S0)) {
                hr_init_obconM(HR_GPUPPET, hr_psw_0805);
            }
            break;
#endif
#ifdef KL2_VER_RETAIL
        case 0x0900:
            if (!(hr_resSV & 0x1)) {
                OBJWORK *objw = (OBJWORK *)hr_init_obconM(HR_OBCEX00, (s32 *)0x201);
                if (objw != NULL) {
                    objw->prty = 0xFF;
                }
            }
            break;
#endif
#ifdef KL2_VER_RETAIL
        case 0x0902:
            if (hr_pflag_check(PT09XX_S1) == 0) {
                hr_init_obconM(HR_GPUPPET, hr_psw_0902);
            }
            break;
#endif
        case 0x0A04:
            if (hr_pflag_check(PT1004_S0) == 0) {
                hr_init_obconM(HR_GPUPPET, hr_psw_1004);
            }
            break;
        case 0x0E02:
            if (hr_check_obcd(1, 1)) {
                hr_init_obconM(HR_MAPEXPL, hr_me_1402);
            }
            break;
        case 0x0E04:
            if (hr_check_obcd(1, 1)) {
                hr_init_obconM(HR_MAPEXPL, hr_me_1404);
#ifdef KL2_VER_RETAIL
                if (!hr_pflag_check(PT14XX_S1)) {
                    hr_init_obconM(HR_GPUPPET, hr_psw_1404);
                }
#endif
            }
            break;
#ifdef KL2_VER_RETAIL
        case 0x0F07:
            if (!hr_pflag_check(PT1507_S0)) {
                var++;
            } else if (!hr_pflag_check(PT1507_S1)) {
                var++;
            }
            if (var) {
                hr_gpt_resReg1((OBJWORK *)hr_init_obconM(HR_GPUPPET, hr_psw_1507), hr_respt1507, 2);
            }
            break;
#endif
#ifdef KL2_VER_RETAIL
        case 0x100A:
            if (!hr_pflag_check(PT16XX_S1)) {
                hr_init_obconM(HR_GPUPPET, hr_psw_160a);
            }
            break;
        case 0x1500:
            if (!hr_pflag_check(PT2100_S1)) {
                hr_init_obconM(HR_GPUPPET, hr_psw_2100);
            }
            break;
        case 0x1600:
            if (!hr_pflag_check(PT4002_S2)) {
                hr_init_obconM(HR_GPUPPET, hr_psw_2200);
            }
            break;
        case 0x1800:
            if (!hr_pflag_check(PT20XX_S3)) {
                var++;
            } else if (!hr_pflag_check(PT20XX_S4)) {
                var++;
            }
            if (var) {
                hr_gpt_resReg1((OBJWORK *)hr_init_obconM(HR_GPUPPET, hr_psw_2400), hr_respt2400, 2);
            }
            break;
        case 0x1A00:
            if (!hr_pflag_check(PT20XX_S6)) {
                hr_init_obconM(HR_GPUPPET, hr_psw_2600);
            }
            break;
        case 0x1B00:
            if (!hr_pflag_check(PT2XXX_S2)) {
                hr_init_obconM(HR_GPUPPET, hr_psw_2700);
            }
            break;
#endif
    }

    if ((s32)hrpt_mini_addr != -1) {
        hr_init_obconM(HR_GPTMINI, NULL);
    }

    if (!hrpt_deb) {
        return;
    }

    hr_pflag_AreaStart(0);
    if (hrpt_flag) {
        KL2_VER_RETAIL_ONLY(OkLastBalloonPicClr());
        if (hr_init_obconM(HR_DPUPPET, NULL) == NULL) {
            hr_pt_fclear();
        }
    }
}

static void hr_mapexpl_flag(HR_OBJW *ow) {
    sceVu0FVECTOR v;
    HR_OBJ *obj;
    s32 flag;
    s32 stat1; // ?
    HR_HOBJ *hh; // ?
    sceVu0FVECTOR *vp; // ?

    obj = ow->obj;
    if (!(obj->extra & 0x8)) {
        flag = obj->on & hEvGetFlag();
    } else if ((flag = hr_route_clip(obj)) != 1) {
        flag = 0;
    }

    if (flag != 0) {
        KL2_VER_RETAIL_ONLY(hr_restart_set(ow->obj->res));

        if (!(obj->extra & 0x4)) {
            ow->objno++;
        }

        if (obj->extra & KL2_VER_COND(0x1, 0x21)) {
            v[0] = obj->px;
            v[1] = obj->py;
            v[2] = obj->pz;
            v[3] = 1.0f;
            stat1 = obj->stat1;
#ifdef KL2_VER_RETAIL
            if (obj->extra & 0x20) {
                stat1 += 23;
                hSeKeyOn(KL2_VAG(2, 73, 1, 0, 10, 0x04, 200, 200), NULL, 0);
            }
#endif
            abSetExplosion(stat1, v);
        }

        if ((ow->hobj = (void *)hr_to_workget()) != NULL) {
            hr_set_hobject2(ow->hobj, ow->hh);
            hr_set_hobject3(ow);
            if (!(obj->extra & 4)) {
                ow->drawno = DMAPEXPL_VPOMOT;
            } else {
                ow->drawno = DMAPEXPL_MOT;
            }
            ow->bun0 = MAPEXPL_MOT;
            hh = ow->hh;
#ifdef KL2_VER_RETAIL
            if (!(hh->flag & 0x6)) {
                return;
            }
            if (hh->flag & 2) {
                v[0] = hh->px;
                v[1] = hh->py;
                v[2] = hh->pz;
                v[3] = 1.0f;
                vp = &v;
            } else {
                vp = NULL;
            }
            hSeKeyOn(hh->vag, *vp, 0);
#endif
        } else if (!(obj->extra & 0x4)) {
            ow->drawno = DMAPEXPL_VPO;
            ow->bun0 = MAPEXPL_AFTER;
        } else {
            ow->drawno = DMAPEXPL_NON;
            ow->bun0 = MAPEXPL_ERASE;
        }
    } else if (hr_route_clip(ow->obj)) {
        ow->drawno = DMAPEXPL_VPO;
    } else {
        ow->drawno = DMAPEXPL_NON;
    }
}

static void hr_mapexpl_mot(HR_OBJW *ow) {
    KL2_VER_RETAIL_ONLY(sceVu0FVECTOR v);

    if (hr_to_motion(ow->hobj, 0)) {
        if (ow->obj->extra & 2) {
            hr_to_workdel(ow->hobj);
            ow->hobj = NULL;
            if (!(ow->obj->extra & 4)) {
                ow->drawno = DMAPEXPL_VPO;
                ow->bun0 = MAPEXPL_AFTER;
            } else {
                ow->drawno = DMAPEXPL_NON;
                ow->bun0 = MAPEXPL_ERASE;
            }
        } else {
            hr_to_motionpause(ow->hobj, 1);
            if (KL2_VER_COND(1, !(ow->obj->extra & 4))) {
                ow->drawno = DMAPEXPL_VPOS;
                ow->bun0 = MAPEXPL_AFTER;
            } else {
                ow->drawno = DMAPEXPL_MOT;
                ow->bun0 = MAPEXPL_AFTM;
            }
        }
    }

    ow->count++;

#ifdef KL2_VER_RETAIL
    if (!(ow->obj->extra & 0x10) || ow->count != 125) {
        return;
    }
    v[0] = ow->obj->px;
    v[1] = ow->obj->py;
    v[2] = ow->obj->pz;
    v[3] = 1.0f;
    abSetExplosion(ow->obj->stat1, v);

    if (ow->hh->flag & 8) {
        hSeKeyOn(ow->hh->vag, NULL, 0);
    }
#endif
}

static void hr_mapexpl_after(HR_OBJW *ow) {
    if (hr_route_clip(ow->obj)) {
        if (ow->hobj != NULL) {
            ow->drawno = DMAPEXPL_VPOS;
        } else {
            ow->drawno = DMAPEXPL_VPO;
        }
    } else {
        ow->drawno = DMAPEXPL_NON;
    }
}

static void hr_mapexpl_erase(HR_OBJW *ow) {
    // Empty function
}

#ifdef KL2_VER_RETAIL
static void hr_mapexpl_aftm(HR_OBJW *ow) {
    if (hr_route_clip(ow->obj)) {
        ow->drawno = DMAPEXPL_MOT;
    } else {
        ow->drawno = DMAPEXPL_NON;
    }
}
#endif

static void (*hrMapExplTbl[])(HR_OBJW *) = {
    hr_mapexpl_flag,
    hr_mapexpl_mot,
    hr_mapexpl_after,
    hr_mapexpl_erase,
#ifdef KL2_VER_RETAIL
    hr_mapexpl_aftm
#endif
};

static void hr_mapexpl(OBJWORK *objw) {
    HR_OBJW *ow;
    s32 i;

    for (i = 0, ow = (HR_OBJW *)objw->work; i < objw->reg0; i++, ow++) {
        hrMapExplTbl[ow->bun0](ow);
    }
}

static void hr_dummy_obcw(OBJWORK *objw) {
    // Empty function
}

static void (*hrObjFuncTbl[8])(OBJWORK *) = {
    hr_mapexpl,
    hr_switch_trg,
    hr_game_puppet,
    hr_ptefc_work,
    hr_game_puppet,
    hr_game_puppet,
    hr_obcex_work,
    hr_dummy_obcw
};

void hr_work_obcon(OBJWORK *objw) {
    hrObjFuncTbl[objw->stat1](objw);
}

void hrLoadObcData(char *stname) {
    char Name[128];
    char GName[128];
    char VName[128];
    s32 i;
    s32 j;
    VPOINFO *info;

    hr_obcvpf = (u32 *)-1;
    hr_obcdata = (u32 *)-1;
    hr_obcvpo = (VPOINFO *)-1;
    strcpy(Name, stname);
    strcat(Name, "/hro");
    hr_stage_no(Name, 0);
    strcpy(GName, Name);
    strcpy(VName, Name);
    strcat(Name, ".bin");
    strcat(GName, ".gms");
    strcat(VName, ".vpf");
    hr_obcdata = getBuff(0, 0, GName, &i);
    if ((s32)hr_obcdata != -1) {
        nkLoadGms((qword *)hr_obcdata);
        sceGsSyncPath(0, 0);
        freeBuff(0, 0, GName);
    }
    hr_obcvpf = getBuff(0, 0, VName, &i);
    if ((s32)hr_obcvpf != -1) {
        j = *hr_obcvpf;
        hr_obcvpo = getBuff(1, j * 16, "obcvpo", &i);
        if ((s32)hr_obcvpo != -1) {
            for (i = 0, info = hr_obcvpo; i < j; i++, info++) {
                DecodeVpo2(GetFHMAddress(hr_obcvpf, i), info);
            }
        }
    }
    hr_obcdata = (u32 *)-1;
}
