#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <string.h>
#include <getopt.h>
#include <stdarg.h>
#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>
#include "mod_main.h"

#ifdef SYS_DEBUG
#define MAIN_DEBUG SYS_DEBUG
#else
#define MAIN_DEBUG printf
#endif

#ifndef MOD_BUILD_NAME
#define MOD_BUILD_NAME  "Amonitor"
#endif

#ifndef MOD_BUILD_TIMESTAMP
#define MOD_BUILD_TIMESTAMP  "2017-04-01"
#endif

static stMOD_MAIN_PARA_T gpara;
static pstMOD_MAIN_PARA_T gppara = &gpara;

#define MOD_PATH_DEFAULT    "./"
#define MOD_PORT_DEFAULT    9090

static int _util_dir_is_existed(char* dir)
{
    if(NULL == dir)
    {
        return 0;
    }

    if(NULL == opendir(dir))
    {
        return 0;
    }

    return 1;
}

static int _util_dir_create(char* dir)
{
    int ii = 0;
    int len = 0;
    char ddir[1024];
    strcpy(ddir, dir);
    len = strlen(ddir);

    if('/' != ddir[len-1])
    {
        strcat(ddir,"/");
    }

    len = strlen(ddir);

    for(ii=1; ii<len; ii++)
    {
        if('/' == ddir[ii])
        {
            ddir[ii] = 0;
            if(0 != access(ddir, F_OK))
            {
                if(-1 == mkdir(ddir, 0755))
                {
                    perror("mkdir error");
                    return -1;
                }
            }
            ddir[ii] = '/';
        }
    }

    return 0;
}

static int _main_dump_help(char **argv)
{
    printf("\n");
    printf("Usage: %s\n", argv[0]);
    printf("  Arguments:\n");
    printf("    -h --help           print this help info \n");
    printf("    -m --mode           the mod path\n");
    printf("    -p --port           listen port , aka 8080 \n");
    exit(EXIT_FAILURE);
    return -1;
}

static int _main_args_dump()
{
    MAIN_DEBUG("mod path: %s \n", gppara->mod_path);
    MAIN_DEBUG("    port: %d \n", gppara->port);
    return 0;
}

static int _main_args_default()
{
    static char mod_path[] = MOD_PATH_DEFAULT;
    int port = MOD_PORT_DEFAULT;
    gppara->mod_path = mod_path;
    gppara->port = port;
    return 0;
}

static int _main_show_info()
{
    MAIN_DEBUG("%s (%s) \n", MOD_BUILD_NAME, MOD_BUILD_TIMESTAMP);
    return 0;
}

static int _main_check_path()
{
    if(0 == _util_dir_is_existed(gppara->mod_path))
    {
        return _util_dir_create(gppara->mod_path);
    }
    else
    {
        return 0;
    }
}

static int _main_args_process(int argc, char **argv)
{
    signed char opt = 0;
    int option_index = 0;

    static struct option long_options[] =
    {
        {"help",                    no_argument,        NULL,       'h'},
        {"mode",                    required_argument,  NULL,       'm'},
        {"port",                    required_argument,  NULL,       'p'},
        { NULL, 0, NULL, 0}
    };

    while((opt = getopt_long(argc, argv, "hm:p:", long_options, &option_index)) != -1)
    {
        switch (opt)
        {
            case 0:
            case 'h':
                _main_dump_help(argv);
                break;
            case 'm':
                gppara->mod_path = optarg;
                break;
            case 'p':
                gppara->port = atoi(optarg);
                break;
            default:
                break;
        }
    }

    if(0 != _main_check_path())
    {
        fprintf(stderr, "Start failed! Error: check path %s failed \n", gppara->mod_path);
        _main_dump_help(argv);
        return -1;
    }

     return 0;
}


int main(int argc, char **argv)
{
    /* 打印启动消息，软件名称，构建时间等 */
    _main_show_info();

    /* 设置默认系统参数 */
    _main_args_default();

    /* 命令行启动参数处理 */
    _main_args_process(argc, argv);

    /* 打印最终参数 */
    _main_args_dump();

    /* 使用最终参数初始化应用 */
    mod_main_init(gppara);

    /* 应用主进程循环 */
    mod_main_loop();
}
