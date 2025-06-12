#include "hoshino/h_test.h"
#include "hoshino/h_gamesnd.h"
#include "hoshino/h_pad.h"
#include "hoshino/h_str.h"
#include "okanoyo/okmain.h"
#include "okanoyo/okprint.h"

#ifdef KL2_VER_TRIAL
static char *bgmdebug_str[] = {
    "BGM040",
    "BGM058",
    "BGM000",
    "BGM001",
    "BGM060",
    "BGM009",
    "BGM045",
    "BGM036"
};
#else
static char *bgmdebug_str[] = {
    "BGM000",
    "BGM001",
    "BGM002",
    "BGM003",
    "BGM004",
    "BGM005",
    "BGM006",
    "BGM007",
    "BGM008",
    "BGM009",
    "BGM010",
    "BGM011",
    "BGM012",
    "BGM071",
    "BGM013",
    "BGM014",
    "BGM015",
    "BGM016",
    "BGM017",
    "BGM018",
    "BGM019",
    "BGM020",
    "BGM021",
    "BGM022",
    "BGM078",
    "BGM023",
    "BGM077",
    "BGM024",
    "BGM025",
    "BGM026",
    "BGM027",
    "BGM028",
    "BGM029",
    "BGM030",
    "BGM031",
    "BGM032",
    "BGM033",
    "BGM034",
    "BGM035",
    "BGM036",
    "BGM037",
    "BGM038",
    "BGM039",
    "BGM040",
    "BGM062",
    "BGM041",
    "BGM042",
    "BGM043",
    "BGM044",
    "BGM045",
    "BGM046",
    "BGM047",
    "BGM048",
    "BGM050",
    "BGM052",
    "BGM053",
    "BGM054",
    "BGM060",
    "BGM055",
    "BGM056",
    "BGM057",
    "BGM058",
    "BGM059",
    "BGM070",
    "BGM061",
    "BGM075",
    "BGM076",
    "BGM063",
    "BGM064",
    "BGM065",
    "BGM066",
    "BGM067",
    "BGM068",
    "BGM069",
    "BGM072",
    "BGM073",
    "BGM074",
    "BGM079",
    "BGM080",
    "BGM081",
    "BGM082",
    "BGM083",
    "BGM049",
    "BGM084",
    "BGM085",
    "BGM086"
};
#endif
#ifdef KL2_VER_RETAIL
static f32 hTestBGM_3FAB00 = 0.0f;
s32 TestSkip = 0;
#endif
s32 TestMode = 0;
static s32 templist[] = {
    24, 0,  1,  2,
    3,  4,  5,  6,
    7,  8,  9,  10,
    11, 12, 13, 14,
    15, 16, 17, 18,
    19, 20, 21, 22,
    23, 0
};

void hTestInit() {
    s32 ret;

    SysGbl.smode++;
    memoryStageFormat();
    TestWork = (s32)getBuff(1, 0x200000, NULL, &ret);
    hSeInitGrp(0);
    KL2_VER_RETAIL_ONLY(hPadInit());
    hSndSetMVol(1.0f);
    hPptReset();
    hPptSetList(templist);
}

