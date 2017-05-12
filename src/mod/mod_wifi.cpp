#include "mod_wifi.h"

#include <stdio.h>
#include <stdint.h>
#include "mod_def.h"

#define _WIFI_DEBUG    printf
#define _WIFI_NAME     "Wifi"

/** @brief 示例模块初始化 */
static int _wifi_init(void* mod);
/** @brief 示例模块控制 */
static int _wifi_ctrl(void* mod, char *jsonrpc, char *method, char *param, char *id);
/** @brief 示例模块结束 */
static int _wifi_fini(void* mod);

extern stMOD_BASE_T mod_base =
{
    NULL,
    _WIFI_NAME,
    _wifi_init,
    _wifi_ctrl,
    _wifi_fini,
};

static int _wifi_init(void* mod)
{
    _WIFI_DEBUG("%s \n", __func__);
    return 0;
}

static int _wifi_ctrl(void* mod, char* jsonrpc, char* method, char* param, char* id)
{
    _WIFI_DEBUG("%s method %s param: %s\n", __func__, method,  param);
    return 0;
}

static int _wifi_fini(void* mod)
{
    _WIFI_DEBUG("%s \n", __func__);
    return 0;
}
