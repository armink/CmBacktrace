#include "arch_interrupt.h"
#include "arch_exception.h"
#include "os_task.h"
#include <os_memory.h>
#include <os_spinlock.h>
#include <arch_interrupt.h>
#include "os_kernel_internal.h"
#include "os_errno.h"
#include "protocol.h"
#include "devdef.h"
#include "stdio.h"
#include "string.h"
#include <cm_backtrace.h>

void cm_backtrace_hard_fault_exception(uint32_t lr, uint32_t sp)
{
    os_meminfo_t info;

    OS_KERNEL_INIT();

    OS_KERNEL_ENTER();

    os_memory_info(&info);
    os_kprintf("\r\nmemory info:\r\n");
    os_kprintf("Used: %d    maxUsed: %d    total: %d\r\n\n", info.mem_used, info.mem_maxused, info.mem_total);

    sh_show_task_info();

    cm_backtrace_fault(*((uint32_t*)(cmb_get_sp() + sizeof(uint32_t) * 8)), cmb_get_sp() + sizeof(uint32_t) * 9);

    while (1);

    OS_KERNEL_EXIT();
}

os_err_t os_hw_hard_fault_exception_hook(void* context, os_size_t* msp, os_size_t* psp)
{

    cm_backtrace_hard_fault_exception(0, 0);

    return OS_EOK;
}

extern void os_hw_exception_install(os_err_t (*exception_handle)(void*, os_size_t*, os_size_t*));

int cmBacktrace_init(void)
{
    char hardware[10];

    memset(hardware, 0, sizeof(hardware));
    sprintf(hardware, "%d", DAYB_HARD_VER);

    /* CmBacktrace initialize */
    cm_backtrace_init("oneos", hardware, FIRMWARE_VERSION);

    /* set exception hook */
    os_hw_exception_install(os_hw_hard_fault_exception_hook);

    return OS_EOK;
}
OS_APP_INIT(cmBacktrace_init, OS_INIT_SUBLEVEL_LOW);