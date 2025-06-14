#include "take/title.h"
#include "take/object.h"

qword_uni LogoGsEnv[64] = {};
int LogoGsEnvInd = 0;
qword_uni Kumo1GsEnv[64] = {};
int Kumo1GsEnvInd = 0;
qword_uni Kumo2GsEnv[64] = {};
int Kumo2GsEnvInd = 0;
void *pLogo = NULL;
void *pKumo1 = NULL;
void *pKumo2 = NULL;
static kPadDATA *kpd0;
static kPadDATA *kpd1;
#ifdef KL2_VER_RETAIL
static sceVu0FVECTOR SkyRot;
#endif
static sceVu0FVECTOR DbCameraRot;
static sceVu0FVECTOR DbCameraTra;

void SfxInitDebugCamera() {
    sceVu0FMATRIX TmpMtx;

    SETVEC(DbCameraRot, 0.0f, 0.0f, 0.0f, 0.0f);
    SETVEC(DbCameraTra, 0.0f, 0.0f, 0.0f, 1.0f);
    
#ifdef KL2_VER_RETAIL
    sceVu0UnitMatrix(TmpMtx);
    sceVu0RotMatrix(TmpMtx, TmpMtx, DbCameraRot);
    sceVu0RotMatrix(TmpMtx, TmpMtx, DbCameraRot);
    sceVu0TransMatrix(TmpMtx, TmpMtx, DbCameraTra);
#endif
    GetRotTransMatrixZYX(TmpMtx, DbCameraRot, DbCameraTra);
    sceVu0InversMatrix(Scr.WvMtx, TmpMtx);
    sceVu0MulMatrix(Scr.WsMtx, Scr.VsMtx, Scr.WvMtx);
}

void SfxDebugCameraWork() {
	sceVu0FMATRIX TmpMtx;

    if (!(GameGbl.kpd[1].lvl & 0xF0FA)) { // If you || all of the macros below, compiler does ld instead of lw
        return;
    }

    if (PAD_LVL_CROSS(GameGbl.kpd[1])) {
        DbCameraRot[0] += M_PI / 60.0;
        if (DbCameraRot[0] > M_PI) {
            DbCameraRot[0] -= M_PI * 2.0;
        }
    }
    if (PAD_LVL_TRIANG(GameGbl.kpd[1])) {
        DbCameraRot[0] -= M_PI / 60.0;
        if (DbCameraRot[0] < -M_PI) {
            DbCameraRot[0] += M_PI * 2.0;
        }
    }
    if (PAD_LVL_CIRCLE(GameGbl.kpd[1])) {
        DbCameraRot[1] += M_PI / 60.0;
        if (DbCameraRot[1] > M_PI) {
            DbCameraRot[1] -= M_PI * 2.0;
        }
    }
    if (PAD_LVL_SQUARE(GameGbl.kpd[1])) {
        DbCameraRot[1] -= M_PI / 60.0;
        if (DbCameraRot[1] < -M_PI) {
            DbCameraRot[1] += M_PI * 2.0;
        }
    }

    if (PAD_LVL_DOWN(GameGbl.kpd[1])) {
        DbCameraTra[1] += 1.0;
    }
    if (PAD_LVL_UP(GameGbl.kpd[1])) {
        DbCameraTra[1] -= 1.0;
    }
    if (PAD_LVL_RIGHT(GameGbl.kpd[1])) {
        DbCameraTra[0] += 1.0;
    }
    if (PAD_LVL_LEFT(GameGbl.kpd[1])) {
        DbCameraTra[0] -= 1.0;
    }
    if (PAD_LVL_R1(GameGbl.kpd[1])) {
        DbCameraTra[2] -= 1.0;
    }
    if (PAD_LVL_R2(GameGbl.kpd[1])) {
        DbCameraTra[2] += 1.0;
    }

    GetRotTransMatrixZYX(TmpMtx, DbCameraRot, DbCameraTra);
    sceVu0InversMatrix(Scr.WvMtx, TmpMtx);
    sceVu0MulMatrix(Scr.WsMtx, Scr.VsMtx, Scr.WvMtx);
}