#include "kazuya/interfac.h"
#include "hoshino/h_file.h"
#include "kazuya/bios.h"
#include "kazuya/cvar.h"
#include "kazuya/string.h"
#include "kazuya/td_job.h"
#include "kazuya/td_mhjob.h"
#include "kazuya/td_sys.h"
#include "kazuya/wm_job.h"
#include "nakano/dma.h"
#include "nakano/sinit.h"

DVECTOR STRBASE_SYS_NOWLOAD = { 0x104, 0xC8 };
static s32 nowload_count = 0;

void kzLoadCommonGms() {
    u8 *gms = (u8 *)hGetSysDataAddr(7);
    if (gms != NULL) {
        nkLoadGms(KL2_FHM_ADDR(gms, 0));
        sceGsSyncPath(0, 0);
    }
}

#ifdef KL2_VER_RETAIL
void kzInitNowload() {
    klworks_flag = GameGbl.vision == 0x0105;
    dl_status = DL_STATUS_NML_LOAD;
    ret_gameread = 0;
    if (GameGbl.vision == 0x0105) {
        klwcnt = 0;
    }
}
#endif

void kzReturnTitle() {
    if (first_enter) {
        nkChangeArea(KL2_VISION(30, 0), 0, 0, 0.0);
    } else {
        nkChangeArea(KL2_VISION(30, 2), 0, 0, 0.0);
    }
}

s32 kzCheckGenju() {
    return mommet_mode == MOM_MODE_GENJU;
}

void kzReturnGenju() {
    if (kzCheckGenju()) {
        nkChangeArea(KL2_VISION(35, 1), 0, 0, 0.0);
    }
}

s32 kzCheckTheater() {
    return mommet_mode == MOM_MODE_THEATER;
}

void kzReturnTheater() {
    if (kzCheckTheater()) {
        nkChangeArea(KL2_VISION(35, 1), 0, 0, 0.0);
    }
}

s32 kzGetScene() {
    return 0;
}

void kzGameMainCL() {
    switch (cloud_flag) {
        case CLOUD_NORMAL:
            KumoDraw();
            break;
        case CLOUD_LIGHT:
            kz_Draw_Cloud_Core();
            break;
        default:
            break;
    }

    cloud_flag = CLOUD_NONE;
}

void kzGameMainWM() {
    if (kz_Get_StageNo() >= 0) {
        kzWorldMapJobTbl[wm_jobcnt]();
    }
}

void kzGameMainTD() {
    if (pause_interval > 0) {
        pause_interval--;
    }

    kzTwoDmsnJobTbl[td_jobcnt]();
    kzTD_Draw_Fade();
}

void kzInitNowload() {
    nowload_count = 40;
}

void kzDrawNowload() {
	KZCOLOR col = { 0x80, 0x80, 0x80, 0x80 };

    nowload_count++;
    if (nowload_count > 120) {
        nowload_count = 0;
    }
    if (nowload_count < 80) {
        f32 alpha = cos((nowload_count * KL2_2PI) / 80.0f) * 64.0 + 64.0;
        if (alpha < 0.0f) {
            col.a = 0x00;
        } else {
            col.a = alpha;
        }
    }

    kzTD_Set_GsEnv_Std();
    kzSTR_Draw(&STRBASE_SYS_NOWLOAD, 0xFFFF, &col, STR_SYSTEM_00);
}

void kzVisionStartOn() {
    if (kz_Get_StageMode() != STG_MODE_ETC && td_jobcnt != TD_JOB_GAM_VISIONSTART) {
        vision_count = 0;
        td_jobcnt_next0 = TD_JOB_GAM_VISIONSTART;
        kzTD_Change_Job();
    }
}

void kzPauseOn() {
    if (pause_interval > 0) {
        return;
    }

    switch (kz_Get_StageMode()) {
        case STG_MODE_GAME:
            td_jobcnt_next0 = TD_JOB_GAM_PAUSE;
            break;
        case STG_MODE_BOSS:
            if (kzCheckGenju()) {
                td_jobcnt_next0 = TD_JOB_MOM_PAUSE;
            } else {
                td_jobcnt_next0 = TD_JOB_GAM_PAUSE;
            }
            break;
        case STG_MODE_ETC:
            return;
        default:
            return;
    }

    switch (td_jobcnt) {
        case TD_JOB_IDLE:
            pause_return = TD_JOB_IDLE;
            break;
        case TD_JOB_GAM_VISIONSTART:
            pause_return = TD_JOB_GAM_VISIONSTART;
            break;
        default:
            return;
    }

    GameGbl.pause_flag2 = 1;
    kzTD_Change_Job();
}