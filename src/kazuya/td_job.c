#include "kazuya/td_job.h"
#include "kazuya/td_fljob.h"
#include "kazuya/td_mhjob.h"
#include "kazuya/td_nejob.h"
#include "harada/hr_pall.h"
#include "kazuya/bios.h"
#include "kazuya/cvar.h"
#include "kazuya/string.h"
#include "kazuya/td_sys.h"
#include "nakano/sinit.h"

s32 first_enter = 1;
s32 after_puppet_dst = 0;
s32 offset_X = 2048;
s32 offset_Y = 2048;
DVECTOR GIMBASE_1ST_LOGO = { 136, 176 };
DVECTOR GIMBASE_TTL_WAIT = { 246, 330 };
DVECTOR GIMBASE_TTL_LOGO = { 28, 32 };
DVECTOR STRBASE_OPT_SCREXPLAIN = { 48, 54 };
DVECTOR STRBASE_OPT_CURRENT = { 366, 192 };
DVECTOR STRBASE_OPT_PAD = { 304, 266 };
DVECTOR STRBASE_OPT_SOUND = { 448, 266 };
DVECTOR GIMBASE_PAD_CONTROLER = { 316, 192 };
DVECTOR STRBASE_PAD_TYPE = { 240, 160 };
DVECTOR STRBASE_PAD_RU = { 508, 192 };
DVECTOR STRBASE_PAD_RD = { 508, 320 };
DVECTOR STRBASE_PAD_RL = { 244, 260 };
DVECTOR STRBASE_PAD_RR = { 508, 260 };
DVECTOR STRBASE_PAD_ACTION = { 250, 352 };
DVECTOR GIMBASE_SND_MONO = { 344, 160 };
DVECTOR GIMBASE_SND_STEREO = { 296, 160 };
DVECTOR GIMBASE_SND_5P1CH = { 266, 160 };
DVECTOR STRBASE_SND_MODE = { 376, 348 };
DVECTOR GIMBASE_ADJ_SQUARE = { 16, 16 };
DVECTOR GIMSIZE_ADJ_SQUARE = { 608, 416 };
DVECTOR GIMBASE_ADJ_TRIANGLE = { 140, 101 };
DVECTOR STRBASE_ADJ_SCREXPLAIN = { 130, 71 };
DVECTOR GIMBASE_WMP_MENU = { 260, 190 };
DVECTOR GIMBASE_WMP_STATUS = { 48, 36 };
DVECTOR STRBASE_WMP_PLACE = { 52, 394 };
DVECTOR GIMBASE_GAM_PSPLACE = { 196, 90 };
DVECTOR GIMBASE_GAM_PAUSE = { 260, 130 };
DVECTOR GIMBASE_GAM_VISION_S = { 164, 144 };
DVECTOR GIMBASE_GAM_START = { 328, 144 };
DVECTOR GIMBASE_GAM_STGNAME = { 140, 224 };
DVECTOR GIMBASE_GAM_STGINTRO = { 140, 296 };
DVECTOR GIMBASE_GAM_VISION_O = { 174, 90 };
DVECTOR GIMBASE_GAM_OVER = { 338, 90 };
KZCOLOR GCOL_ADJ_SQUARE = { 0xFF, 0x00, 0x00, 0x80 };
KZCOLOR GCOL_ADJ_TRIANG = { 0xFF, 0x00, 0x00, 0x80 };

void kzTD_Step_Job(s32 add) {
    td_jobcnt += add;
}

void kzTD_Back_Job(s32 sub) {
    td_jobcnt -= sub;
}

void kzTD_Change_Job() {
    if (td_jobcnt_next0 <= TD_JOB_NONE) return;
    if (td_jobcnt_next0 >= TD_JOB_NUM) return;

    td_jobcnt_current = td_jobcnt_next0;
    td_jobcnt = td_jobcnt_next0;
    td_jobcnt_next0 = td_jobcnt_next1;
    td_jobcnt_next1 = TD_JOB_NONE;
}

void kzTD_Call_Job() {
    if (td_jobcnt_sub <= TD_JOB_NONE) return;
    if (td_jobcnt_sub >= TD_JOB_NUM) return;
    
    td_jobcnt_ret = td_jobcnt_current;
    td_jobcnt = td_jobcnt_sub;
    td_jobcnt_sub = TD_JOB_NONE;
}

void kzTD_Return_Job() {
    if (td_jobcnt_ret <= TD_JOB_NONE) return;
    if (td_jobcnt_ret >= TD_JOB_NUM) return;

    td_jobcnt = td_jobcnt_ret;
    td_jobcnt_ret = TD_JOB_NONE;
}

void kzTD_Draw_Common_Ttl() {
    kzTD_Draw_Ground(GROUND_OPT_SCREXPLAIN);
    kzTD_Draw_Ground(GROUND_OPT_HELPINFO);
}

