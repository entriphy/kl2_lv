#include "hoshino/h_test_se.h"
#include "hoshino/h_pad.h"
#include "hoshino/h_sound.h"
#include "hoshino/h_test.h"
#include "hoshino/h_util.h"
#include "okanoyo/okmain.h"
#include "okanoyo/okprint.h"

static char *bankname[] = {
    "main",
    "st01",
    "st02",
    "st03",
    "st04",
    "st05",
    "st06",
    "st07",
    "st08",
    "st09",
    "st10",
    "st11",
    "st12",
    "st13",
    "st14",
    "st15",
    "st16",
    "st17",
    "st18",
    "st19",
    "st20",
    "st21",
    "st22",
    "st23",
    "st24",
    "st25",
    "st26",
    "st27",
    "st28",
    "st29",
    "st30",
    "st31",
    "st32",
    "st33",
    "st34",
    "st35",
    "st36",
    "st37",
    "st38",
    "st39",
    "st40",
    "st41",
    "st42",
    "st43",
    "st44",
    "st45",
    "st46",
    "st47",
    "st48",
    "st49"
};
static SEINFO *SEinfo;
static s32 bank;
static s32 bank0;
static s32 vag;
static s32 vagmax;

s32 TestKeyon(s32 prog, s32 splt, s32 eff) {
    hSndPkKeyOn(0, eff, bank0 != 0, prog, splt, sD->seMVol, sD->seMVol);
    KL2_DEBUG_PRINT(("bank=%d prog=%d splt=%d\n", bank0, prog, splt));
}

#ifdef KL2_VER_RETAIL
s32 TestKeyonInv(s32 prog, s32 splt, s32 eff) {
    hSndPkKeyOn(0, eff, bank0 != 0, prog, splt, sD->seMVol, -sD->seMVol);
}
#endif

void hTestSEBankSet() {
    char temp[256];

    if (bank != 0) {
        GameGbl.vision = bank << 8;
        hSndBankSetStage();
        if (!sD->stageBank) {
            return;
        }
    }

    bank0 = bank;
    sprintf(temp, "host0:../../sdat/%sbank.ifo", bankname[bank]);
    hFileLoad(temp, TestWork);
    SEinfo = (SEINFO *)(TestWork + 4);
    vagmax = *(s32 *)TestWork;
    vag = 0;
}

void hTestSE() {
    hPAD_DATA pad;

    hPadGet(&pad, 0);

    KL2_OK_PRINT((0, 1, 0, scr_p[0], "----[SOUND TEST]--[SE]----");)
    KL2_OK_PRINT((0, 1, 2, scr_p[0], "[BANK]"));
    KL2_OK_PRINT((0, 1, 3, scr_p[0], "  CUR  = %d [%s]", bank0, bankname[bank0]));
    KL2_OK_PRINT((0, 1, 4, scr_p[0], "  NO   = %d / %d", bank, 49));
    KL2_OK_PRINT((0, 1, 5, scr_p[0], "  FILE = %s", bankname[bank]));
    
    KL2_OK_PRINT((0, 1, 7,  scr_p[0], "[VAG]"));
    KL2_OK_PRINT((0, 1, 8,  scr_p[0], "  NAME = %s", SEinfo[vag].name));
    KL2_OK_PRINT((0, 1, 9,  scr_p[0], "  NO   = %d / %d", vag, vagmax - 1));
    KL2_OK_PRINT((0, 1, 10, scr_p[0], "  PROG = %d", SEinfo[vag].prog));
    KL2_OK_PRINT((0, 1, 11, scr_p[0], "  SPLT = %d", SEinfo[vag].splt));

    if (pad.on & 0x40) {
        TestKeyon(SEinfo[vag].prog, SEinfo[vag].splt, 1);
    }
    if (pad.on & 0x10) {
        TestKeyon(SEinfo[vag].prog, SEinfo[vag].splt, 2);
    }
    if (pad.on & 0x80) {
        TestKeyon(SEinfo[vag].prog, SEinfo[vag].splt, 3);
    }
    if (pad.on & 0x20) {
        hSndPkKeyOff(0);
    }

    if (KL2_VER_COND(pad.on, (pad.r2 | pad.on)) & 0x1000) {
        if (--vag < 0) {
            vag = vagmax - 1;
        }
    }
    if (KL2_VER_COND(pad.on, (pad.r2 | pad.on)) & 0x4000) {
        if (++vag >= vagmax) {
            vag = 0;
        }
    }
    if (KL2_VER_COND(pad.on, (pad.r2 | pad.on)) & 0x8000) {
        if (--bank < 0) {
            bank = 49;
        }
    }
    if (KL2_VER_COND(pad.on, (pad.r2 | pad.on)) & 0x2000) {
        if (++bank > 49) {
            bank = 0;
        }
    }

    if (pad.on & 0x800) {
        hTestSEBankSet();
    }
}

void hTestSEInit() {
    KL2_DEBUG_PRINT(("hTestSEInit ...\n"));
    bank = 0;
    hTestSEBankSet();
    KL2_DEBUG_PRINT(("hTestSEInit ... done\n"));
}