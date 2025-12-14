#include "abe/ab_objtest.h"
#include "nakano/objfunc.h"

static void DrawObjTest(OBJWORK *objw) {
    abGifPacket pack;
    sceVu0IVECTOR vi0;
    sceVu0IVECTOR vi1;
    sceVu0IVECTOR vi2;
    sceVu0FVECTOR vf0;
    sceVu0FVECTOR vf1;
    sceVu0FVECTOR vf2;
    sceVu0FMATRIX lmat;

    SETVEC(vf0, 0.0f,   0.0f,   0.0f, 1.0f);
    SETVEC(vf1, 100.0f, 0.0f,   0.0f, 1.0f);
    SETVEC(vf2, 0.0f,   100.0f, 0.0f, 1.0f);

    sceVu0UnitMatrix(lmat);
    sceVu0RotMatrixX(lmat, lmat, objw->rot[0]);
    sceVu0RotMatrixY(lmat, lmat, objw->rot[1]);
    sceVu0RotMatrixZ(lmat, lmat, objw->rot[2]);
    sceVu0TransMatrix(lmat, lmat, objw->posi);
    sceVu0MulMatrix(lmat, GameGbl.wsm, lmat);
    sceVu0RotTransPers(vi0, lmat, vf0, 1);
    sceVu0RotTransPers(vi1, lmat, vf1, 1);
    sceVu0RotTransPers(vi2, lmat, vf2, 1);

    pack.size = 0;
    pack.buf = SPR_MEM;
    pack.buf->ul128 = 0;
    pack.buf[pack.size++].ul32[0] = 0x70000007;
    
    pack.buf[pack.size].ul64[0] = 0x2005c00000008003;
    pack.buf[pack.size++].ul64[1] = SCE_GS_RGBAQ | SCE_GS_XYZ2 << 4;

    SETVEC(pack.buf[pack.size].ul32, 0xFF, 0x00, 0x00, 0x80);
    pack.size++;
    SETVEC(pack.buf[pack.size].ul32, vi0[0], vi0[1], vi0[2], 0x00);
    pack.size++;
    SETVEC(pack.buf[pack.size].ul32, 0x00, 0xFF, 0x00, 0x80);
    pack.size++;
    SETVEC(pack.buf[pack.size].ul32, vi1[0], vi1[1], vi1[2], 0x00);
    pack.size++;
    SETVEC(pack.buf[pack.size].ul32, 0x00, 0x00, 0xFF, 0x80);
    pack.size++;
    SETVEC(pack.buf[pack.size].ul32, vi2[0], vi2[1], vi2[2], 0x00);
    pack.size++;

    FlushCache(WRITEBACK_DCACHE);
    DmaChGIF->chcr.TTE = 1;
    sceDmaSend(DmaChGIF, SPR_SEND);
    sceDmaSync(DmaChGIF, 0, 0);
}

static void ObjInit(OBJWORK *objw) {
    objw->reg0 = 0;
    objw->draw = DrawObjTest;
    objw->bun0 = 1;
}

static void ObjMain(OBJWORK *objw) {
    objw->posi[0] += objw->spd[0];
    objw->posi[1] += objw->spd[1];
    
    if (objw->posi[0] < -1000.0f || objw->posi[0] > 1000.0f) {
        objw->spd[0] = -objw->spd[0];
    }

    if (objw->posi[1] < -1000.0f || objw->posi[1] > 1000.0f) {
        objw->spd[1] = -objw->spd[1];
    }

    objw->rot[0] += KL2_PI / 100.0f;
    objw->rot[1] += KL2_2PI / 100.0f;
    objw->rot[2] += KL2_PI3 / 10.0f;
    KL2_PI_CLAMP(objw->rot[0]);
    KL2_PI_CLAMP(objw->rot[1]);
    KL2_PI_CLAMP(objw->rot[2]);
}

static void (*ObjFuncTbl[])(OBJWORK *objw) = { ObjInit, ObjMain };

void abObjTest(OBJWORK *objw) {
    ObjFuncTbl[objw->bun0](objw);
}

void abSetObjTest(sceVu0FVECTOR vf) {
    OBJWORK *objw = SearchOBJWORK(SysGbl.objwork, SysGbl.n_objw);
    objw->stat0 = 6;
    objw->stat1 = 1;
    objw->bun0 = 0;
    SETVEC_XYZ(objw->posi, vf[0], vf[1], vf[2]);
    SETVEC_XY(objw->spd, 4.0f, -6.0f);
    SETVEC_XYZ(objw->rot, 0.0f, 0.0f, 0.0f);
}
