#include "nakano/camera.h"
#include "nakano/main.h"
#include "nakano/vu0mac.h"
#include "nakano/k_math.h"
#include "nakano/route.h"
#include "harada/hr_pcam.h"
#include "okanoyo/okmain.h"
#include "okanoyo/okprint.h"

static nkCamNOR cmnor0701[] = {
    { 0x190, 11, 0, 0, 0, -40, 582, 0 },
    { 0x1F4, 30, 0, 0, 0, -40, 582, 0 },
    { 0x1BC, -20, 0, 0, 0, -40, 582, 0 },
    { 0x1E0, -40, 0, 0, 0, -40, 582, 0 },
    { 0x18B, 16, 20, 0, 0, -40, 582, 0 },
    { 0x000, 0, 0, 0, 0, 0, 0, 0x80 }
};
static VWork ViCon;
static VCONTBL *vcontbl[64];
static CAM_WORK camThr;
static nkCamMNG *camMng[64];
static nkCamNOR *camNor;
static nkCamFIX *camFix;

void CamDataNone() {
    s32 lp1;

    for (lp1 = 0; lp1 < 64; lp1++) {
        camMng[lp1] = NULL;
    }
}

void MngDataInit(s32 *adrs, nkCamMNG *mng_p[], nkCamNOR *nmr_p[], nkCamFIX *fix_p[]) {
    nkCamMNG *mng;
    nkCamNOR *nmr;
    s32 lp1;
    s32 n;

    adrs++;
    n = *adrs;
    adrs++;

    mng = (nkCamMNG *)&adrs[n];
    for (lp1 = 0; lp1 < 64; lp1++) {
        mng_p[lp1] = mng;
        while (!(mng->flg & 0x40)) {
            mng++;
        }
        if (mng->flg & 0x80) {
            break;
        }
        mng++;
    }

    mng++;
    lp1++;
    nmr = (nkCamNOR *)mng;
    for (; lp1 < 64; lp1++) {
        mng_p[lp1] = NULL;
    }

    *nmr_p = nmr;
    while (!(nmr->flg & 0x80)) {
        nmr++;
    }

    nmr++;
    *fix_p = (nkCamFIX *)nmr;
}

void CamDataInit(s32 *adrs) {
    MngDataInit(adrs, camMng, &camNor, &camFix);
}

void nkCeVtAdrInit(VCONTBL *vtp, s32 rtn) {
    vcontbl[rtn] = vtp;
}

void CamInit(CAM_WORK *cam) {
    VWork *vwrk = &ViCon;
    vwrk->zoom = 340.0f;
    vwrk->angx = KL2_PI / 16.0f;
    vwrk->angy = 0.0f;
    vwrk->angz = 0.0f;
    vwrk->posix = 0.0f;
    vwrk->posiy = 0.0f;
    vwrk->wangx = 0.0f;
    vwrk->wangy = 0.0f;
    vwrk->offx = 0.0f;
    vwrk->offy = 0.0f;
#ifdef KL2_VER_TRIAL
    vwrk->dcnt = 0.0f;
    vwrk->dtime = 0.0f;
#else
    vwrk->dtime = 0.0f;
    vwrk->dcnt = 0.0f;
    vwrk->release = 0;
#endif
    vwrk->flg = 0;
    vwrk->flg2 = 0;
    vwrk->frtime = 0.0f;
    vwrk->fwtime = 0.0f;
    vwrk->rtlen = 0x200000;
    SETVEC(vwrk->tposi, 0.0f, 0.0f, 0.0f, 1.0f);
    vwrk->nml = cmnor0701;
    vwrk->adiv[0] = 48.0f;
    vwrk->adiv[1] = 48.0f;
    vwrk->adiv[2] = 48.0f;
    vwrk->tblcnt = 0;
    vwrk->mode = 0;
    cam->mode = 2;
    SETVEC(cam->posi, 0.0f, 0.0f, -4000.0f, 1.0f);
    SETVEC(cam->ang, 0.0f, 0.0f, 0.0f, 1.0f);
    cam->scr_z = 582.0f;
    vwrk->zoom = 400.0f;
}

void CamCalMatrix(CAM_WORK *cam) {
    sceVu0FMATRIX tpmat;
    sceVu0FVECTOR camera_p2;

    sceVu0CopyMatrix(GameGbl.d_wsm, GameGbl.wsm);
    sceVu0CopyMatrix(GameGbl.d_wvm, GameGbl.wvm);
    sceVu0CopyMatrix(GameGbl.d_vsm, GameGbl.vsm);
    KL2_VER_RETAIL_ONLY(GameGbl.d_cam = GameGbl.cam);
    sceVu0UnitMatrix(tpmat);
    sceVu0UnitMatrix(GameGbl.wsm);
    sceVu0RotMatrixY(tpmat, tpmat, cam->ang[1]);
    sceVu0RotMatrixX(tpmat, tpmat, cam->ang[0]);
    sceVu0RotMatrixZ(tpmat, tpmat, cam->ang[2]);
    sceVu0MulMatrix(tpmat, GameGbl.wsm, tpmat);
    camera_p2[0] = -cam->posi[0];
    camera_p2[1] = -cam->posi[1];
    camera_p2[2] = -cam->posi[2];
    sceVu0ApplyMatrix(camera_p2, tpmat, camera_p2);
    camera_p2[3] = 1.0f;
    sceVu0TransMatrix(GameGbl.wvm, tpmat, camera_p2);
    sceVu0ViewScreenMatrix(GameGbl.vsm,cam->scr_z, 1.0f, 0.47f, 2048.0f, 2048.0f, 1.0f, 16777215.0f, 0.1f, 65535.0f);
    sceVu0MulMatrix(GameGbl.wsm, GameGbl.vsm, GameGbl.wvm);
}

