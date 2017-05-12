#ifndef MOD_DEF_H
#define MOD_DEF_H

#include <stdint.h>
#include <sys/types.h>

#define MOD_NAME_LEN_MAX    512
#define MOD_BASE_NAME       "mod_base"

/**
 * @brief 模块初始化函数原型
 */
typedef int (*func_mod_init_t)(void* mod);

/**
 * @brief 模块控制函数原型
 */
typedef int (*func_mod_ctrl_t)(void* mod, char* jsonrpc, char* method, char* param, char* id);

/**
 * @brief 模块销毁函数原型
 */
typedef int (*func_mod_fini_t)(void* mod);

typedef struct
{
    void* mod;
    char name[MOD_NAME_LEN_MAX];
    func_mod_init_t mod_init;
    func_mod_ctrl_t mod_ctrl;
    func_mod_fini_t mod_fini;
}stMOD_BASE_T, *pstMOD_BASE_T;

#endif // MOD_DEF_H
