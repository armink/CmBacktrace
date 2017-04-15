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
* Filename      : cpu_core.h
* Version       : V1.29.01
* Programmer(s) : SR
*                 ITJ
*********************************************************************************************************
* Note(s)       : (1) Assumes the following versions (or more recent) of software modules are included in 
*                     the project build :
*
*                     (a) uC/LIB V1.35.00
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This core CPU header file is protected from multiple pre-processor inclusion through use of 
*               the  core CPU module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  CPU_CORE_MODULE_PRESENT                                /* See Note #1.                                         */
#define  CPU_CORE_MODULE_PRESENT


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   CPU_CORE_MODULE
#define  CPU_CORE_EXT
#else
#define  CPU_CORE_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                            INCLUDE FILES
*
* Note(s) : (1) CPU-configuration software files are located in the following directories :
*
*               (a) \<Your Product Application>\cpu_cfg.h
*
*               (b) (1) \<CPU-Compiler Directory>\cpu_*.*
*                   (2) \<CPU-Compiler Directory>\<cpu>\<compiler>\cpu*.*
*
*                       where
*                               <Your Product Application>      directory path for Your Product's Application
*                               <CPU-Compiler Directory>        directory path for common CPU-compiler software
*                               <cpu>                           directory name for specific processor (CPU)
*                               <compiler>                      directory name for specific compiler
*
*           (2) NO compiler-supplied standard library functions SHOULD be used.
*
*               (a) Standard library functions are implemented in the custom library module(s) :
*
*                       \<Custom Library Directory>\lib_*.*
*
*                           where
*                                   <Custom Library Directory>      directory path for custom library software
*
*           (3) Compiler MUST be configured to include as additional include path directories :
*
*               (a) '\<Your Product Application>\' directory                            See Note #1a
*
*               (b) (1) '\<CPU-Compiler Directory>\'                  directory         See Note #1b1
*                   (2) '\<CPU-Compiler Directory>\<cpu>\<compiler>\' directory         See Note #1b2
*
*               (c) '\<Custom Library Directory>\' directory                            See Note #2a
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>
#include  <cpu_cfg.h>

#if (CPU_CFG_NAME_EN == DEF_ENABLED)
#include  <lib_mem.h>
#include  <lib_str.h>
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                          CPU CONFIGURATION
*
* Note(s) : (1) The following pre-processor directives correctly configure CPU parameters.  DO NOT MODIFY.
*
*           (2) CPU timestamp timer feature is required for :
*
*               (a) CPU timestamps
*               (b) CPU interrupts disabled time measurement
*
*               See also 'cpu_cfg.h  CPU TIMESTAMP CONFIGURATION  Note #1'
*                      & 'cpu_cfg.h  CPU INTERRUPTS DISABLED TIME MEASUREMENT CONFIGURATION  Note #1'.
*********************************************************************************************************
*/

#ifdef   CPU_CFG_TS_EN
#undef   CPU_CFG_TS_EN
#endif


#if    ((CPU_CFG_TS_32_EN == DEF_ENABLED) || \
        (CPU_CFG_TS_64_EN == DEF_ENABLED))
#define  CPU_CFG_TS_EN                          DEF_ENABLED
#else
#define  CPU_CFG_TS_EN                          DEF_DISABLED
#endif

#if    ((CPU_CFG_TS_EN == DEF_ENABLED) || \
(defined(CPU_CFG_INT_DIS_MEAS_EN)))
#define  CPU_CFG_TS_TMR_EN                      DEF_ENABLED
#else
#define  CPU_CFG_TS_TMR_EN                      DEF_DISABLED
#endif


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  CPU_TIME_MEAS_NBR_MIN                             1u
#define  CPU_TIME_MEAS_NBR_MAX                           128u


/*$PAGE*/
/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           CPU ERROR CODES
*********************************************************************************************************
*/

typedef enum cpu_err {

    CPU_ERR_NONE                            =         0u,
    CPU_ERR_NULL_PTR                        =        10u,

    CPU_ERR_NAME_SIZE                       =      1000u,

    CPU_ERR_TS_FREQ_INVALID                 =      2000u

} CPU_ERR;


/*
*********************************************************************************************************
*                                      CPU TIMESTAMP DATA TYPES
*
* Note(s) : (1) CPU timestamp timer data type defined to the binary-multiple of 8-bit octets as configured 
*               by 'CPU_CFG_TS_TMR_SIZE' (see 'cpu_cfg.h  CPU TIMESTAMP CONFIGURATION  Note #2').
*********************************************************************************************************
*/

typedef  CPU_INT32U  CPU_TS32;
typedef  CPU_INT64U  CPU_TS64;

typedef  CPU_TS32    CPU_TS;                                    /* Req'd for backwards-compatibility.                   */


