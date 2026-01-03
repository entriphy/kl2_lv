#include "harada/hrmenu.h"
#include "harada/hr_pall.h"
// this may need to be included
// #include "harada/hr_pflag.h"
#include "okanoyo/okmain.h"
#include "okanoyo/okprint.h"
#include "nakano/nkpad.h"

// IMPORTANT: build date :O
static char *hr_date = "Dec 13 2000";
static char *hr_time = "16:27:35";
static MENU_WORK MenuGbl;
#ifdef KL2_VER_RETAIL
static s8 D_3FA730;
#endif

static s32 hrMenuInit() {
    SysGbl.smode++;
    MenuGbl.mode = 0;
    MenuGbl.vision = 0;
    MenuGbl.flag = 0;
    MenuGbl.vscnt = 0;
    sceGsResetGraph(0, SCE_GS_INTERLACE, SCE_GS_NTSC, SCE_GS_FRAME);
    sceGsSetDefDBuffDc(&GameGbl.db, SCE_GS_PSMCT32, SCR_WIDTH, SCR_HEIGHT, SCE_GS_ZGREATER, SCE_GS_PSMZ24, SCE_GS_CLEAR);
    FlushCache(WRITEBACK_DCACHE);
    OkDefaultSysInit(SCR_WIDTH, SCR_HEIGHT, 16, 8);
    OkPrintSysInit(4, SCR_WIDTH, SCR_HEIGHT, 0x20, 12);
    hr_pt_fclear();
    hrpt_pack = (u32 *)-1;
    KL2_VER_RETAIL_ONLY(D_3FA730 = 1);
    // Return intentionally left blank
}

#define MENU_MAX KL2_VER_COND(4, 5)
// what the fuck https://decomp.me/scratch/Ao1RH
static s32 hrMenuMain() {
    static struct {
        u8 *str0;
        u8 *str1;
        s32 fmode;
        s32 smode;
    } MenuCont[MENU_MAX] = {
        { (u8 *)"MAP",  (u8 *)"_MAPVIEWER", 1, 0 },
        { (u8 *)"VU1V", (u8 *)"_TEST1",     1, 0 },
        { (u8 *)"PT",   (u8 *)"_TEST2",     2, 0 },
        { (u8 *)"VPO",  (u8 *)"_TEST3",     3, 0 },
#ifdef KL2_VER_RETAIL
        { (u8 *)"LANG", (u8 *)"_TEST4",     4, 0 }
#endif
    };

    s32 lp1;
    s32 sy;
    kPadDATA *kpd;
    s32 inter;
    s32 vs1;
    s32 vs2;
    u64 pmode; // erm, this should be s32

    sceGsSwapDBuffDc(&GameGbl.db, GameGbl.fr);
    GameGbl.fr++;
    sceGsSyncPath(0, 0);

    kpd = &GameGbl.kpd[0];
    nkGetPad();
    kpd->lvl = nkGetPlvl(0);
    kpd->trg = nkGetPtrg(0);
    kpd->rep = nkGetPrep(0);
    FlushCache(WRITEBACK_DCACHE);
    KL2_OK_PRINT((0, 10, 1, scr_p[0], "HARADA MENU"));
    KL2_OK_PRINT((0, 23, 1, scr_p[0], "irqc=%d", SysGbl.irqc));
    KL2_OK_PRINT((0, 10, 3, scr_p[0], "%s %s", hr_date, hr_time));

    sy = 6;
    for (lp1 = 0; lp1 < MENU_MAX; lp1++) {
        KL2_OK_PRINT((0, 4, sy, scr_p[0], (char *)MenuCont[lp1].str0));
        sy++;
    }

    if (MenuGbl.mode == 0) {
        vs1 = GameGbl.vision / 256;
        vs2 = GameGbl.vision & 0xFF;

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
                    if (vs1 > 99) {
                        vs1 = 0;
                    }
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
                    if (vs1 < 0) {
                        vs1 = 99;
                    }
                    break;
                case 1:
                    vs2 += 0xFF;
                    vs2 &= 0xFF;
                    break;
            }
        }
        GameGbl.vision = (vs1 << 8) + vs2;
    }

    // IMPORTANT: this forces SysGbl.irqc to be read, even on retail
    if (SysGbl.irqc & 0x20 || MenuGbl.vscnt != 0 || kpd->lvl & (PAD_LEFT | PAD_RIGHT)) {
        KL2_OK_PRINT((0, 11, 6, scr_p[0], "%d", (GameGbl.vision / 0xA00) % 10));
        KL2_OK_PRINT((0, 12, 6, scr_p[0], "%d", (GameGbl.vision / 0x100) % 10));
    }
    if (SysGbl.irqc & 0x20 || MenuGbl.vscnt != 1 || kpd->lvl & (PAD_LEFT | PAD_RIGHT)) {
        KL2_OK_PRINT((0, 14, 6, scr_p[0], "%02x", GameGbl.vision % 0x100));
    }
    KL2_OK_PRINT((0, 13, 6, scr_p[0], "-"));

    if (MenuGbl.mode == 1) {
        char *vu1v_name[3] = { "harada", "user 1", "user 2" };

        if (pPAD_REP_RIGHT(kpd)) {
            MenuGbl.vscnt++;
            if (MenuGbl.vscnt > 2) {
                MenuGbl.vscnt = 0;
            }
        } else if (pPAD_REP_LEFT(kpd)) {
            MenuGbl.vscnt--;
            if (MenuGbl.vscnt < 0) {
                MenuGbl.vscnt = 2;
            }
        }

        KL2_OK_PRINT((0, 13, MenuGbl.mode + 6, scr_p[0], "%s", vu1v_name[MenuGbl.vscnt]));
    }

    if (MenuGbl.mode == 2) {
        if (pPAD_REP_RIGHT(kpd)) {
            MenuGbl.vscnt++;
            if (MenuGbl.vscnt > 9) {
                MenuGbl.vscnt = 0;
            }
        } else if (pPAD_REP_LEFT(kpd)) {
            MenuGbl.vscnt--;
            if (MenuGbl.vscnt < 0) {
                MenuGbl.vscnt = 9;
            }
        }

#ifdef KL2_VER_RETAIL
        if (kpd->trg & (PAD_L1 | PAD_R1)) { // L1/R1
            D_3FA730 ^= 1;
        }
#endif

        KL2_OK_PRINT((0, 13, MenuGbl.mode + 6, scr_p[0], "%d", MenuGbl.vscnt));
        KL2_OK_PRINT((0, 17, MenuGbl.mode + 6, scr_p[0], "%f", 1.48f));
        KL2_OK_PRINT((0, 27, MenuGbl.mode + 6, scr_p[0], "take"));
    }
    KL2_OK_PRINT((0, 3, MenuGbl.mode + 6, scr_p[0], ">"));

