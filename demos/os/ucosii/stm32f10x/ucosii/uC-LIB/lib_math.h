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
*                                        MATHEMATIC OPERATIONS
*
* Filename      : lib_math.h
* Version       : V1.37.01
* Programmer(s) : SR
*                 ITJ
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
*
*********************************************************************************************************
* Notice(s)     : (1) The Institute of Electrical and Electronics Engineers and The Open Group, have given
*                     us permission to reprint portions of their documentation.  Portions of this text are
*                     reprinted and reproduced in electronic form from the IEEE Std 1003.1, 2004 Edition,
*                     Standard for Information Technology -- Portable Operating System Interface (POSIX),
*                     The Open Group Base Specifications Issue 6, Copyright (C) 2001-2004 by the Institute
*                     of Electrical and Electronics Engineers, Inc and The Open Group.  In the event of any
*                     discrepancy between these versions and the original IEEE and The Open Group Standard,
*                     the original IEEE and The Open Group Standard is the referee document.  The original
*                     Standard can be obtained online at http://www.opengroup.org/unix/online.html.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This mathematics library header file is protected from multiple pre-processor inclusion 
*               through use of the mathematics library module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  LIB_MATH_MODULE_PRESENT                                /* See Note #1.                                         */
#define  LIB_MATH_MODULE_PRESENT


/*$PAGE*/
/*
*********************************************************************************************************
*                                            INCLUDE FILES
*
* Note(s) : (1) The custom library software files are located in the following directories :
*
*               (a) \<Custom Library Directory>\lib_*.*
*
*                       where
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
*               (a) '\<Custom Library Directory>\' directory                            See Note #1a
*
*               (b) (1) '\<CPU-Compiler Directory>\'                  directory         See Note #2a
*                   (2) '\<CPU-Compiler Directory>\<cpu>\<compiler>\' directory         See Note #2b
*
*           (4) NO compiler-supplied standard library functions SHOULD be used.
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <cpu_core.h>

#include  <lib_def.h>


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   LIB_MATH_MODULE
#define  LIB_MATH_EXT
#else
#define  LIB_MATH_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                        RANDOM NUMBER DEFINES
*
* Note(s) : (1) (a) IEEE Std 1003.1, 2004 Edition, Section 'rand() : DESCRIPTION' states that "if rand() 
*                   is called before any calls to srand() are made, the same sequence shall be generated 
*                   as when srand() is first called with a seed value of 1".
*
*               (b) (1) BSD/ANSI-C implements rand() as a Linear Congruential Generator (LCG) :
*
*                       (A) random_number       =  [(a * random_number ) + b]  modulo m
*                                        n + 1                        n
*
*                               where
*                                       (1) (a) random_number       Next     random number to generate
*                                                            n+1
*                                           (b) random_number       Previous random number    generated
*                                                            n
*                                           (c) random_number       Initial  random number seed
*                                                            0                      See also Note #1a
*
*                                       (2) a =   1103515245        LCG multiplier
*                                       (3) b =        12345        LCG incrementor
*                                       (4) m = RAND_MAX + 1        LCG modulus     See also Note #1b2
*
*                   (2) (A) IEEE Std 1003.1, 2004 Edition, Section 'rand() : DESCRIPTION' states that 
*                           "rand() ... shall compute a sequence of pseudo-random integers in the range 
*                           [0, {RAND_MAX}] with a period of at least 2^32".
*
*                       (B) However, BSD/ANSI-C 'stdlib.h' defines "RAND_MAX" as "0x7fffffff", or 2^31; 
*                           which therefore limits the range AND period to no more than 2^31.
*********************************************************************************************************
*/

#define  RAND_SEED_INIT_VAL                                1u   /* See Note #1a.                                        */

#define  RAND_LCG_PARAM_M                         0x7FFFFFFFu   /* See Note #1b2B.                                      */
#define  RAND_LCG_PARAM_A                         1103515245u   /* See Note #1b1A2.                                     */
#define  RAND_LCG_PARAM_B                              12345u   /* See Note #1b1A3.                                     */


/*$PAGE*/
/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       RANDOM NUMBER DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_INT32U  RAND_NBR;


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void      Math_Init       (void);

                                                                /* ------------------ RAND NBR FNCTS ------------------ */
void      Math_RandSetSeed(RAND_NBR  seed);

RAND_NBR  Math_Rand       (void);

RAND_NBR  Math_RandSeed   (RAND_NBR  seed);


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             MODULE END
*
* Note(s) : (1) See 'lib_math.h  MODULE'.
*********************************************************************************************************
*/

#endif                                                          /* End of lib math module include.                      */