#if     (CPU_CFG_TS_TMR_EN   == DEF_ENABLED)                    /* CPU ts tmr defined to cfg'd word size (see Note #1). */
#if     (CPU_CFG_TS_TMR_SIZE == CPU_WORD_SIZE_08)
typedef  CPU_INT08U  CPU_TS_TMR;
#elif   (CPU_CFG_TS_TMR_SIZE == CPU_WORD_SIZE_16)
typedef  CPU_INT16U  CPU_TS_TMR;
#elif   (CPU_CFG_TS_TMR_SIZE == CPU_WORD_SIZE_64)
typedef  CPU_INT64U  CPU_TS_TMR;
#else                                                           /* CPU ts tmr dflt size = 32-bits.                      */
typedef  CPU_INT32U  CPU_TS_TMR;
#endif
#endif


/*
*********************************************************************************************************
*                               CPU TIMESTAMP TIMER FREQUENCY DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT32U  CPU_TS_TMR_FREQ;


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/

#if    (CPU_CFG_NAME_EN   == DEF_ENABLED)
CPU_CORE_EXT  CPU_CHAR         CPU_Name[CPU_CFG_NAME_SIZE];     /* CPU host name.                                       */
#endif


#if ((CPU_CFG_TS_32_EN    == DEF_ENABLED)  && \
     (CPU_CFG_TS_TMR_SIZE <  CPU_WORD_SIZE_32))
CPU_CORE_EXT  CPU_TS32         CPU_TS_32_Accum;                 /* 32-bit accum'd ts  (in ts tmr cnts).                 */
CPU_CORE_EXT  CPU_TS_TMR       CPU_TS_32_TmrPrev;               /* 32-bit ts prev tmr (in ts tmr cnts).                 */
#endif

#if ((CPU_CFG_TS_64_EN    == DEF_ENABLED)  && \
     (CPU_CFG_TS_TMR_SIZE <  CPU_WORD_SIZE_64))
CPU_CORE_EXT  CPU_TS64         CPU_TS_64_Accum;                 /* 64-bit accum'd ts  (in ts tmr cnts).                 */
CPU_CORE_EXT  CPU_TS_TMR       CPU_TS_64_TmrPrev;               /* 64-bit ts prev tmr (in ts tmr cnts).                 */
#endif

#if  (CPU_CFG_TS_TMR_EN   == DEF_ENABLED)
CPU_CORE_EXT  CPU_TS_TMR_FREQ  CPU_TS_TmrFreq_Hz;               /* CPU ts tmr freq (in Hz).                             */
#endif


#ifdef  CPU_CFG_INT_DIS_MEAS_EN
CPU_CORE_EXT  CPU_INT16U       CPU_IntDisMeasCtr;               /* Nbr tot    ints dis'd ctr.                           */
CPU_CORE_EXT  CPU_INT16U       CPU_IntDisNestCtr;               /* Nbr nested ints dis'd ctr.                           */
                                                                /* Ints dis'd time (in ts tmr cnts) : ...               */
