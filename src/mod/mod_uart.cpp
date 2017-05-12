#include "mod_uart.h"
#include <stdio.h>
#include <stdint.h>
#include "mod_def.h"

#define _UART_DEBUG    printf
#define _UART_NAME     "Uart"

/** @brief 示例模块初始化 */
static int _uart_init(void* mod);
/** @brief 示例模块控制 */
static int _uart_ctrl(void* mod, char *jsonrpc, char *method, char *param, char *id);
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

static int _uart_ctrl(void* mod, char *jsonrpc, char *method, char *param, char *id)
{
    _UART_DEBUG("%s method %s param: %s\n", __func__, method,  param);
    return 0;
}

static int _uart_fini(void* mod)
{
    _UART_DEBUG("%s \n", __func__);
    return 0;
}
