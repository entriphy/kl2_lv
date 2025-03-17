#include "hoshino/h_file.h"
#include "hoshino/h_cdvd.h"
#include "hoshino/h_util.h"

// Note: buff type changed from s32 to void*
static void *GameDataTop;
static void *SysDataTop;

s32 hGameDataSize(s32 mode) {
    return hCdGetSize((GameGbl.vision >> 7 & 0x1FE) + mode) << 0xB;
}

// Note: buff type changed from s32 to void*
void hGameRead(s32 mode, void *buff) {
    GameDataTop = buff;
    hCdReadData((GameGbl.vision >> 7 & 0x1FE) + mode, buff);
    KL2_DEBUG_PRINT(("GameDataTop=%08x mode=%d\n", (u32)GameDataTop, mode));
}

// Note: buff type changed from s32 to void*
void hSysDataRead(void *buff) {
    SysDataTop = buff;
    hCdReadDataBlock(199, buff);
}

s32 hGameReadOK() {
    return hCdReadSync();
}

s32 hGetDataAddr(s32 i) {
    s32 *addr = GetFHMAddress(GameDataTop, i);
    return *addr == -1 ? 0 : (s32)addr;
}

s32 hGetSysDataAddr(s32 i) {
    s32 *addr = GetFHMAddress((u32 *)SysDataTop, i);
    return *addr == -1 ? 0 : (s32)addr;
}
