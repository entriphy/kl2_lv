#include "kazuya/sample.h"
#include "kazuya/cvar.h"
#include "nakano/camera.h"
#include "nakano/dma.h"
#include "nakano/drawof.h"
#include "nakano/game.h"
#include "nakano/main.h"
#include "nakano/nkpad.h"
#include "nakano/objfunc.h"
#include "nakano/wmeter.h"
#include "okanoyo/okio.h"
#include "okanoyo/okmain.h"
#include "okanoyo/okprint.h"
#include "take/sfxbios.h"
#include <libdev.h>

static s32 SampleInit() {
    sceVu0FVECTOR vf;

    memoryStageFormat();
    memoryAreaptrSet();
    memoryAreaFormat();
    SysGbl.objwork = ObjWorkBuff;
    SysGbl.n_objw = 128;
    InitAllObjWork(ObjWorkBuff, 128);
    sceGsResetPath();
    sceDevGifReset();
    sceDevVif1Reset();
    sceDevVu1Reset();
    sceDevVif0Reset();
    sceDevVu0Reset();
    sceGsResetGraph(0, SCE_GS_INTERLACE, SCE_GS_NTSC, SCE_GS_FRAME);
    sceGsSetDefDBuffDc(&GameGbl.db, SCE_GS_PSMCT32, SCR_WIDTH, SCR_HEIGHT, SCE_GS_ZGREATER, SCE_GS_PSMZ16S, SCE_GS_CLEAR);
    FlushCache(0);
    nkInitDma();
    OkSetIDprofile();
    OkDefaultSysInit(SCR_WIDTH, SCR_HEIGHT, 12, 6);
    OkPrintSysInit(8, SCR_WIDTH, SCR_HEIGHT, 12, 6);
    SfxSystemInit((u32 *)PsfxWorkBuff);
    CamInit(&GameGbl.cam);
    SysGbl.smode++;
    return 0;
}

static s32 SampleMain() {
    s32 inter;

    kpd0 = &GameGbl.kpd[0];
    nkGetPad();
    kpd0->lvl = nkGetPlvl(0);
    kpd0->trg = nkGetPtrg(0);
    kpd0->rep = nkGetPrep(0);

    kpd1 = &GameGbl.kpd[1];
    kpd1->lvl = nkGetPlvl(1);
    kpd1->trg = nkGetPtrg(1);
    kpd1->rep = nkGetPrep(1);
    nkSetMeter();
    SortObjWork(SysGbl.objwork, SysGbl.n_objw);
    ObjFunc(SysGbl.objwork);
    CamDebug(&GameGbl.cam);
    CamCalMatrix(&GameGbl.cam);
    DrawObjFunc(SysGbl.objwork);
    sceGsSyncPath(0, 0);
    KL2_OK_PRINT((8, 28, 1, scr_p[8], "IRQC= %d", SysGbl.irqc));
    KL2_OK_PRINT((8, 2, 1, scr_p[8], "Kazuya Sample Program"));
    KL2_OK_PRINT((8, 10, 30, scr_p[8], "Push <SELECT> button to Exit"));
    OkPFontFlush(pPAD_TRG_SQUARE(kpd0) && pPAD_LVL_CIRCLE(kpd0));
    inter = sceGsSyncV(0) ^ 1;
    if (GameGbl.fr & 1) {
        sceGsSetHalfOffset(&GameGbl.db.draw11, 0x800, 0x800, inter);
        sceGsSetHalfOffset2(&GameGbl.db.draw12, 0x800, 0x800, inter);
    } else {
        sceGsSetHalfOffset(&GameGbl.db.draw01, 0x800, 0x800, inter);
        sceGsSetHalfOffset2(&GameGbl.db.draw02, 0x800, 0x800, inter);
    }
    sceGsSwapDBuffDc(&GameGbl.db, GameGbl.fr);
    GameGbl.fr++;
    if (pPAD_TRG_SELECT(kpd0)) {
        SysGbl.fmode = 0;
        SysGbl.smode = 0;
    }

    return 0;
}

s32 (*kzSampleFuncTbl[])() = { SampleInit, SampleMain };