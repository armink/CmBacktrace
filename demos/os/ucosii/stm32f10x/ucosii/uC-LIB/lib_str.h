/*
*********************************************************************************************************
*                                                uC/LIB
*                                        CUSTOM LIBRARY MODULES
*
*                          (c) Copyright 2004-2012; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/LIB is provided in source form to registered licensees ONLY.  It is 
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
*                                       ASCII STRING MANAGEMENT
*
* Filename      : lib_str.h
* Version       : V1.37.01
* Programmer(s) : ITJ
*                 JDH
*********************************************************************************************************
* Note(s)       : (1) NO compiler-supplied standard library functions are used in library or product software.
*
*                     (a) ALL standard library functions are implemented in the custom library modules :
*
*                         (1) \<Custom Library Directory>\lib_*.*
*
*                         (2) \<Custom Library Directory>\Ports\<cpu>\<compiler>\lib*_a.*
*
*                               where
*                                       <Custom Library Directory>      directory path for custom library software
*                                       <cpu>                           directory name for specific processor (CPU)
*                                       <compiler>                      directory name for specific compiler
*
*                     (b) Product-specific library functions are implemented in individual products.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This string library header file is protected from multiple pre-processor inclusion through 
*               use of the string library module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  LIB_STR_MODULE_PRESENT                                 /* See Note #1.                                         */
#define  LIB_STR_MODULE_PRESENT


/*$PAGE*/
/*
*********************************************************************************************************
*                                 ASCII STRING CONFIGURATION DEFINES
*
* Note(s) : (1) Some ASCII string configuration #define's MUST be available PRIOR to including any 
*               application configuration (see 'INCLUDE FILES  Note #1a').
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                    STRING FLOATING POINT DEFINES
*
* Note(s) : (1) (a) (1) The maximum accuracy for 32-bit floating-point numbers :
*
*
*                             Maximum Accuracy            log [Internal-Base ^ (Number-Internal-Base-Digits)]
*                       32-bit Floating-point Number  =  -----------------------------------------------------
*                                                                         log [External-Base]
*
*                                                         log [2 ^ 24]
*                                                     =  --------------
*                                                           log [10]
*
*                                                     <  7.225  Base-10 Digits
*
*                           where
*                                   Internal-Base                   Internal number base of floating-
*                                                                       point numbers (i.e.  2)
*                                   External-Base                   External number base of floating-
*                                                                       point numbers (i.e. 10)
*                                   Number-Internal-Base-Digits     Number of internal number base
*                                                                       significant digits (i.e. 24)
*
*                   (2) Also, since some 32-bit floating-point calculations are converted to 32-bit 
*                       unsigned numbers, the maximum accuracy is limited to the maximum accuracy
*                       for 32-bit unsigned numbers of 9 digits.
*
*               (b) Some CPUs' &/or compilers' floating-point implementations MAY further reduce the 
*                   maximum accuracy.
*********************************************************************************************************
*/

#define  LIB_STR_FP_MAX_NBR_DIG_SIG_MIN                    1u
#define  LIB_STR_FP_MAX_NBR_DIG_SIG_MAX                    9u   /* See Note #1a2.                                       */
#define  LIB_STR_FP_MAX_NBR_DIG_SIG_DFLT                   7u   /* See Note #1a1.                                       */


/*$PAGE*/
/*
*********************************************************************************************************
*                                            INCLUDE FILES
*
* Note(s) : (1) The custom library software files are located in the following directories :
*
*               (a) \<Your Product Application>\lib_cfg.h
*
*               (b) \<Custom Library Directory>\lib_*.*
*
*                       where
*                               <Your Product Application>      directory path for Your Product's Application
*                               <Custom Library Directory>      directory path for custom library software
*
*           (2) CPU-configuration  software files are located in the following directories :
*
*               (a) \<CPU-Compiler Directory>\cpu_*.*
*               (b) \<CPU-Compiler Directory>\<cpu>\<compiler>\cpu*.*
*
*                       where
*                               <CPU-Compiler Directory>        directory path for common CPU-compiler software
*                               <cpu>                           directory name for specific processor (CPU)
*                               <compiler>                      directory name for specific compiler
*
*           (3) Compiler MUST be configured to include as additional include path directories :
*
*               (a) '\<Your Product Application>\' directory                            See Note #1a
*
*               (b) '\<Custom Library Directory>\' directory                            See Note #1b
*
*               (c) (1) '\<CPU-Compiler Directory>\'                  directory         See Note #2a
*                   (2) '\<CPU-Compiler Directory>\<cpu>\<compiler>\' directory         See Note #2b
*
*           (4) NO compiler-supplied standard library functions SHOULD be used.
*
*               #### The reference to standard library header files SHOULD be removed once all custom
*               library functions are implemented WITHOUT reference to ANY standard library function(s).
*
*               See also 'STANDARD LIBRARY MACRO'S  Note #1'.
*********************************************************************************************************
*/

#include  <cpu.h>

#include  <lib_def.h>
#include  <lib_ascii.h>