CPU_CORE_EXT  CPU_TS_TMR       CPU_IntDisMeasStart_cnts;        /* ...  start time.                                     */
CPU_CORE_EXT  CPU_TS_TMR       CPU_IntDisMeasStop_cnts;         /* ...  stop  time.                                     */
CPU_CORE_EXT  CPU_TS_TMR       CPU_IntDisMeasOvrhd_cnts;        /* ...        time meas ovrhd.                          */
CPU_CORE_EXT  CPU_TS_TMR       CPU_IntDisMeasMaxCur_cnts;       /* ...     resetable max time dis'd.                    */
CPU_CORE_EXT  CPU_TS_TMR       CPU_IntDisMeasMax_cnts;          /* ... non-resetable max time dis'd.                    */
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               MACRO'S
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         CPU_SW_EXCEPTION()
*
* Description : Trap unrecoverable software exception.
*
* Argument(s) : err_rtn_val     Error type &/or value of the calling function to return (see Note #2b).
*
* Return(s)   : none.
*
* Caller(s)   : various.
*
* Note(s)     : (1) CPU_SW_EXCEPTION() deadlocks the current code execution -- whether multi-tasked/
*                   -processed/-threaded or single-threaded -- when the current code execution cannot 
*                   gracefully recover or report a fault or exception condition.
*
*                   Example CPU_SW_EXCEPTION() call :
*
*                       void  Fnct (CPU_ERR  *p_err)
*                       {
*                           :
*
*                           if (p_err == (CPU_ERR *)0) {        If 'p_err' NULL, cannot return error ...
*                               CPU_SW_EXCEPTION(;);            ... so trap invalid argument exception.
*                           }
*
*                           :
*                       }
*
*                   See also 'cpu_core.c  CPU_SW_Exception()  Note #1'.
*
*               (2) (a) CPU_SW_EXCEPTION()  MAY be developer-implemented to output &/or handle any error or 
*                       exception conditions; but since CPU_SW_EXCEPTION() is intended to trap unrecoverable 
*                       software  conditions, it is recommended that developer-implemented versions prevent 
*                       execution of any code following calls to CPU_SW_EXCEPTION() by deadlocking the code 
*                       (see Note #1).
*
*                           Example CPU_SW_EXCEPTION() :
*
*                               #define  CPU_SW_EXCEPTION(err_rtn_val)      do {                         \
*                                                                               Log(__FILE__, __LINE__); \
*                                                                               CPU_SW_Exception();      \
*                                                                           } while (0)
*
*                   (b) (1) However, if execution of code following calls to CPU_SW_EXCEPTION() is required 
*                           (e.g. for automated testing); it is recommended that the last statement in 
*                           developer-implemented versions be to return from the current function to prevent 
*                           possible software exception(s) in the current function from triggering CPU &/or 
*                           hardware exception(s).
*
*                           Example CPU_SW_EXCEPTION() :
*
*                               #define  CPU_SW_EXCEPTION(err_rtn_val)      do {                         \
*                                                                               Log(__FILE__, __LINE__); \
*                                                                               return  err_rtn_val;     \
*                                                                           } while (0)
*
*                           (A) Note that 'err_rtn_val' in the return statement MUST NOT be enclosed in 
*                               parentheses.  This allows CPU_SW_EXCEPTION() to return from functions that 
*                               return 'void', i.e. NO return type or value (see also Note #2b2A).
*$PAGE*
*                       (2) In order for CPU_SW_EXCEPTION() to return from functions with various return 
*                           types/values, each caller function MUST pass an appropriate error return type 
*                           & value to CPU_SW_EXCEPTION().
*
*                           (A) Note that CPU_SW_EXCEPTION()  MUST NOT be passed any return type or value 
*                               for functions that return 'void', i.e. NO return type or value; but SHOULD 
*                               instead be passed a single semicolon.  This prevents possible compiler 
*                               warnings that CPU_SW_EXCEPTION() is passed too few arguments.  However, 
*                               the compiler may warn that CPU_SW_EXCEPTION() does NOT prevent creating 
*                               null statements on lines with NO other code statements.
*
*                           Example CPU_SW_EXCEPTION() calls :
*
*                               void  Fnct (CPU_ERR  *p_err)
*                               {
*                                   :
*
*                                   if (p_err == (CPU_ERR *)0) {
*                                       CPU_SW_EXCEPTION(;);            Exception macro returns NO value
*                                   }                                       (see Note #2b2A)
*
*                                   :
*                               }
*
*                               CPU_BOOLEAN  Fnct (CPU_ERR  *p_err)
*                               {
*                                   :
*
*                                   if (p_err == (CPU_ERR *)0) {
*                                       CPU_SW_EXCEPTION(DEF_FAIL);     Exception macro returns 'DEF_FAIL'
*                                   }
*
*                                   :
*                               }
*
*                               OBJ  *Fnct (CPU_ERR  *p_err)
*                               {
*                                   :
*
*                                   if (p_err == (CPU_ERR *)0) {
*                                       CPU_SW_EXCEPTION((OBJ *)0);     Exception macro returns NULL 'OBJ *'
*                                   }
*
*                                   :
*                               }
*
*********************************************************************************************************
*/

#ifndef  CPU_SW_EXCEPTION                                                       /* See Note #2.                         */
#define  CPU_SW_EXCEPTION(err_rtn_val)              do {                    \
                                                        CPU_SW_Exception(); \
                                                    } while (0)
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                           CPU_VAL_UNUSED()
*
* Description : 
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : #### various.
*
* Note(s)     : none.
*********************************************************************************************************
*/


#define  CPU_VAL_UNUSED(val)        ((void)&(val));


#define  CPU_VAL_IGNORED(val)       CPU_VAL_UNUSED(val)


/*$PAGE*/
/*
*********************************************************************************************************
*                                          CPU_TYPE_CREATE()
*
* Description : Creates a generic type value.
*
* Argument(s) : char_1      1st ASCII character to create generic type value.
*
*               char_2      2nd ASCII character to create generic type value.
*
*               char_3      3rd ASCII character to create generic type value.
*
*               char_4      4th ASCII character to create generic type value.
*
* Return(s)   : 32-bit generic type value.
*
* Caller(s)   : various.
*
* Note(s)     : (1) (a) Generic type values should be #define'd with large, non-trivial values to trap 
*                       & discard invalid/corrupted objects based on type value.
*
*                       In other words, by assigning large, non-trivial values to valid objects' type 
*                       fields; the likelihood that an object with an unassigned &/or corrupted type 
*                       field will contain a value is highly improbable & therefore the object itself 
*                       will be trapped as invalid.
*
*                   (b) (1) CPU_TYPE_CREATE()  creates a 32-bit type value from four values.
*
*                       (2) Ideally, generic type values SHOULD be created from 'CPU_CHAR' characters to 
*                           represent ASCII string abbreviations of the specific object types.  Memory 
*                           displays of object type values will display the specific object types with 
*                           their chosen ASCII names.
*
*                           Examples :
*
*                               #define  FILE_TYPE  CPU_TYPE_CREATE('F', 'I', 'L', 'E')
*                               #define  BUF_TYPE   CPU_TYPE_CREATE('B', 'U', 'F', ' ')
*********************************************************************************************************
*/

#if     (CPU_CFG_ENDIAN_TYPE == CPU_ENDIAN_TYPE_BIG)
#define  CPU_TYPE_CREATE(char_1, char_2, char_3, char_4)        (((CPU_INT32U)((CPU_INT08U)(char_1)) << (3u * DEF_OCTET_NBR_BITS)) | \
                                                                 ((CPU_INT32U)((CPU_INT08U)(char_2)) << (2u * DEF_OCTET_NBR_BITS)) | \
                                                                 ((CPU_INT32U)((CPU_INT08U)(char_3)) << (1u * DEF_OCTET_NBR_BITS)) | \
                                                                 ((CPU_INT32U)((CPU_INT08U)(char_4)) << (0u * DEF_OCTET_NBR_BITS)))

