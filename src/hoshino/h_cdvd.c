#include "hoshino/h_cdvd.h"
#include "hoshino/h_str.h"

#ifdef KL2_VER_TRIAL
#define KLDATA_PATH "\\KLONOA2\\KLDATA.BIN;1"
#else
#define KLDATA_PATH "\\KLDATA.BIN;1"
#endif

#ifdef KL2_VER_TRIAL
KLTABLE FileData[] = {
    { 0, 179 },
    { 179, 1 },
    { 180, 393 },
    { 573, 7026 },
    { 7599, 37 },
    { 7636, 7 },
    { 7643, 215 },
    { 7858, 1 },
    { 7859, 37 },
    { 7896, 6513 },
    { 14409, 253 },
    { 14662, 7016 },
    { 21678, 37 },
    { 21715, 24 },
    { 21739, 193 },
    { 21932, 65 },
    { 21997, 37 },
    { 22034, 1 },
    { 22035, 37 },
    { 22072, 1 },
    { 22073, 37 },
    { 22110, 4 },
    { 22114, 37 },
    { 22151, 5 },
    { 22156, 37 },
    { 22193, 1 },
    { 22194, 37 },
    { 22231, 1 },
    { 22232, 37 },
    { 22269, 1 },
    { 22270, 37 },
    { 22307, 1 },
    { 22308, 37 },
    { 22345, 1 },
    { 22346, 37 },
    { 22383, 1 },
    { 22384, 37 },
    { 22421, 1 },
    { 22422, 37 },
    { 22459, 1 },
    { 22460, 1 },
    { 22461, 1 },
    { 22462, 83 },
    { 22545, 1 },
    { 22546, 83 },
    { 22629, 1 },
    { 22630, 141 },
    { 22771, 1 },
    { 22772, 85 },
    { 22857, 1 },
    { 22858, 77 },
    { 22935, 1 },
    { 22936, 83 },
    { 23019, 1 },
    { 23020, 77 },
    { 23097, 1 },
    { 23098, 77 },
    { 23175, 1 },
    { 23176, 77 },
    { 23253, 1 },
    { 23254, 367 },
    { 23621, 85 },
    { 23706, 37 },
    { 23743, 1 },
    { 23744, 1 },
    { 23745, 1 },
    { 23746, 1 },
    { 23747, 1 },
    { 23748, 131 },
    { 23879, 1 },
    { 23880, 82 },
    { 23962, 1 },
    { 23963, 37 },
    { 24000, 1 },
    { 24001, 37 },
    { 24038, 1 },
    { 24039, 37 },
    { 24076, 1 },
    { 24077, 37 },
    { 24114, 1 },
    { 24115, 37 },
    { 24152, 1 },
    { 24153, 37 },
    { 24190, 1 },
    { 24191, 37 },
    { 24228, 1 },
    { 24229, 37 },
    { 24266, 1 },
    { 24267, 37 },
    { 24304, 1 },
    { 24305, 37 },
    { 24342, 1 },
    { 24343, 37 },
    { 24380, 1 },
    { 24381, 37 },
    { 24418, 1 },
    { 24419, 37 },
    { 24456, 1 },
    { 24457, 37 },
    { 24494, 1 },
    { 24495, 1 },
    { 24496, 1 },
    { 24497, 1 },
    { 24498, 1 },
    { 24499, 1 },
    { 24500, 1 },
    { 24501, 1 },
    { 24502, 1 },
    { 24503, 1 },
    { 24504, 1 },
    { 24505, 1 },
    { 24506, 1 },
    { 24507, 1 },
    { 24508, 1 },
    { 24509, 1 },
    { 24510, 1 },
    { 24511, 1 },
    { 24512, 1 },
    { 24513, 1 },
    { 24514, 1 },
    { 24515, 1 },
    { 24516, 1 },
    { 24517, 1 },
    { 24518, 1 },
    { 24519, 1 },
    { 24520, 1 },
    { 24521, 1 },
    { 24522, 1 },
    { 24523, 1 },
    { 24524, 1 },
    { 24525, 1 },
    { 24526, 1 },
    { 24527, 1 },
    { 24528, 1 },
    { 24529, 1 },
    { 24530, 1 },
    { 24531, 1 },
    { 24532, 1 },
    { 24533, 1 },
    { 24534, 1 },
    { 24535, 1 },
    { 24536, 1 },
    { 24537, 1 },
    { 24538, 1 },
    { 24539, 1 },
    { 24540, 1 },
    { 24541, 1 },
    { 24542, 1 },
    { 24543, 1 },
    { 24544, 1 },
    { 24545, 1 },
    { 24546, 1 },
    { 24547, 1 },
    { 24548, 1 },
    { 24549, 1 },
    { 24550, 1 },
    { 24551, 1 },
    { 24552, 1 },
    { 24553, 1 },
    { 24554, 1 },
    { 24555, 1 },
    { 24556, 1 },
    { 24557, 1 },
    { 24558, 1 },
    { 24559, 1 },
    { 24560, 1 },
    { 24561, 1 },
    { 24562, 1 },
    { 24563, 1 },
    { 24564, 1 },
    { 24565, 1 },
    { 24566, 1 },
    { 24567, 1 },
    { 24568, 1 },
    { 24569, 1 },
    { 24570, 1 },
    { 24571, 1 },
    { 24572, 1 },
    { 24573, 1 },
    { 24574, 1 },
    { 24575, 1 },
    { 24576, 1 },
    { 24577, 1 },
    { 24578, 1 },
    { 24579, 1 },
    { 24580, 1 },
    { 24581, 1 },
    { 24582, 1 },
    { 24583, 1 },
    { 24584, 1 },
    { 24585, 1 },
    { 24586, 1 },
    { 24587, 1 },
    { 24588, 1 },
    { 24589, 1 },
    { 24590, 1 },
    { 24591, 1 },
    { 24592, 1 },
    { 24593, 565 },
    { 25158, 100 }
};
#endif
hCDDATA CdData = {};
hCDDATA *cD = NULL;
hCDCUE *cQ = NULL;
u8 cb_stack[0x2000] = {};

