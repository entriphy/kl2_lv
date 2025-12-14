#include "kazuya/wm_job.h"
#include "harada/hr_main.h"
#include "harada/hr_mapdr.h"
#include "kazuya/bios.h"
#include "kazuya/cvar.h"
#include "kazuya/obj_std.h"
#include "nakano/camera.h"

void kzWM_Step_Job(s32 add) {
    wm_jobcnt += add;
}

void kzWM_Back_Job(s32 sub) {
    wm_jobcnt -= sub;
}

void kzWM_Change_Job() {
    if (wm_jobcnt_next0 <= WM_JOB_NONE) return;
    if (wm_jobcnt_next0 >= WM_JOB_NUM) return;

    wm_jobcnt_current = wm_jobcnt_next0;
    wm_jobcnt = wm_jobcnt_next0;
    wm_jobcnt_next0 = wm_jobcnt_next1;
    wm_jobcnt_next1 = WM_JOB_NONE;
}

void kzWM_Call_Job() {
    if (wm_jobcnt_sub <= WM_JOB_NONE) return;
    if (wm_jobcnt_sub >= WM_JOB_NUM) return;
    
    wm_jobcnt_ret = wm_jobcnt_current;
    wm_jobcnt = wm_jobcnt_sub;
    wm_jobcnt_sub = WM_JOB_NONE;
}

void kzWM_Return_Job() {
    if (wm_jobcnt_ret <= WM_JOB_NONE) return;
    if (wm_jobcnt_ret >= WM_JOB_NUM) return;

    wm_jobcnt = wm_jobcnt_ret;
    wm_jobcnt_ret = WM_JOB_NONE;
}

void kzWM_Init_All() {
    wm_jobcnt_current = WM_JOB_IDLE;
    wm_jobcnt = WM_JOB_IDLE;
    wm_jobcnt_ret = WM_JOB_NONE;
    wm_jobcnt_sub = WM_JOB_NONE;
    wm_jobcnt_next1 = WM_JOB_NONE;
    wm_jobcnt_next0 = WM_JOB_NONE;
}

void kzWM_Job_Idle() {
    // Empty function
}

