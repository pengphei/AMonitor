#include "mod_main.h"
#include <unistd.h>
#include <stdio.h>
#include "mod_loader.h"


int mod_main_init(pstMOD_MAIN_PARA_T ppara)
{
    stMOD_BASE_T* pbase = NULL;
    return 0;
}

int mod_main_loop()
{
    while(1)
    {
        sleep(10);
    }
    return 0;
}

int mod_main_fini()
{
    return 0;
}
