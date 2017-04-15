/*
*********************************************************************************************************
*                                                uC/CPU
*                                    CPU CONFIGURATION & PORT LAYER
*
*                          (c) Copyright 2004-2011; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/CPU is provided in source form to registered licensees ONLY.  It is
*               illegal to distribute this source code to any third party unless you receive
*               written permission by an authorized Micrium representative.  Knowledge of
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           CORE CPU MODULE
*
* Filename      : cpu_core.c
* Version       : V1.29.01
* Programmer(s) : SR
*                 ITJ
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#define    MICRIUM_SOURCE
#define    CPU_CORE_MODULE
#include  <cpu_core.h>


/*$PAGE*/
/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                  CPU COUNT LEAD ZEROs LOOKUP TABLE
*
* Note(s) : (1) Index into bit pattern table determines the number of leading zeros in an 8-bit value :
*
*                         b07  b06  b05  b04  b03  b02  b01  b00    # Leading Zeros
*                         ---  ---  ---  ---  ---  ---  ---  ---    ---------------
*                          1    x    x    x    x    x    x    x            0
*                          0    1    x    x    x    x    x    x            1
*                          0    0    1    x    x    x    x    x            2
*                          0    0    0    1    x    x    x    x            3
*                          0    0    0    0    1    x    x    x            4
*                          0    0    0    0    0    1    x    x            5
*                          0    0    0    0    0    0    1    x            6
*                          0    0    0    0    0    0    0    1            7
*                          0    0    0    0    0    0    0    0            8
*********************************************************************************************************
*/

#if (!(defined(CPU_CFG_LEAD_ZEROS_ASM_PRESENT)) || \
      (CPU_CFG_DATA_SIZE_MAX > CPU_CFG_DATA_SIZE))
static  const  CPU_INT08U  CPU_CntLeadZerosTbl[256] = {                             /* Data vals :                      */
/*   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F   */
    8u,  7u,  6u,  6u,  5u,  5u,  5u,  5u,  4u,  4u,  4u,  4u,  4u,  4u,  4u,  4u,  /*   0x00 to 0x0F                   */
    3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  /*   0x10 to 0x1F                   */
    2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  /*   0x20 to 0x2F                   */
    2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  /*   0x30 to 0x3F                   */
    1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  /*   0x40 to 0x4F                   */
    1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  /*   0x50 to 0x5F                   */
    1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  /*   0x60 to 0x6F                   */
    1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  /*   0x70 to 0x7F                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0x80 to 0x8F                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0x90 to 0x9F                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xA0 to 0xAF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xB0 to 0xBF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xC0 to 0xCF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xD0 to 0xDF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xE0 to 0xEF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u   /*   0xF0 to 0xFF                   */
};
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

#if    (CPU_CFG_NAME_EN   == DEF_ENABLED)                           /* ---------------- CPU NAME FNCTS ---------------- */
static  void        CPU_NameInit         (void);
#endif


                                                                    /* ----------------- CPU TS FNCTS ----------------- */
#if   ((CPU_CFG_TS_EN     == DEF_ENABLED) || \
       (CPU_CFG_TS_TMR_EN == DEF_ENABLED))
static  void        CPU_TS_Init          (void);
#endif


#ifdef  CPU_CFG_INT_DIS_MEAS_EN                                     /* ---------- CPU INT DIS TIME MEAS FNCTS --------- */
static  void        CPU_IntDisMeasInit   (void);

static  CPU_TS_TMR  CPU_IntDisMeasMaxCalc(CPU_TS_TMR  time_tot_cnts);
#endif


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*$PAGE*/
/*
*********************************************************************************************************
*                                             CPU_Init()
*
* Description : (1) Initialize CPU module :
*
*                   (a) Initialize CPU timestamps
*                   (b) Initialize CPU interrupts disabled time measurements
*                   (c) Initialize CPU host name
*
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Your Product's Application.
*
*               This function is a CPU initialization function & MAY be called by application/
*               initialization function(s).
*
* Note(s)     : (2) CPU_Init() MUST be called ... :
*
*                   (a) ONLY ONCE from a product's application; ...
*                   (b) BEFORE product's application calls any core CPU module function(s)
*
*               (3) The following initialization functions MUST be sequenced as follows :
*
*                   (a) CPU_TS_Init()           SHOULD precede ALL calls to other CPU timestamp functions
*
*                   (b) CPU_IntDisMeasInit()    SHOULD precede ALL calls to CPU_CRITICAL_ENTER()/CPU_CRITICAL_EXIT()
*                                                   & other CPU interrupts disabled time measurement functions
*********************************************************************************************************
*/

void  CPU_Init (void)
{
                                                                /* --------------------- INIT TS ---------------------- */
#if ((CPU_CFG_TS_EN     == DEF_ENABLED) || \
     (CPU_CFG_TS_TMR_EN == DEF_ENABLED))
    CPU_TS_Init();                                              /* See Note #3a.                                        */
#endif
                                                                /* -------------- INIT INT DIS TIME MEAS -------------- */
#ifdef  CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasInit();                                       /* See Note #3b.                                        */
#endif

                                                                /* ------------------ INIT CPU NAME ------------------- */
#if (CPU_CFG_NAME_EN == DEF_ENABLED)
     CPU_NameInit();
#endif
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                         CPU_SW_Exception()
*
* Description : Trap unrecoverable software exception.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : various.
*
* Note(s)     : (1) CPU_SW_Exception() deadlocks the current code execution -- whether multi-tasked/
*                   -processed/-threaded or single-threaded -- when the current code execution cannot 
*                   gracefully recover or report a fault or exception condition.
*
*                   See also 'cpu_core.h  CPU_SW_EXCEPTION()  Note #1'.
*********************************************************************************************************
*/

