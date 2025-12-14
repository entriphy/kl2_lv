#include "kazuya/td_mhjob.h"
#include "kazuya/bios.h"
#include "kazuya/cvar.h"
#include "kazuya/string.h"
#include "kazuya/td_job.h"
#include "kazuya/td_sys.h"
#include "nakano/sinit.h"
#include "harada/hr_pflag.h"

s32 mommet_mode = MOM_MODE_NORMAL;
s32 puppet_group_no = 0;
DVECTOR STRBASE_MOM_MESSAGE = { 70, 328 };
DVECTOR STRBASE_MOM_PUPPETTOP = { 50, 30 };
DVECTOR STRBASE_MOM_GENJU = { 22, 364 };
DVECTOR GIMBASE_MOM_PLYREW = { 350, 290 };
DVECTOR GIMBASE_MOM_PLYSTP = { 420, 290 };
DVECTOR GIMBASE_MOM_PLYFWD = { 490, 290 };
DVECTOR STRBASE_MOM_PLYTUNE = { 380, 140 };
DVECTOR NUMBASE_MOM_PLYTUNE = { 430, 140 };
KZCOLOR GCOL_MOM_PLYNML = { 0x40, 0x40, 0x40, 0x80 };
KZCOLOR GCOL_MOM_PLYPRS = { 0x80, 0x80, 0x80, 0x80 };


void kzTD_Job_Mom_Top() {
    s32 sel_no = SELECT_MOM_TOP;
    s32 status;
    s32 str_no;

    kzTD_Draw_SelViewer(SELECT_ETC_PADEXP3);
    kzTD_Set_GsEnv_Std();
    kzTD_Draw_Ground(GROUND_MOM_MESSAGE);

    if (td_jobcnt == TD_JOB_MOM_TOP) {
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
                    td_jobcnt_next0 = TD_JOB_MOM_GENJU;
                    break;
                case 1:
                    td_jobcnt_next0 = TD_JOB_MOM_CONCERT;
                    break;
                case 2:
                    td_jobcnt_next0 = TD_JOB_MOM_PUPPETTOP;
                    break;
                default:
                    td_jobcnt_next0 = TD_JOB_MOM_GALLERY;
                    break;
            }
            kzTD_Close_Selector(sel_no, 1);
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_CIRCLE(kpd0)) {
            td_jobcnt_next0 = TD_JOB_TTL_MENU;
            kzTD_Close_Selector(sel_no, 0);
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_UP(kpd0)) {
            kzTD_CsrMove_Up(sel_no);
        } else if (pPAD_TRG_DOWN(kpd0)) {
            kzTD_CsrMove_Down(sel_no);
        }
    }

    if (kzTD_Get_SelFlag(sel_no)) {
        switch (kzTD_Get_IdxPlate(sel_no)) {
            case 0:
                str_no = STR_PUPPET_43;
                break;
            case 1:
                str_no = STR_PUPPET_01;
                break;
            case 2:
                str_no = STR_PUPPET_07;
                break;
            default:
                str_no = STR_PUPPET_09;
                break;
        }

        kzSTR_Draw(&STRBASE_MOM_MESSAGE, 0xFFFF, &FCOL_STD, str_no);
    }

    if (td_jobcnt == TD_JOB_MOM_TOP_END && status == SL_STATUS_OUT_END) {
        if (td_jobcnt_next0 == TD_JOB_TTL_MENU || td_jobcnt_next0 == TD_JOB_MOM_CONCERT || td_jobcnt_next0 == TD_JOB_MOM_GALLERY) {
            if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
                kzTD_Change_Job();
            }
        } else {
            kzTD_Change_Job();
        }
    }
}

