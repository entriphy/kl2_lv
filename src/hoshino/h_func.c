#include "hoshino/h_func.h"
#include "hoshino/h_init.h"
#include "hoshino/h_menu.h"
// #include "h_test.h"
#include "okanoyo/okprint.h"

#ifdef KL2_VER_TRIAL
#define FONT_WIDTH  12
#define FONT_HEIGHT 6
#else
#define FONT_WIDTH  16
#define FONT_HEIGHT 8
#endif

// TODO: delete
extern s32 (*hTestFuncTbl[])();
extern s32 TestMode;

static FUNCTBL MainFuncTbl[] = {
    {hMenuFuncTbl, -1},
    {hTestFuncTbl, -1},
    {NULL,         -1}
};
s32 (*HFuncTbl[])() = {
    hInit,
    hMain
};

s32 hInit() {
    KL2_DEBUG_PRINT(("hInit\n"));
    memset(&hG, 0, sizeof(hGLOBAL));
#ifdef KL2_VER_TRIAL
    sceGsResetGraph(0, SCE_GS_INTERLACE, SCE_GS_NTSC, SCE_GS_FRAME);
    sceGsSetDefDBuffDc(&hG.db, SCE_GS_PSMCT32, SCR_WIDTH, SCR_HEIGHT, SCE_GS_ZGREATER, SCE_GS_PSMZ24, SCE_GS_CLEAR);
#endif
    FlushCache(WRITEBACK_DCACHE);
    while (!sceGsSyncV(0));
    OkDefaultSysInit(SCR_WIDTH, SCR_HEIGHT, FONT_WIDTH, FONT_HEIGHT);
    OkPrintSysInit(3, SCR_WIDTH, SCR_HEIGHT, FONT_WIDTH, FONT_HEIGHT);
    hPkInit(&hG.PkData);
    hPkSetBp(10000);
    SysGbl.nsmode++;

    // Return intentionally left blank
}

s32 hMain() {
    s32 (**subfunctbl)();
    s32 inter;

#ifdef KL2_VER_TRIAL
    sceGsSwapDBuffDc(&hG.db, hG.fr);
#else
    sceGsSwapDBuffDc(&GameGbl.db, hG.fr);
#endif
    hG.fr++;
    sceGsSyncPath(0, 0);
    FlushCache(0);

    subfunctbl = MainFuncTbl[SysGbl.fmode].func;
    if (subfunctbl != NULL) {
        subfunctbl[SysGbl.smode]();
    } else {
        SysGbl.fmode = 0;
        SysGbl.smode = 0;
    }

    inter = SyncV();
#ifdef KL2_VER_TRIAL
    if (hG.fr & 1) {
        sceGsSetHalfOffset(&hG.db.draw11, 0x800, 0x800, inter);
        sceGsSetHalfOffset2(&hG.db.draw12, 0x800, 0x800, inter);
    } else {
        sceGsSetHalfOffset(&hG.db.draw01, 0x800, 0x800, inter);
        sceGsSetHalfOffset2(&hG.db.draw02, 0x800, 0x800, inter);
    }
#else
    if (TestMode != 3) {
        if (hG.fr & 1) {
            sceGsSetHalfOffset(&GameGbl.db.draw11, 0x800, 0x800, inter);
            sceGsSetHalfOffset2(&GameGbl.db.draw12, 0x800, 0x800, inter);
        } else {
            sceGsSetHalfOffset(&GameGbl.db.draw01, 0x800, 0x800, inter);
            sceGsSetHalfOffset2(&GameGbl.db.draw02, 0x800, 0x800, inter);
        }
    }
#endif

    FlushCache(0);
    sceGsSyncPath(0, 0);
    OkPFontFlush(PAD_TRG_SELECT(GameGbl.kpd[1]));

    // Return intentionally left blank
}