void  CPU_SW_Exception (void)
{
    while (DEF_ON) {
        ;
    }
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                            CPU_NameClr()
*
* Description : Clear CPU Name.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : CPU_NameInit(),
*               Application.
*
*               This function is a CPU module application programming interface (API) function & MAY be 
*               called by application function(s).
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (CPU_CFG_NAME_EN == DEF_ENABLED)
void  CPU_NameClr (void)
{
    CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();
    Mem_Clr((void     *)&CPU_Name[0],
            (CPU_SIZE_T) CPU_CFG_NAME_SIZE);
    CPU_CRITICAL_EXIT();
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                            CPU_NameGet()
*
* Description : Get CPU host name.
*
* Argument(s) : p_name      Pointer to an ASCII character array that will receive the return CPU host
*                               name ASCII string from this function (see Note #1).
*
*               p_err       Pointer to variable that will receive the return error code from this function :
*
*                               CPU_ERR_NONE                    CPU host name successfully returned.
*                               CPU_ERR_NULL_PTR                Argument 'p_name' passed a NULL pointer.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
*               This function is a CPU module application programming interface (API) function & MAY 
*               be called by application function(s).
*
* Note(s)     : (1) The size of the ASCII character array that will receive the return CPU host name
*                   ASCII string :
*
*                   (a) MUST   be greater than or equal to the current CPU host name's ASCII string
*                           size including the terminating NULL character;
*                   (b) SHOULD be greater than or equal to CPU_CFG_NAME_SIZE
*********************************************************************************************************
*/

#if (CPU_CFG_NAME_EN == DEF_ENABLED)
void  CPU_NameGet (CPU_CHAR  *p_name,
                   CPU_ERR   *p_err)
{
    CPU_SR_ALLOC();


    if (p_err == (CPU_ERR *)0) {
        CPU_SW_EXCEPTION(;);
    }

    if (p_name == (CPU_CHAR *)0) {
       *p_err = CPU_ERR_NULL_PTR;
        return;
    }

    CPU_CRITICAL_ENTER();
   (void)Str_Copy_N(p_name,
                   &CPU_Name[0],
                    CPU_CFG_NAME_SIZE);
    CPU_CRITICAL_EXIT();

   *p_err = CPU_ERR_NONE;
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                            CPU_NameSet()
*
* Description : Set CPU host name.
*
* Argument(s) : p_name      Pointer to CPU host name to set.
*
*               p_err       Pointer to variable that will receive the return error code from this function :
*
*                               CPU_ERR_NONE                    CPU host name successfully set.
*                               CPU_ERR_NULL_PTR                Argument 'p_name' passed a NULL pointer.
*                               CPU_ERR_NAME_SIZE               Invalid CPU host name size (see Note #1).
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
*               This function is a CPU module application programming interface (API) function & MAY be 
*               called by application function(s).
*
* Note(s)     : (1) 'p_name' ASCII string size, including the terminating NULL character, MUST be less
*                    than or equal to CPU_CFG_NAME_SIZE.
*********************************************************************************************************
*/

#if (CPU_CFG_NAME_EN == DEF_ENABLED)
void  CPU_NameSet (const  CPU_CHAR  *p_name,
                          CPU_ERR   *p_err)
{
    CPU_SIZE_T  len;
    CPU_SR_ALLOC();


    if (p_err == (CPU_ERR *)0) {
        CPU_SW_EXCEPTION(;);
    }

    if (p_name == (const CPU_CHAR *)0) {
       *p_err = CPU_ERR_NULL_PTR;
        return;
    }

    len = Str_Len_N(p_name,
                    CPU_CFG_NAME_SIZE);
    if (len < CPU_CFG_NAME_SIZE) {                              /* If       cfg name len < max name size, ...           */
        CPU_CRITICAL_ENTER();
       (void)Str_Copy_N(&CPU_Name[0],                           /* ... copy cfg name to CPU host name.                  */
                         p_name,
                         CPU_CFG_NAME_SIZE);
        CPU_CRITICAL_EXIT();
       *p_err = CPU_ERR_NONE;

    } else {
       *p_err = CPU_ERR_NAME_SIZE;
    }
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                           CPU_TS_Get32()
*
* Description : Get current 32-bit CPU timestamp.
*
* Argument(s) : none.
*
* Return(s)   : Current 32-bit CPU timestamp (in timestamp timer counts).
*
* Caller(s)   : Application.
*
*               This function is a CPU module application programming interface (API) function & MAY 
*               be called by application function(s).
*
* Note(s)     : (1) When applicable, the amount of time measured by CPU timestamps is calculated by
*                   either of the following equations :
*
*                       (a) Time measured  =  Number timer counts  *  Timer period
*
*                               where
*
*                                   Number timer counts     Number of timer counts measured
*                                   Timer period            Timer's period in some units of
*                                                               (fractional) seconds
*                                   Time measured           Amount of time measured, in same
*                                                               units of (fractional) seconds
*                                                               as the Timer period
*
*                                              Number timer counts
*                       (b) Time measured  =  ---------------------
*                                                Timer frequency
*
*                               where
*
*                                   Number timer counts     Number of timer counts measured
*                                   Timer frequency         Timer's frequency in some units
*                                                               of counts per second
*                                   Time measured           Amount of time measured, in seconds
*
*                   See also 'cpu_core.h  FUNCTION PROTOTYPES  CPU_TS_TmrRd()  Note #2c1'.
*
*               (2) In case the CPU timestamp timer has lower precision than the 32-bit CPU timestamp;
*                   its precision is extended via periodic updates by accumulating the deltas of the
*                   timestamp timer count values into the higher-precision 32-bit CPU timestamp.
*
*               (3) After initialization, 'CPU_TS_32_Accum' & 'CPU_TS_32_TmrPrev' MUST ALWAYS
*                   be accessed AND updated exclusively with interrupts disabled -- but NOT
*                   with critical sections.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_32_EN == DEF_ENABLED)
CPU_TS32  CPU_TS_Get32 (void)
{
    CPU_TS32    ts;
#if (CPU_CFG_TS_TMR_SIZE <  CPU_WORD_SIZE_32)
    CPU_TS_TMR  tmr_cur;
    CPU_TS_TMR  tmr_delta;
    CPU_SR_ALLOC();
#endif


#if (CPU_CFG_TS_TMR_SIZE >= CPU_WORD_SIZE_32)
    ts = (CPU_TS32)CPU_TS_TmrRd();                                  /* Get cur ts tmr val (in 32-bit ts cnts).          */

#else
    CPU_INT_DIS();
    tmr_cur            = (CPU_TS_TMR) CPU_TS_TmrRd();               /* Get cur ts tmr val (in ts tmr cnts).             */
    tmr_delta          = (CPU_TS_TMR)(tmr_cur - CPU_TS_32_TmrPrev); /* Calc      delta ts tmr cnts.                     */
    CPU_TS_32_Accum   += (CPU_TS32  ) tmr_delta;                    /* Inc ts by delta ts tmr cnts (see Note #2).       */
    CPU_TS_32_TmrPrev  = (CPU_TS_TMR) tmr_cur;                      /* Save cur ts tmr cnts for next update.            */
    ts                 = (CPU_TS32  ) CPU_TS_32_Accum;
    CPU_INT_EN();
#endif

    return (ts);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                           CPU_TS_Get64()
*
* Description : Get current 64-bit CPU timestamp.
*
* Argument(s) : none.
*
* Return(s)   : Current 64-bit CPU timestamp (in timestamp timer counts).
*
* Caller(s)   : Application.
*
*               This function is a CPU module application programming interface (API) function & MAY 
*               be called by application function(s).
*
* Note(s)     : (1) When applicable, the amount of time measured by CPU timestamps is calculated by
*                   either of the following equations :
*
*                       (a) Time measured  =  Number timer counts  *  Timer period
*
*                               where
*
*                                   Number timer counts     Number of timer counts measured
*                                   Timer period            Timer's period in some units of
*                                                               (fractional) seconds
*                                   Time measured           Amount of time measured, in same
*                                                               units of (fractional) seconds
*                                                               as the Timer period
*
*                                              Number timer counts
*                       (b) Time measured  =  ---------------------
*                                                Timer frequency
*
*                               where
*
*                                   Number timer counts     Number of timer counts measured
*                                   Timer frequency         Timer's frequency in some units
*                                                               of counts per second
*                                   Time measured           Amount of time measured, in seconds
*
*                   See also 'cpu_core.h  FUNCTION PROTOTYPES  CPU_TS_TmrRd()  Note #2c1'.
*
*               (2) In case the CPU timestamp timer has lower precision than the 64-bit CPU timestamp;
*                   its precision is extended via periodic updates by accumulating the deltas of the
*                   timestamp timer count values into the higher-precision 64-bit CPU timestamp.
*
*               (3) After initialization, 'CPU_TS_64_Accum' & 'CPU_TS_64_TmrPrev' MUST ALWAYS
*                   be accessed AND updated exclusively with interrupts disabled -- but NOT
*                   with critical sections.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_64_EN == DEF_ENABLED)
CPU_TS64  CPU_TS_Get64 (void)
{
    CPU_TS64    ts;
#if (CPU_CFG_TS_TMR_SIZE <  CPU_WORD_SIZE_64)
    CPU_TS_TMR  tmr_cur;
    CPU_TS_TMR  tmr_delta;
    CPU_SR_ALLOC();
#endif


#if (CPU_CFG_TS_TMR_SIZE >= CPU_WORD_SIZE_64)
    ts = (CPU_TS64)CPU_TS_TmrRd();                                  /* Get cur ts tmr val (in 64-bit ts cnts).          */

#else
    CPU_INT_DIS();
    tmr_cur            = (CPU_TS_TMR) CPU_TS_TmrRd();               /* Get cur ts tmr val (in ts tmr cnts).             */
    tmr_delta          = (CPU_TS_TMR)(tmr_cur - CPU_TS_64_TmrPrev); /* Calc      delta ts tmr cnts.                     */
    CPU_TS_64_Accum   += (CPU_TS64  ) tmr_delta;                    /* Inc ts by delta ts tmr cnts (see Note #2).       */
    CPU_TS_64_TmrPrev  = (CPU_TS_TMR) tmr_cur;                      /* Save cur ts tmr cnts for next update.            */
    ts                 = (CPU_TS64  ) CPU_TS_64_Accum;
    CPU_INT_EN();
#endif

    return (ts);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                           CPU_TS_Update()
*
* Description : Update current CPU timestamp(s).
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application/BSP periodic time handler (see Note #1).
*
*               This function is a CPU timestamp BSP function & SHOULD be called only by appropriate
*               application/BSP function(s).
*
* Note(s)     : (1) (a) CPU timestamp(s) MUST be updated periodically by some application (or BSP) time
*                       handler in order to (adequately) maintain CPU timestamp(s)' time.
*
*                   (b) CPU timestamp(s) MUST be updated more frequently than the CPU timestamp timer
*                       overflows; otherwise, CPU timestamp(s) will lose time.
*
*                       See also 'cpu_core.h  FUNCTION PROTOTYPES  CPU_TS_TmrRd()  Note #2c2'.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_EN == DEF_ENABLED)
void  CPU_TS_Update (void)
{
#if ((CPU_CFG_TS_32_EN    == DEF_ENABLED)  && \
     (CPU_CFG_TS_TMR_SIZE <  CPU_WORD_SIZE_32))
   (void)CPU_TS_Get32();
#endif

#if ((CPU_CFG_TS_64_EN    == DEF_ENABLED)  && \
     (CPU_CFG_TS_TMR_SIZE <  CPU_WORD_SIZE_64))
   (void)CPU_TS_Get64();
#endif
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                         CPU_TS_TmrFreqGet()
*
* Description : Get CPU timestamp's timer frequency.
*
* Argument(s) : p_err       Pointer to variable that will receive the return error code from this function :
*
*                               CPU_ERR_NONE                    CPU timestamp's timer frequency successfully
*                                                                   returned.
*                               CPU_ERR_TS_FREQ_INVALID         CPU timestamp's timer frequency invalid &/or
*                                                                   NOT yet configured.
*
* Return(s)   : CPU timestamp's timer frequency (in Hertz), if NO error(s).
*
*               0,                                          otherwise.
*
* Caller(s)   : Application.
*
*               This function is a CPU module application programming interface (API) function & MAY be 
*               called by application function(s).
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
CPU_TS_TMR_FREQ  CPU_TS_TmrFreqGet (CPU_ERR  *p_err)
{
    CPU_TS_TMR_FREQ  freq_hz;


    if (p_err == (CPU_ERR *)0) {
        CPU_SW_EXCEPTION(;);
    }

    freq_hz =  CPU_TS_TmrFreq_Hz;
   *p_err   = (freq_hz != 0u) ? CPU_ERR_NONE : CPU_ERR_TS_FREQ_INVALID;

    return (freq_hz);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                         CPU_TS_TmrFreqSet()
*
* Description : Set CPU timestamp's timer frequency.
*
* Argument(s) : freq_hz     Frequency (in Hertz) to set for CPU timestamp's timer.
*
* Return(s)   : none.
*
* Caller(s)   : CPU_TS_TmrInit(),
*               Application/BSP initialization function(s).
*
*               This function is a CPU module BSP function & SHOULD be called only by appropriate
*               application/BSP function(s) [see Note #1].
*
* Note(s)     : (1) (a) (1) CPU timestamp timer frequency is NOT required for internal CPU timestamp
*                           operations but may OPTIONALLY be configured by CPU_TS_TmrInit() or other
*                           application/BSP initialization functions.
*
*                       (2) CPU timestamp timer frequency MAY be used with optional CPU_TSxx_to_uSec()
*                           to convert CPU timestamps from timer counts into microseconds.
*
*                           See also 'cpu_core.h  FUNCTION PROTOTYPES  CPU_TSxx_to_uSec()  Note #2a'.
*
*                   (b) CPU timestamp timer period SHOULD be less than the typical measured time but MUST
*                       be less than the maximum measured time; otherwise, timer resolution inadequate to
*                       measure desired times.
*
*                       See also 'cpu_core.h  FUNCTION PROTOTYPES  CPU_TSxx_to_uSec()  Note #2b'.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
void  CPU_TS_TmrFreqSet (CPU_TS_TMR_FREQ  freq_hz)
{
    CPU_TS_TmrFreq_Hz = freq_hz;
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                     CPU_IntDisMeasMaxCurReset()
*
* Description : Reset current maximum interrupts disabled time.
*
* Argument(s) : none.
*
* Return(s)   : Maximum interrupts disabled time (in CPU timestamp timer counts) before resetting.
*
*               See also 'cpu_core.h  FUNCTION PROTOTYPES  CPU_TS_TmrRd()      Note #2c'
*                      & 'cpu_core.h  FUNCTION PROTOTYPES  CPU_TSxx_to_uSec()  Note #2'.
*
* Caller(s)   : Application.
*
*               This function is a CPU module application programming interface (API) function 
*               & MAY be called by application function(s).
*
* Note(s)     : (1) After initialization, 'CPU_IntDisMeasMaxCur_cnts' MUST ALWAYS be accessed
*                   exclusively with interrupts disabled -- but NOT with critical sections.
*********************************************************************************************************
*/

#ifdef  CPU_CFG_INT_DIS_MEAS_EN
CPU_TS_TMR  CPU_IntDisMeasMaxCurReset (void)
{
    CPU_TS_TMR  time_max_cnts;
    CPU_SR_ALLOC();


    time_max_cnts             = CPU_IntDisMeasMaxCurGet();
    CPU_INT_DIS();
    CPU_IntDisMeasMaxCur_cnts = 0u;
    CPU_INT_EN();

    return (time_max_cnts);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                      CPU_IntDisMeasMaxCurGet()
*
* Description : Get current maximum interrupts disabled time.
*
* Argument(s) : none.
*
* Return(s)   : Current maximum interrupts disabled time (in CPU timestamp timer counts).
*
*               See also 'cpu_core.h  FUNCTION PROTOTYPES  CPU_TS_TmrRd()      Note #2c'
*                      & 'cpu_core.h  FUNCTION PROTOTYPES  CPU_TSxx_to_uSec()  Note #2'.
*
* Caller(s)   : CPU_IntDisMeasMaxCurReset(),
*               Application.
*
*               This function is a CPU module application programming interface (API) function 
*               & MAY be called by application function(s).
*
* Note(s)     : (1) After initialization, 'CPU_IntDisMeasMaxCur_cnts' MUST ALWAYS be accessed
*                   exclusively with interrupts disabled -- but NOT with critical sections.
*********************************************************************************************************
*/

#ifdef  CPU_CFG_INT_DIS_MEAS_EN
CPU_TS_TMR  CPU_IntDisMeasMaxCurGet (void)
{
    CPU_TS_TMR  time_tot_cnts;
    CPU_TS_TMR  time_max_cnts;
    CPU_SR_ALLOC();


    CPU_INT_DIS();
    time_tot_cnts = CPU_IntDisMeasMaxCur_cnts;
    CPU_INT_EN();
    time_max_cnts = CPU_IntDisMeasMaxCalc(time_tot_cnts);

    return (time_max_cnts);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                       CPU_IntDisMeasMaxGet()
*
* Description : Get (non-resetable) maximum interrupts disabled time.
*
* Argument(s) : none.
*
* Return(s)   : (Non-resetable) maximum interrupts disabled time (in CPU timestamp timer counts).
*
*               See also 'cpu_core.h  FUNCTION PROTOTYPES  CPU_TS_TmrRd()      Note #2c'
*                      & 'cpu_core.h  FUNCTION PROTOTYPES  CPU_TSxx_to_uSec()  Note #2'.
*
* Caller(s)   : CPU_IntDisMeasInit(),
*               Application.
*
*               This function is a CPU module application programming interface (API) function 
*               & MAY be called by application function(s).
*
* Note(s)     : (1) After initialization, 'CPU_IntDisMeasMax_cnts' MUST ALWAYS be accessed
*                   exclusively with interrupts disabled -- but NOT with critical sections.
*********************************************************************************************************
*/

#ifdef  CPU_CFG_INT_DIS_MEAS_EN
CPU_TS_TMR  CPU_IntDisMeasMaxGet (void)
{
    CPU_TS_TMR  time_tot_cnts;
    CPU_TS_TMR  time_max_cnts;
    CPU_SR_ALLOC();


    CPU_INT_DIS();
    time_tot_cnts = CPU_IntDisMeasMax_cnts;
    CPU_INT_EN();
    time_max_cnts = CPU_IntDisMeasMaxCalc(time_tot_cnts);

    return (time_max_cnts);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CPU_IntDisMeasStart()
*
* Description : Start interrupts disabled time measurement.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : CPU_CRITICAL_ENTER().
*
*               This function is an INTERNAL CPU module function & MUST NOT be called by application
*               function(s).
*
* Note(s)     : none.
*********************************************************************************************************
*/

#ifdef  CPU_CFG_INT_DIS_MEAS_EN
void  CPU_IntDisMeasStart (void)
{
    CPU_IntDisMeasCtr++;
    if (CPU_IntDisNestCtr == 0u) {                                  /* If ints NOT yet dis'd, ...                       */
        CPU_IntDisMeasStart_cnts = CPU_TS_TmrRd();                  /* ... get ints dis'd start time.                   */
    }
    CPU_IntDisNestCtr++;
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CPU_IntDisMeasStop()
*
* Description : Stop interrupts disabled time measurement.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : CPU_CRITICAL_EXIT().
*
*               This function is an INTERNAL CPU module function & MUST NOT be called by application
*               function(s).
*
* Note(s)     : (1) (a) The total amount of time interrupts are disabled by system &/or application code
*                       during critical sections is calculated by the following equations :
*
*                       (1) When interrupts disabled time measurements are disabled :
*
*
*                               |   CRITICAL  |                           |   CRITICAL  |
*                               |<- SECTION ->|                           |<- SECTION ->|
*                               |    ENTER    |                           |    EXIT     |
*
*                            Disable                                    Enable
*                           Interrupts                                Interrupts
*
*                               ||           ||                           ||           ||
*                               ||           ||                           ||           ||
*                               ||       |   ||<------------------------->||       |   ||
*                               ||       |<->||             |             ||<----->|   ||
*                               ||       | | ||             |             ||   |   |   ||
*                                        | |                |                  |   |
*                                   interrupts            time                 interrupts
*                                    disabled                 interrupts       |enabled
*                                          |                   disabled        |
*                                          |              (via application)    |
*                                       time                                 time
*                                           interrupts                           interrupts
*                                         disabled ovrhd                        enabled ovrhd
*
*
*                           (A) time            =  [ time            -  time           ]  -  time
*                                   interrupts     [     interrupts         interrupts ]         total
*                                    disabled      [      enabled            disabled  ]         ovrhd
*                               (via application)
*
*
*                           (B) time       =  time              +  time
*                                   total         interrupts           interrupts
*                                   ovrhd        enabled ovrhd       disabled ovrhd
*
*
*                                   where
*
*                                           time                    time interrupts are disabled between
*                                               interrupts              first critical section enter &
*                                                disabled               last  critical section exit (i.e.
*                                           (via application)           minus total overhead time)
*
*                                           time                    time when interrupts are disabled
*                                               interrupts
*                                                disabled
*
*                                           time                    time when interrupts are  enabled
*                                               interrupts
*                                                enabled
*
*
*                                           time                    total overhead time to disable/enable
*                                               total                   interrupts during critical section
*                                               ovrhd                   enter & exit
*
*                                           time                    total overhead time to disable interrupts
*                                               interrupts              during critical section enter
*                                             disabled ovrhd
*
*                                           time                    total overhead time to enable  interrupts
*                                               interrupts              during critical section exit
*                                              enabled ovrhd
*
*$PAGE*
*
*                       (2) When interrupts disabled time measurements are enabled :
*
*
*        |                                    |                           |                                       |
*        |<----- CRITICAL SECTION ENTER ----->|                           |<------- CRITICAL SECTION EXIT ------->|
*        |                                    |                           |                                       |
*
*                   Time                                                 Time
*     Disable    Measurement                                          Measurement                  Enable
*    Interrupts     Start                                                Stop                    Interrupts
*
*        ||           |                      ||                           ||                         |           ||
*        ||           |                      ||                           ||                         |           ||
*        ||           |        |             ||<------------------------->||               |         |           ||
*        ||       |   |        |<----------->||             |             ||<------------->|         |       |   ||
*        ||       |   |        |      |      ||             |             ||       |       |         |       |   ||
*                 |            |      |                     |                      |       |                 |
*            interrupts       get     |                   time                     |      get            interrupts
*             disabled    start time  |                       interrupts           |   stop time          enabled
*                            meas     |                        disabled            |     meas
*                                   time                  (via application)      time
*                                       start meas                                   stop meas
*                                         ovrhd                                        ovrhd
*
*
*                           (A) time            =  [ time       -  time      ]  -  time
*                                   interrupts     [      stop         start ]         total meas
*                                    disabled      [      meas         meas  ]           ovrhd
*                               (via application)
*
*
*                           (B) time            =  time            +  time
*                                   total meas         start meas         stop meas
*                                     ovrhd              ovrhd              ovrhd
*
*
*                                   where
*
*                                           time                    time interrupts are disabled between first
*                                               interrupts              critical section enter & last critical
*                                                disabled               section exit (i.e. minus measurement
*                                           (via application)           overhead time; however, this does NOT
*                                                                       include any overhead time to disable
*                                                                       or enable interrupts during critical
*                                                                       section enter & exit)
*
*                                           time                    time of disable interrupts start time
*                                               start                   measurement (in timer counts)
*                                               meas
*
*                                           time                    time of disable interrupts stop  time
*                                               stop                    measurement (in timer counts)
*                                               meas
*
*
*                                           time                    total overhead time to start/stop disabled
*                                               total meas              interrupts time measurements (in timer
*                                                 ovrhd                 counts)
*
*                                           time                    total overhead time after getting start
*                                               start meas              time until end of start measurement
*                                                 ovrhd                 function  (in timer counts)
*
*                                           time                    total overhead time from beginning of stop
*                                               stop meas               measurement function until after getting
*                                                 ovrhd                 stop time (in timer counts)
*
*
*$PAGE*
*                   (b) (1) (A) In order to correctly handle unsigned subtraction overflows of start times 
*                               from stop times, CPU timestamp timer count values MUST be returned via 
*                               word-size-configurable 'CPU_TS_TMR' data type.
*
*                               See also 'cpu_core.h  FUNCTION PROTOTYPES  CPU_TS_TmrRd()  Note #2a'.
*
*                           (B) Since unsigned subtraction of start times from stop times assumes increasing
*                               values, timestamp timer count values MUST increase with each time count.
*
*                               See also 'cpu_core.h  FUNCTION PROTOTYPES  CPU_TS_TmrRd()  Note #2b'.
*
*                       (2) (A) To expedite & reduce interrupts disabled time measurement overhead; only the
*                               subtraction of start times from stop times is performed.
*
*                           (B) The final calculations to subtract the interrupts disabled time measurement
*                               overhead is performed asynchronously in appropriate API functions.
*
*                               See also 'CPU_IntDisMeasMaxCalc()  Note #1b'.
*********************************************************************************************************
*/

#ifdef  CPU_CFG_INT_DIS_MEAS_EN
void  CPU_IntDisMeasStop (void)
{
    CPU_TS_TMR  time_ints_disd_cnts;


    CPU_IntDisNestCtr--;
    if (CPU_IntDisNestCtr == 0u) {                                  /* If ints NO longer dis'd,        ...              */
        CPU_IntDisMeasStop_cnts = CPU_TS_TmrRd();                   /* ... get  ints dis'd stop time & ...              */
                                                                    /* ... calc ints dis'd tot  time (see Note #1b2A).  */
        time_ints_disd_cnts     = CPU_IntDisMeasStop_cnts -
                                  CPU_IntDisMeasStart_cnts;
                                                                    /* Calc max ints dis'd times.                       */
        if (CPU_IntDisMeasMaxCur_cnts < time_ints_disd_cnts) {
            CPU_IntDisMeasMaxCur_cnts = time_ints_disd_cnts;
        }
        if (CPU_IntDisMeasMax_cnts    < time_ints_disd_cnts) {
            CPU_IntDisMeasMax_cnts    = time_ints_disd_cnts;
        }
    }
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                         CPU_CntLeadZeros()
*
* Description : Count the number of contiguous, most-significant, leading zero bits in a data value.
*
* Argument(s) : val         Data value to count leading zero bits.
*
* Return(s)   : Number of contiguous, most-significant, leading zero bits in 'val', if NO error(s).
*
*               DEF_INT_CPU_U_MAX_VAL,                                              otherwise.
*
* Caller(s)   : CPU_CntTrailZeros(),
*               Application.
*
*               This function is a CPU module application programming interface (API) function & MAY 
*               be called by application function(s).
*
* Note(s)     : (1) (a) Supports the following data value sizes :
*
*                       (1)  8-bits
*                       (2) 16-bits
*                       (3) 32-bits
*                       (4) 64-bits
*
*                       See also 'cpu_def.h  CPU WORD CONFIGURATION  Note #1'.
*
*                   (b) (1) For  8-bit values :
*
*                                  b07  b06  b05  b04  b03  b02  b01  b00    # Leading Zeros
*                                  ---  ---  ---  ---  ---  ---  ---  ---    ---------------
*                                   1    x    x    x    x    x    x    x            0
*                                   0    1    x    x    x    x    x    x            1
*                                   0    0    1    x    x    x    x    x            2
*                                   0    0    0    1    x    x    x    x            3
*                                   0    0    0    0    1    x    x    x            4
*                                   0    0    0    0    0    1    x    x            5
*                                   0    0    0    0    0    0    1    x            6
*                                   0    0    0    0    0    0    0    1            7
*                                   0    0    0    0    0    0    0    0            8
*
*
*                       (2) For 16-bit values :
*
*                             b15  b14  b13  ...  b04  b03  b02  b01  b00    # Leading Zeros
*                             ---  ---  ---       ---  ---  ---  ---  ---    ---------------
*                              1    x    x         x    x    x    x    x            0
*                              0    1    x         x    x    x    x    x            1
*                              0    0    1         x    x    x    x    x            2
*                              :    :    :         :    :    :    :    :            :
*                              :    :    :         :    :    :    :    :            :
*                              0    0    0         1    x    x    x    x           11
*                              0    0    0         0    1    x    x    x           12
*                              0    0    0         0    0    1    x    x           13
*                              0    0    0         0    0    0    1    x           14
*                              0    0    0         0    0    0    0    1           15
*                              0    0    0         0    0    0    0    0           16
*
*$PAGE*
*                       (3) For 32-bit values :
*
*                             b31  b30  b29  ...  b04  b03  b02  b01  b00    # Leading Zeros
*                             ---  ---  ---       ---  ---  ---  ---  ---    ---------------
*                              1    x    x         x    x    x    x    x            0
*                              0    1    x         x    x    x    x    x            1
*                              0    0    1         x    x    x    x    x            2
*                              :    :    :         :    :    :    :    :            :
*                              :    :    :         :    :    :    :    :            :
*                              0    0    0         1    x    x    x    x           27
*                              0    0    0         0    1    x    x    x           28
*                              0    0    0         0    0    1    x    x           29
*                              0    0    0         0    0    0    1    x           30
*                              0    0    0         0    0    0    0    1           31
*                              0    0    0         0    0    0    0    0           32
*
*
*                       (4) For 64-bit values :
*
*                             b63  b62  b61  ...  b04  b03  b02  b01  b00    # Leading Zeros
*                             ---  ---  ---       ---  ---  ---  ---  ---    ---------------
*                              1    x    x         x    x    x    x    x            0
*                              0    1    x         x    x    x    x    x            1
*                              0    0    1         x    x    x    x    x            2
*                              :    :    :         :    :    :    :    :            :
*                              :    :    :         :    :    :    :    :            :
*                              0    0    0         1    x    x    x    x           59
*                              0    0    0         0    1    x    x    x           60
*                              0    0    0         0    0    1    x    x           61
*                              0    0    0         0    0    0    1    x           62
*                              0    0    0         0    0    0    0    1           63
*                              0    0    0         0    0    0    0    0           64
*
*
*                       See also 'CPU COUNT LEAD ZEROs LOOKUP TABLE  Note #1'.
*********************************************************************************************************
*/

#ifndef   CPU_CFG_LEAD_ZEROS_ASM_PRESENT
CPU_DATA  CPU_CntLeadZeros (CPU_DATA  val)
{
    CPU_DATA  nbr_lead_zeros;


#if   (CPU_CFG_DATA_SIZE == CPU_WORD_SIZE_08)
    nbr_lead_zeros = CPU_CntLeadZeros08((CPU_INT08U)val);

#elif (CPU_CFG_DATA_SIZE == CPU_WORD_SIZE_16)
    nbr_lead_zeros = CPU_CntLeadZeros16((CPU_INT16U)val);

#elif (CPU_CFG_DATA_SIZE == CPU_WORD_SIZE_32)
    nbr_lead_zeros = CPU_CntLeadZeros32((CPU_INT32U)val);

#elif (CPU_CFG_DATA_SIZE == CPU_WORD_SIZE_64)
    nbr_lead_zeros = CPU_CntLeadZeros64((CPU_INT64U)val);

#else                                                           /* See Note #1a.                                        */
    nbr_lead_zeros = DEF_INT_CPU_U_MAX_VAL;
#endif


    return (nbr_lead_zeros);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CPU_CntLeadZeros08()
*
* Description : Count the number of contiguous, most-significant, leading zero bits in an 8-bit data value.
*
* Argument(s) : val         Data value to count leading zero bits.
*
* Return(s)   : Number of contiguous, most-significant, leading zero bits in 'val'.
*
* Caller(s)   : CPU_CntLeadZeros(),
*               CPU_CntTrailZeros08(),
*               Application.
*
*               This function is a CPU module application programming interface (API) function & MAY be 
*               called by application function(s).
*
* Note(s)     : (1) Supports  8-bit values :
*
*                               b07  b06  b05  b04  b03  b02  b01  b00    # Leading Zeros
*                               ---  ---  ---  ---  ---  ---  ---  ---    ---------------
*                                1    x    x    x    x    x    x    x            0
*                                0    1    x    x    x    x    x    x            1
*                                0    0    1    x    x    x    x    x            2
*                                0    0    0    1    x    x    x    x            3
*                                0    0    0    0    1    x    x    x            4
*                                0    0    0    0    0    1    x    x            5
*                                0    0    0    0    0    0    1    x            6
*                                0    0    0    0    0    0    0    1            7
*                                0    0    0    0    0    0    0    0            8
*
*
*                   See also 'CPU COUNT LEAD ZEROs LOOKUP TABLE  Note #1'.
*********************************************************************************************************
*/

#if (CPU_CFG_DATA_SIZE_MAX >= CPU_WORD_SIZE_08)
CPU_DATA  CPU_CntLeadZeros08 (CPU_INT08U  val)
{
#if  (!((defined(CPU_CFG_LEAD_ZEROS_ASM_PRESENT)) && \
        (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_08)))
    CPU_DATA  ix;
#endif
    CPU_DATA  nbr_lead_zeros;

                                                                                /* ---------- ASM-OPTIMIZED ----------- */
#if ((defined(CPU_CFG_LEAD_ZEROS_ASM_PRESENT)) && \
     (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_08))
    nbr_lead_zeros  =  CPU_CntLeadZeros((CPU_DATA)val);
    nbr_lead_zeros -= (CPU_CFG_DATA_SIZE - CPU_WORD_SIZE_08) * DEF_OCTET_NBR_BITS;


#else                                                                           /* ----------- C-OPTIMIZED ------------ */
                                                                                /* Chk bits [07:00] :                   */
                                                                                /* .. Nbr lead zeros =               .. */
    ix              = (CPU_DATA)(val >>  0u);                                   /* .. lookup tbl ix  = 'val' >>  0 bits */
    nbr_lead_zeros  = (CPU_DATA)(CPU_CntLeadZerosTbl[ix] +  0u);                /* .. plus nbr msb lead zeros =  0 bits.*/
#endif


    return (nbr_lead_zeros);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CPU_CntLeadZeros16()
*
* Description : Count the number of contiguous, most-significant, leading zero bits in a 16-bit data value.
*
* Argument(s) : val         Data value to count leading zero bits.
*
* Return(s)   : Number of contiguous, most-significant, leading zero bits in 'val'.
*
* Caller(s)   : CPU_CntLeadZeros(),
*               CPU_CntTrailZeros16(),
*               Application.
*
*               This function is a CPU module application programming interface (API) function & MAY be 
*               called by application function(s).
*
* Note(s)     : (1) Supports 16-bit values :
*
*                          b15  b14  b13  ...  b04  b03  b02  b01  b00    # Leading Zeros
*                          ---  ---  ---       ---  ---  ---  ---  ---    ---------------
*                           1    x    x         x    x    x    x    x            0
*                           0    1    x         x    x    x    x    x            1
*                           0    0    1         x    x    x    x    x            2
*                           :    :    :         :    :    :    :    :            :
*                           :    :    :         :    :    :    :    :            :
*                           0    0    0         1    x    x    x    x           11
*                           0    0    0         0    1    x    x    x           12
*                           0    0    0         0    0    1    x    x           13
*                           0    0    0         0    0    0    1    x           14
*                           0    0    0         0    0    0    0    1           15
*                           0    0    0         0    0    0    0    0           16
*
*
*                   See also 'CPU COUNT LEAD ZEROs LOOKUP TABLE  Note #1'.
*********************************************************************************************************
*/

#if (CPU_CFG_DATA_SIZE_MAX >= CPU_WORD_SIZE_16)
CPU_DATA  CPU_CntLeadZeros16 (CPU_INT16U  val)
{
#if  (!((defined(CPU_CFG_LEAD_ZEROS_ASM_PRESENT)) && \
        (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_16)))
    CPU_DATA  ix;
#endif
    CPU_DATA  nbr_lead_zeros;

                                                                                /* ---------- ASM-OPTIMIZED ----------- */
#if ((defined(CPU_CFG_LEAD_ZEROS_ASM_PRESENT)) && \
     (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_16))
    nbr_lead_zeros  =  CPU_CntLeadZeros((CPU_DATA)val);
    nbr_lead_zeros -= (CPU_CFG_DATA_SIZE - CPU_WORD_SIZE_16) * DEF_OCTET_NBR_BITS;


#else                                                                           /* ----------- C-OPTIMIZED ------------ */
    if (val > 0x00FFu) {                                                        /* Chk bits [15:08] :                   */
                                                                                /* .. Nbr lead zeros =               .. */
        ix             = (CPU_DATA)(val >>  8u);                                /* .. lookup tbl ix  = 'val' >>  8 bits */
        nbr_lead_zeros = (CPU_DATA)(CPU_CntLeadZerosTbl[ix] +  0u);             /* .. plus nbr msb lead zeros =  0 bits.*/

    } else {                                                                    /* Chk bits [07:00] :                   */
                                                                                /* .. Nbr lead zeros =               .. */
        ix             = (CPU_DATA)(val >>  0u);                                /* .. lookup tbl ix  = 'val' >>  0 bits */
        nbr_lead_zeros = (CPU_DATA)(CPU_CntLeadZerosTbl[ix] +  8u);             /* .. plus nbr msb lead zeros =  8 bits.*/
    }
#endif


    return (nbr_lead_zeros);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CPU_CntLeadZeros32()
*
* Description : Count the number of contiguous, most-significant, leading zero bits in a 32-bit data value.
*
* Argument(s) : val         Data value to count leading zero bits.
*
* Return(s)   : Number of contiguous, most-significant, leading zero bits in 'val'.
*
* Caller(s)   : CPU_CntLeadZeros(),
*               CPU_CntTrailZeros32(),
*               Application.
*
*               This function is a CPU module application programming interface (API) function & MAY be 
*               called by application function(s).
*
* Note(s)     : (1) Supports 32-bit values :
*
*                          b31  b30  b29  ...  b04  b03  b02  b01  b00    # Leading Zeros
*                          ---  ---  ---       ---  ---  ---  ---  ---    ---------------
*                           1    x    x         x    x    x    x    x            0
*                           0    1    x         x    x    x    x    x            1
*                           0    0    1         x    x    x    x    x            2
*                           :    :    :         :    :    :    :    :            :
*                           :    :    :         :    :    :    :    :            :
*                           0    0    0         1    x    x    x    x           27
*                           0    0    0         0    1    x    x    x           28
*                           0    0    0         0    0    1    x    x           29
*                           0    0    0         0    0    0    1    x           30
*                           0    0    0         0    0    0    0    1           31
*                           0    0    0         0    0    0    0    0           32
*
*
*                   See also 'CPU COUNT LEAD ZEROs LOOKUP TABLE  Note #1'.
*********************************************************************************************************
*/

#if (CPU_CFG_DATA_SIZE_MAX >= CPU_WORD_SIZE_32)
CPU_DATA  CPU_CntLeadZeros32 (CPU_INT32U  val)
{
#if  (!((defined(CPU_CFG_LEAD_ZEROS_ASM_PRESENT)) && \
        (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_32)))
    CPU_DATA  ix;
#endif
    CPU_DATA  nbr_lead_zeros;

                                                                                /* ---------- ASM-OPTIMIZED ----------- */
#if ((defined(CPU_CFG_LEAD_ZEROS_ASM_PRESENT)) && \
     (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_32))
    nbr_lead_zeros  =  CPU_CntLeadZeros((CPU_DATA)val);
    nbr_lead_zeros -= (CPU_CFG_DATA_SIZE - CPU_WORD_SIZE_32) * DEF_OCTET_NBR_BITS;


#else                                                                           /* ----------- C-OPTIMIZED ------------ */
    if (val > 0x0000FFFFu) {
        if (val > 0x00FFFFFFu) {                                                /* Chk bits [31:24] :                   */
                                                                                /* .. Nbr lead zeros =               .. */
            ix             = (CPU_DATA)(val >> 24u);                            /* .. lookup tbl ix  = 'val' >> 24 bits */
            nbr_lead_zeros = (CPU_DATA)(CPU_CntLeadZerosTbl[ix] +  0u);         /* .. plus nbr msb lead zeros =  0 bits.*/

        } else {                                                                /* Chk bits [23:16] :                   */
                                                                                /* .. Nbr lead zeros =               .. */
            ix             = (CPU_DATA)(val >> 16u);                            /* .. lookup tbl ix  = 'val' >> 16 bits */
            nbr_lead_zeros = (CPU_DATA)(CPU_CntLeadZerosTbl[ix] +  8u);         /* .. plus nbr msb lead zeros =  8 bits.*/
        }

    } else {
        if (val > 0x000000FFu) {                                                /* Chk bits [15:08] :                   */
                                                                                /* .. Nbr lead zeros =               .. */
            ix             = (CPU_DATA)(val >>  8u);                            /* .. lookup tbl ix  = 'val' >>  8 bits */
            nbr_lead_zeros = (CPU_DATA)(CPU_CntLeadZerosTbl[ix] + 16u);         /* .. plus nbr msb lead zeros = 16 bits.*/

        } else {                                                                /* Chk bits [07:00] :                   */
                                                                                /* .. Nbr lead zeros =               .. */
            ix             = (CPU_DATA)(val >>  0u);                            /* .. lookup tbl ix  = 'val' >>  0 bits */
            nbr_lead_zeros = (CPU_DATA)(CPU_CntLeadZerosTbl[ix] + 24u);         /* .. plus nbr msb lead zeros = 24 bits.*/
        }
    }
#endif


    return (nbr_lead_zeros);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CPU_CntLeadZeros64()
*
* Description : Count the number of contiguous, most-significant, leading zero bits in a 64-bit data value.
*
* Argument(s) : val         Data value to count leading zero bits.
*
* Return(s)   : Number of contiguous, most-significant, leading zero bits in 'val'.
*
* Caller(s)   : CPU_CntLeadZeros(),
*               CPU_CntTrailZeros64(),
*               Application.
*
*               This function is a CPU module application programming interface (API) function & MAY be 
*               called by application function(s).
*
* Note(s)     : (1) Supports 64-bit values :
*
*                          b63  b62  b61  ...  b04  b03  b02  b01  b00    # Leading Zeros
*                          ---  ---  ---       ---  ---  ---  ---  ---    ---------------
*                           1    x    x         x    x    x    x    x            0
*                           0    1    x         x    x    x    x    x            1
*                           0    0    1         x    x    x    x    x            2
*                           :    :    :         :    :    :    :    :            :
*                           :    :    :         :    :    :    :    :            :
*                           0    0    0         1    x    x    x    x           59
*                           0    0    0         0    1    x    x    x           60
*                           0    0    0         0    0    1    x    x           61
*                           0    0    0         0    0    0    1    x           62
*                           0    0    0         0    0    0    0    1           63
*                           0    0    0         0    0    0    0    0           64
*
*
*                   See also 'CPU COUNT LEAD ZEROs LOOKUP TABLE  Note #1'.
*********************************************************************************************************
*/
/*$PAGE*/
#if (CPU_CFG_DATA_SIZE_MAX >= CPU_WORD_SIZE_64)
CPU_DATA  CPU_CntLeadZeros64 (CPU_INT64U  val)
{
#if  (!((defined(CPU_CFG_LEAD_ZEROS_ASM_PRESENT)) && \
        (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_64)))
    CPU_DATA  ix;
#endif
    CPU_DATA  nbr_lead_zeros;

                                                                                /* ---------- ASM-OPTIMIZED ----------- */
#if ((defined(CPU_CFG_LEAD_ZEROS_ASM_PRESENT)) && \
     (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_64))
    nbr_lead_zeros  =  CPU_CntLeadZeros((CPU_DATA)val);
    nbr_lead_zeros -= (CPU_CFG_DATA_SIZE - CPU_WORD_SIZE_64) * DEF_OCTET_NBR_BITS;


#else                                                                           /* ----------- C-OPTIMIZED ------------ */
    if (val > 0x00000000FFFFFFFFu) {
        if (val > 0x0000FFFFFFFFFFFFu) {
            if (val > 0x00FFFFFFFFFFFFFFu) {                                    /* Chk bits [63:56] :                   */
                                                                                /* .. Nbr lead zeros =               .. */
                ix             = (CPU_DATA)(val >> 56u);                        /* .. lookup tbl ix  = 'val' >> 56 bits */
                nbr_lead_zeros = (CPU_DATA)(CPU_CntLeadZerosTbl[ix] +  0u);     /* .. plus nbr msb lead zeros =  0 bits.*/

            } else {                                                            /* Chk bits [55:48] :                   */
                                                                                /* .. Nbr lead zeros =               .. */
                ix             = (CPU_DATA)(val >> 48u);                        /* .. lookup tbl ix  = 'val' >> 48 bits */
                nbr_lead_zeros = (CPU_DATA)(CPU_CntLeadZerosTbl[ix] +  8u);     /* .. plus nbr msb lead zeros =  8 bits.*/
            }

        } else {
            if (val > 0x000000FFFFFFFFFFu) {                                    /* Chk bits [47:40] :                   */
                                                                                /* .. Nbr lead zeros =               .. */
                ix             = (CPU_DATA)(val >> 40u);                        /* .. lookup tbl ix  = 'val' >> 40 bits */
                nbr_lead_zeros = (CPU_DATA)(CPU_CntLeadZerosTbl[ix] + 16u);     /* .. plus nbr msb lead zeros = 16 bits.*/

            } else {                                                            /* Chk bits [39:32] :                   */
                                                                                /* .. Nbr lead zeros =               .. */
                ix             = (CPU_DATA)(val >> 32u);                        /* .. lookup tbl ix  = 'val' >> 32 bits */
                nbr_lead_zeros = (CPU_DATA)(CPU_CntLeadZerosTbl[ix] + 24u);     /* .. plus nbr msb lead zeros = 24 bits.*/
            }
        }

    } else {
        if (val > 0x000000000000FFFFu) {
            if (val > 0x0000000000FFFFFFu) {                                    /* Chk bits [31:24] :                   */
                                                                                /* .. Nbr lead zeros =               .. */
                ix             = (CPU_DATA)(val >> 24u);                        /* .. lookup tbl ix  = 'val' >> 24 bits */
                nbr_lead_zeros = (CPU_DATA)(CPU_CntLeadZerosTbl[ix] + 32u);     /* .. plus nbr msb lead zeros = 32 bits.*/

            } else {                                                            /* Chk bits [23:16] :                   */
                                                                                /* .. Nbr lead zeros =               .. */
                ix             = (CPU_DATA)(val >> 16u);                        /* .. lookup tbl ix  = 'val' >> 16 bits */
                nbr_lead_zeros = (CPU_DATA)(CPU_CntLeadZerosTbl[ix] + 40u);     /* .. plus nbr msb lead zeros = 40 bits.*/
            }

        } else {
            if (val > 0x00000000000000FFu) {                                    /* Chk bits [15:08] :                   */
                                                                                /* .. Nbr lead zeros =               .. */
                ix             = (CPU_DATA)(val >>  8u);                        /* .. lookup tbl ix  = 'val' >>  8 bits */
                nbr_lead_zeros = (CPU_DATA)(CPU_CntLeadZerosTbl[ix] + 48u);     /* .. plus nbr msb lead zeros = 48 bits.*/

            } else {                                                            /* Chk bits [07:00] :                   */
                                                                                /* .. Nbr lead zeros =               .. */
                ix             = (CPU_DATA)(val >>  0u);                        /* .. lookup tbl ix  = 'val' >>  0 bits */
                nbr_lead_zeros = (CPU_DATA)(CPU_CntLeadZerosTbl[ix] + 56u);     /* .. plus nbr msb lead zeros = 56 bits.*/
            }
        }
    }
#endif


    return (nbr_lead_zeros);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                         CPU_CntTrailZeros()
*
* Description : Count the number of contiguous, least-significant, trailing zero bits in a data value.
*
* Argument(s) : val         Data value to count trailing zero bits.
*
* Return(s)   : Number of contiguous, least-significant, trailing zero bits in 'val'.
*
* Caller(s)   : Application.
*
*               This function is a CPU module application programming interface (API) function & MAY 
*               be called by application function(s).
*
* Note(s)     : (1) (a) Supports the following data value sizes :
*
*                       (1)  8-bits
*                       (2) 16-bits
*                       (3) 32-bits
*                       (4) 64-bits
*
*                       See also 'cpu_def.h  CPU WORD CONFIGURATION  Note #1'.
*
*                   (b) (1) For  8-bit values :
*
*                                  b07  b06  b05  b04  b03  b02  b01  b00    # Trailing Zeros
*                                  ---  ---  ---  ---  ---  ---  ---  ---    ----------------
*                                   x    x    x    x    x    x    x    1            0
*                                   x    x    x    x    x    x    1    0            1
*                                   x    x    x    x    x    1    0    0            2
*                                   x    x    x    x    1    0    0    0            3
*                                   x    x    x    1    0    0    0    0            4
*                                   x    x    1    0    0    0    0    0            5
*                                   x    1    0    0    0    0    0    0            6
*                                   1    0    0    0    0    0    0    0            7
*                                   0    0    0    0    0    0    0    0            8
*
*
*                       (2) For 16-bit values :
*
*                             b15  b14  b13  b12  b11  ...  b02  b01  b00    # Trailing Zeros
*                             ---  ---  ---  ---  ---       ---  ---  ---    ----------------
*                              x    x    x    x    x         x    x    1            0
*                              x    x    x    x    x         x    1    0            1
*                              x    x    x    x    x         1    0    0            2
*                              :    :    :    :    :         :    :    :            :
*                              :    :    :    :    :         :    :    :            :
*                              x    x    x    x    1         0    0    0           11
*                              x    x    x    1    0         0    0    0           12
*                              x    x    1    0    0         0    0    0           13
*                              x    1    0    0    0         0    0    0           14
*                              1    0    0    0    0         0    0    0           15
*                              0    0    0    0    0         0    0    0           16
*
*
*                       (3) For 32-bit values :
*
*                             b31  b30  b29  b28  b27  ...  b02  b01  b00    # Trailing Zeros
*                             ---  ---  ---  ---  ---       ---  ---  ---    ----------------
*                              x    x    x    x    x         x    x    1            0
*                              x    x    x    x    x         x    1    0            1
*                              x    x    x    x    x         1    0    0            2
*                              :    :    :    :    :         :    :    :            :
*                              :    :    :    :    :         :    :    :            :
*                              x    x    x    x    1         0    0    0           27
*                              x    x    x    1    0         0    0    0           28
*                              x    x    1    0    0         0    0    0           29
*                              x    1    0    0    0         0    0    0           30
*                              1    0    0    0    0         0    0    0           31
*                              0    0    0    0    0         0    0    0           32
*
*
*                       (4) For 64-bit values :
*
*                             b63  b62  b61  b60  b59  ...  b02  b01  b00    # Trailing Zeros
*                             ---  ---  ---  ---  ---       ---  ---  ---    ----------------
*                              x    x    x    x    x         x    x    1            0
*                              x    x    x    x    x         x    1    0            1
*                              x    x    x    x    x         1    0    0            2
*                              :    :    :    :    :         :    :    :            :
*                              :    :    :    :    :         :    :    :            :
*                              x    x    x    x    1         0    0    0           59
*                              x    x    x    1    0         0    0    0           60
*                              x    x    1    0    0         0    0    0           61
*                              x    1    0    0    0         0    0    0           62
*                              1    0    0    0    0         0    0    0           63
*                              0    0    0    0    0         0    0    0           64
*
*$PAGE*
*               (2) For non-zero values, the returned number of contiguous, least-significant, trailing 
*                   zero bits is also equivalent to the bit position of the least-significant set bit.
*
*               (3) 'val' SHOULD be validated for non-'0' PRIOR to all other counting zero calculations :
*
*                   (a) CPU_CntTrailZeros()'s final conditional statement calculates 'val's number of 
*                       trailing zeros based on its return data size, 'CPU_CFG_DATA_SIZE', & 'val's 
*                       calculated number of lead zeros ONLY if the initial 'val' is non-'0' :
*
*                           if (val != 0u) {
*                               nbr_trail_zeros = ((CPU_CFG_DATA_SIZE * DEF_OCTET_NBR_BITS) - 1u) - nbr_lead_zeros;
*                           } else {
*                               nbr_trail_zeros = nbr_lead_zeros;
*                           }
*
*                       Therefore, initially validating all non-'0' values avoids having to conditionally 
*                       execute the final 'if' statement.
*********************************************************************************************************
*/

#ifndef   CPU_CFG_TRAIL_ZEROS_ASM_PRESENT
CPU_DATA  CPU_CntTrailZeros (CPU_DATA  val)
{
    CPU_DATA  val_bit_mask;
    CPU_DATA  nbr_lead_zeros;
    CPU_DATA  nbr_trail_zeros;


    if (val == 0u) {                                            /* Rtn ALL val bits as zero'd (see Note #3).            */
        return (CPU_CFG_DATA_SIZE * DEF_OCTET_NBR_BITS);
    }


    val_bit_mask    = val & ((CPU_DATA)~val + 1u);              /* Zero/clr all bits EXCEPT least-sig set bit.          */
    nbr_lead_zeros  = CPU_CntLeadZeros(val_bit_mask);           /* Cnt  nbr lead  0s.                                   */
                                                                /* Calc nbr trail 0s = (nbr val bits - 1) - nbr lead 0s.*/
    nbr_trail_zeros = ((CPU_CFG_DATA_SIZE * DEF_OCTET_NBR_BITS) - 1u) - nbr_lead_zeros;


    return (nbr_trail_zeros);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CPU_CntTrailZeros08()
*
* Description : Count the number of contiguous, least-significant, trailing zero bits in an 8-bit data value.
*
* Argument(s) : val         Data value to count trailing zero bits.
*
* Return(s)   : Number of contiguous, least-significant, trailing zero bits in 'val'.
*
* Caller(s)   : Application.
*
*               This function is a CPU module application programming interface (API) function & MAY be 
*               called by application function(s).
*
* Note(s)     : (1) Supports  8-bit values :
*
*                               b07  b06  b05  b04  b03  b02  b01  b00    # Trailing Zeros
*                               ---  ---  ---  ---  ---  ---  ---  ---    ----------------
*                                x    x    x    x    x    x    x    1            0
*                                x    x    x    x    x    x    1    0            1
*                                x    x    x    x    x    1    0    0            2
*                                x    x    x    x    1    0    0    0            3
*                                x    x    x    1    0    0    0    0            4
*                                x    x    1    0    0    0    0    0            5
*                                x    1    0    0    0    0    0    0            6
*                                1    0    0    0    0    0    0    0            7
*                                0    0    0    0    0    0    0    0            8
*
*
*               (2) For non-zero values, the returned number of contiguous, least-significant, trailing 
*                   zero bits is also equivalent to the bit position of the least-significant set bit.
*
*               (3) 'val' SHOULD be validated for non-'0' PRIOR to all other counting zero calculations :
*
*                   (a) For assembly-optimized implementations, CPU_CntTrailZeros() returns 'val's 
*                       number of trailing zeros via CPU's native data size, 'CPU_CFG_DATA_SIZE'.  
*                       If the returned number of zeros exceeds CPU_CntTrailZeros08()'s  8-bit return 
*                       data size, then the returned number of zeros must be offset by the difference 
*                       between CPU_CntTrailZeros()'s  & CPU_CntTrailZeros08()'s return data size :
*
*                           nbr_trail_zeros = CPU_CntTrailZeros((CPU_DATA)val);
*                           if (nbr_trail_zeros >  (CPU_WORD_SIZE_08  * DEF_OCTET_NBR_BITS)) {
*                               nbr_trail_zeros -= (CPU_CFG_DATA_SIZE - CPU_WORD_SIZE_08) * DEF_OCTET_NBR_BITS;
*                           }
*
*                       However, this ONLY occurs for an initial 'val' of '0' since all non-'0'  8-bit 
*                       values would return a number of trailing zeros less than or equal to  8 bits.
*
*                       Therefore, initially validating all non-'0' values prior to calling assembly-
*                       optimized CPU_CntTrailZeros() avoids having to offset the number of returned 
*                       trailing zeros by the difference in CPU data size and  8-bit data value bits.
*
*                   (b) For CPU_CntTrailZeros08()'s C implementation, the final conditional statement 
*                       calculates 'val's number of trailing zeros based on CPU_CntTrailZeros08()'s 
*                        8-bit return data size & 'val's calculated number of lead zeros ONLY if the 
*                       initial 'val' is non-'0' :
*
*                           if (val != 0u) {
*                               nbr_trail_zeros = ((CPU_WORD_SIZE_08 * DEF_OCTET_NBR_BITS) - 1u) - nbr_lead_zeros;
*                           } else {
*                               nbr_trail_zeros = nbr_lead_zeros;
*                           }
*
*                       Therefore, initially validating all non-'0' values avoids having to conditionally 
*                       execute the final 'if' statement.
*********************************************************************************************************
*/
/*$PAGE*/
#if (CPU_CFG_DATA_SIZE_MAX >= CPU_WORD_SIZE_08)
CPU_DATA  CPU_CntTrailZeros08 (CPU_INT08U  val)
{
#if  (!((defined(CPU_CFG_TRAIL_ZEROS_ASM_PRESENT)) && \
        (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_08)))
    CPU_INT08U  val_bit_mask;
    CPU_DATA    nbr_lead_zeros;
#endif
    CPU_DATA    nbr_trail_zeros;


    if (val == 0u) {                                            /* Rtn ALL val bits as zero'd (see Note #3).            */
        return (CPU_WORD_SIZE_08 * DEF_OCTET_NBR_BITS);
    }

                                                                /* ------------------ ASM-OPTIMIZED ------------------- */
#if ((defined(CPU_CFG_TRAIL_ZEROS_ASM_PRESENT)) && \
     (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_08))
    nbr_trail_zeros = CPU_CntTrailZeros((CPU_DATA)val);

#else                                                           /* ------------------- C-OPTIMIZED -------------------- */
    val_bit_mask    = val & ((CPU_INT08U)~val + 1u);            /* Zero/clr all bits EXCEPT least-sig set bit.          */
    nbr_lead_zeros  = CPU_CntLeadZeros08(val_bit_mask);         /* Cnt  nbr lead  0s.                                   */
                                                                /* Calc nbr trail 0s = (nbr val bits - 1) - nbr lead 0s.*/
    nbr_trail_zeros = ((CPU_WORD_SIZE_08 * DEF_OCTET_NBR_BITS) - 1u) - nbr_lead_zeros;
#endif


    return (nbr_trail_zeros);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CPU_CntTrailZeros16()
*
* Description : Count the number of contiguous, least-significant, trailing zero bits in a 16-bit data value.
*
* Argument(s) : val         Data value to count trailing zero bits.
*
* Return(s)   : Number of contiguous, least-significant, trailing zero bits in 'val'.
*
* Caller(s)   : Application.
*
*               This function is a CPU module application programming interface (API) function & MAY be 
*               called by application function(s).
*
* Note(s)     : (1) Supports 16-bit values :
*
*                          b15  b14  b13  b12  b11  ...  b02  b01  b00    # Trailing Zeros
*                          ---  ---  ---  ---  ---       ---  ---  ---    ----------------
*                           x    x    x    x    x         x    x    1            0
*                           x    x    x    x    x         x    1    0            1
*                           x    x    x    x    x         1    0    0            2
*                           :    :    :    :    :         :    :    :            :
*                           :    :    :    :    :         :    :    :            :
*                           x    x    x    x    1         0    0    0           11
*                           x    x    x    1    0         0    0    0           12
*                           x    x    1    0    0         0    0    0           13
*                           x    1    0    0    0         0    0    0           14
*                           1    0    0    0    0         0    0    0           15
*                           0    0    0    0    0         0    0    0           16
*
*
*               (2) For non-zero values, the returned number of contiguous, least-significant, trailing 
*                   zero bits is also equivalent to the bit position of the least-significant set bit.
*
*               (3) 'val' SHOULD be validated for non-'0' PRIOR to all other counting zero calculations :
*
*                   (a) For assembly-optimized implementations, CPU_CntTrailZeros() returns 'val's 
*                       number of trailing zeros via CPU's native data size, 'CPU_CFG_DATA_SIZE'.  
*                       If the returned number of zeros exceeds CPU_CntTrailZeros16()'s 16-bit return 
*                       data size, then the returned number of zeros must be offset by the difference 
*                       between CPU_CntTrailZeros()'s  & CPU_CntTrailZeros16()'s return data size :
*
*                           nbr_trail_zeros = CPU_CntTrailZeros((CPU_DATA)val);
*                           if (nbr_trail_zeros >  (CPU_WORD_SIZE_16  * DEF_OCTET_NBR_BITS)) {
*                               nbr_trail_zeros -= (CPU_CFG_DATA_SIZE - CPU_WORD_SIZE_16) * DEF_OCTET_NBR_BITS;
*                           }
*
*                       However, this ONLY occurs for an initial 'val' of '0' since all non-'0' 16-bit 
*                       values would return a number of trailing zeros less than or equal to 16 bits.
*
*                       Therefore, initially validating all non-'0' values prior to calling assembly-
*                       optimized CPU_CntTrailZeros() avoids having to offset the number of returned 
*                       trailing zeros by the difference in CPU data size and 16-bit data value bits.
*
*                   (b) For CPU_CntTrailZeros16()'s C implementation, the final conditional statement 
*                       calculates 'val's number of trailing zeros based on CPU_CntTrailZeros16()'s 
*                       16-bit return data size & 'val's calculated number of lead zeros ONLY if the 
*                       initial 'val' is non-'0' :
*
*                           if (val != 0u) {
*                               nbr_trail_zeros = ((CPU_WORD_SIZE_16 * DEF_OCTET_NBR_BITS) - 1u) - nbr_lead_zeros;
*                           } else {
*                               nbr_trail_zeros = nbr_lead_zeros;
*                           }
*
*                       Therefore, initially validating all non-'0' values avoids having to conditionally 
*                       execute the final 'if' statement.
*********************************************************************************************************
*/
/*$PAGE*/
#if (CPU_CFG_DATA_SIZE_MAX >= CPU_WORD_SIZE_16)
CPU_DATA  CPU_CntTrailZeros16 (CPU_INT16U  val)
{
#if  (!((defined(CPU_CFG_TRAIL_ZEROS_ASM_PRESENT)) && \
        (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_16)))
    CPU_INT16U  val_bit_mask;
    CPU_DATA    nbr_lead_zeros;
#endif
    CPU_DATA    nbr_trail_zeros;


    if (val == 0u) {                                            /* Rtn ALL val bits as zero'd (see Note #3).            */
        return (CPU_WORD_SIZE_16 * DEF_OCTET_NBR_BITS);
    }

                                                                /* ------------------ ASM-OPTIMIZED ------------------- */
#if ((defined(CPU_CFG_TRAIL_ZEROS_ASM_PRESENT)) && \
     (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_16))
    nbr_trail_zeros = CPU_CntTrailZeros((CPU_DATA)val);

#else                                                           /* ------------------- C-OPTIMIZED -------------------- */
    val_bit_mask    = val & ((CPU_INT16U)~val + 1u);            /* Zero/clr all bits EXCEPT least-sig set bit.          */
    nbr_lead_zeros  = CPU_CntLeadZeros16(val_bit_mask);         /* Cnt  nbr lead  0s.                                   */
                                                                /* Calc nbr trail 0s = (nbr val bits - 1) - nbr lead 0s.*/
    nbr_trail_zeros = ((CPU_WORD_SIZE_16 * DEF_OCTET_NBR_BITS) - 1u) - nbr_lead_zeros;
#endif


    return (nbr_trail_zeros);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CPU_CntTrailZeros32()
*
* Description : Count the number of contiguous, least-significant, trailing zero bits in a 32-bit data value.
*
* Argument(s) : val         Data value to count trailing zero bits.
*
* Return(s)   : Number of contiguous, least-significant, trailing zero bits in 'val'.
*
* Caller(s)   : Application.
*
*               This function is a CPU module application programming interface (API) function & MAY be 
*               called by application function(s).
*
* Note(s)     : (1) Supports 32-bit values :
*
*                          b31  b30  b29  b28  b27  ...  b02  b01  b00    # Trailing Zeros
*                          ---  ---  ---  ---  ---       ---  ---  ---    ----------------
*                           x    x    x    x    x         x    x    1            0
*                           x    x    x    x    x         x    1    0            1
*                           x    x    x    x    x         1    0    0            2
*                           :    :    :    :    :         :    :    :            :
*                           :    :    :    :    :         :    :    :            :
*                           x    x    x    x    1         0    0    0           27
*                           x    x    x    1    0         0    0    0           28
*                           x    x    1    0    0         0    0    0           29
*                           x    1    0    0    0         0    0    0           30
*                           1    0    0    0    0         0    0    0           31
*                           0    0    0    0    0         0    0    0           32
*
*
*               (2) For non-zero values, the returned number of contiguous, least-significant, trailing 
*                   zero bits is also equivalent to the bit position of the least-significant set bit.
*
*               (3) 'val' SHOULD be validated for non-'0' PRIOR to all other counting zero calculations :
*
*                   (a) For assembly-optimized implementations, CPU_CntTrailZeros() returns 'val's 
*                       number of trailing zeros via CPU's native data size, 'CPU_CFG_DATA_SIZE'.  
*                       If the returned number of zeros exceeds CPU_CntTrailZeros32()'s 32-bit return 
*                       data size, then the returned number of zeros must be offset by the difference 
*                       between CPU_CntTrailZeros()'s  & CPU_CntTrailZeros32()'s return data size :
*
*                           nbr_trail_zeros = CPU_CntTrailZeros((CPU_DATA)val);
*                           if (nbr_trail_zeros >  (CPU_WORD_SIZE_32  * DEF_OCTET_NBR_BITS)) {
*                               nbr_trail_zeros -= (CPU_CFG_DATA_SIZE - CPU_WORD_SIZE_32) * DEF_OCTET_NBR_BITS;
*                           }
*
*                       However, this ONLY occurs for an initial 'val' of '0' since all non-'0' 32-bit 
*                       values would return a number of trailing zeros less than or equal to 32 bits.
*
*                       Therefore, initially validating all non-'0' values prior to calling assembly-
*                       optimized CPU_CntTrailZeros() avoids having to offset the number of returned 
*                       trailing zeros by the difference in CPU data size and 32-bit data value bits.
*
*                   (b) For CPU_CntTrailZeros32()'s C implementation, the final conditional statement 
*                       calculates 'val's number of trailing zeros based on CPU_CntTrailZeros32()'s 
*                       32-bit return data size & 'val's calculated number of lead zeros ONLY if the 
*                       initial 'val' is non-'0' :
*
*                           if (val != 0u) {
*                               nbr_trail_zeros = ((CPU_WORD_SIZE_32 * DEF_OCTET_NBR_BITS) - 1u) - nbr_lead_zeros;
*                           } else {
*                               nbr_trail_zeros = nbr_lead_zeros;
*                           }
*
*                       Therefore, initially validating all non-'0' values avoids having to conditionally 
*                       execute the final 'if' statement.
*********************************************************************************************************
*/
/*$PAGE*/
#if (CPU_CFG_DATA_SIZE_MAX >= CPU_WORD_SIZE_32)
CPU_DATA  CPU_CntTrailZeros32 (CPU_INT32U  val)
{
#if  (!((defined(CPU_CFG_TRAIL_ZEROS_ASM_PRESENT)) && \
        (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_32)))
    CPU_INT32U  val_bit_mask;
    CPU_DATA    nbr_lead_zeros;
#endif
    CPU_DATA    nbr_trail_zeros;


    if (val == 0u) {                                            /* Rtn ALL val bits as zero'd (see Note #3).            */
        return (CPU_WORD_SIZE_32 * DEF_OCTET_NBR_BITS);
    }

                                                                /* ------------------ ASM-OPTIMIZED ------------------- */
#if ((defined(CPU_CFG_TRAIL_ZEROS_ASM_PRESENT)) && \
     (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_32))
    nbr_trail_zeros = CPU_CntTrailZeros((CPU_DATA)val);

#else                                                           /* ------------------- C-OPTIMIZED -------------------- */
    val_bit_mask    = val & ((CPU_INT32U)~val + 1u);            /* Zero/clr all bits EXCEPT least-sig set bit.          */
    nbr_lead_zeros  = CPU_CntLeadZeros32(val_bit_mask);         /* Cnt  nbr lead  0s.                                   */
                                                                /* Calc nbr trail 0s = (nbr val bits - 1) - nbr lead 0s.*/
    nbr_trail_zeros = ((CPU_WORD_SIZE_32 * DEF_OCTET_NBR_BITS) - 1u) - nbr_lead_zeros;
#endif


    return (nbr_trail_zeros);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CPU_CntTrailZeros64()
*
* Description : Count the number of contiguous, least-significant, trailing zero bits in a 64-bit data value.
*
* Argument(s) : val         Data value to count trailing zero bits.
*
* Return(s)   : Number of contiguous, least-significant, trailing zero bits in 'val'.
*
* Caller(s)   : Application.
*
*               This function is a CPU module application programming interface (API) function & MAY be 
*               called by application function(s).
*
* Note(s)     : (1) Supports 64-bit values :
*
*                          b63  b62  b61  b60  b59  ...  b02  b01  b00    # Trailing Zeros
*                          ---  ---  ---  ---  ---       ---  ---  ---    ----------------
*                           x    x    x    x    x         x    x    1            0
*                           x    x    x    x    x         x    1    0            1
*                           x    x    x    x    x         1    0    0            2
*                           :    :    :    :    :         :    :    :            :
*                           :    :    :    :    :         :    :    :            :
*                           x    x    x    x    1         0    0    0           59
*                           x    x    x    1    0         0    0    0           60
*                           x    x    1    0    0         0    0    0           61
*                           x    1    0    0    0         0    0    0           62
*                           1    0    0    0    0         0    0    0           63
*                           0    0    0    0    0         0    0    0           64
*
*
*               (2) For non-zero values, the returned number of contiguous, least-significant, trailing 
*                   zero bits is also equivalent to the bit position of the least-significant set bit.
*
*               (3) 'val' SHOULD be validated for non-'0' PRIOR to all other counting zero calculations :
*
*                   (a) For assembly-optimized implementations, CPU_CntTrailZeros() returns 'val's 
*                       number of trailing zeros via CPU's native data size, 'CPU_CFG_DATA_SIZE'.  
*                       If the returned number of zeros exceeds CPU_CntTrailZeros64()'s 64-bit return 
*                       data size, then the returned number of zeros must be offset by the difference 
*                       between CPU_CntTrailZeros()'s  & CPU_CntTrailZeros64()'s return data size :
*
*                           nbr_trail_zeros = CPU_CntTrailZeros((CPU_DATA)val);
*                           if (nbr_trail_zeros >  (CPU_WORD_SIZE_64  * DEF_OCTET_NBR_BITS)) {
*                               nbr_trail_zeros -= (CPU_CFG_DATA_SIZE - CPU_WORD_SIZE_64) * DEF_OCTET_NBR_BITS;
*                           }
*
*                       However, this ONLY occurs for an initial 'val' of '0' since all non-'0' 64-bit 
*                       values would return a number of trailing zeros less than or equal to 64 bits.
*
*                       Therefore, initially validating all non-'0' values prior to calling assembly-
*                       optimized CPU_CntTrailZeros() avoids having to offset the number of returned 
*                       trailing zeros by the difference in CPU data size and 64-bit data value bits.
*
*                   (b) For CPU_CntTrailZeros64()'s C implementation, the final conditional statement 
*                       calculates 'val's number of trailing zeros based on CPU_CntTrailZeros64()'s 
*                       64-bit return data size & 'val's calculated number of lead zeros ONLY if the 
*                       initial 'val' is non-'0' :
*
*                           if (val != 0u) {
*                               nbr_trail_zeros = ((CPU_WORD_SIZE_64 * DEF_OCTET_NBR_BITS) - 1u) - nbr_lead_zeros;
*                           } else {
*                               nbr_trail_zeros = nbr_lead_zeros;
*                           }
*
*                       Therefore, initially validating all non-'0' values avoids having to conditionally 
*                       execute the final 'if' statement.
*********************************************************************************************************
*/
/*$PAGE*/
#if (CPU_CFG_DATA_SIZE_MAX >= CPU_WORD_SIZE_64)
CPU_DATA  CPU_CntTrailZeros64 (CPU_INT64U  val)
{
#if  (!((defined(CPU_CFG_TRAIL_ZEROS_ASM_PRESENT)) && \
        (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_64)))
    CPU_INT64U  val_bit_mask;
    CPU_DATA    nbr_lead_zeros;
