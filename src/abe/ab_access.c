#include "abe/ab_access.h"

extern GAME_WORK GameGbl;

OBJWORK* abGetKlonoa(s32 player) {
    return GameGbl.klonoa;
}

OBJWORK* abGetMochifuku(s32 player) {
    return ((HERO_WORK *)GameGbl.klonoa->work)->mochifuku;
}
