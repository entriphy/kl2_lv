#ifndef __HR_PRM_H
#define __HR_PRM_H

#include "common.h"
#include "sfx.h"
#include "harada/hr_pcam.h"

typedef struct { // 0x3d0
    /* 0x000 */ PCAMSC pos;
    /* 0x050 */ PCAMSC rot;
    /* 0x0a0 */ sceVu0FVECTOR nlight[3];
    /* 0x0d0 */ PCAMSC nlw[3];
    /* 0x1c0 */ PCAMSC lcolor[3];
    /* 0x2b0 */ sceVu0FVECTOR ambi;
    /* 0x2c0 */ sceVu0FMATRIX NormalLight;
    /* 0x300 */ sceVu0FMATRIX LightColor;
    /* 0x340 */ sceVu0FVECTOR rtpos;
    /* 0x350 */ sceVu0FVECTOR rtrot;
    /* 0x360 */ s32 flag;
    /* 0x364 */ s32 *read;
    /* 0x368 */ s32 *ret;
    /* 0x36c */ tOBJECT *hObj;
    /* 0x370 */ u16 motno;
    /* 0x372 */ u16 motlp;
    /* 0x374 */ u16 motret;
    /* 0x376 */ u16 motlpi;
    /* 0x378 */ s16 id;
    /* 0x37a */ s16 chr;
    /* 0x37c */ s16 fhm;
    /* 0x37e */ s16 time;
    /* 0x380 */ s32 getft;
    /* 0x384 */ s32 lightno;
    /* 0x388 */ s32 efc;
    /* 0x38c */ s32 *mem;
    /* 0x390    f32 shady; */
    /* 0x390 */ s32 sevag; // ?
    /* 0x394 */ s32 pad0;
    /* 0x398 */ s16 loop[2];
    /* 0x39c */ s16 pad2;
    /* 0x39e */ s16 pad3;
    /* 0x3a0 */ PCAMSR route;
    /* 0x3c0 */ RT_WRK rtw;
} HR_CALL;

typedef struct { // 0x10
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 a;
    /* 0x4 */ u8 ma;
    /* 0x5 */ u8 pad0;
    /* 0x6 */ u8 pad1;
    /* 0x7 */ u8 pad2;
    /* 0x8 */ s32 flag;
    /* 0xc */ u16 time;
    /* 0xe */ u16 count;
} HR_FADE;

typedef struct { // 0x20
    /* 0x00 */ s32 id;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0c */ f32 z;
    /* 0x10 */ f32 rx;
    /* 0x14 */ f32 ry;
    /* 0x18 */ f32 rz;
    /* 0x1c */ f32 pad0;
} HR_ECONT;

typedef struct { // 0x20
    /* 0x00 */ s32 trg;
    /* 0x04 */ s32 oldtrg;
    /* 0x08 */ s32 lvl;
    /* 0x0c */ s32 oldlvl;
    /* 0x10 */ s32 open;
    /* 0x14 */ s32 pad0;
    /* 0x18 */ s32 pad1;
    /* 0x1c */ s32 pad2;
} HR_PKEY;

typedef struct { // 0x50
    /* 0x00 */ PCAMSR pit;
    /* 0x20 */ PCAMSL vol;
    /* 0x40 */ s32 flag;
    /* 0x44 */ s32 id;
    /* 0x48 */ s32 pad0;
    /* 0x4c */ u32 splt;
} HR_PTSE;

typedef struct { // 0x4
    /* 0x0 */ u16 code;
    /* 0x2 */ s16 ss0;
} PT32A;

typedef struct { // 0x4
    /* 0x0 */ u16 code;
    /* 0x2 */ u16 us0;
} PT32B;

typedef struct { // 0x8
    /* 0x0 */ u16 code;
    /* 0x2 */ s16 ss0;
    /* 0x4 */ s16 ss1;
    /* 0x6 */ s16 ss2;
} PT64A;

typedef struct { // 0x8
    /* 0x0 */ u16 code;
    /* 0x2 */ u16 us0;
    /* 0x4 */ s32 si0;
} PT64B;

typedef struct { // 0x8
    /* 0x0 */ u16 code;
    /* 0x2 */ u16 us0;
    /* 0x4 */ f32 f0;
} PT64C;

typedef struct { // 0x8
    /* 0x0 */ u16 code;
    /* 0x2 */ u8 uc0;
    /* 0x3 */ u8 uc1;
    /* 0x4 */ s32 si0;
} PT64D;