void hTestBGM() {
    hPAD_DATA pad;
    static s32 cur_y = 0;
    static s32 no = 0;
    static s32 ch = 0;
    static s32 frame = 0;
    static s32 frame2 = 0;
    static s32 curtbl[] = { 3, 4, 5, 7, 8, 11, 12, 13 };
    static char str[256];

    hPadGet(&pad, 0);
    KL2_OK_PRINT((0, 0, curtbl[cur_y], scr_p[0], "->"));
    KL2_OK_PRINT((0, 2, 0, scr_p[0], "----[SOUND TEST]--[BGM]----"));
    KL2_OK_PRINT((0, 2, 2, scr_p[0], " NAME = %s", bgmdebug_str[no]));
    KL2_OK_PRINT((0, 2, 3, scr_p[0], " NO   = %d / %d", no, 7));
    KL2_OK_PRINT((0, 2, 4, scr_p[0], " CH   = %d", ch));
    KL2_OK_PRINT((0, 2, 5, scr_p[0], " VOL  = %d", (s32)(bD->bgmVol * 127.0f + 0.5f)));

    KL2_OK_PRINT((0, 2, 6, scr_p[0], " FADE TIME"));
    sprintf(str, "   IN = %2.2f", frame / 60.0f);
    KL2_OK_PRINT((0, 2, 7, scr_p[0], "%s", str));
    sprintf(str, "  OUT = %2.2f", frame2 / 60.0f);
    KL2_OK_PRINT((0, 2, 8, scr_p[0], "%s", str));

    KL2_OK_PRINT((0, 2, 10, scr_p[0], "[MASTER VOL]"));
    KL2_OK_PRINT((0, 2, 11, scr_p[0], "  BGM = %d", (s32)(sD->bgmMVol * 127.0f + 0.5f)));
    KL2_OK_PRINT((0, 2, 12, scr_p[0], "  SE  = %d", (s32)(sD->seMVol * 127.0f + 0.5f)));
    KL2_OK_PRINT((0, 2, 13, scr_p[0], "  PPT = %d", (s32)(sD->pptMVol * 127.0f + 0.5f)));
    KL2_VER_RETAIL_ONLY(hTestBGM_3FAB00 = TestSkip / 25200.0f);

    if (pad.on & 0x40) {
        hBgmFadeIn(no, ch, frame);
    }
    if (pad.on & 0x20) {
        hBgmFadeOut(frame2);
    }
    if (pad.on & 0x80) {
        KL2_VER_COND(hBgmFadeNext(frame2, no, ch, frame, bD->bgmVol), hBgmChangeChX(ch));
    }
    if (pad.on & 0x10) {
        KL2_VER_COND(hBgmReset(), hBgmPlayLast10sec(no, ch));
    }
    if (pad.l & 0x800) {
        KL2_VER_COND(hBgmPause(), hBgmFadeNext(frame2, no, ch, frame, bD->bgmVol));
    }

    if (pad.on & 0x1000) {
        cur_y--;
        if (cur_y < 0) {
            cur_y = KL2_VER_COND(7, 8);
        }
    }
    if (pad.on & 0x4000) {
        cur_y++;
        if (cur_y > KL2_VER_COND(7, 8)) {
            cur_y = 0;
        }
    }

    switch (cur_y) {
        case 0:
            if (pad.on & 0x8000) {
                if (--no < 0) {
                    no = ARR_COUNT_SIGNED(bgmdebug_str) - 1;
                }
                ch = 0;
            }
            if (pad.on & 0x2000) {
                if (++no > ARR_COUNT_SIGNED(bgmdebug_str) - 1) {
                    no = 0;
                }
                ch = 0;
            }
            break;
        case 1:
            if (pad.on & 0x8000) {
                if (--ch < 0) {
                    ch = hBgmGetMaxCh(no) - 1;
                }

            }
            if (pad.on & 0x2000) {
                if (++ch >= hBgmGetMaxCh(no)) {
                    ch = 0;
                }
            }
            break;
        case 2:
            if (pad.l & 0x8000) {
                bD->bgmVol -= 0.002f;
                if (bD->bgmVol < 0.0f) {
                    bD->bgmVol = 0.0f;
                }
            }
            if (pad.l & 0x2000) {
                bD->bgmVol += 0.002f;
                if (bD->bgmVol > 1.0f) {
                    bD->bgmVol = 1.0f;
                }
            }
            break;
        case 3:
            if (pad.l & 0x8000) {
                if (--frame < 0) {
                    frame = 0;
                }
            }
            if (pad.l & 0x2000) {
                frame++;
            }
            break;
        case 4:
            if (pad.l & 0x8000) {
                if (--frame2 < 0) {
                    frame2 = 0;
                }
            }
            if (pad.l & 0x2000)
                frame2++;
            break;
#ifdef KL2_VER_RETAIL
        case 5:
            if ((pad.r2 | pad.on) & 0x8000) {
                TestSkip -= 0x100;
                if (TestSkip < 0) {
                    TestSkip = 0;
                }
            }
            if ((pad.r2 | pad.on) & 0x2000) {
                TestSkip += 0x100;
            }
            if ((pad.r2 | pad.on) & 0x4) {
                TestSkip -= 0x3E800;
                if (TestSkip < 0) {
                    TestSkip = 0;
                }
            }
            if ((pad.r2 | pad.on) & 0x8) {
                TestSkip += 0x3E800;
            }
            break;
#endif
        case KL2_VER_COND(5, 6):
            if (pad.l & 0x8000) {
                sD->bgmMVol -= 0.002f;
                if (sD->bgmMVol < 0.0f) {
                    sD->bgmMVol = 0.0f;
                }
            }
            if (pad.l & 0x2000) {
                sD->bgmMVol += 0.002f;
                if (sD->bgmMVol > 1.0f) {
                    sD->bgmMVol = 1.0f;
                }
            }
            break;
        case KL2_VER_COND(6, 7):
            if (pad.l & 0x8000) {
                sD->seMVol -= 0.002f;
                if (sD->seMVol < 0.0f) {
                    sD->seMVol = 0.0f;
                }
            }
            if (pad.l & 0x2000) {
                sD->seMVol += 0.002f;
                if (sD->seMVol > 1.0f) {
                    sD->seMVol = 1.0f;
                }
            }
            break;
        case KL2_VER_COND(7, 8):
            if (pad.l & 0x8000) {
                sD->pptMVol -= 0.002f;
                if (sD->pptMVol < 0.0f) {
                    sD->pptMVol = 0.0f;
                }
            }
            if (pad.l & 0x2000) {
                sD->pptMVol += 0.002f;
                if (sD->pptMVol > 1.0f) {
                    sD->pptMVol = 1.0f;
                }
            }
            break;
    }
}

