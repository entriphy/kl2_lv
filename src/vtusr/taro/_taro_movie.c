#include "vtusr/taro/taro_movie.h"
#include "common.h"
#include "kit.h"
#include "vtusr/vtutil.h"
#include <eeregs.h>

static u16 dmaStat = 0;
static u16 _ipuTimeout = 20;
static char _funcname[256];

void vtIPU_pr_vtIDEC_MOVIE(vtIDEC_MOVIE *movie, char *msg) {
    s32 i;
    
    KL2_DEBUG_PRINT(("-----------------------------------------------------\n"));
    KL2_DEBUG_PRINT(("%s", msg));
    KL2_DEBUG_PRINT(("(vtIPU_pr_vtIDEC_MOVIE) dmaStat = 0x%x\n", dmaStat));
    KL2_DEBUG_PRINT(("(vtIPU_pr_vtIDEC_MOVIE) movie = 0x%x\n", movie));
    KL2_DEBUG_PRINT(("\ttype = 0x%x\n", movie->type));
    KL2_DEBUG_PRINT(("\tbsDataSize = 0x%x\n", movie->bsDataSize));
    KL2_DEBUG_PRINT(("\tnframes = %d\n", movie->nframes));
    KL2_DEBUG_PRINT(("\tframe_cnt = %d\n", movie->frame_cnt));
    KL2_DEBUG_PRINT(("\twidth,height  = [%d %d]\n", movie->width, movie->height));
    KL2_DEBUG_PRINT(("\tmbx,mby       = [%d %d]\n", movie->mbx, movie->mby));
    KL2_DEBUG_PRINT(("\ttexbp,texbw   = [%d %d]\n", movie->texbp, movie->texbw));
    KL2_DEBUG_PRINT(("\ttw,th         = [%d %d]\n", movie->tw, movie->th));
    KL2_DEBUG_PRINT(("\tthVal0,thVal1 = [%d %d]\n", movie->thVal0, movie->thVal1));
    KL2_DEBUG_PRINT(("\tincnum = %d\n", movie->incnum));
    KL2_DEBUG_PRINT(("\tcbp = 0x%x\n", movie->cbp));
    KL2_DEBUG_PRINT(("\tcpsm,csm,csa,cld = [%d %d %d %d]\n", movie->cpsm, movie->csm, movie->csa, movie->cld));
    KL2_DEBUG_PRINT(("\tgsClut = 0x%x\n", movie->gsClut));
    KL2_DEBUG_PRINT(("\tipuClut = 0x%x\n", movie->ipuClut));
    KL2_DEBUG_PRINT(("\tkillFg = %d\n", movie->killFg));
    KL2_DEBUG_PRINT(("\ttop = 0x%x\n", movie->top));
    for (i = 0; i < movie->nframes; i++) {
        KL2_DEBUG_PRINT(("\t    top[%d] = 0x%x\n", i, movie->top[i]));
    }
    KL2_DEBUG_PRINT(("\tbsData = 0x%x\n", movie->bsData));
    KL2_DEBUG_PRINT(("\tbsData1Addr = 0x%x\n", movie->bsData1Addr));
    KL2_DEBUG_PRINT(("\tbsData1Size = 0x%x\n", movie->bsData1Size));
    KL2_DEBUG_PRINT(("\tbsTags = 0x%x\n", movie->bsTags));
    KL2_DEBUG_PRINT(("\tdmaTags = [0x%x 0x%x]\n", movie->dmaTags[0], movie->dmaTags[1]));
    KL2_DEBUG_PRINT(("\tcscBuff = [0x%x 0x%x]\n", movie->cscBuff[0], movie->cscBuff[1]));
    KL2_DEBUG_PRINT(("\tidctBuff = [0x%x 0x%x]\n", movie->idctBuff[0], movie->idctBuff[1]));
    KL2_DEBUG_PRINT(("\tvqBuff = [0x%x 0x%x]\n", movie->vqBuff[0], movie->vqBuff[1]));
    KL2_DEBUG_PRINT(("\tcurrentBufNo = %d\n", movie->currentBufNo));
    KL2_DEBUG_PRINT(("-----------------------------------------------------\n", msg)); // no %s?
}

// TODO: regswap
s32 vtIPU_Sync(s32 mode, u16 timeout) {
    s32 i;

    if (DGET_IPU_CTRL() & IPU_CTRL_ECD_M) {
        DPUT_IPU_CTRL(IPU_CTRL_RST_M);
        sceIpuSync(0, 0);
        DPUT_D_ENABLEW(D_ENABLEW_CPND_M);
        while (!(DGET_D_ENABLER() & D_ENABLER_CPND_M));
    } else {
        i = 0;
        while (i < timeout * 720 && *(vs32 *)IPU_CTRL < 0) {
            i++;
        }
        if (i < timeout * 720) {
            return 0;
        }
        KL2_DEBUG_PRINT(("IPU TIMEOUT: %s\n", _funcname));
        DPUT_IPU_CTRL(IPU_CTRL_RST_M);
        sceIpuSync(0, 0);
        DPUT_D_ENABLEW(D_ENABLEW_CPND_M);
        while (!(DGET_D_ENABLER() & D_ENABLER_CPND_M));
    }

    DPUT_D3_CHCR(0);
    i = dmaStat;
    DPUT_D_STAT(0x8);
    DPUT_D4_CHCR(0);
    i &= ~0x18;
    dmaStat = i;
    DPUT_D_STAT(0x10);
    DPUT_D_ENABLEW(0);
    sceIpuInit();
    sceIpuSync(0,0);
    DPUT_IPU_CMD(0);
    sceIpuSync(0,0);

    return -1;
}

