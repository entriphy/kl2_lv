#include "hoshino/h_game.h"
#include "hoshino/h_sound.h"
#include "hoshino/h_str.h"

BGMAREA v____[] = {
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f}
};

BGMAREA v0100[] = {
#ifdef KL2_VER_TRIAL
    {BGM001, 0, 0.0f, 1.0f},
    {BGM040, 0, 0.0f, 0.5f},
    {BGM058, 0, 0.0f, 1.0f},
#else
    {BGM000, 0, 0.0f, 60.0f},
    {BGM040, 0, 0.0f, 30.0f},
    {BGM058, 0, 0.0f, 60.0f},
    {BGM083, 0, 0.0f, 60.0f},
#endif
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f}
};

BGMAREA v0101[] = {
#ifdef KL2_VER_TRIAL
    {BGM001, 0, 0.0f, 1.0f},
#else
    {BGM000, 1, 0.0f, 60.0f},
#endif
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f}
};

BGMAREA v0102[] = {
#ifdef KL2_VER_TRIAL
    {BGM001, 0, 0.0f, 1.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
#else
    {BGM000, 0, 0.0f, 180.0f},
    {BGM001, 0, 0.0f, 60.0f},
#endif
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f}
};

BGMAREA v0103[] = {
#ifdef KL2_VER_TRIAL
    {BGM001, 0, 0.0f, 1.0f},
#else
    {BGM001, 0, 0.0f, 60.0f},
#endif
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f}
};

BGMAREA v0104[] = {
#ifdef KL2_VER_TRIAL
    {BGM001, 0, 0.0f, 1.0f},
    {BGM040, 0, 1.0f, 1.0f},
#else
    {BGM001, 0, 0.0f, 60.0f},
    {BGM062, 0, 0.0f, 60.0f},
#endif
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f}
};

#ifndef KL2_VER_TRIAL
BGMAREA v0105[] = {
    {BGM072, 0, 0.0f, 60.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f}
};

BGMAREA v0106[] = {
    {BGM076, 0, 0.0f, 60.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f}
};
#endif

BGMAREA v0500[] = {
#ifdef KL2_VER_TRIAL
    {BGM009, 0, 0.0f, 1.0f},
    {BGM060, 0, 0.0f, 1.0f},
#else
    {BGM009, 0, 0.0f, 60.0f},
    {BGM060, 0, 0.0f, 60.0f},
#endif
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f}
};

BGMAREA v0501[] = {
#ifdef KL2_VER_TRIAL
    {BGM009, 0, 0.0f, 1.0f},
#else
    {BGM009, 0, 0.0f, 60.0f},
#endif
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f}
};

BGMAREA v0502[] = {
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f}
};

BGMAREA v0503[] = {
#ifdef KL2_VER_TRIAL
    {BGM009, 0, 0.0f, 1.0f},
#else
    {BGM009, 1, 0.0f, 60.0f},
#endif
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f}
};

BGMAREA v0504[] = {
#ifdef KL2_VER_TRIAL
    {BGM009, 0, 0.0f, 1.0f},
#else
    {BGM009, 0, 0.0f, 60.0f},
#endif
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f}
};

BGMAREA v0505[] = {
#ifdef KL2_VER_TRIAL
    {BGM009, 0, 0.0f, 1.0f},
    {BGM045, 0, 0.0f, 1.0f},
    {BGM036, 0, 0.0f, 1.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
#else
    {BGM009, 1, 0.0f, 60.0f},
    {BGM080, 0, 0.0f, 60.0f},
    {BGM036, 0, 0.0f, 60.0f},
    {BGM079, 0, 0.0f, 60.0f},
#endif
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f},
    {BGM_NO, 0, 0.0f, 0.0f}
};