void hTestPPT() {
#ifdef KL2_VER_RETAIL
    static s32 id;
#endif
    hPAD_DATA pad;
    

    hPadGet(&pad, 0);
    KL2_OK_PRINT((0, 1, 0, scr_p[0], "----[SOUND TEST]--[PPT]----"));
    KL2_OK_PRINT((0, 1, 2, scr_p[0], " PPT VOL = %d", (s32)(sD->pptMVol * 127.0f + 0.5f)));

    if (pad.on & 0x40) {
        KL2_VER_COND(hPptReq(), id = hPptReq());
    }
    if (pad.on & 0x20) {
        hPptReset();
    }
    if (pad.on & 0x80) {
        KL2_VER_COND(hPptPause(), hPptStop(id));
    }
    if (pad.on & 0x10) {
        hPptSetList(templist);
    }

    if (pad.l & 0x1000) {
        sD->pptMVol -= 0.002f;
        if (sD->pptMVol < 0.0f) {
            sD->pptMVol = 0.0f;
        }
    }
    if (pad.l & 0x4000) {
        sD->pptMVol += 0.002f;
        if (sD->pptMVol > 1.0f) {
            sD->pptMVol = 1.0f;
        }
    }
}

void hTestAC3() {
#ifdef KL2_VER_RETAIL
    static s32 D_3FAB28 = 0;
#endif
    hPAD_DATA pad;

    KL2_VER_RETAIL_ONLY(sD->Stereo = SND_MODE_5P1CH);
    hPadGet(&pad, 0);
    KL2_OK_PRINT((0, 1, 0, scr_p[0], "----[SOUND TEST]--[AC3]----"));
    KL2_OK_PRINT((0, 1, 2, scr_p[0], " DON NOT TOUCH !  HOSHINO ONLY !!"));

#ifdef KL2_VER_RETAIL
    if (pad.on & 0x40) {
        if (D_3FAB28 == 4) {
            hStr_0016f6e8();
        } else {
            if (hStr_0016f680() == 0) {
                hStr_0016f6a8(D_3FAB28);
            }
        }
    }
    if (pad.on & 0x1000) {
        D_3FAB28--;
    }
    if (pad.on & 0x4000) {
        D_3FAB28++;
    }

    if (D_3FAB28 < 0) {
        D_3FAB28 = 4;
    }
    if (D_3FAB28 > 4) {
        D_3FAB28 = 0;
    }
#endif
}