void vtCpMovieStruct(vtIDEC_MOVIE *m1, vtIDEC_MOVIE *m0, u32 vram_addr) {
m1->type = m0->type;
    m1->bsDataSize = m0->bsDataSize;
    m1->width = m0->width;
    m1->height = m0->height;
    m1->nframes = m0->nframes;
    m1->thVal0 = m0->thVal0;
    m1->thVal1 = m0->thVal1;
    m1->incnum = m0->incnum;
    m1->frame_cnt = m0->frame_cnt;
    m1->mbx = m0->mbx;
    m1->mby = m0->mby;
    m1->texbp = vram_addr;
    m1->texbw = m0->texbw;
    m1->tw = m0->tw;
    m1->th = m0->th;
    m1->killFg = m0->killFg;
    m1->top = m0->top;
    m1->bsData = m0->bsData;
    m1->bsData1Addr = m0->bsData1Addr;
    m1->bsData1Size = m0->bsData1Size;
    m1->bsTags = m0->bsTags;
    m1->dmaTags[0] = vtGetBuf64(0x6400);
    m1->dmaTags[1] = vtGetBuf64(0x6400);
    m1->cscBuff[0] = m0->cscBuff[0];
    m1->cscBuff[1] = m0->cscBuff[1];
    vtIPU_mkDmaTagOfSendTex(m1->dmaTags[0], m1->cscBuff[0], m1);
    vtIPU_mkDmaTagOfSendTex(m1->dmaTags[1], m1->cscBuff[1], m1);
}

void vtIPU_setTH(vtIDEC_MOVIE *movie, s32 maxVal, s32 minVal) {
    movie->thVal1 = maxVal > 255 ? 255 : maxVal < 0 ? 0 : maxVal;
    movie->thVal0 = minVal < 0 ? 0 : minVal > 255 ? 255 : minVal;
}

void vtIPU_setMabiki(vtIDEC_MOVIE *movie, u32 skipVal) {
    if (movie->type != 1) {
        return;
    }

    skipVal++;
    if (skipVal > movie->nframes) {
        skipVal = movie->nframes;
    }

    if (movie->type == 1) { // you already checked for this...
        if (movie->incnum < 0) {
            movie->incnum = -skipVal;
        } else {
            movie->incnum = skipVal;
        }
    }
}

void vtIPU_setIncrementNum(vtIDEC_MOVIE *movie, s32 num) {
    if (movie->type != 1) {
        movie->incnum = 1;
        return;
    }

    if (num > 0) {
        if (num > movie->nframes) {
            num = movie->nframes;
        }
    } else {
        if (-num < movie->nframes) {
            num = -movie->nframes;
        }
    }

    if (movie->type == 1) {
        movie->incnum = num;
    }
}

void vtIPU_initVQ(vtIDEC_MOVIE *movie, u16 *ipuClut, u8 *gsClut, u32 cbp, u32 cpsm, u32 csm, u32 csa, u32 cld) {
    movie->ipuClut = ipuClut;
    movie->gsClut = gsClut;
    if (cbp == 0) {
        s32 var_v1 = (s32)powf(2.0, movie->tw + movie->th - 6) + movie->texbp;
        cbp = var_v1;
    }
    movie->cbp = cbp;
    movie->cpsm = cpsm;
    movie->csm = csm;
    movie->csa = csa;
    movie->cld = cld;

    KL2_DEBUG_PRINT(("movie->cpb = %d 0x%x\n", movie->cbp, movie->cbp));
    KL2_DEBUG_PRINT(("movie->cpsm = %d\n", movie->cpsm));
    KL2_DEBUG_PRINT(("movie->csm = %d\n", movie->csm));
    KL2_DEBUG_PRINT(("movie->csa = %d\n", movie->csa));
    KL2_DEBUG_PRINT(("movie->cld = %d\n", movie->cld));
}

void vtIPU_init(vtIDEC_MOVIE *movie, s64 texaddr) {
    if (texaddr < 0) {
        movie->frame_cnt = 0;
    } else {
        movie->texbp = texaddr;
        movie->frame_cnt = 0;
    }
    movie->currentBufNo = 0;
    movie->killFg = 0;

    DPUT_D_PCR(DGET_D_PCR() | 0x318);
    DPUT_D_STAT(0x8);
    DPUT_D_STAT(0x10);
    DPUT_D_STAT(0x100);
    DPUT_D_STAT(0x200);
    DPUT_D_CTRL(DGET_D_CTRL() & 0x70F | 0x70);
    dmaStat = 0;
    sceIpuInit();
}

s32 vtIPU_getFilesize(char *file) {
    s32 fd;
    s32 filesize;

    fd = sceOpen(file, SCE_RDONLY);
    if (fd < 0) {
        return 0;
    }

    filesize = sceLseek(fd, 0, SEEK_END);
    sceClose(fd);

    return filesize;
}

s32 vtIPU_readFile(char *file, u8 *buff, s32 filesize) {
    s32 fd = sceOpen(file, SCE_RDONLY);
    if (fd < 0) {
        return 0;
    }

    KL2_DEBUG_PRINT(("Read Data start: file[%s] %dbytes\n", file, filesize));
    if (sceRead(fd, buff, filesize) != filesize) {
        sceClose(fd);
        return 0;
    } else {
        KL2_DEBUG_PRINT(("Read done: file[%s] %dbytes\n", file, filesize));
        sceClose(fd);
        return 1;
    }
}

