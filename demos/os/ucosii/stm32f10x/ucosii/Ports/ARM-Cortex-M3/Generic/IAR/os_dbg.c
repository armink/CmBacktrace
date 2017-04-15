/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*                                          DEBUGGER CONSTANTS
*
*                                (c) Copyright 2006, Micrium, Weston, FL
*                                          All Rights Reserved
*
*                                           ARM Cortex-M3 Port
*
* File      : OS_DBG.C
* Version   : V2.89
* By        : Jean J. Labrosse
*
* For       : ARMv7M Cortex-M3
* Mode      : Thumb2
* Toolchain : IAR EWARM
*********************************************************************************************************
*/

#include <ucos_ii.h>

#define  OS_COMPILER_OPT  __root

/*
*********************************************************************************************************
*                                             DEBUG DATA
*********************************************************************************************************
*/

OS_COMPILER_OPT  INT16U  const  OSDebugEn           = OS_DEBUG_EN;               /* Debug constants are defined below   */

#if OS_DEBUG_EN > 0u

OS_COMPILER_OPT  INT32U  const  OSEndiannessTest    = 0x12345678L;               /* Variable to test CPU endianness     */

OS_COMPILER_OPT  INT16U  const  OSEventEn           = OS_EVENT_EN;
OS_COMPILER_OPT  INT16U  const  OSEventMax          = OS_MAX_EVENTS;             /* Number of event control blocks      */
OS_COMPILER_OPT  INT16U  const  OSEventNameEn       = OS_EVENT_NAME_EN;
#if (OS_EVENT_EN > 0u) && (OS_MAX_EVENTS > 0u)
OS_COMPILER_OPT  INT16U  const  OSEventSize         = sizeof(OS_EVENT);          /* Size in Bytes of OS_EVENT           */
OS_COMPILER_OPT  INT16U  const  OSEventTblSize      = sizeof(OSEventTbl);        /* Size of OSEventTbl[] in bytes       */
#else
OS_COMPILER_OPT  INT16U  const  OSEventSize         = 0u;
OS_COMPILER_OPT  INT16U  const  OSEventTblSize      = 0u;
#endif
OS_COMPILER_OPT  INT16U  const  OSEventMultiEn      = OS_EVENT_MULTI_EN;


OS_COMPILER_OPT  INT16U  const  OSFlagEn            = OS_FLAG_EN;
#if (OS_FLAG_EN > 0u) && (OS_MAX_FLAGS > 0u)
OS_COMPILER_OPT  INT16U  const  OSFlagGrpSize       = sizeof(OS_FLAG_GRP);       /* Size in Bytes of OS_FLAG_GRP        */
OS_COMPILER_OPT  INT16U  const  OSFlagNodeSize      = sizeof(OS_FLAG_NODE);      /* Size in Bytes of OS_FLAG_NODE       */
OS_COMPILER_OPT  INT16U  const  OSFlagWidth         = sizeof(OS_FLAGS);          /* Width (in bytes) of OS_FLAGS        */
#else
OS_COMPILER_OPT  INT16U  const  OSFlagGrpSize       = 0u;
OS_COMPILER_OPT  INT16U  const  OSFlagNodeSize      = 0u;
OS_COMPILER_OPT  INT16U  const  OSFlagWidth         = 0u;
#endif
OS_COMPILER_OPT  INT16U  const  OSFlagMax           = OS_MAX_FLAGS;
OS_COMPILER_OPT  INT16U  const  OSFlagNameEn        = OS_FLAG_NAME_EN;

OS_COMPILER_OPT  INT16U  const  OSLowestPrio        = OS_LOWEST_PRIO;

OS_COMPILER_OPT  INT16U  const  OSMboxEn            = OS_MBOX_EN;

