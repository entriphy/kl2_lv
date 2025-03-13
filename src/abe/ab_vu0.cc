#include "abe/ab_vu0.h"

void abRotTransPers(sceVu0IVECTOR v0, sceVu0FMATRIX m0, sceVu0FVECTOR v1) {
    f32 ox = 32767.5f;
    f32 cx = 1.0f / 32767.5f;

    __asm__ volatile(
        "qmtc2      %0, $vf16\n"
        "vmr32.xyzw $vf16, $vf16\n"
        "qmtc2      %0, $vf31\n"
        "vmove.x    $vf16, $vf31\n"
        "vmr32.xyzw $vf16, $vf16\n"
        "qmtc2      %1, $vf31\n"
        "vmove.x    $vf16, $vf31\n"
        "vmr32.xyzw $vf16, $vf16\n"
        "vmr32.xyzw $vf16, $vf16\n"
        "qmtc2      %1, $vf17\n"
        "vmr32.xyzw $vf17, $vf17\n"
        "qmtc2      %1, $vf31\n"
        "vmove.x    $vf17, $vf31\n"
        "vmr32.xyzw $vf17, $vf17\n"
        "qmtc2      %1, $vf31\n"
        "vmove.x    $vf1, $vf31\n"
        "vmr32.xyzw $vf17, $vf17\n"
        "vmr32.xyzw $vf17, $vf17\n"
        "ctc2       $0, $vi18\n"
    : : "r" (*(u32 *)&ox), "r" (*(u32 *)&cx));

    __asm__ volatile(
        "lqc2       $vf2, 0x0(%1)\n"
        "lqc2       $vf4, 0x0(%0)\n"
        "lqc2       $vf5, 0x10(%0)\n"
        "lqc2       $vf6, 0x20(%0)\n"
        "lqc2       $vf7, 0x30(%0)\n"
        "vmulax.xyzw ACC, $vf4, $vf2x\n"
        "vmadday.xyzw ACC, $vf5, $vf2y\n"
        "vmaddaz.xyzw ACC, $vf6, $vf2z\n"
        "vmaddw.xyzw $vf1, $vf7, $vf2w\n"
        "vdiv       Q, $vf0w, $vf1w\n"
        "vwaitq\n"
        "vmulq.xyz  $vf1, $vf1, Q\n"
    : : "r" (m0), "r" (v1));

    __asm__ volatile(
        "vftoi4.xyzw $vf1, $vf1\n"
        "sqc2        $vf1, 0x0(%0)\n"
    : : "r" (v0));
}

void abRotTransPers(sceVu0FVECTOR v0, sceVu0FMATRIX m0, sceVu0FVECTOR v1) {
    f32 ox = 65536.0f;
    f32 cx = 1.0f / ox;

    __asm__ volatile(
        "qmtc2      %0, $vf16\n"
        "vmr32.xyzw $vf16, $vf16\n"
        "qmtc2      %0, $vf31\n"
        "vmove.x    $vf16, $vf31\n"
        "vmr32.xyzw $vf16, $vf16\n"
        "qmtc2      %1, $vf31\n"
        "vmove.x    $vf16, $vf31\n"
        "vmr32.xyzw $vf16, $vf16\n"
        "vmr32.xyzw $vf16, $vf16\n"
        "qmtc2      %1, $vf17\n"
        "vmr32.xyzw $vf17, $vf17\n"
        "qmtc2      %1, $vf31\n"
        "vmove.x    $vf17, $vf31\n"
        "vmr32.xyzw $vf17, $vf17\n"
        "qmtc2      %1, $vf31\n"
        "vmove.x    $vf1, $vf31\n"
        "vmr32.xyzw $vf17, $vf17\n"
        "vmr32.xyzw $vf17, $vf17\n"
        "ctc2       $0, $vi18\n"
    : : "r" (ox), "r" (cx));

    __asm__ volatile(
        "lqc2       $vf2, 0x0(%1)\n"
        "lqc2       $vf4, 0x0(%0)\n"
        "lqc2       $vf5, 0x10(%0)\n"
        "lqc2       $vf6, 0x20(%0)\n"
        "lqc2       $vf7, 0x30(%0)\n"
        "vmulax.xyzw ACC, $vf4, $vf2x\n"
        "vmadday.xyzw ACC, $vf5, $vf2y\n"
        "vmaddaz.xyzw ACC, $vf6, $vf2z\n"
        "vmaddw.xyzw $vf1, $vf7, $vf2w\n"
        "vdiv       Q, $vf0w, $vf1w\n"
        "vwaitq\n"
        "vmulq.xyz  $vf1, $vf1, Q\n"
    : : "r" (m0), "r" (v1));

    __asm__ volatile(
        "sqc2        $vf1, 0x0(%0)\n"
    : : "r" (v0));
}