介绍
========================

本项目为 Linux 平台系统检测和硬件自动化测试工具。

模块结构
========================

* src/mod , 检测模块库。
* doc , doxygen 文档生成配置文件。
* site_scons , scons 用于 doxygen 文档生成相关脚本。
* lib , 第三方库。
* SConscript , 各个模块的构建脚本，用于生成应用程序或者库文件。

构建说明
========================

目前项目构建分为两部分，应用程序构建和文档构建。

在构建应用之前请确保系统中安装了 scons 构建工具，以及用于文档生成的 doxygen 和 graphviz 程序。

对于 Debian/Ubuntu 衍生系统，通过下述指令进行安装：

.. code-block:: shell
   
   sudo apt-get install scons doxygen graphviz

对于 redhat/fedora 衍生系统，安装命令如下：

.. code-block:: shell

   sudo yum install scons doxygen graphviz

对于 opensuse 系统，安装命令如下：

.. code-block:: shell

   sudo zypper in scons doxygen graphviz


应用程序构建
------------------------

.. code-block:: shell
    
   # 构建 arm 平台应用，需要在 SConstruct 中指明工具链。
   scons platform=arm

   # 构建本机测试平台
   scons

.. note::

   在构建完成后, 根据平台不同，将会在 build/out 目录下生成对应平台的应用程序和静态库。

   对于 src 中的项目将会在主目录下生成 *.map 文件，该文件为 Linux 程序的内存映射文件。在发生错误时可以对比参考
   内存出错位置，定位问题原因。

文档构建
------------------------

.. code-block:: shell

   scons build-doc=1

.. note::

   在构建完成后, 将会在 build/doxygen 目录下生成相应的文档说明。目前仅生成 html 格式说明。