#ifdef KL2_VER_TRIAL
void LoadDebugFont(u32 *buff) {
    printf("LoadDebugFont\n");
    hCdReadFile("\\D\\ASC.TIM;1", buff);
}
#endif

void hCdReadFile(char *filename, u32 *buff) {
    sceCdlFILE fp;
    s32 sectors;
    s32 rsec;
    s32 flag;
    s32 wait;
    
    KL2_DEBUG_PRINT(("load file=%s\n",filename));
    sceCdDiskReady(0);
    while (!sceCdSearchFile(&fp, filename));
    sectors = ((fp.size + 0x7FF) / 0x800);
    if (sectors > 0x400) {
        sectors = 0x400;
    }

#ifdef KL2_VER_TRIAL
    while (!hCdRead(fp.lsn, sectors, buff, &cD->RMode));
    while (1) {
        rsec = 0xFFFFF;
        flag = sceCdSync(1);
        for (wait = 0; wait <= rsec; wait++);
        if (!flag) {
            break;
        }
    }
#else
    while (!sceCdRead(fp.lsn, sectors, buff, &cD->mode));
    while (1) {
        rsec = 0xFFFFF;
        for (wait = 0; wait <= rsec; wait++);
        flag = sceCdSync(1);
        if (!flag) {
            break;
        }
    }
#endif
}

#ifndef KL2_VER_TRIAL
u32* hCdReadFileRet(char *filename) {
    sceCdlFILE file;
    u32 *buf;
    s32 ret;
    s32 sectors;
    
    sceCdDiskReady(0);
    while (!sceCdSearchFile(&file, filename));
    sectors = ((file.size + 0x7FF) / 0x800);
    buf = (u32 *)getBuff(1, sectors * 0x800, NULL, &ret);
    while (!sceCdRead(file.lsn, sectors, buf, &cD->mode));
    do {
        s32 i;
        for (i = 0; i < 0x100000; i++);
    } while (sceCdSync(1));

    return buf;
}
#endif

void hCdCuePushLIFO(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 id;
    
    cQ->Exe--;
    if (cQ->Exe < 0) {
        cQ->Exe = 31;
    }

    id = cQ->Exe;
    cQ->Arg[id][0] = arg0;
    cQ->Arg[id][1] = arg1;
    cQ->Arg[id][2] = arg2;
    cQ->Arg[id][3] = arg3;
    cQ->Arg[id][4] = arg4;
    cQ->Num++;
}

void hCdCuePush(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 id = cQ->Reg;

    cQ->Arg[id][0] = arg0;
    cQ->Arg[id][1] = arg1;
    cQ->Arg[id][2] = arg2;
    cQ->Arg[id][3] = arg3;
    cQ->Arg[id][4] = arg4;
    if (++cQ->Reg == 32) {
        cQ->Reg = 0;
    }
    cQ->Num++;
}

void hCdCuePop(s32 *p) {
    s32 id = cQ->Exe;
    
    p[0] = cQ->Arg[id][0];
    p[1] = cQ->Arg[id][1];
    p[2] = cQ->Arg[id][2];
    p[3] = cQ->Arg[id][3];
    p[4] = cQ->Arg[id][4];

    cQ->Exe++;
    if (cQ->Exe == 32) {
        cQ->Exe = 0;
    }
    cQ->Num--;
}

