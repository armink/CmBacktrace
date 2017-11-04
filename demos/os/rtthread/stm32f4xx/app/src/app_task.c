#include "app_task.h"
#include <stdlib.h>
#include <stdio.h>
#include <bsp.h>
#include <finsh.h>
#include <shell.h>
#include <delay_conf.h>
#include <cpuusage.h>
#include <utils.h>
#include <cm_backtrace.h>

#define thread_sys_monitor_prio        30
#define HARDWARE_VERSION               "V1.0.0"
#define SOFTWARE_VERSION               "V0.1.0"

extern void fault_test_by_unalign(void);
extern void fault_test_by_div0(void);

ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t thread_sys_monitor_stack[512];

struct rt_thread thread_sys_monitor;
uint8_t cpu_usage_major, cpu_usage_minor;

/**
 * System monitor thread.
 *
 * @param parameter parameter
 */
void thread_entry_sys_monitor(void* parameter)
{
    extern void cpu_usage_get(rt_uint8_t *major, rt_uint8_t *minor);

    /* CmBacktrace test */
//    fault_test_by_unalign();
    fault_test_by_div0();
    while (1)
    {
        if(get_system_status() == SYSTEM_STATUS_RUN){
            cpu_usage_get(&cpu_usage_major, &cpu_usage_minor);
            LED_RUN_ON;
            rt_thread_delay(DELAY_SYS_RUN_LED_ON);
            LED_RUN_OFF;
            rt_thread_delay(DELAY_SYS_RUN_LED_OFF);
        } else if (get_system_status() == SYSTEM_STATUS_INIT){
            LED_RUN_ON;
            rt_thread_delay(DELAY_SYS_INIT_LED_ON);
            LED_RUN_OFF;
            rt_thread_delay(DELAY_SYS_INIT_LED_OFF);
        } else if (get_system_status() == SYSTEM_STATUS_FAULT){
            LED_RUN_ON;
            rt_thread_delay(DELAY_SYS_FAULT_LED_ON);
            LED_RUN_OFF;
            rt_thread_delay(DELAY_SYS_FAULT_LED_OFF);
        }
        IWDG_Feed();
    }
}

static rt_err_t exception_hook(void *context) {
    extern long list_thread(void);
    uint8_t _continue = 1;

    rt_enter_critical();

#ifdef RT_USING_FINSH
    list_thread();
#endif

    cm_backtrace_fault(*((uint32_t *)(cmb_get_sp() + sizeof(uint32_t) * 8)), cmb_get_sp() + sizeof(uint32_t) * 9);

    while (_continue == 1);

    return RT_EOK;
}

/**
 * System initialization thread.
 *
 * @param parameter parameter
 */
void sys_init_thread(void* parameter){
    set_system_status(SYSTEM_STATUS_INIT);
    
    /* CmBacktrace initialize */
    cm_backtrace_init("CmBacktrace", HARDWARE_VERSION, SOFTWARE_VERSION);
    
    /* set exception hook */
    rt_hw_exception_install(exception_hook);

    /* initialize OK and switch to running status */
    set_system_status(SYSTEM_STATUS_RUN);

    rt_thread_delete(rt_thread_self());
}

int rt_application_init(void)
{
    rt_thread_t init_thread = NULL;
    rt_thread_init(&thread_sys_monitor,
                   "sys_monitor",
                   thread_entry_sys_monitor,
                   RT_NULL,
                   thread_sys_monitor_stack,
                   sizeof(thread_sys_monitor_stack),
                   thread_sys_monitor_prio, 5);
    rt_thread_startup(&thread_sys_monitor);

    init_thread = rt_thread_create("sys init", sys_init_thread,
            NULL, 512, 10, 10);
    if (init_thread != NULL) {
        rt_thread_startup(init_thread);
    }
    return 0;
}

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
    extern void cpu_usage_init(void);

    /* init board */
    rt_hw_board_init();

    /* show version */
    rt_show_version();

    /* init tick */
    rt_system_tick_init();

    /* init kernel object */
    rt_system_object_init();

    /* init timer system */
    rt_system_timer_init();

#ifdef RT_USING_HEAP
	/* init memory system */
	rt_system_heap_init((void*)STM32_SRAM_BEGIN, (void*)STM32_SRAM_END);
#endif

    /* init scheduler system */
    rt_system_scheduler_init();

    /* initialize timer */
    rt_system_timer_init();

    /* init timer thread */
    rt_system_timer_thread_init();

    /* Add CPU usage to system */
    cpu_usage_init();

#ifdef RT_USING_COMPONENTS_INIT
    /* initialization RT-Thread Components */
    rt_components_init();
#endif

#ifdef  RT_USING_FINSH
    /* init finsh */
    finsh_system_init();
    finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    /* initialization RT-Thread Components */
    rt_components_init();
#endif

    /* init application */
    rt_application_init();

    /* init idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return;
}

