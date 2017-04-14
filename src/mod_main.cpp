#include "mod_main.h"
#include <unistd.h>
#include <stdio.h>
#include "mod_loader.h"

int mod_main_init(pstMOD_MAIN_PARA_T ppara)
{
    stMOD_BASE_T* pbase = NULL;
    mod_loader_init(ppara->mod_path);

    mod_loader_open("libmod_sample.so", &pbase);

    printf("name: %s\n", pbase->name);
    pbase->mod_init(pbase->mod);
    pbase->mod_ctrl(pbase->mod, 0, NULL);
    pbase->mod_fini(pbase->mod);

    mod_loader_open("libmod_sample.so", &pbase);

    printf("name: %s\n", pbase->name);
    pbase->mod_init(pbase->mod);
    pbase->mod_ctrl(pbase->mod, 0, NULL);
    pbase->mod_fini(pbase->mod);
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