s32 vtIPU_setBsdata(vtIDEC_MOVIE *movie, u8 *data) {
    s32 n;

    movie->bsDataSize = *(u32 *)(data + 0x04);
    movie->width = *(u16 *)(data + 0x08);
    movie->height = *(u16 *)(data + 0x0A);
    movie->nframes = *(u32 *)(data + 0x0C);
    if (data[0] == 'v' && data[1] == 't' && data[2] == 'i' && data[3] == 'p') {
        movie->type = 1;
        movie->top = (u32 *)(data + 0x20);
        n = movie->nframes * 4;
        n = (n + 55) >> 4 << 4;
        movie->bsData = data + n;
        movie->thVal0 = *(data + 0x10);
        movie->thVal1 = *(data + 0x11);
        movie->incnum = *(u16 *)(data + 0x12) + 1;
        movie->texbp = *(u32 *)(data + 0x14);
    } else if (data[0] == 'i' && data[1] == 'p' && data[2] == 'u' && data[3] == 'm') {
        movie->type = 0;
        movie->bsDataSize -= 8;
        movie->bsData = data + 0x10;
        movie->thVal0 = 0;
        movie->thVal1 = 0;
        movie->incnum = 1;
    } else if (data[0] == 'v' && data[1] == 't' && data[2] == 'i' && data[3] == 'c') {
        movie->type = 1;
        movie->thVal0 = *(data + 0x10);
        movie->thVal1 = *(data + 0x11);
        movie->incnum = *(u16 *)(data + 0x12) + 1;
        movie->texbp = *(u32 *)(data + 0x14);
        return 0;
    } else {
        return -1;
    }

    KL2_DEBUG_PRINT(("movie type = %s\n", movie->type == 0 ? "SCE" : "VT"));
    KL2_DEBUG_PRINT(("movie bsDataSize = %d\n", movie->bsDataSize));
    KL2_DEBUG_PRINT(("movie nframes = %d\n", movie->nframes));
    if (movie->type != 0) {
        KL2_DEBUG_PRINT(("movie texbp = %d 0x%x\n", movie->texbp, movie->texbp));
        KL2_DEBUG_PRINT(("movie thVal0 = %d thVal1 = %d\n", movie->thVal0, movie->thVal1));
        KL2_DEBUG_PRINT(("movie incnum = %d\n", movie->incnum));
    }

    movie->mbx = movie->width >> 4;
    movie->mby = movie->height >> 4;
    movie->texbw = movie->width >> 6;

    for (movie->tw = 0; movie->width >> movie->tw > 1; movie->tw++);
    for (movie->th = 0; movie->height >> movie->th > 1; movie->th++);

    KL2_DEBUG_PRINT(("movie width = %d\n", movie->width));
    KL2_DEBUG_PRINT(("movie height = %d\n", movie->height));
    KL2_DEBUG_PRINT(("movie mbx = %d\n", movie->mbx));
    KL2_DEBUG_PRINT(("movie mby = %d\n", movie->mby));
    KL2_DEBUG_PRINT(("movie texbw = %d\n", movie->texbw));
    KL2_DEBUG_PRINT(("movie tw = %d\n", movie->tw));
    KL2_DEBUG_PRINT(("movie th = %d\n", movie->th));

    return 1;
}

s32 vtIPU_getBsTags_buflen(vtIDEC_MOVIE *movie) {
    if (movie->type == 0) {
        return 11;
    } else {
        return movie->nframes + 1;
    }
}

void vtIPU_setWorkBuff(vtIDEC_MOVIE *movie, u128 *bstags, u128 *dmaTags0, u128 *dmaTags1, sceIpuRGB32 *cscBuff0, sceIpuRGB32 *cscBuff1) {
    movie->bsTags = bstags;
    movie->dmaTags[0] = dmaTags0;
    movie->dmaTags[1] = dmaTags1;
    movie->cscBuff[0] = cscBuff0;
    movie->cscBuff[1] = cscBuff1;
}

void vtIPU_mkDmaTagToIPU(vtIDEC_MOVIE *movie) {
    if (movie->type == 0) {
        movie->incnum = 0;
        mkDmaTagToIPU_SCE(movie->bsTags, movie->bsData, movie->bsDataSize);
    }
}

// awful
static u128* _mk1DmaTagToIPU(vtIDEC_MOVIE *movie, u64 *ptr, u32 *size) {
    u64 *p;
    s32 i;
    s32 j;

    *size = 0;
    if (!((u32)ptr & 0x70000000)) {
        p = UNCACHED(ptr);
    } else {
        p = ptr;
    }

    i = movie->frame_cnt;
    for (j = 0; j <= 0 && i < movie->nframes; i += movie->incnum, j++, p += 2) {
        *p = (u64)((movie->top[i + 1] >> 4) - (movie->top[i] >> 4) | DMAref) | (u64)((u32)movie->bsData + (movie->top[i] & 0xFFFFFFF0) & 0x0FFFFFFF) << 32; 
        *size += (movie->top[i + 1] >> 4) - (movie->top[i] >> 4);
    }

    i = movie->nframes;
    *p = ((u64)(((u32)movie->bsData + (movie->top[i] & 0xFFFFFFF0) & 0x0FFFFFFF)) << 32) | 0x30000001;
    *size += 1;
    *p &= 0xFFFFFFFFCFFFFFFF;
    p += 2;
    __asm__("sync");
    
    return !((u32)ptr & 0x70000000) ? (u128 *)((u32)p & 0x0FFFFFFF) : (u128 *)p;
}

