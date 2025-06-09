#include "hoshino/h_init.h"
#include "hoshino/h_rpc.h"
#include <libcdvd.h>
#include <sifrpc.h>

#ifdef KL2_VER_TRIAL
char *LoadModuleList[] = {
    "cdrom0:\\KLONOA2\\M\\SIFCMD.IRX;1",
    "cdrom0:\\KLONOA2\\M\\SIO2MAN.IRX;1",
    "cdrom0:\\KLONOA2\\M\\MCMAN.IRX;1",
    "cdrom0:\\KLONOA2\\M\\MCSERV.IRX;1",
    "cdrom0:\\KLONOA2\\M\\PADMAN.IRX;1",
    "cdrom0:\\KLONOA2\\M\\LIBSD.IRX;1",
    "cdrom0:\\KLONOA2\\M\\SDRDRV.IRX;1",
    "cdrom0:\\KLONOA2\\M\\KL2.IRX;1"
};
#else
char *LoadModuleList[] = {
    "cdrom:\\M\\SIFCMD.IRX;1",
    "cdrom:\\M\\SIO2MAN.IRX;1",
    "cdrom:\\M\\MCMAN.IRX;1",
    "cdrom:\\M\\MCSERV.IRX;1",
    "cdrom:\\M\\PADMAN.IRX;1",
    "cdrom:\\M\\LIBSD.IRX;1",
    "cdrom:\\M\\SDRDRV.IRX;1",
    "cdrom:\\M\\KL2.IRX;1"
};
#endif

#define KL2_IOP_IMAGE_FILE "IOPRP213.IMG"

#ifdef KL2_VER_TRIAL
static s32 Pre2Switch = 0;

s32 hPre2Check() {
    return Pre2Switch;
}

void hPre2SetSW(s32 i) {
    Pre2Switch = i;
}
#endif

void hInitBoot() {
    s32 i, j;

    KL2_DEBUG_PRINT(("hInitBoot ...\n"));
    sceSifInitRpc(0);
    while (!sceCdInit(SCECdINIT));
#ifdef KL2_VER_TRIAL
    while (!sceSifRebootIop("cdrom0:\\KLONOA2\\M\\"KL2_IOP_IMAGE_FILE";1"));
#else
    while (!sceSifRebootIop("cdrom:\\M\\"KL2_IOP_IMAGE_FILE";1"));
#endif
    while (!sceSifSyncIop());
    sceSifInitRpc(0);
    sceSifInitIopHeap();
    sceSifLoadFileReset();
    while (!sceCdInit(SCECdINIT));
    while (!sceCdMmode(SCECdDVD));
    sceFsReset();
    for (i = 0; i < sizeof(LoadModuleList) / sizeof(LoadModuleList[0]); i++) {
        KL2_DEBUG_PRINT(("Load Module [%s]\n", LoadModuleList[i]));
        while ((j = sceSifLoadModule(LoadModuleList[i], 0, NULL)) < 0) {
            KL2_DEBUG_PRINT(("*** cant Load Module %s=%d\n", LoadModuleList[i], -j));
            KL2_DEBUG_PRINT(("SCE_EBINDMISS=%d SCE_EVERSIONMISS=%d SCE_ECALLMISS=%d\n", SCE_EBINDMISS, SCE_EVERSIONMISS, SCE_ECALLMISS));
            while (!sceCdInit(SCECdINIT));
            sceCdDiskReady(0);
            while (!sceCdMmode(SCECdDVD));
            sceFsReset();
        }
    }

    hRpcInit();
    hRpc(IOP_IopInit);
#ifndef KL2_VER_TRIAL
    init_config_system();
#endif
    hCdInit();
#ifndef KL2_VER_TRIAL
    hMovInit();
#endif
    hSndInit();
    
    GameGbl.vision = KL2_VISION(99, 0);
    hSndBankSetMain();
    KL2_DEBUG_PRINT(("JOCHU SIZE=%d\n", hGameDataSize(1)));
    hSysDataRead((s32)getBuff(1, hGameDataSize(1), NULL, &j));
    memoryStageptrSet();
    htInitRand(0x399);
#ifdef KL2_VER_TRIAL
    hPre2SetSW(1);
#endif

    KL2_DEBUG_PRINT(("hInitBoot ... done\n"));
}

void hLoopTop() {
    while (hRpcSync());
    hSndRpcRet();
}

void hLoopBottom() {
    hSndMain();
    hCdMain();
}

s32 SyncV() {
    hLoopBottom();
    return sceGsSyncV(0) ^ 1;
}