void CamDebug(CAM_WORK *cam) {
    kPadDATA *kpd = &GameGbl.kpd[1];

    if (pPAD_LVL_CIRCLE(kpd)) {
        cam->ang[1] -= KL2_PI180;
    }
    if (pPAD_LVL_SQUARE(kpd)) {
        cam->ang[1] += KL2_PI180;
    }
    if (pPAD_LVL_CROSS(kpd)) {
        cam->ang[0] += KL2_PI180;
    }
    if (pPAD_LVL_TRIANG(kpd)) {
        cam->ang[0] -= KL2_PI180;
    }

    if (pPAD_LVL_UP(kpd)) {
        cam->posi[0] -= _sin(cam->ang[1]) * 8.0f;
        cam->posi[2] += _cos(cam->ang[1]) * 8.0f;
    }
    if (pPAD_LVL_DOWN(kpd)) {
        cam->posi[0] += _sin(cam->ang[1]) * 8.0f;
        cam->posi[2] -= _cos(cam->ang[1]) * 8.0f;
    }
    if (pPAD_LVL_RIGHT(kpd)) {
        cam->posi[0] += _cos(cam->ang[1]) * 8.0f;
        cam->posi[2] += _sin(cam->ang[1]) * 8.0f;
    }
    if (pPAD_LVL_LEFT(kpd)) {
        cam->posi[0] -= _cos(cam->ang[1]) * 8.0f;
        cam->posi[2] -= _sin(cam->ang[1]) * 8.0f;
    }

    if (pPAD_LVL_R2(kpd)) {
        cam->posi[1] += 5.0f;
    }
    if (pPAD_LVL_R1(kpd)) {
        cam->posi[1] -= 5.0f;
    }

    cam->ang[1] = nkRadMask(cam->ang[1]);
    cam->ang[0] = nkRadMask(cam->ang[0]);

    if (pPAD_LVL_L1(kpd)) {
        cam->scr_z += 10.0f;
    }
    if (pPAD_LVL_L2(kpd) && cam->scr_z > 20.0f) {
        cam->scr_z -= 10.0f;
    }
}

static void CamScrLim(OBJWORK *objw, sceVu0FVECTOR posi, sceVu0FVECTOR scrv) {
    f32 work;
    HERO_WORK *herow;
    VWork *vwrk = &ViCon;
    s32 muki = ((HERO_WORK *)GameGbl.klonoa->work)->buki_muki;
    f32 wlimit;

    herow = objw->work;

    if (vwrk->flg & 2) {
        work = MichiPosiY(&objw->rtw) - scrv[1];
        vwrk->flg2 |= 8;

        if (work < 0.0f) {
            if (work > -4.0f) {
                scrv[1] -= -work;
            } else {
                scrv[1] -= 4.0f;
            }
        }

        if (work > 0.0f) {
            if (work < 4.0f) {
                scrv[1] += work;
            } else {
                scrv[1] += 4.0f;
            }
        }
    } else {
        work = (posi[1] - scrv[1]) * GameGbl.vsm[1][1] / vwrk->zoom;
        if (herow->yuka_hit) {
            if (work < 0.0f) {
                if (work > -4.0f) {
                    scrv[1] -= -work;
                } else {
                    scrv[1] -= 4.0f;
                }
            }
            if (work > 0.0f) {
                if (work < 4.0f) {
                    scrv[1] += work;
                } else {
                    scrv[1] += 4.0f;
                }
            }
        } else {
            if (vwrk->flg2 & 8) {
                if (work < -88.0f) {
                    wlimit = -(work + 8.0f);
                    if (wlimit < 88.0f) {
                        wlimit = 80.0f;
                        vwrk->flg2 &= ~0x8;
                    }
                } else {
                    wlimit = 80.0f;
                }
            } else {
                wlimit = 80.0f;
            }

            if (work < -80.0f) {
                scrv[1] = posi[1] + wlimit / GameGbl.vsm[1][1] * vwrk->zoom;
            }

            if (vwrk->flg2 & 8) {
                if (work > 50.0f + herow->jumpspd_limit) {
                    wlimit = -(work + herow->jumpspd_limit);
                    if (wlimit > -(50.0f + herow->jumpspd_limit)) {
                        wlimit = -50.0f;
                        vwrk->flg2 &= ~0x8;
                    }
                } else {
                    wlimit = -50.0f;
                }
            } else {
                wlimit = -50.0f;
            }

            if (work > 50.0f) {
                scrv[1] = posi[1] + wlimit / GameGbl.vsm[1][1] * vwrk->zoom;
            }
        }
    }

    if (vwrk->flg & 4) {
        if (vwrk->offx < 0.0f) {
            vwrk->offx += 2.0f;
        } else if (vwrk->offx > 0.0f) {
            vwrk->offx -= 2.0f;
        }
    } else if (objw->bun0 == 1) {
        if (muki == 0 && vwrk->offx < 40.0f) {
            vwrk->offx += 2.0f;
        }
        if (muki == 1 && vwrk->offx > -40.0f) {
            vwrk->offx -= 2.0f;
        }
    }

    MichiPosiXZ(&objw->rtw, scrv);
}

