#include "mod_monitor.h"
#include <stdio.h>
#include <stdint.h>
#include "mod_def.h"

#define _MONITOR_DEBUG    printf
#define _MONITOR_NAME     "Monitor"

/** @brief 示例模块初始化 */
static int _monitor_init(void* mod);
/** @brief 示例模块控制 */
static int _monitor_ctrl(void* mod, char *jsonrpc, char *method, char *param, char *id);
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

static int _monitor_ctrl(void* mod, char *jsonrpc, char *method, char *param, char *id)
{
    _MONITOR_DEBUG("%s method %s param: %s\n", __func__, method,  param);
    return 0;
}

static int _monitor_fini(void* mod)
{
    _MONITOR_DEBUG("%s \n", __func__);
    return 0;
}