void kzWM_Job_Main() {
    sceVu0FMATRIX mat;
    sceVu0FVECTOR fv;
    static VPOINFO *vpo = NULL;
    OBJ_STD_INFO *obj = StdObjects[0];

    if (pPAD_LVL_UP(kpd0))    (*obj->pos)[1] -= 1.0f;
    if (pPAD_LVL_DOWN(kpd0))  (*obj->pos)[1] += 1.0f;
    if (pPAD_LVL_LEFT(kpd0))  (*obj->pos)[0] -= 1.0f;
    if (pPAD_LVL_RIGHT(kpd0)) (*obj->pos)[0] += 1.0f;
    if (pPAD_LVL_L1(kpd0))    (*obj->pos)[2] -= 1.0f;
    if (pPAD_LVL_L2(kpd0))    (*obj->pos)[2] += 1.0f;

    if (pPAD_LVL_R1(kpd0))        (*obj->rot)[1] += 0.1f;
    if (pPAD_LVL_R2(kpd0))        (*obj->rot)[1] -= 0.1f;
    if ((*obj->rot)[1] > KL2_PI)  (*obj->rot)[1] = -KL2_PI;
    if ((*obj->rot)[1] < -KL2_PI) (*obj->rot)[1] = KL2_PI;

    if (pPAD_LVL_TRIANG(kpd0)) {
        (*obj->scale)[0] -= 0.1f;
        (*obj->scale)[1] -= 0.1f;
        (*obj->scale)[2] -= 0.1f;
    }
    if (pPAD_LVL_CROSS(kpd0)) {
        (*obj->scale)[0] += 0.1f;
        (*obj->scale)[1] += 0.1f;
        (*obj->scale)[2] += 0.1f;
    }
    if ((*obj->scale)[0] < 0.0f) (*obj->scale)[0] = 0.0f;
    if ((*obj->scale)[1] < 0.0f) (*obj->scale)[1] = 0.0f;
    if ((*obj->scale)[2] < 0.0f) (*obj->scale)[2] = 0.0f;

    if (pPAD_TRG_SQUARE(kpd0)) {
        KL2_DEBUG_PRINT(("#################################################\n\n"));
        KL2_DEBUG_PRINT(("     Trans X = %f\n", (*obj->pos)[0]));
        KL2_DEBUG_PRINT(("           Y = %f\n", (*obj->pos)[1]));
        KL2_DEBUG_PRINT(("           Z = %f\n", (*obj->pos)[2]));
        KL2_DEBUG_PRINT(("\n"));
        KL2_DEBUG_PRINT(("     Rot   Y = %f\n", (*obj->rot)[1]));
        KL2_DEBUG_PRINT(("\n"));
        KL2_DEBUG_PRINT(("     Scale   = %f\n", (*obj->scale)[0]));
        KL2_DEBUG_PRINT(("\n#################################################\n"));
    }

    CamDebug(&GameGbl.cam);

    if (wm_jobcnt == WM_JOB_MAIN) {
        kzOST_Setup(OBJECT_STD_KLONOA_WM);
        CamInit(&GameGbl.cam);
        GameGbl.cam.posi[0] = 292.0f;
        GameGbl.cam.posi[1] = -692.0f;
        GameGbl.cam.posi[2] = -525.0f;
        GameGbl.cam.ang[0] = 0.82030398f;
        GameGbl.cam.scr_z = 1040.0f;
        vpo = hrget_vpoinfo(0);
        kzWM_Step_Job(1);
    }

    if (wm_jobcnt == WM_JOB_MAIN_MAIN) {
        CamCalMatrix(&GameGbl.cam);
        sceVu0UnitMatrix(mat);
        SETVEC(fv, 0.0f, 0.0f, 0.0f, 1.0f);
        sceVu0TransMatrix(mat, mat, fv);
        sceVu0MulMatrix(mat, GameGbl.wsm, mat);
        if (vpo != NULL) {
            hrDrawVpoi(mat, vpo, 0);
        }
    }
}

void kzWM_Job_Status() {
    sceVu0FMATRIX mat;
    sceVu0FVECTOR fv;
    s32 i;
    s32 last_doll;
    static s32 rack_mode = 2;
    static VPOINFO *vpo = NULL;
    static s32 rack_vpo[4] = { 0, 1, 2, 3 };
    static sceVu0FVECTOR campos[4] = {
        { -77.0f, -155.0f, -860.0f, 1500.0f },
        { -77.0f, -134.0f, -860.0f, 1500.0f },
        { -77.0f, -113.0f, -860.0f, 1500.0f },
        { -77.0f, -92.0f,  -860.0f, 1500.0f },
    };
    static s32 obj_array[16] = {
        OBJECT_STD_MMD_00,
        OBJECT_STD_MMD_01,
        OBJECT_STD_MMD_02,
        OBJECT_STD_MMD_03,
        OBJECT_STD_MMD_04,
        OBJECT_STD_MMD_05,
        OBJECT_STD_MMD_06,
        OBJECT_STD_MMD_07,
        OBJECT_STD_MMD_08,
        OBJECT_STD_MMD_09,
        OBJECT_STD_MMD_10,
        OBJECT_STD_MMD_11,
        OBJECT_STD_MMD_12,
        OBJECT_STD_MMD_13,
        OBJECT_STD_MMD_14,
        OBJECT_STD_MMD_15
    };
    static s32 sel_obj = 0;

    last_doll = sel_obj;

    if (pPAD_TRG_L1(kpd0)) {
        sel_obj--;
        if (sel_obj < 0) sel_obj = 15;
    }
    if (pPAD_TRG_R1(kpd0)) {
        sel_obj++;
        if (sel_obj > 15) sel_obj = 0;
    }
    if (pPAD_TRG_SQUARE(kpd0)) {
        KL2_DEBUG_PRINT(("#################################################\n\n"));
        KL2_DEBUG_PRINT(("     Camera X = %f\n", GameGbl.cam.posi[0]));
        KL2_DEBUG_PRINT(("            Y = %f\n", GameGbl.cam.posi[1]));
        KL2_DEBUG_PRINT(("            Z = %f\n", GameGbl.cam.posi[2]));
        KL2_DEBUG_PRINT(("\n#################################################\n"));
    }

    CamDebug(&GameGbl.cam);

    if (wm_jobcnt == WM_JOB_STATUS) {
        for (i = 0; i < 16; i++) {
            kzOST_Setup(obj_array[i]);
            last_doll = i;
        }

        if (last_doll < 4) {
            rack_mode = 0;
        } else if (last_doll < 8) {
            rack_mode = 1;
        } else if (last_doll < 12) {
            rack_mode = 2;
        } else {
            rack_mode = 3;
        }

        CamInit(&GameGbl.cam);
        GameGbl.cam.posi[0] = campos[rack_mode][0];
        GameGbl.cam.posi[1] = campos[rack_mode][1];
        GameGbl.cam.posi[2] = campos[rack_mode][2];
        GameGbl.cam.scr_z = campos[rack_mode][3];
        vpo = hrget_vpoinfo(rack_vpo[rack_mode]);
        kzWM_Step_Job(1);
    }

    if (wm_jobcnt == WM_JOB_STATUS_MAIN) {
        CamCalMatrix(&GameGbl.cam);
        sceVu0UnitMatrix(mat);
        SETVEC(fv, 0.0f, 0.0f, 0.0f, 1.0f);
        sceVu0TransMatrix(mat, mat, fv);
        sceVu0MulMatrix(mat, GameGbl.wsm, mat);
        if (vpo != NULL) {
            hrDrawVpoi(mat, vpo, 0);
        }
    }

}

