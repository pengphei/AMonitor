#include "mod_loader.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <dlfcn.h>

#define MOD_LOADER_DEBUG    printf

int mod_loader_open(char* path, stMOD_BASE_T** ppbase)
{
    void* pmod = NULL;
    void* pbase = NULL;

    /* open dynamic library */
    pmod = dlopen(path, RTLD_LAZY|RTLD_NODELETE);
    if(NULL == pmod)
    {
        MOD_LOADER_DEBUG("%s: open %s failed \n", path);
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
