#include "mod_monitor.h"
#include <stdio.h>
#include <stdint.h>
#include "mod_def.h"

#define _MONITOR_DEBUG    printf
#define _MONITOR_NAME     "Monitor"

/** @brief 示例模块初始化 */
static int _monitor_init(void* mod);
/** @brief 示例模块控制 */
static int _monitor_ctrl(void* mod, uint32_t ctrl, void* data);
/** @brief 示例模块结束 */
static int _monitor_fini(void* mod);


extern stMOD_BASE_T mod_base =
{
    NULL,
    _MONITOR_NAME,
    _monitor_init,
    _monitor_ctrl,
    _monitor_fini,
};

static int _monitor_init(void* mod)
{
    _MONITOR_DEBUG("%s \n", __func__);
    return 0;
}

static int _monitor_ctrl(void* mod, uint32_t ctrl, void* data)
{
    _MONITOR_DEBUG("%s ctrl 0x%08x \n", __func__, ctrl);
    return 0;
}

static int _monitor_fini(void* mod)
{
    _MONITOR_DEBUG("%s \n", __func__);
    return 0;
}
