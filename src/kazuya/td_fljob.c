#include "kazuya/td_fljob.h"
#include "kazuya/bios.h"
#include "kazuya/cvar.h"
#include "kazuya/string.h"
#include "kazuya/td_job.h"
#include "kazuya/td_sys.h"

DVECTOR STRBASE_FIL_NAME = { 248, 152 };
DVECTOR STRBASE_FIL_DATA = { 252, 180 };
DVECTOR STRBASE_FIL_STAGE = { 252, 196 };
DVECTOR GIMBASE_FIL_REMAIN = { 496, 188 };
DVECTOR NUMBASE_FIL_REMAIN = { 532, 200 };
DVECTOR GIMBASE_FIL_DATCSR = { 244, 176 };
DVECTOR GIMSIZE_FIL_DATCSR = { 340, 48 };
DVECTOR GIMBASE_1ST_TRIALMES = { 64, 176 };
KZCOLOR GCOL_FIL_DATCSR = { 0x3F, 0xBB, 0xEF, 0x80 };
static s32 datcsr_offset = 0;


void kzTD_Set_PlateStr_FN(s32 sel_no) {
	s32 i;

    for (i = 0; i < 4; i++) {
        kzTD_Set_PlateStr(sel_no, i, kzCHR_Get_StringPtr(STR_FILE_00));
    }

    if (td_jobcnt != TD_JOB_FIL_MAKESEL && td_jobcnt != TD_JOB_FIL_MAKESEL_MAIN && td_jobcnt != TD_JOB_FIL_MAKESEL_END) {
        kzTD_Set_PlateStr(sel_no, 0, mci->name);
    }
}

void kzTD_Draw_Common_Fil(s32 file_no) {
    DVECTOR pos0;
    DVECTOR pos1;
    DVECTOR pos2;
    DVECTOR pos3;
    s32 i;
    s32 offset;
    s32 array_data[] = { STR_DATA_00, STR_DATA_01, STR_DATA_02, STR_DATA_03 };
    s32 array_stage[] = { 
        STR_STAGE_00,
        STR_STAGE_01,
        STR_STAGE_02,
        STR_STAGE_03,
        STR_STAGE_04,
        STR_STAGE_05,
        STR_STAGE_06,
        STR_STAGE_07,
        STR_STAGE_08,
        STR_STAGE_09,
        STR_STAGE_10,
        STR_STAGE_11,
        STR_STAGE_12,
        STR_STAGE_13,
        STR_STAGE_14,
        STR_STAGE_15,
        STR_STAGE_16,
        STR_STAGE_17,
        STR_STAGE_18
    };
    s32 exist[4] = { 1, 1 };
    s32 place[4] = { STR_STAGE_00, STR_STAGE_01 };
    s32 remain[4] = { STR_OPTION_00, STR_OPTION_02 };
    s32 flag;

    if (td_jobcnt != TD_JOB_FIL_MAKESEL && td_jobcnt != TD_JOB_FIL_MAKESEL_MAIN && td_jobcnt != TD_JOB_FIL_MAKESEL_END) {
        flag = 0;
    } else {
        flag = 1;
    }

    if (flag) {
        kzSTR_Draw(&STRBASE_FIL_NAME, 0xFFFF, &FCOL_STD, STR_FILE_00);
    } else {
        kzSTR_Draw_Direct(&STRBASE_FIL_NAME, 0xFFFF, &FCOL_STD, mci->name);
    }

    for (i = 0; i < 4; i++) {
        offset = i * 52;
        SETDVEC(pos0, STRBASE_FIL_DATA.vx, STRBASE_FIL_DATA.vy + offset);
        SETDVEC(pos1, STRBASE_FIL_STAGE.vx, STRBASE_FIL_STAGE.vy + offset);
        SETDVEC(pos2, GIMBASE_FIL_REMAIN.vx, GIMBASE_FIL_REMAIN.vy + offset);
        SETDVEC(pos3, NUMBASE_FIL_REMAIN.vx, NUMBASE_FIL_REMAIN.vy + offset);
        kzSTR_Draw(&pos0, 0xFFFF, &FCOL_STD, array_data[i]);

        if (!flag && exist[i]) {
            kzSTR_Draw(&pos1, 0xFFFF, &FCOL_STD, place[i]);
            kzGIM_Draw(&pos2, 0xFFFF, &GCOL_STD, GIM_ZANKI);
            kzNUM_Draw(&pos3, 0xFFFF, &FCOL_STD, 1, 2, remain[i]);
        }
    }
}