#include  <lib_cfg.h>

#if 0                                                           /* See Note #4.                                         */
#include  <stdio.h>
#endif


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   LIB_STR_MODULE
#define  LIB_STR_EXT
#else
#define  LIB_STR_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        DEFAULT CONFIGURATION
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                 STRING FLOATING POINT CONFIGURATION
*
* Note(s) : (1) Configure LIB_STR_CFG_FP_EN to enable/disable floating point string function(s).
*
*           (2) Configure LIB_STR_CFG_FP_MAX_NBR_DIG_SIG to configure the maximum number of significant 
*               digits to calculate &/or display for floating point string function(s).
*
*               See also 'STRING FLOATING POINT DEFINES  Note #1'.
*********************************************************************************************************
*/

                                                                /* Configure floating point feature(s) [see Note #1] :  */
#ifndef  LIB_STR_CFG_FP_EN
#define  LIB_STR_CFG_FP_EN                      DEF_DISABLED
                                                                /*   DEF_DISABLED     Floating point functions DISABLED */
                                                                /*   DEF_ENABLED      Floating point functions ENABLED  */
#endif

                                                                /* Configure floating point feature(s)' number of ...   */
                                                                /* ... significant digits (see Note #2).                */
#ifndef  LIB_STR_CFG_FP_MAX_NBR_DIG_SIG
#define  LIB_STR_CFG_FP_MAX_NBR_DIG_SIG         LIB_STR_FP_MAX_NBR_DIG_SIG_DFLT
#endif


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  STR_CR_LF                     "\r\n"
#define  STR_LF_CR                     "\n\r"
#define  STR_NEW_LINE                   STR_CR_LF
#define  STR_PARENT_PATH               ".."

#define  STR_CR_LF_LEN                 (sizeof(STR_CR_LF)       - 1)
#define  STR_LF_CR_LEN                 (sizeof(STR_LF_CR)       - 1)
#define  STR_NEW_LINE_LEN              (sizeof(STR_NEW_LINE)    - 1)
#define  STR_PARENT_PATH_LEN           (sizeof(STR_PARENT_PATH) - 1)


/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*$PAGE*/
/*
*********************************************************************************************************
*                                              MACRO'S
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      STANDARD LIBRARY MACRO'S
*
* Note(s) : (1) NO compiler-supplied standard library functions SHOULD be used.
*
*               #### The reference to standard memory functions SHOULD be removed once all custom library
*               functions are implemented WITHOUT reference to ANY standard library function(s).
*
*               See also 'INCLUDE FILES  Note #3'.
*********************************************************************************************************
*/

                                                                /* See Note #1.                                         */
#define  Str_FmtPrint                   snprintf
#define  Str_FmtScan                    sscanf


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

                                                                /* ------------------ STR LEN  FNCTS ------------------ */
CPU_SIZE_T   Str_Len            (const  CPU_CHAR      *pstr);

CPU_SIZE_T   Str_Len_N          (const  CPU_CHAR      *pstr,
                                        CPU_SIZE_T     len_max);


                                                                       /* ------------------ STR COPY FNCTS ------------------ */
CPU_CHAR    *Str_Copy           (       CPU_CHAR      *pstr_dest,
                                 const  CPU_CHAR      *pstr_src);

CPU_CHAR    *Str_Copy_N         (       CPU_CHAR      *pstr_dest,
                                 const  CPU_CHAR      *pstr_src,
                                        CPU_SIZE_T     len_max);


CPU_CHAR    *Str_Cat            (       CPU_CHAR      *pstr_dest,
                                 const  CPU_CHAR      *pstr_cat);

CPU_CHAR    *Str_Cat_N          (       CPU_CHAR      *pstr_dest,
                                 const  CPU_CHAR      *pstr_cat,
                                        CPU_SIZE_T     len_max);


                                                                       /* ------------------ STR CMP  FNCTS ------------------ */
CPU_INT16S   Str_Cmp            (const  CPU_CHAR      *p1_str,
                                 const  CPU_CHAR      *p2_str);

CPU_INT16S   Str_Cmp_N          (const  CPU_CHAR      *p1_str,
                                 const  CPU_CHAR      *p2_str,
                                        CPU_SIZE_T     len_max);

CPU_INT16S   Str_CmpIgnoreCase  (const  CPU_CHAR      *p1_str,
                                 const  CPU_CHAR      *p2_str);

CPU_INT16S   Str_CmpIgnoreCase_N(const  CPU_CHAR      *p1_str,
                                 const  CPU_CHAR      *p2_str,
                                        CPU_SIZE_T     len_max);


                                                                       /* ------------------ STR SRCH FNCTS ------------------ */
CPU_CHAR    *Str_Char           (const  CPU_CHAR      *pstr,
                                        CPU_CHAR       srch_char);

CPU_CHAR    *Str_Char_N         (const  CPU_CHAR      *pstr,
                                        CPU_SIZE_T     len_max,
                                        CPU_CHAR       srch_char);