#ifdef KL2_VER_RETAIL
    if (MenuGbl.mode == 4) {
        if (pPAD_REP_RIGHT(kpd)) {
            SysGbl.Language++;
            if (SysGbl.Language > 5) {
                SysGbl.Language = 1;
            }
        } else if (pPAD_REP_LEFT(kpd)) {
            SysGbl.Language--;
            if (SysGbl.Language < 1) {
                SysGbl.Language = 5;
            }
        }
    }

    {
        char name[4];
        switch (SysGbl.Language) {
            case 1:
                strcpy(name, "ENG");
                break;
            case 2:
                strcpy(name, "FRN");
                break;
            case 3:
                strcpy(name, "SPA");
                break;
            case 4:
                strcpy(name, "GET");
                break;
            case 5:
                strcpy(name, "ITA");
                break;
        }
    }
#endif

    if (MenuGbl.mode > 0 && pPAD_TRG_UP(kpd)) {
        MenuGbl.mode--;
        MenuGbl.vscnt = 0;
    } else if (MenuGbl.mode < MENU_MAX - 1 && pPAD_TRG_DOWN(kpd)) {
        MenuGbl.mode++;
        MenuGbl.vscnt = 0;
    }

    if (pPAD_TRG_START(kpd) && MenuGbl.mode < MENU_MAX) {
        SysGbl.fmode = MenuGbl.mode + 1;
        SysGbl.smode = 0;
        if (MenuGbl.mode == 2) {
            hr_pt_set(1, MenuGbl.vscnt, KL2_VER_COND(1, D_3FA730 + 1), 1);
            if (pPAD_LVL_CIRCLE(kpd)) {
                pmode = 1;
            } else if (pPAD_LVL_CROSS(kpd)) {
                pmode = 2;
            } else if (pPAD_LVL_SQUARE(kpd)) {
                pmode = 3;
            } else {
                u64 h = kpd->lvl;
                h /= 4;
                pmode = h & 4;
            }
            hr_pflag_theatar(hr_pflag_get_id(), pmode);
        }
    }

    if (pPAD_TRG_R2(kpd)) {
        SysGbl.nmode = 4;
        SysGbl.nsmode = 0;
    }
    if (pPAD_TRG_L2(kpd)) {
        SysGbl.nmode = 2;
        SysGbl.nsmode = 0;
    }

    sceGsSyncPath(0,0);
    OkPFontFlush(PAD_TRG_SELECT(GameGbl.kpd[1]));
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
    // Return intentionally left blank
}

s32 (*hrMenuFuncTbl[])() = { hrMenuInit, hrMenuMain };
