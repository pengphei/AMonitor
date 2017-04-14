#include "mod_uart.h"
#include <stdio.h>
#include <stdint.h>
#include "mod_def.h"

#define _UART_DEBUG    printf
#define _UART_NAME     "Uart"

/** @brief 示例模块初始化 */
static int _uart_init(void* mod);
/** @brief 示例模块控制 */
static int _uart_ctrl(void* mod, uint32_t ctrl, void* data);
/** @brief 示例模块结束 */
static int _uart_fini(void* mod);

extern stMOD_BASE_T mod_base =
{
    NULL,
    _UART_NAME,
    _uart_init,
    _uart_ctrl,
    _uart_fini,
};

static int _uart_init(void* mod)
{
    _UART_DEBUG("%s \n", __func__);
    return 0;
}

static int _uart_ctrl(void* mod, uint32_t ctrl, void* data)
{
    _UART_DEBUG("%s ctrl 0x%08x \n", __func__, ctrl);
    return 0;
}

static int _uart_fini(void* mod)
{
    _UART_DEBUG("%s \n", __func__);
    return 0;
}
