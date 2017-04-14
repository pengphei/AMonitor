#include "mod_can.h"
#include <stdio.h>
#include <stdint.h>
#include "mod_def.h"

#define _CAN_DEBUG    printf
#define _CAN_NAME     "CAN"

/** @brief 示例模块初始化 */
static int _can_init(void* mod);
/** @brief 示例模块控制 */
static int _can_ctrl(void* mod, uint32_t ctrl, void* data);
/** @brief 示例模块结束 */
static int _can_fini(void* mod);

extern stMOD_BASE_T mod_base =
{
    NULL,
    _CAN_NAME,
    _can_init,
    _can_ctrl,
    _can_fini,
};

static int _can_init(void* mod)
{
    _CAN_DEBUG("%s \n", __func__);
    return 0;
}

static int _can_ctrl(void* mod, uint32_t ctrl, void* data)
{
    _CAN_DEBUG("%s ctrl 0x%08x \n", __func__, ctrl);
    return 0;
}

static int _can_fini(void* mod)
{
    _CAN_DEBUG("%s \n", __func__);
    return 0;
}