#else

#if    ((CPU_CFG_DATA_SIZE   == CPU_WORD_SIZE_64) || \
        (CPU_CFG_DATA_SIZE   == CPU_WORD_SIZE_32))
#define  CPU_TYPE_CREATE(char_1, char_2, char_3, char_4)        (((CPU_INT32U)((CPU_INT08U)(char_1)) << (0u * DEF_OCTET_NBR_BITS)) | \
                                                                 ((CPU_INT32U)((CPU_INT08U)(char_2)) << (1u * DEF_OCTET_NBR_BITS)) | \
                                                                 ((CPU_INT32U)((CPU_INT08U)(char_3)) << (2u * DEF_OCTET_NBR_BITS)) | \
                                                                 ((CPU_INT32U)((CPU_INT08U)(char_4)) << (3u * DEF_OCTET_NBR_BITS)))


#elif   (CPU_CFG_DATA_SIZE   == CPU_WORD_SIZE_16)
#define  CPU_TYPE_CREATE(char_1, char_2, char_3, char_4)        (((CPU_INT32U)((CPU_INT08U)(char_1)) << (2u * DEF_OCTET_NBR_BITS)) | \
                                                                 ((CPU_INT32U)((CPU_INT08U)(char_2)) << (3u * DEF_OCTET_NBR_BITS)) | \
                                                                 ((CPU_INT32U)((CPU_INT08U)(char_3)) << (0u * DEF_OCTET_NBR_BITS)) | \
                                                                 ((CPU_INT32U)((CPU_INT08U)(char_4)) << (1u * DEF_OCTET_NBR_BITS)))

#else                                                           /* Dflt CPU_WORD_SIZE_08.                               */
#define  CPU_TYPE_CREATE(char_1, char_2, char_3, char_4)        (((CPU_INT32U)((CPU_INT08U)(char_1)) << (3u * DEF_OCTET_NBR_BITS)) | \
                                                                 ((CPU_INT32U)((CPU_INT08U)(char_2)) << (2u * DEF_OCTET_NBR_BITS)) | \
                                                                 ((CPU_INT32U)((CPU_INT08U)(char_3)) << (1u * DEF_OCTET_NBR_BITS)) | \
                                                                 ((CPU_INT32U)((CPU_INT08U)(char_4)) << (0u * DEF_OCTET_NBR_BITS)))
#endif
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*
* Note(s) : (1) CPU interrupts disabled time measurement functions prototyped/defined only if 
*               CPU_CFG_INT_DIS_MEAS_EN  #define'd in 'cpu_cfg.h'.
*
*           (2) (a) CPU_CntLeadZeros()  defined in :
*
*                   (1) 'cpu_a.asm',  if CPU_CFG_LEAD_ZEROS_ASM_PRESENT       #define'd in 'cpu.h'/
*                                         'cpu_cfg.h' to enable assembly-optimized function(s)
*
*                   (2) 'cpu_core.c', if CPU_CFG_LEAD_ZEROS_ASM_PRESENT   NOT #define'd in 'cpu.h'/
*                                         'cpu_cfg.h' to enable C-source-optimized function(s)
*
*               (b) CPU_CntTrailZeros() defined in :
*
*                   (1) 'cpu_a.asm',  if CPU_CFG_TRAIL_ZEROS_ASM_PRESENT      #define'd in 'cpu.h'/
*                                         'cpu_cfg.h' to enable assembly-optimized function(s)
*
*                   (2) 'cpu_core.c', if CPU_CFG_TRAIL_ZEROS_ASM_PRESENT  NOT #define'd in 'cpu.h'/
*                                         'cpu_cfg.h' to enable C-source-optimized function(s)
*********************************************************************************************************
*/

void             CPU_Init                 (void);

void             CPU_SW_Exception         (void);



#if (CPU_CFG_NAME_EN == DEF_ENABLED)                                    /* -------------- CPU NAME FNCTS -------------- */
void             CPU_NameClr              (void);

void             CPU_NameGet              (       CPU_CHAR  *p_name,
                                                  CPU_ERR   *p_err);

void             CPU_NameSet              (const  CPU_CHAR  *p_name,
                                                  CPU_ERR   *p_err);
#endif



                                                                        /* --------------- CPU TS FNCTS --------------- */
#if (CPU_CFG_TS_32_EN == DEF_ENABLED)
CPU_TS32         CPU_TS_Get32             (void);
#endif

#if (CPU_CFG_TS_64_EN == DEF_ENABLED)
CPU_TS64         CPU_TS_Get64             (void);
#endif

#if (CPU_CFG_TS_EN    == DEF_ENABLED)
void             CPU_TS_Update            (void);
#endif


