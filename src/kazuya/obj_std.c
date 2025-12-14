#include "kazuya/obj_std.h"
#include "nakano/objfunc.h"
#include "sfx.h"
#include "take/motsys.h"
#include "take/object.h"
#include "okanoyo/okio.h"

sceVu0FVECTOR OBJPOS_STD_DEFAULT = { 0.0f, 0.0f, 0.0f, 0.0f };
sceVu0FVECTOR OBJROT_STD_DEFAULT = { 0.0f, 0.0f, 0.0f, 0.0f };
sceVu0FVECTOR OBJSCL_STD_DEFAULT = { 1.0f, 1.0f, 1.0f, 0.0f };
sceVu0FVECTOR OBJPOS_STD_KLONOA_WM = { 164.0f, -29.0f, -16.0f, 0.0f };
sceVu0FVECTOR OBJROT_STD_KLONOA_WM = { 0.0f, 0.0f, 0.0f, 0.0f };
sceVu0FVECTOR OBJSCL_STD_KLONOA_WM = { 1.0f, 1.0f, 1.0f, 0.0f };
sceVu0FVECTOR OBJPOS_STD_MOMMET = { -32.0f, 0.0f, -568.0f, 0.0f };
sceVu0FVECTOR OBJPOS_STD_MMD_00 = { -51.0f, -132.0f, 0.0f, 0.0f };
sceVu0FVECTOR OBJPOS_STD_MMD_01 = { -17.0f, -132.0f, 0.0f, 0.0f };
sceVu0FVECTOR OBJPOS_STD_MMD_02 = { 17.0f, -132.0f, 0.0f, 0.0f };
sceVu0FVECTOR OBJPOS_STD_MMD_03 = { 51.0f, -132.0f, 0.0f, 0.0f };
sceVu0FVECTOR OBJPOS_STD_MMD_04 = { -51.0f, -91.0f, 0.0f, 0.0f };
sceVu0FVECTOR OBJPOS_STD_MMD_05 = { -17.0f, -91.0f, 0.0f, 0.0f };
sceVu0FVECTOR OBJPOS_STD_MMD_06 = { 17.0f, -91.0f, 0.0f, 0.0f };
sceVu0FVECTOR OBJPOS_STD_MMD_07 = { 51.0f, -91.0f, 0.0f, 0.0f };
sceVu0FVECTOR OBJPOS_STD_MMD_08 = { -51.0f, -49.0f, 0.0f, 0.0f };
sceVu0FVECTOR OBJPOS_STD_MMD_09 = { -17.0f, -49.0f, 0.0f, 0.0f };
sceVu0FVECTOR OBJPOS_STD_MMD_10 = { 17.0f, -49.0f, 0.0f, 0.0f };
sceVu0FVECTOR OBJPOS_STD_MMD_11 = { 51.0f, -49.0f, 0.0f, 0.0f };
sceVu0FVECTOR OBJPOS_STD_MMD_12 = { -51.0f, -8.0f, 0.0f, 0.0f };
sceVu0FVECTOR OBJPOS_STD_MMD_13 = { -17.0f, -8.0f, 0.0f, 0.0f };
sceVu0FVECTOR OBJPOS_STD_MMD_14 = { 17.0f, -8.0f, 0.0f, 0.0f };
sceVu0FVECTOR OBJPOS_STD_MMD_15 = { 51.0f, -8.0f, 0.0f, 0.0f };
OBJ_STD_INFO ObjStdInfo_Klonoa_WM = { 1, 371, 2,  &OBJPOS_STD_KLONOA_WM, &OBJROT_STD_KLONOA_WM, &OBJSCL_STD_KLONOA_WM };
OBJ_STD_INFO ObjStdInfo_Klonoa_VO = { 1, 371, 40, &OBJPOS_STD_DEFAULT,   &OBJROT_STD_DEFAULT,   &OBJSCL_STD_DEFAULT };
OBJ_STD_INFO ObjStdInfo_Mommet = { 1, 10, 1, &OBJPOS_STD_MOMMET, &OBJROT_STD_DEFAULT, &OBJSCL_STD_DEFAULT };
OBJ_STD_INFO ObjStdInfo_Mmd_00 = { 0, 661, 2, &OBJPOS_STD_MMD_00, &OBJROT_STD_DEFAULT, &OBJSCL_STD_DEFAULT };
OBJ_STD_INFO ObjStdInfo_Mmd_01 = { 0, 662, 2, &OBJPOS_STD_MMD_01, &OBJROT_STD_DEFAULT, &OBJSCL_STD_DEFAULT };
OBJ_STD_INFO ObjStdInfo_Mmd_02 = { 0, 664, 2, &OBJPOS_STD_MMD_02, &OBJROT_STD_DEFAULT, &OBJSCL_STD_DEFAULT };
OBJ_STD_INFO ObjStdInfo_Mmd_03 = { 0, 665, 2, &OBJPOS_STD_MMD_03, &OBJROT_STD_DEFAULT, &OBJSCL_STD_DEFAULT };
OBJ_STD_INFO ObjStdInfo_Mmd_04 = { 0, 667, 2, &OBJPOS_STD_MMD_04, &OBJROT_STD_DEFAULT, &OBJSCL_STD_DEFAULT };
OBJ_STD_INFO ObjStdInfo_Mmd_05 = { 0, 668, 2, &OBJPOS_STD_MMD_05, &OBJROT_STD_DEFAULT, &OBJSCL_STD_DEFAULT };;
OBJ_STD_INFO ObjStdInfo_Mmd_06 = { 0, 669, 2, &OBJPOS_STD_MMD_06, &OBJROT_STD_DEFAULT, &OBJSCL_STD_DEFAULT };
OBJ_STD_INFO ObjStdInfo_Mmd_07 = { 0, 670, 2, &OBJPOS_STD_MMD_07, &OBJROT_STD_DEFAULT, &OBJSCL_STD_DEFAULT };
OBJ_STD_INFO ObjStdInfo_Mmd_08 = { 0, 671, 2, &OBJPOS_STD_MMD_08, &OBJROT_STD_DEFAULT, &OBJSCL_STD_DEFAULT };
OBJ_STD_INFO ObjStdInfo_Mmd_09 = { 0, 672, 2, &OBJPOS_STD_MMD_09, &OBJROT_STD_DEFAULT, &OBJSCL_STD_DEFAULT };
OBJ_STD_INFO ObjStdInfo_Mmd_10 = { 0, 673, 2, &OBJPOS_STD_MMD_10, &OBJROT_STD_DEFAULT, &OBJSCL_STD_DEFAULT };
OBJ_STD_INFO ObjStdInfo_Mmd_11 = { 0, 495, 2, &OBJPOS_STD_MMD_11, &OBJROT_STD_DEFAULT, &OBJSCL_STD_DEFAULT };
OBJ_STD_INFO ObjStdInfo_Mmd_12 = { 0, 496, 2, &OBJPOS_STD_MMD_12, &OBJROT_STD_DEFAULT, &OBJSCL_STD_DEFAULT };
OBJ_STD_INFO ObjStdInfo_Mmd_13 = { 0, 497, 2, &OBJPOS_STD_MMD_13, &OBJROT_STD_DEFAULT, &OBJSCL_STD_DEFAULT };
OBJ_STD_INFO ObjStdInfo_Mmd_14 = { 0, 498, 2, &OBJPOS_STD_MMD_14, &OBJROT_STD_DEFAULT, &OBJSCL_STD_DEFAULT };
OBJ_STD_INFO ObjStdInfo_Mmd_15 = { 0, 499, 2, &OBJPOS_STD_MMD_15, &OBJROT_STD_DEFAULT, &OBJSCL_STD_DEFAULT };
OBJ_STD_INFO *StdObjects[] = {
    &ObjStdInfo_Klonoa_WM,
    &ObjStdInfo_Klonoa_VO,
    &ObjStdInfo_Mommet,
    &ObjStdInfo_Mmd_00,
    &ObjStdInfo_Mmd_01,
    &ObjStdInfo_Mmd_02,
    &ObjStdInfo_Mmd_03,
    &ObjStdInfo_Mmd_04,
    &ObjStdInfo_Mmd_05,
    &ObjStdInfo_Mmd_06,
    &ObjStdInfo_Mmd_07,
    &ObjStdInfo_Mmd_08,
    &ObjStdInfo_Mmd_09,
    &ObjStdInfo_Mmd_10,
    &ObjStdInfo_Mmd_11,
    &ObjStdInfo_Mmd_12,
    &ObjStdInfo_Mmd_13,
    &ObjStdInfo_Mmd_14,
    &ObjStdInfo_Mmd_15
};
static sceVu0FMATRIX NormalLight;
static sceVu0FMATRIX LightColor;

