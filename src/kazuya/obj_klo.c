#include "kazuya/obj_klo.h"
#include "nakano/objfunc.h"
#include "nakano/route.h"
#include "take/motsys.h"
#include "take/object.h"
#include "take/sfxbios.h"
#include "okanoyo/okio.h"

static sceVu0FMATRIX NormalLight;
static sceVu0FMATRIX LightColor;
static sceVu0FVECTOR RTV_Buffer[65];
static s32 RTV_Now;

void kzOKL_Init_Light() {
    static s32 dir[3][2] = {
        { -38, 17 },
        { 155, 0 },
        { 0, 0 }
    };
    static u8 col[4][4] = {
        { 0x54, 0x3F, 0x1F, 0x00 },
        { 0x0C, 0x16, 0x17, 0x00 },
        { 0x00, 0x00, 0x00, 0x00 },
        { 0x40, 0x40, 0x40, 0x00 }
    };
    sceVu0FVECTOR light[3];
    sceVu0FVECTOR color[4];
    s32 i;
    s32 j;

    for (i = 0; i < 3; i++) {
        light[i][0] = sinf(dir[i][0] * KL2_2PI / 360.0f);
        light[i][0] *= cosf(dir[i][1] * KL2_2PI / 360.0f);
        light[i][2] = cosf(dir[i][0] * KL2_2PI / 360.0f);
        light[i][2] *= cosf(dir[i][1] * KL2_2PI / 360.0f);
        light[i][1] = sinf(dir[i][1] * KL2_2PI / 360.0f);
        light[i][3] = 0.0f;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            color[i][j] = (f32)col[i][j] / 255.0f;
        }
    }

    sceVu0NormalLightMatrix(NormalLight, light[0], light[1], light[2]);
    sceVu0LightColorMatrix(LightColor, color[0], color[1], color[2], color[3]);
}

void kzOKL_Init_RTV_Buffer(RT_WRK *rtw, s16 rtn) {
    s32 i;
    sceVu0FVECTOR vct;
    ROUTE *mapr;

    SetRouteNo(rtw, rtn);
    RTV_Now = 32;
    SetMichinori(rtw, 0);
    GetMichiVec(rtw, RTV_Buffer[RTV_Now]);
    sceVu0CopyVector(vct, RTV_Buffer[RTV_Now]);

    for (i = 32 - 1; i >= 0; i--) {
        MichiMove(rtw, -0x1000);
        if (rtw->cnt >= 0) {
            GetMichiVec(rtw, vct);
        }
        sceVu0CopyVector(RTV_Buffer[i], vct);
    }
    SetMichinori(rtw, 0);
    sceVu0CopyVector(vct, RTV_Buffer[RTV_Now]);

    for (i = 32 + 1; i < 64 + 1; i++) {
        MichiMove(rtw, 0x1000);
        mapr = &rtw->rtp[rtw->plc];
        if (rtw->cnt >> 12 <= mapr->co) {
            GetMichiVec(rtw, vct);
        }
        sceVu0CopyVector(RTV_Buffer[i], vct);
    }

    SetMichinori(rtw, 0);
}

void kzOKL_Renew_RTV_Buffer(RT_WRK *rtw) {
    s32 mcn;
    s32 RTV_Top;
    s32 RTV_Prv;
    ROUTE *mapr;

    mcn = GetMichinori(rtw);
    RTV_Now++;
    if (RTV_Now > 64) {
        RTV_Now -= 65;
    }
    RTV_Top = RTV_Now + 32;
    if (RTV_Top > 64) {
        RTV_Top -= 65;
    }

    MichiMove(rtw, 0x20000);
    mapr = &rtw->rtp[rtw->plc];
    if (rtw->cnt >> 12 <= mapr->co) {
        GetMichiVec(rtw, RTV_Buffer[RTV_Top]);
    } else {
        RTV_Prv = RTV_Top - 1;
        if (RTV_Prv < 0) {
            RTV_Prv += 65;
        }
        sceVu0CopyVector(RTV_Buffer[RTV_Top], RTV_Buffer[RTV_Prv]);
    }

    SetMichinori(rtw, mcn);
    MichiMove(rtw, 0x1000);
}

