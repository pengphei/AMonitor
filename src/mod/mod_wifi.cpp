#include "mod_wifi.h"

#include <stdio.h>
#include <stdint.h>
#include "mod_def.h"

#define _WIFI_DEBUG    printf
#define _WIFI_NAME     "Wifi"

/** @brief 示例模块初始化 */
static int _wifi_init(void* mod);
/** @brief 示例模块控制 */
static int _wifi_ctrl(void* mod, uint32_t ctrl, void* data);
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

static int _wifi_ctrl(void* mod, uint32_t ctrl, void* data)
{
    _WIFI_DEBUG("%s ctrl 0x%08x \n", __func__, ctrl);
    return 0;
}

static int _wifi_fini(void* mod)
{
    _WIFI_DEBUG("%s \n", __func__);
    return 0;
}
