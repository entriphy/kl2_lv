#include <sifdev.h>
#include "nakano/readfile.h"

s32 read_file(char *name, char *buff) {
    s32 fd;
    s32 size;

    fd = sceOpen(name, SCE_RDONLY);
    if (fd < 0) {
        KL2_DEBUG_PRINT(("cannot open file.[%s]\n", name));
        return -1;
    }

    size = sceLseek(fd, 0, SCE_SEEK_END);
    sceLseek(fd, 0, SCE_SEEK_SET);
    size = (size + 15) / 16 * 16;
    sceRead(fd, buff, size);
    sceClose(fd);
    KL2_DEBUG_PRINT(("Read [%s] file. size of = %d\n", name, size));
    return size;
}

qword* read_file128(char *name, qword *buff) {
    s32 fd;
    s32 size;
    s32 h;

    fd = sceOpen(name, SCE_RDONLY);
    if (fd < 0) {
        KL2_DEBUG_PRINT(("cannot open file.[%s]\n", name));
        return (qword *)-1;
    }

    size = sceLseek(fd, 0, SCE_SEEK_END);
    sceLseek(fd, 0, SCE_SEEK_SET);
    size = (size + 15) / 16;
    sceRead(fd, buff, size * 16);
    sceClose(fd);
    KL2_DEBUG_PRINT(("Read [%s] file. size of = %d\n", name, size));
    return (qword *)(buff + size);
}