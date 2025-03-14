#include "nakano/calc3d.h"

s32 nkVu0ClipScreen(sceVu0FVECTOR v0) {
    sceVu0IVECTOR vi;
    s32 flag;

    v0[3] = 1.0f;
    sceVu0RotTransPers(vi, GameGbl.wsm, v0, 1);
    vi[0] = (vi[0] - GS_X_COORD(0)) >> 4;
    vi[1] = (vi[1] - GS_Y_COORD(0)) >> 4;
    if (vi[0] < 0 || vi[0] > SCR_WIDTH || vi[1] < 0 || vi[1] > SCR_HEIGHT_PROG || vi[2] - 1 >= 0xFFFFFEU) {
        flag = 1;
    } else {
        flag = 0;
    }

    return flag;
}