OS_COMPILER_OPT  INT16U  const  OSMemEn             = OS_MEM_EN;
OS_COMPILER_OPT  INT16U  const  OSMemMax            = OS_MAX_MEM_PART;           /* Number of memory partitions         */
OS_COMPILER_OPT  INT16U  const  OSMemNameEn         = OS_MEM_NAME_EN;
#if (OS_MEM_EN > 0u) && (OS_MAX_MEM_PART > 0u)
OS_COMPILER_OPT  INT16U  const  OSMemSize           = sizeof(OS_MEM);            /* Mem. Partition header sine (bytes)  */
OS_COMPILER_OPT  INT16U  const  OSMemTblSize        = sizeof(OSMemTbl);
#else
OS_COMPILER_OPT  INT16U  const  OSMemSize           = 0u;
OS_COMPILER_OPT  INT16U  const  OSMemTblSize        = 0u;
#endif
OS_COMPILER_OPT  INT16U  const  OSMutexEn           = OS_MUTEX_EN;

OS_COMPILER_OPT  INT16U  const  OSPtrSize           = sizeof(void *);            /* Size in Bytes of a pointer          */

OS_COMPILER_OPT  INT16U  const  OSQEn               = OS_Q_EN;
OS_COMPILER_OPT  INT16U  const  OSQMax              = OS_MAX_QS;                 /* Number of queues                    */
#if (OS_Q_EN > 0u) && (OS_MAX_QS > 0u)
OS_COMPILER_OPT  INT16U  const  OSQSize             = sizeof(OS_Q);              /* Size in bytes of OS_Q structure     */
#else
OS_COMPILER_OPT  INT16U  const  OSQSize             = 0u;
#endif

OS_COMPILER_OPT  INT16U  const  OSRdyTblSize        = OS_RDY_TBL_SIZE;           /* Number of bytes in the ready table  */

OS_COMPILER_OPT  INT16U  const  OSSemEn             = OS_SEM_EN;

OS_COMPILER_OPT  INT16U  const  OSStkWidth          = sizeof(OS_STK);            /* Size in Bytes of a stack entry      */

OS_COMPILER_OPT  INT16U  const  OSTaskCreateEn      = OS_TASK_CREATE_EN;
OS_COMPILER_OPT  INT16U  const  OSTaskCreateExtEn   = OS_TASK_CREATE_EXT_EN;
OS_COMPILER_OPT  INT16U  const  OSTaskDelEn         = OS_TASK_DEL_EN;
OS_COMPILER_OPT  INT16U  const  OSTaskIdleStkSize   = OS_TASK_IDLE_STK_SIZE;
OS_COMPILER_OPT  INT16U  const  OSTaskProfileEn     = OS_TASK_PROFILE_EN;
OS_COMPILER_OPT  INT16U  const  OSTaskMax           = OS_MAX_TASKS + OS_N_SYS_TASKS; /* Total max. number of tasks      */
OS_COMPILER_OPT  INT16U  const  OSTaskNameEn        = OS_TASK_NAME_EN;
OS_COMPILER_OPT  INT16U  const  OSTaskStatEn        = OS_TASK_STAT_EN;
OS_COMPILER_OPT  INT16U  const  OSTaskStatStkSize   = OS_TASK_STAT_STK_SIZE;
OS_COMPILER_OPT  INT16U  const  OSTaskStatStkChkEn  = OS_TASK_STAT_STK_CHK_EN;
OS_COMPILER_OPT  INT16U  const  OSTaskSwHookEn      = OS_TASK_SW_HOOK_EN;

OS_COMPILER_OPT  INT16U  const  OSTCBPrioTblMax     = OS_LOWEST_PRIO + 1u;       /* Number of entries in OSTCBPrioTbl[] */
OS_COMPILER_OPT  INT16U  const  OSTCBSize           = sizeof(OS_TCB);            /* Size in Bytes of OS_TCB             */
OS_COMPILER_OPT  INT16U  const  OSTicksPerSec       = OS_TICKS_PER_SEC;
OS_COMPILER_OPT  INT16U  const  OSTimeTickHookEn    = OS_TIME_TICK_HOOK_EN;
OS_COMPILER_OPT  INT16U  const  OSVersionNbr        = OS_VERSION;

