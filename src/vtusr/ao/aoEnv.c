#include "vtusr/ao/aoEnv.h"

u128* setSprayEnv(u128 *pkt, aoWaveStruct *aoStruct) {
    struct {
        u64 dmatag;
        u32 vifcode0;
        u32 vifcode1;
        u64 giftag;
        u64 regs;
        u64 texflush_data;
        u64 texflush_addr;
        u64 clamp1_data;
        u64 clamp1_addr;
        u64 alpha1_data;
        u64 alpha1_addr;
        u64 test1_data;
        u64 test1_addr;
        u64 tex1_1_data;
        u64 tex1_1_addr;
    } *packet = (void *)pkt; // i made this up

    packet->dmatag = DMAcnt | sizeof(*packet) / 0x10 - 1;
    packet->vifcode0 = SCE_VIF1_SET_FLUSH(0);
    packet->vifcode1 = SCE_VIF1_SET_DIRECT(sizeof(*packet) / 0x10 - 1, 0);
    packet->regs = SCE_GIF_PACKED_AD;
    packet->giftag = SCE_GIF_SET_TAG(sizeof(*packet) / 0x10 - 2, 1, 0, 0, 0, 1);
    packet->texflush_addr = SCE_GS_TEXFLUSH;
    packet->texflush_data = 0;
    packet->clamp1_addr = SCE_GS_CLAMP_1;
    packet->clamp1_data = SCE_GS_SET_CLAMP_1(SCE_GS_CLAMP, SCE_GS_CLAMP, 0, 0, 0, 0);
    packet->alpha1_addr = SCE_GS_ALPHA_1;
    packet->alpha1_data = SCE_GS_SET_ALPHA_1(SCE_GS_BLEND_RGB_SRC, SCE_GS_BLEND_RGB_DST, SCE_GS_BLEND_ALPHA_SRC, SCE_GS_BLEND_RGB_DST, 0);
    packet->test1_addr = SCE_GS_TEST_1;
    packet->test1_data = SCE_GS_SET_TEST_1(SCE_GS_TRUE, SCE_GS_ALPHA_NEVER, 0, SCE_GS_AFAIL_RGB_ONLY, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZGREATER);
    packet->tex1_1_addr = SCE_GS_TEX1_1;
    packet->tex1_1_data = SCE_GS_SET_TEX1_2(0, 0, SCE_GS_LINEAR, SCE_GS_LINEAR, 0, 0, 0);

    packet++;
    return (u128 *)packet;
}

u128* endSprayEnv(u128 *pkt) {
    struct {
        u64 dmatag;
        u32 vifcode0;
        u32 vifcode1;
        u64 giftag;
        u64 regs;
        u64 alpha1_data;
        u64 alpha1_addr;
        u64 test1_data;
        u64 test1_addr;
    } *packet = (void *)pkt; // i also made this up

    packet->dmatag = DMAcnt | sizeof(*packet) / 0x10 - 1;
    packet->vifcode0 = SCE_VIF1_SET_FLUSH(0);
    packet->vifcode1 = SCE_VIF1_SET_DIRECT(sizeof(*packet) / 0x10 - 1, 0);
    packet->regs = SCE_GIF_PACKED_AD;
    packet->giftag = SCE_GIF_SET_TAG(sizeof(*packet) / 0x10 - 2, 1, 0, 0, 0, 1);
    packet->alpha1_addr = SCE_GS_ALPHA_1;
    packet->alpha1_data = SCE_GS_SET_ALPHA_1(SCE_GS_BLEND_RGB_SRC, SCE_GS_BLEND_RGB_DST, SCE_GS_BLEND_ALPHA_SRC, SCE_GS_BLEND_RGB_DST, 0);
    packet->test1_addr = SCE_GS_TEST_1;
    packet->test1_data = SCE_GS_SET_TEST_1(SCE_GS_FALSE, SCE_GS_ALPHA_NEVER, 0, SCE_GS_AFAIL_KEEP, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZGREATER);

    packet++;
    return (u128 *)packet;
}