void kzTD_Init_All() {
    kzTD_Init_SelViewer(SELECT_ETC_PADEXP0, 0, 0);
    kzTD_Init_SelViewer(SELECT_ETC_PADEXP1, 0, 0);
    kzTD_Init_SelViewer(SELECT_ETC_PADEXP2 ,0, 1);
    kzTD_Init_SelViewer(SELECT_ETC_PADEXP3, 0, 0);
    kzTD_Init_SelViewer(SELECT_ETC_PADEXP4, 0, 0);
    kzTD_Init_SelViewer(SELECT_ETC_PADEXP5, 0, 0);
    kzTD_Init_SelViewer(SELECT_ETC_PADEXP6, 0, 0);
    td_jobcnt_current = TD_JOB_IDLE;
    td_jobcnt = TD_JOB_IDLE;
    td_jobcnt_ret = TD_JOB_NONE;
    td_jobcnt_sub = TD_JOB_NONE;
    td_jobcnt_next1 = TD_JOB_NONE;
    td_jobcnt_next0 = TD_JOB_NONE;
    vision_count = 0;
    pause_return = TD_JOB_IDLE;
    pause_interval = 0;
    cloud_flag = CLOUD_NONE;
}

void kzTD_Job_Idle() {
    // Empty function
}

void kzTD_Job_1st_Logo() {
	static s32 count = 0;

    kzTD_Set_GsEnv_Std();
    kzGIM_Draw(&GIMBASE_1ST_LOGO, 0xFFFF, &GCOL_STD, GIM_PBYNAM);
    if (td_jobcnt == TD_JOB_1ST_LOGO) {
        if (kzTD_Set_Fade(FD_MODE_IN) != FD_STATUS_IN_END) {
            return;
        }
        count = 0;
        kzTD_Step_Job(1);
    }
    if (td_jobcnt == TD_JOB_1ST_LOGO_MAIN) {
        count++;
        if (count > 120) {
            td_jobcnt_next0 = TD_JOB_TTL_MENU;
            kzTD_Step_Job(1);
        }
    }
    if (td_jobcnt == TD_JOB_1ST_LOGO_END) {
        if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
            kzTD_Change_Job();
        }
    }
}

void kzTD_Job_Pup_Wait() {
	static s32 vision = KL2_VISION(1, 0);

    if (td_jobcnt == TD_JOB_PUP_WAIT) {
        kzTD_Step_Job(1);
    }
    if (td_jobcnt == TD_JOB_PUP_WAIT_MAIN) {
        if (!hr_pt_check()) {
            vision = after_puppet_dst;
            td_jobcnt_next0 = TD_JOB_IDLE;
            kzTD_Step_Job(1);
        }
    }
    if (td_jobcnt == TD_JOB_PUP_WAIT_END) {
        nkChangeArea(vision, 0, 0, 0.0f);
        kzTD_Change_Job();
    }
}

void kzTD_Job_Ttl_Menu() {
	static u32 vision = KL2_VISION(1, 0);
	static s32 count = 0;
	static s32 demo_no = 0;
	s32 sel_no = SELECT_TRI_TTLMENU;
	s32 status;

    kz_Draw_Cloud(CLOUD_NORMAL);
    kzTD_Set_GsEnv_Std();
    kzGIM_Draw(&GIMBASE_TTL_LOGO, 0xFFFF, &GCOL_STD, GIM_LOGO);

    if (td_jobcnt == TD_JOB_TTL_MENU) {
        if (kzTD_Set_Fade(FD_MODE_IN) != FD_STATUS_IN_END) {
            return;
        }
        kzTD_Step_Job(1);
        count = 0;
        kzTD_Init_Selector(sel_no, 0, 0);
    }

    status = kzTD_Draw_Selector(sel_no);
    if (td_jobcnt == TD_JOB_TTL_MENU_MAIN) {
        if (status == SL_STATUS_WAIT) {
            if (pPAD_TRG_START(kpd0) || pPAD_TRG_CROSS(kpd0)) {
                if (kzTD_Get_IdxPlate(sel_no) != 0) {
                    vision = KL2_VISION(5, 0);
                } else {
                    vision = KL2_VISION(1, 0);
                }
                td_jobcnt_next0 = TD_JOB_IDLE;
                kzTD_Close_Selector(sel_no, 1);
                kzTD_Step_Job(1);
            } else if (pPAD_TRG_LEFT(kpd0)) {
                count = 0;
                kzTD_CsrMove_Left(sel_no);
            } else if (pPAD_TRG_RIGHT(kpd0)) {
                count = 0;
                kzTD_CsrMove_Right(sel_no);
            }
        }

        count++;
        if (count > 600) {
            if (demo_no != 0) {
                vision = KL2_VISION(5, 0);
            } else {
                vision = KL2_VISION(1, 0);
            }

            demo_no ^= 1;
            td_jobcnt_next0 = TD_JOB_IDLE;
            kzTD_Step_Job(1);
        }
    }

    if (td_jobcnt == TD_JOB_TTL_MENU_END) {
        if (count > 600) {
            if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
                nkGoPlayDemo();
                nkChangeArea(vision, 0, 0, 0.0f);
                kzTD_Change_Job();
            }
        } else {
            if (status == SL_STATUS_OUT_END && kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
                nkChangeArea(vision, 0, 0, 0.0f);
                kzTD_Change_Job();
            }
        }
    }
}

