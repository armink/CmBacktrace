#include <FreeRTOS.h>
#include <task.h>
#include <bsp.h>
#include <cm_backtrace.h>
#include <stdio.h>

#define HARDWARE_VERSION               "V1.0.0"
#define SOFTWARE_VERSION               "V0.1.0"

static void AppTaskStart(void *p_arg);
extern void fault_test_by_unalign(void);
extern void fault_test_by_div0(void);

int main(void)
{

    BSP_Init();    
    /* CmBacktrace initialize */
    cm_backtrace_init("CmBacktrace", HARDWARE_VERSION, SOFTWARE_VERSION);

    xTaskCreate( AppTaskStart, "app_start", 40, NULL, tskIDLE_PRIORITY+2, NULL );

    printf("System initialize finish. Starting..\r\n");
    
    vTaskStartScheduler();
       
    return (1);
}

static  void  AppTaskStart (void *p_arg)
{
//    fault_test_by_unalign();
    fault_test_by_div0();

    while (1) {
        LED_RUN_ON;
        vTaskDelay(500/portTICK_RATE_MS);
        LED_RUN_OFF;
        vTaskDelay(500/portTICK_RATE_MS);
    }
}