typedef struct { // 0x8
    /* 0x0 */ u16 code;
    /* 0x2 */ u16 us0;
    /* 0x4 */ u8 uc0;
    /* 0x5 */ u8 uc1;
    /* 0x6 */ u8 uc2;
    /* 0x7 */ u8 uc3;
} PT64E;

typedef struct { // 0x8
    /* 0x0 */ u16 code;
    /* 0x2 */ u8 uc0;
    /* 0x3 */ u8 uc1;
    /* 0x4 */ f32 f0;
} PT64F;

typedef struct { // 0xc
    /* 0x0 */ u16 code;
    /* 0x2 */ u16 us0;
    /* 0x4 */ u16 us1;
    /* 0x6 */ s16 ss0;
    /* 0x8 */ u32 ui0;
} PT96A;

typedef struct { // 0xc
    /* 0x0 */ u16 code;
    /* 0x2 */ u16 us0;
    /* 0x4 */ u16 us1;
    /* 0x6 */ s16 ss0;
    /* 0x8 */ f32 f0;
} PT96B;

typedef struct { // 0xc
    /* 0x0 */ u16 code;
    /* 0x2 */ u16 us0;
    /* 0x4 */ u32 ui0;
    /* 0x8 */ u32 ui1;
} PT96C;

typedef struct { // 0xc
    /* 0x0 */ u16 code;
    /* 0x2 */ u16 us0;
    /* 0x4 */ s32 si0;
    /* 0x8 */ f32 f0;
} PT96D;

typedef struct { // 0xc
    /* 0x0 */ u16 code;
    /* 0x2 */ u8 uc0;
    /* 0x3 */ u8 uc1;
    /* 0x4 */ s32 si0;
    /* 0x8 */ u32 ui0;
} PT96E;

typedef struct { // 0xc
    /* 0x0 */ u16 code;
    /* 0x2 */ u8 uc0;
    /* 0x3 */ u8 uc1;
    /* 0x4 */ f32 f0;
    /* 0x8 */ u32 ui0;
} PT96F;

typedef struct { // 0x10
    /* 0x0 */ u16 code;
    /* 0x2 */ s16 ss0;
    /* 0x4 */ f32 f0;
    /* 0x8 */ f32 f1;
    /* 0xc */ f32 f2;
} PT128A;

typedef struct { // 0x10
    /* 0x0 */ u16 code;
    /* 0x2 */ u8 uc0;
    /* 0x3 */ u8 uc1;
    /* 0x4 */ f32 f0;
    /* 0x8 */ f32 f1;
    /* 0xc */ f32 f2;
} PT128B;

typedef struct { // 0x10
    /* 0x0 */ u16 code;
    /* 0x2 */ u16 us0;
    /* 0x4 */ u16 us1;
    /* 0x6 */ s16 ss0;
    /* 0x8 */ u32 ui0;
    /* 0xc */ s16 ss1;
    /* 0xe */ s16 ss2;
} PT128C;

typedef struct { // 0x14
    /* 0x00 */ u16 code;
    /* 0x02 */ u8 uc0;
    /* 0x03 */ u8 uc1;
    /* 0x04 */ f32 f0;
    /* 0x08 */ f32 f1;
    /* 0x0c */ f32 f2;
    /* 0x10 */ s16 ss0;
    /* 0x12 */ s16 ss1;
} PT160A;

typedef struct { // 0x40
    /* 0x00 */ s16 time;
    /* 0x02 */ s16 wtime;
    /* 0x04 */ s32 dcnt;
    /* 0x08 */ u16 *dtop;
    /* 0x0c */ u16 *page;
    /* 0x10 */ u16 *read;
    /* 0x14 */ u16 *next;
    /* 0x18 */ s32 flag;
    /* 0x1c */ s32 mode;
    /* 0x20 */ s32 count;
    /* 0x24 */ u32 *font;
    /* 0x28 */ s32 stop;
    /* 0x2c */ s16 cntv;
    /* 0x2e */ s16 hasv;
    /* 0x30 */ u32 *mema;
    /* 0x34 */ s32 acnt;
    /* 0x38 */ s32 skipcnt;
    /* 0x3c */ s32 pad0;
} HRPMOJI;

typedef struct { // 0x20
    /* 0x00 */ s32 tex0[4];
    /* 0x10 */ s32 flag;
    /* 0x14 */ u32 *gms;
    /* 0x18 */ s32 pad0;
    /* 0x1c */ s32 pad1;
} HRPMWAKU;

