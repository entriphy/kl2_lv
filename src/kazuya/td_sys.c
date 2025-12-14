#include "kazuya/td_sys.h"
#include "kazuya/bios.h"
#include "kazuya/cvar.h"
#include "kazuya/string.h"
#include "hoshino/h_gamesnd.h"
#include "nakano/gssub.h"
#include "nakano/k_math.h"

GIM_FORM GimForm_PLTA01 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 7, 10, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2601, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 0, 720 },
    { 120, 48 }
};

GIM_FORM GimForm_PLTA02 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 8, 10, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2604, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 120, 720 },
    { 120, 48 }
};

GIM_FORM GimForm_PLTA03 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 10, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2605, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 240, 632 },
    { 240, 28 }
};

GIM_FORM GimForm_PLTA04 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 10, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2610, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 240, 660 },
    { 240, 28 }
};

GIM_FORM GimForm_PLTA05 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 8, 10, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2611, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 0, 692 },
    { 240, 28 }
};

GIM_FORM GimForm_PLTA06 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 10, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2614, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 400, 688 },
    { 100, 28 }
};

GIM_FORM GimForm_PLTA07 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 8, 10, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2615, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 0, 524 },
    { 180, 48 }
};

GIM_FORM GimForm_PLTA08 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 10, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2602, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 180, 524 },
    { 180, 48 }
};

GIM_FORM GimForm_PLTA09 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 8, 10, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2603, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 0, 572 },
    { 240, 60 }
};

GIM_FORM GimForm_PLTA10 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 10, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2606, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 240, 572 },
    { 240, 60 }
};

GIM_FORM GimForm_PLTA11 = {
    SCE_GS_SET_TEX0(0x2640, 10, SCE_GS_PSMT4, 10, 8, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2827, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 240, 178 },
    { 320, 48 }
};

GIM_FORM GimForm_PLTA12 = {
    SCE_GS_SET_TEX0(0x2640, 10, SCE_GS_PSMT4, 10, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2832, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 240, 226 },
    { 320, 48 }
};

GIM_FORM GimForm_PLTB01 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2607, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 400, 400 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTB02 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2607, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 400, 384 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTB03 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2607, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 384, 400 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTB04 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2607, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 416, 400 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTB05 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2607, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 400, 416 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTB06 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2607, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 384, 384 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTB07 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2607, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 416, 384 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTB08 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2607, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 384, 416 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTB09 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2607, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 416, 416 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTC01 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2612, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 448, 400 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTC02 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2612, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 448, 384 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTC03 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2612, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 432, 400 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTC04 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2612, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 464, 400 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTC05 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2612, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 448, 416 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTC06 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2612, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 432, 384 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTC07 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2612, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 464, 384 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTC08 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2612, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 432, 416 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTC09 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2612, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 464, 416 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTD01 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2613, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 400, 448 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTD02 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2613, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 400, 432 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTD03 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2613, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 384, 448 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTD04 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2613, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 416, 448 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTD05 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2613, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 400, 464 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTD06 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2613, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 384, 432 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTD07 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2613, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 416, 432 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTD08 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2613, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 384, 464 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTD09 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2613, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 416, 464 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTE01 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2635, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 448, 448 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTE02 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2635, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 448, 432 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTE03 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2635, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 432, 448 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTE04 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2635, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 464, 448 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTE05 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2635, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 448, 464 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTE06 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2635, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 432, 432 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTE07 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2635, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 464, 432 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTE08 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2635, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 432, 464 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTE09 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2635, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 464, 464 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTF01 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2622, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 352, 400 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTF02 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2622, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 352, 384 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTF03 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2622, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 336, 400 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTF04 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2622, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 368, 400 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTF05 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2622, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 352, 416 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTF06 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2622, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 336, 384 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTF07 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2622, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 368, 384 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTF08 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2622, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 336, 416 },
    { 16, 16 }
};

GIM_FORM GimForm_PLTF09 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2622, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 368, 416 },
    { 16, 16 }
};

GIM_FORM GimForm_SEL0000 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 10, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2623, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 360, 528 },
    { 152, 44 }
};

GIM_FORM GimForm_SEL0001 = {
    SCE_GS_SET_TEX0(0x2640, 6, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x27C1, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 160, 344 },
    { 160, 44 }
};

GIM_FORM GimForm_SEL0002 = {
    SCE_GS_SET_TEX0(0x2640, 6, SCE_GS_PSMT4, 8, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x27C4, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 0, 344 },
    { 160, 44 }
};

GIM_FORM GimForm_SEL0003 = {
    SCE_GS_SET_TEX0(0x2640, 6, SCE_GS_PSMT4, 9, 7, SCE_GS_TRUE, SCE_GS_MODULATE, 0x27C5, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 200, 48 },
    { 120, 32 }
};

GIM_FORM GimForm_SEL0005 = {
    SCE_GS_SET_TEX0(0x2640, 6, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x27D0, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 0, 216 },
    { 360, 56 }
};

GIM_FORM GimForm_SEL0006 = {
    SCE_GS_SET_TEX0(0x2640, 6, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x27D1, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 0, 272 },
    { 360, 44 }
};

GIM_FORM GimForm_SEL0007 = {
    SCE_GS_SET_TEX0(0x2640, 6, SCE_GS_PSMT4, 9, 6, SCE_GS_TRUE, SCE_GS_MODULATE, 0x27D4, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 200, 0 },
    { 164, 48 }
};

GIM_FORM GimForm_SEL0008 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 10, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2626, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 364, 716 },
    { 100, 32 }
};

GIM_FORM GimForm_SEL0010 = {
    SCE_GS_SET_TEX0(0x2640, 6, SCE_GS_PSMT4, 8, 7, SCE_GS_TRUE, SCE_GS_MODULATE, 0x27C3, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 120, 0 },
    { 80, 80 }
};

GIM_FORM GimForm_SEL0016 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 10, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2627, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 240, 720 },
    { 124, 44 }
};

GIM_FORM GimForm_SEL0019 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2616, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 300, 480 },
    { 88, 28 }
};

GIM_FORM GimForm_SEL0020 = {
    SCE_GS_SET_TEX0(0x2640, 6, SCE_GS_PSMT4, 8, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x27DD, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 0, 432 },
    { 256, 32 }
};

GIM_FORM GimForm_SEL0100 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2617, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 448, 340 },
    { 16, 16 }
};

GIM_FORM GimForm_SEL0101 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2608, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 464, 340 },
    { 16, 16 }
};

GIM_FORM GimForm_SEL0102 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2609, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 480, 340 },
    { 16, 16 }
};

GIM_FORM GimForm_SEL0103 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x260C, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 368, 340 },
    { 32, 12 }
};

GIM_FORM GimForm_SEL0104 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x260D, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 400, 340 },
    { 12, 12 }
};

GIM_FORM GimForm_SEL0105 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2618, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 424, 340 },
    { 12, 12 }
};

GIM_FORM GimForm_SEL0106 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2619, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 436, 340 },
    { 12, 12 }
};

GIM_FORM GimForm_SEL0107 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x261C, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 480, 448 },
    { 32, 24 }
};

GIM_FORM GimForm_SEL0111 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x260E, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 300, 372 },
    { 20, 20 }
};

GIM_FORM GimForm_SEL0112 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x260F, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 480, 472 },
    { 32, 24 }
};

GIM_FORM GimForm_SEL0113 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2630, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 300, 392 },
    { 20, 20 }
};

GIM_FORM GimForm_SEL0114 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2631, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 496, 340 },
    { 16, 16 }
};

GIM_FORM GimForm_SEL0115 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2634, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 412, 340 },
    { 12, 12 }
};

GIM_FORM GimForm_SEL0400 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2621, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 324, 340 },
    { 24, 32 }
};

GIM_FORM GimForm_SEL0401 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2624, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 300, 340 },
    { 24, 32 }
};

GIM_FORM GimForm_HANE01 = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2600, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 480, 384 },
    { 32, 32 }
};

GIM_FORM GimForm_ZANKI = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2620, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 480, 416 },
    { 32, 32 }
};

GIM_FORM GimForm_LOGO = {
    SCE_GS_SET_TEX0(0x2F80, 10, SCE_GS_PSMT8, 10, 9, SCE_GS_TRUE, SCE_GS_MODULATE, 0x3340, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 0, 0 },
    { 592, 384 }
};

GIM_FORM GimForm_PBYNAM = {
    SCE_GS_SET_TEX0(0x2A20, 12, SCE_GS_PSMT4, 9, 10, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2F61, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 0, 768 },
    { 384, 96 }
};

GIM_FORM GimForm_CHR_SLASH = {
    SCE_GS_SET_TEX0(0x2300, 8, SCE_GS_PSMT4, 9, 10, SCE_GS_TRUE, SCE_GS_MODULATE, 0x261E, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 192, 438 },
    { 12, 14 }
};

GIM_FORM GimForm_MOM0007 = {
    SCE_GS_SET_TEX0(0x2640, 10, SCE_GS_PSMT4, 9, 8, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2834, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 240, 120 },
    { 32, 32 }
};

GIM_FORM GimForm_MOM0008 = {
    SCE_GS_SET_TEX0(0x2640, 10, SCE_GS_PSMT4, 9, 8, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2835, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 272, 120 },
    { 32, 32 }
};

GIM_FORM GimForm_MOM0009 = {
    SCE_GS_SET_TEX0(0x2640, 10, SCE_GS_PSMT4, 9, 8, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2822, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 304, 120 },
    { 32, 32 }
};

GIM_FORM GimForm_MOM0010 = {
    SCE_GS_SET_TEX0(0x2640, 10, SCE_GS_PSMT4, 9, 8, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2823, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 336, 120 },
    { 32, 32 }
};

GIM_FORM GimForm_KUMO1 = {
    SCE_GS_SET_TEX0(0x27E0, 4, SCE_GS_PSMT8, 8, 8, SCE_GS_TRUE, SCE_GS_MODULATE, 0x28E0, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 0, 0 },
    { 256, 256 }
};

GIM_FORM GimForm_KUMO2 = {
    SCE_GS_SET_TEX0(0x2900, 4, SCE_GS_PSMT8, 8, 8, SCE_GS_TRUE, SCE_GS_MODULATE, 0x2A00, SCE_GS_PSMCT32, SCE_GS_FALSE, 0x00, 1),
    { 0, 0 },
    { 256, 256 }
};

GIM_FORM *GimForms[] = {
    &GimForm_PLTA01,
    &GimForm_PLTA02,
    &GimForm_PLTA03,
    &GimForm_PLTA04,
    &GimForm_PLTA05,
    &GimForm_PLTA06,
    &GimForm_PLTA07,
    &GimForm_PLTA08,
    &GimForm_PLTA09,
    &GimForm_PLTA10,
    &GimForm_PLTA11,
    &GimForm_PLTA12,
    &GimForm_PLTB01,
    &GimForm_PLTB02,
    &GimForm_PLTB03,
    &GimForm_PLTB04,
    &GimForm_PLTB05,
    &GimForm_PLTB06,
    &GimForm_PLTB07,
    &GimForm_PLTB08,
    &GimForm_PLTB09,
    &GimForm_PLTC01,
    &GimForm_PLTC02,
    &GimForm_PLTC03,
    &GimForm_PLTC04,
    &GimForm_PLTC05,
    &GimForm_PLTC06,
    &GimForm_PLTC07,
    &GimForm_PLTC08,
    &GimForm_PLTC09,
    &GimForm_PLTD01,
    &GimForm_PLTD02,
    &GimForm_PLTD03,
    &GimForm_PLTD04,
    &GimForm_PLTD05,
    &GimForm_PLTD06,
    &GimForm_PLTD07,
    &GimForm_PLTD08,
    &GimForm_PLTD09,
    &GimForm_PLTE01,
    &GimForm_PLTE02,
    &GimForm_PLTE03,
    &GimForm_PLTE04,
    &GimForm_PLTE05,
    &GimForm_PLTE06,
    &GimForm_PLTE07,
    &GimForm_PLTE08,
    &GimForm_PLTE09,
    &GimForm_PLTF01,
    &GimForm_PLTF02,
    &GimForm_PLTF03,
    &GimForm_PLTF04,
    &GimForm_PLTF05,
    &GimForm_PLTF06,
    &GimForm_PLTF07,
    &GimForm_PLTF08,
    &GimForm_PLTF09,
    &GimForm_SEL0000,
    &GimForm_SEL0001,
    &GimForm_SEL0002,
    &GimForm_SEL0003,
    &GimForm_SEL0005,
    &GimForm_SEL0006,
    &GimForm_SEL0007,
    &GimForm_SEL0008,
    &GimForm_SEL0010,
    &GimForm_SEL0016,
    &GimForm_SEL0019,
    &GimForm_SEL0020,
    &GimForm_SEL0100,
    &GimForm_SEL0101,
    &GimForm_SEL0102,
    &GimForm_SEL0103,
    &GimForm_SEL0104,
    &GimForm_SEL0105,
    &GimForm_SEL0106,
    &GimForm_SEL0107,
    &GimForm_SEL0111,
    &GimForm_SEL0112,
    &GimForm_SEL0113,
    &GimForm_SEL0114,
    &GimForm_SEL0115,
    &GimForm_SEL0400,
    &GimForm_SEL0401,
    &GimForm_HANE01,
    &GimForm_ZANKI,
    &GimForm_LOGO,
    &GimForm_PBYNAM,
    &GimForm_CHR_SLASH,
    &GimForm_MOM0007,
    &GimForm_MOM0008,
    &GimForm_MOM0009,
    &GimForm_MOM0010,
    &GimForm_KUMO1,
    &GimForm_KUMO2,
};