#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)                                  /* ------------- CPU TS TMR FNCTS ------------- */
CPU_TS_TMR_FREQ  CPU_TS_TmrFreqGet        (CPU_ERR          *p_err);

void             CPU_TS_TmrFreqSet        (CPU_TS_TMR_FREQ   freq_hz);
#endif



#ifdef  CPU_CFG_INT_DIS_MEAS_EN                                         /* -------- CPU INT DIS TIME MEAS FNCTS ------- */
                                                                        /* See Note #1.                                 */
CPU_TS_TMR       CPU_IntDisMeasMaxCurReset(void);

CPU_TS_TMR       CPU_IntDisMeasMaxCurGet  (void);

CPU_TS_TMR       CPU_IntDisMeasMaxGet     (void);


void             CPU_IntDisMeasStart      (void);

void             CPU_IntDisMeasStop       (void);
#endif



                                                                        /* ----------- CPU CNT ZEROS FNCTS ------------ */
CPU_DATA         CPU_CntLeadZeros         (CPU_DATA    val);

#if     (CPU_CFG_DATA_SIZE_MAX >= CPU_WORD_SIZE_08)
CPU_DATA         CPU_CntLeadZeros08       (CPU_INT08U  val);
#endif
#if     (CPU_CFG_DATA_SIZE_MAX >= CPU_WORD_SIZE_16)
CPU_DATA         CPU_CntLeadZeros16       (CPU_INT16U  val);
#endif
#if     (CPU_CFG_DATA_SIZE_MAX >= CPU_WORD_SIZE_32)
CPU_DATA         CPU_CntLeadZeros32       (CPU_INT32U  val);
#endif
#if     (CPU_CFG_DATA_SIZE_MAX >= CPU_WORD_SIZE_64)
CPU_DATA         CPU_CntLeadZeros64       (CPU_INT64U  val);
#endif


CPU_DATA         CPU_CntTrailZeros        (CPU_DATA    val);

