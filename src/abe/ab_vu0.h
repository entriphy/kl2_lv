#ifndef __AB_VU0_H
#define __AB_VU0_H

#include "common.h"

#ifdef __cplusplus

inline void abVu0MulMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1, sceVu0FMATRIX m2) {
    sceVu0MulMatrix(m0, m1, m2);
}

inline void abVu0TransMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1, sceVu0FVECTOR tv) {
    sceVu0TransMatrix(m0, m1, tv);
}

inline void abVu0CopyMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1) {
    sceVu0CopyMatrix(m0, m1);
}

inline void abVu0RotTransPers(sceVu0IVECTOR v0, sceVu0FMATRIX m0, sceVu0FVECTOR v1, s32 mode) {
    // abRotTransPers(v0, m0, v1, mode);
}



#endif

#endif