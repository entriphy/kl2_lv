#include "hoshino/h_menu.h"
#include "okanoyo/okprint.h"
#include "okanoyo/okmain.h"

hGLOBAL hG __attribute__((section(".bss")));;
s32 RpcArg[16] __attribute__((section(".bss")));
s128 hPacketArea[2048] __attribute__((section(".bss")));
static MENU_WORK MenuGbl;

static s32 hMenuInit() {
    SysGbl.smode++;
    MenuGbl.mode = 0;
    MenuGbl.vision = 0;
    MenuGbl.flag = 0;
    MenuGbl.vscnt = 0;

    // Return intentionally left blank
}

static s32 hMenuMain() {
    static struct {
        char *str0;
        char *str1;
        s32 fmode;
        s32 smode;
    } MenuCont[] = {
        "SOUND TEST", "_TEST", 1, 0
    };
    s32 lp1;
    s32 sy;
    kPadDATA *kpd;

    kpd = &GameGbl.kpd[0];
    nkGetPad();
    kpd->lvl = nkGetPlvl(0);
    kpd->trg = nkGetPtrg(0);
    kpd->rep = nkGetPrep(0);

    KL2_OK_PRINT((0, 10, 1, scr_p[0], "HOSHINO MENU"));
    KL2_OK_PRINT((0, 23, 1, scr_p[0], "irqc=%d", SysGbl.irqc));
    sy = 6;
    for (lp1 = 0; lp1 < 1; lp1++) {
        KL2_OK_PRINT((0, 4, sy, scr_p[0], MenuCont[lp1].str0));
        sy++;
    }
    KL2_OK_PRINT((0, 3, MenuGbl.mode + 6, scr_p[0], ">"));

    if (MenuGbl.mode > 0 && pPAD_TRG_UP(kpd) != 0) {
        MenuGbl.mode--;
    } else if (MenuGbl.mode < 0 && pPAD_TRG_DOWN(kpd) != 0) {
        MenuGbl.mode++;
    }

    if (pPAD_TRG_START(kpd) && MenuGbl.mode < 1) {
        SysGbl.fmode = MenuGbl.mode + 1;
        SysGbl.smode = 0;
    }
    if (pPAD_TRG_R2(kpd)) {
        SysGbl.nmode = 3;
        SysGbl.nsmode = 0;
    }
    if (pPAD_TRG_L2(kpd)) {
        SysGbl.nmode = 1;
        SysGbl.nsmode = 0;
    }

    // Return intentionally left blank
}

s32 (*hMenuFuncTbl[])() = {
    hMenuInit,
    hMenuMain
};