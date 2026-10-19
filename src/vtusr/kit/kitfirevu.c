#include "vtusr/kit/kitfirevu.h"
#include "kit.h"
#include "vtusr/kit/kitfiremain.h"

static kitDMAPACKET *packet_vu1;
static u32 packet_num;
static u32 vu1_odev;
static u32 loop_num;

void kitInitVu1Dma(u128 *p) {
    packet_vu1 = (kitDMAPACKET *)p;
    packet_num = 0;
    vu1_odev = 0;
    loop_num = 0;
}

// Line 30
// any way to do this without the volatile stuff?
inline void kitPushVu1VertexF(f32 v0, f32 v1, f32 v2, f32 v3) {
    if (packet_num % 120 == 0) {
        ((volatile u64 *)packet_vu1->ul)[0] = 0;
        ((volatile u64 *)packet_vu1->ul)[0] = DMAcnt | 120;
        packet_vu1->ui[2] = SCE_VIF1_SET_MSCNT(0);
        packet_vu1->ui[3] = !vu1_odev ? SCE_VIF1_SET_UNPACK(0x160, 120, VIF_UNPACK_V4_32, 0) : SCE_VIF1_SET_UNPACK(0xE0, 120, VIF_UNPACK_V4_32, 0);
        packet_vu1++;
        vu1_odev = 1 - vu1_odev;
        loop_num++;
    }

    ((volatile f32 *)packet_vu1->fl)[0] = v0;
    packet_vu1->fl[1] = v1;
    packet_vu1->fl[2] = v2;
    packet_vu1->fl[3] = v3;
    packet_vu1++;
    packet_num++;
}

// Line 51
// same with this
inline void kitPushVu1VertexI(u32 v0, u32 v1, u32 v2, u32 v3) {
    if (packet_num % 120 == 0) {
        ((volatile u64 *)packet_vu1->ul)[0] = 0;
        ((volatile u64 *)packet_vu1->ul)[0] = DMAcnt | 120;
        packet_vu1->ui[2] = SCE_VIF1_SET_MSCNT(0);
        packet_vu1->ui[3] = !vu1_odev ? SCE_VIF1_SET_UNPACK(0x160, 120, VIF_UNPACK_V4_32, 0) : SCE_VIF1_SET_UNPACK(0xE0, 120, VIF_UNPACK_V4_32, 0);
        packet_vu1++;
        vu1_odev = 1 - vu1_odev;
        loop_num++;
    }

    ((volatile u32 *)packet_vu1->ui)[0] = v0;
    packet_vu1->ui[1] = v1;
    packet_vu1->ui[2] = v2;
    packet_vu1->ui[3] = v3;
    packet_vu1++;
    packet_num++;
}

u128* kitEndVu1Vertex() {
    sceVu0FVECTOR vec[3];
    s32 last;

    if (packet_num == 0) {
        return (u128 *)packet_vu1;
    }

    last = packet_num % 120;
    if (last != 0) {
        last = 120 - last;
        sceVu0CopyVector(vec[0], (f32 *)&packet_vu1[-3]);
        sceVu0CopyVector(vec[1], (f32 *)&packet_vu1[-2]);
        sceVu0CopyVector(vec[2], (f32 *)&packet_vu1[-1]);
        for (; last > 0; last -= 3) {
            sceVu0CopyVector((f32 *)packet_vu1, vec[0]);
            packet_vu1++;
            sceVu0CopyVector((f32 *)packet_vu1, vec[1]);
            packet_vu1++;
            sceVu0CopyVector((f32 *)packet_vu1, vec[2]);
            packet_vu1++;
        }
    }

    packet_vu1->ul[0] = 0;
    do {} while (0); // yeah
    packet_vu1->ul[0] = DMAcnt;
    do {} while (0); // ok
    packet_vu1->ui[2] = SCE_VIF1_SET_MSCNT(0);
    packet_vu1->ui[3] = SCE_VIF1_SET_FLUSH(0);
    packet_vu1++;

    return (u128 *)packet_vu1;
}