void kzTD_Job_Opt_Top() {
    s32 sel_no = SELECT_OPT_TOP;
    s32 status;
    s32 str_no0;
    s32 str_no1;

    kz_Draw_Cloud(CLOUD_NORMAL);
    kzTD_Draw_Common_Ttl();
    kzTD_Set_GsEnv_Std();
    kzSTR_Draw(&STRBASE_OPT_SCREXPLAIN, 0xFFFF, &FCOL_STD, STR_ETC_13);

    if (td_jobcnt == TD_JOB_OPT_TOP) {
        if (kzTD_Set_Fade(FD_MODE_IN) != FD_STATUS_IN_END) {
            return;
        }
        kzTD_Step_Job(1);
        kzTD_Init_Selector(sel_no, -1, -1);
    }

    status = kzTD_Draw_Selector(sel_no);
    if (status == SL_STATUS_WAIT) {
        if (pPAD_TRG_CROSS(kpd0)) {
            switch (kzTD_Get_IdxPlate(sel_no)) {
                case 0:
                    td_jobcnt_sub = TD_JOB_OPT_PAD;
                    break;
                case 1:
                    td_jobcnt_sub = TD_JOB_OPT_SOUND;
                    break;
                case 2:
                    td_jobcnt_sub = TD_JOB_OPT_ADJUST;
                    break;
                default:
                    td_jobcnt_sub = TD_JOB_NONE;
                    break;
            }
            
            kzTD_Close_Selector(sel_no, 1);
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_UP(kpd0)) {
            kzTD_CsrMove_Up(sel_no);
        } else if (pPAD_TRG_DOWN(kpd0)) {
            kzTD_CsrMove_Down(sel_no);
        }
    }

    if (mci->pad != 0) {
        str_no0 = STR_OPTION_05;
    } else {
        str_no0 = STR_OPTION_04;
    }
    
    switch (mci->sound) {
        case 0:
            str_no1 = STR_OPTION_06;
            break;
        case 1:
            str_no1 = STR_OPTION_07;
            break;
        case 2:
            str_no1 = STR_OPTION_08;
            break;
        default:
            str_no1 = STR_OPTION_08;
            break;
    }

    kzSTR_Draw(&STRBASE_OPT_CURRENT, 0xFFFF, &FCOL_STD, STR_ETC_17);
    kzSTR_Draw(&STRBASE_OPT_PAD, 0xFFFF, &FCOL_STD, str_no0);
    kzSTR_Draw(&STRBASE_OPT_SOUND, 0xFFFF, &FCOL_STD, str_no1);

    if (td_jobcnt == TD_JOB_OPT_TOP_END && status == SL_STATUS_OUT_END) {
        switch (td_jobcnt_sub) {
            case TD_JOB_NONE:
                if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
                    kzTD_Change_Job();
                }
                break;
            case TD_JOB_OPT_ADJUST:
                if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
                    kzTD_Init_Window(WINDOW_ETC_04, 0, 0);
                    kzTD_Call_Job();
                }
                break;
            default:
                kzTD_Call_Job();
                break;
        }
    }
}