void kzOST_Init_Light() {
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

void kzOST_Draw(OBJWORK *objw) {
    SFXOBJ *pObj;
    PsfxMODEL *model;
    OBJ_STD_INFO *info = objw->work;

    sceVu0CopyMatrix(Scr.WvMtx, GameGbl.wvm);
    sceVu0CopyMatrix(Scr.VsMtx, GameGbl.vsm);
    sceVu0CopyMatrix(Scr.WsMtx, GameGbl.wsm);

    model = objw->prim;
    pObj = model->pObj;
    SetObjPause(pObj, GameGbl.pause_flag);
    pObj->Condition = 1;
    SetObjNormalLight(pObj, &NormalLight);
    SetObjLightColor(pObj, &LightColor);
    SETVEC(model->Trans, (*info->pos)[0], (*info->pos)[1], (*info->pos)[2], (*info->pos)[3]);
    SETVEC(model->Rot, (*info->rot)[0], (*info->rot)[1], (*info->rot)[2], (*info->rot)[3]);
    SETVEC(model->Scale, (*info->scale)[0], (*info->scale)[1], (*info->scale)[2], (*info->scale)[3]);
    SetBaseMatrix(pObj, model->Rot, model->Trans, 0);
    SetObjScale(pObj, model->Scale);
    ModelDraw(pObj);
}

void kzOST_Init(OBJWORK *objw) {
	PsfxMODEL *model;
	SFXOBJ *pObj;
	OBJ_STD_INFO *info = objw->work;

    objw->prim = getmem(sizeof(PsfxMODEL));
    model = objw->prim;
    objw->draw = kzOST_Draw;

    model->pObj = GetSfxObjectData(info->obj_no);
    if (model->pObj == NULL) {
        KL2_DEBUG_PRINT(("cannot get work. [kzOST_Init]\n"));
    }
    pObj = model->pObj;
    pObj->Condition = 1;
    model->ActNum = info->act_no;
    SetAct(pObj, model->ActNum);
    if (info->outline == 0) {
        SetObjOutlineOff(pObj);
    }
    SETVEC(model->Trans, (*info->pos)[0], (*info->pos)[1], (*info->pos)[2], (*info->pos)[3]);
    SETVEC(model->Rot, (*info->rot)[0], (*info->rot)[1], (*info->rot)[2], (*info->rot)[3]);
    SETVEC(model->Scale, (*info->scale)[0], (*info->scale)[1], (*info->scale)[2], (*info->scale)[3]);
    SetBaseMatrix(pObj, model->Rot, model->Trans, 0);
    SetObjScale(pObj, model->Scale);
    kzOST_Init_Light();
    objw->bun0++;
}

void kzOST_Main(OBJWORK *objw) {
    // Empty function
}

void (*kzObjectStandardFuncTbl[])(OBJWORK *) = { kzOST_Init, kzOST_Main };

void kzOST_Entry(OBJWORK *objw) {
    kzObjectStandardFuncTbl[objw->bun0](objw);
}

void kzOST_Setup(s32 obj_no) {
	OBJWORK *objw = SearchOBJWORK(SysGbl.objwork, SysGbl.n_objw);
    if (objw != NULL) {
        objw->work = StdObjects[obj_no];
        objw->stat0 = 8;
        objw->stat1 = 1;
        objw->bun0 = 0;
    }
}