void hCdCuePopTest(s32 *p) {
    s32 id = cQ->Exe;

    p[0] = cQ->Arg[id][0];
    p[1] = cQ->Arg[id][1];
    p[2] = cQ->Arg[id][2];
    p[3] = cQ->Arg[id][3];
    p[4] = cQ->Arg[id][4];
}

s32 hCdCueNum() {
    return cQ->Num;
}

s32 hCdCueTime() {
    return cQ->Arg[cQ->Exe][4];
}

void hCdCueFlushBGM() {
    s32 arr[32][5];
    s32 i;
    s32 num;

    num = 0;
    while (hCdCueNum() != 0) {
        hCdCuePop(arr[num++]);
    }
    
    for (i = 0; i < num; i++) {
        if (arr[i][3] != 1 && arr[i][3] != 2) {
            hCdCuePush(arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4]);
        }
    }
}

void hCdCueFlushPPT() {
    s32 arr[32][5];
    s32 i;
    s32 num;

    num = 0;
    while (hCdCueNum() != 0) {
        hCdCuePop(arr[num++]);
    }
    
    for (i = 0; i < num; i++) {
        if (arr[i][3] != 3) {
            hCdCuePush(arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4]);
        }
    }
}

#ifndef KL2_VER_TRIAL
void hCdCueFlushBGM2() {
    s32 i;
    s32 iVar2;
    s32 cue;
    u32 arr[32][5];

    i = 0;
    while ((cue = hCdCueNum()) != 0) {
        hCdCuePop(arr[i++]);
    }
    
    for (iVar2 = 0; iVar2 < i; iVar2++) {
        if (arr[iVar2][3] - 1 > 1) {
            hCdCuePush(arr[iVar2][0], arr[iVar2][1], arr[iVar2][2], arr[iVar2][3], arr[iVar2][4]);
        }
    }
}
#endif

void hCdCallback(s32 cb_reason) {
    // Empty function
}

s32 hCdRead(u32 lsn, u32 sectors, void *buff, sceCdRMode *mode) {
    KL2_DEBUG_PRINT(("hCdRead LSN=%d nSEC=%d BUFF=%08x\n", lsn, sectors, (u32)buff));
    sceCdDiskReady(0);
    if (sceCdRead(lsn, sectors, buff, mode) == 0) {
        KL2_DEBUG_PRINT(("CD COMMAND FAILED\n"));
        return 0;
    } else {
        cD->dataLSN = lsn;
        cD->dataSectors = sectors;
        cD->dataBuff = buff;
        return 1;
    }
}

s32 hCdReadIOPm(u32 lsn, u32 sectors, void *buff, sceCdRMode *mode) {
    sceCdDiskReady(0);
    if (sceCdReadIOPm(lsn, sectors, buff, mode) == 0) {
        KL2_DEBUG_PRINT(("CD COMMAND FAILED(IOP)\n"));
        return 0;
    } else {
        cD->dataLSN = lsn;
        cD->dataSectors = sectors;
        cD->dataBuff = buff;
        return 1;
    }
}

s32 hCdGetSize(s32 no) {
    return FileData[no].sectors;
}

// Note: buff type changed from s32 to void* (???)
void hCdReadDataBlock(s32 no, void *buff) {
#ifdef KL2_VER_TRIAL
    hCdRead(cD->Fp.lsn + FileData[no].lsn, FileData[no].sectors, buff, &cD->RMode);
    while (sceCdSync(1));
#else
    sceCdDiskReady(0);
    while (!sceCdRead( cD->file.lsn + FileData[no].lsn, FileData[no].sectors, (void *)buff, &cD->mode));
    do {
        s32 i;
        for (i = 0; i < 0x100000; i++) {
            // Do nothing
        }
    } while (sceCdSync(1));
#endif
}

// Note: buff type changed from s32 to void*
void hCdReadData(s32 no, void *buff) {
    hCdCuePush((cD->Fp).lsn + FileData[no].lsn, FileData[no].sectors, (s32)buff, 4, cD->eeCnt);
}

s32 hCdReadSync() {
    if (cD->dataFlag == CDREAD_DATA && cD->dataStat == 2) {
        return 1;
    } else {
        return 0;
    }
}

#ifndef KL2_VER_TRIAL
s32 hCdDataStat() {
    return cD->dataStat;
}
#endif

