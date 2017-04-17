#include "mod_manage.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MOD_PATH_MAX        1024
#define MOD_LIB_PATH_MAX    512

typedef struct
{
    int32_t init_flag;
    char path[MOD_LIB_PATH_MAX];
}_stMOD_MAN_ATTR_T, *_pstMOD_MAN_ATTR_T;


static _stMOD_MAN_ATTR_T _man_attr;
static _pstMOD_MAN_ATTR_T _pman_attr = &_man_attr;

int mod_man_init(char *exe_path)
{
    strncpy(_pman_attr->path, exe_path, MOD_LIB_PATH_MAX);
    _pman_attr->init_flag = 1;
    return 0;
}
