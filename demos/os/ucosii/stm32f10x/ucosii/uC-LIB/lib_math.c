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
* Filename      : lib_math.c
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
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#define    MICRIUM_SOURCE
#define    LIB_MATH_MODULE
#include  <lib_math.h>


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
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

RAND_NBR  Math_RandSeedCur;                                     /* Cur rand nbr seed.                                   */


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*$PAGE*/
/*
*********************************************************************************************************
*                                             Math_Init()
*
* Description : (1) Initialize Mathematic Module :
*
*                   (a) Initialize random number seed value
*
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (2) IEEE Std 1003.1, 2004 Edition, Section 'rand() : DESCRIPTION' states that "if rand()
*                   is called before any calls to srand() are made, the same sequence shall be generated
*                   as when srand() is first called with a seed value of 1".
*********************************************************************************************************
*/

void  Math_Init (void)
{
    Math_RandSetSeed((RAND_NBR)RAND_SEED_INIT_VAL);             /* See Note #2.                                         */
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                         Math_RandSetSeed()
*
* Description : Set the current pseudo-random number generator seed.
*
* Argument(s) : seed        Initial (or current) value to set for the pseudo-random number sequence.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) IEEE Std 1003.1, 2004 Edition, Section 'rand() : DESCRIPTION' states that "srand() 
*                   ... uses the argument as a seed for a new sequence of pseudo-random numbers to be 
*                   returned by subsequent calls to rand()".
*
*               (2) 'Math_RandSeedCur' MUST always be accessed exclusively in critical sections.
*
*                   See also 'Math_Rand()  Note #1b'.
*********************************************************************************************************
*/

void  Math_RandSetSeed (RAND_NBR  seed)
{
    CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();
    Math_RandSeedCur = seed;
    CPU_CRITICAL_EXIT();
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                             Math_Rand()
*
* Description : Calculate the next pseudo-random number.
*
* Argument(s) : none.
*
* Return(s)   : Next pseudo-random number in the sequence after 'Math_RandSeedCur'.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) The pseudo-random number generator is implemented as a Linear Congruential 
*                       Generator (LCG).
*
*                   (b) The pseudo-random number generated is in the range [0, RAND_LCG_PARAM_M].
*
*                   See also 'Math_RandSeed()  Note #1'.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'rand() : DESCRIPTION' states that "rand() 
*                       ... need not be reentrant ... [and] is not required to be thread-safe".
*
*                   (b) However, in order to implement Math_Rand() as re-entrant; 'Math_RandSeedCur' MUST 
*                       always be accessed & updated exclusively in critical sections.
*
*                   See also 'Math_RandSeed()  Note #2'.
*********************************************************************************************************
*/

RAND_NBR  Math_Rand (void)
{
    RAND_NBR  seed;
    RAND_NBR  rand_nbr;
    CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();
    seed             = Math_RandSeedCur;
    rand_nbr         = Math_RandSeed(seed);
    Math_RandSeedCur = rand_nbr;
    CPU_CRITICAL_EXIT();

    return (rand_nbr);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                           Math_RandSeed()
*
* Description : Calculate the next pseudo-random number.
*
* Argument(s) : seed        Initial (or current) value for the pseudo-random number sequence.
*
* Return(s)   : Next pseudo-random number in the sequence after 'seed'.
*
* Caller(s)   : Math_Rand(),
*               Application.
*
* Note(s)     : (1) (a) BSD/ANSI-C implements rand() as a Linear Congruential Generator (LCG) :
*
*                       (A) random_number       =  [(a * random_number ) + b]  modulo m
*                                        n + 1                        n
*
*                               where
*                                       (1) (a) random_number           Next     random number to generate
*                                                            n+1
*                                           (b) random_number           Previous random number    generated
*                                                            n
*
*                                       (2) a = RAND_LCG_PARAM_A        LCG multiplier
*                                       (3) b = RAND_LCG_PARAM_B        LCG incrementor
*                                       (4) m = RAND_LCG_PARAM_M + 1    LCG modulus
*
*                   (b) The pseudo-random number generated is in the range [0, RAND_LCG_PARAM_M].
*
                    See also 'lib_math.h  RANDOM NUMBER DEFINES  Note #1b'.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'rand() : DESCRIPTION' states that "rand() 
*                       ... need not be reentrant ... [and] is not required to be thread-safe".
*
*                   (b) However, Math_RandSeed() is re-entrant since it calculates the next random number 
*                       using ONLY local variables.
*********************************************************************************************************
*/

RAND_NBR  Math_RandSeed (RAND_NBR  seed)
{
    RAND_NBR  rand_nbr;


    rand_nbr = (((RAND_NBR)RAND_LCG_PARAM_A * seed) + (RAND_NBR)RAND_LCG_PARAM_B)  %  ((RAND_NBR)RAND_LCG_PARAM_M + 1u);

    return (rand_nbr);
}

