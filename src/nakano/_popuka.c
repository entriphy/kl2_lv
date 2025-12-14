#include "nakano/popuka.h"
#include "harada/hr_pall.h"
#include "nakano/light.h"
#include "nakano/vu0mac.h"
#include "okanoyo/okmain.h"
#include "sfx.h"
#include "take/motsys.h"
#include "take/object.h"

#ifdef KL2_VER_RETAIL
static void DrawObjMir(OBJWORK *objw) {
    OBJWORK *objklo = GameGbl.klonoa;
    sceVu0FMATRIX *nl;
    sceVu0FMATRIX *lc;

    if (hr_pt_check() != 1) {
        PsfxMODEL *reg2 = (PsfxMODEL *)objw->reg2;
        SFXOBJ *pObj = reg2->pObj;
        SetSfxMotionSync(pObj, ((PsfxMODEL *)objw->prim)->pObj);
        pObj->Condition = 4;
        SetObjPause(pObj, 1);
        nkSetLight2(&objklo->rtw, objw->posi, &nl, &lc);
        SetObjNormalLight(pObj, nl);
        SetObjLightColor(pObj, lc);
        ModelDraw(pObj);
    }
}
#endif

static void DrawObj(OBJWORK *objw) {
    SFXOBJ *pObj;
    SupWORK *supw;
    PsfxMODEL *model;
    OBJWORK *objklo;
    HERO_WORK *herow;
#ifdef KL2_VER_RETAIL
    sceVu0FVECTOR vec;
#endif
    sceVu0FVECTOR vf;
    f32 rad;
    sceVu0FMATRIX *nl;
    sceVu0FMATRIX *lc;
    s32 var_s7;

    supw = objw->work;
#ifdef KL2_VER_RETAIL
    var_s7 = 0;
    objklo = GameGbl.klonoa;
    herow = objklo->work;
#endif
    model = objw->prim;

    if (hr_pt_check() == 1 || KL2_VER_COND(fontDispID != 0, 0)) {
        return;
    }

    pObj = model->pObj;
    SetObjPause(pObj, GameGbl.pause_flag);
    // if (objklo->reg0 & 0x200) {
    //     nkSetLight2(&herow->okuyuka->rtw, objw->posi, &nl, &lc);
    // } else {
    //     nkSetLight2(&objklo->rtw, objw->posi, &nl, &lc);
    // }
    // SetObjNormalLight(pObj, nl);
    // SetObjLightColor(pObj, lc);

    vu0_LoadMtx(GameGbl.d_wsm);
    vu0_ApplyMtx(vf, objw->posi);

#ifdef KL2_VER_TRIAL
    if (vf[3] > 512.0f) {
        pObj->Condition = 2;
    } else {
        pObj->Condition = 4;
    }
#else
    if (vf[3] < 128.0f) {
        pObj->Condition = 1;
    } else if (vf[3] < 256.0f) {
        pObj->Condition = 2;
    } else {
        pObj->Condition = 4;
    }
#endif

    // if (GameGbl.klonoa->reg0 & 0x400) {
    //     model->Rot[2] = 3.141592f;
    // } else {
    //     model->Rot[2] = 0.0f;
    // }
    // model->Rot[0] = objw->rot[0];

    // if (objw->bun1 == 4) {
    //     vf[1] = _atan2(objw->muki[0], objw->muki[2]) + 3.141592f;
    //     if (supw->muki == 2) {
    //         vf[1] = _atan2(objw->muki[0], objw->muki[2]) + 1.570796f;
    //     } else if (supw->muki == 3) {
    //         vf[1] = _atan2(objw->muki[0], objw->muki[2]) - 1.570796f;
    //     }
    //     vf[1] = nkRadMask(vf[1]);

    //     rad = vf[1] - model->Rot[1];
    //     rad = nkRadMask(rad);
    //     if (rad > 0.392699f) {
    //         model->Rot[1] += 0.392699f;
    //         var_s7 = 1;
    //     } else if (rad < -0.392699f) {
    //         model->Rot[1] -= 0.392699f;
    //         var_s7 = 1;
    //     } else {
    //         model->Rot[1] = vf[1];
    //     }
    //     model->Rot[1] = nkRadMask(model->Rot[1]);

    //     switch (supw->stat) {
    //         case 1:
    //             nkCallMotion(pObj, &model->ActNum, 3);
    //             break;
    //         case 3:
    //             nkCallMotion(pObj, &model->ActNum, 7);
    //             break;
    //         case 2:
    //             if (objw->spd[1] < 0.0f) {
    //                 nkCallMotion(pObj, &model->ActNum, 4);
    //             } else if (objw->spd[1] > 0.0f) {
    //                 nkCallMotion(pObj, &model->ActNum, 6);
    //             }
    //             break;
    //         case 11:
    //             if (var_s7) {
    //                 nkCallMotion(pObj, &model->ActNum, 3);
    //             } else {
    //                 nkCallMotion(pObj, &model->ActNum, 2);
    //             }
    //             break;
    //     }
    // } else {
    //     switch (objw->bun1) {
    //         case 1:
    //             vf[1] = objw->rot[1];
    //             rad = vf[1] - model->Rot[1];
    //             rad = nkRadMask(rad);
    //             model->Rot[1] += rad / 8.0f;
    //             model->Rot[1] = nkRadMask(model->Rot[1]);
    //             objw->rot[1] = model->Rot[1];
    //             nkCallMotion(pObj, &model->ActNum, 11);
    //             break;
    //         case 2:
    //             nkCallMotion(pObj, &model->ActNum, 9);
    //             break;
    //         case 3:
    //             model->Rot[1] = objw->rot[1];
    //             nkCallMotion(pObj, &model->ActNum, 10);
    //             if (objw->reg1 == 0) {
    //                 objw->reg1 = (s32)SetPopStar(pObj);
    //             }
    //             break;
    //     }
    // }

    // if (objw->bun1 != 3 && objw->reg1 != 0) {
    //     EraseStar(objw->reg1);
    //     objw->reg1 = 0;
    // }

    sceVu0CopyVector(model->Trans, objw->posi);
    SetBaseMatrix(pObj, model->Rot, model->Trans, 1);
    KL2_VER_RETAIL_ONLY(model->Scale[0] = model->Scale[1] = model->Scale[2] = objw->freg2);
    SetObjScale(pObj, model->Scale);
    ModelDraw(pObj);

#ifdef KL2_VER_RETAIL
    supw->motcnt = GetActCnt(pObj);
    supw->motcnt_end = GetActEndCnt(pObj);
    supw->motstop_flag = GetActStopFlag(pObj);
    supw->mot_actno = model->ActNum;
#endif
}