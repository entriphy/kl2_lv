#ifndef __AO_VU1_DUMP_H
#define __AO_VU1_DUMP_H

#include "common.h"

extern void print_vu1_Mem();
extern void print_vu1_Micro();
extern void print_vu1_FloatRegister();
extern void print_vu1_IntRegister();
extern void print_vu1_ControlRegister();
extern void print_pkt(u32 *pos, s32 num);

#endif