OS_COMPILER_OPT  INT16U  const  OSTmrEn             = OS_TMR_EN;
OS_COMPILER_OPT  INT16U  const  OSTmrCfgMax         = OS_TMR_CFG_MAX;
OS_COMPILER_OPT  INT16U  const  OSTmrCfgNameEn      = OS_TMR_CFG_NAME_EN;
OS_COMPILER_OPT  INT16U  const  OSTmrCfgWheelSize   = OS_TMR_CFG_WHEEL_SIZE;
OS_COMPILER_OPT  INT16U  const  OSTmrCfgTicksPerSec = OS_TMR_CFG_TICKS_PER_SEC;

#if (OS_TMR_EN > 0u) && (OS_TMR_CFG_MAX > 0u)
OS_COMPILER_OPT  INT16U  const  OSTmrSize           = sizeof(OS_TMR);
OS_COMPILER_OPT  INT16U  const  OSTmrTblSize        = sizeof(OSTmrTbl);
OS_COMPILER_OPT  INT16U  const  OSTmrWheelSize      = sizeof(OS_TMR_WHEEL);
OS_COMPILER_OPT  INT16U  const  OSTmrWheelTblSize   = sizeof(OSTmrWheelTbl);
#else
OS_COMPILER_OPT  INT16U  const  OSTmrSize           = 0u;
OS_COMPILER_OPT  INT16U  const  OSTmrTblSize        = 0u;
OS_COMPILER_OPT  INT16U  const  OSTmrWheelSize      = 0u;
OS_COMPILER_OPT  INT16U  const  OSTmrWheelTblSize   = 0u;
#endif

#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                             DEBUG DATA
*                            TOTAL DATA SPACE (i.e. RAM) USED BY uC/OS-II
*********************************************************************************************************
*/
#if OS_DEBUG_EN > 0u

OS_COMPILER_OPT  INT16U  const  OSDataSize = sizeof(OSCtxSwCtr)
#if (OS_EVENT_EN > 0u) && (OS_MAX_EVENTS > 0u)
                                           + sizeof(OSEventFreeList)
                                           + sizeof(OSEventTbl)
#endif
#if (OS_FLAG_EN > 0u) && (OS_MAX_FLAGS > 0u)
                                           + sizeof(OSFlagTbl)
                                           + sizeof(OSFlagFreeList)
#endif
#if OS_TASK_STAT_EN > 0u
                                           + sizeof(OSCPUUsage)
                                           + sizeof(OSIdleCtrMax)
                                           + sizeof(OSIdleCtrRun)
                                           + sizeof(OSStatRdy)
                                           + sizeof(OSTaskStatStk)
#endif
#if OS_TICK_STEP_EN > 0u
                                           + sizeof(OSTickStepState)
#endif
#if (OS_MEM_EN > 0u) && (OS_MAX_MEM_PART > 0u)
                                           + sizeof(OSMemFreeList)
                                           + sizeof(OSMemTbl)
#endif
#if (OS_Q_EN > 0u) && (OS_MAX_QS > 0u)
                                           + sizeof(OSQFreeList)
                                           + sizeof(OSQTbl)
#endif
#if OS_TIME_GET_SET_EN > 0u
                                           + sizeof(OSTime)
#endif
#if (OS_TMR_EN > 0u) && (OS_TMR_CFG_MAX > 0u)
                                           + sizeof(OSTmrFree)
                                           + sizeof(OSTmrUsed)
                                           + sizeof(OSTmrTime)
                                           + sizeof(OSTmrSem)
                                           + sizeof(OSTmrSemSignal)
                                           + sizeof(OSTmrFreeList)
                                           + sizeof(OSTmrTbl)
                                           + sizeof(OSTmrWheelTbl)
#endif
                                           + sizeof(OSIntNesting)
                                           + sizeof(OSLockNesting)
                                           + sizeof(OSPrioCur)
                                           + sizeof(OSPrioHighRdy)
                                           + sizeof(OSRdyGrp)
                                           + sizeof(OSRdyTbl)
                                           + sizeof(OSRunning)
                                           + sizeof(OSTaskCtr)
                                           + sizeof(OSIdleCtr)
                                           + sizeof(OSTaskIdleStk)
                                           + sizeof(OSTCBCur)
                                           + sizeof(OSTCBFreeList)
                                           + sizeof(OSTCBHighRdy)
                                           + sizeof(OSTCBList)
                                           + sizeof(OSTCBPrioTbl)
                                           + sizeof(OSTCBTbl);