void vtIPU_sendBsdataToSPR(vtIDEC_MOVIE *movie, u32 ptrOnSPR) {
    s32 n;

    if (movie->type != 1) {
        return;
    }

    movie->bsData1Addr = (ptrOnSPR + 0x3F) >> 6 << 6;
    n = movie->top[movie->frame_cnt];
    vtIPU_wait(movie,9);
    vtIPU_wait(movie,4);
    DPUT_D9_MADR((u32)&movie->bsData[n] & 0xFFFFFFF0);
    DPUT_D9_QWC((movie->top[movie->frame_cnt + 1] >> 4) - (n >> 4));
    DPUT_D9_SADR(movie->bsData1Addr);
    DPUT_D9_CHCR(0x100);
    dmaStat |= 0x200;
    movie->bsData1Size = ((movie->top[movie->frame_cnt + 1] - n) + 0xF) >> 4 << 4;
}

static s32 _decodeFlag(u32 *flag) {
    strcpy(_funcname, "_decodeFlag()");

    DPUT_IPU_CMD(0x40000000);
    sceIpuSync(0, 0);
    *flag = DGET_IPU_CMD() >> 0x18;
    if (vtIPU_Sync(0, _ipuTimeout)) {
        return -1;
    }

    DPUT_IPU_CMD(0x40000008);
    if (vtIPU_Sync(0, _ipuTimeout)) {
        return -1;
    }

    DPUT_IPU_CTRL((*flag & 0xfffffffb) << 0x10 | 0x1000000);
    return 0;
}

void vtIPU_startDecode(vtIDEC_MOVIE *movie) {
    vtIPU_decode(movie);
}

static s32 vtIPU_decodeSCE(vtIDEC_MOVIE *movie) {
    sceIpuDmaEnv env;

    strcpy(_funcname, "vtIPU_decodeSCE()");

    if (movie->frame_cnt != 0) {
        return 0;
    }

    DPUT_IPU_CTRL(0x40000000);
    if (vtIPU_Sync(0, _ipuTimeout)) {
        return -1;
    }

    sceIpuStopDMA(&env);
    DPUT_IPU_CMD(0x00);
    sceIpuRestartDMA(&env);
    if (vtIPU_Sync(0, _ipuTimeout)) {
        return -1;
    }

    vtIPU_wait(movie,4);
    DPUT_D4_TADR(movie->bsTags);
    DPUT_D4_MADR(0x0);
    DPUT_D4_QWC(0x0);
    DPUT_D4_CHCR(0x104);
    dmaStat |= 0x10;

    return 0;
}

s32 vtIPU_decode(vtIDEC_MOVIE *movie) {
    u32 flag;
    sceIpuDmaEnv env;
    u8 *p;
    s32 i;
    s32 j;

    strcpy(_funcname, "vtIPU_decode()");
    if (movie->frame_cnt >= movie->nframes) {
        movie->frame_cnt = 0;
    } else {
        movie->frame_cnt = (movie->frame_cnt + (movie->type == 1 ? movie->incnum : 1)) % movie->nframes;
    }
    movie->currentBufNo ^= 1;
    if (movie->type == 0) {
        if (vtIPU_decodeSCE(movie)) {
            return -1;
        }
    } else {
        DPUT_IPU_CTRL(0x40000000);
        if (vtIPU_Sync(0, _ipuTimeout)) {
            return -1;
        }

        sceIpuStopDMA(&env);
        DPUT_IPU_CMD(0x00);
        sceIpuRestartDMA(&env);
        if (vtIPU_Sync(0, _ipuTimeout)) {
            return -1;
        }
        
        if (movie->killFg) {
            return 0;
        }

        vtIPU_sendBsdataToSPR(movie, (u32)SPR_MEM);
        p = (u8 *)(movie->bsData1Addr | 0x70000000) + movie->bsData1Size;
        movie->bsData1Size += 19;
        movie->bsData1Size >>= 4;
        movie->bsData1Size <<= 4;
        vtIPU_wait(movie, 9);

        for (i = 0; i < 16; i++) {
            j = -i;
            if (p[j - 1] == 0xB0 && p[j - 2] == 1) {
                p[j + 0] = 0x00;
                p[j + 1] = 0x00;
                p[j + 2] = 0x01;
                p[j + 3] = 0xB1;
                for (j = i - 4; j >= 0; j--) {
                    p[-j] = 0;
                }
            }
        }

        vtIPU_wait(movie, 4);
        DPUT_D4_TADR(0x00);
        DPUT_D4_MADR(movie->bsData1Addr & 0x0FFFFFFF | 0x80000000);
        DPUT_D4_QWC(movie->bsData1Size >> 4);
        DPUT_D4_CHCR(0x100);
        dmaStat |= 0x10;
    }

    vtIPU_wait(movie, 3);
    DPUT_D3_MADR(movie->cscBuff[movie->currentBufNo]);
    DPUT_D3_QWC((movie->mbx * movie->mby) << 10 >> 4);
    DPUT_D3_CHCR(0x100);
    dmaStat |= 0x8;
    DPUT_IPU_CMD(0x90000000 | movie->thVal1 << 16 | movie->thVal0);
    if (_decodeFlag(&flag) == -1) {
        return -1;
    }
    DPUT_IPU_CMD(0x10010000 | (flag >> 2 & 1) << 24);
    return 0;
}

static s32 _skipFrameDelimitaCode() {
    strcpy(_funcname, "_skipFrameDelimitaCode()");
    DPUT_IPU_CMD(0x40000020);
    if (vtIPU_Sync(0, _ipuTimeout)) {
        return -1;
    }
    return 0;
}