#endif
    CPU_DATA    nbr_trail_zeros;


    if (val == 0u) {                                            /* Rtn ALL val bits as zero'd (see Note #3).            */
        return (CPU_WORD_SIZE_64 * DEF_OCTET_NBR_BITS);
    }

                                                                /* ------------------ ASM-OPTIMIZED ------------------- */
#if ((defined(CPU_CFG_TRAIL_ZEROS_ASM_PRESENT)) && \
     (CPU_CFG_DATA_SIZE >= CPU_WORD_SIZE_64))
    nbr_trail_zeros = CPU_CntTrailZeros((CPU_DATA)val);

#else                                                           /* ------------------- C-OPTIMIZED -------------------- */
    val_bit_mask    = val & ((CPU_INT64U)~val + 1u);            /* Zero/clr all bits EXCEPT least-sig set bit.          */
    nbr_lead_zeros  = CPU_CntLeadZeros64(val_bit_mask);         /* Cnt  nbr lead  0s.                                   */
                                                                /* Calc nbr trail 0s = (nbr val bits - 1) - nbr lead 0s.*/
    nbr_trail_zeros = ((CPU_WORD_SIZE_64 * DEF_OCTET_NBR_BITS) - 1u) - nbr_lead_zeros;
#endif


    return (nbr_trail_zeros);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*********************************************************************************************************