void hTestConfig() {
    hPAD_DATA pad;
    static f32 mvol = 1.0f;
    static s32 cur_y = 0;
    static s32 cur_tbl[] = { 2, 5, 6, 7, 8 };
    static char *effmodename[] = {
        "SD_REV_MODE_OFF",
        "SD_REV_MODE_ROOM",
        "SD_REV_MODE_STUDIO_A",
        "SD_REV_MODE_STUDIO_B",
        "SD_REV_MODE_STUDIO_C",
        "SD_REV_MODE_HALL",
        "SD_REV_MODE_SPACE",
        "SD_REV_MODE_ECHO",
        "SD_REV_MODE_DELAY",
        "SD_REV_MODE_PIPE"
    };

    hPadGet(&pad, 0);
    KL2_OK_PRINT((0, 1, 0, scr_p[0], "----[SOUND TEST]--[CONFIG]----"));
    KL2_OK_PRINT((0, 2, 2, scr_p[0], " MVOL = %d / 100", (s32)(mvol * 100.0f)));
    KL2_OK_PRINT((0, 2, 4, scr_p[0], " [EFFECT]"));
    KL2_OK_PRINT((0, 2, 5, scr_p[0], "   MODE  = %d %s", sD->effMode, effmodename[sD->effMode]));
    KL2_OK_PRINT((0, 2, 6, scr_p[0], "   DEPTH = %d", sD->effDepth));
    KL2_OK_PRINT((0, 2, 7, scr_p[0], "   DELAY = %d", sD->effDelay));
    KL2_OK_PRINT((0, 2, 8, scr_p[0], "   FEED  = %d", sD->effFeed));
    KL2_OK_PRINT((0, 0, cur_tbl[cur_y], scr_p[0], "->"));

    if (pad.on & 0x1000) {
        if (--cur_y < 0) {
            cur_y = 4;
        }
    }
    if (pad.on & 0x4000) {
        if (++cur_y > 4) {
            cur_y = 0;
        }
    }

    switch (cur_y) {
        case 0:
            if (pad.l & 0x8000) {
                mvol -= 0.005f;
                if (mvol < 0.0f) {
                    mvol = 0.0f;
                }
                hSndSetMVol(mvol);
            }
            if (pad.l & 0x2000) {
                mvol += 0.005f;
                if (mvol > 1.0f) {
                    mvol = 1.0f;
                }
                hSndSetMVol(mvol);
            }
            break;
        case 1:
            if (pad.on & 0x8000) {
                if (--sD->effMode < 0) {
                    sD->effMode = 9;
                }
            }
            if (pad.on & 0x2000) {
                if (++sD->effMode > 9) {
                    sD->effMode = 0;
                }
            }
            break;
        case 2:
            if (pad.l & 0x8000) {
                sD->effDepth -= 0x100;
                if (sD->effDepth < 0) {
                    sD->effDepth = 0;
                }
            }
            if (pad.l & 0x2000) {
                sD->effDepth += 0x100;
                if (sD->effDepth > 0x7FFF) {
                    sD->effDepth = 0x7FFF;

                }
            }
            break;
        case 3:
            if (pad.l & 0x8000) {
                if (--sD->effDelay < 0) {
                    sD->effDelay = 0;
                }
            }
            if (pad.l & 0x2000) {
                if (++sD->effDelay > 0x7F) {
                    sD->effDelay = 0x7F;
                }
            }
            break;
        case 4:
            if (pad.l & 0x8000) {
                if (--sD->effFeed < 0) {
                    sD->effFeed = 0;
                }
            }
            if (pad.l & 0x2000) {
                if (++sD->effFeed > 0x7F) {
                    sD->effFeed = 0x7F;
                }
            }
            break;
    }

    if (pad.l & 0x40) {
        hSndPkEffect();
    }
    if (pad.on & 0x800) {
        hSndPkEffect();
    }
}

#ifdef KL2_VER_RETAIL
void hTestMov() {
    hPAD_DATA pad;

    hPadGet(&pad, 0);
    if (func_002DA2B0() == -1) {
        nkGsInitFrm();
        OkPrintDataLoad();
        TestMode = 0;
    }
}
#endif

void hTestMain() {
    hPAD_DATA pad;

    hPadRead();
    hPadGet(&pad, 0);

    if (pad.on & 1) {
        if (--TestMode < 0) {
            TestMode = KL2_VER_COND(2, 3);
        }
    }
    if (pad.on & 2) {
        if (++TestMode > KL2_VER_COND(2, 3)) {
            TestMode = 0;
        }
    }

#ifdef KL2_VER_TRIAL
    switch (TestMode) {
        case 0:
            hTestBGM();
            break;
        case 1:
            hTestPPT();
            break;
        case 2:
            hTestConfig();
            break;
        case 3:
            hTestSE();
            break;
    }
#else
    switch (TestMode) {
        case 0:
            hTestAC3();
            break;
        case 1:
            hTestMov();
            break;
        case 2:
            hTestConfig();
            break;
        case 3:
            hTestBGM();
            break;
        case 4:
            hTestSE();
            break;
    }
#endif

    if (pad.on & 0x100) {
        SysGbl.fmode = 0;
        SysGbl.smode = 1;
        freeBuff(1, 0x200000, NULL);
    }
}

s32 TestWork = 0;
s32 (*hTestFuncTbl[])() = { // don't ask
    (s32 (*)())hTestInit,
    (s32 (*)())hTestMain,
};