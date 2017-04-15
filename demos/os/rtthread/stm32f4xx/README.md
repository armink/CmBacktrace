# stm32f4xx RT-Thread Demo

## STEP 1

文件夹 `RVMDK` 下为 Keil 工程，`EMARM` 下为 IAR 工程。打开工程后，在 `app/src/app_task.c` 中有 `fault_test_by_unalign()` 及 `fault_test_by_div0()` 两个 HardFault 测试函数，可以选择性的执行测试函数。

## STEP 2

将程序下载至开发板，并将其串口 1 与电脑串口连接。

## STEP 3

电脑上打开该串口，串口配置 115200 8 1 N ，给开发板上电，即可看到类似如下的输出信息，故障原因也已被准确的诊断出来：

```
Firmware name: CmBacktrace, hardware version: V1.0.0, software version: V0.1.0
Fault on thread sys_monitor
===== Thread stack information =====
  addr: 10002d58    data: 00000000
  addr: 10002d5c    data: 00000000
  addr: 10002d60    data: deadbeef
  addr: 10002d64    data: deadbeef
  addr: 10002d68    data: deadbeef
  addr: 10002d6c    data: 08000191
  addr: 10002d70    data: deadbeef
  addr: 10002d74    data: 080009e5
====================================
=================== Registers information ====================
  R0 : 00000000  R1 : 00000000  R2 : 00000000  R3 : 00000000
  R12: 00000000  LR : 08000191  PC : 0800035c  PSR: 41000000
==============================================================
Usage fault is caused by Indicates a divide by zero has taken place (can be set only if DIV_0_TRP is set)
Show more call stack info by run: addr2line -e CmBacktrace.out -a -f 0800035c 0800018d 080009e1
```

## STEP 4

打开电脑上的命令行工具，进入项目工程的可执行文件所在路径（Keil 一般在 `Output` 下，可执行文件后缀 `.axf`；IAR 一般在 ` Exe` 下，可执行文件后缀 `.out`），将 STEP 3 最后输出的 `addr2line -e CmBacktrace.out -a -f 0800035c 0800018d 080009e1` 拷贝至控制台，并执行（[点击查看 addr2line 工具的使用教程](https://github.com/armink/CmBacktrace/blob/master/docs/zh/how_to_use_addr2line_for_call_stack.md)），可看到类似如下，包含函数名称及代码行号的函数调用栈信息：

```
D:\Program\STM32\CmBacktrace\demos\os\rtthread\stm32f4xx\EWARM\STM32F405RG\Exe>addr2line -e CmBacktrace.out -a -f 0800035c 0800018d 080009e1
0x0800035c
fault_test_by_div0
D:\Program\STM32\CmBacktrace\demos\os\rtthread\stm32f4xx\app\src/fault_test.c:38
0x0800018d
thread_entry_sys_monitor
D:\Program\STM32\CmBacktrace\demos\os\rtthread\stm32f4xx\app\src/app_task.c:36
0x080009e1
rt_list_remove
D:\Program\STM32\CmBacktrace\demos\os\rtthread\stm32f4xx\RT-Thread-1.2.2\include/rtservice.h:95

D:\Program\STM32\CmBacktrace\demos\os\rtthread\stm32f4xx\EWARM\STM32F405RG\Exe>
```
