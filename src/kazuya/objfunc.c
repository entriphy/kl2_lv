#include "kazuya/objfunc.h"
#include "kazuya/obj_klo.h"
#include "kazuya/obj_std.h"

static void (*ObjJTbl[])(OBJWORK *) = {
    NULL,
    kzOST_Entry,
    kzOKL_Entry
};

void kzObjFunc(OBJWORK *objw) {
    if (objw->stat1 != 0) {
        ObjJTbl[objw->stat1](objw);
    }
}