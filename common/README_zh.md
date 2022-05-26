# RT-Thread BSP Common 仓库

# 该仓库的目的
- 在同一个地方适配RT-Thread 驱动框架
- 在同一处升级HPM_SDK以及RT-THread驱动适配层
- 在同一处修复bug


# 如何使用该仓库
该仓库作为submodule被使用，在BSP仓库中以 __"common"__ 目录的形式存在

- 当开始建立新的rt-thread BSP 仓库时，可通过下面的命令将本仓库添加为submodule:
``` shell
    git submodule add -b master git@192.168.11.211:oss/rtt-bsp-common.git common
```
- 若需要获取更新/切换到新的tag/commit/branch, 可按如下命令操作:
``` shell
    cd common
    git fetch
    git checkout <commit/tag/branch>
    cd ..
```
- 记得在rt-thread BSP仓库里提前submodule的改动


# 本仓库由如下部分组成:
- __rt-thread__ 源代码
- __libraries__
  - __hpm_sdk__ - HPM_SDK 源码 (删除了文档部分)
  - __drivers__ - RT-Thread 驱动适配层
- __startup__ 适配了RT-Thread的启动代码
