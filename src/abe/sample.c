#include "abe/sample.h"
#include "abe/ab_objtest.h"
#include "harada/hr_main.h"
#include "nakano/camera.h"
#include "nakano/drawof.h"
#include "nakano/game.h"
#include "nakano/main.h"
#include "nakano/objfunc.h"
#include "nakano/dma.h"
#include "nakano/wmeter.h"
#include "okanoyo/okmain.h"
#include "okanoyo/okprint.h"
#include "nakano/nkpad.h"
#include <libdev.h>

static s32 SampleInit() {
    sceVu0FVECTOR vf;
    vpmINFO *vpmi;
    u32 i;

    vpmi = &VpmInfo;
    SysGbl.objwork = malloc(sizeof(OBJWORK) * 128);
    SysGbl.n_objw = 128;
    InitAllObjWork(SysGbl.objwork, 128);
    sceGsResetPath();
    sceDevGifReset();
    sceDevVif1Reset();
    sceDevVu1Reset();
    sceDevVif0Reset();
    sceDevVu0Reset();
    sceGsResetGraph(0, SCE_GS_INTERLACE, SCE_GS_NTSC, SCE_GS_FRAME);
    sceGsSetDefDBuffDc(&GameGbl.db, 0, SCR_WIDTH, SCR_HEIGHT, 3, 0x3a, 1);
    FlushCache(0);
    nkInitDma();
    _nkGetMapBuf();
    nkMapFileRead();
    draw_id = 0;
    vpmi->block_list[0] = 0;
    for (i = 0; i < 2048; i++) {
        vpmi->block_list[i + 1] = 0;
    }
    nkPathReset();
    nkInitAtrMain();
    sceGsSyncPath(0,0);
    nkDebFlush();
    nkPathFlush();
    MapConfFileRead();
    OkSetIDprofile();
    OkDefaultSysInit(SCR_WIDTH, SCR_HEIGHT, 12, 6);
    OkPrintSysInit(1, SCR_WIDTH, SCR_HEIGHT, 12, 6);
    vf[0] = 100.0f;
    vf[1] = 100.0f;
    vf[2] = 0.0f;
    abSetObjTest(vf);
    CamInit(&GameGbl.cam);
    SysGbl.smode++;

    if (fontDispID == 5) {
        KL2_DEBUG_PRINT(("Abe/Sample Init\n"));
    }

    return 0;
}

static s32 SampleMain() {
    s32 inter;
	kPadDATA *kpd0;
	kPadDATA *kpd1;
	s32 lp;

    kpd0 = &GameGbl.kpd[0];
    nkGetPad();
    kpd0->lvl = nkGetPlvl(0);
    kpd0->trg = nkGetPtrg(0);
    kpd0->rep = nkGetPrep(0);

    kpd1 = &GameGbl.kpd[1];
    kpd1->lvl = nkGetPlvl(1);
    kpd1->trg = nkGetPtrg(1);
    kpd1->rep = nkGetPrep(1);

    nkPathReset();
    for (lp = 0; lp < 100000; lp++) {
        
    }

    nkSetMeter();
    ObjFunc(SysGbl.objwork);
    for (lp = 0; lp < 100000; lp++) {
        
    }

    CamDebug(&GameGbl.cam);
    CamCalMatrix(&GameGbl.cam);
    DrawObjFunc(SysGbl.objwork);
    MapVDrawBG();
    nkDrawMap();
    sceGsSyncPath(0, 0);

    KL2_OK_PRINT((5, 28, 1, scr_p[5], "IRQC= %d", SysGbl.irqc));
    KL2_OK_PRINT((5, 2, 1, scr_p[5], "ABE Sample Program"));
    KL2_OK_PRINT((5, 10, 30, scr_p[5], "Push <SELECT> button to Exit"));

    nkSetMeter();
    nkDrawWorkMeter();
    OkPFontFlush(pPAD_TRG_SQUARE(kpd0) && pPAD_LVL_CIRCLE(kpd0));
    inter = sceGsSyncV(0) ^ 1;
    if ((GameGbl.fr & 1) != 0) {
        sceGsSetHalfOffset(&GameGbl.db.draw11, 0x800, 0x800, inter);
        sceGsSetHalfOffset2(&GameGbl.db.draw12, 0x800, 0x800, inter);
    } else {
        sceGsSetHalfOffset(&GameGbl.db.draw01, 0x800, 0x800, inter);
        sceGsSetHalfOffset2(&GameGbl.db.draw02, 0x800, 0x800, inter);
    }
    sceGsSwapDBuffDc(&GameGbl.db, GameGbl.fr);
    GameGbl.fr++;
    nkResetMeter();
    FlushCache(WRITEBACK_DCACHE);
    nkPathFlush();
    if (pPAD_TRG_SELECT(kpd0)) {
        SysGbl.fmode = 0;
        SysGbl.smode = 0;
    }
    
    return 0;
}

s32 (*abSampleFuncTbl[])() = { SampleInit, SampleMain };