nkCamMNG* CamGetMNG(OBJWORK *objw) {
    VWork *vwrk = &ViCon;
    nkCamMNG *mng;
    s32 rtn;
    s32 rtcnt;
    HERO_WORK *herow = objw->work;

    if (objw->reg0 & 0x200) {
        rtn = GetMichiNo(herow->okuyuka->rtw.rtp);
        rtcnt = herow->okuyuka->rtw.mcn >> 12;
    } else {
        rtn = GetMichiNo(objw->rtw.rtp);
        rtcnt = objw->rtw.mcn >> 12;
    }

    mng = camMng[rtn];
    vwrk->tblcnt = 0;
    if (mng == NULL) {
        return NULL;
    }

    while (1) {
        if (mng->flg & 0x40) {
            break;
        }
        if (rtcnt < (mng + 1)->rtcnt) {
            goto cringe;
        }
        mng++;
        vwrk->tblcnt++;

        if (mng->rtcnt == (mng + 1)->rtcnt && objw->posi[1] > mng->height) {
            nkCamMNG *b_mng;
            for (b_mng = mng; mng->rtcnt == b_mng->rtcnt; b_mng++);
            if (b_mng->rtcnt > rtcnt) {
                break;
            }
        }
    }
    cringe: // cringe
    return mng;
}

void CamInitNml(nkCamNOR *nml, OBJWORK *objw, CAM_WORK *cam) {
    sceVu0FMATRIX mat;
    sceVu0FVECTOR vf;
    sceVu0FVECTOR rtv;
    RT_WRK *rtw = &objw->rtw;
    ROUTE *rtp = &rtw->rtp[rtw->plc];
    VWork *vwrk = &ViCon;
    sceVu0IVECTOR vi;

    vwrk->zoom = nml->zoom;
    vwrk->angx = nml->angx * 2.0f * KL2_PI / 360.0f;
    vwrk->angy = nml->angy * 2.0f * KL2_PI / 360.0f;
    vwrk->posiy = nml->trnsy;
    vwrk->posix = nml->trnsx;
    vwrk->offy = 0.0f;

    sceVu0CopyVector(vwrk->tposi, objw->posi);
    if (nml->flg & 2) {
        vwrk->tposi[1] = MichiPosiY(&objw->rtw);
    }

    vi[0] = rtp->vec.x;
    vi[1] = rtp->vec.y;
    vi[2] = rtp->vec.z;
    vu0_ITOF0Vector(rtv, vi);
    vwrk->wangy = _atan2(rtv[0], rtv[2]) + KL2_3PI2 + vwrk->angy;
    vwrk->wangx = -vwrk->angx;
    if (vwrk->wangx < -KL2_PI) {
        vwrk->wangx += KL2_2PI;
    } else if (vwrk->wangx > KL2_PI) {
        vwrk->wangx -= KL2_2PI;
    }
    if (vwrk->wangy < -KL2_PI) {
        vwrk->wangy += KL2_2PI;
    } else if (vwrk->wangy > KL2_PI) {
        vwrk->wangy -= KL2_2PI;
    }

    if (cam == NULL) {
        return;
    }
    sceVu0UnitMatrix(mat);
    sceVu0RotMatrixX(mat, mat, vwrk->wangx);
    sceVu0RotMatrixY(mat, mat, vwrk->wangy);
    sceVu0TransMatrix(mat, mat, vwrk->tposi);
    vf[0] = vwrk->posix + vwrk->offx;
    vf[1] = vwrk->posiy;
    vf[2] = -vwrk->zoom;
    vf[3] = 1.0f;
    sceVu0ApplyMatrix(cam->posi, mat, vf);
    cam->ang[0] = -vwrk->wangx;
    cam->ang[1] = -vwrk->wangy;
    cam->ang[2] = vwrk->angz;
    if (cam->ang[0] < -KL2_PI) {
        cam->ang[0] += KL2_2PI;
    } else if (cam->ang[0] > KL2_PI) {
        cam->ang[0] -= KL2_2PI;
    }
    if (cam->ang[1] < -KL2_PI) {
        cam->ang[1] += KL2_2PI;
    } else if (cam->ang[1] > KL2_PI) {
        cam->ang[1] -= KL2_2PI;
    }
    if (cam->ang[2] < -KL2_PI) {
        cam->ang[2] += KL2_2PI;
    } else if (cam->ang[2] > KL2_PI) {
        cam->ang[2] -= KL2_2PI;
    }
}

void CamReverseInit() {
    VWork *vwrk = &ViCon;
    vwrk->frtime = 30.0f;
}

void CamVWorkInit(OBJWORK *objw, CAM_WORK *cam) {
    VWork *vwrk = &ViCon;
    nkCamMNG *mng = CamGetMNG(objw);
    s32 type;
    nkCamFIX *fix;

    vwrk->old_rtn = GetMichiNo(objw->rtw.rtp);
    vwrk->release = 0;

    if (mng == NULL) {
        CamInitNml(vwrk->nml, objw, cam);
        return;
    }

    type = mng->type;
    if (type == 1) {
        if (GameGbl.cam.mode != 7 && GameGbl.cam.mode != 6) {
            if (objw->bun0 == 3 || objw->bun1 == 4) {
                GameGbl.cam.mode = 8;
            } else {
                GameGbl.cam.mode = 1;
            }
        }
        vwrk->nml = &camNor[mng->idx];
        CamInitNml(vwrk->nml, objw, cam);
    } else if (type == 2) {
        fix = &camFix[mng->idx];
        cam->posi[0] = fix->posix;
        cam->posi[1] = fix->posiy;
        cam->posi[2] = fix->posiz;
        cam->ang[0] = (fix->angx * 2.0f * KL2_PI) / 360.0f;
        cam->ang[1] = (fix->angy * 2.0f * KL2_PI) / 360.0f;
        cam->ang[2] = (fix->angz * 2.0f * KL2_PI) / 360.0f;
        vwrk->frtime = fix->time;
        vwrk->dtime = fix->time;
        vwrk->dcnt = 0.0f;
        sceVu0CopyVector(vwrk->tposi, objw->posi);
        GameGbl.cam.mode = 9;
    }
}

