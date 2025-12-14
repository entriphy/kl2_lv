#include "kazuya/func.h"
#include "kazuya/menu.h"
#include "kazuya/sample.h"
#include "kazuya/wm_main.h"
#include "okanoyo/okmain.h"

static FUNCTBL MainFuncTbl[] = {
    { kzMenuFuncTbl,     -1 },
    { kzWorldMapFuncTbl, -1 },
    { NULL,              -1 },
    { NULL,              -1 },
    { kzSampleFuncTbl,   -1 }
};

s32 kzInit() {
    SysGbl.nsmode++;
    if (fontDispID == 8) {
        KL2_DEBUG_PRINT(("kzInit\n"));
    }
    return 0;
}

s32 kzMain() {
	s32 (**subfunctbl)() = MainFuncTbl[SysGbl.fmode].func;
    if (subfunctbl != NULL) {
        subfunctbl[SysGbl.smode]();
    } else {
        SysGbl.fmode = 0;
        SysGbl.smode = 0;
    }
    return 0;
}

s32 (*kzFuncTbl[])() = { kzInit, kzMain };
