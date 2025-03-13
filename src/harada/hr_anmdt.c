#include "harada/hr_anmdt.h"
#include "harada/hr_anmvp.h"
#include "nakano/main.h"

static void hr_anm_v0100i(HRANMV *av);
static void hr_anm_v0100w(HRANMV *av);

static HRANMVS hr_v_avt_tbl[1] = { {hr_anm_v0100w, hr_anm_v0100i, 2, &VpmInfo} };

static void hr_anm_v0100i(HRANMV *av) {
    OBJWORK *obj;

    obj = GameGbl.klonoa;
    hr_set_vlight(&hrvlight[0], obj->posi[0], obj->posi[1], obj->posi[2], 1.0f, 1.0f, 2.0f, 20.0f, 300.0f);
    hr_set_vlight(&hrvlight[1], obj->posi[0], obj->posi[1] - 200.0f, obj->posi[2], 2.0f, 1.0f, 1.0f, 20.0f, 300.0f);
    hr_set_vlightMini(&hrvlight[0], 0.1f, 0.1f, 0.1f);
    #ifndef KL2_VER_TRIAL
    hr_set_vlightMini(&hrvlight[1], 0.0f, 0.0f, 0.0f);
    #else
    hr_set_vlightMini(&hrvlight[1], 0.1f, 0.1f, 0.1f);
    #endif
}

static void hr_anm_v0100w(HRANMV *av) {
    #ifdef KL2_VER_TRIAL
    OBJWORK *obj = GameGbl.klonoa;
    hrvlight[0].x = obj->posi[0];
    hrvlight[0].y = obj->posi[1];
    hrvlight[0].z = obj->posi[2];
    hrvlight[1].x = obj->posi[0];
    hrvlight[1].y = obj->posi[1] - 200.0f;
    hrvlight[1].z = obj->posi[2];
    #endif
}

void hr_vision_anmVPM_set() {
    switch (GameGbl.vision) {
        case 0x0D00:
        case 0x0D01:
        case 0x0D02:
        case 0x0D03:
        case 0x0D04:
            hr_anmVPM_set(&hr_v_avt_tbl[0]);
            hrmapoff = 1;
            break;
    }
}

void hr_change_anmVPM(s32 id) {
    HRANMV *anmv;

    anmv = &hravbuf[0];
    switch (id) {
        case HRAV_SINT:
            anmv->drawno = id;
            anmv->prog = hr_anm_v0100w;
            break;
        case HRAV_SINT2:
            anmv->drawno = id;
            anmv->prog = hr_anm_v0100w;
            break;
        default:
            return;
    }
}