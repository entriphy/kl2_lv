#include "kazuya/td_nejob.h"
#include "common.h"
#include "kazuya/bios.h"
#include "kazuya/cvar.h"
#include "kazuya/string.h"
#include "kazuya/td_job.h"
#include "kazuya/td_sys.h"

DVECTOR GIMBASE_NAM_ENTRY = { 246, 130 };
DVECTOR GIMBASE_NAM_PANEL = { 36, 28 };
DVECTOR GIMBASE_NAM_CRSS = { 64, 114 };
DVECTOR GIMBASE_NAM_CRSL = { 466, 128 };
DVECTOR GIMBASE_NAM_CRSB = { 44, 84 };
DVECTOR CHRBASE_NAM_UPPER = { 44, 40 };
DVECTOR CHRBASE_NAM_LOWER = { 80, 130 };
DVECTOR STRBASE_NAM_FUNC = { 474, 134 };
s32 chrrot_count = 0;
s32 chrmag_count = 0;
s32 usepage = 0;
s32 nextpage = 0;
s32 stpjob_count = 0;

static void kzTD_Delete_Chr() {
    if (crsB_H > 0) {
        crsB_H--;
        name_array[crsB_H] = 0;
    }
}

static s32 kzTD_Move_Counter() {
    s32 ret = 0;

    if (chrrot_count > 0) {
        chrrot_count++;
        if (chrrot_count > 10) {
            chrrot_count = -10;
            usepage = nextpage;
        }
        ret = 1;
    } else if (chrrot_count < 0) {
        chrrot_count++;
        if (chrrot_count >= 0) {
            chrrot_count = 0;
        }
        ret = 1;
    }

    if (chrmag_count > 0) {
        chrmag_count++;
        if (chrmag_count > 5) {
            chrmag_count = -5;
        }
        ret = 1;
    } else if (chrmag_count < 0) {
        chrmag_count++;
        if (chrmag_count >= 0) {
            chrmag_count = 0;
        }
        ret = 1;
    }


    return ret;
}

static void kzTD_Draw_NameChrs(s32 str_no) {
    sceVu0IVECTOR crd0;
    sceVu0IVECTOR crd1;
    sceVu0IVECTOR crd2;
    sceVu0IVECTOR crd3;
    sceVu0IVECTOR crd4;
    sceVu0IVECTOR crd5;
    sceVu0IVECTOR crd6;
    sceVu0IVECTOR crd7;
    sceVu0IVECTOR *src_array[4] = { &crd0, &crd1, &crd2, &crd3 };
    sceVu0IVECTOR *dst_array[4] = { &crd4, &crd5, &crd6, &crd7 };
    sceVu0IVECTOR *crdS;
    sceVu0IVECTOR *crdD;
    DVECTOR uv0;
    DVECTOR uv1;
    DVECTOR uv2;
    DVECTOR uv3;
    sceVu0FVECTOR fcrd;
    sceVu0FMATRIX mat;
    GIM_FORM **font_table = FontTables[FONT_JN];
    GIM_FORM *form;
    s16 *chr_table = Strings[str_no];
    f32 rot;
    s32 i;
    s32 j;
    s32 k;
    s32 add_X;
    s32 add_Y;
    s32 idx;

    if (chrrot_count == 0) {
        rot = 0.0f;
    } else if (chrrot_count > 0) {
        rot = (chrrot_count * KL2_PI2) / 10.0f;
    } else { // what
        rot = (chrrot_count * KL2_PI2) / 10.0f;
    }
    sceVu0UnitMatrix(mat);
    sceVu0RotMatrixY(mat, mat, rot);

    crd0[0] = crd2[0] = -10;
    crd1[0] = crd3[0] = 9;
    crd0[1] = crd1[1] = -10;
    crd2[1] = crd3[1] = 9;
    crd0[2] = crd1[2] = crd2[2] = crd3[2] = crd0[3] = crd1[3] = crd2[3] = crd3[3] = 0;
    for (i = 0; i < 4; i++) {
        crdS = src_array[i];
        sceVu0ITOF0Vector(fcrd, *crdS);
        sceVu0ApplyMatrix(fcrd, mat, fcrd);
        sceVu0FTOI4Vector(*crdS, fcrd);
        (*crdS)[1] >>= 1;
        (*crdS)[2] = 0xFFFF;
        (*crdS)[3] = 0;
    }

    for (i = 0; i < 10; i++) {
        add_Y = (CHRBASE_NAM_LOWER.vy + i * 30) << 3;

        for (j = 0; j < 9; j++) {
            add_X = (CHRBASE_NAM_LOWER.vx + j * 40) << 4;

            for (k = 0; k < 4; k++) {
                crdS = src_array[k];
                crdD = dst_array[k];
                SETVEC((*crdD), (*crdS)[0] + add_X, (*crdS)[1] + add_Y, (*crdS)[2], (*crdS)[3]);
            }

            idx = i * 9 + j;
            idx = chr_table[idx + 1];
            if (idx > 0) {
                form = font_table[idx - 1];
                SETDVEC(uv0, form->uv.vx, form->uv.vy);
                SETDVEC(uv1, form->uv.vx + form->wh.vx, form->uv.vy);
                SETDVEC(uv2, form->uv.vx, form->uv.vy + form->wh.vy);
                SETDVEC(uv3, form->uv.vx + form->wh.vx, form->uv.vy + form->wh.vy);
                kz_Set_Tex0_Imd(form->tex0);
                kz_Set_PolyFT4UV(&crd4, &crd5, &crd6, &crd7, &uv0, &uv1, &uv2, &uv3, &FCOL_STD);
            }
        }
    }
}

