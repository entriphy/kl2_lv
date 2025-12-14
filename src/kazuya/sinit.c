#include "kazuya/sinit.h"
#include "hoshino/h_file.h"
#include "kazuya/bios.h"
#include "kazuya/cvar.h"
#include "kazuya/interfac.h"
#include "kazuya/td_job.h"
#include "kazuya/td_mhjob.h"
#include "kazuya/td_sys.h"
#include "nakano/dma.h"

s32 kzPack0_title[] = {PF_SELTITLE_GMS, PF_SELLOGO_GMS, PF_KUMO1_GMS, PF_KUMO2_GMS, -1 };
s32 kzPack0_wmap[] = { PF_SELTITLE_GMS, PF_KUMO1_GMS, PF_KUMO2_GMS, -1 };
s32 kzPack0_mommet[] = { PF_SELTITLE_GMS, -1 };
char *kzBulk0_title[] = { "seltitle.gms", "sellogo.gms", "kumo1.gms", "kumo2.gms", NULL };
char *kzBulk0_wmap[] = { "selmap.gms", "kumo1.gms", "kumo2.gms", NULL };
char *kzBulk0_mommet[] = { "selmome.gms", NULL };

#ifdef KL2_VER_TRIAL
void kzStageInit0() {
    char path[256];
    u32 *pack_adr;
    s32 i;
    s32 stage_no;
    s32 *arrayP;

    kzLoadCommonGms();
    stage_no = kz_Get_StageNo();
    if (stage_no < 0) {
        return;
    }
    switch (stage_no) {
        case 30:
            arrayP = kzPack0_title;
            break;
        case 34:
            arrayP = kzPack0_wmap;
            break;
        case 35:
            arrayP = kzPack0_mommet;
            break;
        default:
            arrayP = kzPack0_mommet;
            break;
    }

    pack_adr = (u32 *)hGetDataAddr(7);
    if (pack_adr != NULL) {
        for (i = arrayP[0]; i >= 0; i = arrayP[i]) {
            nkLoadGms(KL2_FHM_ADDR(pack_adr, i));
            sceGsSyncPath(0, 0);
            i++;
        }
    }
    FlushCache(WRITEBACK_DCACHE);

}
#else
void kzStageInit0() {
    s32 stage_no;
    s32 *gms_language;
    u8 *gms;
    s32 i;
    u8 stackShiz[0x100];
    
    kzLoadCommonGms();
    stage_no = kz_Get_KazuyaStageNo();
    if (stage_no > -1) {
        switch (stage_no) {
            case 30:
                switch (SysGbl.Language) {
                    case 1:
                        gms_language = ENGLISH_30;
                        break;
                    case 2:
                        gms_language = FRENCH_30;
                        break;
                    case 3:
                        gms_language = SPANISH_30;
                        break;
                    case 4:
                        gms_language = GERMAN_30;
                        break;
                    case 5:
                        gms_language = ITALIAN_30;
                        break;
                }
                break;
            case 31:
                gms_language = MUTLI_31;
                break;
            case 32:
                switch (SysGbl.Language) {
                    case 1:
                        gms_language = ENGLISH_32;
                        break;
                    case 2:
                        gms_language = FRENCH_32;
                        break;
                    case 3:
                        gms_language = SPANISH_32;
                        break;
                    case 4:
                        gms_language = GERMAN_32;
                        break;
                    case 5:
                        gms_language = ITALIAN_32;
                        break;
                }
                break;
            case 33:
                return;
            case 34:
                switch (SysGbl.Language) {
                    case 1:
                        gms_language = ENGLISH_34;
                        break;
                    case 2:
                        gms_language = FRENCH_34;
                        break;
                    case 3:
                        gms_language = SPANISH_34;
                        break;
                    case 4:
                        gms_language = GERMAN_34;
                        break;
                    case 5:
                        gms_language = ITALIAN_34;
                        break;
                }
                break;
            case 35:
                gms_language = MULTI_35;
                break;
        }

        i = 0;
        gms = (u8 *)hGetDataAddr(7);
        if (gms != NULL) {
            while (gms_language[i] >= 0) {
                nkLoadGms(gms + ((s32 *)gms)[i + 1]);
                sceGsSyncPath(0, 0);
                i++;
            }
        }
        FlushCache(WRITEBACK_DCACHE);
    }
}
#endif