void kzTD_Job_Opt_Pad() {
    s32 sel_no = SELECT_OPT_PAD;
    s32 status;
    s32 str_no0;
    s32 str_no1;
    s32 str_no2;

    kz_Draw_Cloud(CLOUD_NORMAL);
    kzTD_Draw_Common_Ttl();
    kzTD_Draw_SelViewer(SELECT_ETC_PADEXP0);
    kzTD_Set_GsEnv_Std();
    kzSTR_Draw(&STRBASE_OPT_SCREXPLAIN, 0xFFFF, &FCOL_STD, STR_ETC_13);

    if (td_jobcnt == TD_JOB_OPT_PAD) {
        kzTD_Init_Selector(sel_no, 0, mci->pad);
        kzTD_Step_Job(1);
    }

    status = kzTD_Draw_Selector(sel_no);
    if (status == SL_STATUS_WAIT) {
        if (pPAD_TRG_CROSS(kpd0)) {
            mci->pad = kzTD_Get_IdxPlate(sel_no);
            kzTD_Close_Selector(sel_no, 1);
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_CIRCLE(kpd0)) {
            kzTD_Close_Selector(sel_no, 0);
            kzTD_Step_Job(1);
        }else if (pPAD_TRG_UP(kpd0)) {
            kzTD_CsrMove_Up(sel_no);
        } else if (pPAD_TRG_DOWN(kpd0)) {
            kzTD_CsrMove_Down(sel_no);
        }
    }

    if (kzTD_Get_IdxPlate(sel_no) == 0) {
        str_no0 = STR_OPTION_04;
        str_no1 = STR_ETC_14;
        str_no2 = STR_ETC_15;
    } else {
        str_no0 = STR_OPTION_05;
        str_no1 = STR_ETC_15;
        str_no2 = STR_ETC_14;
    }

    kzGIM_Draw(&GIMBASE_PAD_CONTROLER, 0xFFFF, &GCOL_STD, GIM_SEL0000);
    kzSTR_Draw(&STRBASE_PAD_TYPE, 0xFFFF, &FCOL_STD, str_no0);
    kzSTR_Draw(&STRBASE_PAD_RU, 0xFFFF, &FCOL_STD, str_no1);
    kzSTR_Draw(&STRBASE_PAD_RD, 0xFFFF, &FCOL_STD, str_no1);
    kzSTR_Draw(&STRBASE_PAD_RL, 0xFFFF, &FCOL_STD, str_no2);
    kzSTR_Draw(&STRBASE_PAD_RR, 0xFFFF, &FCOL_STD, str_no2);
    kzSTR_Draw(&STRBASE_PAD_ACTION, 0xFFFF, &FCOL_STD, STR_ETC_16);

    if (td_jobcnt == TD_JOB_OPT_PAD_END && status == SL_STATUS_OUT_END) {
        kzTD_Return_Job();
    }
}

void kzTD_Job_Opt_Sound() {
    s32 sel_no = SELECT_OPT_SOUND1;
    s32 status;
    s32 str_no;

    kz_Draw_Cloud(CLOUD_NORMAL);
    kzTD_Draw_Common_Ttl();
    kzTD_Draw_SelViewer(SELECT_ETC_PADEXP0);
    kzTD_Set_GsEnv_Std();
    kzSTR_Draw(&STRBASE_OPT_SCREXPLAIN, 0xFFFF, &FCOL_STD, STR_ETC_13);

    if (td_jobcnt == TD_JOB_OPT_SOUND) {
        kzTD_Init_Selector(sel_no, 0, mci->sound);
        kzTD_Step_Job(1);
    }

    status = kzTD_Draw_Selector(sel_no);
    if (status == SL_STATUS_WAIT) {
        if (pPAD_TRG_CROSS(kpd0)) {
            mci->sound = kzTD_Get_IdxPlate(sel_no);
            kzTD_Close_Selector(sel_no, 1);
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_CIRCLE(kpd0)) {
            kzTD_Close_Selector(sel_no, 0);
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_UP(kpd0)) {
            kzTD_CsrMove_Up(sel_no);
        } else if (pPAD_TRG_DOWN(kpd0)) {
            kzTD_CsrMove_Down(sel_no);
        }
    }

    if (kzTD_Get_IdxPlate(sel_no) == 0) {
        kzGIM_Draw(&GIMBASE_SND_MONO, 0xFFFF, &GCOL_STD, GIM_SEL0000);
        str_no = STR_OPTION_06;
    } else {
        kzGIM_Draw(&GIMBASE_SND_STEREO, 0xFFFF, &GCOL_STD, GIM_SEL0001);
        str_no = STR_OPTION_07;
    }
    kzSTR_Draw(&STRBASE_SND_MODE, 0xFFFF, &FCOL_STD, str_no);

    if (td_jobcnt == TD_JOB_OPT_SOUND_END && status == SL_STATUS_OUT_END) {
        kzTD_Return_Job();
    }
}

