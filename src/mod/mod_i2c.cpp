#include "mod_i2c.h"
#include <stdio.h>
#include <stdint.h>
#include "mod_def.h"

#define _I2C_DEBUG    printf
#define _I2C_NAME     "I2C"

/** @brief 示例模块初始化 */
static int _i2c_init(void* mod);
/** @brief 示例模块控制 */
static int _i2c_ctrl(void* mod, char *jsonrpc, char *method, char *param, char *id);
/** @brief 示例模块结束 */
static int _i2c_fini(void* mod);

extern stMOD_BASE_T mod_base =
{
    NULL,
    _I2C_NAME,
    _i2c_init,
    _i2c_ctrl,
    _i2c_fini,
};

static int _i2c_init(void* mod)
{
    _I2C_DEBUG("%s \n", __func__);
    return 0;
}

static int _i2c_ctrl(void* mod, char *jsonrpc, char *method, char *param, char *id)
{
    _I2C_DEBUG("%s method %s param: %s\n", __func__, method,  param);
    return 0;
}

static int _i2c_fini(void* mod)
{
    _I2C_DEBUG("%s \n", __func__);
    return 0;
}
