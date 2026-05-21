
/**
 * @file replace_fault.c
 * @author fool_dog (2696652257@qq.com)
 * @brief 借助ARMLinker的$Super$$Sub$机制，替换Keil中的HardFault_Handler
 *            这样HAL库重新生成的时候不用注释掉HardFault_Handler,与cmb_fault.s二选一添加编译
 * @note 需要ARMLinker支持，Keil环境下使用
 * @version 1.0
 * @date 2024-08-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdint.h>

/* 声明一下老版本的HardFault_Handler */
extern void $Super$$HardFault_Handler(void);

extern void cm_backtrace_fault(uint32_t fault_handler_lr, uint32_t fault_handler_sp);

/* 新版本的HardFault_Handler */
__attribute__((used)) void $Sub$$HardFault_Handler(void)
{
    uint32_t lr, sp;

    __asm__ volatile(
        "mov %0, lr\n"
        "mov %1, sp\n"
        : "=r"(lr), "=r"(sp)
        :
        : "memory");

    /*  调用cm_backtrace_fault函数 */
    cm_backtrace_fault(lr, sp);

    /* 调用原来的HardFault_Handler */
    $Super$$HardFault_Handler();
}
