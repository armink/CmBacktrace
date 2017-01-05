# stm32f10x non-os Demo

## STEP 1

文件夹 `RVMDK` 下为 Keil 工程，`EMARM` 下为 IAR 工程。打开工程后，在 `app/src/app.c` 中有 `fault_test_by_unalign()` 及 `fault_test_by_div0()` 两个 HardFault 测试函数，可以选择性的执行测试函数。

## STEP 2

将程序下载至开发板，并将其串口1 与电脑串口连接。

## STEP 3

电脑上打开该串口，串口配置 115200 8 1 N ，给开发板上电，即可看到类似如下的输出信息，故障原因也已被准确的诊断出来：

```
Firmware name: CmBacktrace, hardware version: V1.0.0, software version: V0.1.0
Fault on interrupt or bare metal(no OS) environment
====== Main stack information ======
  addr: 20001140    data: 00000000
  addr: 20001144    data: e000ed14
  addr: 20001148    data: 0000000a
  addr: 2000114c    data: 00000000
  addr: 20001150    data: a046ac2b
  addr: 20001154    data: 08000145
  addr: 20001158    data: e000ed14
  addr: 2000115c    data: 08003143
====================================
=================== Registers information ====================
  R0 : 00000000  R1 : 200012ec  R2 : 00000000  R3 : 00000000
  R12: 00008080  LR : 08000145  PC : 08000a60  PSR: 61000000
==============================================================
Usage fault is caused by Indicates a divide by zero has taken place (can be set only if DIV_0_TRP is set)
Show more call stack info by run: addr2line -e CmBacktrace.out -a -f 08000a60 08000141 0800313f 
```

## STEP 4

打开电脑上的命令行工具，进入项目工程的可执行文件所在路径（Keil 一般在 `Output` 下，可执行文件后缀 `.axf`；IAR 一般在 ` Exe` 下，可执行文件后缀 `.out`），将 STEP 3 最后输出的 `addr2line -e CmBacktrace.out -a -f 08000a60 08000141 0800313f` 拷贝至控制台，并执行（[点击查看 addr2line 工具的使用教程](https://github.com/armink/CmBacktrace/blob/master/docs/zh/how_to_use_addr2line_for_call_stack.md)），可看到类似如下，包含函数名称及代码行号的函数调用栈信息：

```
D:\Program\STM32\CmBacktrace\demo\non_os\stm32f10x\EWARM\stm32f103xE\Exe>addr2line -e CmBacktrace.out -a -f 08000a60 08000141 0800313f
0x08000a60
fault_test_by_div0
D:\Program\STM32\CmBacktrace\demo\non_os\stm32f10x\app\src/fault_test.c:38
0x08000141
main
D:\Program\STM32\CmBacktrace\demo\non_os\stm32f10x\app\src/app.c:20
0x0800313f
_call_main
??:?

D:\Program\STM32\CmBacktrace\demo\non_os\stm32f10x\EWARM\stm32f103xE\Exe>
```