BGMAREA *BGMvision[][24] = {
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
#ifdef KL2_VER_TRIAL
    { v0100, v0101, v0102, v0103, v0104, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v0500, v0501, v0502, v0503, v0504, v0505, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____ },
#else
    { v0100, v0101, v0102, v0103, v0104, v0105, v0106, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v0200, v0201, v0202, v0203, v0204, v0205, v0206, v0207, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v0400, v0401, v0402, v0403, v0404, v0405, v0406, v0407, v0408, v0409, v040a, v040b, v040c, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v0500, v0501, v0502, v0503, v0504, v0505, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v0600, v0601, v0602, v0603, v0604, v0605, v0606, v0607, v0608, v0609, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v0700, v0701, v0702, v0703, v0704, v0705, v0706, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v0800, v0801, v0802, v0803, v0804, v0805, v0806, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v0900, v0901, v0902, v0903, v0904, v0905, v0906, v0907, v0908, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v1000, v1001, v1002, v1003, v1004, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v1100, v1101, v1102, v1103, v1104, v1105, v1106, v1107, v1108, v1109, v110a, v110b, v110c, v110d, v110e, v110f, v1110, v1111, v____, v____, NULL, NULL, NULL, NULL },
    { v1200, v1201, v1202, v1203, v1204, v1205, v1206, v1207, v1208, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v1300, v1301, v1302, v1303, v1304, v1305, v1306, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v1400, v1401, v1402, v1403, v1404, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v1500, v1501, v1502, v1503, v1504, v1505, v1506, v1507, v1508, v1509, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v1600, v1601, v1602, v1603, v1604, v1605, v1606, v1607, v1608, v1609, v160a, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v1700, v1701, v1702, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v1800, v1801, v1802, v1803, v1804, v1805, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v1900, v1901, v1902, v1903, v1904, v1905, v1906, v1907, v1908, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v2100, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v2200, v2201, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v2300, v2301, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v2400, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v2600, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v2700, v2701, v2702, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v3000, v3001, v3002, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v3100, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v3200, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v3400, v3401, v3402, v3403, v3404, v3405, v3406, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v3500, v3501, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v3900, v3901, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v4000, v4001, v4002, v4003, v4004, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
    { v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, v____, NULL, NULL, NULL, NULL },
#endif
};

hGAMEDATA GameData = {};
hGAMEDATA *gD = NULL;

void hInitGame() {
    KL2_DEBUG_PRINT(("hInitGame ...\n"));
    KL2_DEBUG_PRINT(("hInitGame ... done\n"));
}

void hExitGame() {
    KL2_DEBUG_PRINT(("hExitGame ...\n"));
    KL2_DEBUG_PRINT(("hExitGame ... done\n"));
}

void hInitStage0() {
    KL2_DEBUG_PRINT(("hInitStage0 ...\n"));
    gD = &GameData;
    hSndReset();
#ifndef KL2_VER_TRIAL
    hSeLock(0);
#endif
    hSndBankSetStage();
#ifdef KL2_VER_TRIAL
    hSndSetMVol(1.0f);
#else
    hSndSetMVol(0.0f);
#endif
    gD->BGMmode = BGMMODE_TOP;
    gD->BGMppt = 0;
    gD->resFlag = 0;
    KL2_DEBUG_PRINT(("hInitStage0 ... done\n"));
}

void hInitStage1() {
    KL2_DEBUG_PRINT(("hInitStage1 ...\n"));
    hEvStageInit();
#ifndef KL2_VER_TRIAL
    if (GameGbl.vision == 0x1E00) {
        hSndFadeInAll(20);
    } else {
        hSndSetMVol(1.0f);
    }
    gD->BGMmode = BGMMODE_TOP;
    gD->BGMppt = 0;
    gD->resFlag = 0;
#endif
    KL2_DEBUG_PRINT(("hInitStage1 ... done\n"));
}

void hExitStage() {
    KL2_DEBUG_PRINT(("hExitStage1 ...\n"));
    gD->BGMmode = BGMMODE_TOP;
    KL2_DEBUG_PRINT(("hExitStage1 ... done\n"));
}

s32 hGameAreaStart(s32 flag) {
    KL2_DEBUG_PRINT(("hGameAreaStart ...\n"));

#ifndef KL2_VER_TRIAL
    hSeLock(0);
#endif
    hSeInitGrp(0);
#ifdef KL2_VER_TRIAL
    if ((GameGbl.vision & 0xFF) == KL2_VISION(0, 238)) {
        return 0;
    }
#endif
    hEvAreaInit();

    if (gD->resFlag) {
        if (hBgmGetStat()) {
            KL2_DEBUG_PRINT(("BGM KEIZOKU=%d\n", gD->BGMmode));
            gD->BGMmode = BGMMODE_GAME;
        } else {
            KL2_DEBUG_PRINT(("BGMRESTART REQ!=%d\n", gD->resBGM));
            gD->BGMmode = BGMMODE_START;
            gD->BGMid = gD->resBGM;
        }
    } else if (gD->BGMchgreq) {
        gD->BGMmode = BGMMODE_GAME;
    } else {
        if (gD->BGMmode == BGMMODE_TOP) {
            gD->BGMmode = BGMMODE_START;
        }
        gD->BGMid = 0;
    }

    gD->BGMchgreq = 0;
    sD->pptFade = 0;
    hSndEffSetArea();
    if (gD->resFlag) {
        sD->effVol = gD->resEVol;
    }
    hSeEnvStart();
    gD->areaTime = 0;
    gD->resFlag = 0;
    gD->deadFlag = 0;

    KL2_DEBUG_PRINT(("hGameAreaStart ... done\n"));
    return 0;
}

s32 hGameAreaEnd(s32 next) {
    KL2_DEBUG_PRINT(("hGameAreaEnd ...\n"));
#ifdef KL2_VER_TRIAL
    hEvObjAllDel();
#endif
    hSeKeyOffAll();
#ifndef KL2_VER_TRIAL
    sD->envNum = 0;
#endif
    gD->BGMmode = BGMMODE_END;
    gD->nextVision = next;
    KL2_DEBUG_PRINT(("NEXTAREA=%04x\n", next));
#ifndef KL2_VER_TRIAL
    hSeLock(1);
#endif
    KL2_DEBUG_PRINT(("hGameAreaEnd ... done\n"));
    return 0;
}

s32 hGameBgmGetID() {
    return gD->BGMid;
}

BGM hGameBgmGetNo() {
    BGMAREA *area;

    area = BGMvision[GameGbl.vision >> 8 & 0xFF][GameGbl.vision & 0xFF];
    area = &area[gD->BGMid];
    return area->bgmNo;
}

s32 hGameBgmGetCh() {
    BGMAREA *area;

    area = BGMvision[GameGbl.vision >> 8 & 0xFF][GameGbl.vision & 0xFF];
    area = &area[gD->BGMid];
    return area->bgmCh;
}

void hGameBgmChange() {
    BGMAREA *area;
    BGMAREA *next;
    s32 fadeout;

    area = BGMvision[GameGbl.vision >> 8 & 0xFF][GameGbl.vision & 0xFF];
    area = &area[gD->BGMid];
    switch (gD->BGMchgmode) {
        case 0:
#ifdef KL2_VER_TRIAL
            fadeout = area->fadeOut * 60.0f + 0.5f;
#else
            fadeout = area->fadeOut;
#endif
            break;
        case 1:
            fadeout = 60;
            break;
        case 2:
            fadeout = 1;
            break;
    }

    if (gD->BGMchgid == -1) {
#ifdef KL2_VER_TRIAL
        hBgmFadeOut(fadeout);
        gD->BGMid = -1;
#else
        if (hBgmGetStat() != 0) {
            hBgmFadeOut(fadeout);
        }
        gD->BGMid = 0;
#endif
        return;
    }

    next = BGMvision[GameGbl.vision >> 8 & 0xFF][GameGbl.vision & 0xFF];
    next = &next[gD->BGMchgid];

#ifdef KL2_VER_TRIAL
    if (next->bgmNo == hBgmGetPlayNo()) {
        if (next->bgmCh != hBgmGetPlayCh()) {
            hBgmChangeChX(next->bgmCh);
        }
    } else {
        hBgmFadeNext(fadeout, next->bgmNo, next->bgmCh, next->fadeIn * 60.0f, hBgmGetDefVol(next->bgmNo));
    }
#else
    if (next->bgmNo == -1) {
        if (hBgmGetStat() != 0) {
            hBgmFadeOut(fadeout);
        }
        gD->BGMid = 0;
        return;
    }

    switch (hBgmGetStat()) {
        case 1:
        case 2:
            if (next->bgmNo == hBgmGetPlayNo()) {
                if (next->bgmCh != hBgmGetPlayCh()) {
                    hBgmChangeChX(next->bgmCh);
                }
            } else {
                hBgmFadeNext(fadeout, next->bgmNo, next->bgmCh, next->fadeIn, hBgmGetDefVol(next->bgmNo));
            }
            break;
        case 3:
            hBgmFadeNext(fadeout, next->bgmNo, next->bgmCh, next->fadeIn, hBgmGetDefVol(next->bgmNo));
            break;
        case 0:
            hBgmFadeIn(next->bgmNo, next->bgmCh, next->fadeIn);
            hBgmSetVol(hBgmGetDefVol(next->bgmNo));
            break;
    }

#endif
    gD->BGMid = gD->BGMchgid;
#ifndef KL2_VER_TRIAL
    gD->BGMchgreq = 0;
#endif
}

void hGameMain() {
    BGMAREA *area;
    BGMAREA *next;
    s32 i;

#ifdef KL2_VER_TRIAL
    if (GameGbl.pause_flag != 0) {
        hSndMute();
        hBgmPause();
        hPptPause();
    }
#else
    if (GameGbl.pause_flag != 0 && hrpt_sbgm == 0) {
        hBgmPause();
        hPptPause();
    }

    for (i = 0; i < sD->envNum; i++) {
        if (sD->envFade[i] != 0) {
            f32 vol;

            if (sD->envFadeCnt[i] >= sD->envFadeMax[i]) {
                vol = sD->envFadeVol1[i];
                sD->envFade[i] = 0;
            } else {
                vol = sD->envFadeVol0[i] + (sD->envFadeVol1[i] - sD->envFadeVol0[i]) * sD->envFadeCnt[i] / sD->envFadeMax[i];
                sD->envFadeCnt[i]++;
            }

            hSeEnvSetVol(i, vol);
        }
    }
#endif

    switch ((s32)gD->BGMmode) {
        case BGMMODE_START:
            if (gD->BGMchgreq != 0) {
                gD->BGMid = gD->BGMchgid;
            }
            area = BGMvision[GameGbl.vision >> 8 & 0xFF][GameGbl.vision & 0xFF];
            area = &area[gD->BGMid];

            if (area->bgmNo != -1 && (area->bgmNo != hBgmGetPlayNo() || area->bgmCh != hBgmGetPlayCh())) {
#ifdef KL2_VER_TRIAL
                hBgmFadeIn(area->bgmNo, area->bgmCh, area->fadeIn * 60.0f);
                hBgmSetVol(hBgmGetDefVol(next->bgmNo)); // next is not set :(
#else
                hBgmFadeIn(area->bgmNo, area->bgmCh, area->fadeIn);
                hBgmSetVol(hBgmGetDefVol(area->bgmNo));
#endif
                
            }

            gD->BGMmode = BGMMODE_GAME;
            break;
        case BGMMODE_GAME:
#ifndef KL2_VER_TRIAL
            if (hrpt_id != PT0102_S0 && hrpt_id != PT0805_S0 && hrpt_id != PTENDING) {
#endif
                if (hr_pt_check() != 0 && sD->pptFade == 0) {
                    sD->pptFade = 1;
                    sD->pptFadeCnt = 0.0f;
                }
                if (hr_pt_check() == 0 && sD->pptFade == 2) {
                    sD->pptFade = 3;
                    sD->pptFadeCnt = 0.0f;
                }
#ifndef KL2_VER_TRIAL
            }
#endif

            if (gD->BGMchgreq != 0) {
                hGameBgmChange();
            }
            break;
        case BGMMODE_END:
#ifndef KL2_VER_TRIAL
            gD->BGMmode = BGMMODE_GAME;
#endif
            area = BGMvision[GameGbl.vision >> 8 & 0xFF][GameGbl.vision & 0xFF];
            area = &area[gD->BGMid];

#ifdef KL2_VER_TRIAL
            next = BGMvision[gD->nextVision >> 8 & 0xFF][gD->nextVision & 0xFF];
            if (next->bgmNo == hBgmGetPlayNo()) {
                if (next->bgmCh != hBgmGetPlayCh()) {
                    hBgmChangeChX(next->bgmCh);
                }
            } else if (next->bgmNo != -1) {
                hBgmFadeNext(area->fadeOut * 60.0f, next->bgmNo, next->bgmCh, next->fadeIn * 60.0f, hBgmGetDefVol(next->bgmNo));
            } else {
                hBgmFadeOut(area->fadeOut * 60.0f);
            }
#else

            if (gD->nextVision == -1) {
                hBgmFadeOut(area->fadeOut);
            } else {
                next = BGMvision[gD->nextVision >> 8 & 0xFF][gD->nextVision & 0xFF];
                if (hBgmGetStat() == 0) {
                    if (next->bgmNo != -1) {
                        hBgmFadeIn(next->bgmNo, next->bgmCh, next->fadeIn);
                        hBgmSetVol(hBgmGetDefVol(next->bgmNo));
                    }
                } else if (next->bgmNo == hBgmGetPlayNo()) {
                    if (next->bgmCh != hBgmGetPlayCh()) {
                        hBgmChangeChX(next->bgmCh);
                    }
                } else if (next->bgmNo != -1) {
                    hBgmFadeNext(area->fadeOut, next->bgmNo, next->bgmCh, next->fadeIn, hBgmGetDefVol(next->bgmNo));
                } else {
                    hBgmFadeOut(area->fadeOut);
                }
            }
#endif

#ifdef KL2_VER_TRIAL
            gD->BGMmode = BGMMODE_GAME;
#endif
            break;
    }

    gD->BGMchgreq = 0;
    if (gD->deadFlag) {
        KL2_DEBUG_PRINT(("DEADCNT=%d\n", gD->deadCnt));
        if (gD->deadCnt == 49) {
            KL2_DEBUG_PRINT(("SE ALL KEYOFF\n"));
            hSeKeyOffAll();
#ifndef KL2_VER_TRIAL
            hSeLock(1);
#endif
        }
        if (gD->deadCnt <= 0) {
            KL2_DEBUG_PRINT(("DEAD END\n"));
            gD->deadFlag = 0;
        }
        gD->deadCnt--;
    }
    gD->areaTime++;
}

void hPushRestart() {
    KL2_DEBUG_PRINT(("hPushRestart ...\n"));
    gD->resVision = GameGbl.vision;
    gD->resEVol = sD->effVol;
    gD->resBGM = gD->BGMid;
    hEvPushRestart();
    KL2_DEBUG_PRINT(("EVOL=%f\n", gD->resEVol));
    KL2_DEBUG_PRINT(("BGM =%d\n", gD->resBGM));
    KL2_DEBUG_PRINT(("hPushRestart ... done\n"));
}

void hPopRestart() {
    KL2_DEBUG_PRINT(("hPopRestart ...\n"));
    gD->resFlag = 1;
    hEvPopRestart();
    KL2_DEBUG_PRINT(("hPopRestart ... done\n"));
}

void hKlonoaDead(s32 vision, s32 frame, DEAD pattern) {
    KL2_DEBUG_PRINT(("hKlonoaDead ...\n"));
    KL2_DEBUG_PRINT(("vision=%04x\n", vision));
    KL2_DEBUG_PRINT(("frame=%d\n", frame));
    KL2_DEBUG_PRINT(("pattern=%d\n", pattern));

    gD->deadFlag = 1;
    gD->deadCnt = frame;

    switch (pattern) {
#ifdef KL2_VER_TRIAL
        case DEAD_DAMAGE:
            hSeKeyOn(KL2_VAG(11, 0, 0, 1, 10, 0x1C, 1200, 1200), NULL, 0);
            hSeKeyOn(KL2_VAG(25, 1, 0, 2, 10, 0x0C, 1200, 1200), NULL, 0);
            break;
        case DEAD_FALL:
            hSeKeyOn(KL2_VAG(12, 0, 0, 1, 10, 0x1C, 1200, 1200), NULL, 0);
            hSeKeyOn(KL2_VAG(11, 1, 0, 2, 10, 0x0C, 1200, 1200), NULL, 0);
            break;
        case DEAD_DROWN:
            hSeKeyOn(KL2_VAG(15, 0, 0, 1, 10, 0x0C,  200,  200), NULL, 0);
            hSeKeyOn(KL2_VAG(14, 0, 0, 1, 10, 0x0C, 1200, 1200), NULL, 0);
            hSeKeyOn(KL2_VAG(12, 1, 0, 2, 10, 0x0C, 1200, 1200), NULL, 0);
            break;
        case DEAD_CHOKE:
            hSeKeyOn(KL2_VAG(29, 1, 0, 2, 10, 0x0C, 1200, 1200), NULL, 0);
            break;
        case DEAD_BURN:
            hSeKeyOn(KL2_VAG(29, 1, 0, 2, 10, 0x0C, 1200, 1200), NULL, 0);
            break;
#else
        case DEAD_DAMAGE:
            hSeKeyOn(KL2_VAG(11, 0, 0, 1, 10, 0x1C, 1200, 1200), NULL, 0);
            hSeKeyOn(KL2_VAG(9,  1, 0, 2, 10, 0x0C,  200,  200), NULL, 0);
            break;
        case DEAD_FALL:
            hSeKeyOn(KL2_VAG(12, 0, 0, 1, 10, 0x1C, 1200, 1200), NULL, 0);
            hSeKeyOn(KL2_VAG(8,  1, 0, 2, 10, 0x0C,  200,  200), NULL, 0);
            break;
        case DEAD_DROWN:
            hSeKeyOn(KL2_VAG(8,  0, 0, 1, 10, 0x0C,  200,  200), NULL, 0);
            hSeKeyOn(KL2_VAG(14, 0, 0, 1, 10, 0x0C, 1200, 1200), NULL, 0);
            hSeKeyOn(KL2_VAG(10, 1, 0, 2, 10, 0x0C,  200,  200), NULL, 0);
            break;
        case DEAD_CHOKE:
        case DEAD_BURN:
            break;
#endif
    }

    if (hGameBgmComp(GameGbl.vision, gD->BGMid, gD->resVision, gD->resBGM) != 0 || vision == -1) {
        hBgmFadeOut(60);
    }
    KL2_DEBUG_PRINT(("hKlonoaDead ... done\n"));
}

s32 hGameBgmComp(s32 v0, s32 id0, s32 v1, s32 id1) {
    BGMAREA *bgm0;
    BGMAREA *bgm1;

    bgm0 = BGMvision[v0 >> 8 & 0xFF][v0 & 0xFF];
    bgm0 = &bgm0[id0];
    bgm1 = BGMvision[v1 >> 8 & 0xFF][v1 & 0xFF];
    bgm1 = &bgm1[id1];
    return (bgm0->bgmNo != bgm1->bgmNo || bgm0->bgmCh != bgm1->bgmCh);
}