#if     (CPU_CFG_DATA_SIZE_MAX >= CPU_WORD_SIZE_08)
CPU_DATA         CPU_CntTrailZeros08      (CPU_INT08U  val);
#endif
#if     (CPU_CFG_DATA_SIZE_MAX >= CPU_WORD_SIZE_16)
CPU_DATA         CPU_CntTrailZeros16      (CPU_INT16U  val);
#endif
#if     (CPU_CFG_DATA_SIZE_MAX >= CPU_WORD_SIZE_32)
CPU_DATA         CPU_CntTrailZeros32      (CPU_INT32U  val);
#endif
#if     (CPU_CFG_DATA_SIZE_MAX >= CPU_WORD_SIZE_64)
CPU_DATA         CPU_CntTrailZeros64      (CPU_INT64U  val);
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*                                      DEFINED IN PRODUCT'S BSP
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          CPU_TS_TmrInit()
*
* Description : Initialize & start CPU timestamp timer.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : CPU_TS_Init().
*
*               This function is an INTERNAL CPU module function & MUST be implemented by application/
*               BSP function(s) [see Note #1] but MUST NOT be called by application function(s).
*
* Note(s)     : (1) CPU_TS_TmrInit() is an application/BSP function that MUST be defined by the developer 
*                   if either of the following CPU features is enabled :
*
*                   (a) CPU timestamps
*                   (b) CPU interrupts disabled time measurements
*
*                   See 'cpu_cfg.h  CPU TIMESTAMP CONFIGURATION  Note #1'
*                     & 'cpu_cfg.h  CPU INTERRUPTS DISABLED TIME MEASUREMENT CONFIGURATION  Note #1a'.
*
*               (2) (a) Timer count values MUST be returned via word-size-configurable 'CPU_TS_TMR' 
*                       data type.
*
*                       (1) If timer has more bits, truncate timer values' higher-order bits greater 
*                           than the configured 'CPU_TS_TMR' timestamp timer data type word size.
*
*                       (2) Since the timer MUST NOT have less bits than the configured 'CPU_TS_TMR' 
*                           timestamp timer data type word size; 'CPU_CFG_TS_TMR_SIZE' MUST be 
*                           configured so that ALL bits in 'CPU_TS_TMR' data type are significant.
*
*                           In other words, if timer size is not a binary-multiple of 8-bit octets 
*                           (e.g. 20-bits or even 24-bits), then the next lower, binary-multiple 
*                           octet word size SHOULD be configured (e.g. to 16-bits).  However, the 
*                           minimum supported word size for CPU timestamp timers is 8-bits.
*
*                       See also 'cpu_cfg.h   CPU TIMESTAMP CONFIGURATION  Note #2'
*                              & 'cpu_core.h  CPU TIMESTAMP DATA TYPES     Note #1'.
*
*                   (b) Timer SHOULD be an 'up'  counter whose values increase with each time count.
*
*                   (c) When applicable, timer period SHOULD be less than the typical measured time 
*                       but MUST be less than the maximum measured time; otherwise, timer resolution 
*                       inadequate to measure desired times.
*
*                   See also 'CPU_TS_TmrRd()  Note #2'.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
void  CPU_TS_TmrInit(void);
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                           CPU_TS_TmrRd()
*
* Description : Get current CPU timestamp timer count value.
*
* Argument(s) : none.
*
* Return(s)   : Timestamp timer count (see Notes #2a & #2b).
*
* Caller(s)   : CPU_TS_Init(),
*               CPU_TS_Get32(),
*               CPU_TS_Get64(),
*               CPU_IntDisMeasStart(),
*               CPU_IntDisMeasStop().
*
*               This function is an INTERNAL CPU module function & MUST be implemented by application/
*               BSP function(s) [see Note #1] but SHOULD NOT be called by application function(s).
*
* Note(s)     : (1) CPU_TS_TmrRd() is an application/BSP function that MUST be defined by the developer 
*                   if either of the following CPU features is enabled :
*
*                   (a) CPU timestamps
*                   (b) CPU interrupts disabled time measurements
*
*                   See 'cpu_cfg.h  CPU TIMESTAMP CONFIGURATION  Note #1'
*                     & 'cpu_cfg.h  CPU INTERRUPTS DISABLED TIME MEASUREMENT CONFIGURATION  Note #1a'.
*
*               (2) (a) Timer count values MUST be returned via word-size-configurable 'CPU_TS_TMR' 
*                       data type.
*
*                       (1) If timer has more bits, truncate timer values' higher-order bits greater 
*                           than the configured 'CPU_TS_TMR' timestamp timer data type word size.
*
*                       (2) Since the timer MUST NOT have less bits than the configured 'CPU_TS_TMR' 
*                           timestamp timer data type word size; 'CPU_CFG_TS_TMR_SIZE' MUST be 
*                           configured so that ALL bits in 'CPU_TS_TMR' data type are significant.
*
*                           In other words, if timer size is not a binary-multiple of 8-bit octets 
*                           (e.g. 20-bits or even 24-bits), then the next lower, binary-multiple 
*                           octet word size SHOULD be configured (e.g. to 16-bits).  However, the 
*                           minimum supported word size for CPU timestamp timers is 8-bits.
*
*                       See also 'cpu_cfg.h   CPU TIMESTAMP CONFIGURATION  Note #2'
*                              & 'cpu_core.h  CPU TIMESTAMP DATA TYPES     Note #1'.
*
*                   (b) Timer SHOULD be an 'up'  counter whose values increase with each time count.
*
*                       (1) If timer is a 'down' counter whose values decrease with each time count,
*                           then the returned timer value MUST be ones-complemented.
*
*                   (c) (1) When applicable, the amount of time measured by CPU timestamps is 
*                           calculated by either of the following equations :
*
*                           (A) Time measured  =  Number timer counts  *  Timer period
*
*                                   where
*
*                                       Number timer counts     Number of timer counts measured 
*                                       Timer period            Timer's period in some units of 
*                                                                   (fractional) seconds
*                                       Time measured           Amount of time measured, in same 
*                                                                   units of (fractional) seconds 
*                                                                   as the Timer period
*
*                                                  Number timer counts
*                           (B) Time measured  =  ---------------------
*                                                    Timer frequency
*
*                                   where
*
*                                       Number timer counts     Number of timer counts measured
*                                       Timer frequency         Timer's frequency in some units 
*                                                                   of counts per second
*                                       Time measured           Amount of time measured, in seconds
*
*                       (2) Timer period SHOULD be less than the typical measured time but MUST be less 
*                           than the maximum measured time; otherwise, timer resolution inadequate to 
*                           measure desired times.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
CPU_TS_TMR  CPU_TS_TmrRd(void);
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                         CPU_TSxx_to_uSec()
*
* Description : Convert a 32-/64-bit CPU timestamp from timer counts to microseconds.
*
* Argument(s) : ts_cnts   CPU timestamp (in timestamp timer counts [see Note #2aA]).
*
* Return(s)   : Converted CPU timestamp (in microseconds           [see Note #2aD]).
*
* Caller(s)   : Application.
*
*               This function is an (optional) CPU module application programming interface (API) 
*               function which MAY be implemented by application/BSP function(s) [see Note #1] & 
*               MAY be called by application function(s).
*
* Note(s)     : (1) CPU_TS32_to_uSec()/CPU_TS64_to_uSec() are application/BSP functions that MAY be 
*                   optionally defined by the developer when either of the following CPU features is 
*                   enabled :
*
*                   (a) CPU timestamps
*                   (b) CPU interrupts disabled time measurements
*
*                   See 'cpu_cfg.h  CPU TIMESTAMP CONFIGURATION  Note #1'
*                     & 'cpu_cfg.h  CPU INTERRUPTS DISABLED TIME MEASUREMENT CONFIGURATION  Note #1a'.
*
*               (2) (a) The amount of time measured by CPU timestamps is calculated by either of 
*                       the following equations :
*
*                                                                        10^6 microseconds
*                       (1) Time measured  =   Number timer counts   *  -------------------  *  Timer period
*                                                                            1 second
*
*                                              Number timer counts       10^6 microseconds
*                       (2) Time measured  =  ---------------------  *  -------------------
*                                                Timer frequency             1 second
*
*                               where
*
*                                   (A) Number timer counts     Number of timer counts measured
*                                   (B) Timer frequency         Timer's frequency in some units 
*                                                                   of counts per second
*                                   (C) Timer period            Timer's period in some units of 
*                                                                   (fractional)  seconds
*                                   (D) Time measured           Amount of time measured, 
*                                                                   in microseconds
*
*                   (b) Timer period SHOULD be less than the typical measured time but MUST be less 
*                       than the maximum measured time; otherwise, timer resolution inadequate to 
*                       measure desired times.
*
*                   (c) Specific implementations may convert any number of CPU_TS32 or CPU_TS64 bits 
*                       -- up to 32 or 64, respectively -- into microseconds.
*********************************************************************************************************
*/

#if (CPU_CFG_TS_32_EN == DEF_ENABLED)
CPU_INT64U  CPU_TS32_to_uSec(CPU_TS32  ts_cnts);
#endif

#if (CPU_CFG_TS_64_EN == DEF_ENABLED)
CPU_INT64U  CPU_TS64_to_uSec(CPU_TS64  ts_cnts);
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  CPU_CFG_NAME_EN
#error  "CPU_CFG_NAME_EN                       not #define'd in 'cpu_cfg.h'"
#error  "                                [MUST be  DEF_ENABLED ]           "
#error  "                                [     ||  DEF_DISABLED]           "

#elif  ((CPU_CFG_NAME_EN != DEF_ENABLED ) && \
        (CPU_CFG_NAME_EN != DEF_DISABLED))
#error  "CPU_CFG_NAME_EN                 illegally #define'd in 'cpu_cfg.h'"
#error  "                                [MUST be  DEF_ENABLED ]           "
#error  "                                [     ||  DEF_DISABLED]           "


#elif   (CPU_CFG_NAME_EN == DEF_ENABLED)

#ifndef  CPU_CFG_NAME_SIZE
#error  "CPU_CFG_NAME_SIZE                     not #define'd in 'cpu_cfg.h'"
#error  "                                [MUST be  >=   1]                 "
#error  "                                [     &&  <= 255]                 "

#elif   (DEF_CHK_VAL(CPU_CFG_NAME_SIZE,            \
                     1,                            \
                     DEF_INT_08U_MAX_VAL) != DEF_OK)
#error  "CPU_CFG_NAME_SIZE               illegally #define'd in 'cpu_cfg.h'"
#error  "                                [MUST be  >=   1]                 "
#error  "                                [     &&  <= 255]                 "
#endif

#endif




#ifndef  CPU_CFG_TS_32_EN
#error  "CPU_CFG_TS_32_EN                      not #define'd in 'cpu_cfg.h'"
#error  "                                [MUST be  DEF_DISABLED]           "
#error  "                                [     ||  DEF_ENABLED ]           "

#elif  ((CPU_CFG_TS_32_EN != DEF_DISABLED) && \
        (CPU_CFG_TS_32_EN != DEF_ENABLED ))
#error  "CPU_CFG_TS_32_EN                illegally #define'd in 'cpu_cfg.h'"
#error  "                                [MUST be  DEF_DISABLED]           "
#error  "                                [     ||  DEF_ENABLED ]           "

#endif


#ifndef  CPU_CFG_TS_64_EN
#error  "CPU_CFG_TS_64_EN                      not #define'd in 'cpu_cfg.h'"
#error  "                                [MUST be  DEF_DISABLED]           "
#error  "                                [     ||  DEF_ENABLED ]           "

#elif  ((CPU_CFG_TS_64_EN != DEF_DISABLED) && \
        (CPU_CFG_TS_64_EN != DEF_ENABLED ))
#error  "CPU_CFG_TS_64_EN                illegally #define'd in 'cpu_cfg.h'"
#error  "                                [MUST be  DEF_DISABLED]           "
#error  "                                [     ||  DEF_ENABLED ]           "

#endif

                                                                /* Correctly configured in 'cpu_core.h'; DO NOT MODIFY. */
#ifndef  CPU_CFG_TS_EN
#error  "CPU_CFG_TS_EN                         not #define'd in 'cpu_core.h'"
#error  "                                [MUST be  DEF_DISABLED]            "
#error  "                                [     ||  DEF_ENABLED ]            "

#elif  ((CPU_CFG_TS_EN != DEF_DISABLED) && \
        (CPU_CFG_TS_EN != DEF_ENABLED ))
#error  "CPU_CFG_TS_EN                   illegally #define'd in 'cpu_core.h'"
#error  "                                [MUST be  DEF_DISABLED]            "
#error  "                                [     ||  DEF_ENABLED ]            "

#endif


/*$PAGE*/
                                                                /* Correctly configured in 'cpu_core.h'; DO NOT MODIFY. */
#ifndef  CPU_CFG_TS_TMR_EN
#error  "CPU_CFG_TS_TMR_EN                     not #define'd in 'cpu_core.h'"
#error  "                                [MUST be  DEF_DISABLED]            "
#error  "                                [     ||  DEF_ENABLED ]            "

#elif  ((CPU_CFG_TS_TMR_EN != DEF_DISABLED) && \
        (CPU_CFG_TS_TMR_EN != DEF_ENABLED ))
#error  "CPU_CFG_TS_TMR_EN               illegally #define'd in 'cpu_core.h'"
#error  "                                [MUST be  DEF_DISABLED]            "
#error  "                                [     ||  DEF_ENABLED ]            "


#elif   (CPU_CFG_TS_TMR_EN == DEF_ENABLED)

#ifndef  CPU_CFG_TS_TMR_SIZE
#error  "CPU_CFG_TS_TMR_SIZE                   not #define'd in 'cpu_cfg.h'       "
#error  "                                [MUST be  CPU_WORD_SIZE_08   8-bit timer]"
#error  "                                [     ||  CPU_WORD_SIZE_16  16-bit timer]"
#error  "                                [     ||  CPU_WORD_SIZE_32  32-bit timer]"
#error  "                                [     ||  CPU_WORD_SIZE_64  64-bit timer]"

#elif  ((CPU_CFG_TS_TMR_SIZE != CPU_WORD_SIZE_08) && \
        (CPU_CFG_TS_TMR_SIZE != CPU_WORD_SIZE_16) && \
        (CPU_CFG_TS_TMR_SIZE != CPU_WORD_SIZE_32) && \
        (CPU_CFG_TS_TMR_SIZE != CPU_WORD_SIZE_64))
