#include "harada/hr_ttt.h"

#ifdef KL2_VER_TRIAL
void EraseVoiceMime(SFXOBJ *pObj) {
    if (pObj->pMime != NULL) {
        pObj->pMime->pVmime = NULL;
        pObj->pMime->VmimeInd = 0;
        pObj->pMime->VmimeCnt = 0.0f;
        pObj->pMime->VmimeCntSpeed = 1.0f; 
    }
}
#endif