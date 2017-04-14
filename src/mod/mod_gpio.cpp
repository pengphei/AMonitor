#include "mod_gpio.h"
#include <stdio.h>
#include <stdint.h>
#include "mod_def.h"

#define _GPIO_DEBUG    printf
#define _GPIO_NAME     "GPIO"

/** @brief 示例模块初始化 */
static int _gpio_init(void* mod);
/** @brief 示例模块控制 */
static int _gpio_ctrl(void* mod, uint32_t ctrl, void* data);
/** @brief 示例模块结束 */
static int _gpio_fini(void* mod);

extern stMOD_BASE_T mod_base =
{
    NULL,
    _GPIO_NAME,
    _gpio_init,
    _gpio_ctrl,
    _gpio_fini,
};

static int _gpio_init(void* mod)
{
    _GPIO_DEBUG("%s \n", __func__);
    return 0;
}

static int _gpio_ctrl(void* mod, uint32_t ctrl, void* data)
{
    _GPIO_DEBUG("%s ctrl 0x%08x \n", __func__, ctrl);
    return 0;
}
