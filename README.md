# CmBacktrace: ARM Cortex-M 系列 MCU 错误追踪库

---

## 0、CmBacktrace 是什么

[CmBacktrace](https://github.com/armink/CmBacktrace) （Cortex Microcontroller Backtrace）是一款开源的针对 ARM Cortex-M 系列 MCU 的错误追踪库。主要特性如下：

- 追踪的对象包括：
    - 断言（assert）
    - 故障（Hard Fault, Memory Management Fault, Bus Fault, Usage Fault, Debug Fault）
- **自动诊断** 故障原因，无需手动分析故障寄存器；
- 输出断言及故障现场时的 **函数调用栈**（需配合 addr2line 工具进行精确定位），定位问题代码更加快捷、精准。也可以在正常状态下使用该库，获取当时的函数调用栈；
- 支持 裸机 及以下操作系统平台：
    - [RT-Thread](http://www.rt-thread.org/)
    - UCOS
    - FreeRTOS
- 根据错误现场状态，输出对应的 线程栈 或 C 主栈；
- 故障诊断信息支持多国语言（目前：简体中文、英文）；
- 适配 Cortex-M0/M3/M4/M7 MCU；
- 支持 IAR、KEIL、GCC 编译器；

## 1、为什么选择 CmBacktrace

**入门新人** ：对于从 C51 、MSP430 等简单单片机转而使用更加复杂的 ARM  新人来说，时不时出现的 "hard falut" 死机会让新人瞬间懵掉。定位错误的方法也往往是连接上仿真器，一步步 F10/F11 单步，定位到具体的错误代码，再去猜测、排除、推敲错误原因，这种过程十分痛苦。

**熟练老手** ：慢慢的大家知道可以通过故障寄存器信息来定位故障原因及故障代码地址，虽然这样能解决一小部分问题，但是重复的、繁琐的分析过程也会耽误很多时间。而且对于一些复杂问题，只依靠代码地址是无法解决的，必须得还原错误现场的函数调用逻辑关系。此时产品可能无法连接仿真器或者即便连接仿真器，问题也很难被复现，所以定位这类问题就显得难上加难。

**使用本库** ：上述所有问题都迎刃而解，可以将错误信息输出到控制台上，还可以将错误信息使用 [EasyFlash](https://github.com/armink/EasyFlash) 的 Log 功能保存至 Flash 中，设备死机后重启依然能够读取上次的错误信息。CmBacktrace 输出的信息包括函数调用栈、故障诊断结果、堆栈、故障寄存器及产品固件信息，极大的提升了错误定位的效率及准确性。

俗话说，工欲善其事，必先利其器。所以有时候做事效率低的原因也许是，你会用的工具种类太少。

**合作、贡献** ：开源软件的发展离不开大家的支持，欢迎大家多提建议，也希望更多的人一起参与进来，共同提高  。如果觉得这个开源项目很赞，可以点击 [项目主页](https://github.com/armink/CmBacktrace) **([Github](https://github.com/armink/CmBacktrace)|[OSChina](http://git.oschina.net/armink/CmBacktrace)|[Coding](https://coding.net/u/armink/p/CmBacktrace/git))**  右上角的 **Star** ，同时把它推荐给更多有需要的朋友。

## 2、CmBacktrace 如何使用

### 2.1 演示

- 制造除零异常
- 查看错误诊断信息
- 查看函数调用栈
- 定位错误代码
- 检查出错代码

### 2.2 Demo

|目录|平台|链接|
|:--|:--:|:--:|
| `\demo\non-os\stm32f10x` |裸机 STM32 Cortex-M3|[点击查看](https://github.com/armink/CmBacktrace/tree/master/demo/non_os/stm32f10x)|
| `\demo\os\freertos\stm32f10x` |FreeRTOS STM32 Cortex-M3|[点击查看](https://github.com/armink/CmBacktrace/tree/master/demo/os/freertos/stm32f10x)|
| `\demo\os\ucosii\stm32f20x` |UCOSII STM32 Cortex-M3|[点击查看](https://github.com/armink/CmBacktrace/tree/master/demo/os/ucosii/stm32f20x)|
| `\demo\os\rtthread\stm32f4xx`|RT-Thread STM32 Cortex-M4|[点击查看](https://github.com/armink/CmBacktrace/tree/master/demo/os/rtthread/stm32f4xx)|

### 2.3 移植说明

#### 2.3.1 准备工作

- 1、查看 `\demo` 目录下有没有合适自己的 Demo ，如有类似，则建议在其基础上修改
- 2、明确操作系统/裸机平台及 CPU 平台
- 3、将 `\src` 下的全部源文件添加至产品工程中，并保证源码目录被添加至头文件路径
- 4、cmb_fault.s 汇编文件可以选择性添加至工程，添加后一方面需要将文件中的需要将文件中的 `#if 0` 改为 `#if 1` ，另一方面需要把项目原有的 `HardFault_Handler` 注释掉
- 5、把 `cm_backtrace_init` 函数放在项目初始化地方执行
- 6、将 `cm_backtrace_assert` 放在项目的断言函数中执行，具体使用方法参照下面的 API 说明
- 7、如果第 4 步骤没有将 cmb_fault.s 汇编文件启用，则需要将 `cm_backtrace_fault` 放到故障处理函数（例如： `HardFault_Handler` ）中执行，具体使用方法参照下面的 API 说明

#### 2.3.2 配置说明

配置文件名： `cmb_cfg.h` ，针对不同的平台和场景，用户需要自自行手动配置，常用配置如下：

| 配置名称 |功能|备注|
|:--|:--|:--|
|cmb_println(...)|错误及诊断信息输出|必须配置|
|CMB_USING_BARE_METAL_PLATFORM|是否使用在裸机平台|使用则定义该宏|
|CMB_USING_OS_PLATFORM|是否使用在操作系统平台|操作系统与裸机必须二选一|
|CMB_OS_PLATFORM_TYPE|操作系统平台|RTT/UCOSII/UCOSIII/FREERTOS|
|CMB_CPU_PLATFORM_TYPE|CPU平台|M0/M3/M4/M7|
|CMB_USING_DUMP_STACK_INFO|是否使用 Dump 堆栈的功能|使用则定义该宏|
|CMB_PRINT_LANGUAGE|输出信息时的语言|CHINESE/ENGLISH|

> 注意：以上部分配置的内容可以在 `cmb_def.h` 中选择，更多灵活的配置请阅读源码

### 2.4 API 说明

#### 2.4.1 库初始化

```C
void cm_backtrace_init(const char *firmware_name, const char *hardware_ver, const char *software_ver)
```

|参数                                    |描述|
|:-----                                  |:----|
|firmware_name                           |固件名称，需与编译器生成的固件名称对应|
|hardware_ver                            |硬件版本号|
|software_ver                            |软件版本号|

> **注意** ：以上入参将会在断言或故障时输出，主要起了追溯的作用

#### 2.4.2 获取函数调用栈

```C
size_t cm_backtrace_call_stack(uint32_t *buffer, size_t size, uint32_t sp)
```

|参数                                    |描述|
|:-----                                  |:----|
|buffer                                  |存储函数调用栈的缓冲区|
|size                                    |缓冲区大小|
|sp                                      |待获取的堆栈指针|

示例：

```C
/* 建立深度为 16 的函数调用栈缓冲区，深度大小不应该超过 CMB_CALL_STACK_MAX_DEPTH（默认16） */
uint32_t call_stack[16] = {0};
size_t i, depth = 0;
/* 获取当前环境下的函数调用栈，每个元素将会以 32 位地址形式存储， depth 为函数调用栈实际深度 */
depth = cm_backtrace_call_stack(call_stack, sizeof(call_stack), __get_SP());
/* 输出当前函数调用栈信息
 * 注意：查看函数名称及具体行号时，需要使用 addr2line 工具转换
 */
for (i = 0; i < depth; i++) {
    printf("%08x ", call_stack[i]);
}
```

#### 2.4.3 追踪断言错误信息

```C
void cm_backtrace_assert(uint32_t sp)
```

|参数                                    |描述|
|:-----                                  |:----|
|sp                                      |断言环境时的堆栈指针|

> **注意** ：入参 SP 尽量在断言函数内部获取，而且尽可能靠近断言函数开始的位置。当在断言函数的子函数中（例如：在 RT-Thread 的断言钩子方法中）使用时，由于函数嵌套会存在寄存器入栈的操作，此时再获取 SP 将发生变化，就需要人为调整（加减固定的偏差值）入参值，所以作为新手 **不建议在断言的子函数** 中使用该函数。

#### 2.4.4 追踪故障错误信息

```C
void cm_backtrace_fault(uint32_t fault_handler_lr, uint32_t fault_handler_sp)
```

|参数                                    |描述|
|:-----                                  |:----|
|fault_handler_lr                        |故障处理函数环境下的 LR 寄存器值|
|fault_handler_sp                        |故障处理函数环境下的 SP 寄存器值|

该函数可以在故障处理函数（例如： `HardFault_Handler`）中调用。另外，库本身提供了 `HardFault` 处理的汇编文件，会在故障时自动调用 `cm_backtrace_fault` 方法。所以移植时，最简单的方式就是直接使用该汇编文件（把 cmb_fault.s 添加到工程，并修改 `#if 0` 为 `#if 1` ）。

### 2.5 常见错误

#### 编译出错，提示需要 C99 支持

开启 C99 教程： [点击查看]()

#### 无法准确查看到函数调用栈中的函数名及代码行号
#### 无法准备获取到故障时的寄存器信息
#### HardFault_Handler 重复定义

### 2.6 许可

采用 MIT 开源协议，细节请阅读项目中的 LICENSE 文件内容。