#error  "CPU_CFG_TS_TMR_SIZE             illegally #define'd in 'cpu_cfg.h'       "
#error  "                                [MUST be  CPU_WORD_SIZE_08   8-bit timer]"
#error  "                                [     ||  CPU_WORD_SIZE_16  16-bit timer]"
#error  "                                [     ||  CPU_WORD_SIZE_32  32-bit timer]"
#error  "                                [     ||  CPU_WORD_SIZE_64  64-bit timer]"
#endif

#endif



#ifndef  CPU_CFG_INT_DIS_MEAS_EN
#if 0                                                           /* Optionally configured in 'cpu_cfg.h'; DO NOT MODIFY. */
#error  "CPU_CFG_INT_DIS_MEAS_EN               not #define'd in 'cpu_cfg.h'"
#endif

#else

#ifndef  CPU_CFG_INT_DIS_MEAS_OVRHD_NBR
#error  "CPU_CFG_INT_DIS_MEAS_OVRHD_NBR        not #define'd in 'cpu_cfg.h' "
#error  "                                [MUST be  >= CPU_TIME_MEAS_NBR_MIN]"
#error  "                                [     ||  <= CPU_TIME_MEAS_NBR_MAX]"

#elif   (DEF_CHK_VAL(CPU_CFG_INT_DIS_MEAS_OVRHD_NBR, \
                     CPU_TIME_MEAS_NBR_MIN,          \
                     CPU_TIME_MEAS_NBR_MAX) != DEF_OK)
