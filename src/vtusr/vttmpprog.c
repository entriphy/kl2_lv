#include "vtusr/vttmpprog.h"

// TODO: remove
extern u64 OkGetTex0(s32 index);

void vtLoadVisionData(vtDataPtr *data, u32 vision) {
	char movie_name[64];
	char wave_name[64];
	char spray_name[64];
	char tmp_char[32];
	u128 *buf_ptr;
	char tmp_name[64];
	s32 i;
    s32 var_s4 = vision >> 8 & 0xFF;
    s32 var_s3 = vision & 0xFF;

    strcpy(movie_name, "host0:./debugdata/vtdata/");
    sprintf(tmp_char, "data/");
    strcat(movie_name, tmp_char);
    strcpy(wave_name, movie_name);
    strcpy(spray_name, movie_name);
    strcat(movie_name, "movie");
    strcat(wave_name, "wave");
    strcat(spray_name, "spray");
    sprintf(tmp_char, "%02x%02x", var_s4, var_s3);
    strcat(movie_name, tmp_char);
    strcat(wave_name, tmp_char);
    strcat(spray_name, tmp_char);
    strcat(wave_name, ".wdt");
    strcat(spray_name, ".sdt");
    printf("MOVIE FILE %s\n", movie_name);
    printf("WAVE  FILE %s\n", wave_name);
    printf("SPRAY  FILE %s\n", spray_name); // extra space lol

    buf_ptr = vtFileRead(wave_name);
    if (buf_ptr == NULL) {
        data->wave_data_buf = NULL;
    } else {
        data->wave_data_buf = buf_ptr;
    }

    buf_ptr = vtFileRead(spray_name);
    if (buf_ptr == NULL) {
        data->spray_data_buf = NULL;
    } else {
        data->spray_data_buf = buf_ptr;
    }

    for (i = 0; i < 8; i++) {
        sprintf(tmp_name, "%s%c.ipu", movie_name, i + 65);
        printf("MOVIE FILE %s\n", tmp_name);

        buf_ptr = vtFileRead(tmp_name);
        if (buf_ptr == NULL) {
            data->movie_data_buf[i] = NULL;
        } else {
            data->movie_data_buf[i] = buf_ptr;
        }
    }
}

void vtLoadFixTexture(vtDataPtr *data) {
	u128 tmp[2048];

    ((u64 *)data->tex0)[0] = 0;
    ((u64 *)data->tex0)[1] = 0;

    if (GameGbl.vision == KL2_VISION(1, 0) || GameGbl.vision == KL2_VISION(1, 1) || GameGbl.vision == KL2_VISION(1, 2) || GameGbl.vision == KL2_VISION(1, 4)) {
        ((u64 *)data->tex0)[0] = OkGetTex0(OkSendTex("host0:debugdata/vtdata/gim/wave1.gim", tmp));
        ((u64 *)data->tex0)[1] = OkGetTex0(OkSendTex("host0:debugdata/vtdata/gim/wave2.gim", tmp));
        ((u64 *)data->tex0)[2] = OkGetTex0(OkSendTex("host0:debugdata/vtdata/gim/wave3.gim", tmp));
    }

    if (GameGbl.vision == KL2_VISION(1, 0) || GameGbl.vision == KL2_VISION(1, 2)) {
        ((u64 *)data->tex0)[3] = OkGetTex0(OkSendTex("host0:debugdata/vtdata/gim/spray.gim", tmp));
    }
}