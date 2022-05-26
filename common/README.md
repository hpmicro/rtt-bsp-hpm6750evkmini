# RT-Thread BSP Common Repository

# Purpose of this repository

- Create the unified rt-thread driver adapter and startup in one place
- Upgrade the SDK and RT-Thread Driver adapter in one place
- Fix bugs in one place

# How to use this repository
This repository will be used as a submodule and it exists as __"common"__ folder under the root directory of all BSP repository

- When setting up a new rt-thread BSP repository, the repository owner can add this repository as submodule by the following command:
``` shell
    git submodule add -b master git@192.168.11.211:oss/rtt-bsp-common.git common
```
- Here are the steps to pick up new updates or switch to specific commits/tag/branch if the submodule already exists:
``` shell
    cd common
    git fetch
    git checkout <commit/tag/branch>
    cd ..
```
- Remember to commit the submodule update

# This repostory consists of the following parts:
- __rt-thread__ source code
- __libraries__
  - __hpm_sdk__ - HPM_SDK source code (with docs removed)
  - __drivers__ - RT-Thread driver adapter
- __startup__ code for HPMicro SoCs adapted for rt-thread
