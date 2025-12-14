#include "kazuya/menu.h"
#include "okanoyo/okmain.h"
#include "okanoyo/okprint.h"
#include "nakano/nkpad.h"

typedef struct { // 0x10
    /* 0x0 */ s32 mode;
    /* 0x4 */ s32 vision;
    /* 0x8 */ s32 flag;
    /* 0xc */ s32 vscnt;
} MENU_WORK;

static MENU_WORK MenuGbl;

static s32 kzMenuInit() {
    SysGbl.smode++;
    MenuGbl.mode = 0;
    MenuGbl.vision = 0;
    MenuGbl.flag = 0;
    MenuGbl.vscnt = 0;

    sceGsResetGraph(0, SCE_GS_INTERLACE, SCE_GS_NTSC, SCE_GS_FRAME);
    sceGsSetDefDBuffDc(&GameGbl.db, SCE_GS_PSMCT32, SCR_WIDTH, SCR_HEIGHT, SCE_GS_ZGREATER, SCE_GS_PSMZ24, SCE_GS_CLEAR);
    FlushCache(WRITEBACK_DCACHE);
    OkDefaultSysInit(SCR_WIDTH, SCR_HEIGHT, 12, 6);
    OkPrintSysInit(8, SCR_WIDTH, SCR_HEIGHT, 12, 6);
    return 0;
}

static s32 kzMenuMain() {
	static struct {
		char *str0;
		char *str1;
		s32 fmode;
		s32 smode;
	} MenuCont[4] = {
        "WorldMap", "_WorldMap", 0, 0,
        "TEST1", "_TEST1", 1, 0,
        "TEST2", "_TEST2", 2, 0,
        "Sample", "_Sample", 3, 0,
    };
	s32 lp1;
	s32 sy;
	kPadDATA *kpd;
	s32 inter;

    sceGsSwapDBuffDc(&GameGbl.db, GameGbl.fr);
    GameGbl.fr++;
    sceGsSyncPath(0, 0);

    kpd = &GameGbl.kpd[0];
    nkGetPad();
    kpd->lvl = nkGetPlvl(0);
    kpd->trg = nkGetPtrg(0);
    kpd->rep = nkGetPrep(0);

    FlushCache(WRITEBACK_DCACHE);

    KL2_OK_PRINT((0, 10, 1, scr_p[0], "KAZUYA MENU"));
    KL2_OK_PRINT((0, 23, 1, scr_p[0], "irqc=%d", SysGbl.irqc));
    sy = 6;
    for (lp1 = 0; lp1 < 4; lp1++) {
        KL2_OK_PRINT((0, 4, sy, scr_p[0], MenuCont[lp1].str0));
        sy++;
    }
    KL2_OK_PRINT((0, 3, MenuGbl.mode + 6, scr_p[0], ">"));

    if (MenuGbl.mode > 0 && pPAD_TRG_UP(kpd) != 0) {
        MenuGbl.mode--;
    } else if (MenuGbl.mode < 3 && pPAD_TRG_DOWN(kpd) != 0) {
        MenuGbl.mode++;
    }

    if (pPAD_TRG_START(kpd) && MenuGbl.mode < 4) {
        SysGbl.fmode = MenuGbl.mode + 1;
        SysGbl.smode = 0;
    }
    if (pPAD_TRG_R2(kpd)) {
        SysGbl.nmode = 0;
        SysGbl.nsmode = 0;
    }
    if (pPAD_TRG_L2(kpd)) {
        SysGbl.nmode = 6;
        SysGbl.nsmode = 0;
    }

    sceGsSyncPath(0, 0);
    OkPFontFlush(PAD_TRG_SQUARE(GameGbl.kpd[0]) && PAD_LVL_CIRCLE(GameGbl.kpd[0]));
    inter = sceGsSyncV(0) ^ 1;
    if (GameGbl.fr & 1) {
        sceGsSetHalfOffset(&GameGbl.db.draw11, 0x800, 0x800, inter);
        sceGsSetHalfOffset2(&GameGbl.db.draw12, 0x800, 0x800, inter);
    } else {
        sceGsSetHalfOffset(&GameGbl.db.draw01, 0x800, 0x800, inter);
        sceGsSetHalfOffset2(&GameGbl.db.draw02, 0x800, 0x800, inter);
    }
    FlushCache(WRITEBACK_DCACHE);
    sceGsSyncPath(0, 0);
    return 0;
}

s32 (*kzMenuFuncTbl[])() = { kzMenuInit, kzMenuMain };