typedef struct { // 0x10
    /* 0x0 */ HR_CALL *ca;
    /* 0x4 */ u16 *ptr;
    /* 0x8 */ s16 flag;
    /* 0xa */ s16 time;
    /* 0xc */ s16 alpha;
    /* 0xe */ s16 count;
} HRMESP;

typedef struct {
    sceVu0FMATRIX wmat;
    HR_CALL sys;
    HR_FADE fade;
    HR_ECONT econ[8];
    HR_PKEY key;
    HR_PTSE se[4];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    s16 klov;
    s16 kloy;
    s32 klomc;
    s16 klono;
    s16 ecount0; // 0x68E
    s32 flag; // 0x690
    s32 nflag;
    PT96A *flagptr[4];
    s32 ncall;
    HR_CALL *call; // 0x6AC
    PCAMS *cam; // 0x6B0
    HR_CALL *posc; // 0x6B4
    HR_CALL *intec; // 0x6B8
    s32 *model; // 0x6BC
    HRPMOJI *pmes; // 0x6C0
    HRPMWAKU *waku; // 0x6C4
    OBJWORK *efc; // 0x6C8
    s16 rtno;
    s16 oksw;
    s32 rtmc;
    s32 yuka;
    s32 cntvc;
    s32 *addrvc;
    s32 idvc;
    s32 cntlip;
    u16 *addrlip;
    s16 dckcnt;
    s16 skipcnt;
    s16 ncVi;
    s16 ncSc;
    s16 reqbgm; // 0x6F4
    s16 mircnt;
    HRMESP *mesp;
} HR_PSYS;

typedef struct { // 0x8
    /* 0x0 */ HR_CALL *ca;
    /* 0x4 */ s32 no;
} HPVSEL;

typedef enum {
    PTEFC_NON = 0,
    PT0100_LTBALL = 1,
    PT0100_RINGLT = 2,
    PT0104_RINGOUT = 3,
    PT0706_SWON = 4,
    PT0706_SWOFF = 5,
    PT0706_SMOKE = 6,
    PT0706_JOUKI = 7,
    PT0706_LTOFF0 = 8,
    PT0706_LTOFF1 = 9,
    PT0706_LTOFF2 = 10,
    PT0706_AWAN = 11,
    PT0706_AWAB = 12,
    PT0706_AWAN1 = 13,
    PT0706_AWAB1 = 14,
    PT0706_AWAN2 = 15,
    PT0706_AWAB2 = 16,
    PT4002_ZANZ = 17,
    PT4002_ENGI = 18,
    PTOPEN_HIKA0 = 19,
    PTOPEN_HIKA1 = 20,
    PTOPEN_HIKA2 = 21,
    PTOPEN_HIKA3 = 22,
    PT0104_KANE = 23,
    PT0207_LIGHT = 24,
    PT0207_HANE = 25,
    PT2100_SMOKE = 26,
    PT2100_BOSS0 = 27,
    PT2100_BOSS1 = 28,
    PT2100_KDAMA = 29,
    PT2100_ELEM = 30,
    PT040A_SMOKE = 31,
    PT4004_SPAK = 32,
    PT4004_FIRE = 33,
    PT4004_SMOKE = 34,
    PT4001_ECOL0 = 35,
    PT4001_ECOL1 = 36,
    PT4001_ECOL2 = 37,
    PT4001_ECOL3 = 38,
    PT1306_RSHOT = 39,
    PT1306_KIRA = 40,
    PT1306_HAKK = 41,
    PT1305_HIKW = 42,
    PT1305_SITW = 43,
    PT1400_YURA = 44,
    PT2600_FLUSH0 = 45,
    PT2600_FLUSH1 = 46,
    PT2600_FLUSH2 = 47,
    PT2600_FLUSH3 = 48,
    PT2600_BFOG = 49,
    PT1404_MOYA = 50,
    PT1505_BAKUH = 51,
    PT1505_SMOKE = 52,
    PT1500_SMOKE = 53,
    PT2700_POWUP = 54,
    PT2700_BARI = 55,
    PT2700_FUJN = 56,
    PTEND_HAMON = 57,
    PTEND_KIER = 58,
    PTEND_ASAHI = 59,
    PT2300_BOSS0 = 60,
    PTOPEN_RAKKA = 61,
    PT1111_MIRR = 62,
    PT1111_MIRRF = 63,
    PT4004_AWA = 64,
    PT2301_BOSS1 = 65,
    PT2301_BOSS2 = 66,
    PT2301_REOSHOT = 67,
    PT1306_HANET = 68,
    PT1306_HANEH = 69,
    PT1502_BAKUH = 70,
    PTEFC_NUM = 71
} PTEFC;