*                                           LOCAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           CPU_NameInit()
*
* Description : Initialize CPU Name.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : CPU_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (CPU_CFG_NAME_EN == DEF_ENABLED)
static  void  CPU_NameInit (void)
{
    CPU_NameClr();
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                            CPU_TS_Init()
*
* Description : (1) Initialize CPU timestamp :
*
*                   (a) Initialize/start CPU timestamp timer                            See Note #1
*                   (b) Initialize       CPU timestamp controls
*
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : CPU_Init().
*
* Note(s)     : (1) The following initialization MUST be sequenced as follows :
*
*                   (a) CPU_TS_TmrFreq_Hz     MUST be initialized prior to CPU_TS_TmrInit()
*                   (b) CPU_TS_TmrInit()      SHOULD precede calls to all other CPU timestamp functions;
*                                                 otherwise, invalid time measurements may be calculated/
*                                                 returned.
*
*                   See also 'CPU_Init()  Note #3a'.
*********************************************************************************************************
*/

#if ((CPU_CFG_TS_EN     == DEF_ENABLED) || \
     (CPU_CFG_TS_TMR_EN == DEF_ENABLED))
static  void  CPU_TS_Init (void)
{
#if (((CPU_CFG_TS_32_EN    == DEF_ENABLED     )  && \
      (CPU_CFG_TS_TMR_SIZE <  CPU_WORD_SIZE_32)) || \
     ((CPU_CFG_TS_64_EN    == DEF_ENABLED     )  && \
      (CPU_CFG_TS_TMR_SIZE <  CPU_WORD_SIZE_64)))
    CPU_TS_TMR  ts_tmr_cnts;