s32 vtIPU_wait(vtIDEC_MOVIE *movie, s32 id) {
    strcpy(_funcname, "vtIPU_wait()");

    if ((id == 3 || id == 4) && vtIPU_Sync(0, _ipuTimeout)) {
        return -1;
    }

    if (((dmaStat >> id) & 1) && !(DGET_D_STAT() & 1 << id)) {
        __asm__ volatile(
            "addi  $6,$0,10000\n"
            "sync.p\n"
        "VTIPU_WAIT:\n"
            "bltz  $6,VTIPU_BREAK\n"
            "addi  $6,$6,-1\n"
            "bc0f  VTIPU_WAIT\n"
            "nop\n"
        "VTIPU_BREAK:\n"
            "nop\n"
        );
    }
    dmaStat &= ~(1 << id);
    DPUT_D_STAT(1 << id);
    return 0;
}

s32 vtIPU_syncDecode(vtIDEC_MOVIE *movie) {
    s32 i;
    sceIpuDmaEnv env;

    strcpy(_funcname, "vtIPU_syncDecode()");
    vtIPU_wait(movie, 3);
    if (movie->killFg) {
        movie->killFg = 0;
        return 0;
    }

    DPUT_IPU_CMD(0x40000020);
    strcpy(_funcname, "vtIPU_syncDecode() 2");
    if (vtIPU_Sync(0, _ipuTimeout)) {
        return -1;
    }
    if (movie->type != 1) {
        return 0;
    }

    for (i = movie->top[movie->frame_cnt] & 0xF; i >= 4; i -= 4) {
        DPUT_IPU_CMD(0x40000020);
        if (vtIPU_Sync(0, _ipuTimeout)) {
            return -1;
        }
        strcpy(_funcname, "vtIPU_syncDecode() 3");
    }

    if (i > 0) {
        DPUT_IPU_CMD(0x40000000 | i << 3);
        strcpy(_funcname, "vtIPU_syncDecode() 4");
        if (vtIPU_Sync(0, _ipuTimeout)) {
            return -1;
        }
    }

    return 0;
}

s32 vtIPU_VQ(vtIDEC_MOVIE *movie) {
    if (vtIPU_SetVQ(movie, movie->ipuClut)) {
        return -1;
    }

    sceIpuSync(0, 0);
    return vtIPU_VectorQuantization(movie);
}

s32 vtIPU_SetVQ(vtIDEC_MOVIE *movie, u16 *clut) {
    sceIpuDmaEnv env;

    DPUT_IPU_CTRL(0x40000000);
    sceIpuSync(0, 0);
    sceIpuStopDMA(&env);
    DPUT_IPU_CMD(0x00);
    sceIpuSync(0, 0);
    sceIpuRestartDMA(&env);
    vtIPU_wait(movie, 4);
    DPUT_D4_TADR(0x00);
    DPUT_D4_MADR(clut);
    DPUT_D4_QWC(2);
    DPUT_D4_CHCR(0x100);
    dmaStat |= 0x10;
    DPUT_IPU_CMD(0x60000000);
    return 0;
}

s32 vtIPU_VectorQuantization(vtIDEC_MOVIE *movie) {
    sceIpuDmaEnv env;

    DPUT_IPU_CTRL(0x40000000);
    sceIpuSync(0, 0);
    sceIpuStopDMA(&env);
    DPUT_IPU_CMD(0x00);
    sceIpuRestartDMA(&env);
    sceIpuSync(0, 0);
    vtIPU_wait(movie, 4);
    DPUT_D4_TADR(0x00);
    DPUT_D4_MADR(movie->cscBuff[movie->currentBufNo]);
    DPUT_D4_QWC((movie->mbx * movie->mby) << 10 >> 4);
    DPUT_D4_CHCR(0x100);
    dmaStat |= 0x10;
    vtIPU_wait(movie, 3);
    DPUT_D3_MADR(movie->vqBuff[movie->currentBufNo]);
    DPUT_D3_QWC((movie->mbx * movie->mby) << 7 >> 4);
    DPUT_D3_CHCR(0x100);
    dmaStat |= 0x8;
    DPUT_IPU_CMD(movie->mbx * movie->mby | 0x80000000);
    return 0;
}

