#include "okanoyo/randmt.h"
#include "nakano/vu0mac.h"

void randMT::generateMT() {
    u32 mag01[] = { 0, MATRIX_A };
#ifdef KL2_VER_TRIAL
    sceVu0IVECTOR iv;
#endif
    s32 i;
    u32 u;
    u32 v;

    for (i = 0; i < N - M; i++) {
        u = this->mt[i] & UPPER_MASK | this->mt[i + 1] & LOWER_MASK;
        this->mt[i] = this->mt[i + M] ^ u >> 1 ^ mag01[u & 1];
    }

    this->mt[N] = this->mt[0];

    for (; i < N; i++) {
        u = this->mt[i] & UPPER_MASK | this->mt[i + 1] & LOWER_MASK;
        this->mt[i] = this->mt[i + (M - N)] ^ u >> 1 ^ mag01[u & 1];
    }

    for (i = 0; i < N; i++) {
        u = this->mt[i];
        u ^= TEMPERING_SHIFT_U(u);
        u ^= TEMPERING_SHIFT_S(u) & TEMPERING_MASK_B;
        u ^= TEMPERING_SHIFT_T(u) & TEMPERING_MASK_C;
        u ^= TEMPERING_SHIFT_L(u);
        this->mtr[i] = u;
    }

#ifdef KL2_VER_TRIAL
    for (i = 0; i < N / sizeof(sceVu0IVECTOR); i++) {
        iv[0] &= LOWER_MASK;
        iv[1] &= LOWER_MASK;
        iv[2] &= LOWER_MASK;
        iv[3] &= LOWER_MASK;
        vu0_ITOF0Vector(&this->mtrf[i], iv);
    }
#endif

    this->index = 0;
}

void randMT::srand(u32 s) {
    this->seed = s;
    for (s32 i = 0; i < N; i++) {
        s = 69069 * s + 1;
        u32 v = s & 0xffff0000;
        s = 69069 * s + 1;
        this->mt[i] = v | (s & 0xffff0000) >> 16;
    }
    this->generateMT();
}

u32 randMT::rand() {
    if (this->index >= N) {
        this->generateMT();
    }
    return this->mtr[this->index++];
}

f32 randMT::randf() {
    if (this->index >= N) {
        this->index = 0;
    }
    return this->mtrf[this->index++];
}

f32 randMT::randf(f32 max) {
    sceVu0FVECTOR fv;
    u32 var = 0x2F000000; // ?

    if (this->index >= N) {
        this->index = 0;
    }
    fv[0] = this->mtrf[this->index++];
    sceVu0ScaleVector(fv, fv, max * *(f32 *)&var);
    return fv[0];
}

f32 randMT::GetNormalDistribution(u32 i1, u32 i2) {
    f64 u1 = (i1 & 0xFFFFFF) / (f64)0xFFFFFF;
    f64 u2 = (i2 & 0xFFFFFF) / (f64)0xFFFFFF;
    return (sqrt(log(u1) * -2.0)) * sin(u2 * 6.283184);
}

f32 randMT::GetNormalDistributionf(f32 f1, f32 f2) {
    return vu0_SquareRoot(logf(f1) * -2.0) * sinf(f2 * 6.283184);
}