#error  "CPU_CFG_INT_DIS_MEAS_OVRHD_NBR  illegally #define'd in 'cpu_cfg.h' "
#error  "                                [MUST be  >= CPU_TIME_MEAS_NBR_MIN]"
#error  "                                [     ||  <= CPU_TIME_MEAS_NBR_MAX]"

#endif

#endif




#ifndef  CPU_CFG_LEAD_ZEROS_ASM_PRESENT
#if 0                                                           /* Optionally configured in 'cpu_cfg.h'; DO NOT MODIFY. */
#error  "CPU_CFG_LEAD_ZEROS_ASM_PRESENT        not #define'd in 'cpu.h'/'cpu_cfg.h'"
#endif
#endif


#ifndef  CPU_CFG_TRAIL_ZEROS_ASM_PRESENT
#if 0                                                           /* Optionally configured in 'cpu_cfg.h'; DO NOT MODIFY. */
#error  "CPU_CFG_TRAIL_ZEROS_ASM_PRESENT       not #define'd in 'cpu.h'/'cpu_cfg.h'"
#endif
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                    CPU PORT CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  CPU_CFG_ADDR_SIZE
#error  "CPU_CFG_ADDR_SIZE      not #define'd in 'cpu.h'"
#endif

#ifndef  CPU_CFG_DATA_SIZE
#error  "CPU_CFG_DATA_SIZE      not #define'd in 'cpu.h'"
#endif

#ifndef  CPU_CFG_DATA_SIZE_MAX
#error  "CPU_CFG_DATA_SIZE_MAX  not #define'd in 'cpu.h'"
#endif


/*
*********************************************************************************************************
*                                    LIBRARY CONFIGURATION ERRORS
*********************************************************************************************************
*/

                                                                /* See 'cpu_core.h  Note #1a'.                          */
#if     (LIB_VERSION < 13500u)
#error  "LIB_VERSION  [SHOULD be >= V1.35.00]"
#endif


/*
*********************************************************************************************************
*                                             MODULE END
*
* Note(s) : (1) See 'cpu_core.h  MODULE'.
*********************************************************************************************************
*/

#endif                                                          /* End of CPU core module include.                      */

