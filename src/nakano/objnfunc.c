#include "nakano/objnfunc.h"

// TODO: delete
extern void ObjKlo(OBJWORK *objw);
extern void ObjKazd(OBJWORK *objw);
extern void nkOCamTest(OBJWORK *objw);
extern void ObjGimTest(OBJWORK *objw);
extern void ObjGimTrain(OBJWORK *objw);
extern void ObjGimViking(OBJWORK *objw);
extern void ObjGimBridgeB7(OBJWORK *objw);
extern void ObjGimS2Bridge(OBJWORK *objw);
extern void ObjGimGpDoor0(OBJWORK *objw);
extern void ObjGimGpDoor1(OBJWORK *objw);
extern void ObjGimDoor04Pazzle(OBJWORK *objw);
extern void ObjSpotLight(OBJWORK *objw);
extern void ObjGimTest2(OBJWORK *objw);
extern void SmplMyu(OBJWORK *objw);
extern void nkPopuka(OBJWORK *objw);
extern void nkFilterCtrlObj(OBJWORK *objw);
extern void nkTaiEndObj(OBJWORK *objw);

static void (*ObjJTbl[])(OBJWORK *objw) = {
    NULL,
    ObjKlo,
    ObjKazd,
    nkOCamTest,
    ObjGimTest,
    ObjGimTrain,
    ObjGimViking,
    ObjGimBridgeB7,
    ObjGimS2Bridge,
    ObjGimGpDoor0,
    ObjGimGpDoor1,
    ObjGimDoor04Pazzle,
    ObjSpotLight,
    ObjGimTest2,
    SmplMyu,
    nkPopuka,
    nkFilterCtrlObj,
    nkTaiEndObj,
};

void ObjNFunc(OBJWORK *objw) {
    if (objw->stat1 != 0) {
        ObjJTbl[objw->stat1](objw);
    }
}