extern s32* pt_al_data(HR_CALL *ca, s16 ptr);
extern s32* pt_al_dataB(s32 *base, s16 ptr);
extern void hr_pcall_rtinit(HR_CALL *ca);
extern HR_CALL* hr_pcall_search(HR_PSYS *ps, HR_CALL *call);
extern HR_CALL* hr_id_search(HR_PSYS *ps, s16 id);
extern HR_CALL* hr_pfg_search(HR_PSYS *ps, s32 flag);
extern s32 hr_efc_why(s32 id);
extern void hr_call_efcdel(HR_CALL *ca, HR_PSYS *ps);
extern void hr_call_efcdelE(HR_PSYS *ps, s32 id);
extern void hr_call_efcon(HR_CALL *ca, HR_PSYS *ps, s32 id, s32 cmd);
extern void hr_callbuff_init(HR_PSYS *ps, s32 fg);
extern void hr_rt_posrot(HR_CALL *ca);
extern void pt_set_rtpos(HR_CALL *ca, s32 si0, u16 us0);
extern void pt_get_routeK(HR_CALL *ca);
extern void hr_psys_init(HR_PSYS *ps, s32 *addr, PCAMS *cam, s32 *addrm, HRPMOJI *pmes, HRPMWAKU *waku);
extern void hr_seloop_on(HR_PTSE *se, u32 splt, f32 *pos);
extern void hr_seloop_off(HR_PTSE *se, u32 splt);
extern HR_PTSE* hr_seloop_search(HR_PSYS *ps, u32 splt);
extern void pt_set_mesp(HR_CALL *ca, HR_PSYS *ps, u16 *addr, s16 time);
extern void pt_del_mesp(HR_CALL *ca, HR_PSYS *ps, u16 *addr, s16 time);
extern s32 hr_pt_checkExit(HR_PSYS *ps);
extern s32 hr_psys_exit(HR_PSYS *ps);
extern void hr_pt_getpos(HR_CALL *ca, sceVu0FVECTOR *v);
extern void hr_pt_getrot(HR_CALL *ca, sceVu0FVECTOR *v);
extern void hr_pt_getrotD(HR_CALL *ca, sceVu0FVECTOR *v);
extern s32 hr_pcall_read(HR_CALL *ca, HR_PSYS *ps);
extern void hr_check_time_move(PCAMSC *pcc);
extern s32 hr_check_time_moveRT(PCAMSR *rt);
extern s32 hr_check_time_moveL(PCAMSL *len);
extern void hr_efc_ofs(HR_CALL *ca, s32 id);
extern void hr_call_efcworkDeb(HR_CALL *ca, HR_PSYS *ps);
extern void hr_pcall_mkm(sceVu0FVECTOR pos, sceVu0FVECTOR rot, sceVu0FMATRIX m);
extern void hr_pt_light(HR_CALL *ca);
extern void hr_pt_motion(HR_CALL *ca);
extern void hr_pt_motionS(HOT *hObj);
extern void hr_pt_motionL(HOT *hObj, sceVu0FMATRIX m, sceVu0FVECTOR nlight, sceVu0FVECTOR lcolor);
extern void hr_psys_motdraw(HR_PSYS *ps, s32 pause);
extern void hr_ptmir_drawMain(HR_PSYS *ps);
extern void hr_pkey_init(HR_PKEY *key);
extern void hr_pkey_trg(HR_PKEY *key, s32 trg);
extern void hr_pkey_lvl(HR_PKEY *key, s32 lvl);
extern void hr_loopse_work(HR_PSYS *ps);
extern void hr_psys_work(HR_PSYS *ps);
extern void hr_ptlips_stop(HR_PSYS *ps);
extern void pt_set_skip(HR_PSYS *ps);
extern void pt_set_skip2(HR_PSYS *ps);
extern void pt_set_exit(HR_PSYS *ps, s16 count);
extern s32 pt_flagj_P(u32 id);
extern s32 hr_strt_check(PT96A *p, u16 no, u32 mc, s32 flag);
extern void hr_ptvoice_call(HR_PSYS *ps, HRPMOJI *pmes);
extern void hr_ptvoice_stop(HR_PSYS *ps, HRPMOJI *pmes);
extern void hr_psys_debugMVP(HPVSEL *pcsel, s32 pause);
extern void hr_psys_debug(HR_PSYS *ps, s32 menu, HPVSEL *pcsel, PCAMS *pcam);
extern void hr_psys_debugP(HR_PSYS *ps, s32 pause);

#endif
