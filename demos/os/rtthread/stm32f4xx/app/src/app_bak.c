#include <ucos_ii.h>
#include <cpu_core.h>
#include <bsp.h>
#include <cm_backtrace.h>
#include <stdio.h>

#define HARDWARE_VERSION               "V1.0.0"
#define SOFTWARE_VERSION               "V0.1.0"

static  OS_STK          AppTaskStartStk[APP_TASK_START_STK_SIZE];

static void AppTaskStart(void *p_arg);
extern void fault_test_by_unalign(void);
extern void fault_test_by_div0(void);

int main(void)
{
    INT8U err;
    BSP_IntDisAll();
    BSP_Init();
    CPU_Init();
    OSInit();
    
    /* CmBacktrace initialize */
    cm_backtrace_init("CmBacktrace", HARDWARE_VERSION, SOFTWARE_VERSION);

    OSTaskCreateExt((void (*)(void *)) AppTaskStart,
                    (void           *) 0,
                    (OS_STK         *)&AppTaskStartStk[APP_TASK_START_STK_SIZE - 1],
                    (INT8U           ) APP_TASK_START_PRIO,
                    (INT16U          ) APP_TASK_START_PRIO,
                    (OS_STK         *)&AppTaskStartStk[0],
                    (INT32U          ) APP_TASK_START_STK_SIZE,
                    (void           *) 0,
                    (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
    
    OSTaskNameSet(APP_TASK_START_PRIO, "app_start", &err);

    printf("System initialize finish. Starting..\r\n");

    OSStart();
    
    return (1);
}

static  void  AppTaskStart (void *p_arg)
{
//    fault_test_by_unalign();
    fault_test_by_div0();

    while (DEF_TRUE) {
        LED_RUN_ON;
        OSTimeDlyHMSM(0, 0, 0, 500);
        LED_RUN_OFF;
        OSTimeDlyHMSM(0, 0, 0, 500);
    }
}
