#include "nakano/objfunc.h"
#include "nakano/game.h"

// TODO: delete
extern void ObjNFunc(OBJWORK *objw);
extern void ObjOTest(OBJWORK *objw);
extern void ObjOFunc(OBJWORK *objw);
extern void hr_work_obcon(OBJWORK *objw);
extern void abObjFunc(OBJWORK *objw);
extern void htObjFunc(OBJWORK *objw);
extern void kzObjFunc(OBJWORK *objw);

void (*ObjJTbl[])(OBJWORK *objw) = {
    NULL,
    ObjNFunc,
    ObjOTest,
    ObjOFunc,
    NULL,
    hr_work_obcon,
    abObjFunc,
    htObjFunc,
    kzObjFunc,
    NULL  // ? (func_002198d8)
};

void InitObjWork(OBJWORK *objw) {
    u32 i;

    for (i = 0; i < sizeof(OBJWORK) / sizeof(s32); i++) {
        ((s32 *)objw)[i] = 0;
    }
}

void InitAllObjWork(OBJWORK *objwork, s32 n_objw) {
    OBJWORK *objw;
    s32 i;

    objw = objwork;
    for (i = 0; i < n_objw; i++) {
        InitObjWork(objw);
        objw++;
    }
}

OBJWORK * SearchOBJWORK(OBJWORK *objwork, s32 n_objw) {
    s32 i;
    OBJWORK *objw;

    objw = objwork;
    for (i = 0; i < n_objw; i++) {
        if (objw->stat0 == 0) {
            objw->pers = NULL;
            objw->draw = NULL;
            objw->drmir = NULL;
            objw->dreff = NULL;
            KL2_VER_RETAIL_ONLY(objw->drmiref = NULL);
            return objw;
        }
        objw++;
    }

    return NULL;
}

void SortObjWork(OBJWORK *objwork, s32 n_objw) {
    s32 i;
    s32 j;
    s16 flag;
    OBJWORK *objw;
    s16 *id;
    s16 *prty;
    s16 tmp;

    flag = 1;
    prty = SPR_MEM;
    id = prty + n_objw + 1;
    objw = objwork;
    j = 0;
    for (i = 0; i < n_objw; i++) {
        if (objw->stat0 != 0) {
            id[j] = i;
            prty[j] = objw->prty;
            j++;
        }
        objw++;
    }
    id[j] = -1;
    
    while (flag != 0) {
        flag = 0;
        for (i = 0; i < j - 1; i++) {
            if (prty[i] < prty[i + 1]) {
                tmp = prty[i];
                prty[i] = prty[i + 1];
                prty[i + 1] = tmp;
                
                tmp = id[i];
                id[i] = id[i + 1];
                id[i + 1] = tmp;
                flag = 1;
            }
        }
    }

    for (i = 0; i <= j; i++) {
        obj_id[i] = id[i];
    }
}

s32 ObjFunc(OBJWORK *objwork) {
    s32 i;
    OBJWORK *objw;

    for (i = 0; obj_id[i] >= 0 && i < 128; i++) {
        objw = &objwork[obj_id[i]];
        if (objw->stat0 != 0)
            ObjJTbl[objw->stat0](objw);
    }

    return i;
}
