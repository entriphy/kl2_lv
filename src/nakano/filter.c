#include "nakano/filter.h"
#include "nakano/main.h"
#include "nakano.h"

#ifdef KL2_VER_TRIAL
#define FRAME_FBW 10
#else
#define FRAME_FBW 8
#endif

u8 nkCalIntpl8bit(u8 a, u8 b, f32 pow) {
    f32 af;
    f32 bf;

    af = (f32)a;
    bf = (f32)b;

    af = ((bf - af) * pow) + af;
    if (af < 0.0f) {
        af = 0.0f;
    } else if (af > 255.0f) {
        af = 255.0f;
    }

    return af;
}

u32 nkCalIntplCol(u32 ca, u32 cb, f32 pow) {
    u32 ret;

    // ?
    u8 ret0;
    u8 ret1;
    u8 ret2;

    ret0 = nkCalIntpl8bit(ca, cb, pow);
    nkCalIntpl8bit(ca >> 8, cb >> 8, pow);
    ret1 = nkCalIntpl8bit(ca >> 16, cb >> 16, pow);
    ret2 = nkCalIntpl8bit(ca >> 24, cb >> 24, pow);
    ret = ret2 << 24 | ret1 << 16 | ret1 << 8 | ret0;
    return ret;
}

void nkDrawEffFr() {
    nkEffFrDrawEnv de;
    nkGifPacket packet;
    nkGifPacket *pp;

    sceDmaSync(DmaChGIF, 0, 0);

    de.size_texenv = sceGsSetDefTexEnv2(&de.texenv, 1, 0x1680, 10, 0, 10, 8, 0, 0, 0, 0, 1);
    de.alpha = SCE_GS_SET_ALPHA_2(SCE_GS_BLEND_RGB_DST, SCE_GS_BLEND_RGB_DST, SCE_GS_BLEND_ALPHA_SRC, SCE_GS_BLEND_RGB_SRC, 0);
    de.alp_addr = SCE_GS_ALPHA_2;
    de.size_texenv++;
    de.gif_texenv.NLOOP = de.size_texenv;
    de.gif_texenv.EOP = SCE_GS_TRUE;
    de.gif_texenv.PRE = SCE_GS_FALSE;
    de.gif_texenv.PRIM = 0;
    de.gif_texenv.FLG = SCE_GIF_PACKED;
    de.gif_texenv.NREG = 1;
    de.gif_texenv.REGS0 = SCE_GIF_PACKED_AD;

    FlushCache(0);
    sceDmaSendN(DmaChGIF, &de.gif_texenv, de.size_texenv + 1);
    sceDmaSync(DmaChGIF, 0, 0);

    pp = &packet;
    pp->size = 0;
    pp->buf = SPR_MEM;
    pp->buf[pp->size].ul128 = 0;
    pp->buf[pp->size++].ul32[0] = DMAend | 13;
    pp->buf[pp->size].ul64[0] = SCE_GIF_SET_TAG(4, SCE_GS_TRUE, SCE_GS_TRUE, SCE_GS_SET_PRIM(SCE_GS_PRIM_TRISTRIP, 1, 1, 0, 0, 0, 1, 1, 0), SCE_GIF_PACKED, 3);
    pp->buf[pp->size++].ul64[1] = SCE_GS_UV | SCE_GS_RGBAQ << 4 | SCE_GS_XYZF2 << 8;

    SETVEC(pp->buf[pp->size].ul32, 0x00, SCR_HEIGHT * 0x10, 0x00, 0x00);
    pp->size++;
    SETVEC(pp->buf[pp->size].ul32, 0x88, 0x88, 0x88, 0x40);
    pp->size++;
    SETVEC(pp->buf[pp->size].ul32, GS_X_COORD(0), GS_Y_COORD(SCR_HEIGHT), 0xFFFFF, 0x0000);
    pp->size++;

    SETVEC(pp->buf[pp->size].ul32, 0x00, 0x00, 0x00, 0x00);
    pp->size++;
    SETVEC(pp->buf[pp->size].ul32, 0x88, 0x88, 0x88, 0x40);
    pp->size++;
    SETVEC(pp->buf[pp->size].ul32, GS_X_COORD(0), GS_Y_COORD(0), 0xFFFFF, 0x0000);
    pp->size++;

    SETVEC(pp->buf[pp->size].ul32, SCR_WIDTH * 0x10, SCR_HEIGHT * 0x10, 0x00, 0x00);
    pp->size++;
    SETVEC(pp->buf[pp->size].ul32, 0x88, 0x88, 0x88, 0x40);
    pp->size++;
    SETVEC(pp->buf[pp->size].ul32, GS_X_COORD(SCR_WIDTH), GS_Y_COORD(SCR_HEIGHT), 0xFFFFF, 0x0000);
    pp->size++;

    SETVEC(pp->buf[pp->size].ul32, SCR_WIDTH * 0x10, 0x00, 0x00, 0x00);
    pp->size++;
    SETVEC(pp->buf[pp->size].ul32, 0x88, 0x88, 0x88, 0x40);
    pp->size++;
    SETVEC(pp->buf[pp->size].ul32, GS_X_COORD(SCR_WIDTH), GS_Y_COORD(0), 0xFFFFF, 0x0000);
    pp->size++;

    KL2_VER_TRIAL_ONLY(FlushCache(WRITEBACK_DCACHE));
    DmaChGIF->chcr.TTE = 1;
    sceDmaSend(DmaChGIF, SPR_SEND);
    sceDmaSync(DmaChGIF, 0, 0);
}

