#include "nakano/gflow.h"
#include "nakano/dma.h"
#include "nakano/game.h"
#include "nakano/gssub.h"
#include "nakano/wipe.h"
#include "hoshino/h_game.h"
#include "okanoyo/okmain.h"
#include "okanoyo/okprint.h"

// TODO: retail version https://decomp.me/scratch/INM7d
void GameFlow() {
    if (GameGbl.wipe.intime > 0) {
        GameGbl.wipe.intime--;
    }
    
    if (GameGbl.init_vision) {
        KL2_VER_RETAIL_ONLY(kzSetDispMaskOn());
        nkPathReset();
        nkPathBlock();
        nkInitPS2();
        nkGsSetNormalFZ2_0();
        nkWipeEffBClear();
        nkGsSetNormalFZ2_1();
        nkWipeEffBClear();
        KL2_VER_RETAIL_ONLY(TkRemoveAllEffect());

        if ((GameGbl.vision & 0xFF00) != (GameGbl.init_vision & 0xFF00)) {
            GameGbl.vision = GameGbl.init_vision;
            SysGbl.smode = 0;
        } else {
            GameGbl.vision = GameGbl.init_vision;
            InitAllObjWork2(SysGbl.objwork, SysGbl.n_objw);
            nkAreaInit();
        }
    } else if (GameGbl.wipe.outtime > 0) {
#ifdef KL2_VER_RETAIL
        if (GameGbl.wipe.flag & 2 && GameGbl.wipe.fdata > 0) {
            GameGbl.wipe.fdata--;
            if (GameGbl.wipe.fdata - 1 == -1) {
                hGameAreaEnd(GameGbl.wipe.next_vision);
            }

        } else {
#endif
            GameGbl.wipe.outtime--;
            KL2_OK_PRINT((1, 2, 20, scr_p[1], "WIPE CNT = %d", GameGbl.wipe.outtime));
            if (GameGbl.wipe.outtime < 1) {
                KL2_VER_RETAIL_ONLY(GameGbl.wipe.flag &= 0xFFFD);
                if (GameGbl.wipe.next_vision != 0) {
                    KL2_VER_RETAIL_ONLY(kzSetDispMaskOn());
                    nkPathReset();
                    nkPathBlock();
                    GameGbl.wipe.intime = 64;
                    GameGbl.vision = GameGbl.wipe.next_vision;
                    GameGbl.wipe.next_vision = 0;
                    GameGbl.st_rtn = GameGbl.wipe.rtn;
                    GameGbl.st_mcn = GameGbl.wipe.mcn;
                    GameGbl.Re_st_rtn = -1;
                    nkInitPS2();
                    InitAllObjWork2(SysGbl.objwork, SysGbl.n_objw);
                    KL2_VER_RETAIL_ONLY(TkRemoveAllEffect());
                    nkAreaInit();
                }
            }
#ifdef KL2_VER_RETAIL
        }
#endif
    } else {
        if (KL2_VER_COND((GameGbl.vision & 0xFF) != 0xEE && !(GameGbl.flag & 4), GameGbl.vision >> 8 < 30)) {
            nkRtConnMng(GameGbl.klonoa);
        }
    }
}
