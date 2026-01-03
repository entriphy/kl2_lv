#include "harada/hr_pbgm.h"
#include "harada/hr_prm.h"
#include "harada/hr_pflag.h"
#include "hoshino/h_str.h"

static PTBGM ptbgm_table[82] = {
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 1, 0, 1 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 1, 0, 5 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 1, 0, 1 },
    { 1, 2, 1 },
    { 1, 0, 4 },
    { 1, 0, 4 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
};
static PTBGM *ptb;

#ifdef KL2_VER_RETAIL
s32 hrpt_id;
s16 hrptm_res;
s32 hrpt_sbgm;

s32 hr_ptchk_45(s32 id) {
    s32 var;

    var = id & 2 ? HRPSFG_CHK040B : HRPSFG_CHK0505 ;
    return pt_flagj_P(var);
}
#endif

void hr_pt_setBGM(HR_PSYS *ps, s16 bgm, s32 mode) {
    ps->reqbgm = bgm;
    if (mode == 0) {
        ps->flag |= 0x20000000;
    } else {
        ps->flag |= 0x10000000;
    }
}

void hr_pt_reqBGM(HR_PSYS *ps) {
    s32 mode = ps->flag & 0x20000000 ? 0 : 2;
    ps->flag &= ~0x30000000;
    hBgmChangeID(ps->reqbgm, mode);
    KL2_DEBUG_PRINT(("PuppetBGM %d mode %d\n", ps->reqbgm, mode));
}

void hr_ptbgm_init(HR_PSYS *ps) {
    s32 id;

    ps->reqbgm = -1;
    KL2_VER_TRIAL_ONLY(id = hr_pflag_get_id());
    if (KL2_VER_COND(id != -1, hrpt_id != -1 && hrpt_flag != 4)) {
        ptb = &ptbgm_table[KL2_VER_COND(id, hrpt_id)];
        if (ptb->flag & 1) {
            hr_pt_setBGM(ps, ptb->sbgm, KL2_VER_COND(2, 0));
        }
        return;
    }
}

#ifdef KL2_VER_TRIAL
void hr_ptbgm_end(HR_PSYS *ps, s32 mode) {
    s32 id = hr_pflag_get_id();
    if (id == -1) {
        return;
    }

    ptb = &ptbgm_table[id];
    if (!(ptb->flag & 0x4)) {
        if (ps->reqbgm == -1 || ps->reqbgm != ptb->ebgm) {
            hBgmChangeID(ptb->ebgm, mode);
            KL2_DEBUG_PRINT(("PuppetExitBGM %d mode %d\n", ptb->ebgm, mode));
        }
    }
}
#else
void hr_ptbgm_end(HR_PSYS *ps, s32 mode) {
    if (hrpt_id == -1 || hrpt_flag == 4) {
        return;
    }

    ptb = &ptbgm_table[hrpt_id];
    if (ptb->flag & 0xC) {
        hBgmChangeID(-1, ptb->flag & 8 ? 0 : 2);
    } else if (ptb->flag & 0x10) {
        if (ps->reqbgm == -1 || ps->reqbgm != ptb->ebgm) {
            hBgmChangeID(ptb->ebgm, mode);
        }
    }
}
#endif