static void kzTD_Draw_Variable(DVECTOR *sxy, u32 sz, DVECTOR *wh, DVECTOR *uv, KZCOLOR *col) {
    sceVu0IVECTOR crd0;
    sceVu0IVECTOR crd1;
    sceVu0IVECTOR crd2;
    sceVu0IVECTOR crd3;
    sceVu0IVECTOR *crd_array[4] = { &crd0, &crd1, &crd2, &crd3 };
    sceVu0IVECTOR icenter;
    sceVu0IVECTOR *crd;
    sceVu0FVECTOR fcenter;
    sceVu0FVECTOR fcrd;
    DVECTOR uv0;
    DVECTOR uv1;
    DVECTOR uv2;
    DVECTOR uv3;
    f32 scale;
    s32 i;

    if (chrmag_count == 0) {
        kz_Set_SprtUV(sxy, sz, wh, uv, col);
        return;
    }

    if (chrmag_count > 0) {
        scale = (chrmag_count * 0.5f) / 5.0f + 1.0f;
    } else {
        scale = 1.0f - (chrmag_count * 0.5f) / 5.0f;
    }

    icenter[0] = sxy->vx + wh->vx / 2;
    icenter[1] = sxy->vy + wh->vy / 2;
    icenter[2] = icenter[3] = 0;
    sceVu0ITOF0Vector(fcenter, icenter);

    crd0[0] = crd2[0] = -(wh->vx / 2);
    crd1[0] = crd3[0] = -(wh->vx / 2) + (wh->vx - 1);
    crd0[1] = crd1[1] = -(wh->vy / 2);
    crd2[1] = crd3[1] = -(wh->vy / 2) + (wh->vy - 1);
    for (i = 0; i < 4; i++) {
        crd = crd_array[i];
        sceVu0ITOF0Vector(fcrd, *crd);
        sceVu0ScaleVector(fcrd, fcrd, scale);
        sceVu0AddVector(fcrd, fcrd, fcenter);
        sceVu0FTOI4Vector(*crd, fcrd);
        (*crd)[1] >>= 1;
        (*crd)[2] = sz;
        (*crd)[3] = 0;
    }

    SETDVEC(uv0, uv->vx, uv->vy);
    SETDVEC(uv1, uv->vx + wh->vx, uv->vy);
    SETDVEC(uv2, uv->vx, uv->vy + wh->vy);
    SETDVEC(uv3, uv->vx + wh->vx, uv->vy + wh->vy);
    kz_Set_PolyFT4UV(&crd0, &crd1, &crd2, &crd3, &uv0, &uv1, &uv2, &uv3, col);
}

static void kzTD_Draw_VrblGim(DVECTOR *sxy, u32 sz, KZCOLOR *col, s32 gim_no) {
    GIM_FORM *form = GimForms[gim_no];
    kz_Set_Tex0_Imd(form->tex0);
    kzTD_Draw_Variable(sxy, sz, &form->wh, &form->uv, col);
}

