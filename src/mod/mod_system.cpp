#include "mod_system.h"

#include <stdio.h>
#include <stdint.h>
#include "mod_def.h"

#define _SYSTEM_DEBUG    printf
#define _SYSTEM_NAME     "System"

/** @brief 示例模块初始化 */
static int _system_init(void* mod);
/** @brief 示例模块控制 */
static int _system_ctrl(void* mod, uint32_t ctrl, void* data);
/** @brief 示例模块结束 */
static int _system_fini(void* mod);


extern stMOD_BASE_T mod_base =
{
    NULL,
    _SYSTEM_NAME,
    _system_init,
    _system_ctrl,
    _system_fini,
};

static int _system_init(void* mod)
{
    _SYSTEM_DEBUG("%s \n", __func__);
    return 0;
}

static int _system_ctrl(void* mod, uint32_t ctrl, void* data)
{
    _SYSTEM_DEBUG("%s ctrl 0x%08x \n", __func__, ctrl);
    return 0;
}

static int _system_fini(void* mod)
{
    _SYSTEM_DEBUG("%s \n", __func__);
    return 0;
}