static qword* make_flt_Div(qword *p, s32 dv, u64 scissor, u64 *tex0, u64 *frame) {
    u64 *p0;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 pw;
    s32 ph;
    s32 nloop;
    s32 offx;
    s32 offy;
    s32 offu;

    if (dv < 0) {
        return p;
    }

    n = 1 << dv;
    pw = SCR_WIDTH * 0x10 >> dv;
    ph = SCR_HEIGHT << (4 - dv);
    nloop = pw / 512;
    offy = 0x70 >> dv;
    offu = dv == 2 ? 0x1400 : 0;
    offx = 0;
    for (i = 0; i < dv; i++) {
        offx += 0x140 >> i;
    }
    offx <<= 4;

    ((u64 *)&p[0])[0] = SCE_GIF_SET_TAG(1, SCE_GS_FALSE, SCE_GS_TRUE, SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 1, 0, 0, 0, 1, 0, 0), SCE_GIF_PACKED, 1);
    ((u64 *)&p[0])[1] = SCE_GIF_PACKED_AD;
    ((u64 *)&p[1])[0] = scissor;
    ((u64 *)&p[1])[1] = SCE_GS_SCISSOR_1;
    p += 2;

    for (i = 0; i < n; i++, tex0++) {
        ((u64 *)&p[0])[0] = SCE_GIF_SET_TAG(1, SCE_GS_FALSE, SCE_GS_FALSE, 0, SCE_GIF_REGLIST, 1);
        ((u64 *)&p[0])[1] = SCE_GS_TEX0_1;
        ((u64 *)&p[1])[0] = *tex0;
        p += 2;

        for (j = 0; j < 32; j += 0x10, frame++) {
            ((u64 *)&p[0])[0] = SCE_GIF_SET_TAG(1, SCE_GS_FALSE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1);
            ((u64 *)&p[0])[1] = SCE_GIF_PACKED_AD;
            ((u64 *)&p[1])[0] = *frame;
            ((u64 *)&p[1])[1] = SCE_GS_FRAME_1;
            ((u64 *)&p[2])[0] = SCE_GIF_SET_TAG(nloop, SCE_GS_FALSE, SCE_GS_FALSE, 0, SCE_GIF_REGLIST, 4);
            ((u64 *)&p[2])[1] = SCE_GS_UV << 0 | SCE_GS_XYZ2 << 4 | SCE_GS_UV << 8 | SCE_GS_XYZ2 << 12;
            p += 3;

            p0 = (u64 *)p;
            for (k = 0; k < pw; k += 0x200, p0 += 4) {
                p0[0] = SCE_GS_SET_UV(k + j + offu, j + i * ph);
                p0[1] = SCE_GS_SET_XYZ2((k >> 1) + offx, j * offy + i * (offy << 5), 0x00);
                p0[2] = SCE_GS_SET_UV(k + j + offu + 0x1F8, ph + j + i * ph);
                p0[3] = SCE_GS_SET_XYZ2((k >> 1) + offx + 0xFC, (ph >> 1) + j * offy + i * (offy << 5), 0x00);
            }
            p = (qword *)p0;
        }
    }

    return p;
}

