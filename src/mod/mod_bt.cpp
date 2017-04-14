#include "mod_bt.h"

#include <stdio.h>
#include <stdint.h>
#include "mod_def.h"

#define _BT_DEBUG    printf
#define _BT_NAME     "Bluetooth"

/** @brief 示例模块初始化 */
static int _bt_init(void* mod);
/** @brief 示例模块控制 */
static int _bt_ctrl(void* mod, uint32_t ctrl, void* data);
/** @brief 示例模块结束 */
static int _bt_fini(void* mod);

extern stMOD_BASE_T mod_base =
{
    NULL,
    _BT_NAME,
    _bt_init,
    _bt_ctrl,
    _bt_fini,
};

static int _bt_init(void* mod)
{
    _BT_DEBUG("%s \n", __func__);
    return 0;
}

static int _bt_ctrl(void* mod, uint32_t ctrl, void* data)
{
    _BT_DEBUG("%s ctrl 0x%08x \n", __func__, ctrl);
    return 0;
}

static int _bt_fini(void* mod)
{
    _BT_DEBUG("%s \n", __func__);
    return 0;
}
