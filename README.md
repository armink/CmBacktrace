# CmBacktrace: ARM Cortex-M series MCU error tracking library

[中文页](README_ZH.md) | English

[![GitHub release](https://img.shields.io/github/release/armink/CmBacktrace.svg)](https://github.com/armink/CmBacktrace/releases/latest) [![GitHub commits](https://img.shields.io/github/commits-since/armink/CmBacktrace/1.4.0.svg)](https://github.com/armink/CmBacktrace/compare/1.0.0...master) [![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/armink/CmBacktrace/master/LICENSE)

## 0、What is CmBacktrace

[CmBacktrace](https://github.com/armink/CmBacktrace) (Cortex Microcontroller Backtrace) is an open source library that automatically tracks and locates error codes for ARM Cortex-M series MCUs, and automatically analyzes the causes of errors. The main features are as follows:

- Supported errors include:
    - Assert
    - Fault (Hard Fault, Memory Management Fault, Bus Fault, Usage Fault, Debug Fault)
- Failure reason **Automatic diagnosis**: When a failure occurs, the cause of the failure can be automatically analyzed, and the code location of the failure can be located, without the need to manually analyze the complicated fault registers;
-Output the **function call stack** of the error site (need to cooperate with the addr2line tool for precise positioning), restore the field information when the error occurred, and locate the problem code location and logic more quickly and accurately. You can also use the library under normal conditions to get the current function call stack;
- Support bare metal and the following operating system platforms:
    - [RT-Thread](http://www.rt-thread.org/)
    - UCOS
    - FreeRTOS (source code needs to be modified)
- According to the error scene status, output the corresponding thread stack or C main stack;
- The fault diagnosis information supports multiple languages ​​(currently: Simplified Chinese, English);
- Adapt to Cortex-M0/M3/M4/M7 MCU;
- Support IAR, KEIL, GCC compiler;

## 1. Why choose CmBacktrace

**Beginner Newcomer**: For newcomers who switch from simple microcontrollers such as C51 and MSP430 to more complex ARM, the chance of "hard falut" death from time to time makes newcomers instantly stunned. The method of locating errors is often to connect to the emulator, step by step F10/F11, locate the specific error code, and then guess, eliminate, and deliberate on the cause of the error. This process is very painful.

**Skilled veteran**: Slowly everyone knows that the fault cause and fault code address can be located through the fault register information. Although this can solve a small part of the problem, the repeated and tedious analysis process will also delay a lot of time. Moreover, for some complex problems, it is impossible to solve only by the code address, and the function call logic relationship of the wrong scene must be restored. Although the function call stack can be viewed by connecting to the emulator, it cannot be displayed in the fault state, so it is necessary to step by step F10/F11 to locate the error code. In addition, there are two scenarios,

 1. The emulator must be disconnected when debugging many products
 2. The problem does exist, but it is extremely difficult to reproduce

So locating such problems is even more difficult.

**Use this library**: All the above problems can be solved easily. The error message can be output to the console, and the error message can also be saved using the Log function of [EasyFlash](https://github.com/armink/EasyFlash) In Flash, the last error message can still be read after the device crashes and restarts. The information output by CmBacktrace includes function call stack, fault diagnosis result, stack, fault register and product firmware information, which greatly improves the efficiency and accuracy of error location.

As the saying goes, a worker must first sharpen his tools if he wants to do his job well. So sometimes the reason for the low efficiency may be that you will use too few types of tools.

**Cooperation, Contribution**: The development of open source software is inseparable from everyone's support. You are welcome to make more suggestions and hope that more people will join in and improve together. If you think this open source project is great, you can click [Project Homepage](https://github.com/armink/CmBacktrace) **([Github](https://github.com/armink/CmBacktrace)|[OSChina](http://git.oschina.net/armink/CmBacktrace)|[Coding](https://coding.net/u/armink/p/CmBacktrace/git))** Star** in the upper right corner, At the same time recommend it to more friends in need.

## 2. How to use CmBacktrace

### 2.1 Demo

The demonstration is divided into the following steps:

 1. Manufacturing division by zero exception ([IAR project, click to view source code](https://github.com/armink/CmBacktrace/tree/master/demos/non_os/stm32f10x/app/src))
 2. View error diagnosis information
 3. View the basic information of the function call stack
 4. Enter the path where the executable file is stored in the project project through the command line tool
 5. Use the addr2line command to view the function call stack details and locate the error code

[![cm_backtrace_demo](https://raw.githubusercontent.com/armink/CmBacktrace/master/docs/zh/images/cm_backtrace_demo.gif)](https://github.com/armink/CmBacktrace)

### 2.2 Demo

|Catalog|Platform|Link|
|:--|:--:|:--:|
| `\demos\non_os\stm32f10x` |bare metal STM32 Cortex-M3|[click to view](https://github.com/armink/CmBacktrace/tree/master/demos/non_os/stm32f10x)|
| `\demos\os\rtthread\stm32f4xx`|RT-Thread STM32 Cortex-M4|[Click to view](https://github.com/armink/CmBacktrace/tree/master/demos/os/rtthread/stm32f4xx)|
| `\demos\os\ucosii\stm32f10x` |UCOSII STM32 Cortex-M3|[Click to view](https://github.com/armink/CmBacktrace/tree/master/demos/os/ucosii/stm32f10x)|
| `\demos\os\freertos\stm32f10x` |FreeRTOS STM32 Cortex-M3|[Click to view](https://github.com/armink/CmBacktrace/tree/master/demos/os/freertos/stm32f10x)|



### 2.3 Porting instructions

#### 2.3.1 Preparation

 1. Check whether there is a suitable Demo in the `\demos` directory, if there is a similar, it is recommended to modify it on the basis of it
 2. Identify the operating system/bare metal platform and CPU platform
 3. Add all source files under `\src` to the product project, and ensure that the source code directory is added to the header file path
 4. The cmb_fault.s assembly file ([click to view](https://github.com/armink/CmBacktrace/tree/master/cm_backtrace/fault_handler)) can be optionally added to the project. After adding, you need to add the original project `HardFault_Handler` comment out
 5. Put the `cm_backtrace_init` function in the project initialization place for execution
 6. Put `cm_backtrace_assert` in the assertion function of the project for execution. For specific usage, please refer to the API description below
 7. If the cmb_fault.s assembly file is not enabled in step 4, you need to put `cm_backtrace_fault` in the fault handling function (for example: `HardFault_Handler`) for execution. For details, refer to the API description below

#### 2.3.2 Configuration Instructions

Configuration file name: `cmb_cfg.h`, users need to manually configure themselves for different platforms and scenarios. Common configurations are as follows:

| Configuration name | Function | Remarks |
|:--|:--|:--|
|cmb_println(...)|Error and diagnostic information output|Must be configured|
|CMB_USING_BARE_METAL_PLATFORM|Whether it is used on a bare metal platform|Define this macro if it is used|
|CMB_USING_OS_PLATFORM|Whether it is used on the operating system platform|Operating system and bare metal must choose one of two|
|CMB_OS_PLATFORM_TYPE|Operating System Platform|RTT/UCOSII/UCOSIII/FREERTOS|
|CMB_CPU_PLATFORM_TYPE|CPU platform|M0/M3/M4/M7|
|CMB_USING_DUMP_STACK_INFO|Whether to use Dump stack function|Use to define this macro|
|CMB_PRINT_LANGUAGE|Language when outputting information|CHINESE/ENGLISH|

> Note: The content of the above configuration can be selected in `cmb_def.h`, please read the source code for more flexible configuration

### 2.4 API description

#### 2.4.1 Library initialization

```C
void cm_backtrace_init(const char *firmware_name, const char *hardware_ver, const char *software_ver)
```

|Parameter |Description|
|:----- |:----|
|firmware_name |firmware name, which must correspond to the firmware name generated by the compiler|
|hardware_ver |The hardware version number corresponding to the firmware|
|software_ver |Software version number of the firmware|

> **Note**: The above input parameters will be output in case of assertion or failure, mainly for retrospective purposes

#### 2.4.2 Get function call stack

```C
size_t cm_backtrace_call_stack(uint32_t *buffer, size_t size, uint32_t sp)
```

|Parameter |Description|
|:----- |:----|
|buffer |Buffer for storing function call stack|
|size |Buffer size|
|sp |Stack pointer to be obtained|

Example:

```C
/* Create a function call stack buffer with a depth of 16, and the depth should not exceed CMB_CALL_STACK_MAX_DEPTH (default 16) */
uint32_t call_stack[16] = {0};
size_t i, depth = 0;
/* Get the function call stack in the current environment, each element will be stored as a 32-bit address, and depth is the actual depth of the function call stack */
depth = cm_backtrace_call_stack(call_stack, sizeof(call_stack), cmb_get_sp());
/* Output current function call stack information
 * Note: When viewing the function name and specific line number, you need to use the addr2line tool to convert
 */
for (i = 0; i <depth; i++) {
    printf("%08x ", call_stack[i]);
}
```

#### 2.4.3 Tracking assertion error messages

```C
void cm_backtrace_assert(uint32_t sp)
```

|Parameter |Description|
|:----- |:----|
|sp |Stack pointer when asserting environment|

> **Note**: The input parameter SP should be obtained inside the assertion function as much as possible, and as close as possible to the beginning of the assertion function. When used in the sub-function of the assertion function (for example: in the assertion hook method of RT-Thread), due to the nesting of the function, there will be the operation of registering the stack, and the SP will be changed at this time, and manual adjustment is required ( Add and subtract a fixed deviation value) into the parameter value, so as a novice, it is not recommended to use this function in the sub-function of the assertion.

#### 2.4.4 Tracking fault information

```C
void cm_backtrace_fault(uint32_t fault_handler_lr, uint32_t fault_handler_sp)
```

|Parameter |Description|
|:----- |:----|
|fault_handler_lr |LR register value under fault handling function environment|
|fault_handler_sp |SP register value under fault handling function environment|

This function can be called in the fault handling function (for example: `HardFault_Handler`). In addition, the library itself provides assembly files processed by `HardFault` ([click to view](https://github.com/armink/CmBacktrace/tree/master/cm_backtrace/fault_handler), you need to choose according to your own compiler), The `cm_backtrace_fault` method is automatically called in the event of a fault. So when transplanting, the easiest way is to use the assembly file directly.

### 2.5 FAQ

#### 2.5.1 Compilation error, suggesting that C99 support is required

[Click to view the tutorial: Open Keil/IAR/GCC C99 support in one step](https://github.com/armink/CmBacktrace/blob/master/docs/zh/enable_c99_for_keil_iar_gcc.md)

#### 2.5.2 How to view the specific name and code line number of the function in the function call stack

[Click to view the tutorial: How to use the addr2line tool to get the function call stack details](https://github.com/armink/CmBacktrace/blob/master/docs/zh/how_to_use_addr2line_for_call_stack.md)

#### 2.5.3 Fault handling function: HardFault_Handler repeated definition

When the cmb_fault.s assembly file provided by this library is used, because HardFault_Handler is already defined in the assembly file, if this function is defined elsewhere in the project, an error that HardFault_Handler is repeatedly defined will be prompted. There are two solutions at this time:

 1. Comment/delete the `HardFault_Handler` function defined in other files, and only keep the cmb_fault.s;
 2. Remove cmb_fault.s from the project, and manually add the `cm_backtrace_fault` function to the existing fault handling function, but it should be noted that you must ** ensure the readiness of the function to enter the parameters**, otherwise it may cause The fault diagnosis function and stack printing function cannot operate normally. So if you are a novice, the second solution is not recommended.

#### 2.5.4 Prompt that the main stack information cannot be obtained during initialization

The default main stack configuration is defined in `cmd_def.h`, roughly as follows:

```c

#if defined(__CC_ARM)
    /* C stack block name,default is STACK */
    #ifndef CMB_CSTACK_BLOCK_NAME
    #define CMB_CSTACK_BLOCK_NAME STACK
    #endif
    ...
#elif defined(__ICCARM__)
    /* C stack block name, default is'CSTACK' */
    #ifndef CMB_CSTACK_BLOCK_NAME
    #define CMB_CSTACK_BLOCK_NAME "CSTACK"
    #endif
    ...
#elif defined(__GNUC__)
    /* C stack block start address, defined on linker script file, default is _sstack */
    #ifndef CMB_CSTACK_BLOCK_START
    #define CMB_CSTACK_BLOCK_START _sstack
    #endif
    /* C stack block end address, defined on linker script file, default is _estack */
    #ifndef CMB_CSTACK_BLOCK_END
    #define CMB_CSTACK_BLOCK_END _estack
    #endif
    ...
#else
```

For example, under the Keil-MDK compiler, `STACK` will be selected as the name of the main stack block by default, but under some special platforms, the name of the main stack block of the project may not be called `STACK`, causing CmBacktrace to fail to obtain the correct main stack Information, so there will be the above error message during initialization.

There are generally two ways to solve this problem

 1. Redefine the main stack information in `cmb_cfg.h`. At this time, CmBacktrace will give priority to using the configuration information in `cmb_cfg.h`;
 2. Modify the project configuration. If it is Keil-MDK, change the name of the main stack to the default `STACK` at the beginning of the startup file. This problem rarely occurs with other compilers.

### 2.6 License

The MIT open source agreement is adopted. For details, please read the contents of the LICENSE file in the project.