static qword* make_flt_Acc(qword *p, s32 dv, u64 scissor, u64 *tex0, u64 *frame, u64 c0, u64 c1) {
    u64 *p0;
    s32 i;
    s32 j;
    s32 k;
    s32 t;
    s32 n;
    s32 pw;
    s32 ph;
    s32 nloop;
    s32 offx;
    s32 offy;
    s32 offu;

    if (dv < 0) {
        return p;
    }

    n = 1 << dv;
    pw = SCR_WIDTH * 0x10 >> dv;
    ph = SCR_HEIGHT << (4 - dv);
    nloop = pw / 512;
    offy = 0x70 >> dv;
    offu = dv == 2 ? 0x1400 : 0;
    offx = 0;
    for (i = 0; i < dv; i++) {
        offx += 0x140 >> i;
    }
    offx <<= 4;

    ((u64 *)&p[0])[0] = SCE_GIF_SET_TAG(1, SCE_GS_FALSE, SCE_GS_TRUE, SCE_GS_SET_PRIM(SCE_GS_PRIM_SPRITE, 0, 1, 0, 1, 0, 1, 0, 0), SCE_GIF_PACKED, 1);
    ((u64 *)&p[0])[1] = SCE_GIF_PACKED_AD;
    ((u64 *)&p[1])[0] = scissor;
    ((u64 *)&p[1])[1] = SCE_GS_SCISSOR_1;
    p += 2;

    for (i = 0; i < n; i++, frame++) {
        ((u64 *)&p[0])[0] = SCE_GIF_SET_TAG(1, SCE_GS_FALSE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1);
        ((u64 *)&p[0])[1] = SCE_GIF_PACKED_AD;
        ((u64 *)&p[1])[0] = *frame;
        ((u64 *)&p[1])[1] = SCE_GS_FRAME_1;
        p += 2;

        for (j = 0; j < 2; j++, tex0++) {
            ((u64 *)&p[0])[0] = SCE_GIF_SET_TAG(1, SCE_GS_FALSE, SCE_GS_FALSE, 0, SCE_GIF_REGLIST, 2);
            ((u64 *)&p[0])[1] = SCE_GS_FINISH;
            p0 = (u64 *)(p + 1);
            if (j == 0) {
                p0[0] = c0;
            } else {
                p0[0] = c1;
            }
            p0[1] = *tex0;
            ((u64 *)&p[2])[0] = SCE_GIF_SET_TAG(nloop, SCE_GS_FALSE, SCE_GS_FALSE, 0, SCE_GIF_REGLIST, 4);
            ((u64 *)&p[2])[1] = SCE_GS_UV << 0 | SCE_GS_XYZ2 << 4 | SCE_GS_UV << 8 | SCE_GS_XYZ2 << 12;

            p0 = (u64 *)(p + 3);
            t = 12 - ((i & 1) << 3);
            for (k = 0; k < pw; k += 0x200, p0 += 4) {
                p0[0] = SCE_GS_SET_UV((k >> 1) + t + offx, t + i * ph + (j * (offy << 4)));
                p0[1] = SCE_GS_SET_XYZ2(k + offu, i * (offy << 5), 0x00);
                p0[2] = SCE_GS_SET_UV((k >> 1) + t + offx + 0xFC, ph / 2 + t + i * ph + (j * (offy << 4)));
                p0[3] = SCE_GS_SET_XYZ2(k + offu + 0x1F8, ph + (i * (offy << 5)), 0x00);
            }
            p = (qword *)p0;
        }
    }

    return p;
}