void kzTD_Job_Opt_Adjust() {
    sceVu0IVECTOR *crd;
    sceVu0IVECTOR crd0;
    sceVu0IVECTOR crd1;
    sceVu0IVECTOR crd2;
    sceVu0IVECTOR crd3;
    sceVu0IVECTOR crd4;
    sceVu0IVECTOR crd5;
    sceVu0IVECTOR crd6;
    sceVu0IVECTOR crd7;
    sceVu0IVECTOR crd8;
    sceVu0IVECTOR crd9;
    sceVu0IVECTOR crdA;
    sceVu0IVECTOR crdB;
    sceVu0IVECTOR *crd_array[12] = {
        &crd0,
        &crd1,
        &crd2,
        &crd3,
        &crd4,
        &crd5,
        &crd6,
        &crd7,
        &crd8,
        &crd9,
        &crdA,
        &crdB
    };
    static s32 tmp_X;
    static s32 tmp_Y;
    s32 i;

    kz_Draw_Cloud(CLOUD_NORMAL);
    kzTD_Draw_SelViewer(SELECT_ETC_PADEXP1);
    kzTD_Draw_Window(WINDOW_ETC_04);
    kzTD_Set_GsEnv_Std();
    kzGIM_Draw(&GIMBASE_ADJ_TRIANGLE, 0xFFFF, &GCOL_STD, GIM_SEL0113);
    kz_Set_Box(&GIMBASE_ADJ_SQUARE, 0xFFFF, &GIMSIZE_ADJ_SQUARE, 2, &GCOL_ADJ_SQUARE);

    crd0[0] = crdB[0] = 320;
    crd2[0] = crd4[0] = crd5[0] = crd9[0] = 304;
    crd1[0] = crd6[0] = crd8[0] = crdA[0] = 336;
    crd3[0] = 288;
    crd7[0] = 352;
    
    crd0[1] = 192;
    crd1[1] = crd2[1] = crd4[1] = crd6[1] = 208;
    crd3[1] = crd7[1] = 224;
    crd5[1] = crd8[1] = crd9[1] = crdA[1] = 240;
    crdB[1] = 256;

    for (i = 0; i < 12; i++) {
        crd = crd_array[i];
        (*crd)[0] <<= 4;
        (*crd)[1] <<= 3;
    }
    crd1[0] += 8; crd1[1] += 4;
    crd2[0] -= 8; crd2[1] += 4;

    kz_Set_PolyF3(&crd0, &crd1, &crd2, &GCOL_ADJ_TRIANG);
    kz_Set_PolyF3(&crd3, &crd4, &crd5, &GCOL_ADJ_TRIANG);
    kz_Set_PolyF3(&crd6, &crd7, &crd8, &GCOL_ADJ_TRIANG);
    kz_Set_PolyF3(&crd9, &crdA, &crdB, &GCOL_ADJ_TRIANG);

    if (td_jobcnt == TD_JOB_OPT_ADJUST) {
        if (kzTD_Set_Fade(FD_MODE_IN) != FD_STATUS_IN_END) {
            return;
        }
        tmp_X = offset_X;
        tmp_Y = offset_Y;
        kzTD_Step_Job(1);
    }

    if (td_jobcnt == TD_JOB_OPT_ADJUST_MAIN) {
        if (pPAD_TRG_CROSS(kpd0)) {
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_CIRCLE(kpd0)) {
            offset_X = tmp_X;
            offset_Y = tmp_Y;
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_TRIANG(kpd0)) {
            offset_X = 2048;
            offset_Y = 2048;
        } else {
            if (pPAD_REP_UP(kpd0)) {
                offset_Y++;
                if (offset_Y - 2048 > 32) {
                    offset_Y = 2048 + 32;
                }
            }
            if (pPAD_REP_DOWN(kpd0)) {
                offset_Y--;
                if (offset_Y - 2048 < -32) {
                    offset_Y = 2048 - 32;
                }
            }
            if (pPAD_REP_LEFT(kpd0)) {
                offset_X += 2;
                if (offset_X - 2048 > 64) {
                    offset_X = 2048 + 64;
                }
            }
            if (pPAD_REP_RIGHT(kpd0)) {
                offset_X -= 2;
                if (offset_X - 2048 < -64) {
                    offset_X = 2048 - 64;
                }
            }
        }
    }

    if (td_jobcnt == TD_JOB_OPT_ADJUST_END) {
        if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
            kzTD_Return_Job();
        }
    }
}

void kzTD_Job_Wmp_Enter() {
    static u32 vision = KL2_VISION(1, 0);

    vision = KL2_VISION(34, 2);
    nkChangeArea(vision, 0, 0, 0.0);
    td_jobcnt_next0 = TD_JOB_IDLE;
    kzTD_Change_Job();
}

void kzTD_Job_Wmp_Main() {
    static s32 menu_flag = 1;

    kzTD_Draw_SelViewer(SELECT_ETC_PADEXP6);
    kzTD_Draw_Ground(GROUND_WMP_PLACE);
    kzTD_Set_GsEnv_Std();
    kzSTR_Draw(&STRBASE_WMP_PLACE, 0xFFFF, &FCOL_STD, STR_CHIMEI_25);

    if (td_jobcnt == TD_JOB_WMP_MAIN) {
        if (kzTD_Set_Fade(FD_MODE_IN) != FD_STATUS_IN_END) {
            return;
        }
        kzTD_Step_Job(1);
        kzTD_Init_Selector(SELECT_WMP_MENU, 0, 0);
    }

    if (menu_flag) {
        kzTD_Draw_Selector(SELECT_WMP_MENU);
    }

    if (td_jobcnt == TD_JOB_WMP_MAIN_MAIN && pPAD_TRG_CIRCLE(kpd0)) {
        menu_flag = !menu_flag;
    }

    if (td_jobcnt == TD_JOB_WMP_MAIN_END) {
        if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
            kzTD_Change_Job();
        }
    }
}