static void kzTD_Draw_VrblChr(DVECTOR *sxy, u32 sz, KZCOLOR *col, s32 font_no, s16 code) {
    if (code > 0) {
        GIM_FORM **font_table = FontTables[font_no];
        GIM_FORM *form = font_table[code - 1];
        kz_Set_Tex0_Imd(form->tex0);
        kzTD_Draw_Variable(sxy, sz, &form->wh, &form->uv, col);
    }
}

void kzTD_Job_Nam_Entry() {
    static s32 crsS_H = 0;
    static s32 crsS_V = 0;
    static s32 crsL_V = 0;
    static s32 usecrs = 0;
    s32 cntmove;
    s32 win_conf = WINDOW_ETC_00;
    s32 win_warn = WINDOW_ETC_05;
    DVECTOR sxy;
    s32 i;
    s32 str_no;
    s32 status;
    s32 offset;
    s32 func_array[5] = { STR_NAME_F0, STR_NAME_F1, STR_NAME_F2, STR_NAME_F3, STR_NAME_F4 };

    cntmove = kzTD_Move_Counter();
    name_array = &mci->name[1];
    for (crsB_H = 0; name_array[crsB_H] != 0; crsB_H++);
    kz_Draw_Cloud(CLOUD_NORMAL);
    kzTD_Set_GsEnv_Std();
    for (i = 0; i < 8; i++) {
        sxy.vx = GIMBASE_NAM_PANEL.vx + i * 72;
        sxy.vy = GIMBASE_NAM_PANEL.vy;
        kzGIM_Draw(&sxy, 0xFFFF, &GCOL_STD, GIM_SEL0000);
    }

    switch (usepage) {
        case 0:
            str_no = STR_NAME_P0;
            break;
        case 1:
            str_no = STR_NAME_P1;
            break;
        case 2:
        default:
            str_no = STR_NAME_P2;
            break;
    }

    for (i = 0; i < crsB_H; i++) {
        sxy.vx = CHRBASE_NAM_UPPER.vx + i * 72;
        sxy.vy = CHRBASE_NAM_UPPER.vy;
        kzCHR_Draw_Direct(&sxy, 0xFFFF, &FCOL_STD, FONT_JH, name_array[i]);
    }

    if (td_jobcnt == TD_JOB_NAM_ENTRY || td_jobcnt == TD_JOB_NAM_ENTRY_MAIN) {
        kzTD_Draw_Ground(GROUND_NAM_ENTRY);
        kzTD_Set_GsEnv_Std();
        for (i = 0; i < 5; i++) {
            sxy.vx = STRBASE_NAM_FUNC.vx;
            sxy.vy = STRBASE_NAM_FUNC.vy + i * 60;
            kzSTR_Draw(&sxy, 0xFFFF, &FCOL_STD, func_array[i]);
        }
    }

    if (td_jobcnt == TD_JOB_NAM_ENTRY) {
        if (kzTD_Set_Fade(FD_MODE_IN) != FD_STATUS_IN_END) {
            return;
        }

        kzTD_Step_Job(1);
        crsS_H = crsS_V = crsL_V = usecrs = usepage = 0;
        chrrot_count = -10;
        chrmag_count = 0;
        stpjob_count = 0;
    }

    if (td_jobcnt == TD_JOB_NAM_ENTRY_MAIN) {
        kzTD_Set_GsEnv_Std();
        kzTD_Draw_NameChrs(str_no);

        if (crsB_H < 8) {
            sxy.vx = GIMBASE_NAM_CRSB.vx + crsB_H * 72;
            sxy.vy = GIMBASE_NAM_CRSB.vy;
            kzGIM_Draw(&sxy, 0xFFFF, &GCOL_STD, GIM_SEL0001);
        }

        if (usecrs) {
            sxy.vx = GIMBASE_NAM_CRSL.vx;
            sxy.vy = GIMBASE_NAM_CRSL.vy + crsL_V * 60;
            kzTD_Draw_VrblGim(&sxy, 0xFFFF, &GCOL_STD, GIM_SEL0002);

            if (cntmove) {
                return;
            }

            if (stpjob_count != 0) {
                stpjob_count++;
                if (stpjob_count > 20) {
                    stpjob_count = 0;
                    if (name_array[0] != 1) {
                        kzTD_Init_Window(win_conf, 0, 1);
                        kzTD_Step_Job(1);
                    } else {
                        kzTD_Init_Window(win_warn, 0, 1);
                        kzTD_Step_Job(2);
                    }
                }
            } else {
                if (pPAD_TRG_CROSS(kpd0)) {
                    switch (crsL_V) {
                        case 0:
                        case 1:
                        case 2:
                            if (usepage != crsL_V) {
                                nextpage = crsL_V;
                                chrrot_count = 1;
                                chrmag_count = 1;
                            }
                            break;
                        case 3:
                            if (crsB_H > 0) {
                                kzTD_Delete_Chr();
                                chrmag_count = 1;
                            }
                            break;
                        case 4:
                        default:
                            chrmag_count = 1;
                            stpjob_count = 1;
                            break;
                    }
                } else if (pPAD_TRG_CIRCLE(kpd0)) {
                    kzTD_Delete_Chr();
                } else {
                    if (pPAD_REP_UP(kpd0)) {
                        crsL_V--;
                        if (crsL_V < 0) {
                            crsL_V = 0;
                        }
                    }
                    if (pPAD_REP_DOWN(kpd0)) {
                        crsL_V++;
                        if (crsL_V > 4) {
                            crsL_V = 4;
                        }
                    }

                    if (pPAD_REP_LEFT(kpd0)) {
                        crsS_H = 8;
                        crsS_V = crsL_V * 2;
                        usecrs = 0;
                    }
                }
            }
        } else {
            sxy.vx = GIMBASE_NAM_CRSS.vx + crsS_H * 40;
            sxy.vy = GIMBASE_NAM_CRSS.vy + crsS_V * 30;
            kzTD_Draw_VrblGim(&sxy, 0xFFFF, &GCOL_STD, GIM_SEL0003);

            if (crsB_H > 0) {
                offset = crsB_H - 1;
                offset *= 72;

                sxy.vx = GIMBASE_NAM_PANEL.vx + offset;
                sxy.vy = GIMBASE_NAM_PANEL.vy;
                kzTD_Draw_VrblGim(&sxy, 0xFFFF, &GCOL_STD, GIM_SEL0000);

                sxy.vx = CHRBASE_NAM_UPPER.vx + offset;
                sxy.vy = CHRBASE_NAM_UPPER.vy;
                kzTD_Draw_VrblChr(&sxy, 0xFFFF, &FCOL_STD, FONT_JH, name_array[crsB_H - 1]);
            }

            if (cntmove) {
                return;
            }

            if (pPAD_TRG_CROSS(kpd0)) {
                if (crsB_H < 8) {
                    name_array[crsB_H] = kzCHR_Get_Indirect(str_no, crsS_V * 9 + crsS_H);
                    chrmag_count = 1;
                    crsB_H++;
                }
            } else if (pPAD_TRG_CIRCLE(kpd0)) {
                kzTD_Delete_Chr();
            } else {
                if (pPAD_REP_UP(kpd0)) {
                    crsS_V--;
                    if (crsS_V < 0) {
                        crsS_V = 0;
                    }
                }
                if (pPAD_REP_DOWN(kpd0)) {
                    crsS_V++;
                    if (crsS_V > 9) {
                        crsS_V = 9;
                    }
                }

                if (pPAD_REP_LEFT(kpd0)) {
                    crsS_H--;
                    if (crsS_H < 0) {
                        crsS_H = 0;
                    }
                }
                if (pPAD_REP_RIGHT(kpd0)) {
                    crsS_H++;
                    if (crsS_H > 8) {
                        crsS_H = 8;
                        crsL_V = crsS_V / 2;
                        usecrs = 1;
                    }
                }
            }

        }
    } else {
        if (td_jobcnt == TD_JOB_NAM_ENTRY_CONFIRM) {
            switch (kzTD_Draw_Window(win_conf)) {
                case WN_STATUS_00:
                    td_jobcnt_next0 = TD_JOB_OPT_TOP;
                    td_jobcnt_next1 = TD_JOB_TTL_MENU;
                    kzTD_Step_Job(2);
                    break;
                case WN_STATUS_01:
                    kzTD_Back_Job(1);
                    break;
            }
        }

        if (td_jobcnt == TD_JOB_NAM_ENTRY_WARNING) {
            if (kzTD_Draw_Window(win_warn) != WN_STATUS_WAIT) {
                kzTD_Back_Job(2);
            }
        }

        if (td_jobcnt == TD_JOB_NAM_ENTRY_END) {
            if (kzTD_Set_Fade(FD_MODE_OUT) != FD_STATUS_OUT_END) {
                return;
            }
            kzTD_Change_Job();
        }
    }
}

s16 *name_array;
s32 crsB_H;