void CamPipe(OBJWORK *objw, CAM_WORK *cam) {
    RT_WRK rtw;
    f32 wk;
    sceVu0FVECTOR klpos;
    sceVu0FVECTOR campos;
    sceVu0FVECTOR camang;
    sceVu0FVECTOR vf;
    sceVu0FVECTOR vec;
    nkCamMNG *mng;
    s32 rtlen;
    VWork *vwrk;

    vwrk = &ViCon;
    mng = CamGetMNG(objw);
    rtw = objw->rtw;

    vwrk->old_rtn = GetMichiNo(objw->rtw.rtp);
    vwrk->release = 0;
    if (mng != NULL) {
        vwrk->nml = &camNor[mng->idx];
        KL2_OK_PRINT((1, 2, 22, scr_p[1], "vwrk->nml->zoom = 0x%x", ViCon.nml->zoom));
        rtlen = ((vwrk->nml->zoom << 12) - vwrk->rtlen) / 48;
        vwrk->rtlen += rtlen;
        wk = (vwrk->nml->trnsx - vwrk->offx) / 48.0f;
        vwrk->offx += wk;
        wk = (vwrk->nml->trnsy - vwrk->offy) / 48.0f;
        vwrk->offy += wk;
    }

    MichiPosi(&rtw, klpos);
    MichiMove(&rtw, -vwrk->rtlen);
    MichiPosi(&rtw, campos);
    sceVu0SubVector(vec, objw->posi, klpos);
    sceVu0Normalize(vec, vec);
    vf[0] = vec[0] * vwrk->offx;
    vf[1] = vec[1] * vwrk->offx;
    vf[2] = vec[2] * vwrk->offx;
    sceVu0AddVector(campos, campos, vf);
    cam->posi[0] += campos[0] - cam->posi[0];
    cam->posi[1] += campos[1] - cam->posi[1];
    cam->posi[2] += campos[2] - cam->posi[2];
    vf[0] = vec[0] * vwrk->offy;
    vf[1] = vec[1] * vwrk->offy;
    vf[2] = vec[2] * vwrk->offy;
    sceVu0AddVector(klpos, klpos, vf);
    vwrk->tposi[0] += klpos[0] - vwrk->tposi[0];
    vwrk->tposi[1] += klpos[1] - vwrk->tposi[1];
    vwrk->tposi[2] += klpos[2] - vwrk->tposi[2];
    hr_pcam_pi2rot(cam->posi, vwrk->tposi, camang);
    cam->ang[0] += camang[0] - cam->ang[0];
    cam->ang[1] += camang[1] - cam->ang[1];
    cam->ang[0] = nkRadMask(cam->ang[0]);
    cam->ang[1] = nkRadMask(cam->ang[1]);
    wk = objw->rot[2] - cam->ang[2];
    if (wk < -KL2_PI) {
        wk += KL2_2PI;
    } else if (wk > KL2_PI) {
        wk -= KL2_2PI;
    }
    cam->ang[2] += wk / 8.0f;
    cam->ang[2] = nkRadMask(cam->ang[2]);
}

