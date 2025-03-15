#include "hoshino/h_util.h"

void dump8(u8 *p) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        KL2_DEBUG_PRINT(("%p : ", p));
        for (j = 0; j < 16; j++) {
            if (j == 7)
                printf("%02x-", *p++);
            else
                printf("%02x ", *p++);
        }
        KL2_DEBUG_PRINT(("\n"));
    }
}

void dump64(u64 *p, char *str) {
    s32 i;
    s32 j;

    KL2_DEBUG_PRINT(("[%s]\n", str));
    for (i = 0; i < 16; i++) {
        KL2_DEBUG_PRINT(("%p : ", p));
        for (j = 0; j < 2; j++) {
            KL2_DEBUG_PRINT(("%016lx ", *p++));
        }
        KL2_DEBUG_PRINT(("\n"));
    }
}

// Note: pAddr type was changed from u32* to void*
// I'm pretty sure this dev has an aversion to void pointers...

u32 GetFHMNum(void *pAddr) {
    return *(u32 *)pAddr;
}

void* GetFHMAddress(void *pAddr, u32 nNum) {
    return (u32 *)pAddr + (((u32 *)pAddr)[nNum + 1] >> 2);
}

s32 hFileSize(char *filename) {
    s32 fd;
    s32 size;

    fd = sceOpen(filename, SCE_RDONLY);
    if (fd < 0) {
        KL2_DEBUG_PRINT(("open error!\n"));
        sceClose(fd);
        return -1;
    }

    size = sceLseek(fd, 0, SCE_SEEK_END);
    sceLseek(fd, 0, SCE_SEEK_SET);
    sceClose(fd);
    return size;
}

s32 hFileLoad(char *filename, s32 buff) {
    s32 fd;
    s32 size;
    s32 p; // this is a pointer stored in a signed int variable...

    KL2_DEBUG_PRINT(("file load(%s) ... ", filename));
    fd = sceOpen(filename, SCE_RDONLY);
    if (fd < 0) {
        KL2_DEBUG_PRINT(("open error!\n"));
        sceClose(fd);
        return -1;
    }

    size = sceLseek(fd, 0, SCE_SEEK_END);
    sceLseek(fd, 0, SCE_SEEK_SET);
    if (buff == 0) {
        p = (s32)malloc(size);
        if (p == 0) {
            KL2_DEBUG_PRINT(("malloc error!\n"));
            sceClose(fd);
            return -2;
        }
    } else {
        p = buff;
    }

    size = sceRead(fd, (void *)p, size);
    if (size < 0) {
        KL2_DEBUG_PRINT(("read error!\n"));
        sceClose(fd);
        if (buff == 0) {
            free((void *)p);
        }
        return -3;
    }
    sceClose(fd);
    KL2_DEBUG_PRINT(("complete.\n"));
    return p;
}

s32 hFileRead(char *filename, s32 buff, s32 *size) {
    s32 fd;
    s32 p;

    KL2_DEBUG_PRINT(("file load(%s) ... ", filename));
    fd = sceOpen(filename, SCE_RDONLY);
    if (fd < 0) {
        KL2_DEBUG_PRINT(("open error!\n"));
        sceClose(fd);
        return -1;
    }

    *size = sceLseek(fd, 0, SCE_SEEK_END);
    sceLseek(fd, 0, SCE_SEEK_SET);
    if (buff == 0) {
        p = (s32)malloc(*size);
        if (p == 0) {
            KL2_DEBUG_PRINT(("malloc error!\n"));
            sceClose(fd);
            return -2;
        }
    } else {
        p = buff;
    }

    *size = sceRead(fd, (void *)p, *size);
    if (*size < 0) {
        KL2_DEBUG_PRINT(("read error!\n"));
        sceClose(fd);
        if (buff == 0)
            free((void *)p);
        return -3;
    }
    sceClose(fd);
    KL2_DEBUG_PRINT(("complete.\n"));
    return p;
}

