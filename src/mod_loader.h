#ifndef MOD_LOADER_H
#define MOD_LOADER_H

#include <stdint.h>
#include <sys/types.h>
#include "mod_def.h"

int mod_loader_init(char* exe_path);
int mod_loader_open(char* name, stMOD_BASE_T **ppbase);
int mod_loader_close(stMOD_BASE_T* pbase);
int mod_loader_fini();

#endif // MOD_LOADER_H