s32 vtIPU_IDCT(/* s4 20 */ vtIDEC_MOVIE *movie) {
    /* 0x0(sp) */ sceIpuDmaEnv env;
    /* s0 16 */ u32 flag;
    /* fp 30 */ sceIpuRGB32 *prgb = movie->cscBuff[movie->currentBufNo];
    /* s6 22 */ sceIpuRAW16 *praw = movie->idctBuff[movie->currentBufNo];
    /* t2 10 */ u32 *ppix;
    /* t1 9 */ s16 *py;
    /* a1 5 */ s32 y;
    /* s5 21 */ s32 i;
    /* t3 11 */ s32 j;
    /* 0x30(sp) */ s32 len;
    /* s2 18 */ u32 skipBit;
    /* s1 17 */ u32 qsc;
    /* s3 19 */ struct { // 0x4
        /* 0x000:0 */ u32 first : 1;
        /* 0x000:1 */ u32 dcreset : 1;
        /* 0x000:2 */ u32 dt : 1;
        /* 0x000:3 */ u32 qsc : 1;
        /* 0x000:4 */ u32 tmp : 28;
    } isDecodeFg;
    /* a3 7 */ s32 cb1;
    /* v1 3 */ s32 cb2;
    /* a2 6 */ s32 cr1;
    /* a0 4 */ s32 cr2;
    /* a2 6 */ s32 r;
    /* a0 4 */ s32 g;
    /* a1 5 */ s32 b;

    strcpy(_funcname, "vtIPU_IDCT()");
    if (movie->frame_cnt >= movie->nframes) {
        movie->frame_cnt = 0;
    } else {
        movie->frame_cnt = (movie->frame_cnt + (movie->type == 1 ? movie->incnum : 1)) % movie->nframes;
    }

    movie->currentBufNo ^= 1;
    if (movie->type == 0) {
        return -1;
    }
    
    DPUT_IPU_CTRL(0x40000000);
    if (vtIPU_Sync(0, _ipuTimeout)) {
        return -1;
    }

    sceIpuStopDMA(&env);
    DPUT_IPU_CMD(0x00);
    sceIpuRestartDMA(&env);
    if (vtIPU_Sync(0, _ipuTimeout)) {
        return -1;
    }

    vtIPU_sendBsdataToSPR(movie, (u32)SPR_MEM);
    movie->bsData1Size += 19;
    movie->bsData1Size >>= 4;
    movie->bsData1Size <<= 4;
    vtIPU_wait(movie, 9);
    vtIPU_wait(movie, 4);

    DPUT_D4_TADR(0x00);
    DPUT_D4_MADR(movie->bsData1Addr & 0x0FFFFFFF | 0x80000000);
    DPUT_D4_QWC(movie->bsData1Size >> 4);
    DPUT_D4_CHCR(0x100);
    dmaStat |= 0x10;

    isDecodeFg.first = 1;
    len = movie->mbx * movie->mby;
    for (i = 0; i < len; i++) {
        if (DGET_IPU_CTRL() & 0x4000) {
            KL2_DEBUG_PRINT(("(vtIPU_IDCT) IPU ERROR\n"));
        }
        vtIPU_wait(movie, 3);
        FlushCache(0);
        DPUT_D3_MADR(praw);
        DPUT_D3_QWC(0x30);
        DPUT_D3_CHCR(0x100);
        dmaStat |= 0x8;

        if (isDecodeFg.first) {
            DPUT_IPU_CMD(0x40000000);
            if (vtIPU_Sync(0, _ipuTimeout)) {
                return -1;
            }

            flag = DGET_IPU_CMD();
            flag = (flag >> 24) & 0xFF;
            DPUT_IPU_CTRL(0x1000000 | (flag & 0xFB) << 16);
            if (vtIPU_Sync(0, _ipuTimeout)) {
                return -1;
            }

            DPUT_IPU_CMD(0x40000008);
            isDecodeFg.dt = flag & 0x4 ? 1 : 0;
            isDecodeFg.first = 0;
            isDecodeFg.dcreset = 1;
            skipBit = 0;
        } else {
            DPUT_IPU_CMD(0x40000000);
            isDecodeFg.dcreset = 0;
            skipBit = 1;
        }

        if (vtIPU_Sync(0, _ipuTimeout)) {
            return -1;
        }

        flag = DGET_IPU_CMD();
        KL2_DEBUG_PRINT(("MB flag = 0x%x\n", flag););
        if (flag >> skipBit & 1) {
            skipBit += 1;
            isDecodeFg.qsc = 0;
        } else {
            skipBit += 2;
            isDecodeFg.qsc = 1;
        }

        skipBit += isDecodeFg.dt;
        if (isDecodeFg.qsc) {
            qsc = flag >> skipBit;
            qsc &= 0x1F;
            skipBit += 5;
        } else {
            qsc = 0;
        }
    
        flag = isDecodeFg.dt;
        KL2_DEBUG_PRINT(("isDecodeFg.dt = %d isDecodeFg.qsc = %d qsc = 0x%x\n", flag, isDecodeFg.qsc, qsc));
        DPUT_IPU_CMD(0x28000000 | isDecodeFg.dcreset << 26 | flag << 25 | qsc << 16 | skipBit);
        if (vtIPU_Sync(0, _ipuTimeout)) {
            return -1;
        }

        KL2_DEBUG_PRINT(("raw[%d].y[%d] = 0x%x\n", i, 0, (u32)(movie->idctBuff[movie->currentBufNo] + i)));
        if (i >= 0) {
            vtIPU_wait(movie, 3);
            ppix = UNCACHED(prgb);
            py = UNCACHED(praw);
            for (j = 0; j < 256; j++, ppix++, py++) {
                cr1 = praw->cr[j] - 128;
                cb1 = praw->cb[j] - 128;
                cr2 = ((cr1 * 104) & ~0x3F) >> 6;
                cr1 = ((cr1 * 204) & ~0x3F) >> 6;
                cb2 = ((cb1 * 258) & ~0x3F) >> 6;
                cb1 = ((cb1 * 50) & ~0x3F) >> 6;

                y = *py;
                y = (((y - 16) * 149) & ~0x3F) >> 6;
                
                r = y + cr1;
                g = (y - cb1) - cr2;
                b = y + cb2;
                r = (r >> 1) + (r & 1);
                g = (g >> 1) + (g & 1);
                b = (b >> 1) + (b & 1);
                r = r > 0xFF ? 0xFF : r < 0 ? 0 : r;
                g = g > 0xFF ? 0xFF : g < 0 ? 0 : g;
                b = b > 0xFF ? 0xFF : b < 0 ? 0 : b;

                *ppix = r | g << 8 | b << 16 | 0x80000000;
            }

            prgb++;
            praw++;
        }
    }

    __asm__("sync");
    FlushCache(WRITEBACK_DCACHE);
    return 0;
}

void vtIPU_killDecode(vtIDEC_MOVIE *movie) {
    movie->killFg = 1;
}

void vtIPU_finish(vtIDEC_MOVIE *movie) {
    // Empty function
}

u128* vtIPU_mkPacketVIF(u128 *packet, vtIDEC_MOVIE *movie) {
    return vtIPU_mkDmaTagOfSendTexVIF(packet, movie->cscBuff[movie->currentBufNo], movie);
}

