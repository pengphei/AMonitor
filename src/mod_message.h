#ifndef MOD_MESSAGE_H
#define MOD_MESSAGE_H

#include <stdint.h>
#include <sys/types.h>

int mod_message_init();
int mod_message_parse(uint8_t* pdata);
int mod_message_fini();

#endif // MOD_MESSAGE_H
