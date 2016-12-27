#include <bsp.h>
#include <cm_backtrace.h>
#include <stdio.h>

#define HARDWARE_VERSION               "V1.0.0"
#define SOFTWARE_VERSION               "V0.1.0"

extern void fault_test_by_unalign(void);
extern void fault_test_by_div0(void);

int main(void){
    uint8_t _continue;
        
    BSP_Init();
    
    /* CmBacktrace initialize */
    cm_backtrace_init("CmBacktrace", HARDWARE_VERSION, SOFTWARE_VERSION);
    
//    fault_test_by_unalign();
    fault_test_by_div0();
    
    _continue = 1;
    while(_continue == 1) {
        LED_RUN_ON;
        delay(1000000);
        LED_RUN_OFF;
        delay(1000000);
    }
    
    return 0;
}
