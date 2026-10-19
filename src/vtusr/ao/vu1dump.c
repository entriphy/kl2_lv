#include "vtusr/ao/vu1dump.h"

#define ANSI_CTRL_START "\x1B"
#define ANSI_RESET "\x1B[m"
#define ANSI_BOLD "\x1B[1m"
#define ANSI_INVERT "\x1B[7m"
#define ANSI_FG_WHITE "\x1B[37m"
#define ANSI_BG_BLACK "\x1B[40m"
#define ANSI_BG_BLACK_IDK "\x1B""40m"
#define ANSI_BG_RED "\x1B[41m"
#define ANSI_BG_BLUE "\x1B[44m"

void print_vu1_Mem() {
    s32 i;
    u32 *vu1mem = (u32 *)VU1_MEM;

    KL2_DEBUG_PRINT((ANSI_BG_RED "V U 1  M e m o r y" ANSI_RESET "\n"));
    for (i = 0; i < 0x2600; i += 0x10, vu1mem += 4) {
        if (!(i & 0xFFF)) {
            KL2_DEBUG_PRINT((ANSI_BOLD "        [128   96 95    64 63    32 31     0]" ANSI_RESET "\n"));
        }
        KL2_DEBUG_PRINT((ANSI_BOLD "0x%04x" ANSI_RESET ": [%08x %08x %08x %08x]\n", i, vu1mem[3], vu1mem[2], vu1mem[1], vu1mem[0]));
    }
    KL2_DEBUG_PRINT(("\n"));
}

void print_vu1_Micro() {
    s32 i;
    u32 *vu1micro = (u32 *)VU1_MICRO;

    KL2_DEBUG_PRINT((ANSI_BG_BLUE "V U 1  M i c r o M e m o r y" ANSI_RESET "\n"));
    for (i = 0; i < 0x250; i += 0x08, vu1micro += 2) {
        if (!(i & 0xFFF)) {
            KL2_DEBUG_PRINT((ANSI_BOLD "        [63    32 31     0]" ANSI_RESET "\n"));
        }

        if (*vu1micro == 0x800A06BC) { // XTOP vi10
            KL2_DEBUG_PRINT((ANSI_BOLD "0x%04x" ANSI_RESET ": [" ANSI_FG_WHITE ANSI_BG_BLACK_IDK "%08x %08x" ANSI_RESET "]\n", i, vu1micro[1], vu1micro[0]));
        }
        
    }
    KL2_DEBUG_PRINT(("\n"));
}

void print_vu1_FloatRegister() {
    s32 i;
    sceVu0FVECTOR vf;
    
    KL2_DEBUG_PRINT((ANSI_BG_BLUE "V U 1  F l o t  R e g i s t e r" ANSI_RESET "\n")); // flot
    KL2_DEBUG_PRINT((ANSI_BOLD "         [W        Z        Y        X       ]" ANSI_RESET "\n"));

    __asm__ volatile(
        "li $2, %0\n"
        "ctc2 $2, $vi1\n"
    : : "i" (0x400));

    for (i = 0; i < 32; i++) {
        __asm__ volatile("vlqi.xyzw $vf2, ($vi1++)\n");
        __asm__ volatile("sqc2      $vf2, 0x0(%0)\n" : : "r" (vf));
        KL2_DEBUG_PRINT((ANSI_BOLD "VF(i)%02d" ANSI_RESET ": [" ANSI_INVERT "%08x %08x %08x %08x" ANSI_RESET "]\n", i, ((s32 *)vf)[3], ((s32 *)vf)[2], ((s32 *)vf)[1], ((s32 *)vf)[0]));
        KL2_DEBUG_PRINT((ANSI_BOLD "  (f)%02d" ANSI_RESET ": [%f %f %f %f]\n", i, vf[3], vf[2], vf[1], vf[0]));
    }
    KL2_DEBUG_PRINT(("\n"));
}

void print_vu1_IntRegister() {
    s32 i;
    sceVu0IVECTOR vi;

    KL2_DEBUG_PRINT((ANSI_BG_BLUE "V U 1  I n t e g e r  R e g i s t e r" ANSI_RESET "\n"));
    KL2_DEBUG_PRINT((ANSI_BOLD "         [15      ]" ANSI_RESET "\n"));

    __asm__ volatile(
        "li $2, %0\n"
        "ctc2 $2, $vi1\n"
    : : "i" (0x420));

    for (i = 0; i < 16; i++) {
        __asm__ volatile("vlqi.xyzw $vf2, ($vi1++)\n");
        __asm__ volatile("sqc2      $vf2, 0x0(%0)\n" : : "r" (vi));
        KL2_DEBUG_PRINT((ANSI_BOLD "  VI%02d " ANSI_RESET ": [%08x]\n", i, vi[0]));
    }
    
    KL2_DEBUG_PRINT(("\n"));
}

void print_vu1_ControlRegister() {
    s32 i;
    char c[9];
    sceVu0IVECTOR vi;

    KL2_DEBUG_PRINT((ANSI_BG_BLUE "V U 1  C o n t r o l  R e g i s t e r" ANSI_RESET "\n"));
    KL2_DEBUG_PRINT((ANSI_BOLD "          [31       15      ]" ANSI_RESET "\n"));

    __asm__ volatile(
        "li $2, %0\n"
        "ctc2 $2, $vi1\n"
    : : "i" (0x430));

    for (i = 0; i < 16; i++) {
        __asm__ volatile("vlqi.xyzw $vf2, ($vi1++)\n");
        __asm__ volatile("sqc2      $vf2, 0x0(%0)\n" : : "r" (vi));
        
        switch (i) {
            case 0:
                strcpy(c, "STATUS  ");
                break;
            case 1:
                strcpy(c, "MAC     ");
                break;
            case 2:
                strcpy(c, "CLIPING ");
                break;
            case 4:
                strcpy(c, "R Reg   ");
                break;
            case 5:
                strcpy(c, "I Reg   ");
                break;
            case 6:
                strcpy(c, "Q Reg   ");
                break;
            case 7:
                strcpy(c, "P Reg   ");
                break;
            case 10:
                strcpy(c, "TPC     ");
                break;
            default:
                strcpy(c, "reserved");
                break;
        }

        KL2_DEBUG_PRINT((ANSI_BOLD "%s" ANSI_RESET ": [%08x %08x]\n", c, vi[1], vi[0]));
    }

    KL2_DEBUG_PRINT(("\n"));
}

void print_pkt(u32 *pos, s32 num) {
    s32 i;
    u32 *p = pos;

    for (i = 0; i < num; i++) {
        KL2_DEBUG_PRINT(("%2d: %08lx %08lx %08lx %08lx\n", i, (u64)*p++, (u64)*p++, (u64)*p++, (u64)*p++));
    }

    KL2_DEBUG_PRINT(("\n"));
}