#ifndef __HR_ABE_H
#define __HR_ABE_H

#include "common.h"
#include "harada/hr_prm.h"

extern void hr_abe_efcOn(PTEFC id, sceVu0FVECTOR v);
extern void hr_abe_efcWork(PTEFC id, sceVu0FVECTOR v);
extern void hr_abe_efcDel(PTEFC id);
extern void hr_abe_initCE();
extern void hr_abe_efcClean();
extern void hr_hato_efcOn(PTEFC id, sceVu0FVECTOR v, sceVu0FVECTOR r);
extern void hr_hato_efcWork(PTEFC id, sceVu0FVECTOR v, sceVu0FVECTOR r);
extern void hr_hato_efcDel(PTEFC id);

#endif