void nkDrawFilterShadeOff(sceGsDrawEnv1 *env1, sceGsDrawEnv1 *env1_d, f32 pow) {
    qword *tag;
    qword *p;
    u64 *p0;
    s32 t;
    u64 c0;
    u64 c1;

    if (pow <= 0.0f) {
        return;
    }
    if (pow > 1.0f) {
        pow = 1.0f;
    }

    tag = SPR_MEM_IDX(0);
    p = SPR_MEM_IDX(1);
    ((u64 *)&p[0])[0] = SCE_GIF_SET_TAG(6, 0, 0, 0, 0, 1);
    ((u64 *)&p[0])[1] = SCE_GIF_PACKED_AD;
    ((u64 *)&p[1])[0] = 0x131000000;
    ((u64 *)&p[1])[1] = SCE_GS_ZBUF_1;
    ((u64 *)&p[2])[0] = 0x30000;
    ((u64 *)&p[2])[1] = SCE_GS_TEST_1;
    ((u64 *)&p[3])[0] = 0;
    ((u64 *)&p[3])[1] = SCE_GS_XYOFFSET_1;
    ((u64 *)&p[4])[0] = 0x80;
    ((u64 *)&p[4])[1] = SCE_GS_TEXA;
    ((u64 *)&p[5])[0] = SCE_GS_SET_TEX1_1(0, 0, 1, 1, 0, 0, 0);
    ((u64 *)&p[5])[1] = SCE_GS_TEX1_1;
    ((u64 *)&p[6])[1] = SCE_GS_TEXFLUSH;

    p = SPR_MEM_IDX(8);
    ((u64 *)&p[0])[0] = 0x2400000000000001;
    ((u64 *)&p[0])[1] = 0x18;

    p0 = SPR_MEM_IDX(9);
    p0[0] = SCE_GS_XYZ2;
    p0[1] = 0x80808080;

    {
        u64 tex0_a[1] = { SCE_GS_SET_TEX0(env1->frame1.FBP << 5, 10, env1->frame1.PSM, 10, 9, 0, 0, 0, 0, 0, 0, 0) };
        u64 tex0_b[2] = {
            SCE_GS_SET_TEX0(0x1680, 10, SCE_GS_PSMCT32, 10, 9, 0, 0, 0, SCE_GS_PSMCT32, 0, 0, 0),
            SCE_GS_SET_TEX0(0x1680, 10, SCE_GS_PSMCT32, 10, 9, 0, 0, 0, SCE_GS_PSMCT32, 0, 0, 0)
        };
        u64 tex0_c[4] = {
            SCE_GS_SET_TEX0(0x1680, 10, SCE_GS_PSMCT32, 10, 9, 0, 0, 0, SCE_GS_PSMCT32, 0, 0, 0),
            SCE_GS_SET_TEX0(0x1680, 10, SCE_GS_PSMCT32, 10, 9, 0, 0, 0, SCE_GS_PSMCT32, 0, 0, 0),
            SCE_GS_SET_TEX0(0x1680, 10, SCE_GS_PSMCT32, 10, 9, 0, 0, 0, SCE_GS_PSMCT32, 0, 0, 0),
            SCE_GS_SET_TEX0(0x1680, 10, SCE_GS_PSMCT32, 10, 9, 0, 0, 0, SCE_GS_PSMCT32, 0, 0, 0)
        };
        u64 tex0_d[8] = {
            SCE_GS_SET_TEX0(0x1680, 10, SCE_GS_PSMCT32, 10, 9, 0, 0, 0, SCE_GS_PSMCT32, 0, 0, 0),
            SCE_GS_SET_TEX0(0x1680, 10, SCE_GS_PSMCT32, 10, 9, 0, 0, 0, SCE_GS_PSMCT32, 0, 0, 0),
            SCE_GS_SET_TEX0(0x1680, 10, SCE_GS_PSMCT32, 10, 9, 0, 0, 0, SCE_GS_PSMCT32, 0, 0, 0),
            SCE_GS_SET_TEX0(0x1680, 10, SCE_GS_PSMCT32, 10, 9, 0, 0, 0, SCE_GS_PSMCT32, 0, 0, 0),
            SCE_GS_SET_TEX0(0x1680, 10, SCE_GS_PSMCT32, 10, 9, 0, 0, 0, SCE_GS_PSMCT32, 0, 0, 0),
            SCE_GS_SET_TEX0(0x1680, 10, SCE_GS_PSMCT32, 10, 9, 0, 0, 0, SCE_GS_PSMCT32, 0, 0, 0),
            SCE_GS_SET_TEX0(0x1680, 10, SCE_GS_PSMCT32, 10, 9, 0, 0, 0, SCE_GS_PSMCT32, 0, 0, 0),
            SCE_GS_SET_TEX0(0x1680, 10, SCE_GS_PSMCT32, 10, 9, 0, 0, 0, SCE_GS_PSMCT32, 0, 0, 0)
        };
        u64 frame_b[2] = {
            SCE_GS_SET_FRAME(0xB4, FRAME_FBW, SCE_GS_PSMCT32, 0),
            SCE_GS_SET_FRAME(0xB4, FRAME_FBW, SCE_GS_PSMCT32, 0),
        };
        u64 frame_c[4] = {
            SCE_GS_SET_FRAME(0xB4, FRAME_FBW, SCE_GS_PSMCT32, 0),
            SCE_GS_SET_FRAME(0xB4, FRAME_FBW, SCE_GS_PSMCT32, 0),
            SCE_GS_SET_FRAME(0xB4, FRAME_FBW, SCE_GS_PSMCT32, 0),
            SCE_GS_SET_FRAME(0xB4, FRAME_FBW, SCE_GS_PSMCT32, 0),
        };
        u64 frame_d[8] = {
            SCE_GS_SET_FRAME(0xB4, FRAME_FBW, SCE_GS_PSMCT32, 0),
            SCE_GS_SET_FRAME(0xB4, FRAME_FBW, SCE_GS_PSMCT32, 0),
            SCE_GS_SET_FRAME(0xB4, FRAME_FBW, SCE_GS_PSMCT32, 0),
            SCE_GS_SET_FRAME(0xB4, FRAME_FBW, SCE_GS_PSMCT32, 0),
            SCE_GS_SET_FRAME(0xB4, FRAME_FBW, SCE_GS_PSMCT32, 0),
            SCE_GS_SET_FRAME(0xB4, FRAME_FBW, SCE_GS_PSMCT32, 0),
            SCE_GS_SET_FRAME(0xB4, FRAME_FBW, SCE_GS_PSMCT32, 0),
            SCE_GS_SET_FRAME(0xB4, FRAME_FBW, SCE_GS_PSMCT32, 0)
        };

        p = SPR_MEM_IDX(10);
        p = make_flt_Div(p, 0, SCE_GS_SET_SCISSOR(0, 0x27F, 0, 0x1BF), tex0_a, frame_b);
        p = make_flt_Div(p, 1, SCE_GS_SET_SCISSOR(0, 0x27F, 0, 0x1BF), tex0_b, frame_c);
        p = make_flt_Div(p, 2, SCE_GS_SET_SCISSOR(0, 0x27F, 0, 0x1BF), tex0_c, frame_d);
        ((u64 *)&p[0])[0] = SCE_GIF_SET_TAG(1, 0, 0, 0, 0, 1);
        ((u64 *)&p[0])[1] = SCE_GIF_PACKED_AD;
        ((u64 *)&p[1])[0] = 0x44;
        ((u64 *)&p[1])[1] = SCE_GS_ALPHA_1;
        p += 2;
        p = make_flt_Acc(p, 2, SCE_GS_SET_SCISSOR(0, 0x27F, 0, 0x1BF), tex0_d, frame_c, 0x80808080, 0x40808080);
        p = make_flt_Acc(p, 1, SCE_GS_SET_SCISSOR(0, 0x27F, 0, 0x1BF), tex0_c, frame_b, 0x80808080, 0x40808080);
        ((u64 *)&p[0])[0] = 0x1000000000000001;
        ((u64 *)&p[0])[1] = SCE_GIF_PACKED_AD;
        ((u64 *)&p[1])[0] = 0x44;
        ((u64 *)&p[1])[1] = SCE_GS_ALPHA_1;
        p += 2;
        c1 = nkCalIntplCol(0x808080, 0x40c0c0c0, pow);
        c0 = c1 >> 24;
        c0 = (c0 << 7) / (0x80 - c0);
        c0 = ((c0 << 24) | (c1 & 0xFFFFFF));
        p = make_flt_Acc(p, 0, SCE_GS_SET_SCISSOR(0, 0x27F, 0, 0xDF), tex0_b, (u64 *)env1, c0, c1);
    }

    ((u64 *)&p[0])[0] = SCE_GIF_SET_TAG(5, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1);
    ((u64 *)&p[0])[1] = SCE_GIF_PACKED_AD;
    ((u64 *)&p[1])[0] = *(u64 *)&env1->frame1;
    ((u64 *)&p[1])[1] = SCE_GS_FRAME_1;
    p += 2;
    ((u64 *)&p[0])[0] = *(u64 *)&env1->zbuf1;
    ((u64 *)&p[0])[1] = SCE_GS_ZBUF_1;
    p++;
    ((u64 *)&p[0])[0] = *(u64 *)&env1->test1;
    ((u64 *)&p[0])[1] = SCE_GS_TEST_1;
    p++;
    ((u64 *)&p[0])[0] = *(u64 *)&env1->xyoffset1;
    ((u64 *)&p[0])[1] = SCE_GS_XYOFFSET_1;
    p++;
    ((u64 *)&p[0])[0] = *(u64 *)&env1->scissor1;
    ((u64 *)&p[0])[1] = SCE_GS_SCISSOR_1;
    p++;

    t = ((u32)p - (u32)tag - 1) >> 4;
    (*tag)[0] = (u32)tag | t;
    (*tag)[1] = 0;
    (*tag)[2] = 0;
    (*tag)[3] = DMAcall | t;
    FlushCache(WRITEBACK_DCACHE);
    sceDmaSend(DmaChGIF, SPR_SRC(tag));
    sceDmaSync(DmaChGIF, 0, 0);
}