void kzTD_Job_Wmp_Status() {
    s32 sel_no = SELECT_WMP_STATUS;
    s32 sel_flag = 1;
    s32 status = SL_STATUS_IN;
    static u32 vision = KL2_VISION(1, 0);
    u32 Visions[19] = {
        KL2_VISION(1, 0),
        KL2_VISION(2, 0),
        KL2_VISION(4, 0),
        KL2_VISION(5, 0),
        KL2_VISION(6, 0),
        KL2_VISION(7, 0),
        KL2_VISION(8, 0),
        KL2_VISION(9, 0),
        KL2_VISION(18, 0),
        KL2_VISION(19, 0),
        KL2_VISION(10, 0),
        KL2_VISION(11, 0),
        KL2_VISION(12, 0),
        KL2_VISION(13, 0),
        KL2_VISION(14, 0),
        KL2_VISION(15, 0),
        KL2_VISION(16, 0),
        KL2_VISION(17, 0),
        KL2_VISION(35, 0),
    };
    s32 i;

    kz_Draw_Cloud(CLOUD_LIGHT);
    kzTD_Draw_SelViewer(SELECT_ETC_PADEXP2);
    if (sel_flag) { // sel_flag is always 1...?
        kzTD_Set_GsEnv_Std();
        kzGIM_Draw(&GIMBASE_WMP_STATUS, 0xFFFF, &GCOL_STD, GIM_SEL0019);
    }

    if (td_jobcnt == TD_JOB_WMP_STATUS) {
        if (sel_flag) {
            kzTD_Set_PlateDisp(SELECT_ETC_PADEXP2, 0, 1);
            if (kzTD_Set_Fade(FD_MODE_IN) != FD_STATUS_IN_END) {
                return;
            }
            kzTD_Step_Job(1);
            kzTD_Init_Selector(sel_no, 0, 0);
        } else {
            kzTD_Set_PlateDisp(SELECT_ETC_PADEXP2, 0, 0);
            if (kzTD_Set_Fade(FD_MODE_IN) != FD_STATUS_IN_END) {
                return;
            }
            kzTD_Step_Job(1);
            kzTD_Init_SelViewer(sel_no, 0, 0);
            for (i = 4; i < 19; i++) {
                kzTD_Set_PlateDisp(sel_no, i, 0);
            }
        }
    }

    if (sel_flag) {
        status = kzTD_Draw_Selector(sel_no);
        if (status == SL_STATUS_WAIT) {
            if (pPAD_TRG_CROSS(kpd0)) {
                vision = Visions[kzTD_Get_IdxPlate(sel_no)];
                td_jobcnt_next0 = TD_JOB_IDLE;
                kzTD_Close_Selector(sel_no, 1);
                kzTD_Step_Job(1);
            } else if (pPAD_TRG_CIRCLE(kpd0)) {
                td_jobcnt_next0 = TD_JOB_GAM_PAUSE;
                kzTD_Close_Selector(sel_no, 0);
                kzTD_Step_Job(1);
            } else {
                if (pPAD_REP_UP(kpd0))         kzTD_CsrMove_Up(sel_no);
                else if (pPAD_REP_DOWN(kpd0))  kzTD_CsrMove_Down(sel_no);
                else if (pPAD_TRG_LEFT(kpd0))  kzTD_CsrMove_Left(sel_no);
                else if (pPAD_TRG_RIGHT(kpd0)) kzTD_CsrMove_Right(sel_no);
            }
        }
    } else {
        kzTD_Draw_SelViewer(sel_no);
        if (td_jobcnt == TD_JOB_WMP_STATUS_MAIN && pPAD_TRG_CIRCLE(kpd0)) {
            td_jobcnt_next0 = TD_JOB_IDLE;
            kzTD_Step_Job(1);
        }
    }

    if (td_jobcnt == TD_JOB_WMP_STATUS_END) {
        if (sel_flag) {
            if (status == SL_STATUS_OUT_END) {
                if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
                    if (td_jobcnt_next0 == TD_JOB_IDLE) {
                        nkChangeArea(vision, 0, 0, 0.0f);
                    }
                    kzTD_Change_Job();
                }
            }
        } else {
            if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
                kzTD_Change_Job();
            }
        }
        
    }
}