void kzTD_Job_Mom_Genju() {
	s32 sel_no = SELECT_MOM_GENJU;
	s32 status;
	static u32 vision = KL2_VISION(1, 0);

    kzTD_Draw_SelViewer(SELECT_ETC_PADEXP0);
    kzTD_Set_GsEnv_Std();
    kzSTR_Draw(&STRBASE_MOM_GENJU, 0xFFFF, &FCOL_STD, STR_MAP_02);

    if (td_jobcnt == TD_JOB_MOM_GENJU) {
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
                    vision = KL2_VISION(21, 0);
                    break;
                case 1:
                    vision = KL2_VISION(22, 0);
                    break;
                case 2:
                    vision = KL2_VISION(23, 0);
                    break;
                case 3:
                    vision = KL2_VISION(24, 0);
                    break;
                case 4:
                    vision = KL2_VISION(26, 0);
                    break;
                case 5:
                default:
                    vision = KL2_VISION(27, 0);
                    break;
            }
            mommet_mode = MOM_MODE_GENJU;
            td_jobcnt_next0 = TD_JOB_IDLE;
            kzTD_Close_Selector(sel_no, 1);
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_CIRCLE(kpd0)) {
            td_jobcnt_next0 = TD_JOB_MOM_TOP;
            kzTD_Close_Selector(sel_no, 0);
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_UP(kpd0)) {
            kzTD_CsrMove_Up(sel_no);
        } else if (pPAD_TRG_DOWN(kpd0)) {
            kzTD_CsrMove_Down(sel_no);
        }
    }

    if (td_jobcnt == TD_JOB_MOM_GENJU_END && status == SL_STATUS_OUT_END) {
        if (td_jobcnt_next0 == TD_JOB_IDLE) {
            if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
                nkChangeArea(vision, 0, 0, 0.0f);
                kzTD_Change_Job();
            }
        } else {
            kzTD_Change_Job();
        }
    }
}

