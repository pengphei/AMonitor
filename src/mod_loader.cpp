#include "mod_loader.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <dlfcn.h>

#define MOD_PATH_MAX        1024
#define MOD_LIB_PATH_MAX    512
#define MOD_LOADER_DEBUG    printf

typedef struct
{
    int32_t init_flag;
    char path[MOD_LIB_PATH_MAX];
}_stMOD_LOADER_ATTR_T, *_pstMOD_LOADER_ATTR_T;

static _stMOD_LOADER_ATTR_T _loader_attr;

int mod_loader_init(char* exe_path)
{
    strncpy(_loader_attr.path, exe_path, MOD_LIB_PATH_MAX);
    _loader_attr.init_flag = 1;
    return 0;
}

int mod_loader_open(char* name, stMOD_BASE_T** ppbase)
{
    char exe_mod_path[MOD_PATH_MAX];
    void* pmod = NULL;
    void* pbase = NULL;
    if(NULL == ppbase || 0 == _loader_attr.init_flag)
    {
        return -1;
    }
    strcpy(exe_mod_path, _loader_attr.path);
    strncat(exe_mod_path, name, MOD_NAME_LEN_MAX);

    /* open dynamic library */
    pmod = dlopen(exe_mod_path, RTLD_LAZY|RTLD_NODELETE);
    if(NULL == pmod)
    {
        MOD_LOADER_DEBUG("%s: open %s failed \n", exe_mod_path);
        return -1;
    }

    /* load symbol base */
    pbase = dlsym(pmod, MOD_BASE_NAME);
    if(NULL == pbase)
    {
        MOD_LOADER_DEBUG("%s: load %s failed \n", MOD_BASE_NAME);
        return -1;
    }

    *ppbase = (stMOD_BASE_T*)pbase;

    return 0;
}

int mod_loader_close(stMOD_BASE_T *pbase)
{
    return 0;
}

int mod_loader_fini()
{
    _loader_attr.init_flag = 0;
    return 0;
}
