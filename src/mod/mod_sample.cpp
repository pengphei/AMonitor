#include "mod_sample.h"
#include <stdio.h>
#include <stdint.h>
#include "mod_def.h"

#define _SAMPLE_DEBUG    printf
#define _SAMPLE_NAME     "Sample"

/** @brief 示例模块初始化 */
static int _sample_init(void* mod);
/** @brief 示例模块控制 */
static int _sample_ctrl(void* mod, char *jsonrpc, char *method, char *param, char *id);
/** @brief 示例模块结束 */
static int _sample_fini(void* mod);

extern stMOD_BASE_T mod_base =
{
    NULL,
    _SAMPLE_NAME,
    _sample_init,
    _sample_ctrl,
    _sample_fini,
};

static int _sample_init(void* mod)
{
    _SAMPLE_DEBUG("%s \n", __func__);
    return 0;
}

static int _sample_ctrl(void* mod, char *jsonrpc, char *method, char *param, char *id)
{
    _SAMPLE_DEBUG("%s method %s param: %s\n", __func__, method,  param);
    return 0;
}

static int _sample_fini(void* mod)
{
    _SAMPLE_DEBUG("%s \n", __func__);
    return 0;
}