u128* vtIPU_mkDmaTagOfSendTex(u128 *dmaTag, sceIpuRGB32 *image, vtIDEC_MOVIE *movie) {
    u64 *p = (u64 *)dmaTag;
    s32 mbx;
    s32 mby;
    s32 i;
    s32 j;
    u64 size;
    u8 *pimage = (u8 *)image;

    *p = DMAcnt | 3;
    p++;
    p++;
    *p++ = SCE_GIF_SET_TAG(2, 1, 0, 0, 0, 1);
    *p++ = SCE_GIF_PACKED_AD;
    *p++ = SCE_GS_SET_BITBLTBUF(0, 0, SCE_GS_PSMCT32, movie->texbp, movie->texbw, SCE_GS_PSMCT32);
    *p++ = SCE_GS_BITBLTBUF;
    size = 16 * 16 * 4; // sizeof(sceIpuRGB32)
    *p++ = SCE_GS_SET_TRXREG(16, 16);
    *p++ = SCE_GS_TRXREG;

    mbx = movie->mbx;
    mby = movie->mby;
    for (j = 0; j < mby; j++) {
        for (i = 0; i < mbx; i++, pimage += size) {
            *p = DMAcnt | 4;
            p += 2;
            *p++ = SCE_GIF_SET_TAG(2, 1, 0, 0, SCE_GIF_PACKED, 1);
            *p++ = SCE_GIF_PACKED_AD;
            *p++ = SCE_GS_SET_TRXPOS(0, 0, i << 4, j << 4, 0);
            *p++ = SCE_GS_TRXPOS;
            *p++ = SCE_GS_SET_TRXDIR(0);
            *p++ = SCE_GS_TRXDIR;
            *p++ = SCE_GIF_SET_TAG(size >> 4, 1, 0, 0, SCE_GIF_IMAGE, 0);
            *p++ = 0;
            *p++ = DMAref | size >> 4 | ((u64)pimage & 0x0FFFFFFF) << 32; // IMPORTANT: must cast pimage to u64 rather than u32 > u64
            p++;
        }
    }

    *p = DMAend;
    p++;
    p++;
    return (u128 *)p;
}

u128* vtIPU_mkDmaTagOfSendTexVIF(u128 *dmaTag, sceIpuRGB32 *image, vtIDEC_MOVIE *movie) {
    kitDMAPACKET *packet = (kitDMAPACKET *)dmaTag;
    s32 mbx;
    s32 mby;
    s32 i;
    s32 j;
    u64 size;
    u8 *pimage = (u8 *)image;

    packet->ul[0] = DMAcnt | 3;
    packet->ui[2] = 0;
    packet->ui[3] = SCE_VIF1_SET_DIRECT(3, 0);
    packet++;
    packet->ul[0] = SCE_GIF_SET_TAG(2, 1, 0, 0, 0, 1);
    packet->ul[1] = SCE_GIF_PACKED_AD;
    packet++;
    packet->ul[1] = SCE_GS_BITBLTBUF;
    packet->ul[0] = SCE_GS_SET_BITBLTBUF(0, 0, SCE_GS_PSMCT32, movie->texbp, movie->texbw, SCE_GS_PSMCT32);
    packet++;
    size = 16 * 16 * 4; // sizeof(sceIpuRGB32)
    packet->ul[1] = SCE_GS_TRXREG;
    packet->ul[0] = SCE_GS_SET_TRXREG(16, 16);
    packet++;

    mbx = movie->mbx;
    mby = movie->mby;
    for (j = 0; j < mby; j++) {
        for (i = 0; i < mbx; i++, pimage += size) {
            packet->ul[0] = DMAcnt | 4;
            packet->ui[2] = 0;
            packet->ui[3] = SCE_VIF1_SET_DIRECT(4, 0);
            packet++;
            packet->ul[0] = SCE_GIF_SET_TAG(2, 1, 0, 0, SCE_GIF_PACKED, 1);
            packet->ul[1] = SCE_GIF_PACKED_AD;
            packet++;
            packet->ul[1] = SCE_GS_TRXPOS;
            packet->ul[0] = SCE_GS_SET_TRXPOS(0, 0, i << 4, j << 4, 0);
            packet++;
            packet->ul[1] = SCE_GS_TRXDIR;
            packet->ul[0] = SCE_GS_SET_TRXDIR(0);
            packet++;
            packet->ul[0] = SCE_GIF_SET_TAG(size >> 4, 1, 0, 0, SCE_GIF_IMAGE, 0);
            packet->ul[1] = 0;
            packet++;
            packet->ul[0] = DMAref | size >> 4 | (u64)pimage << 32;
            packet->ui[2] = 0;
            packet->ui[3] = SCE_VIF1_SET_DIRECT(size >> 4, 0);
            packet++;
        }
    }

    return (u128 *)packet;
}