u128* kitFireGsInitPacket(u128 *p) {
    kitDMAPACKET *packet = (kitDMAPACKET *)p;

    packet->ul[0] = DMAcnt | 8;
    packet->ui[2] = 0;
    packet->ui[3] = SCE_VIF1_SET_DIRECT(8, 0);
    packet++;
    packet->ul[0] = SCE_GIF_SET_TAG(7, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1);
    packet->ul[1] = SCE_GIF_PACKED_AD;
    packet++;
    packet->ul[1] = SCE_GS_TEST_1;
    packet->ul[0] = SCE_GS_SET_TEST(SCE_GS_TRUE, SCE_GS_ALPHA_GEQUAL, 1, SCE_GS_AFAIL_KEEP, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZGREATER);
    packet++;
    packet->ul[1] = SCE_GS_ALPHA_1;
    packet->ul[0] = SCE_GS_SET_ALPHA(SCE_GS_BLEND_RGB_SRC, SCE_GS_BLEND_RGB_DST, SCE_GS_BLEND_ALPHA_SRC, SCE_GS_BLEND_RGB_DST, 0);
    packet++;
    packet->ul[1] = SCE_GS_CLAMP_1;
    packet->ul[0] = SCE_GS_SET_CLAMP(SCE_GS_REPEAT, SCE_GS_REPEAT, 0, 0, 0, 0);
    packet++;
    packet->ul[1] = SCE_GS_TEX0_1;
    packet->ul[0] = kitfirestructGBL->tex0;
    packet++;
    packet->ul[1] = SCE_GS_TEXA;
    packet->ul[0] = SCE_GS_SET_TEXA(0, 1, 128);
    packet++;
    packet->ul[1] = SCE_GS_TEXFLUSH;
    packet++;
    packet->ul[1] = SCE_GS_TEX1_1;
    packet->ul[0] = SCE_GS_SET_TEX1(0, 0, SCE_GS_LINEAR, SCE_GS_LINEAR, 0, 0, 0);
    packet++;
    
    return (u128 *)packet;
}

u128* kitFireEndPacket(u128 *p) {
    kitDMAPACKET *var_a0 = (kitDMAPACKET *)p;
    var_a0->ul[0] = DMAcnt | 2;
    var_a0->ui[2] = 0;
    var_a0->ui[3] = SCE_VIF1_SET_DIRECT(2, 0);
    var_a0++;
    var_a0->ul[0] = SCE_GIF_SET_TAG(1, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1);
    var_a0->ul[1] = SCE_GIF_PACKED_AD;
    var_a0++;
    var_a0->ad.addr = SCE_GS_TEST_1;
    var_a0->ad.data = SCE_GS_SET_TEST(SCE_GS_FALSE, 0, 0, 0, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZGREATER);
    var_a0++;
    return (u128 *)var_a0;
}

u128* kitVu1Initialize(u128 *p, sceVu0FMATRIX m) {
    kitDMAPACKET *packet = (kitDMAPACKET *)p;

    packet->ul[0] = DMAcnt | 1;
    packet->ui[2] = SCE_VIF1_SET_FLUSH(0);
    packet->ui[3] = SCE_VIF1_SET_NOP(0);
    packet++;
    packet->ui[0] = SCE_VIF1_SET_STMOD(0, 0);
    packet->ui[1] = SCE_VIF1_SET_NOP(0);
    packet->ui[2] = SCE_VIF1_SET_STMASK(0);
    packet->ui[3] = SCE_VIF1_SET_NOP(0);
    packet++;

    packet->ul[0] = DMAcnt | 8;
    packet->ui[2] = SCE_VIF1_SET_STCYCL(4, 4, 0);
    packet->ui[3] = SCE_VIF1_SET_UNPACK(0x00, 8, VIF_UNPACK_V4_32, 0);
    packet++;
    packet->ul128 = *(u128 *)m[0];
    packet++;
    packet->ul128 = *(u128 *)m[1];
    packet++;
    packet->ul128 = *(u128 *)m[2];
    packet++;
    packet->ul128 = *(u128 *)m[3];
    packet++;
    packet->ul[0] = SCE_GIF_SET_TAG(
        4,
        SCE_GS_FALSE,
        SCE_GS_TRUE,
        SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE),
        SCE_GIF_PACKED,
        3
    );
    packet->ul[1] = SCE_GS_RGBAQ | SCE_GS_ST << 4 | SCE_GS_XYZF2 << 8;
    packet++;
    packet->ul[0] = SCE_GIF_SET_TAG(
        4,
        SCE_GS_TRUE,
        SCE_GS_TRUE,
        SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_TRUE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE, SCE_GS_FALSE),
        SCE_GIF_PACKED,
        3
    );
    packet->ul[1] = SCE_GS_RGBAQ | SCE_GS_ST << 4 | SCE_GS_XYZF2 << 8;
    packet++;
    // idk what these numbers mean
    packet->ui[0] = 352;
    packet->ui[1] = 624;
    packet->ui[2] = 64;
    packet++;
    packet->ui[0] = SCR_HEIGHT;
    packet->ui[1] = 480;
    packet++;

    return (u128 *)packet;
}

u128* kitVu1LoadProg(u128 *p, u32 prog_top, u32 size) {
    kitDMAPACKET *packet = (kitDMAPACKET *)p;

    packet->ul[0] = DMAref | size | (u64)prog_top << 32;
    packet->ui[2] = 0;
    packet->ui[3] = SCE_VIF1_SET_FLUSH(0);
    packet++;
    packet->ul[0] = DMAcnt | 0; // ?
    packet->ui[2] = SCE_VIF1_SET_MSCAL(0, 0);
    packet->ui[3] = SCE_VIF1_SET_FLUSH(0);
    packet++;

    return (u128 *)packet;
}
