## 概述
***
**bldc_foc**工程展示了直流无刷电机的有感转速控制、位置控制，
以及无感转速控制。
- 通过**freemaster**进行转速控制，模式切换，位置控制
- 电机控制算法为**FOC**
- 无感控制算法为**SMO**
- 支持**gnu、nds、segger**工具链

## 硬件设置
***
- 本例程电机使用的是雷赛智能的 **BLM57050-1000** 无刷电机，电机具体参数请参考雷赛智能官网。

- **HPM6750EVK**核心板

	- 拨动核心板的拨码开关S1的第三位到PWM模式

- **DRV-LV50A-MP1907**电机驱动板

	- 使用跳线端子连接J12、J7、J6到HW、HV、HW
	- 使用跳线端子连接J10的VCC到3V3
	- 将电机的U、V、W三相和J4端子按照正确的线序相连
	- 将电机的信号线插入J14插座
	- 将24V电源接入J3端子

	- **NOTE:**
		1. **请注意电源正负极方向**
		2. **插接电路板时不要带电操作**
		3. **单独给电机驱动板上电，观察电流是否异常。如果异常请检查线路连接**
		4. **进行下一步前，请确保已经给电机驱动板断电**

- 核心板和电机驱动板的连接

	- **HPM6750EVK**核心板和**DRV-LV50A-MP1907**电机驱动板

		- 核心板的J8和电机驱动板的J12相连。**注意对照丝印，不要插反**
		- 下图是连接完成后的整体效果图，红色方框标出了可能需要操作的器件的位置：

		![image-1](../../../doc/images/readme/motor_ctrl_hpm_6750evk_drv_lv50a_mp1907__oee.jpg "image-1")

- **freemaster**的准备工作

	- 确保已经正确安装了**freemaster**，请自行通过网络获取相关软件及安装方法。
	- 确保你已经成功编译了工程，并已经生成elf格式文件
	- 在工程目录下找到[bldc_foc_segger.pmpx](./bldc_foc_segger.pmpx)的文件并双击打开
	- 在**freemaster**中加入编译生成的elf文件

		如果使用gnu-gcc或者nds-gcc编译，请使用如下方式配置：

		- Project->Options 可以出现下图，按照下图所示顺序和内容进行配置：

		![image-2](../../../doc/images/readme/motor_ctrl_freemaster_load_elf.jpg "image-2")

		如果使用segger环境，情况稍微复杂一点，请使用如下方式配置：

		**注意这里需要修改Default symbol载入的文件格式为map格式**
		- 打开配置File format的下拉列表并点击，如下图：

		![image-3](../../../doc/images/readme/motor_ctrl_freemaster_cfg_map_1.jpg "image-3")

		- 然后按照如下内容进行配置，下文列出代码，方便拷贝

			```
			HPM_SEGGER_MAP
			([0-9a-fA-F]+)-[0-9a-fA-F]+\s+(\w+)\s+([0-9])
			```
			配置后应当如图所示：

			![image-4](../../../doc/images/readme/motor_ctrl_freemaster_cfg_map_2.jpg "image-4")

	- **freemaster**选择正确的串口，确定核心板连接电脑后的串口号，Project->Options->Comm并按照下图进行配置

	![image-5](../../../doc/images/readme/motor_ctrl_freemaster_cfg_com.jpg "image-5")

- 完成上述过程后，给驱动板上电观察电流无异常后，给核心板上电，再次确认电流无异常后，就可以烧录程序，观察运行现象。

## 代码配置
***

- 如果需要更快的代码运行速度请在该工程的CMakeLists.txt中添加`sdk_compile_options("-mabi=ilp32f")`语句，获得较高的性能提升
- 本代码包含无传感器的滑模控制算法，请将 bldc_foc.c 中的 `#define MOTOR0_SMC_EN               (0) /*使能滑模控制*/`置1即可。


## 运行现象
***
### 有感

当工程正确运行后，电机以20r/s的速度运行。
点击**freemaster**的GO图标，启动freemaster即可配置如下数据：

`fre_setspeed` float类型， 输入范围+40~-40，单位r/s

`fre_setpos` int类型，范围不限，单位-4000~+4000对应-360~+360度

`fre_user_mode` bool类型， 1- 速度模式   0-位置模式

- 速度模式：

	可以在规定的速度范围内输入速度参数，并通过**freemaster**观察速度变化

- 位置模式：

	可以设置电机轴的位置，此时电机轴会锁定在指定的位置

也可以查看如下参数：

	`fre_dispspeed` float类型，单位r/s

### 无感

当工程正确运行后，电机以20r/s的速度运行。
点击**freemaster**的GO图标，启动freemaster即可配置如下数据：

`fre_setspeed` float类型， 输入范围+40~+5，-5~-40单位r/s

也可以查看如下参数：

`fre_dispspeed` float类型，单位r/s

## 注意事项

- 电机上电后首先要完成对中动作，这时候请不要干预电机运行，否则会产生抖动

- 电机运行时，请时刻注意电流大小，如果发生异常，请随时准备切断电源。

- 如果需要功能更多的可配置项，请使用我们提供的**gnu-gcc**工具链，并通过**freemaster**
载入[bldc_foc.pmpx](./bldc_foc.pmpx)
