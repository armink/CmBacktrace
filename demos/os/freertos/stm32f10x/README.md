# stm32f10x FreeRTOS Demo

## STEP 1

文件夹 `RVMDK` 下为 Keil 工程，`EMARM` 下为 IAR 工程。打开工程后，在 `app/src/app.c` 中有 `fault_test_by_unalign()` 及 `fault_test_by_div0()` 两个 HardFault 测试函数，可以选择性的执行测试函数。

## STEP 2

将程序下载至开发板，并将其串口1 与电脑串口连接。

## STEP 3

电脑上打开该串口，串口配置 115200 8 1 N ，给开发板上电，即可看到类似如下的输出信息，故障原因也已被准确的诊断出来：

```
Firmware name: CmBacktrace, hardware version: V1.0.0, software version: V0.1.0
Fault on thread app_start
===== Thread stack information =====
  addr: 200011f0    data: a5a5a5a5
  addr: 200011f4    data: 00000000
  addr: 200011f8    data: a5a5a5a5
  addr: 200011fc    data: a5a5a5a5
  addr: 20001200    data: a5a5a5a5
  addr: 20001204    data: 08000171
  addr: 20001208    data: a5a5a5a5
  addr: 2000120c    data: 080026ed
  addr: 20001210    data: a5a5a5a5
  addr: 20001214    data: a5a5a5a5
====================================
=================== Registers information ====================
  R0 : 00000000  R1 : a5a5a5a5  R2 : a5a5a5a5  R3 : a5a5a5a5
  R12: a5a5a5a5  LR : 08000171  PC : 08001788  PSR: 41000000
==============================================================
Usage fault is caused by Indicates a divide by zero has taken place (can be set only if DIV_0_TRP is set)
Show more call stack info by run: addr2line -e CmBacktrace.out -a -f 08001788 0800016d 080026e9
```

## STEP 4

打开电脑上的命令行工具，进入项目工程的可执行文件所在路径（Keil 一般在 `Output` 下，可执行文件后缀 `.axf`；IAR 一般在 ` Exe` 下，可执行文件后缀 `.out`），将 STEP 3 最后输出的 `addr2line -e CmBacktrace.out -a -f 08001788 0800016d 080026e9` 拷贝至控制台，并执行（[点击查看 addr2line 工具的使用教程](https://github.com/armink/CmBacktrace/blob/master/docs/zh/how_to_use_addr2line_for_call_stack.md)），可看到类似如下，包含函数名称及代码行号的函数调用栈信息：

```
D:\Program\STM32\CmBacktrace\demos\os\freertos\stm32f10x\EWARM\stm32f103xE\Exe>addr2line -e CmBacktrace.out -a -f 08001788 0800016d 080026e9
0x08001788
fault_test_by_div0
D:\Program\STM32\CmBacktrace\demos\os\freertos\stm32f10x\app\src/fault_test.c:38
0x0800016d
AppTaskStart
D:\Program\STM32\CmBacktrace\demos\os\freertos\stm32f10x\app\src/app.c:33
0x080026e9
pxPortInitialiseStack
D:\Program\STM32\CmBacktrace\demos\os\freertos\stm32f10x\FreeRTOS\portable\IAR\ARM_CM3/port.c:224

D:\Program\STM32\CmBacktrace\demos\os\freertos\stm32f10x\EWARM\stm32f103xE\Exe>
```

## FreeRTOS 源码修改说明   
 
因为 FreeRTOS 的 TCB 中没有 StackSize 信息，所以修改了其源码(基于 V9.0.0)，在 `FreeRTOS/tasks.c` 中增加了 `uxSizeOfStack` 字段， 以及 `vTaskStackAddr()` 、 `vTaskStackSize()` 、 `vTaskName()` 函数。