#endif


                                                                /* ----------------- INIT CPU TS TMR ------------------ */
#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
    CPU_TS_TmrFreq_Hz   = 0u;                                   /* Init/clr     ts tmr freq (see Note #1a).             */
    CPU_TS_TmrInit();                                           /* Init & start ts tmr      (see Note #1b).             */
#endif


                                                                /* ------------------- INIT CPU TS -------------------- */
#if (((CPU_CFG_TS_32_EN    == DEF_ENABLED     )  && \
      (CPU_CFG_TS_TMR_SIZE <  CPU_WORD_SIZE_32)) || \
     ((CPU_CFG_TS_64_EN    == DEF_ENABLED     )  && \
      (CPU_CFG_TS_TMR_SIZE <  CPU_WORD_SIZE_64)))
    ts_tmr_cnts = CPU_TS_TmrRd();                               /* Get init ts tmr val (in ts tmr cnts).                */
#endif

#if  ((CPU_CFG_TS_32_EN    == DEF_ENABLED)  && \
      (CPU_CFG_TS_TMR_SIZE <  CPU_WORD_SIZE_32))
    CPU_TS_32_Accum   = 0u;                                     /* Init 32-bit accum'd ts.                              */
    CPU_TS_32_TmrPrev = ts_tmr_cnts;                            /* Init 32-bit ts prev tmr val.                         */
