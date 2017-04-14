# -*- coding: utf-8 -*-
# @file SConscript
# @brief building struct
# @author Han Pengfei <hanpengfei@autobio.com.cn>
#

import os
from configobj import ConfigObj

# 获取 scons 构建参数
build_platform = ARGUMENTS.get('platform','x64')
build_doc = ARGUMENTS.get('build-doc', 0)
build_mode = ARGUMENTS.get('build-mode', "debug")

# 检查配置文件是否存在，提醒构建注意
tools_config = "tools.ini"
if not os.path.exists(tools_config):
    tools_config = "doc/tools.ini"
    print(u"#############################################")
    print(u"tools.ini配置文件不存在，默认使用 doc/tools.ini")
    print(u"请根据自己的环境在当前目录创建 tools.ini 文件")
    print(u"#############################################")

# 读取构建工具链配置文件，获取对应的配置
EnvTools = ConfigObj(tools_config)
PLATFORM = build_platform
EXE_PATH = EnvTools[PLATFORM]["PATH"]
PREFIX = EnvTools[PLATFORM]["PREFIX"]
STAGING_DIR = EnvTools[PLATFORM]["STAGING_DIR"]

# 创建构建全局环境，根据工具脸配置指定对应的构建命令
genv = Environment()
genv["CC"] = PREFIX + EnvTools[PLATFORM]["CC"]
genv["CXX"] = PREFIX + EnvTools[PLATFORM]["CXX"]
genv["AS"] = PREFIX + EnvTools[PLATFORM]["AS"]
genv["AR"] = PREFIX + EnvTools[PLATFORM]["AR"]
genv["LINK"] = PREFIX + EnvTools[PLATFORM]["LINK"]
genv["OBJCOPY"] = PREFIX + EnvTools[PLATFORM]["OBJCOPY"]
genv["NM"] = PREFIX + EnvTools[PLATFORM]["NM"]
genv["ENV"] = os.environ
genv["ENV"]["STAGING_DIR"] = STAGING_DIR
genv["STAGING_DIR"] = STAGING_DIR
genv["PROG_SUFFIX"] = "."+PLATFORM+".run"

genv["out"] = "#build/" + PLATFORM
genv["build"] = "#build/" + PLATFORM
genv["include"] = "#build/" + PLATFORM + "/include"
genv["doc"] = "#build/doc"

genv["BUILD_DOC"] = build_doc
genv["BUILD_PLATFORM"] = PLATFORM
genv["BUILD_MODE"] = build_mode
genv["LIBPATH"] = genv["out"]

genv.PrependENVPath('PATH', EXE_PATH)

Export("genv")

# 如果指定构建文档，则构建代码文档
if '1' == genv["BUILD_DOC"]:
    doc_script = "doc/SConscript"
    genv.SConscript(doc_script)
else:
    # 构建整个项目
    script = 'SConscript'
    genv.SConscript(script, variant_dir=genv["build"])