void kzTD_Job_Mom_Pause() {
    s32 sel_no = SELECT_MOM_PAUSE;
    s32 status;
    KZCOLOR col = { 0xFF, 0xFF, 0xFF, 0x10 };
    static u32 vision;

    kzTD_Set_GsEnv_Std();
    kz_Set_Alpha(2, SCE_GS_BLEND_RGB_0, SCE_GS_BLEND_RGB_SRC, SCE_GS_BLEND_ALPHA_SRC, SCE_GS_BLEND_RGB_DST, 0x80);
    kz_Set_TileF4(&ORIGIN, 0xFFFF, &FULLSCR, &col);
    kz_Set_Alpha(2, SCE_GS_BLEND_RGB_SRC, SCE_GS_BLEND_RGB_DST, SCE_GS_BLEND_ALPHA_SRC, SCE_GS_BLEND_RGB_DST, 0x80);
    kzGIM_Draw(&GIMBASE_GAM_PSPLACE, 0xFFFF, &GCOL_STD, GIM_SEL0020);
    kzGIM_Draw(&GIMBASE_GAM_PAUSE, 0xFFFF, &GCOL_STD, GIM_SEL0003);

    if (td_jobcnt == TD_JOB_MOM_PAUSE) {
        kzTD_Init_Selector(sel_no, 0, 0);
        kzTD_Step_Job(1);
    }

    status = kzTD_Draw_Selector(sel_no);
    if (status == SL_STATUS_WAIT) {
        if (pPAD_TRG_CROSS(kpd0)) {
            switch (kzTD_Get_IdxPlate(sel_no)) {
                case 0:
                    vision = KL2_VISION(0, 0);
                    td_jobcnt_next0 = pause_return;
                    break;
                case 1:
                    vision = GameGbl.vision & 0xFF00;
                    td_jobcnt_next0 = TD_JOB_IDLE;
                    break;
                case 2:
                default:
                    vision = KL2_VISION(35, 1);
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

    if (td_jobcnt == TD_JOB_MOM_PAUSE_END && status == SL_STATUS_OUT_END) {
        if (vision != KL2_VISION(0, 0)) {
            if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
                nkChangeArea(vision, 0, 0, 0.0f);
                kzTD_Change_Job();
            }
        } else {
            GameGbl.pause_flag2 = 0;
            pause_interval = 30;
            kzTD_Change_Job();
        }
    }
}

void kzTD_Job_Mom_PuppetTop() {
	s32 sel_no = SELECT_PUP_TOP;
	s32 status;
	static u32 vision = KL2_VISION(1, 0);

    kzTD_Draw_SelViewer(SELECT_ETC_PADEXP0);

    if (td_jobcnt == TD_JOB_MOM_PUPPETTOP) {
        kzTD_Init_Selector(sel_no, -1, -1);
        kzTD_Step_Job(1);
    }

    status = kzTD_Draw_Selector(sel_no);
    if (status == SL_STATUS_WAIT) {
        if (pPAD_TRG_CROSS(kpd0)) {
            puppet_group_no = kzTD_Get_IdxPlate(sel_no);
            td_jobcnt_next0 = TD_JOB_MOM_PUPPETGROUP;
            kzTD_Close_Selector(sel_no, 1);
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_CIRCLE(kpd0)) {
            td_jobcnt_next0 = TD_JOB_MOM_TOP;
            kzTD_Close_Selector(sel_no, 0);
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_UP(kpd0)) {
            kzTD_CsrMove_Up(sel_no);
        } else if (pPAD_TRG_DOWN(kpd0)) {
            kzTD_CsrMove_Down(sel_no);
        } else if (pPAD_TRG_LEFT(kpd0)) {
            kzTD_CsrMove_Left(sel_no);
        } else if (pPAD_TRG_RIGHT(kpd0)) {
            kzTD_CsrMove_Right(sel_no);
        }
    }

    if (td_jobcnt == TD_JOB_MOM_PUPPETTOP_END && status == SL_STATUS_OUT_END) {
        kzTD_Change_Job();
    }
}

void kzTD_Job_Mom_PuppetGroup() {
    static s32 sel_group[25] = {
        SELECT_PUP_GROUP00,
        SELECT_PUP_GROUP01,
        SELECT_PUP_GROUP02,
        SELECT_PUP_GROUP03,
        SELECT_PUP_GROUP04,
        SELECT_PUP_GROUP05,
        SELECT_PUP_GROUP06,
        SELECT_PUP_GROUP07,
        SELECT_PUP_GROUP08,
        SELECT_PUP_GROUP09,
        SELECT_PUP_GROUP10,
        SELECT_PUP_GROUP11,
        SELECT_PUP_GROUP12,
        SELECT_PUP_GROUP13,
        SELECT_PUP_GROUP14,
        SELECT_PUP_GROUP15,
        SELECT_PUP_GROUP16,
        SELECT_PUP_GROUP17,
        SELECT_PUP_GROUP18,
        SELECT_PUP_GROUP19,
        SELECT_PUP_GROUP20,
        SELECT_PUP_GROUP21,
        SELECT_PUP_GROUP22,
        SELECT_PUP_GROUP23,
        SELECT_PUP_GROUP24
    };
    static s32 sel_no = SELECT_PUP_GROUP00;
    static u32 vision = KL2_VISION(1, 0);
    s32 status;

    kzTD_Draw_SelViewer(SELECT_ETC_PADEXP0);

    if (td_jobcnt == TD_JOB_MOM_PUPPETGROUP) {
        if (kzTD_Set_Fade(FD_MODE_IN) != FD_STATUS_IN_END) {
            return;
        }

        kzTD_Step_Job(1);
        sel_no = sel_group[puppet_group_no];
        kzTD_Init_Selector(sel_no, -1, -1);
    }

    status = kzTD_Draw_Selector(sel_no);
    if (status == SL_STATUS_WAIT) {
        if (pPAD_TRG_CROSS(kpd0)) {
            vision = hr_pflag_get_vs(kzTD_Get_PuppetID(sel_no, 0));
            mommet_mode = MOM_MODE_THEATER;
            td_jobcnt_next0 = TD_JOB_IDLE;
            kzTD_Close_Selector(sel_no, 1);
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_CIRCLE(kpd0)) {
            td_jobcnt_next0 = TD_JOB_MOM_PUPPETTOP;
            kzTD_Close_Selector(sel_no, 0);
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_UP(kpd0)) {
            kzTD_CsrMove_Up(sel_no);
        } else if (pPAD_TRG_DOWN(kpd0)) {
            kzTD_CsrMove_Down(sel_no);
        }
    }

    if (td_jobcnt == TD_JOB_MOM_PUPPETGROUP_END && status == SL_STATUS_OUT_END) {
        if (td_jobcnt_next0 == TD_JOB_IDLE) {
            if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
                nkChangeArea(vision, 0, 0, 0.0f);
                kzTD_Change_Job();
            }
        } else {
            kzTD_Change_Job();
        }
    }
}

void kzTD_Job_Mom_Concert() {
    static s32 mode = 0;
    static s32 tune_no = 0;
    static s32 btn_fwd = 0;
    static s32 btn_rew = 0;
    static s32 btn_stp = 0;
    static s32 btn_count = 0;

    kzTD_Draw_Ground(GROUND_MOM_PLYDISP);
    kzTD_Draw_Ground(GROUND_MOM_PLYCTRL);
    kzTD_Draw_SelViewer(SELECT_ETC_PADEXP5);
    kzTD_Set_GsEnv_Std();

    kzGIM_Draw(&GIMBASE_MOM_PLYFWD, 0xFFFF, btn_fwd ? &GCOL_MOM_PLYPRS : &GCOL_MOM_PLYNML, GIM_MOM0008);
    kzGIM_Draw(&GIMBASE_MOM_PLYREW, 0xFFFF, btn_rew ? &GCOL_MOM_PLYPRS : &GCOL_MOM_PLYNML, GIM_MOM0009);
    kzGIM_Draw(&GIMBASE_MOM_PLYSTP, 0xFFFF, btn_stp ? &GCOL_MOM_PLYPRS : &GCOL_MOM_PLYNML, mode ? GIM_MOM0007 : GIM_MOM0010);
    kzSTR_Draw(&STRBASE_MOM_PLYTUNE, 0xFFFF, &FCOL_STD, STR_ETC_05);
    kzNUM_Draw(&NUMBASE_MOM_PLYTUNE, 0xFFFF, &FCOL_STD, 1, 2, tune_no);

    if (td_jobcnt == TD_JOB_MOM_CONCERT) {
        mode = 0;
        tune_no = 0;
        btn_fwd = btn_rew = btn_stp = 0;
        btn_count = 0;

        if (kzTD_Set_Fade(FD_MODE_IN) != FD_STATUS_IN_END) {
            return;
        }

        kzTD_Step_Job(1);
    }

    if (btn_count != 0) {
        btn_count--;
        if (btn_count <= 0) {
            btn_count = 0;
            btn_fwd = btn_rew = btn_stp = 0;
        }
    }

    if (td_jobcnt == TD_JOB_MOM_CONCERT_MAIN && btn_count == 0) {
        if (pPAD_TRG_L1(kpd0)) {
            if (mode == 0) {
                mode = 1;
                btn_stp = 1;
            }
            btn_rew = 1;
            btn_count = 8;
        } else if (pPAD_TRG_R1(kpd0)) {
            if (mode == 0) {
                mode = 1;
                btn_stp = 1;
            }
            btn_fwd = 1;
            btn_count = 8;
        } else if (pPAD_TRG_LEFT(kpd0)) {
            btn_rew = 1;
            btn_count = 8;
        } else if (pPAD_TRG_RIGHT(kpd0)) {
            btn_fwd = 1;
            btn_count = 8;
        } else if (pPAD_TRG_CIRCLE(kpd0) && mode == 0) {
            mode = 1;
            btn_stp = 1;
            btn_count = 8;
        } else if (pPAD_TRG_SQUARE(kpd0) && mode == 1) {
            s32 var_v1 = mode;
            mode = 0;
            btn_stp = var_v1;
            btn_count = 8;
        } else if (pPAD_TRG_CIRCLE(kpd0)) {
            td_jobcnt_next0 = TD_JOB_MOM_TOP;
            kzTD_Step_Job(1);
        }
    }

    if (td_jobcnt == TD_JOB_MOM_CONCERT_END) {
        if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
            kzTD_Change_Job();
        }
    }
}

void kzTD_Job_Mom_Gallery() {
    kzTD_Set_GsEnv_Std();
    kzGIM_Draw(&STRBASE_MOM_PUPPETTOP, 0xFFFF, &GCOL_STD, GIM_PLTA11);

    if (td_jobcnt == TD_JOB_MOM_GALLERY) {
        if (kzTD_Set_Fade(FD_MODE_IN) != FD_STATUS_IN_END) {
            return;
        }

        kzTD_Step_Job(1);
    }

    if ((td_jobcnt == TD_JOB_MOM_GALLERY_MAIN) && ((kpd0->trg & 0x20U) != 0)) {
        if (pPAD_TRG_CIRCLE(kpd0)) {
            td_jobcnt_next0 = TD_JOB_MOM_TOP;
            kzTD_Step_Job(1);
        }
    }

    if (td_jobcnt == TD_JOB_MOM_GALLERY_END) {
        if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
            kzTD_Change_Job();
        }
    }
}