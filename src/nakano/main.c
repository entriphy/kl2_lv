#include "nakano/main.h"

NKDEBGBL nkDG = {};
SYSGBL SysGbl = {};
sceDmaChan *DmaChVIF0 = NULL;
sceDmaChan *DmaChVIF1 = NULL;
sceDmaChan *DmaChGIF = NULL;
sceDmaChan *DmaChfromIPU = NULL;
sceDmaChan *DmaChtoIPU = NULL;
sceDmaChan *DmaChfromSPR = NULL;
sceDmaChan *DmaChtoSPR = NULL;
qword PsfxWorkBuff[131072] __attribute__((section(".bss")));
vpmINFO VpmInfo = {};
qword *p1_packet_top = NULL;
qword *p1_packet = NULL;
qword *p1_packet_cnt = NULL;
qword p1_packet_buff[2][4096] __attribute__((section(".bss")));;
s32 draw_id = 0;
qword p1_ot_buff[2][5] __attribute__((section(".bss")));;
qword *p1_ot = NULL;
s32 p1_packet_max = 0;
qword vu0mem_image[256] = {};
qword vu1mem_image[1024] = {};
u32 *NakanoPackAdr = NULL;
u32 *nkGimPackAdr = NULL;
#ifndef KL2_VER_TRIAL
qword *D_3FB93C = NULL;
#endif
u32 *vtWaveAdr = NULL;
u32 *vtSprayAdr = NULL;
u32 *vtMovieAdr[8] = {};

extern u16 hrpt_deb; // TODO: remove

s32 main(s32 argc, char *argv[]) {
#ifdef KL2_VER_TRIAL
    u16 language;
    u16 aspect;
    u16 playmode;
    u16 to_inactive;
    u16 to_total;
    u16 mediaType;
    u16 masterVolumeScale;
    u16 directorySectorNum;

    sceDemoStart(argc, argv, &language, &aspect, &playmode, &to_inactive, &to_total, &mediaType, &masterVolumeScale, &directorySectorNum);
    printf("l %d a %d pm %d toa %d tot %d\n", language, aspect, playmode, to_inactive, to_total);
    printf("MEDIA TYpE %d\n", mediaType); // why is the p lowercase
#endif

    memorySysFormat();
    hInitBoot();
    SysGbl.irqc = 0;
    init_config_system();
    *T0_MODE = T_MODE_CLKS_M | T_MODE_CUE_M;
    nkInitPad();
    OkMainInit(argc, argv);
    nkInitSys();
    hr_cold_start();
    hrpt_deb = 1;
    SysGbl.fmode = 1;
    GameGbl.vision = KL2_VISION(30, 0);
    nkDG.opflag |= 4;
    nkDG.opflag |= 2;
    while (!sceGsSyncV(0));
    
    do {
        hLoopTop();
        MainFunc();
        SysGbl.irqc++;
    } while (KL2_VER_COND(hPre2Check(), 1));

#ifdef KL2_VER_TRIAL
    sceSifExitCmd();
    sceDemoEnd(5);
    printf("finish!\n");
#endif

    return 0;
}