#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                       OS DEBUG INITIALIZAZTION
*
* Description: This function is used to make sure that debug variables that are unused in the application
*              are not optimized away.  This function might not be necessary for all compilers.  In this
*              case, you should simply DELETE the code in this function while still leaving the declaration
*              of the function itself.
*
* Arguments  : none
*
* Returns    : none
*
* Note(s)    : (1) This code doesn't do anything, it simply prevents the compiler from optimizing out
*                  the 'const' variables which are declared in this file.
*********************************************************************************************************
*/

#if OS_DEBUG_EN > 0u
void  OSDebugInit (void)
{
    void  *ptemp;


    ptemp = (void *)&OSDebugEn;

    ptemp = (void *)&OSEndiannessTest;

    ptemp = (void *)&OSEventMax;
    ptemp = (void *)&OSEventNameEn;
    ptemp = (void *)&OSEventEn;
    ptemp = (void *)&OSEventSize;
    ptemp = (void *)&OSEventTblSize;
    ptemp = (void *)&OSEventMultiEn;

    ptemp = (void *)&OSFlagEn;
    ptemp = (void *)&OSFlagGrpSize;
    ptemp = (void *)&OSFlagNodeSize;
    ptemp = (void *)&OSFlagWidth;
    ptemp = (void *)&OSFlagMax;
    ptemp = (void *)&OSFlagNameEn;

    ptemp = (void *)&OSLowestPrio;

    ptemp = (void *)&OSMboxEn;

    ptemp = (void *)&OSMemEn;
    ptemp = (void *)&OSMemMax;
    ptemp = (void *)&OSMemNameEn;
    ptemp = (void *)&OSMemSize;
    ptemp = (void *)&OSMemTblSize;

    ptemp = (void *)&OSMutexEn;

    ptemp = (void *)&OSPtrSize;

    ptemp = (void *)&OSQEn;
    ptemp = (void *)&OSQMax;
    ptemp = (void *)&OSQSize;

    ptemp = (void *)&OSRdyTblSize;

    ptemp = (void *)&OSSemEn;

    ptemp = (void *)&OSStkWidth;

    ptemp = (void *)&OSTaskCreateEn;
    ptemp = (void *)&OSTaskCreateExtEn;
    ptemp = (void *)&OSTaskDelEn;
    ptemp = (void *)&OSTaskIdleStkSize;
    ptemp = (void *)&OSTaskProfileEn;
    ptemp = (void *)&OSTaskMax;
    ptemp = (void *)&OSTaskNameEn;
    ptemp = (void *)&OSTaskStatEn;
    ptemp = (void *)&OSTaskStatStkSize;
    ptemp = (void *)&OSTaskStatStkChkEn;
    ptemp = (void *)&OSTaskSwHookEn;

    ptemp = (void *)&OSTCBPrioTblMax;
    ptemp = (void *)&OSTCBSize;

    ptemp = (void *)&OSTicksPerSec;
    ptemp = (void *)&OSTimeTickHookEn;

#if OS_TMR_EN > 0u
    ptemp = (void *)&OSTmrTbl[0];
    ptemp = (void *)&OSTmrWheelTbl[0];

    ptemp = (void *)&OSTmrEn;
    ptemp = (void *)&OSTmrCfgMax;
    ptemp = (void *)&OSTmrCfgNameEn;
    ptemp = (void *)&OSTmrCfgWheelSize;
    ptemp = (void *)&OSTmrCfgTicksPerSec;
    ptemp = (void *)&OSTmrSize;
    ptemp = (void *)&OSTmrTblSize;

    ptemp = (void *)&OSTmrWheelSize;
    ptemp = (void *)&OSTmrWheelTblSize;
#endif

    ptemp = (void *)&OSVersionNbr;

    ptemp = (void *)&OSDataSize;

    ptemp = ptemp;                             /* Prevent compiler warning for 'ptemp' not being used! */
}
#endif
