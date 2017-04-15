# stm32f10x UCOSII Demo

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
  addr: 200024d8    data: 03030303
  addr: 200024dc    data: 00000000
  addr: 200024e0    data: 05050505
  addr: 200024e4    data: 06060606
  addr: 200024e8    data: 07070707
  addr: 200024ec    data: 08000195
  addr: 200024f0    data: 04040404
  addr: 200024f4    data: 08001c99
====================================
=================== Registers information ====================
  R0 : 00000000  R1 : 01010101  R2 : 02020202  R3 : 03030303
  R12: 12121212  LR : 08000195  PC : 08001d24  PSR: 41000000
==============================================================
Usage fault is caused by Indicates a divide by zero has taken place (can be set only if DIV_0_TRP is set)
Show more call stack info by run: addr2line -e CmBacktrace.out -a -f 08001d24 08000191 08001c95
```

## STEP 4

打开电脑上的命令行工具，进入项目工程的可执行文件所在路径（Keil 一般在 `Output` 下，可执行文件后缀 `.axf`；IAR 一般在 ` Exe` 下，可执行文件后缀 `.out`），将 STEP 3 最后输出的 `addr2line -e CmBacktrace.out -a -f 08001d24 08000191 08001c95` 拷贝至控制台，并执行（[点击查看 addr2line 工具的使用教程](https://github.com/armink/CmBacktrace/blob/master/docs/zh/how_to_use_addr2line_for_call_stack.md)），可看到类似如下，包含函数名称及代码行号的函数调用栈信息：

```
D:\Program\STM32\CmBacktrace\demos\os\ucosii\stm32f10x\EWARM\stm32f103xE\Exe>addr2line -e CmBacktrace.out -a -f 08001d24 08000191 08001c95
0x08001d24
fault_test_by_div0
D:\Program\STM32\CmBacktrace\demos\os\ucosii\stm32f10x\app\src/fault_test.c:38
0x08000191
AppTaskStart
D:\Program\STM32\CmBacktrace\demos\os\ucosii\stm32f10x\app\src/app.c:49
0x08001c95
OSTaskSuspend
D:\Program\STM32\CmBacktrace\demos\os\ucosii\stm32f10x\ucosii\Source/os_task.c:1006

D:\Program\STM32\CmBacktrace\demos\os\ucosii\stm32f10x\EWARM\stm32f103xE\Exe>
```