void kzTD_Job_1st_MCCheck() {
    static s32 count = 0;

    kzTD_Set_GsEnv_Std();
    kzGIM_Draw(&GIMBASE_1ST_TRIALMES, 0xFFFF, &GCOL_STD, GIM_LOGO);
    if (td_jobcnt == 1) {
        if (kzTD_Set_Fade(FD_MODE_IN) != FD_STATUS_IN_END) {
            return;
        }
        count = 0;
        kzTD_Step_Job(1);
    }
    if (td_jobcnt == 2) {
        count++;
        if (count > 240) {
            td_jobcnt_next0 = 4;
            kzTD_Step_Job(1);
        }
    }
    if (td_jobcnt == 3) {
        if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
            kzTD_Change_Job();
        }
    }
}

void kzTD_Job_Fil_MakeSel() {
    s32 sel_no = SELECT_FIL_MAKESEL;
    s32 status;

    kz_Draw_Cloud(CLOUD_NORMAL);
    kzTD_Draw_Common_Ttl();
    kzTD_Draw_SelViewer(SELECT_ETC_PADEXP0);
    kzTD_Set_GsEnv_Std();
    kzTD_Draw_Common_Fil(0);
    kzSTR_Draw(&STRBASE_OPT_SCREXPLAIN, 0xFFFF, &FCOL_STD, STR_ETC_11);
    if (td_jobcnt == TD_JOB_FIL_MAKESEL) {
        if (kzTD_Set_Fade(FD_MODE_IN) != FD_STATUS_IN_END) {
            return;
        }
        kzTD_Step_Job(1);
        kzTD_Init_Selector(sel_no, 0, 0);
        kzTD_Set_PlateStr_FN(sel_no);
    }

    status = kzTD_Draw_Selector(sel_no);
    if (status == SL_STATUS_WAIT) {
        if (pPAD_TRG_CROSS(kpd0)) {
            // IMPORTANT: forcing a return value to exist in register
            switch (kzTD_Get_IdxPlate(sel_no)) {
                case 0:
                case 1:
                    td_jobcnt_next0 = TD_JOB_FIL_MAKECONF;
                    break;
                default:
                    td_jobcnt_next0 = TD_JOB_FIL_MAKECONF;
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

    if (td_jobcnt == TD_JOB_FIL_MAKESEL_END && status == SL_STATUS_OUT_END) {
        if (td_jobcnt_next0 == TD_JOB_FIL_MAKECONF) {
            kzTD_Change_Job();
        } else if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
            kzTD_Change_Job();
        }
    }
}

void kzTD_Job_Fil_MakeConf() {
    s32 sel_no = SELECT_FIL_CONFIRM;
    s32 status;

    kz_Draw_Cloud(CLOUD_NORMAL);
    kzTD_Draw_Common_Ttl();
    kzTD_Set_GsEnv_Std();
    kzTD_Draw_Common_Fil(0);
    kzSTR_Draw(&STRBASE_OPT_SCREXPLAIN, 0xFFFF, &FCOL_STD, STR_WINDOW_14);
    if (td_jobcnt == TD_JOB_FIL_MAKECONF) {
        kzTD_Init_Selector(sel_no, 0, 1);
        kzTD_Step_Job(1);
    }

    status = kzTD_Draw_Selector(sel_no);
    if (status == SL_STATUS_WAIT) {
        if (pPAD_TRG_CROSS(kpd0)) {
            if (kzTD_Get_IdxPlate(sel_no) != 0) {
                td_jobcnt_next0 = TD_JOB_FIL_MAKESEL;
            } else {
                td_jobcnt_next0 = TD_JOB_NAM_ENTRY;
            }
            kzTD_Close_Selector(sel_no, 1);
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_UP(kpd0)) {
            kzTD_CsrMove_Up(sel_no);
        } else if (pPAD_TRG_DOWN(kpd0)) {
            kzTD_CsrMove_Down(sel_no);
        }
    }

    if (td_jobcnt == TD_JOB_FIL_MAKECONF_END && status == SL_STATUS_OUT_END) {
        if (td_jobcnt_next0 == TD_JOB_FIL_MAKESEL) {
            kzTD_Change_Job();
        } else if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
            kzTD_Change_Job();
        }
    }
}

void kzTD_Job_Fil_LoadFileSel() {
    s32 sel_no = SELECT_FIL_FILESEL;
    s32 status;

    kz_Draw_Cloud(CLOUD_NORMAL);
    kzTD_Draw_Common_Ttl();
    kzTD_Draw_SelViewer(SELECT_ETC_PADEXP0);
    kzTD_Set_GsEnv_Std();
    kzTD_Draw_Common_Fil(0);
    kzSTR_Draw(&STRBASE_OPT_SCREXPLAIN, 0xFFFF, &FCOL_STD, STR_ETC_12);
    if (td_jobcnt == TD_JOB_FIL_LOADFILESEL) {
        if (kzTD_Set_Fade(FD_MODE_IN) != FD_STATUS_IN_END) {
            return;
        }
        kzTD_Step_Job(1);
        kzTD_Init_Selector(sel_no, 0, 0);
        kzTD_Set_PlateStr_FN(sel_no);
    }

    status = kzTD_Draw_Selector(sel_no);
    if (status == SL_STATUS_WAIT) {
        if (pPAD_TRG_CROSS(kpd0)) {
            switch (kzTD_Get_IdxPlate(sel_no)) {
                case 0:
                case 1:
                    td_jobcnt_next0 = TD_JOB_FIL_LOADDATASEL;
                    break;
                default:
                    td_jobcnt_next0 = TD_JOB_FIL_LOADDATASEL;
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

    if (td_jobcnt == TD_JOB_FIL_LOADFILESEL_END && status == SL_STATUS_OUT_END) {
        if (td_jobcnt_next0 == TD_JOB_TTL_MENU) {
            if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
                kzTD_Change_Job();
            }
        } else {
            kzTD_Change_Job();
        }
    }
}

void kzTD_Job_Fil_LoadDataSel() {
    s32 sel_no = SELECT_FIL_DATASEL;
    s32 status;
    DVECTOR pos;

    kz_Draw_Cloud(CLOUD_NORMAL);
    kzTD_Draw_Common_Ttl();
    kzTD_Draw_SelViewer(SELECT_ETC_PADEXP0);
    kzTD_Set_GsEnv_Std();
    kzTD_Draw_Common_Fil(0);
    kzSTR_Draw(&STRBASE_OPT_SCREXPLAIN, 0xFFFF, &FCOL_STD, STR_ETC_29);
    if (td_jobcnt == TD_JOB_FIL_LOADDATASEL) {
        kzTD_Init_Selector(sel_no, 0, 0);
        kzTD_Step_Job(1);
    }

    status = kzTD_Draw_Selector(sel_no);
    if (status == SL_STATUS_WAIT) {
        if (pPAD_TRG_CROSS(kpd0)) {
            switch (kzTD_Get_IdxPlate(sel_no)) {
                case 0:
                case 1:
                    td_jobcnt_next0 = TD_JOB_TTL_MENU;
                    break;
                default:
                    td_jobcnt_next0 = TD_JOB_TTL_MENU;
                    break;
            }
            kzTD_Close_Selector(sel_no, 1);
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_CIRCLE(kpd0)) {
            td_jobcnt_next0 = TD_JOB_FIL_LOADFILESEL;
            kzTD_Close_Selector(sel_no, 0);
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_UP(kpd0)) {
            kzTD_CsrMove_Up(sel_no);
        } else if (pPAD_TRG_DOWN(kpd0)) {
            kzTD_CsrMove_Down(sel_no);
        }
    }

    if (kzTD_Get_SelFlag(sel_no) != 0) {
        datcsr_offset = kzTD_Get_IdxPlate(sel_no) * 52;
        SETDVEC(pos, GIMBASE_FIL_DATCSR.vx, GIMBASE_FIL_DATCSR.vy + datcsr_offset);
        kz_Set_Box(&pos, 0xFFFF, &GIMSIZE_FIL_DATCSR, 2, &GCOL_FIL_DATCSR);
    }

    if (td_jobcnt == TD_JOB_FIL_LOADDATASEL_END && status == SL_STATUS_OUT_END) {
        if (td_jobcnt_next0 == TD_JOB_FIL_LOADFILESEL) {
            kzTD_Change_Job();
        } else if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
            kzTD_Change_Job();
        }
    }
}

void kzTD_Job_Fil_SaveDataSel() {
    s32 sel_no = SELECT_FIL_DATASEL;
    s32 status;
    DVECTOR pos;

    kzTD_Draw_Common_Ttl();
    kzTD_Draw_SelViewer(SELECT_ETC_PADEXP0);
    kzTD_Set_GsEnv_Std();
    kzTD_Draw_Common_Fil(0);
    kzSTR_Draw(&STRBASE_OPT_SCREXPLAIN, 0xFFFF, &FCOL_STD, STR_ETC_28);
    if (td_jobcnt == TD_JOB_FIL_SAVEDATASEL) {
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
                    td_jobcnt_next0 = TD_JOB_FIL_SAVECONF;
                    break;
                default:
                    td_jobcnt_next0 = TD_JOB_FIL_SAVECONF;
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

    if (kzTD_Get_SelFlag(sel_no) != 0) {
        datcsr_offset = kzTD_Get_IdxPlate(sel_no) * 52;
        SETDVEC(pos, GIMBASE_FIL_DATCSR.vx, GIMBASE_FIL_DATCSR.vy + datcsr_offset);
        kz_Set_Box(&pos, 0xFFFF, &GIMSIZE_FIL_DATCSR, 2, &GCOL_FIL_DATCSR);
    }

    if (td_jobcnt == TD_JOB_FIL_SAVEDATASEL_END && status == SL_STATUS_OUT_END) {
        if (td_jobcnt_next0 == TD_JOB_FIL_SAVECONF) {
            kzTD_Change_Job();
        } else if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
            kzTD_Change_Job();
        }
    }
}

void kzTD_Job_Fil_SaveConf() {
    s32 sel_no = SELECT_FIL_CONFIRM;
    s32 status;
    DVECTOR pos;

    kzTD_Draw_Common_Ttl();
    kzTD_Set_GsEnv_Std();
    kzTD_Draw_Common_Fil(0);
    kzSTR_Draw(&STRBASE_OPT_SCREXPLAIN, 0xFFFF, &FCOL_STD, STR_WINDOW_14);
    if (td_jobcnt == TD_JOB_FIL_SAVECONF) {
        kzTD_Init_Selector(sel_no, 0, 1);
        kzTD_Step_Job(1);
    }

    status = kzTD_Draw_Selector(sel_no);
    if (status == SL_STATUS_WAIT) {
        if (pPAD_TRG_CROSS(kpd0)) {
            if (kzTD_Get_IdxPlate(sel_no) != 0) {
                td_jobcnt_next0 = TD_JOB_FIL_SAVEDATASEL;
            } else {
                td_jobcnt_next0 = TD_JOB_TTL_MENU;
            }
            kzTD_Close_Selector(sel_no, 1);
            kzTD_Step_Job(1);
        } else if (pPAD_TRG_UP(kpd0)) {
            kzTD_CsrMove_Up(sel_no);
        } else if (pPAD_TRG_DOWN(kpd0)) {
            kzTD_CsrMove_Down(sel_no);
        }
    }

    SETDVEC(pos, GIMBASE_FIL_DATCSR.vx, GIMBASE_FIL_DATCSR.vy + datcsr_offset);
    kz_Set_Box(&pos, 0xFFFF, &GIMSIZE_FIL_DATCSR, 2, &GCOL_FIL_DATCSR);

    if (td_jobcnt == TD_JOB_FIL_SAVECONF_END && status == SL_STATUS_OUT_END) {
        if (td_jobcnt_next0 == TD_JOB_FIL_SAVEDATASEL) {
            kzTD_Change_Job();
        } else if (kzTD_Set_Fade(FD_MODE_OUT) == FD_STATUS_OUT_END) {
            kzTD_Change_Job();
        }
    }
}