void kzOKL_Get_Rot(OBJWORK *objw) {
    sceVu0FVECTOR vct;
    s32 i;

    sceVu0CopyVector(vct, RTV_Buffer[0]);
    for (i = 1; i < 65; i++) {
        sceVu0AddVector(vct, vct, RTV_Buffer[i]);
    }
    sceVu0DivVector(vct, vct, 65.0f);
    GetMichiRotXY(vct, objw->rot);
}

void kzOKL_Draw(OBJWORK *objw) {
    SFXOBJ *pObj;
    PsfxMODEL *model = objw->prim;

    OutLineEnvInit(GameGbl.fr, GameGbl.inter);
    sceVu0CopyMatrix(Scr.WvMtx, GameGbl.wvm);
    sceVu0CopyMatrix(Scr.VsMtx, GameGbl.vsm);
    sceVu0CopyMatrix(Scr.WsMtx, GameGbl.wsm);
    Vu0ProgTrans();

    pObj = model->pObj;
    SetObjPause(pObj, GameGbl.pause_flag);
    pObj->Condition = 1;
    SetObjNormalLight(pObj, &NormalLight);
    SetObjLightColor(pObj, &LightColor);
    SETVEC(model->Rot, objw->rot[0], objw->rot[1], objw->rot[2], 0.0f);
    SETVEC(model->Trans, objw->posi[0], objw->posi[1], objw->posi[2], 0.0f);
    SetBaseMatrix(pObj, model->Rot, model->Trans, 1);
    SetObjScale(pObj, model->Scale);
    ModelDraw(pObj);
}

void kzOKL_Init(OBJWORK *objw) {
    PsfxMODEL *model;
    SFXOBJ *pObj;
    s32 ret;

    objw->prim = getmem(sizeof(PsfxMODEL));
    model = objw->prim;
    objw->draw = kzOKL_Draw;
    kzOKL_Init_RTV_Buffer(&objw->rtw, 0);

    model->pObj = SetSfxObject(getBuff(0, 0, "host0:./dat/chr/kldata.bin", &ret));
    if (model->pObj == NULL) {
        KL2_DEBUG_PRINT(("cannot get buffer. [kzOKL_Init]\n"));
    }
    pObj = model->pObj;
    pObj->Condition = 1;
    model->ActNum = 10;
    SetAct(pObj, 10);
    SetBaseMatrix(pObj, model->Rot, model->Trans, 0);
    SETVEC(model->Scale, 1.0f, 1.0f, 1.0f, 0.0f);
    kzOKL_Init_Light();
    objw->bun0++;
}

void kzOKL_Main(OBJWORK *objw) {
    PsfxMODEL *model = objw->prim;
    SFXOBJ *pObj = model->pObj;

    MichiPosi(&objw->rtw, objw->posi);
    kzOKL_Get_Rot(objw);
    kzOKL_Renew_RTV_Buffer(&objw->rtw);
    if (PAD_TRG_CIRCLE(GameGbl.kpd[0])) {
        model->ActNum++;
        if (model->ActNum > 204) {
            model->ActNum = 1;
        }
        SetActIp(pObj, model->ActNum);
    }
}

void (*kzObjectKLonoaFuncTbl[])(OBJWORK *) = { kzOKL_Init, kzOKL_Main };

void kzOKL_Entry(OBJWORK *objw) {
    kzObjectKLonoaFuncTbl[objw->bun0](objw);
}

void kzOKL_Setup() {
	OBJWORK *objw = SearchOBJWORK(SysGbl.objwork, SysGbl.n_objw);
    if (objw != NULL) {
        objw->stat0 = 8;
        objw->stat1 = 2;
        objw->bun0 = 0;
    }
}
