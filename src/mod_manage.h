#ifndef MOD_MANAGE_H
#define MOD_MANAGE_H

#include <stdint.h>
#include <sys/types.h>
#include "mod_def.h"

int mod_man_init(char* exe_path);
int mod_man_append();
int mod_man_check();
int mod_man_process();
int mod_man_fini();

#endif // MOD_MANAGE_H