PARA_DC_STD ParaDcStd_Ttl_00 = { { 10, 14 }, STR_TITLE_00 };
PARA_DC_STD ParaDcStd_Ttl_01 = { { 10, 14 }, STR_TITLE_01 };
PARA_DC_STD ParaDcStd_Fil_04 = { { 10, 14 }, STR_COMMON_00 };
PARA_DC_STD ParaDcStd_Fil_05 = { { 10, 14 }, STR_COMMON_01 };
PARA_DC_STD ParaDcStd_Fil_06 = { { 10, 14 }, STR_DATA_04 };
PARA_DC_STD ParaDcStd_Fil_07 = { { 10, 14 }, STR_DATA_05 };
PARA_DC_STD ParaDcStd_Fil_08 = { { 10, 14 }, STR_DATA_06 };
PARA_DC_STD ParaDcStd_Fil_09 = { { 10, 14 }, STR_DATA_07 };
PARA_DC_STD ParaDcStd_Opt_00 = { { 10, 14 }, STR_OPTION_00 };
PARA_DC_STD ParaDcStd_Opt_01 = { { 10, 14 }, STR_OPTION_01 };
PARA_DC_STD ParaDcStd_Opt_02 = { { 10, 14 }, STR_OPTION_02 };
PARA_DC_STD ParaDcStd_Opt_03 = { { 10, 14 }, STR_OPTION_03 };
PARA_DC_STD ParaDcStd_Opt_04 = { { 10, 14 }, STR_OPTION_04 };
PARA_DC_STD ParaDcStd_Opt_05 = { { 10, 14 }, STR_OPTION_05 };
PARA_DC_STD ParaDcStd_Opt_06 = { { 10, 14 }, STR_OPTION_06 };
PARA_DC_STD ParaDcStd_Opt_07 = { { 10, 14 }, STR_OPTION_07 };
PARA_DC_STD ParaDcStd_Opt_08 = { { 10, 14 }, STR_OPTION_08 };
PARA_DC_STD ParaDcStd_Wmp_00 = { { 10, 14 }, STR_MAP_00 };
PARA_DC_STD ParaDcStd_Wmp_01 = { { 10, 14 }, STR_MAP_01 };
PARA_DC_STD ParaDcStd_Wmp_02 = { { 10, 14 }, STR_MAP_02 };
PARA_DC_STD ParaDcStd_Gam_00 = { { 10, 14 }, STR_MAP_00 };
PARA_DC_STD ParaDcStd_Gam_01 = { { 10, 14 }, STR_PAUSE_00 };
PARA_DC_STD ParaDcStd_Gam_02 = { { 10, 14 }, STR_PAUSE_01 };
PARA_DC_STD ParaDcStd_Gam_03 = { { 10, 14 }, STR_PAUSE_02 };
PARA_DC_STD ParaDcStd_Gam_04 = { { 10, 14 }, STR_OVER_00 };
PARA_DC_STD ParaDcStd_Gam_05 = { { 10, 14 }, STR_OVER_01 };
PARA_DC_STD ParaDcStd_Mom_00 = { { 10, 14 }, STR_MOMMET_01 };
PARA_DC_STD ParaDcStd_Mom_01 = { { 10, 14 }, STR_MOMMET_03 };
PARA_DC_STD ParaDcStd_Mom_02 = { { 10, 14 }, STR_MOMMET_02 };
PARA_DC_STD ParaDcStd_Mom_03 = { { 10, 14 }, STR_MOMMET_04 };
PARA_DC_STD ParaDcStd_Pup_00 = { { 10, 14 }, STR_PUPPET_65 };
PARA_DC_STD ParaDcStd_Pup_01 = { { 10, 14 }, STR_CHIMEI_00 };
PARA_DC_STD ParaDcStd_Pup_02 = { { 10, 14 }, STR_CHIMEI_25 };
PARA_DC_STD ParaDcStd_Pup_03 = { { 10, 14 }, STR_CHIMEI_01 };
PARA_DC_STD ParaDcStd_Pup_04 = { { 10, 14 }, STR_CHIMEI_19 };
PARA_DC_STD ParaDcStd_Pup_05 = { { 10, 14 }, STR_CHIMEI_20 };
PARA_DC_STD ParaDcStd_Pup_06 = { { 10, 14 }, STR_CHIMEI_02 };
PARA_DC_STD ParaDcStd_Pup_07 = { { 10, 14 }, STR_CHIMEI_03 };
PARA_DC_STD ParaDcStd_Pup_08 = { { 10, 14 }, STR_CHIMEI_21 };
PARA_DC_STD ParaDcStd_Pup_09 = { { 10, 14 }, STR_CHIMEI_04 };
PARA_DC_STD ParaDcStd_Pup_10 = { { 10, 14 }, STR_CHIMEI_05 };
PARA_DC_STD ParaDcStd_Pup_11 = { { 10, 14 }, STR_CHIMEI_06 };
PARA_DC_STD ParaDcStd_Pup_12 = { { 10, 14 }, STR_CHIMEI_07 };
PARA_DC_STD ParaDcStd_Pup_13 = { { 10, 14 }, STR_CHIMEI_08 };
PARA_DC_STD ParaDcStd_Pup_14 = { { 10, 14 }, STR_CHIMEI_09 };
PARA_DC_STD ParaDcStd_Pup_15 = { { 10, 14 }, STR_CHIMEI_22 };
PARA_DC_STD ParaDcStd_Pup_16 = { { 10, 14 }, STR_CHIMEI_10 };
PARA_DC_STD ParaDcStd_Pup_17 = { { 10, 14 }, STR_CHIMEI_11 };
PARA_DC_STD ParaDcStd_Pup_18 = { { 10, 14 }, STR_CHIMEI_12 };
PARA_DC_STD ParaDcStd_Pup_19 = { { 10, 14 }, STR_CHIMEI_23 };
PARA_DC_STD ParaDcStd_Pup_20 = { { 10, 14 }, STR_CHIMEI_13 };
PARA_DC_STD ParaDcStd_Pup_21 = { { 10, 14 }, STR_CHIMEI_14 };
PARA_DC_STD ParaDcStd_Pup_22 = { { 10, 14 }, STR_CHIMEI_15 };
PARA_DC_STD ParaDcStd_Pup_23 = { { 10, 14 }, STR_CHIMEI_24 };
PARA_DC_STD ParaDcStd_Pup_24 = { { 10, 14 }, STR_PUPPET_66 };
PARA_DC_STD ParaDcStd_Tri_00 = { { 8, 4 }, STR_CHIMEI_00 };
PARA_DC_STD ParaDcStd_Tri_01 = { { 8, 4 }, STR_CHIMEI_03 };
PARA_DC_GIM ParaDcGim_Etc_00 = {
    { 24, 7 }, STR_OPTION_09,
    { 8, 7 }, GIM_SEL0100
};

PARA_DC_GIM ParaDcGim_Etc_01 = {
    { 24, 7 }, STR_ETC_03,
    { 8, 7 }, GIM_SEL0101
};

PARA_DC_GIM ParaDcGim_Etc_02 = {
    { 24, 7 }, STR_ETC_26,
    { 8, 7 }, GIM_SEL0100
};

PARA_DC_GIM ParaDcGim_Etc_03 = {
    { 24, 7 }, STR_ETC_01,
    { 8, 7 }, GIM_SEL0102
};

PARA_DC_GIM ParaDcGim_Etc_04 = {
    { 24, 7 }, STR_ETC_01,
    { 8, 7 }, GIM_SEL0115
};

PARA_DC_GIM ParaDcGim_Etc_05 = {
    { 24, 7 }, STR_ETC_01,
    { 8, 7 }, GIM_SEL0104
};

PARA_DC_GIM ParaDcGim_Etc_06 = {
    { 24, 7 }, STR_ETC_07,
    { 4, 4 }, GIM_SEL0111
};

PARA_DC_GIM ParaDcGim_Etc_07 = {
    { 24, 7 }, STR_ETC_05,
    { 8, 7 }, GIM_SEL0100
};

PARA_DC_GIM ParaDcGim_Etc_08 = {
    { 24, 7 }, STR_ETC_06,
    { 8, 7 }, GIM_SEL0114
};

PARA_DC_GIM ParaDcGim_Etc_09 = {
    { 24, 7 }, STR_ETC_02,
    { 8, 7 }, GIM_SEL0103
};

PARA_DC_GIM ParaDcGim_Etc_10 = {
    { 24, 7 }, STR_ETC_01,
    { 8, 7 }, GIM_SEL0104
};

PARA_DC_EX0 ParaDcEx0_Stt_00 = { { 8, 8 }, STR_STAGE_00 };
PARA_DC_EX0 ParaDcEx0_Stt_01 = { { 8, 8 }, STR_STAGE_01 };
PARA_DC_EX0 ParaDcEx0_Stt_02 = { { 8, 8 }, STR_STAGE_02 };
PARA_DC_EX0 ParaDcEx0_Stt_03 = { { 8, 8 }, STR_STAGE_03 };
PARA_DC_EX0 ParaDcEx0_Stt_04 = { { 8, 8 }, STR_STAGE_04 };
PARA_DC_EX0 ParaDcEx0_Stt_05 = { { 8, 8 }, STR_STAGE_05 };
PARA_DC_EX0 ParaDcEx0_Stt_06 = { { 8, 8 }, STR_STAGE_06 };
PARA_DC_EX0 ParaDcEx0_Stt_07 = { { 8, 8 }, STR_STAGE_07 };
PARA_DC_EX0 ParaDcEx0_Stt_08 = { { 8, 8 }, STR_STAGE_08 };
PARA_DC_EX0 ParaDcEx0_Stt_09 = { { 8, 8 }, STR_STAGE_09 };
PARA_DC_EX0 ParaDcEx0_Stt_10 = { { 8, 8 }, STR_STAGE_10 };
PARA_DC_EX0 ParaDcEx0_Stt_11 = { { 8, 8 }, STR_STAGE_11 };
PARA_DC_EX0 ParaDcEx0_Stt_12 = { { 8, 8 }, STR_STAGE_12 };
PARA_DC_EX0 ParaDcEx0_Stt_13 = { { 8, 8 }, STR_STAGE_13 };
PARA_DC_EX0 ParaDcEx0_Stt_14 = { { 8, 8 }, STR_STAGE_14 };
PARA_DC_EX0 ParaDcEx0_Stt_15 = { { 8, 8 }, STR_STAGE_15 };
PARA_DC_EX0 ParaDcEx0_Stt_16 = { { 8, 8 }, STR_STAGE_16 };
PARA_DC_EX0 ParaDcEx0_Stt_17 = { { 8, 8 }, STR_STAGE_17 };
PARA_DC_EX0 ParaDcEx0_Stt_18 = { { 8, 8 }, STR_STAGE_18 };
PARA_DC_EX1 ParaDcEx1_Gjk_00 = { { 10, 14 }, STR_BOSS_00 };
PARA_DC_EX1 ParaDcEx1_Gjk_01 = { { 10, 14 }, STR_BOSS_01 };
PARA_DC_EX1 ParaDcEx1_Gjk_02 = { { 10, 14 }, STR_BOSS_02 };
PARA_DC_EX1 ParaDcEx1_Gjk_03 = { { 10, 14 }, STR_BOSS_03 };
PARA_DC_EX1 ParaDcEx1_Gjk_04 = { { 10, 14 }, STR_BOSS_04 };
PARA_DC_EX1 ParaDcEx1_Gjk_05 = { { 10, 14 }, STR_BOSS_05 };
PARA_DC_EX2 ParaDcEx2_Fil_00 = {
    { 10, 14 },
    { STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY },
};

PARA_DC_EX2 ParaDcEx2_Fil_01 = {
    { 10, 14 },
    { STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY },
};

PARA_DC_EX2 ParaDcEx2_Fil_02 = {
    { 10, 14 },
    { STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY },
};

PARA_DC_EX2 ParaDcEx2_Fil_03 = {
    { 10, 14 },
    { STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY, STR_DUMMY },
};