#endif

#if  ((CPU_CFG_TS_64_EN    == DEF_ENABLED)  && \
      (CPU_CFG_TS_TMR_SIZE <  CPU_WORD_SIZE_64))
    CPU_TS_64_Accum   = 0u;                                     /* Init 64-bit accum'd ts.                              */
    CPU_TS_64_TmrPrev = ts_tmr_cnts;                            /* Init 64-bit ts prev tmr val.                         */
#endif
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CPU_IntDisMeasInit()
*
* Description : (1) Initialize interrupts disabled time measurements feature :
*
*                   (a) Initialize interrupts disabled time measurement controls
*                   (b) Calculate  interrupts disabled time measurement overhead
*
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : CPU_Init().
*
* Note(s)     : (2) CPU_IntDisMeasInit() SHOULD precede ALL calls to CPU_CRITICAL_ENTER()/CPU_CRITICAL_EXIT()
*                   & other CPU interrupts disabled time measurement functions; otherwise, invalid interrupts
*                   disabled time measurements may be calculated/returned.
*
*                   See also 'CPU_Init()  Note #3b'.
*
*               (3) (a) (1) Interrupts disabled time measurement overhead performed multiple times to calculate
*                           a rounded average with better accuracy, hopefully of +/- one timer count.
*
*                       (2) However, a single overhead time measurement is recommended, even for instruction-
*                           cache-enabled CPUs, since critical sections are NOT typically called within
*                           instruction-cached loops.  Thus a single non-cached/non-averaged time measurement
*                           is a more realistic overhead for the majority of non-cached interrupts disabled
*                           time measurements.
*
*                   (b) Interrupts MUST be disabled while measuring the interrupts disabled time measurement
*                       overhead; otherwise, overhead measurements could be interrupted which would incorrectly
*                       calculate an inflated overhead time which would then incorrectly calculate deflated
*                       interrupts disabled times.
*********************************************************************************************************
*/

