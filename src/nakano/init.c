#include <eetypes.h>
#include <libdev.h>
#include "nakano/init.h"
#include "nakano/main.h"
#include "harada/hr_pall.h"
#ifdef KL2_VER_RETAIL
#include "nakano/gssub.h"
#include "hoshino/h_file.h"
#endif

void init_config_system() {
    sceDevVif0Reset();
    sceDevVu0Reset();
    sceGsResetPath();
    sceDmaReset(1);
    SysGbl.nmode = 0;
    SysGbl.nsmode = 0;
    SysGbl.fmode = 0;
    SysGbl.smode = 0;
    GameGbl.playdemo_flag = 0;
#ifdef KL2_VER_RETAIL
    GameGbl.kloZanki[0] = 3;
    GameGbl.k_atck_button = 160;
    GameGbl.k_jump_button = 80;
    nkGsInitFrm();
    SysGbl.Language = 1;
    SysGbl.TVSystem = 2;
#endif
}

void nkInitSys() {
    s32 i;
    s32 *data;

    nkDG.capture_num = 0;
    nkDG.map_draw_flag = 0;
    nkDG.opflag = 0;
    hrpt_deb = 0;

#ifdef KL2_VER_RETAIL
    data = (s32 *)hGetSysDataAddr(0);
    if (data != NULL) {
        TkInit((u32 *)((u32)data + data[1]));
    } else {
        TkInit(NULL);
    }

    if (*data == 2) {
        D_3FB93C = (qword *)((u32)data + data[2]);
    } else {
        D_3FB93C = NULL;
    }
#endif
}