PARA_DC_EX3 ParaDcEx3_Pup_25 = {
    { 10, 14 },
    STR_PUPPET_00,
    { 1, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_26 = {
    { 10, 14 },
    STR_PUPPET_01,
    { 3, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_27 = {
    { 10, 14 },
    STR_PUPPET_02,
    { 4, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_28 = {
    { 10, 14 },
    STR_PUPPET_03,
    { 6, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_29 = {
    { 10, 14 },
    STR_PUPPET_04,
    { 11, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_30 = {
    { 10, 14 },
    STR_PUPPET_05,
    { 26, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_31 = {
    { 10, 14 },
    STR_PUPPET_06,
    { 36, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_32 = {
    { 10, 14 },
    STR_PUPPET_07,
    { 46, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_33 = {
    { 10, 14 },
    STR_PUPPET_08,
    { 7, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_34 = {
    { 10, 14 },
    STR_PUPPET_09,
    { 8, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_35 = {
    { 10, 14 },
    STR_PUPPET_10,
    { 9, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_36 = {
    { 10, 14 },
    STR_PUPPET_11,
    { 10, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_37 = {
    { 10, 14 },
    STR_PUPPET_12,
    { 12, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_38 = {
    { 10, 14 },
    STR_PUPPET_13,
    { 24, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_39 = {
    { 10, 14 },
    STR_PUPPET_14,
    { 25, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_40 = {
    { 10, 14 },
    STR_PUPPET_15,
    { 13, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_41 = {
    { 10, 14 },
    STR_PUPPET_16,
    { 14, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_42 = {
    { 10, 14 },
    STR_PUPPET_17,
    { 15, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_43 = {
    { 10, 14 },
    STR_PUPPET_18,
    { 16, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_44 = {
    { 10, 14 },
    STR_PUPPET_19,
    { 17, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_45 = {
    { 10, 14 },
    STR_PUPPET_20,
    { 18, 19 },
};

PARA_DC_EX3 ParaDcEx3_Pup_46 = {
    { 10, 14 },
    STR_PUPPET_22,
    { 20, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_47 = {
    { 10, 14 },
    STR_PUPPET_23,
    { 21, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_48 = {
    { 10, 14 },
    STR_PUPPET_20,
    { 22, 23 },
};

PARA_DC_EX3 ParaDcEx3_Pup_49 = {
    { 10, 14 },
    STR_PUPPET_24,
    { 27, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_50 = {
    { 10, 14 },
    STR_PUPPET_25,
    { 32, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_51 = {
    { 10, 14 },
    STR_PUPPET_26,
    { 33, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_52 = {
    { 10, 14 },
    STR_PUPPET_27,
    { 28, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_53 = {
    { 10, 14 },
    STR_PUPPET_28,
    { 29, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_54 = {
    { 10, 14 },
    STR_PUPPET_29,
    { 30, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_55 = {
    { 10, 14 },
    STR_PUPPET_30,
    { 31, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_56 = {
    { 10, 14 },
    STR_PUPPET_31,
    { 34, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_57 = {
    { 10, 14 },
    STR_PUPPET_32,
    { 35, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_58 = {
    { 10, 14 },
    STR_PUPPET_33,
    { 37, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_59 = {
    { 10, 14 },
    STR_PUPPET_34,
    { 38, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_60 = {
    { 10, 14 },
    STR_PUPPET_35,
    { 39, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_61 = {
    { 10, 14 },
    STR_PUPPET_36,
    { 40, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_62 = {
    { 10, 14 },
    STR_PUPPET_37,
    { 41, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_63 = {
    { 10, 14 },
    STR_PUPPET_38,
    { 42, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_64 = {
    { 10, 14 },
    STR_PUPPET_39,
    { 43, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_65 = {
    { 10, 14 },
    STR_PUPPET_41,
    { 44, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_66 = {
    { 10, 14 },
    STR_PUPPET_42,
    { 45, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_67 = {
    { 10, 14 },
    STR_PUPPET_43,
    { 47, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_68 = {
    { 10, 14 },
    STR_PUPPET_44,
    { 51, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_69 = {
    { 10, 14 },
    STR_PUPPET_45,
    { 53, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_70 = {
    { 10, 14 },
    STR_PUPPET_46,
    { 56, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_71 = {
    { 10, 14 },
    STR_PUPPET_47,
    { 57, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_72 = {
    { 10, 14 },
    STR_PUPPET_48,
    { 58, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_73 = {
    { 10, 14 },
    STR_PUPPET_49,
    { 59, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_74 = {
    { 10, 14 },
    STR_PUPPET_51,
    { 61, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_75 = {
    { 10, 14 },
    STR_PUPPET_52,
    { 62, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_76 = {
    { 10, 14 },
    STR_PUPPET_53,
    { 63, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_77 = {
    { 10, 14 },
    STR_PUPPET_54,
    { 64, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_78 = {
    { 10, 14 },
    STR_PUPPET_55,
    { 65, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_79 = {
    { 10, 14 },
    STR_PUPPET_56,
    { 66, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_80 = {
    { 10, 14 },
    STR_PUPPET_57,
    { 67, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_81 = {
    { 10, 14 },
    STR_PUPPET_58,
    { 68, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_82 = {
    { 10, 14 },
    STR_PUPPET_59,
    { 69, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_83 = {
    { 10, 14 },
    STR_PUPPET_60,
    { 70, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_84 = {
    { 10, 14 },
    STR_PUPPET_61,
    { 71, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_85 = {
    { 10, 14 },
    STR_PUPPET_62,
    { 72, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_86 = {
    { 10, 14 },
    STR_PUPPET_63,
    { 73, 0 },
};

PARA_DC_EX3 ParaDcEx3_Pup_87 = {
    { 10, 14 },
    STR_PUPPET_64,
    { 74, 0 },
};

GIM_FORM *PlateForm_0[2] = { &GimForm_PLTA08, &GimForm_PLTA07 };
GIM_FORM *PlateForm_1[2] = { &GimForm_PLTA06, &GimForm_PLTA06 };
GIM_FORM *PlateForm_2[2] = { &GimForm_PLTA04, &GimForm_PLTA03 };
GIM_FORM *PlateForm_3[2] = { &GimForm_PLTA05, &GimForm_PLTA03 };
GIM_FORM *PlateForm_4[2] = { &GimForm_PLTA10, &GimForm_PLTA09 };
GIM_FORM *PlateForm_5[2] = { &GimForm_PLTA02, &GimForm_PLTA01 };
GIM_FORM *PlateForm_6[2] = { &GimForm_PLTA10, &GimForm_PLTA09 };
GIM_FORM *PlateForm_7[2] = { &GimForm_PLTA12, &GimForm_PLTA11 };
GIM_FORM **PlateForms[] = {
    PlateForm_0,
    PlateForm_1,
    PlateForm_2,
    PlateForm_3,
    PlateForm_4,
    PlateForm_5,
    PlateForm_6,
    PlateForm_7,
};

KZCOLOR FontColor_0[2] = {
    { 0x46, 0x23, 0x0A, 0x80 },
    { 0x32, 0x1B, 0x0A, 0x80 },
};

KZCOLOR FontColor_1[2] = {
    { 0x4B, 0x32, 0x19, 0x80 },
    { 0x32, 0x1B, 0x0A, 0x80 },
};

PLATE_INFO PlateInfo_Ttl_00 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NORMAL,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Ttl_00
};

PLATE_INFO PlateInfo_Ttl_01 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NORMAL,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Ttl_01
};

PLATE_INFO PlateInfo_Fil_00 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_LONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Fil, &ParaDcEx2_Fil_00
};

PLATE_INFO PlateInfo_Fil_01 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_LONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Fil, &ParaDcEx2_Fil_01
};

PLATE_INFO PlateInfo_Fil_02 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_LONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Fil, &ParaDcEx2_Fil_02
};

PLATE_INFO PlateInfo_Fil_03 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_LONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Fil, &ParaDcEx2_Fil_03
};

PLATE_INFO PlateInfo_Fil_04 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NORMAL,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Fil_04
};

PLATE_INFO PlateInfo_Fil_05 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NORMAL,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Fil_05
};

PLATE_INFO PlateInfo_Fil_06 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_LONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Fil_06
};

PLATE_INFO PlateInfo_Fil_07 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_LONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Fil_07
};

PLATE_INFO PlateInfo_Fil_08 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_LONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Fil_08
};

PLATE_INFO PlateInfo_Fil_09 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_LONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Fil_09
};

PLATE_INFO PlateInfo_Opt_00 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_LONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Opt_00
};

PLATE_INFO PlateInfo_Opt_01 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_LONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Opt_01
};

PLATE_INFO PlateInfo_Opt_02 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_LONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Opt_02
};

PLATE_INFO PlateInfo_Opt_03 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_LONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Opt_03
};

PLATE_INFO PlateInfo_Opt_04 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_LONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Opt_04
};

PLATE_INFO PlateInfo_Opt_05 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_LONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Opt_05
};

PLATE_INFO PlateInfo_Opt_06 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_LONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Opt_06
};

PLATE_INFO PlateInfo_Opt_07 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_LONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Opt_07
};

PLATE_INFO PlateInfo_Opt_08 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_LONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Opt_08
};

PLATE_INFO PlateInfo_Etc_00 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_PADEXP,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Gim, &ParaDcGim_Etc_00
};

PLATE_INFO PlateInfo_Etc_01 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_PADEXP,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Gim, &ParaDcGim_Etc_01
};

PLATE_INFO PlateInfo_Etc_02 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_PADEXP,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Gim, &ParaDcGim_Etc_02
};

PLATE_INFO PlateInfo_Etc_03 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_PADEXP,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Gim, &ParaDcGim_Etc_03
};

PLATE_INFO PlateInfo_Etc_04 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_PADEXP,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Gim, &ParaDcGim_Etc_04
};

PLATE_INFO PlateInfo_Etc_05 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_PADEXP,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Gim, &ParaDcGim_Etc_05
};

PLATE_INFO PlateInfo_Etc_06 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_PADEXP,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Gim, &ParaDcGim_Etc_06
};

PLATE_INFO PlateInfo_Etc_07 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_PADEXP,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Gim, &ParaDcGim_Etc_07
};

PLATE_INFO PlateInfo_Etc_08 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_PADEXP,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Gim, &ParaDcGim_Etc_08
};

PLATE_INFO PlateInfo_Etc_09 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_PADEXP,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Gim, &ParaDcGim_Etc_09
};

PLATE_INFO PlateInfo_Etc_10 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_PADEXP,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Gim, &ParaDcGim_Etc_10
};

PLATE_INFO PlateInfo_Wmp_00 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_00
};

PLATE_INFO PlateInfo_Wmp_01 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_01
};

PLATE_INFO PlateInfo_Wmp_02 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_02
};

PLATE_INFO PlateInfo_Wmp_03 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_03
};

PLATE_INFO PlateInfo_Wmp_04 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_04
};

PLATE_INFO PlateInfo_Wmp_05 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_05
};

PLATE_INFO PlateInfo_Wmp_06 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_06
};

PLATE_INFO PlateInfo_Wmp_07 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_07
};

PLATE_INFO PlateInfo_Wmp_08 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW_EX,
    FontColor_1,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_16
};

PLATE_INFO PlateInfo_Wmp_09 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW_EX,
    FontColor_1,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_17
};

PLATE_INFO PlateInfo_Wmp_10 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_08
};

PLATE_INFO PlateInfo_Wmp_11 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_09
};

PLATE_INFO PlateInfo_Wmp_12 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_10
};

PLATE_INFO PlateInfo_Wmp_13 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_11
};

PLATE_INFO PlateInfo_Wmp_14 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_12
};

PLATE_INFO PlateInfo_Wmp_15 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_13
};

PLATE_INFO PlateInfo_Wmp_16 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_14
};

PLATE_INFO PlateInfo_Wmp_17 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_15
};

PLATE_INFO PlateInfo_Wmp_18 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROWx2_EX,
    FontColor_1,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Stt, &ParaDcEx0_Stt_18
};

PLATE_INFO PlateInfo_Wmp_20 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NORMAL,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Wmp_00
};

PLATE_INFO PlateInfo_Wmp_21 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NORMAL,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Wmp_01
};

PLATE_INFO PlateInfo_Wmp_22 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NORMAL,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Wmp_02
};

PLATE_INFO PlateInfo_Gam_00 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NORMAL,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Gam_00
};

PLATE_INFO PlateInfo_Gam_01 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NORMAL,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Gam_01
};

PLATE_INFO PlateInfo_Gam_02 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NORMAL,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Gam_02
};

PLATE_INFO PlateInfo_Gam_03 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NORMAL,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Gam_03
};

PLATE_INFO PlateInfo_Gam_04 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NORMAL,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Gam_04
};

PLATE_INFO PlateInfo_Gam_05 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NORMAL,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Gam_05
};

PLATE_INFO PlateInfo_Mom_00 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Mom_00
};

PLATE_INFO PlateInfo_Mom_01 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Mom_01
};

PLATE_INFO PlateInfo_Mom_02 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Mom_02
};

PLATE_INFO PlateInfo_Mom_03 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Mom_03
};

PLATE_INFO PlateInfo_Mom_04 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Gjk, &ParaDcEx1_Gjk_00
};

PLATE_INFO PlateInfo_Mom_05 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Gjk, &ParaDcEx1_Gjk_01
};

PLATE_INFO PlateInfo_Mom_06 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Gjk, &ParaDcEx1_Gjk_02
};

PLATE_INFO PlateInfo_Mom_07 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Gjk, &ParaDcEx1_Gjk_03
};

PLATE_INFO PlateInfo_Mom_08 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Gjk, &ParaDcEx1_Gjk_04
};

PLATE_INFO PlateInfo_Mom_09 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Gjk, &ParaDcEx1_Gjk_05
};

PLATE_INFO PlateInfo_Pup_00 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_00
};

PLATE_INFO PlateInfo_Pup_01 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_01
};

PLATE_INFO PlateInfo_Pup_02 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_02
};

PLATE_INFO PlateInfo_Pup_03 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_03
};

PLATE_INFO PlateInfo_Pup_04 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_04
};

PLATE_INFO PlateInfo_Pup_05 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_05
};

PLATE_INFO PlateInfo_Pup_06 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_06
};

PLATE_INFO PlateInfo_Pup_07 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_07
};

PLATE_INFO PlateInfo_Pup_08 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_08
};

PLATE_INFO PlateInfo_Pup_09 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_09
};

PLATE_INFO PlateInfo_Pup_10 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_10
};

PLATE_INFO PlateInfo_Pup_11 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_11
};

PLATE_INFO PlateInfo_Pup_12 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_12
};

PLATE_INFO PlateInfo_Pup_13 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_13
};

PLATE_INFO PlateInfo_Pup_14 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_14
};

PLATE_INFO PlateInfo_Pup_15 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_15
};

PLATE_INFO PlateInfo_Pup_16 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_16
};

PLATE_INFO PlateInfo_Pup_17 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_17
};

PLATE_INFO PlateInfo_Pup_18 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_18
};

PLATE_INFO PlateInfo_Pup_19 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_19
};

PLATE_INFO PlateInfo_Pup_20 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_20
};

PLATE_INFO PlateInfo_Pup_21 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_21
};

PLATE_INFO PlateInfo_Pup_22 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_22
};

PLATE_INFO PlateInfo_Pup_23 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_23
};

PLATE_INFO PlateInfo_Pup_24 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Pup_24
};

PLATE_INFO PlateInfo_Pup_25 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_25
};

PLATE_INFO PlateInfo_Pup_26 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_26
};

PLATE_INFO PlateInfo_Pup_27 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_27
};

PLATE_INFO PlateInfo_Pup_28 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_28
};

PLATE_INFO PlateInfo_Pup_29 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_29
};

PLATE_INFO PlateInfo_Pup_30 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_30
};

PLATE_INFO PlateInfo_Pup_31 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_31
};

PLATE_INFO PlateInfo_Pup_32 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_32
};

PLATE_INFO PlateInfo_Pup_33 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_33
};

PLATE_INFO PlateInfo_Pup_34 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_34
};

PLATE_INFO PlateInfo_Pup_35 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_35
};

PLATE_INFO PlateInfo_Pup_36 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_36
};

PLATE_INFO PlateInfo_Pup_37 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_37
};

PLATE_INFO PlateInfo_Pup_38 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_38
};

PLATE_INFO PlateInfo_Pup_39 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_39
};

PLATE_INFO PlateInfo_Pup_40 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_40
};

PLATE_INFO PlateInfo_Pup_41 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_41
};

PLATE_INFO PlateInfo_Pup_42 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_42
};

PLATE_INFO PlateInfo_Pup_43 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_43
};

PLATE_INFO PlateInfo_Pup_44 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_44
};

PLATE_INFO PlateInfo_Pup_45 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_45
};

PLATE_INFO PlateInfo_Pup_46 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_46
};

PLATE_INFO PlateInfo_Pup_47 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_47
};

PLATE_INFO PlateInfo_Pup_48 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_48
};

PLATE_INFO PlateInfo_Pup_49 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_49
};

PLATE_INFO PlateInfo_Pup_50 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_50
};

PLATE_INFO PlateInfo_Pup_51 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_51
};

PLATE_INFO PlateInfo_Pup_52 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_52
};

PLATE_INFO PlateInfo_Pup_53 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_53
};

PLATE_INFO PlateInfo_Pup_54 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_54
};

PLATE_INFO PlateInfo_Pup_55 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_55
};

PLATE_INFO PlateInfo_Pup_56 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_56
};

PLATE_INFO PlateInfo_Pup_57 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_57
};

PLATE_INFO PlateInfo_Pup_58 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_58
};

PLATE_INFO PlateInfo_Pup_59 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_59
};

PLATE_INFO PlateInfo_Pup_60 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_60
};

PLATE_INFO PlateInfo_Pup_61 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_61
};

PLATE_INFO PlateInfo_Pup_62 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_62
};

PLATE_INFO PlateInfo_Pup_63 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_63
};

PLATE_INFO PlateInfo_Pup_64 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_64
};

PLATE_INFO PlateInfo_Pup_65 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_65
};

PLATE_INFO PlateInfo_Pup_66 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_66
};

PLATE_INFO PlateInfo_Pup_67 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_67
};

PLATE_INFO PlateInfo_Pup_68 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_68
};

PLATE_INFO PlateInfo_Pup_69 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_69
};

PLATE_INFO PlateInfo_Pup_70 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_70
};

PLATE_INFO PlateInfo_Pup_71 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_71
};

PLATE_INFO PlateInfo_Pup_72 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_72
};

PLATE_INFO PlateInfo_Pup_73 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_73
};

PLATE_INFO PlateInfo_Pup_74 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_74
};

PLATE_INFO PlateInfo_Pup_75 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_75
};

PLATE_INFO PlateInfo_Pup_76 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_76
};

PLATE_INFO PlateInfo_Pup_77 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_77
};

PLATE_INFO PlateInfo_Pup_78 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_78
};

PLATE_INFO PlateInfo_Pup_79 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_79
};

PLATE_INFO PlateInfo_Pup_80 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_80
};

PLATE_INFO PlateInfo_Pup_81 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_81
};

PLATE_INFO PlateInfo_Pup_82 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_82
};

PLATE_INFO PlateInfo_Pup_83 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_83
};

PLATE_INFO PlateInfo_Pup_84 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_84
};

PLATE_INFO PlateInfo_Pup_85 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_85
};

PLATE_INFO PlateInfo_Pup_86 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_86
};

PLATE_INFO PlateInfo_Pup_87 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_VERYLONG,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Tht, &ParaDcEx3_Pup_87
};

PLATE_INFO PlateInfo_Tri_00 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Tri_00
};

PLATE_INFO PlateInfo_Tri_01 = {
    1, 0, 0,
    PL_STATUS_IN, FORM_NARROW,
    FontColor_0,
    kzTD_Draw_Plate_Std, kzTD_Draw_Contents_Std, &ParaDcStd_Tri_01
};