void hCdInit() {
    u32 *buff;

    KL2_DEBUG_PRINT(("hCdInit ...\n"));
    cD = &CdData;
    cQ = &cD->Cue;

    cQ->Num = 0;
    cQ->Exe = 0;
    cQ->Reg = 0;

    cD->eeCnt = 0;
    cD->dataFlag = CDREAD_IDLE;
    cD->BGMplay = 0;
    cD->RMode.trycount = 0;
#ifdef KL2_VER_TRIAL
    cD->RMode.spindlctrl = 1;
#else
    cD->RMode.spindlctrl = 0;
#endif
    cD->RMode.datapattern = 0;
#ifndef KL2_VER_TRIAL
    cD->RMode.pad = 0;
#endif
    
    sceCdInitEeCB(0, cb_stack, sizeof(cb_stack));
    cD->ThID = GetThreadId();
    ChangeThreadPriority(cD->ThID, 1);

    sceCdDiskReady(0);
    cD->DiscType = sceCdGetDiskType();

#ifndef KL2_VER_TRIAL
    buff = hCdReadFileRet("\\HEADPACK.BIN;1");
    FileData = (KLTABLE *)(GetFHMAddress(buff, 0) + 1);
    PptTable = (PPTTABLE *)(GetFHMAddress(buff, 1) + 1);
    BgmTable = (BGMTABLE *)(GetFHMAddress(buff, 2) + 1);
#endif

    sceCdDiskReady(0);
    while (!sceCdSearchFile(&cD->Fp, KLDATA_PATH));

    KL2_DEBUG_PRINT(("hCdInit ... done\n"));
}

void hCdMain() {
    s32 arg[5];
    s32 com_ok;
    s32 stat;

    while ((cD->DiscError = sceCdGetError()) == -1);
#ifdef KL2_VER_TRIAL
    cD->DiscStat = sceCdStatus();
#endif
    cD->Sync = sceCdSync(1);

    switch (cD->DiscError) {
        case SCECdErNO:
        case SCECdErABRT:
            com_ok = 1;
            break;
        case SCECdErNORDY:
            com_ok = 0;
            break;
        default:
            com_ok = 0;
            while (!sceCdBreak());
            sceCdDiskReady(1);
            if (cD->dataStat != 0) {
                KL2_DEBUG_PRINT(("CD READ RESUME=%d\n", cD->DiscError));
                hCdCuePushLIFO(cD->dataLSN, cD->dataSectors, (s32)cD->dataBuff, cD->dataFlag, cD->eeCnt);
                cD->dataFlag = CDREAD_IDLE;
                cD->dataStat = 0;
            }
            break;
    }

    if (cD->dataStat == 2) {
        cD->dataFlag = CDREAD_IDLE;
        cD->dataStat = 0;
    }

#ifdef KL2_VER_TRIAL
    if (hCdCueNum() > 0 && hCdCueTime() <= cD->eeCnt && com_ok && hCdDiscStatOK() && cD->dataStat == 0)
#else
    if (hCdCueNum() > 0 && hCdCueTime() <= cD->eeCnt && com_ok && cD->dataStat == 0)  
#endif
    {
        hCdCuePopTest(arg);
        cD->dataFlag = arg[3];
        switch (cD->dataFlag) {
            case CDREAD_BGM:
                stat = hCdReadIOPm(arg[0], arg[1], (void *)arg[2], &cD->RMode);
                break;
            case CDREAD_BGM2:
                stat = hCdReadIOPm(arg[0], arg[1], (void *)arg[2], &cD->RMode);
                break;
            case CDREAD_PPT:
                stat = hCdRead(arg[0], arg[1], (void *)arg[2], &cD->RMode);
                break;
            case CDREAD_DATA:
                stat = hCdRead(arg[0], arg[1], (void *)arg[2], &cD->RMode);
                break;
#ifndef KL2_VER_TRIAL
            case 5:
                stat = hCdRead(arg[0], arg[1], arg[2], &cD->mode);
                break;
#endif
        }
        if (stat != 0) {
            hCdCuePop(arg);
            cD->dataStat = 1;
            cD->Sync = 1;
        }
    }

    if (cD->dataStat != 0 && cD->Sync == 0) {
        cD->dataStat = 2;
    }

    hBgmMain();
    hPptMain();
#ifndef KL2_VER_TRIAL
    hStrMain();
#endif
    hStrInfo();

    cD->eeCnt++;
}

s32 hCdDiscStatOK() {
#ifdef KL2_VER_TRIAL
    switch (cD->DiscStat) {
        case SCECdStatSpin:
        case SCECdStatPause:
        case SCECdStatStop:
            return 1;
        default:
            return 0;
        
    }
#else
    switch (cD->DiscError) {
        case SCECdErNO:
        case SCECdErABRT:
            return 0;
        default:
            return 1;
    }
#endif
}