void CamFollow(OBJWORK *objw, CAM_WORK *cam) {
    sceVu0FVECTOR wang;
    sceVu0FVECTOR wvec;
    sceVu0IVECTOR vi;
    sceVu0FVECTOR rtv;
    sceVu0FVECTOR angspd;
    VWork *vwrk = &ViCon;
    sceVu0FVECTOR wsvec;
    sceVu0FMATRIX wmat;
    RT_WRK *rtw = &objw->rtw;
    ROUTE *rtp = &rtw->rtp[rtw->plc];
    f32 fw1;
    HERO_WORK *herow;

    vi[0] = rtp->vec.x;
    vi[1] = rtp->vec.y;
    vi[2] = rtp->vec.z;
    vu0_ITOF0Vector(rtv, vi);
    if (objw->bun1 == 4) {
        CamPipe(objw, cam);
    } else {
        if (objw->bun1 == 3 || objw->bun1 == 4) {
            vwrk->tposi[0] = objw->posi[0];
            vwrk->tposi[1] = objw->posi[1];
            vwrk->tposi[2] = objw->posi[2];
            if (objw->bun1 == 3) {
                vwrk->offx = 0.0f;
            }
        } else if (objw->reg0 & 0x200) {
            herow = objw->work;
            vwrk->tposi[0] = objw->posi[0];
            vwrk->tposi[1] = objw->posi[1];
            vwrk->tposi[2] = objw->posi[2];
            GimGetMichiVec(&objw->rtw, rtv, herow->okuyuka);
        } else {
            CamScrLim(objw, objw->posi, vwrk->tposi);
        }

        wang[1] = _atan2(rtv[0], rtv[2]) + KL2_3PI2 + vwrk->angy;
        if (wang[1] < -KL2_PI) {
            wang[1] += KL2_2PI;
        } else if (wang[1] > KL2_PI) {
            wang[1] -= KL2_2PI;
        }

        if (GameGbl.cam.mode == 6 && vwrk->dcnt > 0.0f) {
            fw1 = -vwrk->angx - vwrk->wangx;
            if (fw1 < -KL2_PI) {
                fw1 += KL2_2PI;
            } else if (fw1 > KL2_PI) {
                fw1 -= KL2_2PI;
            }
            fw1 /= vwrk->dcnt;
            vwrk->wangx += fw1;
        } else {
            wang[0] = -vwrk->angx;
            angspd[0] = wang[0] - vwrk->wangx;
            if (angspd[0] < -KL2_PI) {
                angspd[0] += KL2_2PI;
            } else if (angspd[0] > KL2_PI) {
                angspd[0] -= KL2_2PI;
            }
            angspd[0] /= vwrk->adiv[0];
            vwrk->wangx += angspd[0];
        }
        if (vwrk->wangx < -KL2_PI) {
            vwrk->wangx += KL2_2PI;
        } else if (vwrk->wangx > KL2_PI) {
            vwrk->wangx -= KL2_2PI;
        }
        wang[0] = vwrk->wangx;

        angspd[1] = wang[1] - vwrk->wangy;
        if (angspd[1] < -KL2_PI) {
            angspd[1] += KL2_2PI;
        } else if (angspd[1] > KL2_PI) {
            angspd[1] -= KL2_2PI;
        }
        angspd[1] /= vwrk->adiv[1];
        vwrk->wangy += angspd[1];
        if (vwrk->wangy < -KL2_PI) {
            vwrk->wangy += KL2_2PI;
        } else if (vwrk->wangy > KL2_PI) {
            vwrk->wangy -= KL2_2PI;
        }
        wang[1] = vwrk->wangy;

        wvec[0] = vwrk->tposi[0];
        wvec[1] = vwrk->tposi[1];
        wvec[2] = vwrk->tposi[2];
        wvec[3] = 1.0f;
        sceVu0UnitMatrix(wmat);
        sceVu0RotMatrixX(wmat, wmat, wang[0]);
        sceVu0RotMatrixY(wmat, wmat, wang[1]);
        sceVu0TransMatrix(wmat, wmat, wvec);
        wsvec[0] = vwrk->posix + vwrk->offx;
        wsvec[1] = vwrk->posiy + vwrk->offy;
        wsvec[2] = -vwrk->zoom;
        wsvec[3] = 1.0f;
        sceVu0ApplyMatrix(cam->posi, wmat, wsvec);
        cam->ang[1] = -wang[1];
        cam->ang[0] = -wang[0];
        cam->ang[2] = vwrk->angz;
        if (KL2_VER_COND(((HERO_WORK *)objw->work)->gimm_flag & 0x800, objw->reg0 & 0x400)) {
            vwrk->angz = KL2_PI;
        } else {
            vwrk->angz = 0.0f;
        }
        if (GameGbl.reverse_cnt > 0.0) {
            if (KL2_VER_COND(((HERO_WORK *)objw->work)->gimm_flag & 0x800, objw->reg0 & 0x400)) {
                vwrk->angz = KL2_PI * GameGbl.reverse_cnt / 60.0f;
            } else {
                vwrk->angz = KL2_PI * GameGbl.reverse_cnt / 60.0f + KL2_PI;
            }
            if (vwrk->angz > KL2_PI) {
                vwrk->angz -= KL2_2PI;
            }
        }

        if (vwrk->dcnt > 0.0f) {
            vwrk->dcnt--;
        }
    }
}

void CamFix(CAM_WORK *cam, CAM_WORK *tcam) {
    sceVu0FVECTOR tgtp;
    sceVu0FVECTOR tgta;
    sceVu0FVECTOR vf;
    VWork *vwrk = &ViCon;
    f32 adiv = vwrk->dcnt;

    if (adiv <= 0.0f) {
        return;
    }

    sceVu0CopyVector(tgtp, tcam->posi);
    sceVu0CopyVector(tgta, tcam->ang);

    vf[0] = tgtp[0] - cam->posi[0];
    vf[1] = tgtp[1] - cam->posi[1];
    vf[2] = tgtp[2] - cam->posi[2];
    cam->posi[0] += vf[0] / adiv;
    cam->posi[1] += vf[1] / adiv;
    cam->posi[2] += vf[2] / adiv;

    vf[0] = tgta[0] - cam->ang[0];
    vf[1] = tgta[1] - cam->ang[1];
    vf[2] = tgta[2] - cam->ang[2];
    if (vf[0] < -KL2_PI) {
        vf[0] += KL2_2PI;
    } else if (vf[0] > KL2_PI) {
        vf[0] -= KL2_2PI;
    }
    if (vf[1] < -KL2_PI) {
        vf[1] += KL2_2PI;
    } else if (vf[1] > KL2_PI) {
        vf[1] -= KL2_2PI;
    }
    if (vf[2] < -KL2_PI) {
        vf[2] += KL2_2PI;
    } else if (vf[2] > KL2_PI) {
        vf[2] -= KL2_2PI;
    }
    cam->ang[0] += vf[0] / adiv;
    cam->ang[1] += vf[1] / adiv;
    cam->ang[2] += vf[2] / adiv;
    if (cam->ang[0] < -KL2_PI) {
        cam->ang[0] += KL2_2PI;
    } else if (cam->ang[0] > KL2_PI) {
        cam->ang[0] -= KL2_2PI;
    }
    if (cam->ang[1] < -KL2_PI) {
        cam->ang[1] += KL2_2PI;
    } else if (cam->ang[1] > KL2_PI) {
        cam->ang[1] -= KL2_2PI;
    }
    if (cam->ang[2] < -KL2_PI) {
        cam->ang[2] += KL2_2PI;
    } else if (cam->ang[2] > KL2_PI) {
        cam->ang[2] -= KL2_2PI;
    }

    vwrk->dcnt--;
}

