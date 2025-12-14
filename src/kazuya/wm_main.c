#include "kazuya/wm_main.h"
#include "harada/hr_mapdr.h"
#include "harada/hr_mapv.h"
#include "kazuya/bios.h"
#include "kazuya/cvar.h"
#include "kazuya/obj_klo.h"
#include "kazuya/sinit.h"
#include "kazuya/td_job.h"
#include "kazuya/td_sys.h"
#include "kazuya/wm_job.h"
#include "nakano/camera.h"
#include "nakano/dma.h"
#include "nakano/game.h"
#include "nakano/main.h"
#include "nakano/nkpad.h"
#include "nakano/objfunc.h"
#include "nakano/route.h"
#include "nakano/readfile.h"
#include "nakano/wmeter.h"
#include "okanoyo/okio.h"
#include "okanoyo/okmain.h"
#include "okanoyo/okprint.h"
#include "take/sfxbios.h"
#include <libgraph.h>

// TODO: delete
extern u32 hr_vu1m_iv __attribute__((section(".vudata")));

void kzWM_Set_Path(s32 type, char *path) {
    sprintf(path, "host0:./dat/st01/");
    switch (type) {
        case 0:
            strcat(path, "map0100.gms");
            break;
        case 1:
            strcat(path, "map0100.vpm");
            break;
        case 2:
            strcat(path, "map0100.rt");
            break;
    }
}

void kzWM_Read_Data() {
    vpmINFO *vpmi = &VpmInfo;
    char path[256];
    u32 *buf;
    s32 size;

    kzWM_Set_Path(0, path);
    buf = getBuff(0, 0, path, &size);
    if ((s32)buf != -1) {
        if (size != -1) {
            nkLoadGms((qword *)buf);
            sceGsSyncPath(0, 0);
        }
        freeBuff(0, 0, path);
    }
    
    kzWM_Set_Path(1, path);
    read_file(path, vpmi->data_buff);
    DecodeVpm((u32 *)vpmi->data_buff);
    vpmi->vpm_data_top = (u32 *)vpmi->data_buff;

    kzWM_Set_Path(2, path);
    buf = getBuff(0, 0, path, &size);
    if ((s32)buf != -1 && size != -1) {
        InitMichi(buf);
    }

    FlushCache(WRITEBACK_DCACHE);
}

void kzWM_Set_Block_List() {
	vpmINFO *vpmi = &VpmInfo;
	u32 *list = &vpmi->block_list[1];
	u32 i;

    for (i = 0; i < 16; i++) {
        *list++ = i;
    }
    vpmi->block_list[0] = i;
}

void kzWM_Add_VPM_Packet() {
	vpmINFO *vpmi = &VpmInfo;
	u32 i;
	u32 nblock = vpmi->block_list[0];

    for (i = 0; i < nblock; i++) {
        nkAddRef(vpmi->block_head_ptr + vpmi->block_list[i + 1] * 2);
    }
}

void kzWM_Init_VpmModel() {
	vpmINFO *vpmi = &VpmInfo;
	u32 i;

    vpmi->block_list[0] = 0;
    for (i = 0; i < 2048; i++) {
        vpmi->block_list[i + 1] = 0;
    }
    vpmi->fog_near = 20000;
    vpmi->fog_far = 200000;
    vpmi->fog_col[0] = vpmi->fog_col[1] = vpmi->fog_col[2] = 0;
    nkPathReset();
    hrInitAtrMain();
    nkP1Flush(p1_ot);
}

void kzWM_Draw_VpmModel() {
    vpmINFO *vpmi = &VpmInfo;

    kzWM_Set_Block_List();
    FlushCache(0);
    kz_Set_FogDist(vpmi->fog_near, vpmi->fog_far);
    kz_Set_FogCol(vpmi->fog_col);
    nkMakeUnpackVif1(&p1_packet, GameGbl.wsm, 0x390, 4);
    nkAddRef(&hr_vu1m_iv);
    hrInitAtrVu1mIv(
        SCE_GIF_SET_TAG(1, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 10),
        (u64)SCE_GS_PRIM | (u64)SCE_GS_RGBAQ << 4 | \
            (u64)SCE_GS_ST << 8  | (u64)SCE_GS_XYZF2 << 12 | \
            (u64)SCE_GS_ST << 16 | (u64)SCE_GS_XYZF2 << 20 | \
            (u64)SCE_GS_ST << 24 | (u64)SCE_GS_XYZF2 << 28 | \
            (u64)SCE_GS_ST << 32 | (u64)SCE_GS_XYZF2 << 36,
        6,
        &hrmapst
    );
    kzWM_Add_VPM_Packet();
    FlushCache(WRITEBACK_DCACHE);
    nkP1Flush(p1_ot);
}

static s32 kzWM_Init() {
    nkInitPS2();
    hr_okmem_reset();
    DebmemFormat(8);
    hrGetMapBuf();
    hr_scrst_init(&hrmapst);
    sceGsResetGraph(0, SCE_GS_INTERLACE, SCE_GS_NTSC, SCE_GS_FRAME);
    sceGsSetDefDBuffDc(&GameGbl.db, SCE_GS_PSMCT32, SCR_WIDTH, SCR_HEIGHT, SCE_GS_ZGREATER, SCE_GS_PSMZ16S, SCE_GS_CLEAR);
    FlushCache(WRITEBACK_DCACHE);
    InitAllObjWork(SysGbl.objwork, SysGbl.n_objw);
    hr_nak_dummyVK();
    OkSetIDprofile();
    OkDefaultSysInit(SCR_WIDTH, SCR_HEIGHT, 12, 6);
    OkPrintSysInit(8, SCR_WIDTH, SCR_HEIGHT, 12, 6);
    SfxSystemInit((u32 *)PsfxWorkBuff);
    CamInit(&GameGbl.cam);
    kzWM_Read_Data();
    kzWM_Init_VpmModel();
    sceGsSyncPath(0,0);
    nkPathFlush();
    GameGbl.fr = 0;
    SysGbl.smode++;
    GameGbl.vision = KL2_VISION(30, 0);
    kzStageInit0();
    kzStageInit1();
    td_jobcnt_next0 = TD_JOB_TTL_MENU;
    kzTD_Change_Job();
    kzOKL_Setup();
    return 0;
}

static s32 kzWM_Main() {
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
    FlushCache(WRITEBACK_DCACHE);
    nkPathReset();
    FlushCache(WRITEBACK_DCACHE);
    kzWorldMapJobTbl[wm_jobcnt]();
    sceGsSyncPath(0, 0);
    kzTwoDmsnJobTbl[td_jobcnt]();
    kzTD_Draw_Fade();
    
    KL2_OK_PRINT((8, 28, 1, scr_p[8], "IRQC= %d", SysGbl.irqc));
    KL2_OK_PRINT((8, 2, 1, scr_p[8], "Kazuya World Map"));
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
    sceGsSyncPath(0, 0);
    nkPathFlush();
    if (pPAD_TRG_SELECT(kpd0)) {
        SysGbl.fmode = 0;
        SysGbl.smode = 0;
    }

    return 0;
}

s32 (*kzWorldMapFuncTbl[])() = { kzWM_Init, kzWM_Main };