u128* vtIPU_mkDmaTagOfSendINDX4VIF(/* a0 4 */ u128 *dmaTag, /* a1 5 */ sceIpuINDX4 *image, /* a2 6 */ vtIDEC_MOVIE *movie, /* a3 7 */ u32 vram) {
    /* t0 8 */ kitADDR_DATA *packet = (kitADDR_DATA *)dmaTag + 1;
    /* t6 14 */ s32 mbx;
    /* t7 15 */ s32 mby;
    /* a0 4 */ s32 i;
    /* a3 7 */ s32 j;
    /* s5 21 */ u64 size;
    /* a1 5 */ u8 *pimage = (u8 *)image;
    /* t1 9 */ kitADDR_DATA *pgiftag;
    /* v1 3 */ kitDMAPACKET *pdmatag;

    // packet = (kitADDR_DATA *)dmaTag;
    // packet++;
    // pdmatag = (kitDMAPACKET *)packet;
    // packet++;
    // pgiftag = packet++;

    pdmatag = (kitDMAPACKET *)dmaTag++;
    packet = (kitADDR_DATA *)dmaTag++;
    pgiftag = packet++;

    packet->data = SCE_GS_SET_BITBLTBUF(0, 0, SCE_GS_PSMCT32, vram, movie->texbw, SCE_GS_PSMT4);
    packet->addr = SCE_GS_BITBLTBUF;
    packet++;
    size = sizeof(sceIpuINDX4);
    packet->data = SCE_GS_SET_TRXREG(16, 16);
    packet->addr = SCE_GS_TRXREG;
    packet++;
    pgiftag->data = SCE_GIF_SET_TAG(2, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1);
    pgiftag->addr = SCE_GIF_PACKED_AD;

    pdmatag->ul[0] = DMAcnt | 3;
    pdmatag->ui[2] = 0;
    pdmatag->ui[3] = SCE_VIF1_SET_DIRECT(3, 0);

    mbx = movie->mbx;
    mby = movie->mby;
    for (j = 0; j < mby; j++) {
        for (i = 0; i < mbx; i++, pimage += size) {
            pdmatag = (kitDMAPACKET *)packet++;
            pgiftag = (kitADDR_DATA *)packet++;

            packet->addr = SCE_GS_TRXPOS;
            packet->data = SCE_GS_SET_TRXPOS(0, 0, i << 4, j << 4, 0);
            packet++;
            packet->addr = SCE_GS_TRXDIR;
            packet->data = SCE_GS_SET_TRXDIR(0);
            packet++;
            pgiftag->data = SCE_GIF_SET_TAG(2, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_PACKED, 1);
            pgiftag->addr = SCE_GIF_PACKED_AD;

            pgiftag = (kitADDR_DATA *)packet++;
            pgiftag->data = SCE_GIF_SET_TAG(size >> 4, SCE_GS_TRUE, SCE_GS_FALSE, 0, SCE_GIF_IMAGE, 0);
            pgiftag->addr = 0;

            pdmatag->ul[0] = DMAcnt | 4;
            pdmatag->ui[2] = 0;
            pdmatag->ui[3] = SCE_VIF1_SET_DIRECT(4, 0);

            pdmatag = (kitDMAPACKET *)packet++;
            pdmatag->ul[0] = DMAref | size >> 4 | (u64)pimage << 32;
            pdmatag->ui[2] = 0;
            pdmatag->ui[3] = SCE_VIF1_SET_DIRECT(size >> 4, 0);
        }
    }

    return (u128 *)packet;
}

u128* vtIPU_mkTex0(u128 *dmaTag, vtIDEC_MOVIE *movie, s32 context) {
    kitADDR_DATA *packet = (kitADDR_DATA *)dmaTag;
    packet->data = 0;
    packet->addr = SCE_GS_TEXFLUSH;
    packet++;
    packet->data = SCE_GS_SET_TEX0(movie->texbp, movie->texbw, SCE_GS_PSMCT32, movie->tw, movie->th, SCE_GS_TRUE, SCE_GS_MODULATE, 0, 0, SCE_GS_FALSE, 0, 0);
    packet->addr = context == 0 ? SCE_GS_TEX0_1 : SCE_GS_TEX0_2;
    packet++;
    return (u128 *)packet;
}

u128* vtIPU_mkPacketForVQ(u128 *packet, vtIDEC_MOVIE *movie, s32 context) {
    packet = vtIPU_sendClut(packet, movie->gsClut, movie->cbp, movie->cpsm, movie->csm, movie->csa, movie->cld, context);
    packet = vtIPU_mkDmaTagOfSendINDX4VIF(packet, movie->vqBuff[movie->currentBufNo], movie, movie->texbp);
    return packet;
}

u128* vtIPU_mkTex0ForVQ(u128 *dmaTag, vtIDEC_MOVIE *movie, s32 context) {
    kitADDR_DATA *packet = (kitADDR_DATA *)dmaTag;
    packet->data = 0;
    packet->addr = SCE_GS_TEXFLUSH;
    packet++;
    packet->data = SCE_GS_SET_TEX0(movie->texbp, movie->texbw, SCE_GS_PSMT4, movie->tw, movie->th, SCE_GS_TRUE, SCE_GS_MODULATE, movie->cbp, movie->cpsm, movie->csm, movie->csa, movie->cld);
    packet->addr = context == 0 ? SCE_GS_TEX0_1 : SCE_GS_TEX0_2;
    packet++;
    return (u128 *)packet;
}

u128* vtIPU_sendClut(/* a0 4 */ u128 *packet, /* a1 5 */ u8 *clut, /* a2 6 */ u32 cbp, /* a3 7 */ u32 cpsm, /* t0 8 */ u32 csm, /* t1 9 */ u32 csa, /* t2 10 */ u32 cld, /* t3 11 */ s32 context) {
    /* t5 13 */ kitDMAPACKET *pdmatag = (kitDMAPACKET *)packet;

    
}

// /* 001f76e0 00000074 */ static u_long128* mkDmaTagToIPU_SCE(/* a0 4 */ u_long128 *tags, /* a1 5 */ unsigned char *data, /* a2 6 */ int datasize) {
//     /* a0 4 */ int chunkSize;
//     /* a3 7 */ long unsigned int *p;
// }

// /* 001f7758 000000d4 */ int vtIPU_readDataSCE(/* s2 18 */ char *file, /* s1 17 */ vtIDEC_MOVIE *movie) {
//     /* s0 16 */ int fd;
// }