void CamDivTime(CAM_WORK *cam, CAM_WORK *tcam, f32 *divtime) {
    sceVu0FVECTOR tgtp;
    sceVu0FVECTOR tgta;
    sceVu0FVECTOR vf;
    f32 adiv = *divtime;

    if (adiv <= 0.0f) {
        return;
    }

    adiv = ((adiv - 1.0f) * 0.3f + 1.0f);

    sceVu0CopyVector(tgtp, tcam->posi);
    sceVu0CopyVector(tgta, tcam->ang);

    vf[0] = tgtp[0] - cam->posi[0];
    vf[1] = tgtp[1] - cam->posi[1];
    vf[2] = tgtp[2] - cam->posi[2];
    cam->posi[0] += vf[0] / adiv;
    cam->posi[1] += vf[1] / adiv;
    cam->posi[2] += vf[2] / adiv;

    vf[0] = tgta[0] - cam->ang[0];
    vf[1] = tgta[1] - cam->ang[1];
    vf[2] = tgta[2] - cam->ang[2];
    if (vf[0] < -KL2_PI) {
        vf[0] += KL2_2PI;
    } else if (vf[0] > KL2_PI) {
        vf[0] -= KL2_2PI;
    }
    if (vf[1] < -KL2_PI) {
        vf[1] += KL2_2PI;
    } else if (vf[1] > KL2_PI) {
        vf[1] -= KL2_2PI;
    }
    if (vf[2] < -KL2_PI) {
        vf[2] += KL2_2PI;
    } else if (vf[2] > KL2_PI) {
        vf[2] -= KL2_2PI;
    }
    cam->ang[0] += vf[0] / adiv;
    cam->ang[1] += vf[1] / adiv;
    cam->ang[2] += vf[2] / adiv;
    if (cam->ang[0] < -KL2_PI) {
        cam->ang[0] += KL2_2PI;
    } else if (cam->ang[0] > KL2_PI) {
        cam->ang[0] -= KL2_2PI;
    }
    if (cam->ang[1] < -KL2_PI) {
        cam->ang[1] += KL2_2PI;
    } else if (cam->ang[1] > KL2_PI) {
        cam->ang[1] -= KL2_2PI;
    }
    if (cam->ang[2] < -KL2_PI) {
        cam->ang[2] += KL2_2PI;
    } else if (cam->ang[2] > KL2_PI) {
        cam->ang[2] -= KL2_2PI;
    }

    adiv = *divtime;
    adiv--;
    *divtime = adiv;
}

void CamMonOut(OBJWORK *objw, CAM_WORK *cam) {
    VWork *vwrk = &ViCon;
    f32 angx;
    f32 angy;
    f32 angz;

    if (GameGbl.cam.mode == 3 || GameGbl.cam.mode == 9 || GameGbl.cam.mode == 7) {
        angx = (cam->ang[0] * 360.0f) / KL2_2PI;
        angy = (cam->ang[1] * 360.0f) / KL2_2PI;
        angz = (cam->ang[2] * 360.0f) / KL2_2PI;
        KL2_OK_PRINT((1, 0x27, 0x1d, scr_p[1], "posix = %d", (s32)cam->posi[0]));
        KL2_OK_PRINT((1, 0x27, 0x1e, scr_p[1], "posiy = %d", (s32)cam->posi[1]));
        KL2_OK_PRINT((1, 0x27, 0x1f, scr_p[1], "posiz = %d", (s32)cam->posi[2]));
        KL2_OK_PRINT((1, 0x27, 0x20, scr_p[1], "angx  = %d", (s32)angx));
        KL2_OK_PRINT((1, 0x27, 0x21, scr_p[1], "angy  = %d", (s32)angy));
        KL2_OK_PRINT((1, 0x27, 0x22, scr_p[1], "angz  = %d", (s32)angz));
        KL2_OK_PRINT((1, 0x27, 0x23, scr_p[1], "Proj  = %d", (s32)cam->scr_z));
    } else {
        angx = (vwrk->angx * 360.0f) / KL2_2PI;
        angy = (vwrk->angy * 360.0f) / KL2_2PI;
        angz = (vwrk->angz * 360.0f) / KL2_2PI;
        KL2_OK_PRINT((1, 0x27, 0x1d, scr_p[1], "Zoom = %d", (s32)vwrk->zoom));
        KL2_OK_PRINT((1, 0x27, 0x1e, scr_p[1], "AngX = %d", (s32)angx));
        KL2_OK_PRINT((1, 0x27, 0x1f, scr_p[1], "AngY = %d", (s32)angy));
        KL2_OK_PRINT((1, 0x27, 0x20, scr_p[1], "AngZ = %d", (s32)angz));
        KL2_OK_PRINT((1, 0x27, 0x21, scr_p[1], "PosiX= %d", (s32)vwrk->posix));
        KL2_OK_PRINT((1, 0x27, 0x22, scr_p[1], "PosiY= %d", (s32)vwrk->posiy));
        KL2_OK_PRINT((1, 0x27, 0x23, scr_p[1], "Proj = %d", (s32)cam->scr_z));
    }
}

void CamTblCopy(VCONTBL *vt) {
    VWork *vwrk = &ViCon;

    vt->AngX = (vwrk->angx / KL2_2PI) * 360.0f;
    vt->AngY = (vwrk->angy / KL2_2PI) * 360.0f;
    vt->Zoom = vwrk->zoom;
    vt->PosX = vwrk->posix;
    vt->PosY = vwrk->posiy;
}

void CamNmlDiv(VWork *vwrk, nkCamNOR *nml) {
    f32 fw1;

    fw1 = (vwrk->nml->zoom - vwrk->zoom) / 48.0f;
    vwrk->zoom += fw1;

    fw1 = vwrk->nml->trnsx - vwrk->posix;
    if (fw1 > 2.0f) {
        vwrk->posix += 2.0f;
    } else if (fw1 < -2.0f) {
        vwrk->posix += -2.0f;
    } else {
        vwrk->posix = vwrk->nml->trnsx;
    }

    fw1 = vwrk->nml->trnsy - vwrk->posiy;
    if (fw1 > 2.0f) {
        vwrk->posiy += 2.0f;
    } else if (fw1 < -2.0f) {
        vwrk->posiy += -2.0f;
    } else {
        vwrk->posiy = vwrk->nml->trnsy;
    }

    fw1 = (vwrk->nml->proj - GameGbl.cam.scr_z) / 48.0f;
    GameGbl.cam.scr_z += fw1;

    vwrk->adiv[0] = 48.0f;
    vwrk->adiv[1] = 48.0f;
    vwrk->adiv[2] = 48.0f;
    vwrk->angx = nml->angx * 2.0f * KL2_PI / 360.0f;
    vwrk->angy = nml->angy * 2.0f * KL2_PI / 360.0f;
    vwrk->flg = nml->flg;
}

