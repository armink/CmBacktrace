/*
 * This file is part of the CmBacktrace Library.
 *
 * Copyright (c) 2016, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: It is the configure head file for this library.
 * Created on: 2016-12-15
 */

#ifndef _CMB_CFG_H_
#define _CMB_CFG_H_

/* ========================================================================== */
/*                              User Configuration                            */
/*                              用户配置区                                      */
/* ========================================================================== */

#ifdef CMB_USER_CFG
#include "cmb_user_cfg.h"
#else
	
/* include your RTOS header file, auto detection os platform,
 * Otherwise, the bare-metal platform will be used automatically
 */
// #include "rots.h"  

/*
 * Print output macro, must be configured by the user.
 * 打印输出宏，建议用户配置。
 *
 * For example / 例如：
 *   printf(__VA_ARGS__); printf("\r\n")
 * or / 或
 *   SEGGER_RTT_printf(0, __VA_ARGS__);
 *   SEGGER_RTT_WriteString(0, "\r\n")
 */
#define cmb_println(...)

/* Enable dump stack information. */
/* 启用堆栈信息转储。 */
#define CMB_USING_DUMP_STACK_INFO

/*
 * Language of print information.
 * 打印信息语言。
 *
 * Optional values / 可选值：
 *   CMB_PRINT_LANGUAGE_ENGLISH (default / 默认)
 *   CMB_PRINT_LANGUAGE_CHINESE
 *   CMB_PRINT_LANGUAGE_CHINESE_UTF8
 */
#define CMB_PRINT_LANGUAGE      CMB_PRINT_LANGUAGE_CHINESE

#endif /* CMB_USER_CFG */


/* ========================================================================== */
/*                    Platform Auto Detection (OS / Bare Metal)               */
/*                    平台自动识别区（OS / 裸机）                                 */
/* ========================================================================== */


/* auto enable OS platform  */
/* 根据宏存在自动 启用 OS 平台。 */
#if defined(RTTHREAD_VERSION) || defined(__RTTHREAD__) ||\
    defined(OS_USING_UCOSII) || defined(OS_UCOSII) ||\
    defined(OS_USING_UCOSIII) || defined(OS_UCOSIII) ||\
    defined(USE_FREERTOS) || defined(tskKERNEL_VERSION_NUMBER) ||\
    defined(USE_RTX5) || defined(RTX_VERSION) ||\
    defined(USE_THREADX) || defined(TX_VERSION_ID)
#define CMB_USING_OS_PLATFORM
#else
/* if platform no RTOS, then enable bare metal platform. */
/* 如果平台没有RTOS，则启用裸机平台。 */
#define CMB_USING_BARE_METAL_PLATFORM
#endif

/*
 * If already defined by the user manually, auto detection will be skipped.
 * 如果用户已经手动定义，则不再自动识别。
 */
#ifdef CMB_USING_OS_PLATFORM /* Platform Auto Detection / 平台自动识别 */
    #if defined(RTTHREAD_VERSION) || defined(__RTTHREAD__)
        #define CMB_OS_PLATFORM_TYPE    CMB_OS_PLATFORM_RTT
    #elif defined(OS_USING_UCOSII) || defined(OS_UCOSII)
        #define CMB_OS_PLATFORM_TYPE    CMB_OS_PLATFORM_UCOSII
    #elif defined(OS_USING_UCOSIII) || defined(OS_UCOSIII)
        #define CMB_OS_PLATFORM_TYPE    CMB_OS_PLATFORM_UCOSIII
    #elif defined(USE_FREERTOS) || defined(tskKERNEL_VERSION_NUMBER)
        #define CMB_OS_PLATFORM_TYPE    CMB_OS_PLATFORM_FREERTOS
    #elif defined(USE_RTX5) || defined(RTX_VERSION)
        #define CMB_OS_PLATFORM_TYPE    CMB_OS_PLATFORM_RTX5
    #elif defined(USE_THREADX) || defined(TX_VERSION_ID)
        #define CMB_OS_PLATFORM_TYPE    CMB_OS_PLATFORM_THREADX
    #else
        #error "Unrecognized OS platform, please define CMB_OS_PLATFORM_TYPE manually in cmb_cfg.h"
    #endif
#endif

/* ========================================================================== */
/*                          CPU Platform Auto Detection                       */
/*                          CPU 平台自动识别区                                  */
/* ========================================================================== */

/* Auto detect CPU platform type based on CMSIS __CORTEX_M macro. */
/* 根据 CMSIS 的 __CORTEX_M 宏自动判断 CPU 平台类型。 */
#ifdef USE_HAL_DRIVER
#include "main.h"
#endif

#ifndef CMB_CPU_PLATFORM_TYPE
    #if defined(__CORTEX_M) && (__CORTEX_M == 0)
        #define CMB_CPU_PLATFORM_TYPE    CMB_CPU_ARM_CORTEX_M0

    #elif defined(__CORTEX_M) && (__CORTEX_M == 3)
        #define CMB_CPU_PLATFORM_TYPE    CMB_CPU_ARM_CORTEX_M3

    #elif defined(__CORTEX_M) && (__CORTEX_M == 4)
        #define CMB_CPU_PLATFORM_TYPE    CMB_CPU_ARM_CORTEX_M4

    #elif defined(__CORTEX_M) && (__CORTEX_M == 7)
        #define CMB_CPU_PLATFORM_TYPE    CMB_CPU_ARM_CORTEX_M7

    #elif defined(__CORTEX_M) && (__CORTEX_M == 33)
        #define CMB_CPU_PLATFORM_TYPE    CMB_CPU_ARM_CORTEX_M33

    #else
        #error "Unrecognized Cortex-M core, please define CMB_CPU_PLATFORM_TYPE manually in cmb_cfg.h"
        #error "无法识别的 Cortex-M 内核，请手动在 cmb_cfg.h 中定义 CMB_CPU_PLATFORM_TYPE"
        /*
         * Optional values / 可选值：
         *   CMB_CPU_ARM_CORTEX_M0
         *   CMB_CPU_ARM_CORTEX_M3
         *   CMB_CPU_ARM_CORTEX_M4
         *   CMB_CPU_ARM_CORTEX_M7
         *   CMB_CPU_ARM_CORTEX_M33
         */
        #define CMB_CPU_PLATFORM_TYPE    CMB_CPU_ARM_CORTEX_M??
    #endif
#endif /* CMB_CPU_PLATFORM_TYPE */

/* Define __FUNCTION__ macro to get the current function name. */
/* 定义 __FUNCTION__ 宏，用于获取当前函数名。 */
#ifndef __FUNCTION__
#define __FUNCTION__    __func__
#endif

#endif /* _CMB_CFG_H_ */