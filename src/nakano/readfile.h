#ifndef __NK_READFILE_H
#define __NK_READFILE_H

#include "common.h"

extern s32 read_file(char *name, char *buff);
extern qword* read_file128(char *name, qword *buff);

#endif