void CamCtrlTbl(OBJWORK *objw) {
    VWork *vwrk = &ViCon;
    HERO_WORK *herow = objw->work;
    nkCamMNG *mng = CamGetMNG(objw);
    nkCamNOR *nmr_p = camNor;
    nkCamFIX *fix_p = camFix;
    f32 fw1;
    f32 fw2;
    nkCamFIX *fix;
    s32 rtn;
    CAM_WORK *cam;
    CAM_WORK tcam;

    if (mng == NULL) {
        KL2_OK_PRINT((1, 2, 8, scr_p[1], "Camera DATA nothing!"));
        CamNmlDiv(vwrk, vwrk->nml);
        return;
    }

    if (objw->reg0 & 0x200) {
        rtn = GetMichiNo(herow->okuyuka->rtw.rtp);
    } else {
        rtn = GetMichiNo(objw->rtw.rtp);
    }

    if (mng->type == 1) {
        if (vwrk->tblcnt != vwrk->tblc_b) {
            vwrk->fwtime = 48.0f;
        }
        if (GameGbl.cam.mode != 7 && GameGbl.cam.mode != 6) {
            GameGbl.cam.mode = 1;
        }
        vwrk->nml = &nmr_p[mng->idx];
        if (vwrk->old_type == 2) {
            CamInitNml(vwrk->nml, objw, NULL);
        }
        CamNmlDiv(vwrk, vwrk->nml);
    } else if (mng->type == 2) {
        cam = &GameGbl.cam;
        fix = &fix_p[mng->idx];
        tcam.posi[0] = fix->posix;
        tcam.posi[1] = fix->posiy;
        tcam.posi[2] = fix->posiz;
        tcam.ang[0] = fix->angx * 2.0f * KL2_PI / 360.0f;
        tcam.ang[1] = fix->angy * 2.0f * KL2_PI / 360.0f;
        tcam.ang[2] = fix->angz * 2.0f * KL2_PI / 360.0f;

        fw1 = (fix->proj - GameGbl.cam.scr_z) / 48.0f;
        GameGbl.cam.scr_z += fw1;
        if (vwrk->tblcnt != vwrk->tblc_b || rtn != vwrk->old_rtn) {
            GameGbl.cam.mode = 9;
            vwrk->dtime = fix->time;
            vwrk->dcnt = vwrk->dtime;
            vwrk->frtime = fix->time;
            sceVu0CopyVector(vwrk->tposi, objw->posi);
        }
        CamFix(cam, &tcam);
    }

    vwrk->tblc_b = vwrk->tblcnt;
    vwrk->old_type = mng->type;
    vwrk->old_idx = mng->idx;
    vwrk->old_rtn = rtn;
}

void SetBossCamTbl(s32 tbln) {
    VWork *vwrk = &ViCon;
    vwrk->tblcnt = tbln;
}

void CamBossTbl(OBJWORK *objw) {
    VWork *vwrk = &ViCon;
    nkCamNOR *nmr_p = camNor;

    nmr_p += vwrk->tblcnt;
    vwrk->nml = nmr_p;
    CamNmlDiv(vwrk, nmr_p);
}

void CamGetPrm(sceVu0FVECTOR posi, sceVu0FVECTOR ang, sceVu0FVECTOR div) {
    VWork *vwrk = &ViCon;
    posi[0] = vwrk->posix;
    posi[1] = vwrk->posiy;
    posi[2] = vwrk->zoom;
    ang[0] = vwrk->angx;
    ang[1] = vwrk->angy;
    ang[2] = vwrk->angz;
    sceVu0CopyVector(div, vwrk->adiv);
}

void CamExtCtrl(sceVu0FVECTOR posi, sceVu0FVECTOR ang, sceVu0FVECTOR div) {
    VWork *vwrk = &ViCon;
    vwrk->zoom = posi[2];
    vwrk->posix = posi[0];
    vwrk->posiy = posi[1];
    vwrk->angx = ang[0];
    vwrk->angy = ang[1];
    vwrk->angz = ang[2];
    sceVu0CopyVector(vwrk->adiv, div);
    vwrk->release = 0;
}

void CamSetFlwFlag(s32 flg) {
    VWork *vwrk = &ViCon;
    vwrk->flg = flg;
}

void CamRelease(f32 div) {
    VWork *vwrk = &ViCon;
    if (GameGbl.cam.mode == 7) {
        CamVWorkInit(GameGbl.klonoa, &camThr);
    }
    vwrk->release = 1;
    vwrk->dcnt = div;
    KL2_DEBUG_PRINT(("Release = %f\n", div));
}

void CamInitThr(OBJWORK *objw) {
    // Empty function
}

