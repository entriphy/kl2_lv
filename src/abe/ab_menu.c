#include "abe/ab_menu.h"
#include "okanoyo/okmain.h"
#include "okanoyo/okprint.h"
#include "nakano/nkpad.h"

static MENU_WORK MenuGbl;

s32 abMenuInit() {
    SysGbl.smode++;
    MenuGbl.mode = 0;
    MenuGbl.vision = 0;
    MenuGbl.flag = 0;
    MenuGbl.vscnt = 0;
    sceGsResetGraph(0, SCE_GS_INTERLACE, SCE_GS_NTSC, SCE_GS_FRAME);
    sceGsSetDefDBuffDc(&GameGbl.db, SCE_GS_PSMCT32, SCR_WIDTH, SCR_HEIGHT, SCE_GS_ZGREATER, SCE_GS_PSMZ16S, SCE_GS_CLEAR);
    FlushCache(WRITEBACK_DCACHE);
    OkDefaultSysInit(SCR_WIDTH, SCR_HEIGHT, 16, 8);
    OkPrintSysInit(5, SCR_WIDTH, SCR_HEIGHT, 32, 12);
    return 0;
}

s32 abMenuMain() {
    static struct {
        char *str0;
        char *str1;
        s32 fmode;
        s32 smode;
    } MenuCont[4] = {
        { "Effect Tool", "_Effect Tool", 1, 0 },
        { "Sample",      "_Sample",      3, 0 },
        { "Sample",      "_Sample",      3, 0 },
        { "Sample",      "_Sample",      3, 0 }
    };
    s32 lp1;
    s32 sy;
    kPadDATA *kpd;
    s32 inter;
    s32 vs1;
	s32 vs2;
    
    sceGsSwapDBuffDc(&GameGbl.db, GameGbl.fr);
    GameGbl.fr++;
    sceGsSyncPath(0, 0);
    nkGetPad();
    kpd = &GameGbl.kpd[0];
    kpd->lvl = nkGetPlvl(0);
    kpd->trg = nkGetPtrg(0);
    kpd->rep = nkGetPrep(0);
    FlushCache(WRITEBACK_DCACHE);

    KL2_OK_PRINT((0, 10, 1, scr_p[0], "ABE MENU"));
    KL2_OK_PRINT((0, 23, 1, scr_p[0], "irqc=%d", SysGbl.irqc));
    for (sy = 6, lp1 = 0; lp1 < 4; sy++, lp1++) {
        KL2_OK_PRINT((0, 4, sy, scr_p[0], MenuCont[lp1].str0));
    }

    if (MenuGbl.mode == 0) {
        s32 vs1 = GameGbl.vision / 256;
        s32 vs2 = GameGbl.vision & 0xFF;
        
        // is this an error?
        if (pPAD_TRG_R1(kpd)) {
            MenuGbl.vscnt++;
            MenuGbl.vscnt %= 2;
        }
        if (pPAD_TRG_L1(kpd)) {
            MenuGbl.vscnt++;
            MenuGbl.vscnt %= 2;
        }

        if (pPAD_REP_RIGHT(kpd)) {
            switch (MenuGbl.vscnt) {
                case 0:
                    vs1++;
                    if (vs1 > 99) vs1 = 0;
                    break;
                case 1:
                    vs2++;
                    vs2 &= 0xFF;
                    break;
            }
        } else if (pPAD_REP_LEFT(kpd)) {
            switch (MenuGbl.vscnt) {
                case 0:
                    vs1--;
                    if (vs1 < 0) vs1 = 99;
                    break;
                case 1:
                    vs2 += 0xFF;
                    vs2 &= 0xFF;
                    break;
            }
        }
        
        GameGbl.vision = (vs1 << 8) + vs2;
    }

    if (SysGbl.irqc & 0x20 || MenuGbl.vscnt != 0 || kpd->lvl & (PAD_LEFT | PAD_RIGHT)) {
        KL2_OK_PRINT((0, 17, 6, scr_p[0], "%d", (GameGbl.vision / 0xA00) % 10));
        KL2_OK_PRINT((0, 18, 6, scr_p[0], "%d", (GameGbl.vision / 0x100) % 10));
    }
    if (SysGbl.irqc & 0x20 || MenuGbl.vscnt != 1 || kpd->lvl & (PAD_LEFT | PAD_RIGHT)) {
        KL2_OK_PRINT((0, 20, 6, scr_p[0], "%02x", GameGbl.vision % 0x100));
    }
    KL2_OK_PRINT((0, 19, 6, scr_p[0], "-"));
    KL2_OK_PRINT((0, 3, MenuGbl.mode + 6, scr_p[0], ">"));
    
    if (MenuGbl.mode > 0 && pPAD_TRG_UP(kpd)) {
        MenuGbl.mode--;
    } else if (MenuGbl.mode < 3 && pPAD_TRG_DOWN(kpd)) {
        MenuGbl.mode++;
    }
    
    if (pPAD_TRG_START(kpd) && MenuGbl.mode < 4) {
        SysGbl.fmode = MenuGbl.mode + 1;
        SysGbl.smode = 0;
    }
    if (pPAD_TRG_R2(kpd)) {
        SysGbl.nmode = 5;
        SysGbl.nsmode = 0;
    }
    if (pPAD_TRG_L2(kpd)) {
        SysGbl.nmode = 3;
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

s32 (*abMenuFuncTbl[])() = { abMenuInit, abMenuMain };