#include "nakano/capture.h"

void WriteVram(s32 x, s32 y, s32 x_s, s32 y_s, char *tfn) {
    s32 Fp;
    s32 i;
    s32 j;
    sceGsStoreImage sp;
    u128 *buff0;
    u128 *buff1;
    u128 *buff_dst;
    char fn[512] = "host:";
    char *tg0;
    char *tg1;
    char *dst;
    static u32 Tim_Header[5] = { 0x10, 0x3, 0xD2000 + 12, 0x00, 0x01C003C0 };
    s32 d_ctrl;

    d_ctrl = *D_CTRL;
    *D_CTRL = d_ctrl & 0x70F;
    KL2_DEBUG_PRINT(("capturing...\n"));
    strcat(fn, tfn);
    buff0 = (u128 *)malloc(x_s * (y_s << 2));
    buff1 = (u128 *)malloc(x_s * (y_s << 2));
    buff_dst = (u128 *)malloc(x_s * (y_s << 2) * 2);

    if (buff0 == NULL || buff1 == NULL) {
        KL2_DEBUG_PRINT(("nakano > capture malloc miss!!\n"));
        return;
    }

    for (i = 0; i < SCR_HEIGHT; i++) {
        sceGsSetDefStoreImage(&sp, 0, 10, 0, 0, i, SCR_WIDTH, 1);
        FlushCache(0);
        sceGsExecStoreImage(&sp, &buff0[i * 0xA0]);
    }

    for (i = 0; i < SCR_HEIGHT; i++) {
        sceGsSetDefStoreImage(&sp, 0x8C0, 10, 0, 0, i, SCR_WIDTH, 1);
        FlushCache(0);
        sceGsExecStoreImage(&sp, &buff1[i * 0xA0]);
    }

    Fp = sceOpen(fn, SCE_WRONLY | SCE_CREAT | SCE_TRUNC);
    if (Fp < 0) {
        KL2_DEBUG_PRINT(("nakano > capture file make miss!!\n"));
        return;
    }

    sceWrite(Fp, Tim_Header, sizeof(Tim_Header));

    tg0 = (char *)buff0;
    tg1 = (char *)buff1;
    dst = (char *)buff_dst;
    for (i = 0; i < SCR_HEIGHT; i++) {
        for (j = 0; j < SCR_WIDTH; j++) {
            dst[0] = tg0[0];
            dst[1] = tg0[1];
            dst[2] = tg0[2];
            dst += 3;
            tg0 += 4;
        }

        for (j = 0; j < SCR_WIDTH; j++) {
            dst[0] = tg1[0];
            dst[1] = tg1[1];
            dst[2] = tg1[2];
            dst += 3;
            tg1 += 4;
        }
    }

    sceWrite(Fp, buff_dst, 0xD2000);
    free(buff0);
    free(buff1);
    free(buff_dst);
    sceClose(Fp);
    KL2_DEBUG_PRINT(("> Write \"%s\" file.\n", tfn));
    *D1_CHCR |= 0x40; // TTE = 1
    *D_CTRL = d_ctrl;
}