#ifdef  CPU_CFG_INT_DIS_MEAS_EN
static  void  CPU_IntDisMeasInit (void)
{
    CPU_TS_TMR  time_meas_tot_cnts;
    CPU_INT16U  i;
    CPU_SR_ALLOC();

                                                                /* ----------- INIT INT DIS TIME MEAS CTRLS ----------- */
    CPU_IntDisMeasCtr         = 0u;
    CPU_IntDisNestCtr         = 0u;
    CPU_IntDisMeasStart_cnts  = 0u;
    CPU_IntDisMeasStop_cnts   = 0u;
    CPU_IntDisMeasMaxCur_cnts = 0u;
    CPU_IntDisMeasMax_cnts    = 0u;
    CPU_IntDisMeasOvrhd_cnts  = 0u;

                                                                /* ----------- CALC INT DIS TIME MEAS OVRHD ----------- */
    time_meas_tot_cnts = 0u;
    CPU_INT_DIS();                                              /* Ints MUST be dis'd for ovrhd calc (see Note #3b).    */
    for (i = 0u; i < CPU_CFG_INT_DIS_MEAS_OVRHD_NBR; i++) {
        CPU_IntDisMeasMaxCur_cnts = 0u;
        CPU_IntDisMeasStart();                                  /* Perform multiple consecutive start/stop time meas's  */
        CPU_IntDisMeasStop();
        time_meas_tot_cnts += CPU_IntDisMeasMaxCur_cnts;        /* ...       & sum time meas max's                  ... */
    }
                                                                /* ... to calc avg time meas ovrhd (see Note #3a).      */
    CPU_IntDisMeasOvrhd_cnts  = (time_meas_tot_cnts + (CPU_CFG_INT_DIS_MEAS_OVRHD_NBR / 2u))
                                                    /  CPU_CFG_INT_DIS_MEAS_OVRHD_NBR;
    CPU_IntDisMeasMaxCur_cnts =  0u;                            /* Reset max ints dis'd times.                          */
    CPU_IntDisMeasMax_cnts    =  0u;
    CPU_INT_EN();
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                       CPU_IntDisMeasMaxCalc()
*
* Description : Calculate maximum interrupts disabled time.
*
* Argument(s) : time_tot_cnts   Total interrupt disabled time, in timer counts.
*
* Return(s)   : Maximum interrupts disabled time (in CPU timestamp timer counts).
*
* Caller(s)   : CPU_IntDisMeasMaxCurGet(),
*               CPU_IntDisMeasMaxGet().
*
* Note(s)     : (1) (a) The total amount of time interrupts are disabled by system &/or application code
*                       during critical sections is calculated by the following equations :
*
*                       (1) time            =   [ time      -  time      ]  -  time
*                               interrupts      [     stop         start ]         total meas
*                                disabled       [     meas         meas  ]           ovrhd
*                           (via application)
*
*
*                       (2) time            =  time            +  time
*                               total meas         start meas         stop meas
*                                 ovrhd              ovrhd              ovrhd
*
*
*                               where
*
*                                       time                    time interrupts are disabled between
*                                           interrupts              first critical section enter &
*                                            disabled               last  critical section exit minus
*                                       (via application)           time measurement overhead
*
*                                       time                    time of disable interrupts start time
*                                           start                   measurement (in timer counts)
*                                           meas
*
*                                       time                    time of disable interrupts stop  time
*                                           stop                    measurement (in timer counts)
*                                           meas
*
*                                       time                    total overhead time to start/stop disabled
*                                           total meas              interrupts time measurements (in timer
*                                             ovrhd                 counts)
*
*                                       time                    total overhead time after getting start
*                                           start meas              time until end of start measurement
*                                             ovrhd                 function  (in timer counts)
*
*                                       time                    total overhead time from beginning of stop
*                                           stop meas               measurement function until after getting
*                                             ovrhd                 stop time (in timer counts)
*
*
*                   (b) To expedite & reduce interrupts disabled time measurement overhead, the final 
*                       calculations to subtract the interrupts disabled time measurement overhead is 
*                       performed asynchronously in API functions.
*
*                       See also 'CPU_IntDisMeasStop()  Note #1b2'.
*$PAGE*
*                   (c) The amount of time interrupts are disabled is calculated by either of the
*                       following equations :
*
*                       (1) Interrupts disabled time  =  Number timer counts  *  Timer period
*
*                               where
*
*                                   Number timer counts             Number of timer counts measured
*                                   Timer period                    Timer's period in some units of
*                                                                       (fractional) seconds
*                                   Interrupts disabled time        Amount of time interrupts are
*                                                                       disabled, in same units of
*                                                                       (fractional) seconds as the
*                                                                       Timer period
*
*                                                         Number timer counts
*                       (2) Interrupts disabled time  =  ---------------------
*                                                           Timer frequency
*
*                               where
*
*                                   Number timer counts             Number of timer counts measured
*                                   Timer frequency                 Timer's frequency in some units
*                                                                       of counts per second
*                                   Interrupts disabled time        Amount of time interrupts are
*                                                                       disabled, in seconds
*
*                       See also 'cpu_core.h  FUNCTION PROTOTYPES  CPU_TS_TmrRd()      Note #2c'
*                              & 'cpu_core.h  FUNCTION PROTOTYPES  CPU_TSxx_to_uSec()  Note #2'.
*
*               (2) Although it is not typical, it is possible for an interrupts disabled time
*                   measurement to be less than the interrupts disabled time measurement overhead;
*                   especially if the overhead was calculated with a single, non-cached measurement
*                   & critical sections are called within instruction-cached loops.
*********************************************************************************************************
*/

#ifdef  CPU_CFG_INT_DIS_MEAS_EN
static  CPU_TS_TMR  CPU_IntDisMeasMaxCalc (CPU_TS_TMR  time_tot_cnts)
{
    CPU_TS_TMR  time_max_cnts;


    time_max_cnts = time_tot_cnts;
    if (time_max_cnts >  CPU_IntDisMeasOvrhd_cnts) {            /* If       max ints dis'd time >  ovrhd time, ...      */
        time_max_cnts -= CPU_IntDisMeasOvrhd_cnts;              /* ... adj  max ints dis'd time by ovrhd time; ...      */
    } else {                                                    /* ... else max ints dis'd time <  ovrhd time, ...      */
        time_max_cnts  = 0u;                                    /* ... clr  max ints dis'd time (see Note #2).          */
    }

    return (time_max_cnts);
}
#endif

