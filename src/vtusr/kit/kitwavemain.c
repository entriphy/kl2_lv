#include "vtusr/kit/kitwavemain.h"
#include "okanoyo/okio.h"
#include "vtusr/kit/kitwavevuprog.h"
#include "vtusr/vtwavemain.h"

kitWaveStruct* kitWaveInit(vtDataPtr *data) {
    kitWaveStruct *env;
    kitWaveParam *param;
    s32 i;
    char tmp;
    s32 status;

    env = getBuff(1, sizeof(kitWaveStruct), &tmp, &status);
    memset(env, 0, sizeof(kitWaveStruct));
    kitInitWaveTable(env->table);
    env->param_num = *(u32 *)data->wave_data_buf;
    data->wave_data_buf += 0x10; // incrementing a void pointer, undefined behavior
    
    for (i = 0, param = data->wave_data_buf; i < env->param_num; i++) {
        env->param[i] = param++;
        kitScreenEnvInitialize(&env->screenenv[i], env->param[i]);
    }

    data->tex0[0].TFX = SCE_GS_MODULATE;
    data->tex0[0].TCC = SCE_GS_TRUE;
    data->tex0[1].TFX = SCE_GS_DECAL;
    data->tex0[1].TCC = SCE_GS_TRUE;
    data->tex0[2].TFX = SCE_GS_MODULATE;
    data->tex0[2].TCC = SCE_GS_TRUE;
    env->tex0[0] = *(u64 *)&data->tex0[0];
    env->tex0[1] = *(u64 *)&data->tex0[1];
    env->tex0[2] = *(u64 *)&data->tex0[2];
    env->tex_ajust_x = 0;
    env->tex_ajust_z = 0;

    return env;
}

u128* kitExecWave(u128 *tmp) {
    sceVu0FMATRIX m;
    s32 i;
    s32 add_tex_flag = 0;

    for (i = 0; i < vtWaveGlobal.kitstruct->param_num; i++) {
        if (vtWaveGlobal.kitstruct->param[i]->draw_enable) {
            kitSetCounterParam(vtWaveGlobal.kitstruct, i);
            
            COPY128(vtWaveGlobal.kitstruct->screenenv[i].camera_p, vtWaveGlobal.cam_posi);
            COPY128(vtWaveGlobal.kitstruct->screenenv[i].camera_rot, vtWaveGlobal.cam_rot);
            COPY128(vtWaveGlobal.kitstruct->screenenv[i].world_view[0], GameGbl.wvm[0]);
            COPY128(vtWaveGlobal.kitstruct->screenenv[i].world_view[1], GameGbl.wvm[1]);
            COPY128(vtWaveGlobal.kitstruct->screenenv[i].world_view[2], GameGbl.wvm[2]);
            COPY128(vtWaveGlobal.kitstruct->screenenv[i].world_view[3], GameGbl.wvm[3]);
            kitMakeLocalMatrix(&vtWaveGlobal.kitstruct->screenenv[i]);
            kitMakeLocalMatrixInv(&vtWaveGlobal.kitstruct->screenenv[i]);
            kitDrawMeshClip(&vtWaveGlobal.kitstruct->screenenv[i], vtWaveGlobal.kitstruct->param[i]);

            sceVu0UnitMatrix(m);
            m[1][0] = -vtWaveGlobal.kitstruct->param[i]->shear;
            sceVu0MulMatrix(vtWaveGlobal.kitstruct->screenenv[i].local_screen, vtWaveGlobal.kitstruct->screenenv[i].local_screen, m);

            if (vtWaveGlobal.kitstruct->param[i]->multitex == 1 && !add_tex_flag) {
                tmp = kitMovieAddTex(tmp, vtWaveGlobal.kitstruct->param[i]);
                add_tex_flag = 1;
            }

            tmp = kitWaveSetTexEnv(tmp, vtWaveGlobal.kitstruct->param[i]);
            tmp = kitWaveSetMatrix(tmp, (u128 *)vtWaveGlobal.kitstruct->screenenv[i].local_screen, (u128 *)vtWaveGlobal.kitstruct->screenenv[i].local_light, (u128 *)vtWaveGlobal.kitstruct->screenenv[i].light_color);
            tmp = kitWaveSetVu1Data(tmp, vtWaveGlobal.kitstruct->param[i]);
            tmp = kitWaveSetWaveTable(tmp, vtWaveGlobal.kitstruct->table);
            tmp = kitWaveSetMicroProg(tmp);
        }
    }

    return tmp;
}