void kzStageInit1() {
	s32 stage_no;

    kz_Init_McInfo(&kzMcInfo);
    mci = &kzMcInfo;
    kpd0 = &GameGbl.kpd[0];
    kpd1 = &GameGbl.kpd[1];
    kzWM_Init_All();
    kzTD_Init_All();
    KumoInit();

    stage_no = kz_Get_StageNo();
    if (stage_no < 0) {
        return;
    }
    if (stage_no != 35 || mommet_mode == MOM_MODE_NORMAL) {
        kzTD_Clear_LastInfo();
    }
    FlushCache(WRITEBACK_DCACHE);
}

void kzAreaInit() {
    if (kz_Get_StageNo() < 0) {
        kzTD_Init_Fade(-1);
        return;
    }

    switch (GameGbl.vision) {
        case KL2_VISION(30, 0):
            first_enter = 0;
            kzTD_Init_Fade(1);
            GameGbl.flag |= 0x1;
            wm_jobcnt_next0 = WM_JOB_IDLE;
            td_jobcnt_next0 = TD_JOB_1ST_LOGO;
            break;
        case KL2_VISION(30, 1):
            kzTD_Init_Fade(-1);
            wm_jobcnt_next0 = WM_JOB_IDLE;
            td_jobcnt_next0 = TD_JOB_PUP_WAIT;
            after_puppet_dst = KL2_VISION(30, 2);
            break;
        case KL2_VISION(30, 2):
            kzTD_Init_Fade(1);
            GameGbl.flag |= 0x1;
            wm_jobcnt_next0 = WM_JOB_IDLE;
            td_jobcnt_next0 = TD_JOB_TTL_MENU;
            break;
        case KL2_VISION(31, 0):
            kzTD_Init_Fade(1);
            GameGbl.flag |= 0x1;
            GameGbl.flag |= 0x2;
            wm_jobcnt_next0 = WM_JOB_IDLE;
            td_jobcnt_next0 = TD_JOB_FIL_SAVEDATASEL;
            break;
        case KL2_VISION(32, 0):
            kzTD_Init_Fade(1);
            GameGbl.flag |= 0x1;
            wm_jobcnt_next0 = WM_JOB_VISIONOVER;
            td_jobcnt_next0 = TD_JOB_GAM_VISIONOVER;
            break;
        case KL2_VISION(34, 0):
            kzTD_Init_Fade(1);
            GameGbl.flag |= 0x1;
            GameGbl.flag |= 0x2;
            wm_jobcnt_next0 = WM_JOB_IDLE;
            td_jobcnt_next0 = TD_JOB_WMP_ENTER;
            break;
        case KL2_VISION(34, 1):
            kzTD_Init_Fade(1);
            GameGbl.flag |= 0x1;
            wm_jobcnt_next0 = WM_JOB_STATUS;
            td_jobcnt_next0 = TD_JOB_WMP_STATUS;
            break;
        case KL2_VISION(34, 2):
        case KL2_VISION(34, 3):
        case KL2_VISION(34, 4):
        case KL2_VISION(34, 5):
        case KL2_VISION(34, 6):
            kzTD_Init_Fade(1);
            wm_jobcnt_next0 = WM_JOB_MAIN;
            td_jobcnt_next0 = TD_JOB_WMP_MAIN;
            break;
        case KL2_VISION(35, 0):
            kzTD_Init_Fade(-1);
            wm_jobcnt_next0 = WM_JOB_IDLE;
            td_jobcnt_next0 = TD_JOB_PUP_WAIT;
            after_puppet_dst = KL2_VISION(35, 1);
            break;
        case KL2_VISION(35, 1):
            kzTD_Init_Fade(1);
            switch (mommet_mode) {
                case MOM_MODE_NORMAL:
                    wm_jobcnt_next0 = WM_JOB_MOMTOP;
                    td_jobcnt_next0 = TD_JOB_MOM_TOP;
                    break;
                case MOM_MODE_GENJU:
                    wm_jobcnt_next0 = WM_JOB_MOMTOP;
                    td_jobcnt_next0 = TD_JOB_MOM_GENJU;
                    break;
                case MOM_MODE_THEATER:
                default:
                    wm_jobcnt_next0 = WM_JOB_MOMTOP;
                    td_jobcnt_next0 = TD_JOB_MOM_PUPPETGROUP;
                    break;
            }
            
            mommet_mode = MOM_MODE_NORMAL;
            break;
        default:
            kzTD_Init_Fade(-1);
            wm_jobcnt_next0 = WM_JOB_IDLE;
            td_jobcnt_next0 = TD_JOB_IDLE;
            break;
    }

    kzWM_Change_Job();
    kzTD_Change_Job();
}