void CamPadCtrl(OBJWORK *objw, CAM_WORK *cam) {
    VWork *vwrk = &ViCon;
    kPadDATA *kpd = &GameGbl.kpd[1];

    if (objw->bun1 != 4) {
        if (pPAD_LVL_R1(kpd) && vwrk->zoom > 60.0f) {
            vwrk->zoom -= 4.0f;
        }
        if (pPAD_LVL_R2(kpd) && vwrk->zoom < 9999.0f) {
            vwrk->zoom += 4.0f;
        }
        if (pPAD_LVL_CROSS(kpd)) {
            vwrk->angx -= KL2_PI / 180.0f;
        }
        if (pPAD_LVL_TRIANG(kpd)) {
            vwrk->angx += KL2_PI / 180.0f;
        }
        if (pPAD_LVL_CIRCLE(kpd)) {
            vwrk->angy -= KL2_PI / 180.0f;
        }
        if (pPAD_LVL_SQUARE(kpd)) {
            vwrk->angy += KL2_PI / 180.0f;
        }
        if (pPAD_LVL_DOWN(kpd)) {
            vwrk->posiy += 4.0f;
        }
        if (pPAD_LVL_UP(kpd)) {
            vwrk->posiy -= 4.0f;
        }
        if (pPAD_LVL_RIGHT(kpd)) {
            vwrk->posix += 4.0f;
        }
        if (pPAD_LVL_LEFT(kpd)) {
            vwrk->posix -= 4.0f;
        }
    }

    if (vwrk->angx < -KL2_PI) {
        vwrk->angx += KL2_2PI;
    } else if (vwrk->angx > KL2_PI) {
        vwrk->angx -= KL2_2PI;
    }

    if (vwrk->angy < -KL2_PI) {
        vwrk->angy += KL2_2PI;
    } else if (vwrk->angy > KL2_PI) {
        vwrk->angy -= KL2_2PI;
    }
}

void _CamChangeOku() {
    VWork *vwrk = &ViCon;
    vwrk->angy = KL2_PI2;
}

void _CamChangeTemae() {
    VWork *vwrk = &ViCon;
    vwrk->angy = -KL2_PI2;
}

void CamControl() {
    VWork *vwrk = &ViCon;

    switch (GameGbl.cam.mode) {
        case 1:
            KL2_OK_PRINT((1, 2, 1, scr_p[1], "Game Tbl Camera"));
            CamCtrlTbl(GameGbl.klonoa);
            if (GameGbl.cam.mode == 1) {
                if (vwrk->frtime > 0.0f) {
                    CamFollow(GameGbl.klonoa, &camThr);
                    CamDivTime(&GameGbl.cam, &camThr, &vwrk->frtime);
                } else {
                    CamFollow(GameGbl.klonoa, &GameGbl.cam);
                }
            }
            break;
        case 2:
            KL2_OK_PRINT((1, 2, 1, scr_p[1], "Klo TGT Camera"));
            if (fontDispID != 1) {
                CamFollow(GameGbl.klonoa, &GameGbl.cam);
            }
            break;
        case 3:
            KL2_OK_PRINT((1, 2, 1, scr_p[1], "Debug Camera"));
            if (fontDispID != 1) {
                CamDebug(&GameGbl.cam);
            }
            break;
        case 4:
            KL2_OK_PRINT((1, 2, 1, scr_p[1], "Camera Edit ver0.00"));
            break;
        case 5:
            break;
        case 9:
            KL2_OK_PRINT((1, 2, 1, scr_p[1], "Fix Camera"));
            CamCtrlTbl(GameGbl.klonoa);
#ifdef KL2_VER_RETAIL
            if (vwrk->release == 1 && !(vwrk->dcnt > 1.0f)) {
                vwrk->release = 0;
            }
#endif
            break;
        case 6:
            KL2_OK_PRINT((1, 2, 1, scr_p[1], "Obj Camera"));
            if (vwrk->release == 1) {
                if (vwrk->dcnt > 1.0f) {
                    CamCtrlTbl(GameGbl.klonoa);
                } else {
                    GameGbl.cam.mode = 1;
                    vwrk->release = 0;
                }
                CamFollow(GameGbl.klonoa, &GameGbl.cam);
            } else {
                if (vwrk->offx < 0.0f) {
                    vwrk->offx += 2.0f;
                } else if (vwrk->offx > 0.0f) {
                    vwrk->offx -= 2.0f;
                }
                CamFollow(GameGbl.klonoa, &GameGbl.cam);
            }
            break;
        case 7:
            KL2_OK_PRINT((1, 2, 0xe, scr_p[1], "nkCmTHR"));
            if (vwrk->release == 1) {
                OkPrint(1, 2, 0x16, scr_p[1], "Release! = %f", vwrk->dcnt);
                if (vwrk->dcnt > 0.0f) {
                    CamCtrlTbl(GameGbl.klonoa);
                    CamFollow(GameGbl.klonoa, &camThr);
                    CamDivTime(&GameGbl.cam, &camThr, &vwrk->dcnt);
                } else {
                    GameGbl.cam.mode = 1;
                    vwrk->release = 0;
                    CamFollow(GameGbl.klonoa, &GameGbl.cam);
                }
            }
            break;
        case 8:
            KL2_OK_PRINT((1, 2, 1, scr_p[1], "Suberi Oku Camera"));
            if (!(nkDG.flag & 8)) {
                GameGbl.cam.mode = 1;
            }
            CamPadCtrl(GameGbl.klonoa, &GameGbl.cam);
            CamFollow(GameGbl.klonoa, &GameGbl.cam);
            break;
        case 10:
            KL2_OK_PRINT((1, 2, 1, scr_p[1], "Boss Tbl Camera"));
            CamBossTbl(GameGbl.klonoa);
            if (GameGbl.cam.mode == 10) {
                if (vwrk->frtime > 0.0f) {
                    CamFollow(GameGbl.klonoa, &camThr);
                    CamDivTime(&GameGbl.cam, &camThr, &vwrk->frtime);
                } else {
                    CamFollow(GameGbl.klonoa, &GameGbl.cam);
                }
            }
            break;
    }
}