void kzTD_Job_Wmp_Menu() {
    s32 sel_no = SELECT_WMP_MENU;
    s32 status;
    static u32 vision = KL2_VISION(1, 0);

    kzTD_Set_GsEnv_Std();
    kzGIM_Draw(&GIMBASE_WMP_MENU, 0xFFFF, &GCOL_STD, GIM_PLTA04);
    if (td_jobcnt == TD_JOB_WMP_MENU) {
        kzTD_Init_Selector(sel_no, 0, 0);
        kzTD_Step_Job(1);
    }

    status = kzTD_Draw_Selector(sel_no);
    if (status == SL_STATUS_WAIT) {
        if (pPAD_TRG_CROSS(kpd0)) {
            switch (kzTD_Get_IdxPlate(sel_no)) {
                case 0:
                    td_jobcnt_next0 = TD_JOB_WMP_STATUS;
                    break;
                case 1:
                    td_jobcnt_next0 = TD_JOB_OPT_TOP;
                    td_jobcnt_next1 = TD_JOB_WMP_STATUS;
                    break;
                case 2:
                default:
                    vision = KL2_VISION(30, 0);
                    td_jobcnt_next0 = TD_JOB_IDLE;
                    break;
            }
            kzTD_Close_Selector(sel_no, 1);
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_UP(kpd0)) {
            kzTD_CsrMove_Up(sel_no);
        } else if (pPAD_TRG_DOWN(kpd0)) {
            kzTD_CsrMove_Down(sel_no);
        }
    }

    if (td_jobcnt == TD_JOB_WMP_MENU_END && status == SL_STATUS_OUT_END) {
        if (td_jobcnt_next0 == TD_JOB_IDLE) {
            nkChangeArea(vision, 0, 0, 0.0f);
        }
        kzTD_Change_Job();
    }
}

void kzTD_Job_Gam_Pause() {
    KZCOLOR col = { 0xFF, 0xFF, 0xFF, 0x10 };
    static u32 vision;

    kzTD_Set_GsEnv_Std();
    kz_Set_Alpha(2, SCE_GS_BLEND_RGB_0, SCE_GS_BLEND_RGB_SRC, SCE_GS_BLEND_ALPHA_SRC, SCE_GS_BLEND_RGB_DST, 0x80); // shouldn't alpha blend be FIX?
    kz_Set_TileF4(&ORIGIN, 0xFFFF, &FULLSCR, &col);
    kz_Set_Alpha(2, SCE_GS_BLEND_RGB_SRC, SCE_GS_BLEND_RGB_DST, SCE_GS_BLEND_ALPHA_SRC, SCE_GS_BLEND_RGB_DST, 0x80);
    kzGIM_Draw(&GIMBASE_GAM_PAUSE, 0xFFFF, &GCOL_STD, GIM_SEL0003);

    if (pPAD_TRG_TRIANG(kpd0) || pPAD_TRG_START(kpd0)) {
        td_jobcnt_next0 = pause_return;
        GameGbl.pause_flag2 = 0;
        pause_interval = 30;
        kzTD_Change_Job();
    }
}

void kzTD_Job_Gam_VisionStart() {
    KZCOLOR col = { 0x80, 0x80, 0x80, 0x80 };
    
    vision_count++;
    if (vision_count < 30) {
        return;
    } else if (vision_count < 60) {
        col.a = ((vision_count - 30) << 7) / 30;
    } else if (vision_count < 100) {
        col.a = 0x80;
    } else if (vision_count < 130) {
        col.a = ((130 - vision_count) << 7) / 30;
    } else {
        td_jobcnt_next0 = TD_JOB_IDLE;
        kzTD_Change_Job();
        return;
    }

    kzTD_Set_GsEnv_Std();
    kzGIM_Draw(&GIMBASE_GAM_VISION_S, 0xFFFF, &col, GIM_SEL0000);
    kzGIM_Draw(&GIMBASE_GAM_START, 0xFFFF, &col, GIM_SEL0001);
    kzGIM_Draw(&GIMBASE_GAM_STGNAME, 0xFFFF, &col, GIM_SEL0005);
    kzGIM_Draw(&GIMBASE_GAM_STGINTRO, 0xFFFF, &col, GIM_SEL0006);
}

void kzTD_Job_Gam_VisionOver() {
    s32 sel_no = SELECT_GAM_VOVER;
    s32 status;

    kzTD_Set_GsEnv_Std();
    kzGIM_Draw(&GIMBASE_GAM_VISION_O, 0xFFFF, &GCOL_STD, GIM_SEL0000);
    kzGIM_Draw(&GIMBASE_GAM_OVER, 0xFFFF, &GCOL_STD, GIM_SEL0016);
    if (td_jobcnt == TD_JOB_GAM_VISIONOVER) {
        if (kzTD_Set_Fade(FD_MODE_IN) != FD_STATUS_IN_END) {
            return;
        }
        kzTD_Step_Job(1);
        kzTD_Init_Selector(sel_no, 0, 0);
    }

    status = kzTD_Draw_Selector(sel_no);
    if (status == SL_STATUS_WAIT) {
        if (pPAD_TRG_CROSS(kpd0)) {
            switch (kzTD_Get_IdxPlate(sel_no)) {
                case 0:
                case 1:
                default:
                    td_jobcnt_next0 = TD_JOB_TTL_MENU;
                    break;
            }
            kzTD_Close_Selector(sel_no, 1);
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_LEFT(kpd0)) {
            kzTD_CsrMove_Left(sel_no);
        } else if (pPAD_TRG_RIGHT(kpd0)) {
            kzTD_CsrMove_Right(sel_no);
        }
    }

    if (td_jobcnt == TD_JOB_GAM_VISIONOVER_END && status == SL_STATUS_OUT_END) {
        if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
            kzTD_Change_Job();
        }
    }
}