PLATE_INFO *Plates_Win_YesNo[] = { &PlateInfo_Fil_04, &PlateInfo_Fil_05 };
PLATE_INFO *Plates_Ttl_Menu[] = { &PlateInfo_Ttl_00, &PlateInfo_Ttl_01 };
PLATE_INFO *Plates_Fil_MakeSel[] = { &PlateInfo_Fil_00, &PlateInfo_Fil_01, &PlateInfo_Fil_02, &PlateInfo_Fil_03 };
PLATE_INFO *Plates_Fil_FileSel[] = { &PlateInfo_Fil_00, &PlateInfo_Fil_01, &PlateInfo_Fil_02, &PlateInfo_Fil_03 };
PLATE_INFO *Plates_Fil_DataSel[] = { &PlateInfo_Fil_06, &PlateInfo_Fil_07, &PlateInfo_Fil_08, &PlateInfo_Fil_09 };
PLATE_INFO *Plates_Opt_Top[] = { &PlateInfo_Opt_00, &PlateInfo_Opt_01, &PlateInfo_Opt_02, &PlateInfo_Opt_03 };
PLATE_INFO *Plates_Opt_Pad[] = { &PlateInfo_Opt_04, &PlateInfo_Opt_05 };
PLATE_INFO *Plates_Opt_Sound[] = { &PlateInfo_Opt_06, &PlateInfo_Opt_07, &PlateInfo_Opt_08 };
PLATE_INFO *Plates_Etc_PadExp0[] = { &PlateInfo_Etc_01 };
PLATE_INFO *Plates_Etc_PadExp1[] = { &PlateInfo_Etc_00, &PlateInfo_Etc_01 };
PLATE_INFO *Plates_Etc_PadExp2[] = { &PlateInfo_Etc_02, &PlateInfo_Etc_01 };
PLATE_INFO *Plates_Etc_PadExp3[] = { &PlateInfo_Etc_03, &PlateInfo_Etc_01 };
PLATE_INFO *Plates_Etc_PadExp4[] = { &PlateInfo_Etc_04, &PlateInfo_Etc_07, &PlateInfo_Etc_06, &PlateInfo_Etc_08, &PlateInfo_Etc_05, &PlateInfo_Etc_01 };
PLATE_INFO *Plates_Etc_PadExp5[] = { &PlateInfo_Etc_09, &PlateInfo_Etc_10 };
PLATE_INFO *Plates_Wmp_Status[] = { &PlateInfo_Wmp_00, &PlateInfo_Wmp_01, &PlateInfo_Wmp_02, &PlateInfo_Wmp_03, &PlateInfo_Wmp_04, &PlateInfo_Wmp_05, &PlateInfo_Wmp_06, &PlateInfo_Wmp_07, &PlateInfo_Wmp_08, &PlateInfo_Wmp_09, &PlateInfo_Wmp_10, &PlateInfo_Wmp_11, &PlateInfo_Wmp_12, &PlateInfo_Wmp_13, &PlateInfo_Wmp_14, &PlateInfo_Wmp_15, &PlateInfo_Wmp_16, &PlateInfo_Wmp_17, &PlateInfo_Wmp_18 };
PLATE_INFO *Plates_Wmp_Menu[] = { &PlateInfo_Wmp_20, &PlateInfo_Wmp_21, &PlateInfo_Wmp_22 };
PLATE_INFO *Plates_Gam_Pause[] = { &PlateInfo_Gam_00, &PlateInfo_Gam_01, &PlateInfo_Gam_02 };
PLATE_INFO *Plates_Mom_Pause[] = { &PlateInfo_Gam_00, &PlateInfo_Gam_01, &PlateInfo_Gam_03 };
PLATE_INFO *Plates_Gam_VOver[] = { &PlateInfo_Gam_04, &PlateInfo_Gam_05 };
PLATE_INFO *Plates_Mom_Top[] = { &PlateInfo_Mom_00, &PlateInfo_Mom_01, &PlateInfo_Mom_02, &PlateInfo_Mom_03 };
PLATE_INFO *Plates_Mom_Genju[] = { &PlateInfo_Mom_04, &PlateInfo_Mom_05, &PlateInfo_Mom_06, &PlateInfo_Mom_07, &PlateInfo_Mom_08, &PlateInfo_Mom_09 };
PLATE_INFO *Plates_Pup_Top[] = { &PlateInfo_Pup_00, &PlateInfo_Pup_01, &PlateInfo_Pup_02, &PlateInfo_Pup_03, &PlateInfo_Pup_04, &PlateInfo_Pup_05, &PlateInfo_Pup_06, &PlateInfo_Pup_07, &PlateInfo_Pup_08, &PlateInfo_Pup_09, &PlateInfo_Pup_10, &PlateInfo_Pup_11, &PlateInfo_Pup_12, &PlateInfo_Pup_13, &PlateInfo_Pup_14, &PlateInfo_Pup_15, &PlateInfo_Pup_16, &PlateInfo_Pup_17, &PlateInfo_Pup_18, &PlateInfo_Pup_19, &PlateInfo_Pup_20, &PlateInfo_Pup_21, &PlateInfo_Pup_22, &PlateInfo_Pup_23, &PlateInfo_Pup_24 };
PLATE_INFO *Plates_Pup_Group00[] = { &PlateInfo_Pup_25 };
PLATE_INFO *Plates_Pup_Group01[] = { &PlateInfo_Pup_26, &PlateInfo_Pup_27 };
PLATE_INFO *Plates_Pup_Group02[] = { &PlateInfo_Pup_28, &PlateInfo_Pup_29, &PlateInfo_Pup_30, &PlateInfo_Pup_31, &PlateInfo_Pup_32 };
PLATE_INFO *Plates_Pup_Group03[] = { &PlateInfo_Pup_33, &PlateInfo_Pup_34 };
PLATE_INFO *Plates_Pup_Group04[] = { &PlateInfo_Pup_35, &PlateInfo_Pup_36 };
PLATE_INFO *Plates_Pup_Group05[] = { &PlateInfo_Pup_37, &PlateInfo_Pup_38, &PlateInfo_Pup_39 };
PLATE_INFO *Plates_Pup_Group06[] = { &PlateInfo_Pup_40, &PlateInfo_Pup_41, &PlateInfo_Pup_42, &PlateInfo_Pup_43, &PlateInfo_Pup_44, &PlateInfo_Pup_45 };
PLATE_INFO *Plates_Pup_Group07[] = { &PlateInfo_Pup_46, &PlateInfo_Pup_47, &PlateInfo_Pup_48 };
PLATE_INFO *Plates_Pup_Group08[] = { &PlateInfo_Pup_49, &PlateInfo_Pup_50, &PlateInfo_Pup_51 };
PLATE_INFO *Plates_Pup_Group09[] = { &PlateInfo_Pup_52, &PlateInfo_Pup_53, &PlateInfo_Pup_54 };
PLATE_INFO *Plates_Pup_Group10[] = { &PlateInfo_Pup_55 };
PLATE_INFO *Plates_Pup_Group11[] = { &PlateInfo_Pup_56, &PlateInfo_Pup_57 };
PLATE_INFO *Plates_Pup_Group12[] = { &PlateInfo_Pup_58, &PlateInfo_Pup_59 };
PLATE_INFO *Plates_Pup_Group13[] = { &PlateInfo_Pup_60, &PlateInfo_Pup_61 };
PLATE_INFO *Plates_Pup_Group14[] = { &PlateInfo_Pup_62, &PlateInfo_Pup_63 };
PLATE_INFO *Plates_Pup_Group15[] = { &PlateInfo_Pup_64, &PlateInfo_Pup_65, &PlateInfo_Pup_66 };
PLATE_INFO *Plates_Pup_Group16[] = { &PlateInfo_Pup_67, &PlateInfo_Pup_68 };
PLATE_INFO *Plates_Pup_Group17[] = { &PlateInfo_Pup_69 };
PLATE_INFO *Plates_Pup_Group18[] = { &PlateInfo_Pup_70, &PlateInfo_Pup_71 };
PLATE_INFO *Plates_Pup_Group19[] = { &PlateInfo_Pup_72, &PlateInfo_Pup_73 };
PLATE_INFO *Plates_Pup_Group20[] = { &PlateInfo_Pup_74, &PlateInfo_Pup_75, &PlateInfo_Pup_76, &PlateInfo_Pup_77, &PlateInfo_Pup_78, &PlateInfo_Pup_79 };
PLATE_INFO *Plates_Pup_Group21[] = { &PlateInfo_Pup_80, &PlateInfo_Pup_81 };
PLATE_INFO *Plates_Pup_Group22[] = { &PlateInfo_Pup_82 };
PLATE_INFO *Plates_Pup_Group23[] = { &PlateInfo_Pup_83, &PlateInfo_Pup_84, &PlateInfo_Pup_85, &PlateInfo_Pup_86 };
PLATE_INFO *Plates_Pup_Group24[] = { &PlateInfo_Pup_87 };
PLATE_INFO *Plates_Tri_TtlMenu[] = { &PlateInfo_Tri_00, &PlateInfo_Tri_01 };
s16 LineOffset_Win[] = { 0 };
s16 LineOffset_Ttl[] = { 0 };
s16 LineOffset_Fil[] = { 0, 60, 120, 180 };
s16 LineOffset_Opt[] = { 0, 60, 120, 180 };
s16 LineOffset_PadExp0[] = { 0 };
s16 LineOffset_PadExp1[] = { 0, 40 };
s16 LineOffset_Status[] = { 0, 32, 64, 96, 128, 160, 192, 224, 256, 288 };
s16 LineOffset_WmpMenu[] = { 0, 60, 120 };
s16 LineOffset_Pause[] = { 0, 60, 120 };
s16 LineOffset_VOver[] = { 0 };
s16 LineOffset_MomTop[] = { 0, 60, 120, 180 };
s16 LineOffset_Genju[] = { 0, 60, 120, 180, 240, 300 };
s16 LineOffset_Theater[] = { 0, 60, 120, 180, 240, 300 };
s16 LineOffset_TriTtl[] = { 0 };
s16 RowOffset_Win[] = { 0, 184 };
s16 RowOffset_Ttl[] = { 0, 160 };
s16 RowOffset_Fil[] = { 0 };
s16 RowOffset_Opt[] = { 0 };
s16 RowOffset_PadExp0[] = { 0 };
s16 RowOffset_PadExp1[] = { 0, 120 };
s16 RowOffset_PadExp2[] = { 0 };
s16 RowOffset_PadExp3[] = { 0, 118, 236, 0, 118, 236 };
s16 RowOffset_Status[] = { 0 };
s16 RowOffset_WmpMenu[] = { 0 };
s16 RowOffset_Pause[] = { 0 };
s16 RowOffset_VOver[] = { 0, 200 };
s16 RowOffset_MomTop[] = { 0 };
s16 RowOffset_Genju[] = { 0 };
s16 RowOffset_Theater[] = { 0 };
s16 RowOffset_TriTtl[] = { 0, 272 };
s16 Delay_Win[] = { 0, 8 };
s16 Delay_Ttl[] = { 0, 8 };
s16 Delay_Fil[] = { 0, 3, 6, 9 };
s16 Delay_Opt[] = { 0, 3, 6, 9 };
s16 Delay_PadExp[] = { 0 , 0, 0, 0, 0, 0 };
s16 Delay_Status[] = { 0, 1, 3, 4, 6, 7, 9, 10, 12, 13 };
s16 Delay_WmpMenu[] = { 0, 2, 4 };
s16 Delay_Pause[] = { 0, 2, 4 };
s16 Delay_VOver[] = { 0, 9 };
s16 Delay_MomTop[] = { 0, 2, 4, 6, 8 };
s16 Delay_Genju[] = { 0, 3, 6, 9, 12, 15 };
s16 Delay_Theater[] = { 0, 3, 6, 9, 12, 15 };
s16 Delay_TriTtl[] = { 0, 16 };
SELECT_INFO SelectInfo_Win_YesNo = {
    { 168, 280 },
    { 0, 0 }, { 0, 0 },
    2, 1, 2, 2,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Win, RowOffset_Win, Delay_Win,
    Plates_Win_YesNo,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Ttl_Menu = {
    { 180, 318 },
    { 0, 0 }, { 0, 0 },
    2, 1, 2, 2,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Ttl, RowOffset_Ttl, Delay_Ttl,
    Plates_Ttl_Menu,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Fil_MakeSel = {
    { 36, 156 },
    { 0, 0 }, { 0, 0 },
    4, 4, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Fil, RowOffset_Fil, Delay_Fil,
    Plates_Fil_MakeSel,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Fil_Confirm = {
    { 36, 156 },
    { 0, 0 }, { 0, 0 },
    2, 2, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Fil, RowOffset_Fil, Delay_Fil,
    Plates_Win_YesNo,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Fil_FileSel = {
    { 36, 156 },
    { 0, 0 }, { 0, 0 },
    4, 4, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Fil, RowOffset_Fil, Delay_Fil,
    Plates_Fil_FileSel,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Fil_DataSel = {
    { 36, 156 },
    { 0, 0 }, { 0, 0 },
    4, 4, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Fil, RowOffset_Fil, Delay_Fil,
    Plates_Fil_DataSel,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Opt_Top = {
    { 36, 156 },
    { 0, 0 }, { 0, 0 },
    4, 4, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Opt, RowOffset_Opt, Delay_Opt,
    Plates_Opt_Top,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Opt_Pad = {
    { 36, 156 },
    { 0, 0 }, { 0, 0 },
    2, 2, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Opt, RowOffset_Opt, Delay_Opt,
    Plates_Opt_Pad,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Opt_Sound0 = {
    { 36, 156 },
    { 0, 0 }, { 0, 0 },
    3, 3, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Opt, RowOffset_Opt, Delay_Opt,
    Plates_Opt_Sound,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Opt_Sound1 = {
    { 36, 156 },
    { 0, 0 }, { 0, 0 },
    2, 2, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Opt, RowOffset_Opt, Delay_Opt,
    Plates_Opt_Sound,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Etc_PadExp0 = {
    { 505, 400 },
    { 0, 0 }, { 0, 0 },
    1, 1, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_PadExp0, RowOffset_PadExp0, Delay_PadExp,
    Plates_Etc_PadExp0,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Etc_PadExp1 = {
    { 385, 400 },
    { 0, 0 }, { 0, 0 },
    2, 1, 2, 2,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_PadExp0, RowOffset_PadExp1, Delay_PadExp,
    Plates_Etc_PadExp1,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Etc_PadExp2 = {
    { 385, 400 },
    { 0, 0 }, { 0, 0 },
    2, 1, 2, 2,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_PadExp0, RowOffset_PadExp1, Delay_PadExp,
    Plates_Etc_PadExp2,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Etc_PadExp3 = {
    { 505, 268 },
    { 0, 0 }, { 0, 0 },
    1, 1, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_PadExp0, RowOffset_PadExp2, Delay_PadExp,
    Plates_Etc_PadExp0,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Etc_PadExp4 = {
    { 385, 400 },
    { 0, 0 }, { 0, 0 },
    2, 1, 2, 2,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_PadExp0, RowOffset_PadExp1, Delay_PadExp,
    Plates_Etc_PadExp3,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Etc_PadExp5 = {
    { 272, 360 },
    { 0, 0 }, { 0, 0 },
    6, 2, 3, 3,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_PadExp1, RowOffset_PadExp3, Delay_PadExp,
    Plates_Etc_PadExp4,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Etc_PadExp6 = {
    { 385, 400 },
    { 0, 0 }, { 0, 0 },
    2, 1, 2, 2,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_PadExp0, RowOffset_PadExp1, Delay_PadExp,
    Plates_Etc_PadExp5,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Wmp_Status = {
    { 40, 78 },
    { -28, 144 }, { 244, 144 },
    19, 10, 1, 2,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Status, RowOffset_Status, Delay_Status,
    Plates_Wmp_Status,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Wmp_Menu = {
    { 260, 170 },
    { 0, 0 }, { 0, 0 },
    3, 3, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_WmpMenu, RowOffset_WmpMenu, Delay_WmpMenu,
    Plates_Wmp_Menu,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Gam_Pause = {
    { 260, 170 },
    { 0, 0 }, { 0, 0 },
    3, 3, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Pause, RowOffset_Pause, Delay_Pause,
    Plates_Gam_Pause,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Mom_Pause = {
    { 260, 170 },
    { 0, 0 }, { 0, 0 },
    3, 3, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Pause, RowOffset_Pause, Delay_Pause,
    Plates_Mom_Pause,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Gam_VOver = {
    { 160, 178 },
    { 0, 0 }, { 0, 0 },
    2, 1, 2, 2,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_VOver, RowOffset_VOver, Delay_VOver,
    Plates_Gam_VOver,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Mom_Top = {
    { 280, 32 },
    { 0, 0 }, { 0, 0 },
    4, 4, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_MomTop, RowOffset_MomTop, Delay_MomTop,
    Plates_Mom_Top,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Mom_Genju = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    6, 6, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Genju, RowOffset_Genju, Delay_Genju,
    Plates_Mom_Genju,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Top = {
    { 280, 44 },
    { -32, 128 }, { 330, 128 },
    25, 5, 1, 5,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Top,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group00 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    1, 1, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group00,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group01 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    2, 2, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group01,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group02 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    5, 5, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group02,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group03 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    2, 2, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group03,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group04 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    2, 2, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group04,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group05 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    3, 3, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group05,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group06 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    6, 6, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group06,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group07 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    3, 3, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group07,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group08 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    3, 3, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group08,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group09 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    3, 3, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group09,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group10 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    1, 1, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group10,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group11 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    2, 2, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group11,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group12 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    2, 2, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group12,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group13 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    2, 2, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group13,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group14 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    2, 2, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group14,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group15 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    3, 3, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group15,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group16 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    2, 2, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group16,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group17 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    1, 1, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group17,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group18 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    2, 2, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group18,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group19 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    2, 2, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group19,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group20 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    6, 6, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group20,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group21 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    2, 2, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group21,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group22 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    1, 1, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group22,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group23 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    4, 4, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group23,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Pup_Group24 = {
    { 280, 44 },
    { 0, 0 }, { 0, 0 },
    1, 1, 1, 1,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_Theater, RowOffset_Theater, Delay_Theater,
    Plates_Pup_Group24,
    kzTD_Draw_Mark_Std
};

SELECT_INFO SelectInfo_Tri_TtlMenu = {
    { 64, 295 },
    { 0, 0 }, { 0, 0 },
    2, 1, 2, 2,
    0, 0,
    0, 0,
    0, 0, 0, 0,
    LineOffset_TriTtl, RowOffset_TriTtl, Delay_TriTtl,
    Plates_Tri_TtlMenu,
    kzTD_Draw_Mark_Std
};

SELECT_INFO *Selectors[] = {
    &SelectInfo_Win_YesNo,
    &SelectInfo_Ttl_Menu,
    &SelectInfo_Fil_MakeSel,
    &SelectInfo_Fil_Confirm,
    &SelectInfo_Fil_FileSel,
    &SelectInfo_Fil_DataSel,
    &SelectInfo_Opt_Top,
    &SelectInfo_Opt_Pad,
    &SelectInfo_Opt_Sound0,
    &SelectInfo_Opt_Sound1,
    &SelectInfo_Etc_PadExp0,
    &SelectInfo_Etc_PadExp1,
    &SelectInfo_Etc_PadExp2,
    &SelectInfo_Etc_PadExp3,
    &SelectInfo_Etc_PadExp4,
    &SelectInfo_Etc_PadExp5,
    &SelectInfo_Etc_PadExp6,
    &SelectInfo_Wmp_Status,
    &SelectInfo_Wmp_Menu,
    &SelectInfo_Gam_Pause,
    &SelectInfo_Mom_Pause,
    &SelectInfo_Gam_VOver,
    &SelectInfo_Mom_Top,
    &SelectInfo_Mom_Genju,
    &SelectInfo_Pup_Top,
    &SelectInfo_Pup_Group00,
    &SelectInfo_Pup_Group01,
    &SelectInfo_Pup_Group02,
    &SelectInfo_Pup_Group03,
    &SelectInfo_Pup_Group04,
    &SelectInfo_Pup_Group05,
    &SelectInfo_Pup_Group06,
    &SelectInfo_Pup_Group07,
    &SelectInfo_Pup_Group08,
    &SelectInfo_Pup_Group09,
    &SelectInfo_Pup_Group10,
    &SelectInfo_Pup_Group11,
    &SelectInfo_Pup_Group12,
    &SelectInfo_Pup_Group13,
    &SelectInfo_Pup_Group14,
    &SelectInfo_Pup_Group15,
    &SelectInfo_Pup_Group16,
    &SelectInfo_Pup_Group17,
    &SelectInfo_Pup_Group18,
    &SelectInfo_Pup_Group19,
    &SelectInfo_Pup_Group20,
    &SelectInfo_Pup_Group21,
    &SelectInfo_Pup_Group22,
    &SelectInfo_Pup_Group23,
    &SelectInfo_Pup_Group24,
    &SelectInfo_Tri_TtlMenu,
};

GIM_FORM *WindowParts_00[9] = {
    &GimForm_PLTB01,
    &GimForm_PLTB02,
    &GimForm_PLTB03,
    &GimForm_PLTB04,
    &GimForm_PLTB05,
    &GimForm_PLTB06,
    &GimForm_PLTB07,
    &GimForm_PLTB08,
    &GimForm_PLTB09,
};

GIM_FORM *WindowParts_01[9] = {
    &GimForm_PLTC01,
    &GimForm_PLTC02,
    &GimForm_PLTC03,
    &GimForm_PLTC04,
    &GimForm_PLTC05,
    &GimForm_PLTC06,
    &GimForm_PLTC07,
    &GimForm_PLTC08,
    &GimForm_PLTC09,
};

GIM_FORM *WindowParts_02[9] = {
    &GimForm_PLTD01,
    &GimForm_PLTD02,
    &GimForm_PLTD03,
    &GimForm_PLTD04,
    &GimForm_PLTD05,
    &GimForm_PLTD06,
    &GimForm_PLTD07,
    &GimForm_PLTD08,
    &GimForm_PLTD09,
};

GIM_FORM *WindowParts_03[9] = {
    &GimForm_PLTE01,
    &GimForm_PLTE02,
    &GimForm_PLTE03,
    &GimForm_PLTE04,
    &GimForm_PLTE05,
    &GimForm_PLTE06,
    &GimForm_PLTE07,
    &GimForm_PLTE08,
    &GimForm_PLTE09,
};

GIM_FORM *WindowParts_04[9] = {
    &GimForm_PLTF01,
    &GimForm_PLTF02,
    &GimForm_PLTF03,
    &GimForm_PLTF04,
    &GimForm_PLTF05,
    &GimForm_PLTF06,
    &GimForm_PLTF07,
    &GimForm_PLTF08,
    &GimForm_PLTF09,
};

GROUND_INFO GroundInfo_Win_Std = {
    { 88, 112 },
    { 29, 8 },
    WindowParts_02
};

GROUND_INFO GroundInfo_Opt_ScrExplain = {
    { 32, 40 },
    { 36, 3 },
    WindowParts_00
};

GROUND_INFO GroundInfo_Opt_HelpInfo = {
    { 224, 136 },
    { 24, 16 },
    WindowParts_01
};

GROUND_INFO GroundInfo_Opt_Adjust = {
    { 88, 48 },
    { 29, 6 },
    WindowParts_00
};

GROUND_INFO GroundInfo_Nam_Entry = {
    { 32, 105 },
    { 36, 20 },
    WindowParts_01
};

GROUND_INFO GroundInfo_Mom_PlyDisp = {
    { 272, 104 },
    { 21, 9 },
    WindowParts_01
};

GROUND_INFO GroundInfo_Mom_PlyCtrl = {
    { 320, 264 },
    { 15, 5 },
    WindowParts_00
};

GROUND_INFO GroundInfo_Wmp_Place = {
    { 32, 380 },
    { 15, 3 },
    WindowParts_03
};

GROUND_INFO GroundInfo_Mom_Message = {
    { 35, 310 },
    { 36, 8 },
    WindowParts_04
};

GROUND_INFO *Grounds[] = {
    &GroundInfo_Win_Std,
    &GroundInfo_Opt_ScrExplain,
    &GroundInfo_Opt_HelpInfo,
    &GroundInfo_Opt_Adjust,
    &GroundInfo_Nam_Entry,
    &GroundInfo_Mom_PlyDisp,
    &GroundInfo_Mom_PlyCtrl,
    &GroundInfo_Wmp_Place,
    &GroundInfo_Mom_Message,
};

WINDOW_INFO WindowInfo_Mem_00 = {
    WN_STATUS_00, 1,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_00,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, -1
};

WINDOW_INFO WindowInfo_Mem_01 = {
    WN_STATUS_00, 1,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_01,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, -1
};

WINDOW_INFO WindowInfo_Mem_02 = {
    WN_STATUS_00, 0,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_02,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, SELECT_WIN_YESNO
};

WINDOW_INFO WindowInfo_Mem_03 = {
    WN_STATUS_00, 1,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_03,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, -1
};

WINDOW_INFO WindowInfo_Mem_04 = {
    WN_STATUS_00, 0,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_04,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, SELECT_WIN_YESNO
};

WINDOW_INFO WindowInfo_Mem_05 = {
    WN_STATUS_00, 0,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_05,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, SELECT_WIN_YESNO
};

WINDOW_INFO WindowInfo_Mem_06 = {
    WN_STATUS_00, 1,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_06,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, -1
};

WINDOW_INFO WindowInfo_Mem_07 = {
    WN_STATUS_00, 1,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_07,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, -1
};

WINDOW_INFO WindowInfo_Mem_08 = {
    WN_STATUS_00, 0,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_08,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, SELECT_WIN_YESNO
};

WINDOW_INFO WindowInfo_Mem_09 = {
    WN_STATUS_00, 1,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_09,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, -1
};

WINDOW_INFO WindowInfo_Mem_10 = {
    WN_STATUS_00, 1,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_10,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, -1
};

WINDOW_INFO WindowInfo_Mem_11 = {
    WN_STATUS_00, 1,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_11,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, -1
};

WINDOW_INFO WindowInfo_Mem_12 = {
    WN_STATUS_00, 1,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_12,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, -1
};

WINDOW_INFO WindowInfo_Mem_13 = {
    WN_STATUS_00, 1,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_13,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, -1
};

WINDOW_INFO WindowInfo_Mem_14 = {
    WN_STATUS_00, 0,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_14,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, SELECT_WIN_YESNO
};

WINDOW_INFO WindowInfo_Mem_15 = {
    WN_STATUS_00, 0,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_15,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, -1
};

WINDOW_INFO WindowInfo_Mem_16 = {
    WN_STATUS_00, 0,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_16,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, -1
};

WINDOW_INFO WindowInfo_Mem_17 = {
    WN_STATUS_00, 0,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_17,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, -1
};

WINDOW_INFO WindowInfo_Mem_18 = {
    WN_STATUS_00, 0,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_18,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, -1
};

WINDOW_INFO WindowInfo_Mem_19 = {
    WN_STATUS_00, 1,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_19,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, -1
};

WINDOW_INFO WindowInfo_Etc_00 = {
    WN_STATUS_00, 0,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_20,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, SELECT_WIN_YESNO
};

WINDOW_INFO WindowInfo_Etc_01 = {
    WN_STATUS_00, 0,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_21,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, SELECT_WIN_YESNO
};

WINDOW_INFO WindowInfo_Etc_02 = {
    WN_STATUS_00, 0,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_22,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, SELECT_WIN_YESNO
};

WINDOW_INFO WindowInfo_Etc_03 = {
    WN_STATUS_00, 0,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_23,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, SELECT_WIN_YESNO
};

WINDOW_INFO WindowInfo_Etc_04 = {
    WN_STATUS_00, 0,
    GROUND_OPT_ADJUST,
    { 42, 24 }, STR_ETC_10,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, -1
};

WINDOW_INFO WindowInfo_Etc_05 = {
    WN_STATUS_00, 1,
    GROUND_WIN_STD,
    { 42, 24 }, STR_WINDOW_21,
    { 0x32, 0x1B, 0x0A, 0x80 },
    { 80, 168 }, -1
};

WINDOW_INFO *Windows[] = {
    &WindowInfo_Mem_00,
    &WindowInfo_Mem_01,
    &WindowInfo_Mem_02,
    &WindowInfo_Mem_03,
    &WindowInfo_Mem_04,
    &WindowInfo_Mem_05,
    &WindowInfo_Mem_06,
    &WindowInfo_Mem_07,
    &WindowInfo_Mem_08,
    &WindowInfo_Mem_09,
    &WindowInfo_Mem_10,
    &WindowInfo_Mem_11,
    &WindowInfo_Mem_12,
    &WindowInfo_Mem_13,
    &WindowInfo_Mem_14,
    &WindowInfo_Mem_15,
    &WindowInfo_Mem_16,
    &WindowInfo_Mem_17,
    &WindowInfo_Mem_18,
    &WindowInfo_Mem_19,
    &WindowInfo_Etc_00,
    &WindowInfo_Etc_01,
    &WindowInfo_Etc_02,
    &WindowInfo_Etc_03,
    &WindowInfo_Etc_04,
    &WindowInfo_Etc_05
};

KZCOLOR A_ON = { 0x00, 0x00, 0x00, 0x80 };
KZCOLOR A_OFF = { 0x00, 0x00, 0x00, 0x00 };
KZCOLOR GCOL_STD = { 0x80, 0x80, 0x80, 0x80 };
KZCOLOR GCOL_PSH = { 0x00, 0x00, 0x00, 0x60 };
KZCOLOR GCOL_MRK = { 0xFF, 0x00, 0x00, 0x80 };
KZCOLOR GCOL_SND = { 0xFF, 0xFF, 0xFF, 0x80 };
KZCOLOR FCOL_STD = { 0x32, 0x1B, 0x0A, 0x80 };
DVECTOR ORIGIN = { 0, 0 };
DVECTOR FULLSCR = { 640, 448 };
DVECTOR GIMBASE_SNDMES = { 510, 184 };
DVECTOR GIMOFFSET_YUME = { 142, 8 };
DVECTOR GIMOFFSET_FLCK = { 185, 6 };
DVECTOR GIMOFFSET_DOLL = { 202, 2 };
DVECTOR GIMOFFSET_SLASH = { 213, 9 };
DVECTOR NUMOFFSET_YUME = { 154, 8 };
DVECTOR NUMOFFSET_DOLL0 = { 205, 8 };
DVECTOR NUMOFFSET_DOLL1 = { 223, 8 };
DVECTOR NUMOFFSET_GENJU = { 152, 8 };
static s32 PUP_H = 17;
static s32 PUP_STOP = 12;
static s32 PUP_DIV = 14;
static f32 PROT_INIT = 0.19634950160980225f;
static s32 PROT_DIV = 15;
static f32 PROT_SUB = 0.02454368770122528f;


void kzTD_Set_GsEnv_Std() {
    nkGsSetNormalFZ2();
    kz_Set_Alpha(2, SCE_GS_BLEND_RGB_SRC, SCE_GS_BLEND_RGB_DST, SCE_GS_BLEND_ALPHA_SRC, SCE_GS_BLEND_RGB_DST, 0x80);
    kz_Set_Clamp(2, SCE_GS_CLAMP, SCE_GS_CLAMP, 0, 0, 0 ,0);
    kz_Set_Fba(2, 0x00);
    kz_Set_Pabe(0);
    kz_Set_Test(2, SCE_GS_TRUE, SCE_GS_ALPHA_ALWAYS, 0, SCE_GS_AFAIL_KEEP, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZALWAYS);
    kz_Set_Tex1(2, SCE_GS_NEAREST, SCE_GS_NEAREST, SCE_GS_NEAREST, SCE_GS_NEAREST, 0, 0 ,0);
    kz_Set_Texa(0, 0, 0x80);
}

GIM_FORM* kzGIM_Get_Form(s32 gim_no) {
    return GimForms[gim_no];
}

void kzGIM_Draw(DVECTOR *sxy, u32 sz, KZCOLOR *col, s32 gim_no) {
    GIM_FORM *form = GimForms[gim_no];
    kz_Set_Tex0_Imd(form->tex0);
    kz_Set_SprtUV(sxy, sz, &form->wh, &form->uv, col);
}

void kzGIM_Draw_Eff(DVECTOR *sxy, u32 sz, KZCOLOR *col, s32 gim_no) {
    GIM_FORM *form = GimForms[gim_no];
    kz_Set_Tex0_Imd(form->tex0);
    kz_Set_SprtUV_Eff(sxy, sz, &form->wh, &form->uv, col);
}

void kzTD_Init_Fade(s32 mode) {
    if (mode > 0) {
        fade_count = 30;
    }
    if (mode < 0) {
        fade_count = 0;
    }
    fade_mode = FD_MODE_STOP;
}

s32 kzTD_Set_Fade(s32 mode) {
	s32 ret = FD_STATUS_HALF;

    fade_mode = mode;
    if (fade_count == 0) {
        ret = FD_STATUS_IN_END;
    }
    if (fade_count == 30) {
        ret = FD_STATUS_OUT_END;
    }

    return ret;
}

void kzTD_Draw_Fade() {
    KZCOLOR col = { 0xFF, 0xFF, 0xFF, 0x80 };

    if (fade_mode > 0) {
        if (fade_count < 1) {
            fade_count = 0;
        } else {
            fade_count--;
        }
    } else if (fade_mode < 0) {
        if (fade_count >= 30) {
            fade_count = 30;
        } else {
            fade_count++;
        }
    }

    if (fade_count != 0) {
        nkGsSetNormalFZ2();
        kz_Set_Alpha(2, SCE_GS_BLEND_RGB_0, SCE_GS_BLEND_RGB_SRC, SCE_GS_BLEND_ALPHA_SRC, SCE_GS_BLEND_RGB_DST, 0x80);
        kz_Set_Test(2, SCE_GS_TRUE, SCE_GS_ALPHA_ALWAYS, 0, SCE_GS_AFAIL_KEEP, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZALWAYS);
        col.a = (fade_count << 7) / 30;
        kz_Set_TileF4(&ORIGIN, 0xFFFF, &FULLSCR, &col);
    }
}

void kzTD_Clear_LastInfo() {
    SELECT_INFO *select;
    s32 i;

    for (i = 0; i < 51; i++) {
        select = Selectors[i];
        select->lst_page = 0;
        select->lst_plate = 0;
    }
}

s8 kzTD_Get_IdxPlate(s32 sel_no) {
	SELECT_INFO *select = Selectors[sel_no];
    return select->idx_plate;
}

u8 kzTD_Get_SelFlag(s32 sel_no) {
    SELECT_INFO *select = Selectors[sel_no];
    PLATE_INFO *plate = select->plates[select->idx_plate];
    return plate->sel_flag;
}

s32 kzTD_Get_PuppetID(s32 sel_no, s32 idx) {
    PARA_DC_EX3 *para = Selectors[sel_no]->plates[kzTD_Get_IdxPlate(sel_no)]->dc_para;
    return para->pup_id[idx];
}

void kzTD_Set_PlateDisp(s32 sel_no, s32 idx, u8 flag) {
    PLATE_INFO *plate = Selectors[sel_no]->plates[idx];
    plate->disp_flag = flag;
    FlushCache(WRITEBACK_DCACHE);
}

void kzTD_Set_PlateStr(s32 sel_no, s32 idx, s16 *str) {
    PARA_DC_EX2 *para = Selectors[sel_no]->plates[idx]->dc_para;
    s32 i;

    for (i = 0; i < 10; i++) {
        para->str_array[i] = str[i];
    }

    FlushCache(WRITEBACK_DCACHE);
}

// https://decomp.me/scratch/CEhzV
static s32 kzTD_Get_RowDisp(SELECT_INFO *select, s32 row_no) {
    s32 i;
    s32 count = 0;
    s32 idx_top = row_no * select->num_plate_vert;
    s32 idx_cur;
    
    // this is some bs
    for (i = 0; i < select->num_plate_vert && (idx_cur = idx_top + i) < select->num_plate_all; i++) {
        if (select->plates[idx_cur]->disp_flag) {
            count++;
        }
    }

    return count;
}

static GIM_FORM* kzTD_Get_PlateForm(PLATE_INFO *plate) {
    return PlateForms[plate->form_no][plate->sel_flag];
}

static void kzTD_Set_PlateParam(PLATE_INFO *plate) {
    switch (plate->form_no) {
        case FORM_LONG:
            PUP_H = 17;
            PUP_STOP = 12;
            PUP_DIV = 14;
            PROT_INIT = 0.17453289f;
            PROT_DIV = 15;
            PROT_SUB = 0.024543688f;
            break;
        case FORM_NARROW:
        case FORM_NARROW_EX:
            PUP_H = 16;
            PUP_STOP = 12;
            PUP_DIV = 14;
            PROT_INIT = 0.10833076f;
            PROT_DIV = 15;
            PROT_SUB = 0.024543688f;
            break;
        case FORM_NARROWx2:
        case FORM_NARROWx2_EX:
            PUP_H = 22;
            PUP_STOP = 12;
            PUP_DIV = 14;
            PROT_INIT = 0.12566368f;
            PROT_DIV = 15;
            PROT_SUB = 0.024543688f;
            break;
        case FORM_NORMAL:
            PUP_H = 17;
            PUP_STOP = 12;
            PUP_DIV = 14;
            PROT_INIT = 0.1963495f;
            PROT_DIV = 15;
            PROT_SUB = 0.024543688f;
            break;
        case FORM_VERYLONG:
            PUP_H = 24;
            PUP_STOP = 12;
            PUP_DIV = 14;
            PROT_INIT = 0.104719736f;
            PROT_DIV = 15;
            PROT_SUB = 0.024543688f;
            break;
        default:
            break;
    }
}

static void kzTD_Draw_AlphaBase(PLATE_INFO *plate) {
    GIM_FORM *form = kzTD_Get_PlateForm(plate);
    DVECTOR uv0;
    DVECTOR uv1;
    DVECTOR uv2;
    DVECTOR uv3;
    sceVu0IVECTOR crd0;
    sceVu0IVECTOR crd1;
    sceVu0IVECTOR crd2;
    sceVu0IVECTOR crd3;
    s32 x0 = 0;
    s32 y0 = 0;
    s32 x1 = (form->wh.vx - 1) << 4;
    s32 y1 = (form->wh.vy - 1) << 4;

    SETVEC(crd0, x0, y0, 0xFFFF, 0);
    SETVEC(crd1, x1, y0, 0xFFFF, 0);
    SETVEC(crd2, x0, y1, 0xFFFF, 0);
    SETVEC(crd3, x1, y1, 0xFFFF, 0);

    kz_Set_Test(2, SCE_GS_TRUE, SCE_GS_ALPHA_NEVER, 0, SCE_GS_AFAIL_FB_ONLY, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZALWAYS);
    kz_Set_PolyF4(&crd0, &crd1, &crd2, &crd3, &A_OFF);
    kz_Set_Tex0_Imd(form->tex0);

    SETDVEC(uv0, form->uv.vx,               form->uv.vy);
    SETDVEC(uv1, form->uv.vx + form->wh.vx, form->uv.vy);
    SETDVEC(uv2, form->uv.vx,               form->uv.vy + form->wh.vy);
    SETDVEC(uv3, form->uv.vx + form->wh.vx, form->uv.vy + form->wh.vy);

    kz_Set_PolyFT4UV(&crd0, &crd1, &crd2, &crd3, &uv0, &uv1, &uv2, &uv3, &A_ON);
}

static void kzTD_Draw_AlphaMask(PLATE_INFO *plate, s16 io_count, s16 delay) {
	GIM_FORM *form = kzTD_Get_PlateForm(plate);
	sceVu0IVECTOR crd0;
	sceVu0IVECTOR crd1;
	sceVu0IVECTOR crd2;
	sceVu0IVECTOR crd3;
	sceVu0IVECTOR crd4;
	sceVu0IVECTOR crd5;
	sceVu0IVECTOR crd6;
    s32 x0 = 0;
	s32 y0 = 0;
    s32 x1 = (form->wh.vx - 1) << 4;
	s32 y1 = (form->wh.vy - 1) << 4;
	s32 count;
	s32 move;
	s32 trans_gap = _sin(KL2_PI4) / _cos(KL2_PI4) * y1;
	s32 trans_wl = trans_gap + 1600;
    s32 mask_w = x1 + trans_wl;

    SETVEC(crd0, x0, y0, 0xFFFF, 0);
    SETVEC(crd1, x1, y0, 0xFFFF, 0);
    SETVEC(crd2, x0, y1, 0xFFFF, 0);
    SETVEC(crd3, x1, y1, 0xFFFF, 0);
    kz_Set_Test(2, SCE_GS_TRUE, SCE_GS_ALPHA_NEVER, 0, SCE_GS_AFAIL_FB_ONLY, SCE_GS_TRUE, 1, SCE_GS_TRUE, SCE_GS_ZALWAYS);

    if (io_count > 0) {
        count = io_count - delay;
        if (count < 0) {
            count = 0;
        }

        move = count * 320;
        if (move > mask_w) {
            move = mask_w;
            plate->status = PL_STATUS_IN_END;
        } else {
            plate->status = PL_STATUS_IN;
        }

        crd0[0] += move;
        crd1[0] += move;
        crd2[0] += move;
        crd3[0] += move;
        SETVEC(crd4, move - trans_gap, y1, 0xFFFF, 0);
        SETVEC(crd5, move - 1600,      y0, 0xFFFF, 0);
        SETVEC(crd6, move - trans_wl,  y1, 0xFFFF, 0);
        kz_Set_PolyF4(&crd0, &crd1, &crd4, &crd3, &A_OFF);
        kz_Set_PolyG4(&crd5, &crd0, &crd6, &crd4, &A_ON, &A_OFF, &A_ON, &A_OFF);
        return;
    } else if (io_count < 0) {
        count = io_count + delay;
        if (count > 0) {
            count = 0;
        }

        move = -count * 320;
        if (move > mask_w) {
            move = mask_w;
            plate->status = PL_STATUS_OUT_END;
        } else {
            plate->status = PL_STATUS_OUT;
        }
    } else {
        move = 0;
        plate->status = PL_STATUS_IN_END;
    }

    move -= mask_w;
    crd0[0] += move;
    crd1[0] += move;
    crd2[0] += move;
    crd3[0] += move;
    SETVEC(crd4, move + x1 + trans_gap, y0, 0xFFFF, 0);
    SETVEC(crd5, move + mask_w,         y0, 0xFFFF, 0);
    SETVEC(crd6, move + x1 + 1600,      y1, 0xFFFF, 0);
    kz_Set_PolyF4(&crd0, &crd4, &crd2, &crd3, &A_OFF);
    kz_Set_PolyG4(&crd4, &crd5, &crd3, &crd6, &A_OFF, &A_ON, &A_OFF, &A_ON);
}

static void kzTD_Move_Plate_Crd(SELECT_INFO *select, PLATE_INFO *plate, DVECTOR *sxy, u32 sz, sceVu0IVECTOR *crd0, sceVu0IVECTOR *crd1, sceVu0IVECTOR *crd2, sceVu0IVECTOR *crd3, sceVu0IVECTOR *crd4, sceVu0IVECTOR *crd5, sceVu0IVECTOR *crd6, sceVu0IVECTOR *crd7) {
    s32 i;
    s32 move;
    s32 move_x;
    s32 move_y;
    s32 diff = 0;
    s32 sign;
    f32 rot;
    DVECTOR wh = kzTD_Get_PlateForm(plate)->wh;
    sceVu0FMATRIX mat;
    sceVu0FVECTOR fcenter;
    sceVu0FVECTOR fcrd;
    sceVu0IVECTOR icenter;
    sceVu0IVECTOR *crd_nml;
    sceVu0IVECTOR *crd_shd;
    sceVu0IVECTOR *nml_array[4] = { crd0, crd1, crd2, crd3 };
    sceVu0IVECTOR *shd_array[4] = { crd4, crd5, crd6, crd7 };

    if (select->pop_count > 0) {
        if (select->pop_count > PUP_STOP) {
            plate->status = PL_STATUS_UP_END;
            select->sway_count = 1;
            move = PUP_H * _sin(KL2_PI * (f32)PUP_STOP / (f32)PUP_DIV);
        } else {
            plate->status = PL_STATUS_UP;
            move = PUP_H * _sin(KL2_PI * (f32)select->pop_count / (f32)PUP_DIV);
        }
    } else {
        plate->status = PL_STATUS_UP_END;
        move = PUP_H * _sin(KL2_PI * (f32)PUP_STOP / (f32)PUP_DIV);
    }
    move_x = move << 4;
    move_y = move << 3;

    if (select->sway_count > 0) {
        for (i = 0, sign = 0, rot = PROT_INIT; i < select->sway_count; i += PROT_DIV) {
            rot -= PROT_SUB;
            sign = !sign;
            diff = select->sway_count - i;
        }
        if (rot > 0.0f) {
            select->sway_count++;
            rot *= _sin(KL2_PI * diff / (f32)PROT_DIV);
            if (sign) {
                rot = -rot;
            }
        } else {
            select->sway_count = 0;
            rot = 0.0f;
        }
    } else {
        rot = 0.0f;
    }

    if (!plate->pop_flag) {
        move_x = move_y = 0;
        rot = 0.0f;
    }

    SETVEC_XY(icenter, sxy->vx + wh.vx / 2, sxy->vy + wh.vy / 2);
    icenter[2] = icenter[3] = 0;
    sceVu0ITOF0Vector(fcenter, icenter);

    (*crd0)[0] = (*crd2)[0] = -(wh.vx / 2);
    (*crd1)[0] = (*crd3)[0] = wh.vx - wh.vx / 2 - 1;
    (*crd0)[1] = (*crd1)[1] = -(wh.vy / 2);
    (*crd2)[1] = (*crd3)[1] = wh.vy - wh.vy / 2 - 1;
    (*crd0)[3] = (*crd1)[3] = (*crd2)[3] = (*crd3)[3] = 0;
    (*crd0)[2] = (*crd1)[2] = (*crd2)[2] = (*crd3)[2] = 0;

    sceVu0UnitMatrix(mat);
    sceVu0RotMatrixZ(mat, mat, rot);

    for (i = 0; i < 4; i++) {
        crd_nml = nml_array[i];
        crd_shd = shd_array[i];
        sceVu0ITOF0Vector(fcrd, *crd_nml);
        sceVu0ApplyMatrix(fcrd, mat, fcrd);
        sceVu0AddVector(fcrd, fcrd, fcenter);
        sceVu0FTOI4Vector(*crd_shd, fcrd);
        (*crd_shd)[1] >>= 1;
        (*crd_nml)[2] = (*crd_shd)[2] = sz;
        (*crd_nml)[3] = (*crd_shd)[3] = 0;

        (*crd_nml)[0] = (*crd_shd)[0] - move_x;
        (*crd_nml)[1] = (*crd_shd)[1] - move_y;
        (*crd_nml)[2] = (*crd_shd)[2];
        (*crd_nml)[3] = (*crd_shd)[3];
        (*crd_shd)[0] -= move_x / 4;
        (*crd_shd)[1] -= move_y / 4;
    }
}

static s32 kzTD_Check_Plate_Status(SELECT_INFO *select, s32 mode, s16 status) {
    PLATE_INFO *plate;
    s32 i;
    s32 j;
    s32 idx_cur;
    s32 ret = 1;

    switch (mode) {
        case SEL_IS:
            if (status != select->plates[select->idx_plate]->status) {
                ret = 0;
            }
            break;
        case SEL_ISNOT:
            if (status == select->plates[select->idx_plate]->status) {
                ret = 0;
            }
            break;
        case ALL_ARE:
            for (i = 0; i < select->num_row; i++) {
                if (i < select->idx_page) {
                    continue;
                }
                if (i >= select->idx_page + select->num_plate_hori) {
                    break;
                }

                for (j = 0; j < select->num_plate_vert; j++) {
                    idx_cur = i * select->num_plate_vert + j;
                    if (idx_cur >= select->num_plate_all) {
                        break;
                    }
                    plate = select->plates[idx_cur];
                    if (plate->disp_flag && status != plate->status) {
                        ret = 0;
                    }
                }
            }
            break;
        case ALL_ARENOT:
            for (i = 0; i < select->num_row; i++) {
                if (i < select->idx_page) {
                    continue;
                }
                if (i >= select->idx_page + select->num_plate_hori) {
                    break;
                }

                for (j = 0; j < select->num_plate_vert; j++) {
                    idx_cur = i * select->num_plate_vert + j;
                    if (idx_cur >= select->num_plate_all) {
                        break;
                    }
                    plate = select->plates[idx_cur];
                    if (plate->disp_flag && status == plate->status) {
                        ret = 0;
                    }
                }
            }
            break;
        default:
            ret = 0;
            break;
    }

    return ret;
}

void kzTD_Draw_Plate_Std(void *arg, s32 idx) {
    SELECT_INFO *select = arg;
    PLATE_INFO *plate = select->plates[idx];
    GIM_FORM *form = kzTD_Get_PlateForm(plate);
    DVECTOR pos;
    sceVu0IVECTOR crd0;
    sceVu0IVECTOR crd1;
    sceVu0IVECTOR crd2;
    sceVu0IVECTOR crd3;
    sceVu0IVECTOR crd4;
    sceVu0IVECTOR crd5;
    sceVu0IVECTOR crd6;
    sceVu0IVECTOR crd7;
    DVECTOR uv0;
    DVECTOR uv1;
    DVECTOR uv2;
    DVECTOR uv3;
    s32 line_no;
    s32 row_no;
    s32 idx_top;
    s32 shadow = 0;
    s32 delay;

    kzTD_Set_PlateParam(plate);
    line_no = idx % select->num_plate_vert;
    row_no = idx / select->num_plate_vert - select->idx_page;
    pos.vx = select->base.vx + select->row_offset[row_no];
    pos.vy = select->base.vy + select->line_offset[line_no];
    idx_top = select->idx_page * select->num_plate_vert;
    delay = select->delay[idx - idx_top];
    nkGsSetEffectFZ2();
    kzTD_Draw_AlphaBase(plate);
    if (select->io_count != 0) {
        kzTD_Draw_AlphaMask(plate, select->io_count, delay);
        SETVEC(crd0, pos.vx << 4, pos.vy << 3, 0xFFFF, 1);
        SETVEC(crd1, (pos.vx + form->wh.vx - 1) << 4, pos.vy << 3, 0xFFFF, 1);
        SETVEC(crd2, pos.vx << 4, (pos.vy + form->wh.vy - 1) << 3, 0xFFFF, 1);
        SETVEC(crd3, (pos.vx + form->wh.vx - 1) << 4, (pos.vy + form->wh.vy - 1) << 3, 0xFFFF, 1);
    } else if (select->idx_plate == idx) {
        if (select->pop_count >= 0) {
            shadow = 1;
            kzTD_Move_Plate_Crd(select, plate, &pos, 0xFFFF, &crd0, &crd1, &crd2, &crd3, &crd4, &crd5, &crd6, &crd7);
        } else {
            if (select->pop_count < -10) {
                plate->status = PL_STATUS_DOWN_END;
            } else {
                plate->status = PL_STATUS_DOWN;
            }
            SETVEC(crd0, pos.vx << 4, pos.vy << 3, 0xFFFF, 1);
            SETVEC(crd1, (pos.vx + form->wh.vx - 1) << 4, pos.vy << 3, 0xFFFF, 1);
            SETVEC(crd2, pos.vx << 4, (pos.vy + form->wh.vy - 1) << 3, 0xFFFF, 1);
            SETVEC(crd3, (pos.vx + form->wh.vx - 1) << 4, (pos.vy + form->wh.vy - 1) << 3, 0xFFFF, 1);
        }
    } else {
        plate->status = PL_STATUS_IN_END;
        SETVEC(crd0, pos.vx << 4, pos.vy << 3, 0xFFFF, 1);
        SETVEC(crd1, (pos.vx + form->wh.vx - 1) << 4, pos.vy << 3, 0xFFFF, 1);
        SETVEC(crd2, pos.vx << 4, (pos.vy + form->wh.vy - 1) << 3, 0xFFFF, 1);
        SETVEC(crd3, (pos.vx + form->wh.vx - 1) << 4, (pos.vy + form->wh.vy - 1) << 3, 0xFFFF, 1);
    }

    kz_Set_Test(2, SCE_GS_TRUE, SCE_GS_ALPHA_NEVER, 0, SCE_GS_AFAIL_RGB_ONLY, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZALWAYS);
    plate->dc_func(select, idx);
    kz_Set_Texflush();
    nkGsSetNormalFZ2();
    kz_Set_Test(2, SCE_GS_TRUE, SCE_GS_ALPHA_GREATER, 0, SCE_GS_AFAIL_KEEP, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZALWAYS);

    SETDVEC(uv0, ORIGIN.vx, ORIGIN.vy);
    SETDVEC(uv1, ORIGIN.vx + form->wh.vx, ORIGIN.vy);
    SETDVEC(uv2, ORIGIN.vx, ORIGIN.vy + form->wh.vy);
    SETDVEC(uv3, ORIGIN.vx + form->wh.vx, ORIGIN.vy + form->wh.vy);

    if (shadow) {
        kz_Set_Tex0(0x1680, 10, SCE_GS_PSMCT32, 10, 8, 1, SCE_GS_MODULATE, 0x0000, SCE_GS_PSMCT32, 0, 0, 0);
        kz_Set_PolyFT4UV(&crd4, &crd5, &crd6, &crd7, &uv0, &uv1, &uv2, &uv3, &GCOL_PSH);
    }
    kz_Set_Tex0(0x1680, 10, SCE_GS_PSMCT32, 10, 8, 1, SCE_GS_DECAL, 0x0000, SCE_GS_PSMCT32, 0, 0, 0);
    kz_Set_PolyFT4UV(&crd0, &crd1, &crd2, &crd3, &uv0, &uv1, &uv2, &uv3, &GCOL_STD);
}

void kzTD_Draw_Contents_Std(void *arg, s32 idx) {
    SELECT_INFO *select = arg;
    PLATE_INFO *plate = select->plates[idx];
    PARA_DC_STD *para = plate->dc_para;
    GIM_FORM *form = kzTD_Get_PlateForm(plate);

    kz_Set_Tex0_Imd(form->tex0);
    kz_Set_SprtUV_Eff(&ORIGIN, 0xFFFF, &form->wh, &form->uv, &GCOL_STD);
    kzSTR_Draw_Eff(&para->str_offset, 0xFFFF, &plate->fcol[plate->sel_flag], para->str_no);
}

void kzTD_Draw_Contents_Gim(void *arg, s32 idx) {
    SELECT_INFO *select = arg;
    PLATE_INFO *plate = select->plates[idx];
    PARA_DC_GIM *para = plate->dc_para;
    GIM_FORM *form;

    form = kzTD_Get_PlateForm(plate);
    kz_Set_Tex0_Imd(form->tex0);
    kz_Set_SprtUV_Eff(&ORIGIN, 0xFFFF, &form->wh, &form->uv, &GCOL_STD);

    form = GimForms[para->gim_no];
    kz_Set_Tex0_Imd(form->tex0);
    kz_Set_SprtUV_Eff(&para->gim_offset, 0xFFFF, &form->wh, &form->uv, &GCOL_STD);

    kzSTR_Draw_Eff(&para->str_offset, 0xFFFF, &plate->fcol[plate->sel_flag], para->str_no);
}

void kzTD_Draw_Contents_Stt(void *arg, s32 idx) {
    SELECT_INFO *select = arg;
    PLATE_INFO *plate = select->plates[idx];
    PARA_DC_EX0 *para = plate->dc_para;
    GIM_FORM *form = kzTD_Get_PlateForm(plate);
    KZCOLOR *fcol;
    s32 doll;

    switch (idx) {
        case 0:
            doll = 6;
            break;
        case 1:
            doll = 3;
            break;
        case 2:
            doll = 4;
            break;
        case 3:
            doll = 1;
            break;
        default:
            doll = 6;
            break;
    }

    form = kzTD_Get_PlateForm(plate);
    kz_Set_Tex0_Imd(form->tex0);
    kz_Set_SprtUV_Eff(&ORIGIN, 0xFFFF, &form->wh, &form->uv, &GCOL_STD);

    fcol = &plate->fcol[plate->sel_flag];
    if (idx != 18) {
        if (idx != 8 && idx != 9) {
            if (doll >= 6) {
                kzGIM_Draw_Eff(&GIMOFFSET_DOLL, 0xFFFF, &GCOL_STD, GIM_SEL0112);
            } else {
                kzGIM_Draw_Eff(&GIMOFFSET_DOLL, 0xFFFF, &GCOL_STD, GIM_SEL0107);
                kzGIM_Draw_Eff(&GIMOFFSET_SLASH, 0xFFFF, fcol, GIM_CHR_SLASH);
                kzNUM_Draw_Eff(&NUMOFFSET_DOLL0, 0xFFFF, fcol, 0, 1, doll);
                kzNUM_Draw_Eff(&NUMOFFSET_DOLL1, 0xFFFF, fcol, 0, 1, 6);
            }
        }
    }

    kzSTR_Draw_Eff(&para->str_offset, 0xFFFF, fcol, para->str_no);
}

void kzTD_Draw_Contents_Gjk(void *arg, s32 idx) {
    SELECT_INFO *select = arg;
    PLATE_INFO *plate = select->plates[idx];
    PARA_DC_EX1 *para = plate->dc_para;
    GIM_FORM *form = kzTD_Get_PlateForm(plate);
    KZCOLOR *fcol;

    kz_Set_Tex0_Imd(form->tex0);
    kz_Set_SprtUV_Eff(&ORIGIN, 0xFFFF, &form->wh, &form->uv, &GCOL_STD);
    fcol = &plate->fcol[plate->sel_flag];
    kzSTR_Draw_Eff(&para->str_offset, 0xFFFF, &plate->fcol[plate->sel_flag], para->str_no);
    kzNUM_Draw_Eff(&NUMOFFSET_GENJU, 0xFFFF, fcol, 0, 8, 1234567);

}

void kzTD_Draw_Contents_Fil(void *arg, s32 idx) {
    SELECT_INFO *select = arg;
    PLATE_INFO *plate = select->plates[idx];
    PARA_DC_EX2 *para = plate->dc_para;
    GIM_FORM *form = kzTD_Get_PlateForm(plate);

    kz_Set_Tex0_Imd(form->tex0);
    kz_Set_SprtUV_Eff(&ORIGIN, 0xFFFF, &form->wh, &form->uv, &GCOL_STD);
    kzSTR_Draw_Direct_Eff(&para->str_offset, 0xFFFF, &plate->fcol[plate->sel_flag], para->str_array);
}

void kzTD_Draw_Contents_Tht(void *arg, s32 idx) {
    SELECT_INFO *select = arg;
    PLATE_INFO *plate = select->plates[idx];
    PARA_DC_EX3 *para = plate->dc_para;
    GIM_FORM *form = kzTD_Get_PlateForm(plate);

    kz_Set_Tex0_Imd(form->tex0);
    kz_Set_SprtUV_Eff(&ORIGIN, 0xFFFF, &form->wh, &form->uv, &GCOL_STD);
    kzSTR_Draw_Eff(&para->str_offset, 0xFFFF, &plate->fcol[plate->sel_flag], para->str_no);
}

void kzTD_Draw_Mark_Std(void *arg) {
    SELECT_INFO *select = arg;
    sceVu0IVECTOR crd0;
    sceVu0IVECTOR crd1;
    sceVu0IVECTOR crd2;
    s32 row_no;
    DVECTOR pos;

    select->mark_count++;
    if (select->mark_count > 45) {
        select->mark_count = 0;
    }

    if (select->mark_count <= 30) {
        nkGsSetNormalFZ2();
        kz_Set_Test(2, SCE_GS_TRUE, SCE_GS_ALPHA_ALWAYS, 0, SCE_GS_AFAIL_KEEP, SCE_GS_FALSE, 0, SCE_GS_TRUE, SCE_GS_ZALWAYS);
        crd0[2] = crd1[2] = crd2[2] = 0xFFFF;

        row_no = select->idx_page - 1;
        if (row_no >= 0) {
            if (kzTD_Get_RowDisp(select, row_no) > 0) {
                SETDVEC(pos, select->base.vx + select->mark_L.vx, select->base.vy + select->mark_L.vy);
                kzGIM_Draw(&pos, 0xFFFF, &GCOL_STD, GIM_SEL0401);
            }
        }

        row_no = select->idx_page + select->num_plate_hori;
        if (row_no < select->num_row) {
            if (kzTD_Get_RowDisp(select, row_no) > 0) {
                SETDVEC(pos, select->base.vx + select->mark_R.vx, select->base.vy + select->mark_R.vy);
                kzGIM_Draw(&pos, 0xFFFF, &GCOL_STD, GIM_SEL0400);
            }
        }
    }
}

void kzTD_CsrMove_Up(s32 sel_no) {
    SELECT_INFO *select = Selectors[sel_no];
    s32 row_no = select->idx_plate / select->num_plate_vert;
    s32 line_no = kzTD_Get_RowDisp(select, row_no);
    s32 idx_top;

    if (line_no < 2) {
        return;
    }

    select->sway_count = 0;
    select->plates[select->idx_plate]->sel_flag = 0;
    idx_top = row_no * select->num_plate_vert;
    do {
        if (select->idx_plate - idx_top <= 0) {
            select->idx_plate += select->num_plate_vert - 1;
            if (select->idx_plate >= select->num_plate_all) {
                select->idx_plate = select->num_plate_all - 1;
            }
        } else {
            select->idx_plate--;
        }
    } while (!select->plates[select->idx_plate]->disp_flag);

    select->plates[select->idx_plate]->sel_flag = 1;
    hSeKeyOn(KL2_VAG(2, 10, 0, 0, 10, 0x1C, 1200, 1200), NULL, 0);
}

void kzTD_CsrMove_Down(s32 sel_no) {
    SELECT_INFO *select = Selectors[sel_no];
    s32 row_no = select->idx_plate / select->num_plate_vert;
    s32 line_no = kzTD_Get_RowDisp(select, row_no);
    s32 idx_top;

    if (line_no < 2) {
        return;
    }

    select->sway_count = 0;
    select->plates[select->idx_plate]->sel_flag = 0;
    idx_top = row_no * select->num_plate_vert;
    do {
        if (select->idx_plate - idx_top >= select->num_plate_vert - 1 || select->idx_plate >= select->num_plate_all - 1) {
            select->idx_plate = idx_top;
        } else {
            select->idx_plate++;
        }
    } while (!select->plates[select->idx_plate]->disp_flag);

    select->plates[select->idx_plate]->sel_flag = 1;
    hSeKeyOn(KL2_VAG(2, 10, 0, 0, 10, 0x1C, 1200, 1200), NULL, 0);
}

void kzTD_CsrMove_Left(s32 sel_no) {
	SELECT_INFO *select = Selectors[sel_no];
    s32 row_no = select->idx_plate / select->num_plate_vert - 1;
    s32 line_no;
    s32 idx_new;
    s32 idx_top;

    if (row_no < 0 || kzTD_Get_RowDisp(select, row_no) < 1) {
        return;
    }

    idx_top = row_no * select->num_plate_vert;
    idx_new = select->idx_plate - select->num_plate_vert + 1;
    if (idx_new < 1) {
        idx_new = 1;
    }
    
    do {
        idx_new--;
        line_no = idx_new - idx_top;
    } while (line_no >= 0 && !select->plates[idx_new]->disp_flag);

    if (line_no < 0) {
        idx_new = select->idx_plate - select->num_plate_vert - 1;
        do {
            idx_new++;
            if (idx_new >= select->num_plate_all) {
                break;
            }
            line_no = idx_new - idx_top;
        } while (line_no < select->num_plate_vert && !select->plates[idx_new]->disp_flag);
    }

    if (idx_new >= select->num_plate_all || line_no >= select->num_plate_vert) {
        return;
    }

    select->sway_count = 0;
    select->plates[select->idx_plate]->sel_flag = 0;
    if (row_no < select->idx_page) {
        select->idx_page = row_no;
        select->mark_count = 0;
    }
    select->idx_plate = idx_new;
    select->plates[select->idx_plate]->sel_flag = 1;

    hSeKeyOn(KL2_VAG(2, 10, 0, 0, 10, 0x1C, 1200, 1200), NULL, 0);
}

void kzTD_CsrMove_Right(s32 sel_no) {
    SELECT_INFO *select = Selectors[sel_no];
    s32 row_no = select->idx_plate / select->num_plate_vert + 1;
    s32 line_no;
    s32 idx_new;
    s32 idx_top;

    if (row_no >= select->num_row || kzTD_Get_RowDisp(select, row_no) < 1) {
        return;
    }

    idx_top = row_no * select->num_plate_vert;
    idx_new = select->idx_plate + select->num_plate_vert + 1;
    if (idx_new > select->num_plate_all) {
        idx_new = select->num_plate_all;
    }
    
    do {
        idx_new--;
        line_no = idx_new - idx_top;
    } while (line_no >= 0 && !select->plates[idx_new]->disp_flag);

    if (line_no < 0) {
        idx_new = select->idx_plate + select->num_plate_vert - 1;
        do {
            idx_new++;
            if (idx_new >= select->num_plate_all) {
                break;
            }
            line_no = idx_new - idx_top;
        } while (line_no < select->num_plate_vert && !select->plates[idx_new]->disp_flag);
    }

    if (idx_new >= select->num_plate_all || line_no >= select->num_plate_vert) {
        return;
    }

    select->sway_count = 0;
    select->plates[select->idx_plate]->sel_flag = 0;
    if (row_no >= select->idx_page + select->num_plate_hori) {
        select->idx_page = row_no - select->num_plate_hori + 1;
        select->mark_count = 0;
    }
    select->idx_plate = idx_new;
    select->plates[select->idx_plate]->sel_flag = 1;

    hSeKeyOn(KL2_VAG(2, 10, 0, 0, 10, 0x1C, 1200, 1200), NULL, 0);
}

void kzTD_PageMove_Left(s32 sel_no) {
    SELECT_INFO *select = Selectors[sel_no];
    s32 row_no = select->idx_page - 1;
    s32 line_no;
    s32 idx_new;
    s32 idx_top;
    
    if (row_no < 0 || kzTD_Get_RowDisp(select, row_no) < 1) {
        return;
    }

    row_no = select->idx_plate / select->num_plate_vert;
    if (row_no == select->idx_page + select->num_plate_hori - 1)  {
        row_no--;
        if (kzTD_Get_RowDisp(select, row_no) < 1) {
            return;
        }

        idx_top = row_no * select->num_plate_vert;
        idx_new = select->idx_plate - select->num_plate_vert + 1;
        if (idx_new < 1) {
            idx_new = 1;
        }
        do {
            idx_new--;
            line_no = idx_new - idx_top;
        } while (line_no >= 0 && !select->plates[idx_new]->disp_flag);
        if (line_no < 0) {
            idx_new = select->idx_plate - select->num_plate_vert - 1;
            do {
                idx_new++;
                if (idx_new >= select->num_plate_all) {
                    break;
                }
                line_no = idx_new - idx_top;
            } while (line_no < select->num_plate_vert && !select->plates[idx_new]->disp_flag);
        }
        if (idx_new >= select->num_plate_all || line_no >= select->num_plate_vert) {
            return;
        }

        select->sway_count = 0;
        if (select->plates[select->idx_plate]->sel_flag) {
            select->plates[select->idx_plate]->sel_flag = 0;
            select->plates[idx_new]->sel_flag = 1;
        }
        select->idx_plate = idx_new;
    }

    select->idx_page--;
    select->mark_count = 0;
    hSeKeyOn(KL2_VAG(2, 10, 0, 0, 10, 0x1C, 1200, 1200), NULL, 0);
}

void kzTD_PageMove_Right(s32 sel_no) {
    SELECT_INFO *select = Selectors[sel_no];
    s32 row_no = select->idx_page + select->num_plate_hori;
    s32 line_no;
    s32 idx_new;
    s32 idx_top;
    
    if (row_no >= select->num_row || kzTD_Get_RowDisp(select, row_no) < 1) {
        return;
    }

    row_no = select->idx_plate / select->num_plate_vert;
    if (row_no == select->idx_page)  {
        row_no++;
        if (kzTD_Get_RowDisp(select, row_no) < 1) {
            return;
        }

        idx_top = row_no * select->num_plate_vert;
        idx_new = select->idx_plate + select->num_plate_vert + 1;
        if (idx_new > select->num_plate_all) {
            idx_new = select->num_plate_all;
        }
        do {
            idx_new--;
            line_no = idx_new - idx_top;
        } while (line_no >= 0 && !select->plates[idx_new]->disp_flag);
        if (line_no < 0) {
            idx_new = select->idx_plate + select->num_plate_vert - 1;
            do {
                idx_new++;
                if (idx_new >= select->num_plate_all) {
                    break;
                }
                line_no = idx_new - idx_top;
            } while (line_no < select->num_plate_vert && !select->plates[idx_new]->disp_flag);
        }
        if (idx_new >= select->num_plate_all || line_no >= select->num_plate_vert) {
            return;
        }

        select->sway_count = 0;
        if (select->plates[select->idx_plate]->sel_flag) {
            select->plates[select->idx_plate]->sel_flag = 0;
            select->plates[idx_new]->sel_flag = 1;
        }
        select->idx_plate = idx_new;
    }

    select->idx_page++;
    select->mark_count = 0;
    hSeKeyOn(KL2_VAG(2, 10, 0, 0, 10, 0x1C, 1200, 1200), NULL, 0);
}

void kzTD_Init_Selector(s32 sel_no, s32 idx_page, s32 idx_plate) {
    SELECT_INFO *select = Selectors[sel_no];
    PLATE_INFO *plate;
    s32 i;

    if (idx_page < 0 || idx_plate < 0) {
        select->idx_page = select->lst_page;
        select->idx_plate = select->lst_plate;
    } else {
        select->idx_page = idx_page;
        select->idx_plate = idx_plate;
    }

    select->io_count = 1;
    select->pop_count = 0;
    select->sway_count = 0;
    select->mark_count = 0;
    for (i = 0; i < select->num_plate_all; i++) {
        plate = select->plates[i];
        plate->disp_flag = 1;
        plate->sel_flag = 0;
        plate->pop_flag = 1;
        plate->status = PL_STATUS_IN;
    }
}

s32 kzTD_Draw_Selector(s32 sel_no) {
    SELECT_INFO *select = Selectors[sel_no];
    PLATE_INFO *plate;
    s32 i;
    s32 j;
    s32 idx_cur;

    kzTD_Set_GsEnv_Std();
    if (kzTD_Check_Plate_Status(select, ALL_ARE, PL_STATUS_OUT_END)) {
        select->io_count = 0;
        select->pop_count = 0;
        return SL_STATUS_OUT_END;
    }

    for (i = 0; i < select->num_row; i++) {
        if (i < select->idx_page) {
            continue;
        }
        if (i >= select->idx_page + select->num_plate_hori) {
            break;
        }
        
        for (j = 0; j < select->num_plate_vert; j++) {
            idx_cur = i * select->num_plate_vert + j;
            if (idx_cur >= select->num_plate_all) {
                break;
            }
            if (idx_cur != select->idx_plate) {
                plate = select->plates[idx_cur];
                if (plate->disp_flag) {
                    plate->dp_func(select, idx_cur);
                }
            }
        }
    }

    plate = select->plates[select->idx_plate];
    plate->dp_func(select, select->idx_plate);
    if (kzTD_Check_Plate_Status(select, SEL_IS, PL_STATUS_UP_END)) {
        select->dm_func(select);
    }

    if (select->pop_count > 0) {
        select->pop_count++;
        if (kzTD_Check_Plate_Status(select, SEL_IS, PL_STATUS_UP_END)) {
            select->io_count = 0;
            select->pop_count = 0;
        }
        return SL_STATUS_IN;
    }
    if (select->pop_count < 0) {
        select->pop_count--;
        if (kzTD_Check_Plate_Status(select, SEL_IS, PL_STATUS_DOWN_END)) {
            select->io_count = -1;
            select->pop_count = 0;
        }
        return SL_STATUS_OUT;
    }

    if (select->io_count > 0) {
        select->io_count++;
        if (kzTD_Check_Plate_Status(select, ALL_ARE, PL_STATUS_IN_END)) {
            select->io_count = 0;
            select->pop_count = 1;
            select->plates[select->idx_plate]->sel_flag = 1;
        }
        return SL_STATUS_IN;
    }
    if (select->io_count < 0) {
        select->io_count--;
        return SL_STATUS_OUT;
    }
    return SL_STATUS_WAIT;
}

void kzTD_Close_Selector(s32 sel_no, s32 mode) {
    SELECT_INFO *select = Selectors[sel_no];
    PLATE_INFO *plate;

    if (mode == 0) {
        select->plates[select->idx_plate]->sel_flag = 0;
        hSeKeyOn(KL2_VAG(0, 10, 0, 0, 10, 0x1C, 1200, 1200), NULL, 0);
    } else {
        select->lst_page = select->idx_page;
        select->lst_plate = select->idx_plate;
        hSeKeyOn(KL2_VAG(1, 10, 0, 0, 10, 0x1C, 1200, 1200), NULL, 0);
    }
    select->io_count = 0;

    select->pop_count = -1;
    select->sway_count = 0;
}

void kzTD_Erase_Selector(s32 sel_no) {
    SELECT_INFO *select = Selectors[sel_no];
    PLATE_INFO *plate;
    s32 i;

    select->io_count = 0;
    select->pop_count = 0;
    for (i = 0; i < select->num_plate_all; i++) {
        plate = select->plates[i];
        plate->status = PL_STATUS_OUT_END;
    }
}

void kzTD_Init_SelViewer(s32 sel_no, s32 idx_page, s32 idx_plate) {
    SELECT_INFO *select = Selectors[sel_no];
    PLATE_INFO *plate;
    s32 i;

    kzTD_Init_Selector(sel_no, idx_page, idx_plate);
    select->io_count = 0;
    for (i = 0; i < select->num_plate_all; i++) {
        plate = select->plates[i];
        plate->pop_flag = 0;
        plate->status = PL_STATUS_IN_END;
    }
}

void kzTD_Draw_SelViewer(s32 sel_no) {
    SELECT_INFO *select = Selectors[sel_no];
    PLATE_INFO *plate;
    s32 i;
    s32 j;
    s32 idx_cur;

    kzTD_Set_GsEnv_Std();

    for (i = 0; i < select->num_row; i++) {
        if (i < select->idx_page) {
            continue;
        }
        if (i >= select->idx_page + select->num_plate_hori) {
            break;
        }
        
        for (j = 0; j < select->num_plate_vert; j++) {
            idx_cur = i * select->num_plate_vert + j;
            if (idx_cur >= select->num_plate_all) {
                break;
            }
            plate = select->plates[idx_cur];
            if (plate->disp_flag) {
                plate->dp_func(select, idx_cur);
            }
        }
    }

    select->dm_func(select);
    if (pPAD_TRG_LEFT(kpd0)) {
        kzTD_PageMove_Left(sel_no);
    }
    if (pPAD_TRG_RIGHT(kpd0)) {
        kzTD_PageMove_Right(sel_no);
    }
}

void kzTD_Draw_Ground(s32 grnd_no) {
    GROUND_INFO *ground = Grounds[grnd_no];
    GIM_FORM *form;
    DVECTOR pos;
    DVECTOR wh;
    s32 sidelen_H;
    s32 sidelen_V;

    if (ground->wh.vx < 2 || ground->wh.vy < 2) {
        return;
    }

    kzTD_Set_GsEnv_Std();
    sidelen_H = (ground->wh.vx - 2) << 4;
    sidelen_V = (ground->wh.vy - 2) << 4;
    SETDVEC(wh, 16, 16);
    SETDVEC(pos, ground->base.vx, ground->base.vy);
    
    form = ground->parts[5];
    kz_Set_Tex0_Imd(form->tex0);
    kz_Set_SprtUV(&pos, 0xFFFF, &wh, &form->uv, &GCOL_STD);

    pos.vx = ground->base.vx + 16 + sidelen_H;
    form = ground->parts[6];
    kz_Set_Tex0_Imd(form->tex0);
    kz_Set_SprtUV(&pos, 0xFFFF, &wh, &form->uv, &GCOL_STD);

    pos.vx = ground->base.vx;
    pos.vy = ground->base.vy + 16 + sidelen_V;
    form = ground->parts[7];
    kz_Set_Tex0_Imd(form->tex0);
    kz_Set_SprtUV(&pos, 0xFFFF, &wh, &form->uv, &GCOL_STD);

    pos.vx = ground->base.vx + 16 + sidelen_H;
    form = ground->parts[8];
    kz_Set_Tex0_Imd(form->tex0);
    kz_Set_SprtUV(&pos, 0xFFFF, &wh, &form->uv, &GCOL_STD);

    if (sidelen_H > 0) {
        wh.vx = sidelen_H;
        wh.vy = 16;

        pos.vx = ground->base.vx + 16;
        pos.vy = ground->base.vy;
        form = ground->parts[1];
        kz_Set_Clamp(2, SCE_GS_NEAREST_MIPMAP_LENEAR, SCE_GS_NEAREST_MIPMAP_LENEAR, 15, form->uv.vx, 15, form->uv.vy);
        kz_Set_Tex0_Imd(form->tex0);
        kz_Set_SprtUV(&pos, 0xFFFF, &wh, &form->uv, &GCOL_STD);

        pos.vy = ground->base.vy + 16 + sidelen_V;
        form = ground->parts[4];
        kz_Set_Clamp(2, SCE_GS_NEAREST_MIPMAP_LENEAR, SCE_GS_NEAREST_MIPMAP_LENEAR, 15, form->uv.vx, 15, form->uv.vy);
        kz_Set_Tex0_Imd(form->tex0);
        kz_Set_SprtUV(&pos, 0xFFFF, &wh, &form->uv, &GCOL_STD);
    }

    if (sidelen_V > 0) {
        wh.vx = 16;
        wh.vy = sidelen_V;

        pos.vx = ground->base.vx;
        pos.vy = ground->base.vy + 16;
        form = ground->parts[2];
        kz_Set_Clamp(2, SCE_GS_NEAREST_MIPMAP_LENEAR, SCE_GS_NEAREST_MIPMAP_LENEAR, 15, form->uv.vx, 15, form->uv.vy);
        kz_Set_Tex0_Imd(form->tex0);
        kz_Set_SprtUV(&pos, 0xFFFF, &wh, &form->uv, &GCOL_STD);

        pos.vx = ground->base.vx + 16 + sidelen_H;
        form = ground->parts[3];
        kz_Set_Clamp(2, SCE_GS_NEAREST_MIPMAP_LENEAR, SCE_GS_NEAREST_MIPMAP_LENEAR, 15, form->uv.vx, 15, form->uv.vy);
        kz_Set_Tex0_Imd(form->tex0);
        kz_Set_SprtUV(&pos, 0xFFFF, &wh, &form->uv, &GCOL_STD);
    }

    if (sidelen_H > 0 && sidelen_V > 0) {
        wh.vx = sidelen_H;
        wh.vy = sidelen_V;
        pos.vx = ground->base.vx + 16;
        pos.vy = ground->base.vy + 16;
        form = ground->parts[0];
        kz_Set_Clamp(2, SCE_GS_NEAREST_MIPMAP_LENEAR, SCE_GS_NEAREST_MIPMAP_LENEAR, 15, form->uv.vx, 15, form->uv.vy);
        kz_Set_Tex0_Imd(form->tex0);
        kz_Set_SprtUV(&pos, 0xFFFF, &wh, &form->uv, &GCOL_STD);
    }

    kz_Set_Clamp(2, SCE_GS_LINEAR, SCE_GS_LINEAR, 0, 0, 0, 0);
}

void kzTD_Draw_SendMes() {
    static s32 count = 0;
    DVECTOR pos;
    s32 rise;

    count++;
    if (count > 30) {
        count = 0;
    }

    if (count >= 16) {
        rise = 0;
        
    } else {
        rise = count / 2;
    }

    SETDVEC(pos, GIMBASE_SNDMES.vx, GIMBASE_SNDMES.vy - rise);
    kzGIM_Draw(&pos, 0xFFFF, &GCOL_STD, GIM_HANE01);
}

void kzTD_Init_Window(s32 win_no, s32 idx_page, s32 idx_plate) {
    WINDOW_INFO *window = Windows[win_no];
    GROUND_INFO *ground = Grounds[window->grnd_no];
    SELECT_INFO *select;
    PLATE_INFO *plate;
    s32 i;
    s32 sel_no = window->sel_no;

    window->status = WN_STATUS_WAIT;
    if (sel_no >= 0) {
        select = Selectors[sel_no];
        SETDVEC(select->base, ground->base.vx + window->sel_offset.vx, ground->base.vy + window->sel_offset.vy);
        kzTD_Init_Selector(sel_no, idx_page, idx_plate);
        select->io_count = 0;
        for (i = 0; i < select->num_plate_all; i++) {
            plate = select->plates[i];
            plate->status = PL_STATUS_IN_END;
        }
        plate = select->plates[select->idx_plate];
        plate->sel_flag = 1;
        plate->status = PL_STATUS_UP_END;
    }
}

s32 kzTD_Draw_Window(s32 win_no) {
    WINDOW_INFO *window = Windows[win_no];
    GROUND_INFO *ground;
    SELECT_INFO *select;
    DVECTOR pos;
    s32 grnd_no = window->grnd_no;
    s32 str_no = window->str_no;
    s32 sel_no = window->sel_no;

    if (window->status != WN_STATUS_WAIT) {
        return window->status;
    }
    if (grnd_no < 0) {
        return window->status;
    }

    ground = Grounds[grnd_no];
    kzTD_Draw_Ground(grnd_no);

    if (str_no >= 0) {
        SETDVEC(pos, ground->base.vx + window->str_offset.vx, ground->base.vy + window->str_offset.vy);
        kzSTR_Draw(&pos, 0xFFFF, &window->fcol, str_no);
    }

    if (sel_no >= 0) {
        str_no = kzTD_Draw_Selector(sel_no);
        if (str_no == SL_STATUS_WAIT) {
            if (pPAD_TRG_UP(kpd0)) kzTD_CsrMove_Up(sel_no);
            if (pPAD_TRG_DOWN(kpd0)) kzTD_CsrMove_Down(sel_no);
            if (pPAD_TRG_LEFT(kpd0)) kzTD_CsrMove_Left(sel_no);
            if (pPAD_TRG_RIGHT(kpd0)) kzTD_CsrMove_Right(sel_no);

            if (pPAD_TRG_CROSS(kpd0)) kzTD_Close_Selector(sel_no, 1);
        } else {
            select = Selectors[sel_no];
            if (select->io_count < 0) {
                kzTD_Erase_Selector(sel_no);
                window->status = select->idx_plate;
            }
        }
    }

    if (window->send_flag) {
        kzTD_Draw_SendMes();
        if (pPAD_TRG_CROSS(kpd0)) {
            window->status = WN_STATUS_00;
        }
    }

    return window->status;
}