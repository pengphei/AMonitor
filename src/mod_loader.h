#ifndef MOD_LOADER_H
#define MOD_LOADER_H

#include <stdint.h>
#include <sys/types.h>
#include "mod_def.h"

int mod_loader_open(char* path, stMOD_BASE_T **ppbase);
int mod_loader_close(stMOD_BASE_T* pbase);

#endif // MOD_LOADER_H
