#ifndef __AB_AURA_A_H
#define __AB_AURA_A_H

#include "ab_util.h"
#include "ab_vu0.h"

struct CParticleAuraA : /* 0x00 */ CObject { // 0x14
    static CBillBoard *ptclModelData;
    static s32 N_DRAW;
protected:
    /* 0x04 */ f32 m_zoom;
    /* 0x08 */ f32 m_zoom_spd;
    /* 0x0c */ f32 m_rot;
    /* 0x10 */ f32 m_rot_spd;
    
public:
    // CParticleAuraA& operator=();
    // CParticleAuraA();
    // CParticleAuraA();
    static void Initialize(/* parameters unknown */);
    static void MakeDrawEnv(/* parameters unknown */);
    void Init();
    bool Func();
    bool MakePacket();
    static bool Draw(/* parameters unknown */);
};

#endif