CPU_CHAR    *Str_Char_Last      (const  CPU_CHAR      *pstr,
                                        CPU_CHAR       srch_char);

CPU_CHAR    *Str_Char_Last_N    (const  CPU_CHAR      *pstr,
                                        CPU_SIZE_T     len_max,
                                        CPU_CHAR       srch_char);

CPU_CHAR    *Str_Char_Replace   (       CPU_CHAR      *pstr,
                                        CPU_CHAR       char_srch,
                                        CPU_CHAR       char_replace);

CPU_CHAR    *Str_Char_Replace_N (       CPU_CHAR      *pstr,
                                        CPU_CHAR       char_srch,
                                        CPU_CHAR       char_replace,
                                        CPU_SIZE_T     len_max);

CPU_CHAR    *Str_Str            (const  CPU_CHAR      *pstr,
                                 const  CPU_CHAR      *pstr_srch);

CPU_CHAR    *Str_Str_N          (const  CPU_CHAR      *pstr,
                                 const  CPU_CHAR      *pstr_srch,
                                        CPU_SIZE_T     len_max);


/*$PAGE*/
                                                                       /* ------------------ STR FMT  FNCTS ------------------ */
CPU_CHAR    *Str_FmtNbr_Int32U  (       CPU_INT32U     nbr,
                                        CPU_INT08U     nbr_dig,
                                        CPU_INT08U     nbr_base,
                                        CPU_CHAR       lead_char,
                                        CPU_BOOLEAN    lower_case,
                                        CPU_BOOLEAN    nul,
                                        CPU_CHAR      *pstr);

CPU_CHAR    *Str_FmtNbr_Int32S  (       CPU_INT32S     nbr,
                                        CPU_INT08U     nbr_dig,
                                        CPU_INT08U     nbr_base,
                                        CPU_CHAR       lead_char,
                                        CPU_BOOLEAN    lower_case,
                                        CPU_BOOLEAN    nul,
                                        CPU_CHAR      *pstr);

#if (LIB_STR_CFG_FP_EN == DEF_ENABLED)
CPU_CHAR    *Str_FmtNbr_32      (       CPU_FP32       nbr,
                                        CPU_INT08U     nbr_dig,
                                        CPU_INT08U     nbr_dp,
                                        CPU_CHAR       lead_char,
                                        CPU_BOOLEAN    nul,
                                        CPU_CHAR      *pstr);
#endif


                                                                       /* ----------------- STR PARSE FNCTS ------------------ */
CPU_INT32U   Str_ParseNbr_Int32U(const  CPU_CHAR      *pstr,
                                        CPU_CHAR     **pstr_next,
                                        CPU_INT08U     nbr_base);

CPU_INT32S   Str_ParseNbr_Int32S(const  CPU_CHAR      *pstr,
                                        CPU_CHAR     **pstr_next,
                                        CPU_INT08U     nbr_base);


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  LIB_STR_CFG_FP_EN
#error  "LIB_STR_CFG_FP_EN                     not #define'd in 'lib_cfg.h'"
#error  "                                [MUST be  DEF_DISABLED]           "
#error  "                                [     ||  DEF_ENABLED ]           "

#elif  ((LIB_STR_CFG_FP_EN != DEF_DISABLED) && \
        (LIB_STR_CFG_FP_EN != DEF_ENABLED ))
#error  "LIB_STR_CFG_FP_EN               illegally #define'd in 'lib_cfg.h'"
#error  "                                [MUST be  DEF_DISABLED]           "
#error  "                                [     ||  DEF_ENABLED ]           "


#elif   (LIB_STR_CFG_FP_EN == DEF_ENABLED)

#ifndef  LIB_STR_CFG_FP_MAX_NBR_DIG_SIG
#error  "LIB_STR_CFG_FP_MAX_NBR_DIG_SIG        not #define'd in 'lib_cfg.h'          "
#error  "                                [MUST be  >= LIB_STR_FP_MAX_NBR_DIG_SIG_MIN]"
#error  "                                [     &&  <= LIB_STR_FP_MAX_NBR_DIG_SIG_MAX]"

#elif   (DEF_CHK_VAL(LIB_STR_CFG_FP_MAX_NBR_DIG_SIG,          \
                     LIB_STR_FP_MAX_NBR_DIG_SIG_MIN,          \
                     LIB_STR_FP_MAX_NBR_DIG_SIG_MAX) != DEF_OK)
#error  "LIB_STR_CFG_FP_MAX_NBR_DIG_SIG  illegally #define'd in 'lib_cfg.h'          "
#error  "                                [MUST be  >= LIB_STR_FP_MAX_NBR_DIG_SIG_MIN]"
#error  "                                [     &&  <= LIB_STR_FP_MAX_NBR_DIG_SIG_MAX]"
#endif

#endif


/*
*********************************************************************************************************
*                                             MODULE END
*
* Note(s) : (1) See 'lib_str.h  MODULE'.
*********************************************************************************************************
*/

#endif                                                          /* End of lib str module include.                       */