void kzWM_Job_MomTop() {
    CamDebug(&GameGbl.cam);

    if (wm_jobcnt == WM_JOB_MOMTOP) {
        kzOST_Setup(OBJECT_STD_MOMMET);
        CamInit(&GameGbl.cam);
        GameGbl.cam.posi[0] = 10.0f;
        GameGbl.cam.posi[1] = -55.0f;
        GameGbl.cam.posi[2] = -850.0f;
        GameGbl.cam.scr_z = 1024.0f;
        kzWM_Step_Job(1);
    }

    if (wm_jobcnt == WM_JOB_MOMTOP_MAIN) {
        CamCalMatrix(&GameGbl.cam);
    }
}

void kzWM_Job_VisionOver() {
    if (pPAD_TRG_R2(kpd0)) {
        KL2_DEBUG_PRINT(("#################################################\n\n"));
        KL2_DEBUG_PRINT(("     Camera X = %f\n", GameGbl.cam.posi[0]));
        KL2_DEBUG_PRINT(("            Y = %f\n", GameGbl.cam.posi[1]));
        KL2_DEBUG_PRINT(("            Z = %f\n", GameGbl.cam.posi[2]));
        KL2_DEBUG_PRINT(("\n#################################################\n"));
    }

    CamDebug(&GameGbl.cam);
    if (wm_jobcnt == WM_JOB_VISIONOVER) {
        kzOST_Setup(OBJECT_STD_KLONOA_VO);
        CamInit(&GameGbl.cam);
        GameGbl.cam.posi[0] = 0.0f;
        GameGbl.cam.posi[1] = -60.0f;
        GameGbl.cam.posi[2] = -200.0f;
        kzWM_Step_Job(1);
    }

    if (wm_jobcnt == WM_JOB_VISIONOVER_MAIN) {
        CamCalMatrix(&GameGbl.cam);
    }
}

void (*kzWorldMapJobTbl[])() = {
    kzWM_Job_Idle,
    kzWM_Job_Main,
    kzWM_Job_Main,
    kzWM_Job_Status,
    kzWM_Job_Status,
    kzWM_Job_MomTop,
    kzWM_Job_MomTop,
    kzWM_Job_VisionOver,
    kzWM_Job_VisionOver,
};
