#include "nakano/rtconn.h"
#include "nakano/main.h"
#include "nakano/route.h"
#include "okanoyo/init.h"

static RT_CONN *rt_start;
static RT_CONN *rt_conn[128];
#ifdef KL2_VER_RETAIL
static s32 rtcon_area_max;
#endif

void nkRtConnInit(qword *adr) {
    RT_CONN *rt_conw;
    s32 lp0;
    s32 *version;

    if (nkDG.flag & 4) {
        return;
    }
    if ((*adr)[0] != 2) {
        nkDG.flag |= 4;
        return;
    }

    adr++;
    rt_conw = (RT_CONN *)adr;
    rt_start = rt_conw++;

    lp0 = 0;
    while (1) {
        rt_conn[lp0] = rt_conw;
        while (rt_conw->mode != rcZONEE) {
            rt_conw++;
        }
        rt_conw++;
        KL2_VER_RETAIL_ONLY(lp0++);
        if (rt_conw->mode == rcSTAGEE) {
            break;
        }
        if (KL2_VER_COND(++lp0, lp0) > 128) {
            KL2_DEBUG_PRINT(("nkRtConnInit Route over!!\n"));
            exit(EXIT_FAILURE); // lol???
        }
    };
    KL2_VER_RETAIL_ONLY(rtcon_area_max = lp0);
}

void nkSetRtConn(OBJWORK *objw) {
    RT_CONN *rt_conw = rt_start;
    s32 bun1;
    s32 sube_muki;
    RT_WRK rtw;

    if (nkDG.flag & 4) {
        GameGbl.st_rtn = 0;
        GameGbl.st_mcn = 0;
        return;
    }

    GameGbl.Re_st_rtn = rt_conw->ortn;
    GameGbl.Re_st_mcn = rt_conw->ortcnt << 12;
    GameGbl.Re_st_vision = GameGbl.vision & 0xFF00;
    KL2_VER_TRIAL_ONLY(GameGbl.Re_st_muki = rt_conw->omuki);
#ifdef KL2_VER_RETAIL
    if (GameGbl.flag & 8) {
        GameGbl.Re_st_height = GameGbl.retry_posy;
        GameGbl.Re_st_muki = GameGbl.retry_muki;
        GameGbl.Re_st_klomode = GameGbl.retry_bun1;
    } else {
#endif
        SetRouteNo(&rtw, GameGbl.Re_st_rtn);
        SetMichinori(&rtw, GameGbl.Re_st_mcn);
        GameGbl.Re_st_height = MichiPosiY(&rtw);
        KL2_VER_RETAIL_ONLY(GameGbl.retry_posy = GameGbl.Re_st_height);
        bun1 = nkRtconnKloMode(&rtw, &sube_muki);
        if (bun1 > 1) {
            GameGbl.Re_st_muki = sube_muki;
        }
        KL2_VER_TRIAL_ONLY(GameGbl.Re_st_klomode = bun1);
#ifdef KL2_VER_RETAIL
        else {
            GameGbl.Re_st_muki = rt_conw->omuki;
        }
        GameGbl.retry_muki = GameGbl.Re_st_muki;
        GameGbl.Re_st_klomode = bun1;
        GameGbl.retry_bun1 = bun1;
    }
#endif

    GameGbl.st_flag = rt_conw->flag;
    if (rt_conw->flag & 8) {
        GameGbl.Re_st_height = rt_conw->oheight;
    }
    OkSaveforReStart(GameGbl.Re_st_rtn, GameGbl.Re_st_mcn >> 12, GameGbl.Re_st_height, GameGbl.Re_st_klomode, GameGbl.Re_st_muki);

#ifdef KL2_VER_TRIAL
    if ((GameGbl.vision & 0xFF) != 0) {
        GameGbl.st_rtn = 0;
        GameGbl.st_mcn = 0;
        return;
    }
#endif
    GameGbl.st_rtn = GameGbl.Re_st_rtn;
    GameGbl.st_mcn = GameGbl.Re_st_mcn;
    GameGbl.st_muki = GameGbl.Re_st_muki;
    GameGbl.st_height = GameGbl.Re_st_height;
    GameGbl.st_klomode = GameGbl.Re_st_klomode;
}

INCLUDE_ASM("asm/nonmatchings/nakano/rtconn", nkRtConnMng); // https://decomp.me/scratch/VyTXH

INCLUDE_ASM("asm/nonmatchings/nakano/rtconn", nkRtconnKloMode); // https://decomp.me/scratch/GQyoK