void (*kzTwoDmsnJobTbl[])() = {
    kzTD_Job_Idle,
    kzTD_Job_1st_MCCheck,
    kzTD_Job_1st_MCCheck,
    kzTD_Job_1st_MCCheck,
    kzTD_Job_1st_Logo,
    kzTD_Job_1st_Logo,
    kzTD_Job_1st_Logo,
    kzTD_Job_Pup_Wait,
    kzTD_Job_Pup_Wait,
    kzTD_Job_Pup_Wait,
    kzTD_Job_Ttl_Menu,
    kzTD_Job_Ttl_Menu,
    kzTD_Job_Ttl_Menu,
    kzTD_Job_Fil_MakeSel,
    kzTD_Job_Fil_MakeSel,
    kzTD_Job_Fil_MakeSel,
    kzTD_Job_Fil_MakeConf,
    kzTD_Job_Fil_MakeConf,
    kzTD_Job_Fil_MakeConf,
    kzTD_Job_Fil_LoadFileSel,
    kzTD_Job_Fil_LoadFileSel,
    kzTD_Job_Fil_LoadFileSel,
    kzTD_Job_Fil_LoadDataSel,
    kzTD_Job_Fil_LoadDataSel,
    kzTD_Job_Fil_LoadDataSel,
    kzTD_Job_Fil_SaveDataSel,
    kzTD_Job_Fil_SaveDataSel,
    kzTD_Job_Fil_SaveDataSel,
    kzTD_Job_Fil_SaveConf,
    kzTD_Job_Fil_SaveConf,
    kzTD_Job_Fil_SaveConf,
    kzTD_Job_Nam_Entry,
    kzTD_Job_Nam_Entry,
    kzTD_Job_Nam_Entry,
    kzTD_Job_Nam_Entry,
    kzTD_Job_Nam_Entry,
    kzTD_Job_Opt_Top,
    kzTD_Job_Opt_Top,
    kzTD_Job_Opt_Top,
    kzTD_Job_Opt_Pad,
    kzTD_Job_Opt_Pad,
    kzTD_Job_Opt_Pad,
    kzTD_Job_Opt_Sound,
    kzTD_Job_Opt_Sound,
    kzTD_Job_Opt_Sound,
    kzTD_Job_Opt_Adjust,
    kzTD_Job_Opt_Adjust,
    kzTD_Job_Opt_Adjust,
    kzTD_Job_Wmp_Enter,
    kzTD_Job_Wmp_Main,
    kzTD_Job_Wmp_Main,
    kzTD_Job_Wmp_Main,
    kzTD_Job_Wmp_Status,
    kzTD_Job_Wmp_Status,
    kzTD_Job_Wmp_Status,
    kzTD_Job_Wmp_Menu,
    kzTD_Job_Wmp_Menu,
    kzTD_Job_Wmp_Menu,
    kzTD_Job_Gam_Pause,
    kzTD_Job_Gam_Pause,
    kzTD_Job_Gam_Pause,
    kzTD_Job_Gam_VisionStart,
    kzTD_Job_Gam_VisionStart,
    kzTD_Job_Gam_VisionStart,
    kzTD_Job_Gam_VisionOver,
    kzTD_Job_Gam_VisionOver,
    kzTD_Job_Gam_VisionOver,
    kzTD_Job_Mom_Top,
    kzTD_Job_Mom_Top,
    kzTD_Job_Mom_Top,
    kzTD_Job_Mom_Genju,
    kzTD_Job_Mom_Genju,
    kzTD_Job_Mom_Genju,
    kzTD_Job_Mom_Pause,
    kzTD_Job_Mom_Pause,
    kzTD_Job_Mom_Pause,
    kzTD_Job_Mom_PuppetTop,
    kzTD_Job_Mom_PuppetTop,
    kzTD_Job_Mom_PuppetTop,
    kzTD_Job_Mom_PuppetGroup,
    kzTD_Job_Mom_PuppetGroup,
    kzTD_Job_Mom_PuppetGroup,
    kzTD_Job_Mom_Concert,
    kzTD_Job_Mom_Concert,
    kzTD_Job_Mom_Concert,
    kzTD_Job_Mom_Gallery,
    kzTD_Job_Mom_Gallery,
    kzTD_Job_Mom_Gallery,
};
