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
* Filename      : lib_str.c
* Version       : V1.37.01
* Programmer(s) : ITJ
*                 BAN
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
#define    LIB_STR_MODULE
#include  <lib_str.h>


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

static  const  CPU_INT32U  Str_MultOvfThTbl_Int32U[] = {
   (CPU_INT32U) DEF_INT_32U_MAX_VAL,                /*                Invalid base  0.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL /  1u),         /*                Invalid base  1.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL /  2u),         /* 32-bit mult ovf th for base  2.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL /  3u),         /* 32-bit mult ovf th for base  3.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL /  4u),         /* 32-bit mult ovf th for base  4.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL /  5u),         /* 32-bit mult ovf th for base  5.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL /  6u),         /* 32-bit mult ovf th for base  6.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL /  7u),         /* 32-bit mult ovf th for base  7.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL /  8u),         /* 32-bit mult ovf th for base  8.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL /  9u),         /* 32-bit mult ovf th for base  9.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 10u),         /* 32-bit mult ovf th for base 10.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 11u),         /* 32-bit mult ovf th for base 11.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 12u),         /* 32-bit mult ovf th for base 12.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 13u),         /* 32-bit mult ovf th for base 13.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 14u),         /* 32-bit mult ovf th for base 14.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 15u),         /* 32-bit mult ovf th for base 15.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 16u),         /* 32-bit mult ovf th for base 16.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 17u),         /* 32-bit mult ovf th for base 17.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 18u),         /* 32-bit mult ovf th for base 18.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 19u),         /* 32-bit mult ovf th for base 19.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 20u),         /* 32-bit mult ovf th for base 20.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 21u),         /* 32-bit mult ovf th for base 21.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 22u),         /* 32-bit mult ovf th for base 22.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 23u),         /* 32-bit mult ovf th for base 23.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 24u),         /* 32-bit mult ovf th for base 24.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 25u),         /* 32-bit mult ovf th for base 25.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 26u),         /* 32-bit mult ovf th for base 26.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 27u),         /* 32-bit mult ovf th for base 27.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 28u),         /* 32-bit mult ovf th for base 28.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 29u),         /* 32-bit mult ovf th for base 29.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 30u),         /* 32-bit mult ovf th for base 30.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 31u),         /* 32-bit mult ovf th for base 31.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 32u),         /* 32-bit mult ovf th for base 32.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 33u),         /* 32-bit mult ovf th for base 33.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 34u),         /* 32-bit mult ovf th for base 34.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 35u),         /* 32-bit mult ovf th for base 35.  */
   (CPU_INT32U)(DEF_INT_32U_MAX_VAL / 36u)          /* 32-bit mult ovf th for base 36.  */
};


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*$PAGE*/
/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  CPU_CHAR    *Str_FmtNbr_Int32  (       CPU_INT32U     nbr,
                                               CPU_INT08U     nbr_dig,
                                               CPU_INT08U     nbr_base,
                                               CPU_BOOLEAN    nbr_neg,
                                               CPU_CHAR       lead_char,
                                               CPU_BOOLEAN    lower_case,
                                               CPU_BOOLEAN    nul,
                                               CPU_CHAR      *pstr);

static  CPU_INT32U   Str_ParseNbr_Int32(const  CPU_CHAR      *pstr,
                                               CPU_CHAR     **pstr_next,
                                               CPU_INT08U     nbr_base,
                                               CPU_BOOLEAN    nbr_signed,
                                               CPU_BOOLEAN   *pnbr_neg);


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*$PAGE*/
/*
*********************************************************************************************************
*                                              Str_Len()
*
* Description : Calculate length of a string.
*
* Argument(s) : pstr        Pointer to string (see Note #1).
*
* Return(s)   : Length of string; number of characters in string before terminating NULL character 
*                   (see Note #2b1).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffer NOT modified.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'strlen() : DESCRIPTION' states that :
*
*                       (1) "The strlen() function shall compute the number of bytes in the string to 
*                            which 's' ('pstr') points," ...
*                       (2) "not including the terminating null byte."
*
*                   (b) IEEE Std 1003.1, 2004 Edition, Section 'strlen() : RETURN VALUE' states that :
*
*                       (1) "The strlen() function shall return the length of 's' ('pstr');" ...
*                       (2) "no return value shall be reserved to indicate an error."
*
*               (3) String length calculation terminates when :
*
*                   (a) String pointer points to NULL.
*                       (1) String buffer overlaps with NULL address.
*                       (2) String length calculated for string up to but NOT beyond or including
*                           the NULL address.
*
*                   (b) Terminating NULL character found.
*                       (1) String length calculated for string up to but NOT           including
*                           the NULL character (see Note #2a2).
*********************************************************************************************************
*/

CPU_SIZE_T  Str_Len (const  CPU_CHAR  *pstr)
{
    CPU_SIZE_T  len;


    len = Str_Len_N(pstr,
                    DEF_INT_CPU_U_MAX_VAL);

    return (len);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                             Str_Len_N()
*
* Description : Calculate length of a string, up to a maximum number of characters.
*
* Argument(s) : pstr        Pointer to string (see Note #1).
*
*               len_max     Maximum number of characters to search (see Note #3c).
*
* Return(s)   : Length of string; number of characters in string before terminating NULL character, 
*                   if terminating NULL character     found (see Note #2b1).
*
*               Requested maximum number of characters to search, 
*                   if terminating NULL character NOT found (see Note #3c).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffer NOT modified.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'strlen() : DESCRIPTION' states that :
*
*                       (1) "The strlen() function shall compute the number of bytes in the string to 
*                            which 's' ('pstr') points," ...
*                       (2) "not including the terminating null byte."
*
*                   (b) IEEE Std 1003.1, 2004 Edition, Section 'strlen() : RETURN VALUE' states that :
*
*                       (1) "The strlen() function shall return the length of 's' ('pstr');" ...
*                       (2) "no return value shall be reserved to indicate an error."
*
*               (3) String length calculation terminates when :
*
*                   (a) String pointer points to NULL.
*                       (1) String buffer overlaps with NULL address.
*                       (2) String length calculated for string up to but NOT beyond or including
*                           the NULL address.
*
*                   (b) Terminating NULL character found.
*                       (1) String length calculated for string up to but NOT           including
*                           the NULL character (see Note #2a2).
*
*                   (c) 'len_max' number of characters searched.
*                       (1) 'len_max' number of characters does NOT include the terminating NULL character.
*********************************************************************************************************
*/

CPU_SIZE_T  Str_Len_N (const  CPU_CHAR    *pstr,
                              CPU_SIZE_T   len_max)
{
    const  CPU_CHAR    *pstr_len;
           CPU_SIZE_T   len;


    pstr_len = pstr;
    len      = 0u;
    while (( pstr_len != (const CPU_CHAR *)  0 ) &&             /* Calc str len until NULL ptr (see Note #3a) ...       */
           (*pstr_len != (      CPU_CHAR  )'\0') &&             /* ... or NULL char found      (see Note #3b) ...       */
           ( len      <  (      CPU_SIZE_T)len_max)) {          /* ... or max nbr chars srch'd (see Note #3c).          */
        pstr_len++;
        len++;
    }

    return (len);                                               /* Rtn str len (see Note #3b1).                         */
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                             Str_Copy()
*
* Description : Copy source string to destination string buffer.
*
* Argument(s) : pstr_dest   Pointer to destination string buffer to receive source string copy   (see Note #1a).
*
*               pstr_src    Pointer to source      string to copy into destination string buffer (see Note #1b).
*
* Return(s)   : Pointer to destination string, if NO error(s) [see Note #2b1].
*
*               Pointer to NULL,               otherwise      (see Note #2b2A).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) Destination buffer size NOT validated; buffer overruns MUST be prevented by caller.
*
*                       (1) Destination buffer size MUST be large enough to accommodate the entire source
*                           string size including the terminating NULL character.
*
*                   (b) Source buffer NOT modified.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'strcpy() : DESCRIPTION' states that :
*
*                       (1) "The strcpy() function shall copy the string pointed to by 's2' ('pstr_src') 
*                            ... into the array pointed to by 's1' ('pstr_dest')" ...
*                       (2) "(including the terminating null byte)."
*
*                   (b) IEEE Std 1003.1, 2004 Edition, Section 'strcpy() : RETURN VALUE' states that :
*
*                       (1) "The strcpy() function shall return 's1' ('pstr_dest');" ...
*                       (2) "no return value is reserved to indicate an error."
*                           (A) #### This requirement is intentionally NOT implemented in order to return 
*                               NULL for any error(s).
*
*                   (c) IEEE Std 1003.1, 2004 Edition, Section 'strcpy() : DESCRIPTION' states that "if
*                       copying takes place between objects that overlap, the behavior is undefined".
*
*               (3) String copy terminates when :
*
*                   (a) Destination/Source string pointer(s) are passed NULL pointers.
*                       (1) No string copy performed; NULL pointer returned.
*
*                   (b) Destination/Source string pointer(s) point to NULL.
*                       (1) String buffer(s) overlap with NULL address; NULL pointer returned.
*
*                   (c) Source string's terminating NULL character found.
*                       (1) Entire source string copied into destination string buffer (see Note #2a).
*********************************************************************************************************
*/

CPU_CHAR  *Str_Copy (       CPU_CHAR  *pstr_dest,
                     const  CPU_CHAR  *pstr_src)
{
    CPU_CHAR  *pstr_rtn;


    pstr_rtn = Str_Copy_N(pstr_dest,
                          pstr_src,
                          DEF_INT_CPU_U_MAX_VAL);

    return (pstr_rtn);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                            Str_Copy_N()
*
* Description : Copy source string to destination string buffer, up to a maximum number of characters.
*
* Argument(s) : pstr_dest   Pointer to destination string buffer to receive source string copy   (see Note #1a).
*
*               pstr_src    Pointer to source      string to copy into destination string buffer (see Note #1b).
*
*               len_max     Maximum number of characters  to copy (see Notes #2a2 & #3d).
*
* Return(s)   : Pointer to destination string, if NO error(s) [see Note #2b1].
*
*               Pointer to NULL,               otherwise      (see Note #2b2A).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) Destination buffer size NOT validated; buffer overruns MUST be prevented by caller.
*
*                       (1) Destination buffer size MUST be large enough to accommodate the entire source
*                           string size including the terminating NULL character.
*
*                   (b) Source string buffer NOT modified.
*
*               (2) (a) (1) IEEE Std 1003.1, 2004 Edition, Section 'strncpy() : DESCRIPTION' states that :
*
*                           (A) "The strncpy() function shall copy ... the array pointed to by 's2' 
*                               ('pstr_src') to the array pointed to by 's1' ('pstr_dest')"; ...
*                           (B)  but "not more than 'n' ('len_max') bytes"                   ...
*                           (C)  &   "(bytes that follow a null byte are not copied)".
*
*                       (2) (A) IEEE Std 1003.1, 2004 Edition, Section 'strncpy() : DESCRIPTION' adds that 
*                              "if the array pointed to by 's2' ('pstr_src') is a string that is shorter 
*                               than 'n' ('len_max') bytes, null bytes shall be appended to the copy in 
*                               the array pointed to by 's1' ('pstr_dest'), until 'n' ('len_max') bytes 
*                               in all are written."
*
*                               (1) #### Since Str_Copy() limits the maximum number of characters to copy 
*                                   via Str_Copy_N() by the CPU's maximum number of addressable characters, 
*                                   this requirement is intentionally NOT implemented to avoid appending 
*                                   a potentially large number of unnecessary terminating NULL characters.
*
*                           (B) IEEE Std 1003.1, 2004 Edition, Section 'strncpy() : APPLICATION USAGE' also  
*                               states that "if there is no null byte in the first 'n' ('len_max') bytes of 
*                               the array pointed to by 's2' ('pstr_src'), the result is not null-terminated".
*
*                   (b) IEEE Std 1003.1, 2004 Edition, Section 'strncpy() : RETURN VALUE' states that :
*
*                       (1) "The strncpy() function shall return 's1' ('pstr_dest');" ...
*                       (2) "no return value is reserved to indicate an error."
*                           (A) #### This requirement is intentionally ignored in order to return NULL 
*                               for any error(s).
*
*                   (c) IEEE Std 1003.1, 2004 Edition, Section 'strncpy() : DESCRIPTION' states that "if
*                       copying takes place between objects that overlap, the behavior is undefined".
*
*               (3) String copy terminates when :
*
*                   (a) Destination/Source string pointer(s) are passed NULL pointers.
*                       (1) No string copy performed; NULL pointer returned.
*
*                   (b) Destination/Source string pointer(s) point to NULL.
*                       (1) String buffer(s) overlap with NULL address; NULL pointer returned.
*
*                   (c) Source string's terminating NULL character found.
*                       (1) Entire source string copied into destination string buffer (see Note #2a1A).
*
*                   (d) 'len_max' number of characters copied.
*                       (1) 'len_max' number of characters MAY include the terminating NULL character 
*                           (see Note #2a1C).
*                       (2) Null copies allowed (i.e. zero-length copies).
*                           (A) No string copy performed; destination string returned  (see Note #2b1).
*********************************************************************************************************
*/
/*$PAGE*/
CPU_CHAR  *Str_Copy_N (       CPU_CHAR    *pstr_dest,
                       const  CPU_CHAR    *pstr_src,
                              CPU_SIZE_T   len_max)
{
           CPU_CHAR    *pstr_copy_dest;
    const  CPU_CHAR    *pstr_copy_src;
           CPU_SIZE_T   len_copy;

                                                                /* Rtn NULL if str ptr(s) NULL (see Note #3a1).         */
    if (pstr_dest == (CPU_CHAR *)0) {
        return ((CPU_CHAR *)0);
    }
    if (pstr_src  == (const CPU_CHAR *)0) {
        return ((CPU_CHAR *)0);
    }


    pstr_copy_dest = pstr_dest;
    pstr_copy_src  = pstr_src;
    len_copy       = 0u;

    while (( pstr_copy_dest != (      CPU_CHAR *)  0 ) &&       /* Copy str until NULL ptr(s)  [see Note #3b]  ...      */
           ( pstr_copy_src  != (const CPU_CHAR *)  0 ) &&
           (*pstr_copy_src  != (      CPU_CHAR  )'\0') &&       /* ... or NULL char found      (see Note #3c); ...      */
           ( len_copy       <  (      CPU_SIZE_T)len_max)) {    /* ... or max nbr chars copied (see Note #3d).          */
       *pstr_copy_dest = *pstr_copy_src;
        pstr_copy_dest++;
        pstr_copy_src++;
        len_copy++;
    }
                                                                /* Rtn NULL if NULL ptr(s) found  (see Note #3b1).      */
    if ((pstr_copy_dest == (      CPU_CHAR *)0) ||
        (pstr_copy_src  == (const CPU_CHAR *)0)) {
         return ((CPU_CHAR *)0);
    }

    if (len_copy < len_max) {                                   /* If  copy str len < max buf len (see Note #2a2A), ... */
       *pstr_copy_dest = (CPU_CHAR)'\0';                        /* ... copy NULL char  (see Note #3c1).                 */
    }


    return (pstr_dest);                                         /* Rtn ptr to dest str (see Note #2b1).                 */
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                              Str_Cat()
*
* Description : Append concatenation string to destination string.
*
* Argument(s) : pstr_dest   Pointer to destination   string to append concatenation  string (see Note #1a).
*
*               pstr_cat    Pointer to concatenation string to append to destination string (see Note #1b).
*
* Return(s)   : Pointer to destination string, if NO error(s) [see Note #2b1].
*
*               Pointer to NULL,               otherwise      (see Note #2b2A).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) Destination buffer size NOT validated; buffer overruns MUST be prevented by caller.
*
*                       (1) Destination buffer size MUST be large enough to accommodate the entire 
*                           concatenated string size including the terminating NULL character.
*
*                   (b) Concatenation string buffer NOT modified.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'strcat() : DESCRIPTION' states that :
*
*                       (1) "The strcat() function shall append a copy of the string pointed to by 's2' 
*                           ('pstr_cat') ... to the end of the string pointed to by 's1' ('pstr_dest')."
*
*                       (2) (A) "The initial byte of 's2' ('pstr_cat') overwrites the null byte at the 
*                                end of 's1' ('pstr_dest')."
*                           (B)  A "terminating null byte" is appended at the end of the concatenated 
*                                destination strings.
*
*                   (b) IEEE Std 1003.1, 2004 Edition, Section 'strcat() : RETURN VALUE' states that :
*
*                       (1) "The strcat() function shall return 's1' ('pstr_dest');" ...
*                       (2) "no return value shall be reserved to indicate an error."
*                           (A) #### This requirement is intentionally NOT implemented in order to return 
*                               NULL for any error(s).
*
*                   (c) IEEE Std 1003.1, 2004 Edition, Section 'strcat() : DESCRIPTION' states that "if
*                       copying takes place between objects that overlap, the behavior is undefined."
*
*               (3) String concatenation terminates when :
*
*                   (a) Destination/Concatenation string pointer(s) are passed NULL pointers.
*                       (1) No string concatenation performed; NULL pointer returned.
*
*                   (b) Destination/Concatenation string pointer(s) point to NULL.
*                       (1) String buffer(s) overlap with NULL address; NULL pointer returned.
*
*                   (c) Concatenation string's terminating NULL character found.
*                       (1) Entire concatenation string appended to destination string (see Note #2a1).
*********************************************************************************************************
*/

CPU_CHAR  *Str_Cat (       CPU_CHAR  *pstr_dest,
                    const  CPU_CHAR  *pstr_cat)
{
    CPU_CHAR  *pstr_rtn;


    pstr_rtn = Str_Cat_N(pstr_dest,
                         pstr_cat,
                         DEF_INT_CPU_U_MAX_VAL);

    return (pstr_rtn);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                             Str_Cat_N()
*
* Description : Append concatenation string to destination string, up to a maximum number of characters.
*
* Argument(s) : pstr_dest   Pointer to destination   string to append concatenation  string (see Note #1a).
*
*               pstr_cat    Pointer to concatenation string to append to destination string (see Note #1b).
*
*               len_max     Maximum number of characters to concatenate (see Notes #2a1B & #3d).
*
* Return(s)   : Pointer to destination string, if NO error(s) [see Note #2b1].
*
*               Pointer to NULL,               otherwise      (see Note #2b2A).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) Destination buffer size NOT validated; buffer overruns MUST be prevented by caller.
*
*                       (1) Destination buffer size MUST be large enough to accommodate the entire 
*                           concatenated string size including the terminating NULL character.
*
*                   (b) Concatenation string buffer NOT modified.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'strncat() : DESCRIPTION' states that :
*
*                       (1) (A) "The strncat() function shall append ... the array pointed to by 's2' 
*                               ('pstr_cat') to the end of the string pointed to by 's1' ('pstr_dest')" ...
*                           (B)  but "not more than 'n' ('len_max') bytes".
*
*                       (2) (A) "The initial byte of 's2' ('pstr_cat') overwrites the null byte at the 
*                                end of 's1' ('pstr_dest')."
*                           (B) "(a null byte and bytes that follow it are not appended)."
*                           (C) "A terminating null byte is always appended to the result."
*
*                   (b) IEEE Std 1003.1, 2004 Edition, Section 'strncat() : RETURN VALUE' states that :
*
*                       (1) "The strncat() function shall return 's1' ('pstr_dest');" ...
*                       (2) "no return value shall be reserved to indicate an error."
*                           (A) #### This requirement is intentionally NOT implemented in order to return 
*                               NULL for any error(s).
*
*                   (c) IEEE Std 1003.1, 2004 Edition, Section 'strncat() : DESCRIPTION' states that "if
*                       copying takes place between objects that overlap, the behavior is undefined."
*
*               (3) String concatenation terminates when :
*
*                   (a) Destination/Concatenation string pointer(s) are passed NULL pointers.
*                       (1) No string concatenation performed; NULL pointer returned.
*
*                   (b) Destination/Concatenation string pointer(s) point to NULL.
*                       (1) String buffer(s) overlap with NULL address; NULL pointer returned.
*
*                   (c) Concatenation string's terminating NULL character found.
*                       (1) Entire concatenation string appended to destination string (see Note #2a1A).
*
*                   (d) 'len_max' number of characters concatenated.
*
*                       (1) 'len_max' number of characters does NOT include the terminating NULL character 
*                           (see Note #2a2).
*
*                       (2) Null concatenations allowed (i.e. zero-length concatenations).
*                           (A) No string concatenation performed; destination string returned 
*                               (see Note #2b1).
*********************************************************************************************************
*/
/*$PAGE*/
CPU_CHAR  *Str_Cat_N (       CPU_CHAR    *pstr_dest,
                      const  CPU_CHAR    *pstr_cat,
                             CPU_SIZE_T   len_max)
{
           CPU_CHAR    *pstr_cat_dest;
    const  CPU_CHAR    *pstr_cat_src;
           CPU_SIZE_T   len_cat;

                                                                /* Rtn NULL if str ptr(s) NULL (see Note #3a1).         */
    if (pstr_dest == (CPU_CHAR *)0) {
        return ((CPU_CHAR *)0);
    }
    if (pstr_cat  == (const CPU_CHAR *)0) {
        return ((CPU_CHAR *)0);
    }

    if (len_max < 1) {                                          /* Rtn dest str if cat len = 0 (see Note #3d2A).        */
        return ((CPU_CHAR *)pstr_dest);
    }


    pstr_cat_dest = pstr_dest;
    while (( pstr_cat_dest != (CPU_CHAR *)  0 ) &&              /* Adv to end of cur dest str until NULL ptr ...        */
           (*pstr_cat_dest != (CPU_CHAR  )'\0')) {              /* ... or NULL char found..                             */
        pstr_cat_dest++;
    }
    if (pstr_cat_dest == (CPU_CHAR *)0) {                       /* Rtn NULL if NULL ptr found (see Note #3b1).          */
        return ((CPU_CHAR *)0);
    }

    pstr_cat_src = pstr_cat;
    len_cat      = 0u;

    while (( pstr_cat_dest != (      CPU_CHAR *)  0 ) &&        /* Cat str until NULL ptr(s)  [see Note #3b]  ...       */
           ( pstr_cat_src  != (const CPU_CHAR *)  0 ) &&
           (*pstr_cat_src  != (      CPU_CHAR  )'\0') &&        /* ... or NULL char found     (see Note #3c); ...       */
           ( len_cat       <  (      CPU_SIZE_T)len_max)) {     /* ... or max nbr chars cat'd (see Note #3d).           */
       *pstr_cat_dest = *pstr_cat_src;
        pstr_cat_dest++;
        pstr_cat_src++;
        len_cat++;
    }
                                                                /* Rtn NULL if NULL ptr(s) found (see Note #3b1).       */
    if ((pstr_cat_dest == (      CPU_CHAR *)0) ||
        (pstr_cat_src  == (const CPU_CHAR *)0)) {
         return ((CPU_CHAR *)0);
    }

   *pstr_cat_dest = (CPU_CHAR)'\0';                             /* Append NULL char    (see Note #2a2C).                */


    return (pstr_dest);                                         /* Rtn ptr to dest str (see Note #2b1).                 */
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                              Str_Cmp()
*
* Description : Determine if two strings are identical.
*
* Argument(s) : p1_str      Pointer to first  string (see Note #1).
*
*               p2_str      Pointer to second string (see Note #1).
*
* Return(s)   : 0,              if strings are identical             (see Notes #3a1A, #3a2A, & #3b).
*
*               Negative value, if 'p1_str' is less    than 'p2_str' (see Notes #3a1B1, #3a2B1, & #3c).
*
*               Positive value, if 'p1_str' is greater than 'p2_str' (see Notes #3a1B2, #3a2B2, & #3c).
*
*               See also Note #2b.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffers NOT modified.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'strcmp() : DESCRIPTION' states that "the
*                       strcmp() function shall compare the string pointed to by 's1' ('p1_str') to the 
*                       string pointed to by 's2' ('p2_str)".
*
*                   (b) (1) IEEE Std 1003.1, 2004 Edition, Section 'strcmp() : RETURN VALUE' states that
*                          "upon successful completion, strcmp() shall return an integer greater than,
*                           equal to, or less than 0".
*
*                       (2) IEEE Std 1003.1, 2004 Edition, Section 'strcmp() : DESCRIPTION' adds that "the
*                           sign of a non-zero return value shall be determined by the sign of the difference
*                           between the values of the first pair of bytes ... that differ in the strings
*                           being compared".
*
*               (3) String comparison terminates when :
*
*                   (a) (1) (A) BOTH string pointer(s) are passed NULL pointers.
*                               (1) NULL strings identical; 0 returned.
*
*                           (B) (1) 'p1_str' passed a NULL pointer.
*                                   (a) Return negative value of character pointed to by 'p2_str'.
*
*                               (2) 'p2_str' passed a NULL pointer.
*                                   (a) Return positive value of character pointed to by 'p1_str'.
*
*                       (2) (A) BOTH strings point to NULL.
*                               (1) Strings overlap with NULL address.
*                               (2) Strings identical up to but NOT beyond or including the NULL address;
*                                   0 returned.
*
*                           (B) (1) 'p1_str_cmp_next' points to NULL.
*                                   (a) 'p1_str' overlaps with NULL address.
*                                   (b) Strings compared up to but NOT beyond or including the NULL address.
*                                   (c) Return negative value of character pointed to by 'p2_str_cmp_next'.
*
*                               (2) 'p2_str_cmp_next' points to NULL.
*                                   (a) 'p2_str' overlaps with NULL address.
*                                   (b) Strings compared up to but NOT beyond or including the NULL address.
*                                   (c) Return positive value of character pointed to by 'p1_str_cmp_next'.
*
*                   (b) Terminating NULL character found in both strings.
*                       (1) Strings identical; 0 returned.
*                       (2) Only one NULL character test required in conditional since previous condition
*                           tested character equality.
*
*                   (c) Non-matching characters found.
*                       (1) Return signed-integer difference of the character pointed to by 'p2_str'
*                           from the character pointed to by 'p1_str'.
*
*               (4) Since 16-bit signed arithmetic is performed to calculate a non-identical comparison
*                   return value, 'CPU_CHAR' native data type size MUST be 8-bit.
*********************************************************************************************************
*/

CPU_INT16S  Str_Cmp (const  CPU_CHAR  *p1_str,
                     const  CPU_CHAR  *p2_str)
{
    CPU_INT16S  cmp_val;


    cmp_val = Str_Cmp_N(p1_str,
                        p2_str,
                        DEF_INT_CPU_U_MAX_VAL);

    return (cmp_val);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                             Str_Cmp_N()
*
* Description : Determine if two strings are identical for up to a maximum number of characters.
*
* Argument(s) : p1_str      Pointer to first  string (see Note #1).
*
*               p2_str      Pointer to second string (see Note #1).
*
*               len_max     Maximum number of characters to compare  (see Note  #3d).
*
* Return(s)   : 0,              if strings are identical             (see Notes #3a1A, #3a2A, #3b, & #3d).
*
*               Negative value, if 'p1_str' is less    than 'p2_str' (see Notes #3a1B1, #3a2B1, & #3c).
*
*               Positive value, if 'p1_str' is greater than 'p2_str' (see Notes #3a1B2, #3a2B2, & #3c).
*
*               See also Note #2b.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffers NOT modified.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'strncmp() : DESCRIPTION' states that :
*
*                       (1) "The strncmp() function shall compare ... the array pointed to by 's1' ('p1_str') 
*                            to the array pointed to by 's2' ('p2_str)" ...
*                       (2)  but "not more than 'n' ('len_max') bytes" of either array.
*
*                   (b) (1) IEEE Std 1003.1, 2004 Edition, Section 'strncmp() : RETURN VALUE' states that
*                          "upon successful completion, strncmp() shall return an integer greater than,
*                           equal to, or less than 0".
*
*                       (2) IEEE Std 1003.1, 2004 Edition, Section 'strncmp() : DESCRIPTION' adds that
*                          "the sign of a non-zero return value is determined by the sign of the difference
*                           between the values of the first pair of bytes ... that differ in the strings
*                           being compared".
*
*               (3) String comparison terminates when :
*
*                   (a) (1) (A) BOTH string pointer(s) are passed NULL pointers.
*                               (1) NULL strings identical; 0 returned.
*
*                           (B) (1) 'p1_str' passed a NULL pointer.
*                                   (a) Return negative value of character pointed to by 'p2_str'.
*
*                               (2) 'p2_str' passed a NULL pointer.
*                                   (a) Return positive value of character pointed to by 'p1_str'.
*
*                       (2) (A) BOTH strings point to NULL.
*                               (1) Strings overlap with NULL address.
*                               (2) Strings identical up to but NOT beyond or including the NULL address;
*                                   0 returned.
*
*                           (B) (1) 'p1_str_cmp_next' points to NULL.
*                                   (a) 'p1_str' overlaps with NULL address.
*                                   (b) Strings compared up to but NOT beyond or including the NULL address.
*                                   (c) Return negative value of character pointed to by 'p2_str_cmp_next'.
*
*                               (2) 'p2_str_cmp_next' points to NULL.
*                                   (a) 'p2_str' overlaps with NULL address.
*                                   (b) Strings compared up to but NOT beyond or including the NULL address.
*                                   (c) Return positive value of character pointed to by 'p1_str_cmp_next'.
*
*                   (b) Terminating NULL character found in both strings.
*                       (1) Strings identical; 0 returned.
*                       (2) Only one NULL character test required in conditional since previous condition
*                           tested character equality.
*
*                   (c) Non-matching characters found.
*                       (1) Return signed-integer difference of the character pointed to by 'p2_str'
*                           from the character pointed to by 'p1_str'.
*
*                   (d) (1) 'len_max' passed a zero length.
*                           (A) Zero-length strings identical; 0 returned.
*
*                       (2) First 'len_max' number of characters identical.
*                           (A) Strings identical; 0 returned.
*
*                       See also Note #2a2.
*
*               (4) Since 16-bit signed arithmetic is performed to calculate a non-identical comparison
*                   return value, 'CPU_CHAR' native data type size MUST be 8-bit.
*********************************************************************************************************
*/
/*$PAGE*/
CPU_INT16S  Str_Cmp_N (const  CPU_CHAR    *p1_str,
                       const  CPU_CHAR    *p2_str,
                              CPU_SIZE_T   len_max)
{
    const  CPU_CHAR    *p1_str_cmp;
    const  CPU_CHAR    *p2_str_cmp;
    const  CPU_CHAR    *p1_str_cmp_next;
    const  CPU_CHAR    *p2_str_cmp_next;
           CPU_INT16S   cmp_val;
           CPU_SIZE_T   cmp_len;


    if (len_max < 1) {                                          /* If cmp len = 0,        rtn 0       (see Note #3d1A). */
        return (0);
    }

    if (p1_str == (const CPU_CHAR *)0) {
        if (p2_str == (const CPU_CHAR *)0) {
            return (0);                                         /* If BOTH str ptrs NULL, rtn 0       (see Note #3a1A). */
        }
        cmp_val = (CPU_INT16S)0 - (CPU_INT16S)(*p2_str);
        return (cmp_val);                                       /* If p1_str NULL, rtn neg p2_str val (see Note #3a1B1).*/
    }
    if (p2_str == (const CPU_CHAR *)0) {
        cmp_val = (CPU_INT16S)(*p1_str);
        return (cmp_val);                                       /* If p2_str NULL, rtn pos p1_str val (see Note #3a1B2).*/
    }


    p1_str_cmp      = p1_str;
    p2_str_cmp      = p2_str;
    p1_str_cmp_next = p1_str_cmp;
    p2_str_cmp_next = p2_str_cmp;
    p1_str_cmp_next++;
    p2_str_cmp_next++;
    cmp_len         = 0u;

    while ((*p1_str_cmp      == *p2_str_cmp)            &&      /* Cmp strs until non-matching chars (see Note #3c) ... */
           (*p1_str_cmp      != (      CPU_CHAR  )'\0') &&      /* ... or NULL chars                 (see Note #3b) ... */
           ( p1_str_cmp_next != (const CPU_CHAR *)  0 ) &&      /* ... or NULL ptr(s) found          (see Note #3a2).   */
           ( p2_str_cmp_next != (const CPU_CHAR *)  0 ) &&
           ( cmp_len         <  (      CPU_SIZE_T)len_max)) {   /* ... or max nbr chars cmp'd        (see Note #3d2).   */
        p1_str_cmp++;
        p2_str_cmp++;
        p1_str_cmp_next++;
        p2_str_cmp_next++;
        cmp_len++;
    }


    if (cmp_len == len_max) {                                   /* If strs     identical for max len nbr of chars, ...  */
        return (0);                                             /* ... rtn 0                 (see Note #3d2A).          */
    }

    if (*p1_str_cmp != *p2_str_cmp) {                           /* If strs NOT identical, ...                           */
                                                                /* ... calc & rtn char diff  (see Note #3c1).           */
         cmp_val = (CPU_INT16S)(*p1_str_cmp) - (CPU_INT16S)(*p2_str_cmp);

    } else if (*p1_str_cmp  == (CPU_CHAR)'\0') {                /* If NULL char(s) found, ...                           */
         cmp_val = (CPU_INT16S)0;                               /* ... strs identical; rtn 0 (see Note #3b).            */

    } else {
        if (p1_str_cmp_next == (const CPU_CHAR *)0) {
            if (p2_str_cmp_next == (const CPU_CHAR *)0) {       /* If BOTH next str ptrs NULL, ...                      */
                cmp_val = (CPU_INT16S)0;                        /* ... rtn 0                       (see Note #3a2A).    */
            } else {                                            /* If p1_str_cmp_next NULL, ...                         */
                                                                /* ... rtn neg p2_str_cmp_next val (see Note #3a2B1).   */
                cmp_val = (CPU_INT16S)0 - (CPU_INT16S)(*p2_str_cmp_next);
            }
        } else {                                                /* If p2_str_cmp_next NULL, ...                         */
            cmp_val = (CPU_INT16S)(*p1_str_cmp_next);           /* ... rtn pos p1_str_cmp_next val (see Note #3a2B2).   */
        }
    }


    return (cmp_val);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                         Str_CmpIgnoreCase()
*
* Description : Determine if two strings are identical, ignoring case.
*
* Argument(s) : p1_str      Pointer to first  string (see Note #1).
*
*               p2_str      Pointer to second string (see Note #1).
*
* Return(s)   : 0,              if strings are identical             (see Notes #3a1A, #3a2A, & #3b).
*
*               Negative value, if 'p1_str' is less    than 'p2_str' (see Notes #3a1B1, #3a2B1, & #3c).
*
*               Positive value, if 'p1_str' is greater than 'p2_str' (see Notes #3a1B2, #3a2B2, & #3c).
*
*               See also Note #2b.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffers NOT modified.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'strcasecmp() : DESCRIPTION' states that :
*
*                       (1) (A) "The strcasecmp() function shall compare ... the string pointed to by 's1' 
*                                ('p1_str') to the string pointed to by 's2' ('p2_str')" ...
*                           (B) "ignoring differences in case".
*
*                       (2) "strcasecmp() ... shall behave as if the strings had been converted to lowercase
*                            and then a byte comparison performed."
*
*                   (b) (1) IEEE Std 1003.1, 2004 Edition, Section 'strcasecmp() : RETURN VALUE' states that
*                          "upon successful completion, strcasecmp() shall return an integer greater than,
*                           equal to, or less than 0".
*
*                       (2) IEEE Std 1003.1, 2004 Edition, Section 'strcmp() : DESCRIPTION' adds that "the
*                           sign of a non-zero return value shall be determined by the sign of the difference
*                           between the values of the first pair of bytes ... that differ in the strings
*                           being compared".
*
*               (3) String comparison terminates when :
*
*                   (a) (1) (A) BOTH string pointer(s) are passed NULL pointers.
*                               (1) NULL strings identical; 0 returned.
*
*                           (B) (1) 'p1_str' passed a NULL pointer.
*                                   (a) Return negative value of character pointed to by 'p2_str', converted
*                                       to lower case (see Note #2a2).
*
*                               (2) 'p2_str' passed a NULL pointer.
*                                   (a) Return positive value of character pointed to by 'p1_str', converted
*                                       to lower case (see Note #2a2).
*
*                       (2) (A) BOTH strings point to NULL.
*                               (1) Strings overlap with NULL address.
*                               (2) Strings identical up to but NOT beyond or including the NULL address;
*                                   0 returned.
*
*                           (B) (1) 'p1_str_cmp_next' points to NULL.
*                                   (a) 'p1_str' overlaps with NULL address.
*                                   (b) Strings compared up to but NOT beyond or including the NULL address.
*                                   (c) Return negative value of character pointed to by 'p2_str_cmp_next',
*                                       converted to lower case (see Note #2a2).
*
*                               (2) 'p2_str_cmp_next' points to NULL.
*                                   (a) 'p2_str' overlaps with NULL address.
*                                   (b) Strings compared up to but NOT beyond or including the NULL address.
*                                   (c) Return positive value of character pointed to by 'p1_str_cmp_next',
*                                       converted to lower case (see Note #2a2).
*
*                   (b) Terminating NULL character found in both strings.
*                       (1) Strings identical; 0 returned.
*                       (2) Only one NULL character test required in conditional since previous condition
*                           tested character equality.
*
*                   (c) Non-matching characters found.
*                       (1) Return signed-integer difference of the character pointed to by 'p2_str',
*                           converted to lower case, from the character pointed to by 'p1_str', converted
*                           to lower case.
*
*               (4) Since 16-bit signed arithmetic is performed to calculate a non-identical comparison
*                   return value, 'CPU_CHAR' native data type size MUST be 8-bit.
*********************************************************************************************************
*/
/*$PAGE*/
CPU_INT16S  Str_CmpIgnoreCase (const  CPU_CHAR  *p1_str,
                               const  CPU_CHAR  *p2_str)
{
    CPU_INT16S  cmp_val;


    cmp_val = Str_CmpIgnoreCase_N(p1_str,
                                  p2_str,
                                  DEF_INT_CPU_U_MAX_VAL);

    return (cmp_val);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                        Str_CmpIgnoreCase_N()
*
* Description : Determine if two strings are identical for up to a maximum number of characters,
*                   ignoring case.
*
* Argument(s) : p1_str      Pointer to first  string (see Note #1).
*
*               p2_str      Pointer to second string (see Note #1).
*
*               len_max     Maximum number of characters to compare  (see Note  #3d).
*
* Return(s)   : 0,              if strings are identical             (see Notes #3a1A, #3a2A, #3b, & #3d).
*
*               Negative value, if 'p1_str' is less    than 'p2_str' (see Notes #3a1B1, #3a2B1, & #3c).
*
*               Positive value, if 'p1_str' is greater than 'p2_str' (see Notes #3a1B2, #3a2B2, & #3c).
*
*               See also Note #2b.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffers NOT modified.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'strncasecmp() : DESCRIPTION' states that :
*
*                       (1) (A) "The strncasecmp() function shall compare ... the string pointed to by 's1' 
*                                ('p1_str') to the string pointed to by 's2' ('p2_str')" ...
*                           (B) "ignoring differences in case"                           ...
*                           (C)  but "not more than 'n' ('len_max') bytes" of either string.
*
*                       (2) "strncasecmp() shall behave as if the strings had been converted to lowercase
*                            and then a byte comparison performed."
*
*                   (b) (1) IEEE Std 1003.1, 2004 Edition, Section 'strncasecmp() : RETURN VALUE' states that
*                          "upon successful completion, strncasecmp() shall return an integer greater than,
*                           equal to, or less than 0".
*
*                       (2) IEEE Std 1003.1, 2004 Edition, Section 'strcmp() : DESCRIPTION' adds that "the
*                           sign of a non-zero return value shall be determined by the sign of the difference
*                           between the values of the first pair of bytes ... that differ in the strings
*                           being compared".
*
*               (3) String comparison terminates when :
*
*                   (a) (1) (A) BOTH string pointer(s) are passed NULL pointers.
*                               (1) NULL strings identical; 0 returned.
*
*                           (B) (1) 'p1_str' passed a NULL pointer.
*                                   (a) Return negative value of character pointed to by 'p2_str', converted
*                                       to lower case (see Note #2a2).
*
*                               (2) 'p2_str' passed a NULL pointer.
*                                   (a) Return positive value of character pointed to by 'p1_str', converted
*                                       to lower case (see Note #2a2).
*
*                       (2) (A) BOTH strings point to NULL.
*                               (1) Strings overlap with NULL address.
*                               (2) Strings identical up to but NOT beyond or including the NULL address;
*                                   0 returned.
*
*                           (B) (1) 'p1_str_cmp_next' points to NULL.
*                                   (a) 'p1_str' overlaps with NULL address.
*                                   (b) Strings compared up to but NOT beyond or including the NULL address.
*                                   (c) Return negative value of character pointed to by 'p2_str_cmp_next',
*                                       converted to lower case (see Note #2a2).
*
*                               (2) 'p2_str_cmp_next' points to NULL.
*                                   (a) 'p2_str' overlaps with NULL address.
*                                   (b) Strings compared up to but NOT beyond or including the NULL address.
*                                   (c) Return positive value of character pointed to by 'p1_str_cmp_next',
*                                       converted to lower case (see Note #2a2).
*
*                   (b) Terminating NULL character found in both strings.
*                       (1) Strings identical; 0 returned.
*                       (2) Only one NULL character test required in conditional since previous condition
*                           tested character equality.
*
*                   (c) Non-matching characters found.
*                       (1) Return signed-integer difference of the character pointed to by 'p2_str',
*                           converted to lower case, from the character pointed to by 'p1_str', converted
*                           to lower case.
*
*                   (d) (1) 'len_max' passed a zero length.
*                           (A) Zero-length strings identical; 0 returned.
*
*                       (2) First 'len_max' number of characters identical.
*                           (A) Strings identical; 0 returned.
*
*                       See also Note #2a1C.
*$PAGE*
*               (4) Since 16-bit signed arithmetic is performed to calculate a non-identical comparison
*                   return value, 'CPU_CHAR' native data type size MUST be 8-bit.
*********************************************************************************************************
*/

CPU_INT16S  Str_CmpIgnoreCase_N (const  CPU_CHAR    *p1_str,
                                 const  CPU_CHAR    *p2_str,
                                        CPU_SIZE_T   len_max)
{
    const  CPU_CHAR    *p1_str_cmp;
    const  CPU_CHAR    *p2_str_cmp;
    const  CPU_CHAR    *p1_str_cmp_next;
    const  CPU_CHAR    *p2_str_cmp_next;
           CPU_CHAR     char_1;
           CPU_CHAR     char_2;
           CPU_INT16S   cmp_val;
           CPU_SIZE_T   cmp_len;


    if (len_max < 1) {                                          /* If cmp len = 0,        rtn 0       (see Note #3d1A). */
        return (0);
    }

    if (p1_str == (const CPU_CHAR *)0) {
        if (p2_str == (const CPU_CHAR *)0) {
            return (0);                                         /* If BOTH str ptrs NULL, rtn 0       (see Note #3a1A). */
        }
        char_2  =  ASCII_ToLower(*p2_str);
        cmp_val = (CPU_INT16S)0 - (CPU_INT16S)char_2;
        return (cmp_val);                                       /* If p1_str NULL, rtn neg p2_str val (see Note #3a1B1).*/
    }
    if (p2_str == (const CPU_CHAR *)0) {
        char_1  =  ASCII_ToLower(*p1_str);
        cmp_val = (CPU_INT16S)char_1;
        return (cmp_val);                                       /* If p2_str NULL, rtn pos p1_str val (see Note #3a1B2).*/
    }


    p1_str_cmp      = p1_str;
    p2_str_cmp      = p2_str;
    p1_str_cmp_next = p1_str_cmp;
    p2_str_cmp_next = p2_str_cmp;
    p1_str_cmp_next++;
    p2_str_cmp_next++;
    char_1          = ASCII_ToLower(*p1_str_cmp);
    char_2          = ASCII_ToLower(*p2_str_cmp);
    cmp_len         = 0u;

    while (( char_1          ==  char_2)                &&      /* Cmp strs until non-matching chars (see Note #3c) ... */
           (*p1_str_cmp      != (      CPU_CHAR  )'\0') &&      /* ... or NULL chars                 (see Note #3b) ... */
           ( p1_str_cmp_next != (const CPU_CHAR *)  0 ) &&      /* ... or NULL ptr(s) found          (see Note #3a2).   */
           ( p2_str_cmp_next != (const CPU_CHAR *)  0 ) &&
           ( cmp_len         <  (      CPU_SIZE_T)len_max)) {   /* ... or max nbr chars cmp'd        (see Note #3d2).   */
        p1_str_cmp++;
        p2_str_cmp++;
        p1_str_cmp_next++;
        p2_str_cmp_next++;
        cmp_len++;
        char_1 = ASCII_ToLower(*p1_str_cmp);
        char_2 = ASCII_ToLower(*p2_str_cmp);
    }


    if (cmp_len == len_max) {                                   /* If strs     identical for max len nbr of chars, ...  */
        return (0);                                             /* ... rtn 0                 (see Note #3d2A).          */
    }

    if (char_1 != char_2) {                                     /* If strs NOT identical, ...                           */
         cmp_val = (CPU_INT16S)char_1 - (CPU_INT16S)char_2;     /* ... calc & rtn char diff  (see Note #3c1).           */

    } else if (char_1 == (CPU_CHAR)'\0') {                      /* If NULL char(s) found, ...                           */
         cmp_val = (CPU_INT16S)0;                               /* ... strs identical; rtn 0 (see Note #3b).            */

    } else {
        if (p1_str_cmp_next == (const CPU_CHAR *)0) {
            if (p2_str_cmp_next == (const CPU_CHAR *)0) {       /* If BOTH next str ptrs NULL, ...                      */
                cmp_val = (CPU_INT16S)0;                        /* ... rtn 0                       (see Note #3a2A).    */
            } else {                                            /* If p1_str_cmp_next NULL, ...                         */
                char_2  =  ASCII_ToLower(*p2_str_cmp_next);
                cmp_val = (CPU_INT16S)0 - (CPU_INT16S)char_2;   /* ... rtn neg p2_str_cmp_next val (see Note #3a2B1).   */
            }
        } else {                                                /* If p2_str_cmp_next NULL, ...                         */
            char_1  =  ASCII_ToLower(*p1_str_cmp_next);
            cmp_val = (CPU_INT16S)char_1;                       /* ... rtn pos p1_str_cmp_next val (see Note #3a2B2).   */
        }
    }


    return (cmp_val);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                             Str_Char()
*
* Description : Search string for first occurrence of specific character.
*
* Argument(s) : pstr            Pointer to string (see Note #1).
*
*               srch_char       Search character.
*
* Return(s)   : Pointer to first occurrence of search character in string, if any    (see Note #2b1).
*
*               Pointer to NULL,                                           otherwise (see Note #2b2).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffer NOT modified.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'strchr() : DESCRIPTION' states that :
*
*                       (1) "The strchr() function shall locate the first occurrence of 'c' ('srch_char') 
*                            ... in the string pointed to by 's' ('pstr')."
*                       (2) "The terminating null byte is considered to be part of the string."
*
*                   (b) IEEE Std 1003.1, 2004 Edition, Section 'strchr() : RETURN VALUE' states that 
*                       "upon completion, strchr() shall return" :
*
*                       (1) "a pointer to the byte," ...
*                       (2) "or a null pointer if the byte was not found."
*                           (A) #### Although NO strchr() specification states to return NULL for 
*                               any other reason(s), NULL is also returned for any error(s).
*
*               (3) String search terminates when :
*
*                   (a) String pointer passed a NULL pointer.
*                       (1) No string search performed; NULL pointer returned.
*
*                   (b) String pointer points to NULL.
*                       (1) String overlaps with NULL address; NULL pointer returned.
*
*                   (c) String's terminating NULL character found.
*                       (1) Search character NOT found in search string; NULL pointer returned 
*                           (see Note #2b2).
*                       (2) Applicable even if search character is the terminating NULL character 
*                           (see Note #2a2).
*
*                   (d) Search character found.
*                       (1) Return pointer to first occurrence of search character in search string
*                           (see Note #2a1).
*********************************************************************************************************
*/

CPU_CHAR  *Str_Char (const  CPU_CHAR  *pstr,
                            CPU_CHAR   srch_char)
{
    CPU_CHAR  *pstr_rtn;


    pstr_rtn = Str_Char_N(pstr,
                          DEF_INT_CPU_U_MAX_VAL,
                          srch_char);

    return (pstr_rtn);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                            Str_Char_N()
*
* Description : Search string for first occurrence of specific character, up to a maximum number 
*                   of characters.
*
* Argument(s) : pstr            Pointer to string (see Note #1).
*
*               len_max         Maximum number of characters to search (see Notes #2c & #3e).
*
*               srch_char       Search character.
*
* Return(s)   : Pointer to first occurrence of search character in string, if any    (see Note #2b1).
*
*               Pointer to NULL,                                           otherwise (see Note #2b2).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffer NOT modified.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'strchr() : DESCRIPTION' states that :
*
*                       (1) "The strchr() function shall locate the first occurrence of 'c' ('srch_char') 
*                            ... in the string pointed to by 's' ('pstr')."
*                       (2) "The terminating null byte is considered to be part of the string."
*
*                   (b) IEEE Std 1003.1, 2004 Edition, Section 'strchr() : RETURN VALUE' states that 
*                       "upon completion, strchr() shall return" :
*
*                       (1) "a pointer to the byte," ...
*                       (2) "or a null pointer if the byte was not found."
*                           (A) #### Although NO strchr() specification states to return NULL for 
*                               any other reason(s), NULL is also returned for any error(s).
*
*                   (c) Ideally, the 'len_max' argument would be the last argument in this function's
*                       argument list for consistency with all other custom string library functions.
*                       However, the 'len_max' argument is sequentially ordered as the second argument 
*                       to comply with most standard library's strnchr() argument list.
*
*               (3) String search terminates when :
*
*                   (a) String pointer passed a NULL pointer.
*                       (1) No string search performed; NULL pointer returned.
*
*                   (b) String pointer points to NULL.
*                       (1) String overlaps with NULL address; NULL pointer returned.
*
*                   (c) String's terminating NULL character found.
*                       (1) Search character NOT found in search string; NULL pointer returned 
*                           (see Note #2b2).
*                       (2) Applicable even if search character is the terminating NULL character 
*                           (see Note #2a2).
*
*                   (d) Search character found.
*                       (1) Return pointer to first occurrence of search character in search string
*                           (see Note #2a1).
*
*                   (e) 'len_max' number of characters searched.
*                       (1) Search character NOT found in search string within first 'len_max' number 
*                           of characters; NULL pointer returned.
*                       (2) 'len_max' number of characters MAY include terminating NULL character 
*                           (see Note #2a2).
*********************************************************************************************************
*/
/*$PAGE*/
CPU_CHAR  *Str_Char_N (const  CPU_CHAR    *pstr,
                              CPU_SIZE_T   len_max,
                              CPU_CHAR     srch_char)
{
    const  CPU_CHAR    *pstr_char;
           CPU_SIZE_T   len_srch;


    if (pstr == (const CPU_CHAR *)0) {                          /* Rtn NULL if srch str ptr NULL (see Note #3a1).       */
        return ((CPU_CHAR *)0);
    }

    if (len_max < 1) {                                          /* Rtn NULL if srch len = 0      (see Note #3e1).       */
        return ((CPU_CHAR *)0);
    }


    pstr_char = pstr;
    len_srch  = 0u;

    while (( pstr_char != (const CPU_CHAR *)  0 )      &&       /* Srch str until NULL ptr     [see Note #3b]  ...      */
           (*pstr_char != (      CPU_CHAR  )'\0')      &&       /* ... or NULL char            (see Note #3c)  ...      */
           (*pstr_char != (      CPU_CHAR  )srch_char) &&       /* ... or srch char found      (see Note #3d); ...      */
           ( len_srch  <  (      CPU_SIZE_T)len_max)) {         /* ... or max nbr chars srch'd (see Note #3e).          */
        pstr_char++;
        len_srch++;
    }


    if (pstr_char == (const CPU_CHAR *)0) {                     /* Rtn NULL if NULL ptr found      (see Note #3b1).     */
        return ((CPU_CHAR *)0);
    }

    if (len_srch >= len_max) {                                  /* Rtn NULL if srch char NOT found ...                  */
        return ((CPU_CHAR *)0);                                 /* ... within max nbr of chars     (see Note #3e1).     */
    }

    if (*pstr_char != srch_char) {                              /* Rtn NULL if srch char NOT found (see Note #3c1).     */
         return ((CPU_CHAR *)0);
    }


    return ((CPU_CHAR *)pstr_char);                             /* Else rtn ptr to found srch char (see Note #3d1).     */
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                           Str_Char_Last()
*
* Description : Search string for last occurrence of specific character.
*
* Argument(s) : pstr            Pointer to string (see Note #1).
*
*               srch_char       Search character.
*
* Return(s)   : Pointer to last occurrence of search character in string, if any    (see Note #2b1).
*
*               Pointer to NULL,                                          otherwise (see Note #2b2).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffer NOT modified.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'strrchr() : DESCRIPTION' states that :
*
*                       (1) "The strrchr() function shall locate the last occurrence of 'c' ('srch_char') 
*                            ... in the string pointed to by 's' ('pstr')."
*                       (2) "The terminating null byte is considered to be part of the string."
*
*                   (b) IEEE Std 1003.1, 2004 Edition, Section 'strrchr() : RETURN VALUE' states that 
*                       "upon successful completion, strrchr() shall return" :
*
*                       (1) "a pointer to the byte" ...
*                       (2) "or a null pointer if 'c' ('srch_char') does not occur in the string."
*                           (A) #### Although NO strrchr() specification states to return NULL for 
*                               any other reason(s), NULL is also returned for any error(s).
*
*               (3) String search terminates when :
*
*                   (a) String pointer passed a NULL pointer.
*                       (1) No string search performed; NULL pointer returned.
*
*                   (b) String pointer points to NULL.
*                       (1) String overlaps with NULL address; NULL pointer returned.
*
*                   (c) String searched from end to beginning.
*                       (1) Search character NOT found in search string; NULL pointer returned.
*                       (2) Applicable even if search character is the terminating NULL character 
*                           (see Note #2a2).
*
*                   (d) Search character found.
*                       (1) Return pointer to last occurrence of search character in search string 
*                           (see Note #2a1).
*********************************************************************************************************
*/

CPU_CHAR  *Str_Char_Last (const  CPU_CHAR  *pstr,
                                 CPU_CHAR   srch_char)
{
    CPU_CHAR  *pstr_rtn;


    pstr_rtn = Str_Char_Last_N(pstr,
                               DEF_INT_CPU_U_MAX_VAL,
                               srch_char);

    return (pstr_rtn);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                          Str_Char_Last_N()
*
* Description : Search string for last occurrence of specific character, up to a maximum number 
*                   of characters.
*
* Argument(s) : pstr            Pointer to string (see Note #1).
*
*               len_max         Maximum number of characters to search (see Notes #2c & #3e).
*
*               srch_char       Search character.
*
* Return(s)   : Pointer to last occurrence of search character in string, if any    (see Note #2b1).
*
*               Pointer to NULL,                                          otherwise (see Note #2b2).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffer NOT modified.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'strrchr() : DESCRIPTION' states that :
*
*                       (1) "The strrchr() function shall locate the last occurrence of 'c' ('srch_char') 
*                            ... in the string pointed to by 's' ('pstr')."
*                       (2) "The terminating null byte is considered to be part of the string."
*
*                   (b) IEEE Std 1003.1, 2004 Edition, Section 'strrchr() : RETURN VALUE' states that 
*                       "upon successful completion, strrchr() shall return" :
*
*                       (1) "a pointer to the byte" ...
*                       (2) "or a null pointer if 'c' ('srch_char') does not occur in the string."
*                           (A) #### Although NO strrchr() specification states to return NULL for 
*                               any other reason(s), NULL is also returned for any error(s).
*
*                   (c) Ideally, the 'len_max' argument would be the last argument in this function's
*                       argument list for consistency with all other custom string library functions.
*                       However, the 'len_max' argument is sequentially ordered as the second argument 
*                       to comply with most standard library's strnrchr() argument list.
*
*                       See also 'Str_Char_N()  Note #2c'.
*
*               (3) String search terminates when :
*
*                   (a) String pointer passed a NULL pointer.
*                       (1) No string search performed; NULL pointer returned.
*
*                   (b) String pointer points to NULL.
*                       (1) String overlaps with NULL address; NULL pointer returned.
*
*                   (c) String searched from end to beginning.
*                       (1) Search character NOT found in search string; NULL pointer returned 
*                           (see Note #2b2).
*                       (2) Applicable even if search character is the terminating NULL character 
*                           (see Note #2a2).
*
*                   (d) Search character found.
*                       (1) Return pointer to last occurrence of search character in search string 
*                           (see Note #2a1).
*
*                   (e) 'len_max' number of characters searched.
*                       (1) Search character NOT found in search string within last 'len_max' number 
*                           of characters; NULL pointer returned.
*                       (2) 'len_max' number of characters MAY include terminating NULL character 
*                           (see Note #2a2).
*********************************************************************************************************
*/
/*$PAGE*/
CPU_CHAR  *Str_Char_Last_N (const  CPU_CHAR    *pstr,
                                   CPU_SIZE_T   len_max,
                                   CPU_CHAR     srch_char)
{
    const  CPU_CHAR    *pstr_char;
           CPU_SIZE_T   str_len_max;
           CPU_SIZE_T   str_len;


    if (pstr == (const CPU_CHAR *)0) {                          /* Rtn NULL if srch str ptr NULL (see Note #3a1).       */
        return ((CPU_CHAR *)0);
    }

    if (len_max < 1) {                                          /* Rtn NULL if srch len = 0      (see Note #3e1).       */
        return ((CPU_CHAR *)0);
    }


    pstr_char    = pstr;
     str_len_max = len_max - sizeof((CPU_CHAR)'\0');            /* Str len adj'd for NULL char len.                     */
     str_len     = Str_Len_N(pstr_char, str_len_max);
    pstr_char   += str_len;

    if (pstr_char == (const CPU_CHAR *)0) {                     /* Rtn NULL if NULL ptr found        (see Note #3b1).   */
        return ((CPU_CHAR *)0);
    }

    while (( pstr_char != pstr) &&                              /* Srch str from end until beginning (see Note #3c) ... */
           (*pstr_char != srch_char)) {                         /* ... until srch char found         (see Note #3d).    */
        pstr_char--;
    }


    if (*pstr_char != srch_char) {                              /* Rtn NULL if srch char NOT found   (see Note #3c1).   */
         return ((CPU_CHAR *)0);
    }


    return ((CPU_CHAR *)pstr_char);                             /* Else rtn ptr to found srch char   (see Note #3d1).   */
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                         Str_Char_Replace()
*
* Description : Search string for specific character and replace it by another specific character.
*
* Argument(s) : pstr            Pointer to string (see Note #1).
*
*               char_srch       Search character.
*
*               char_replace    Replace character.
*
* Return(s)   : Pointer to string, if NO error(s).
*
*               Pointer to NULL,   otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffer modified.
*
*               (2) String search terminates when :
*
*                   (a) String pointer passed a NULL pointer.
*                       (1) No string search performed; NULL pointer returned.
*
*                   (b) String pointer points to NULL.
*                       (1) String overlaps with NULL address; NULL pointer returned.
*
*                   (c) String's terminating NULL character found.
*                       (1) Search character NOT found in search string; NULL pointer returned
*                       (2) Applicable even if search character is the terminating NULL character
*
*                   (d) Search character found.
*                       (1) Replace character found by the specified character.
*********************************************************************************************************
*/

CPU_CHAR  *Str_Char_Replace (CPU_CHAR  *pstr,
                             CPU_CHAR   char_srch,
                             CPU_CHAR   char_replace)
{
    CPU_CHAR  *pstr_rtn;


    pstr_rtn = Str_Char_Replace_N(pstr,
                                  char_srch,
                                  char_replace,
                                  DEF_INT_CPU_U_MAX_VAL);

    return (pstr_rtn);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                        Str_Char_Replace_N()
*
* Description : Search string for specific character and replace it by another specific character, up to
*               a maximum number of characters.
*
* Argument(s) : pstr            Pointer to string (see Note #1).
*
*               char_srch       Search character.
*
*               char_replace    Replace character.
*
*               len_max         Maximum number of characters to search (see Notes #2c & #3e).
*
* Return(s)   : Pointer to string, if NO error(s).
*
*               Pointer to NULL,   otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffer modified.
*
*               (2) String search terminates when :
*
*                   (a) String pointer passed a NULL pointer.
*                       (1) No string search performed; NULL pointer returned.
*
*                   (b) String pointer points to NULL.
*                       (1) String overlaps with NULL address; NULL pointer returned.
*
*                   (c) String's terminating NULL character found.
*                       (1) Search character NOT found in search string; NULL pointer returned
*                       (2) Applicable even if search character is the terminating NULL character
*
*                   (d) Search character found.
*                       (1) Replace character found by the specified character.
*
*                   (e) 'len_max' number of characters searched.
*                       (1) Search character NOT found in search string within first 'len_max' number
*                           of characters; NULL pointer returned.
*                       (2) 'len_max' number of characters MAY include terminating NULL character
*                           (see Note #2a2).
*********************************************************************************************************
*/

CPU_CHAR  *Str_Char_Replace_N (CPU_CHAR    *pstr,
                               CPU_CHAR     char_srch,
                               CPU_CHAR     char_replace,
                               CPU_SIZE_T   len_max)
{
    CPU_CHAR    *pstr_char;
    CPU_SIZE_T   len;


    if (pstr == (const CPU_CHAR *)0) {                          /* Rtn NULL if srch str ptr NULL (see Note #2a1).       */
        return ((CPU_CHAR *)0);
    }

    if (len_max < 1) {                                          /* Rtn NULL if srch len = 0      (see Note #2e1).       */
        return ((CPU_CHAR *)0);
    }

    pstr_char = pstr;
    len       = len_max;

    while (( pstr_char != (const CPU_CHAR *)0) &&               /* Srch str until NULL ptr     [see Note #2b]  ...      */
           (*pstr_char !=  ASCII_CHAR_NULL   ) &&               /* ... or NULL char            (see Note #2c)  ...      */
           ( len        >                   0)) {               /* ... or max nbr chars srch'd (see Note #2e).          */

        if (*pstr_char == char_srch) {
            *pstr_char  = char_replace;                         /* Replace char if srch char is found.                  */
        }

        pstr_char++;
        len--;
    }

    return (pstr);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                              Str_Str()
*
* Description : Search string for first occurence of a specific search string.
*
* Argument(s) : pstr            Pointer to        string (see Note #1).
*
*               pstr_srch       Pointer to search string (see Note #1).
*
* Return(s)   : Pointer to first occurrence of search string in string, if any                (see Note #2b1A).
*
*               Pointer to string,                                      if NULL search string (see Note #2b2).
*
*               Pointer to NULL,                                        otherwise             (see Note #2b1B).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffers NOT modified.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'strstr() : DESCRIPTION' states that :
*
*                       (1) "The strstr() function shall locate the first occurrence  in the string 
*                            pointed to by 's1' ('pstr') of the sequence of bytes ... in the string 
*                            pointed to by 's2' ('pstr_srch')" ...
*                       (2) "(excluding the terminating null byte)."
*
*                   (b) IEEE Std 1003.1, 2004 Edition, Section 'strstr() : RETURN VALUE' states that :
*
*                       (1) "Upon successful completion, strstr() shall return" :
*                           (A) "a pointer to the located string" ...
*                           (B) "or a null pointer if the string is not found."
*                               (1) #### Although NO strstr() specification states to return NULL for 
*                                   any other reason(s), NULL is also returned for any error(s).
*
*                       (2) "If 's2' ('pstr_srch') points to a string with zero length, the function 
*                            shall return 's1' ('pstr')."
*
*               (3) String search terminates when :
*
*                   (a) String pointer(s) are passed NULL pointers.
*                       (1) No string search performed; NULL pointer returned.
*
*                   (b) String pointer(s) point to NULL.
*                       (1) String buffer(s) overlap with NULL address; NULL pointer returned.
*
*                   (c) Search string length equal to zero.
*                       (1) No string search performed; string pointer returned (see Note #2b2).
*
*                   (d) Search string length greater than string length.
*                       (1) No string search performed; NULL   pointer returned (see Note #2b1B).
*
*                   (e) Entire string has been searched.
*                       (1) Search string not found; NULL pointer returned (see Note #2b1B).
*
*                   (f) Search string found.
*                       (1) Return pointer to first occurrence of search string in string (see Note #2b1A).
*********************************************************************************************************
*/

CPU_CHAR  *Str_Str (const  CPU_CHAR  *pstr,
                    const  CPU_CHAR  *pstr_srch)
{
    CPU_CHAR  *pstr_rtn;


    pstr_rtn = Str_Str_N(pstr,
                         pstr_srch,
                         DEF_INT_CPU_U_MAX_VAL);

    return (pstr_rtn);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                             Str_Str_N()
*
* Description : Search string for first occurence of a specific search string, up to a maximum number 
*                   of characters.
*
* Argument(s) : pstr            Pointer to        string (see Note #1).
*
*               pstr_srch       Pointer to search string (see Note #1).
*
*               len_max         Maximum number of characters to search (see Note #3g).
*
* Return(s)   : Pointer to first occurrence of search string in string, if any                (see Note #2b1A).
*
*               Pointer to string,                                      if NULL search string (see Note #2b2).
*
*               Pointer to NULL,                                        otherwise             (see Note #2b1B).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffers NOT modified.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'strstr() : DESCRIPTION' states that :
*
*                       (1) "The strstr() function shall locate the first occurrence  in the string 
*                            pointed to by 's1' ('pstr') of the sequence of bytes ... in the string 
*                            pointed to by 's2' ('pstr_srch')" ...
*                       (2) "(excluding the terminating null byte)."
*
*                   (b) IEEE Std 1003.1, 2004 Edition, Section 'strstr() : RETURN VALUE' states that :
*
*                       (1) "Upon successful completion, strstr() shall return" :
*                           (A) "a pointer to the located string" ...
*                           (B) "or a null pointer if the string is not found."
*                               (1) #### Although NO strstr() specification states to return NULL for 
*                                   any other reason(s), NULL is also returned for any error(s).
*
*                       (2) "If 's2' ('pstr_srch') points to a string with zero length, the function 
*                            shall return 's1' ('pstr')."
*
*               (3) String search terminates when :
*
*                   (a) String pointer(s) are passed NULL pointers.
*                       (1) No string search performed; NULL pointer returned.
*
*                   (b) String pointer(s) point to NULL.
*                       (1) String buffer(s) overlap with NULL address; NULL pointer returned.
*
*                   (c) Search string length equal to zero.
*                       (1) No string search performed; string pointer returned (see Note #2b2).
*
*                   (d) Search string length greater than string length.
*                       (1) No string search performed; NULL   pointer returned (see Note #2b1B).
*
*                   (e) Entire string has been searched.
*                       (1) Search string not found; NULL pointer returned (see Note #2b1B).
*                       (2) Maximum size of the search is defined as the subtraction of the
*                           search string length from the string length.
*
*                   (f) Search string found.
*                       (1) Return pointer to first occurrence of search string in string (see Note #2b1A).
*                       (2) Search string found via Str_Cmp_N().
*
*                   (g) 'len_max' number of characters searched.
*                       (1) 'len_max' number of characters does NOT include terminating NULL character
*                           (see Note #2a2).
*********************************************************************************************************
*/
/*$PAGE*/
CPU_CHAR  *Str_Str_N (const  CPU_CHAR    *pstr,
                      const  CPU_CHAR    *pstr_srch,
                             CPU_SIZE_T   len_max)
{
           CPU_SIZE_T    str_len;
           CPU_SIZE_T    str_len_srch;
           CPU_SIZE_T    len_max_srch;
           CPU_SIZE_T    srch_len;
           CPU_SIZE_T    srch_ix;
           CPU_BOOLEAN   srch_done;
           CPU_INT16S    srch_cmp;
    const  CPU_CHAR     *pstr_str;
    const  CPU_CHAR     *pstr_srch_ix;

                                                                /* Rtn NULL if str ptr(s) NULL (see Note #3a).          */
    if (pstr == (const CPU_CHAR *)0) {
        return ((CPU_CHAR *)0);
    }
    if (pstr_srch == (const CPU_CHAR *)0) {
        return ((CPU_CHAR *)0);
    }

    if (len_max < 1) {                                          /* Rtn NULL if srch len = 0    (see Note #3g).          */
        return ((CPU_CHAR *)0);
    }

                                                                /* Lim max srch str len (to chk > str len).             */
    len_max_srch = (len_max <       DEF_INT_CPU_U_MAX_VAL)
                 ? (len_max + 1u) : DEF_INT_CPU_U_MAX_VAL;

    str_len      = Str_Len_N(pstr,      len_max);
    str_len_srch = Str_Len_N(pstr_srch, len_max_srch);
    if (str_len_srch < 1) {                                     /* Rtn ptr to str if srch str len = 0 (see Note #2b2).  */
        return ((CPU_CHAR *)pstr);
    }
    if (str_len_srch > str_len) {                               /* Rtn NULL if srch str len > str len (see Note #3d).   */
        return ((CPU_CHAR *)0);
    }
                                                                /* Rtn NULL if NULL ptr found         (see Note #3b1).  */
    pstr_str = pstr      + str_len;
    if (pstr_str == (const CPU_CHAR *)0) {
        return ((CPU_CHAR *)0);
    }
    pstr_str = pstr_srch + str_len_srch;
    if (pstr_str == (const CPU_CHAR *)0) {
        return ((CPU_CHAR *)0);
    }


    srch_len  = str_len - str_len_srch;                         /* Calc srch len (see Note #3e2).                       */
    srch_ix   = 0u;
    srch_done = DEF_NO;

    do {
        pstr_srch_ix = (const CPU_CHAR *)(pstr + srch_ix);
        srch_cmp     =  Str_Cmp_N(pstr_srch_ix, pstr_srch, str_len_srch);
        srch_done    = (srch_cmp == 0) ? DEF_YES : DEF_NO;
        srch_ix++;
    } while ((srch_done == DEF_NO) && (srch_ix <= srch_len));


    if (srch_cmp != 0) {                                        /* Rtn NULL if srch str NOT found (see Note #3e2).      */
        return ((CPU_CHAR *)0);
    }

    return ((CPU_CHAR *)pstr_srch_ix);                          /* Else rtn ptr to found srch str (see Note #3f1).      */
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                         Str_FmtNbr_Int32U()
*
* Description : Format 32-bit unsigned integer into a multi-digit character string.
*
* Argument(s) : nbr             Number           to format.
*
*               nbr_dig         Number of digits to format (see Note #1).
*
*                               The following may be used to specify the number of digits to format :
*
*                                   DEF_INT_32U_NBR_DIG_MIN     Minimum number of 32-bit unsigned digits
*                                   DEF_INT_32U_NBR_DIG_MAX     Maximum number of 32-bit unsigned digits
*
*               nbr_base        Base   of number to format (see Note #2).
*
*                               The following may be used to specify the number base :
*
*                                   DEF_NBR_BASE_BIN            Base  2
*                                   DEF_NBR_BASE_OCT            Base  8
*                                   DEF_NBR_BASE_DEC            Base 10
*                                   DEF_NBR_BASE_HEX            Base 16
*
*               lead_char       Prepend leading character  (see Note #3) :
*
*                                   '\0'                    Do NOT prepend leading character to string.
*                                     Printable character          Prepend leading character to string.
*                                   Unprintable character   Format invalid string (see Note #6).
*
*               lower_case      Format alphabetic characters (if any) in lower case :
*
*                                   DEF_NO          Format alphabetic characters in upper case.
*                                   DEF_YES         Format alphabetic characters in lower case.
*
*               nul             Append terminating NULL-character (see Note #4) :
*
*                                   DEF_NO          Do NOT append terminating NULL-character to string.
*                                   DEF_YES                Append terminating NULL-character to string.
*
*               pstr            Pointer to character array to return formatted number string (see Note #5).
*
* Return(s)   : Pointer to formatted string, if NO error(s).
*
*               Pointer to NULL,             otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) If the number of digits to format ('nbr_dig') is zero; then NO formatting 
*                       is performed except possible NULL-termination of the string (see Note #4).
*
*                           Example :
*
*                               nbr      = 23456
*                               nbr_dig  = 0
*                               nbr_base = 10
*
*                               pstr     = ""                   See Note #6a
*
*                   (b) If the number of digits to format ('nbr_dig') is less than the number of 
*                       significant integer digits of the number to format ('nbr'); then an invalid 
*                       string is formatted instead of truncating any significant integer digits.
*
*                           Example :
*
*                               nbr      = 23456
*                               nbr_dig  = 3
*                               nbr_base = 10
*
*                               pstr     = "???"                See Note #6b
*
*               (2) The number's base MUST be between 2 & 36, inclusive.
*$PAGE*
*               (3) Leading character option prepends leading characters prior to the first non-zero digit.
*
*                   (a) (1) Leading character MUST be a printable ASCII character.
*
*                       (2) (A) Leading character MUST NOT be a number base digit, ...
*                           (B) with the exception of '0'.
*
*                   (b) The number of leading characters is such that the total number of significant 
*                       integer digits plus the number of leading characters is equal to the requested 
*                       number of integer digits to format ('nbr_dig').
*
*                           Example :
*
*                               nbr       = 23456
*                               nbr_dig   = 7
*                               nbr_base  = 10
*                               lead_char = ' '
*
*                               pstr      = "  23456"
*
*                   (c) (1) If the value of the number to format is     zero  ...
*                       (2) ... & the number of digits to format is non-zero, ...
*                       (3) ... but NO leading character available;           ...
*                       (4) ... then one digit of '0' value is formatted.
*
*                           This is NOT a leading character; but a single integer digit of '0' value.
*
*               (4) (a) NULL-character terminate option DISABLED prevents overwriting previous character
*                       array formatting.
*
*                   (b) WARNING: Unless 'pstr' character array is pre-/post-terminated, NULL-character
*                       terminate option DISABLED will cause character string run-on.
*
*               (5) (a) Format buffer size NOT validated; buffer overruns MUST be prevented by caller.
*
*                   (b) To prevent character buffer overrun :
*
*                           Character array size MUST be  >=  ('nbr_dig'          +
*                                                               1 'NUL' terminator)  characters
*
*               (6) For any unsuccessful string format or error(s), an invalid string of question marks 
*                   ('?') will be formatted, where the number of question marks is determined by the 
*                   number of digits to format ('nbr_dig') :
*
*                      Invalid string's     {  (a)   0 (NULL string)  ,  if 'nbr_dig' = 0
*                          number of     =  {
*                       question marks      {  (b)  'nbr_dig'         ,  if 'nbr_dig' > 0
*
*********************************************************************************************************
*/

CPU_CHAR  *Str_FmtNbr_Int32U (CPU_INT32U    nbr,
                              CPU_INT08U    nbr_dig,
                              CPU_INT08U    nbr_base,
                              CPU_CHAR      lead_char,
                              CPU_BOOLEAN   lower_case,
                              CPU_BOOLEAN   nul,
                              CPU_CHAR     *pstr)
{
    CPU_CHAR  *pstr_fmt;


    pstr_fmt = Str_FmtNbr_Int32(nbr,                            /* Fmt unsigned int into str.                           */
                                nbr_dig,
                                nbr_base,
                                DEF_NO,
                                lead_char,
                                lower_case,
                                nul,
                                pstr);

    return (pstr_fmt);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                         Str_FmtNbr_Int32S()
*
* Description : Format 32-bit signed integer into a multi-digit character string.
*
* Argument(s) : nbr             Number           to format.
*
*               nbr_dig         Number of digits to format (see Note #1).
*
*                               The following may be used to specify the number of digits to format :
*
*                                   DEF_INT_32S_NBR_DIG_MIN + 1     Minimum number of 32-bit signed digits
*                                   DEF_INT_32S_NBR_DIG_MAX + 1     Maximum number of 32-bit signed digits
*                                                                   (plus 1 digit for possible negative sign)
*
*               nbr_base        Base   of number to format (see Note #2).
*
*                               The following may be used to specify the number base :
*
*                                   DEF_NBR_BASE_BIN            Base  2
*                                   DEF_NBR_BASE_OCT            Base  8
*                                   DEF_NBR_BASE_DEC            Base 10
*                                   DEF_NBR_BASE_HEX            Base 16
*
*               lead_char       Prepend leading character  (see Note #3) :
*
*                                   '\0'                    Do NOT prepend leading character to string.
*                                     Printable character          Prepend leading character to string.
*                                   Unprintable character   Format invalid string (see Note #6).
*
*               lower_case      Format alphabetic characters (if any) in lower case :
*
*                                   DEF_NO          Format alphabetic characters in upper case.
*                                   DEF_YES         Format alphabetic characters in lower case.
*
*               nul             Append terminating NULL-character (see Note #4) :
*
*                                   DEF_NO          Do NOT append terminating NULL-character to string.
*                                   DEF_YES                Append terminating NULL-character to string.
*
*               pstr            Pointer to character array to return formatted number string (see Note #5).
*
* Return(s)   : Pointer to formatted string, if NO error(s).
*
*               Pointer to NULL,             otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) If the number of digits to format ('nbr_dig') is zero; then NO formatting 
*                       is performed except possible NULL-termination of the string (see Note #4).
*
*                           Example :
*
*                               nbr      = -23456
*                               nbr_dig  =  0
*                               nbr_base = 10
*
*                               pstr     = ""                   See Note #6a
*
*                   (b) If the number of digits to format ('nbr_dig') is less than the number of 
*                       significant integer digits of the number to format ('nbr'); then an invalid 
*                       string is formatted instead of truncating any significant integer digits.
*
*                           Example :
*
*                               nbr      = 23456
*                               nbr_dig  = 3
*                               nbr_base = 10
*
*                               pstr     = "???"                See Note #6b
*
*                   (c) If the number to format ('nbr') is negative but the number of digits to format 
*                       ('nbr_dig') is equal to the number of significant integer digits of the number 
*                       to format ('nbr'); then an invalid string is formatted instead of truncating 
*                       the negative sign.
*
*                           Example :
*
*                               nbr      = -23456
*                               nbr_dig  =  5
*                               nbr_base = 10
*
*                               pstr     = "?????"              See Note #6b
*
*               (2) The number's base MUST be between 2 & 36, inclusive.
*$PAGE*
*               (3) Leading character option prepends leading characters prior to the first non-zero digit.
*
*                   (a) (1) Leading character MUST be a printable ASCII character.
*
*                       (2) (A) Leading character MUST NOT be a number base digit, ...
*                           (B) with the exception of '0'.
*
*                   (b) (1) The number of leading characters is such that the total number of significant 
*                           integer digits plus the number of leading characters plus possible negative 
*                           sign character is equal to the requested number of integer digits to format 
*                           ('nbr_dig').
*
*                               Examples :
*
*                                   nbr       = 23456
*                                   nbr_dig   = 7
*                                   nbr_base  = 10
*                                   lead_char = ' '
*
*                                   pstr      = "  23456"
*
*
*                                   nbr       = -23456
*                                   nbr_dig   =  7
*                                   nbr_base  = 10
*                                   lead_char = ' '
*
*                                   pstr      = " -23456"
*
*                       (2) (A) If the number to format ('nbr') is negative AND the leading character 
*                               ('lead_char') is     a '0' digit; then the negative sign character 
*                               prefixes all leading characters prior to the formatted number.
*
*                                   Examples :
*
*                                       nbr        = -23456
*                                       nbr_dig    =  8
*                                       nbr_base   = 10
*                                       lead_char  = '0'
*
*                                       pstr       = "-0023456"
*
*
*                                       nbr        = -43981
*                                       nbr_dig    =  8
*                                       nbr_base   = 16
*                                       lead_char  = '0'
*                                       lower_case = DEF_NO
*
*                                       pstr       = "-000ABCD"
*
*                           (B) If the number to format ('nbr') is negative AND the leading character 
*                               ('lead_char') is NOT a '0' digit; then the negative sign character 
*                               immediately prefixes the most significant digit of the formatted number.
*
*                                   Examples :
*
*                                       nbr        = -23456
*                                       nbr_dig    =  8
*                                       nbr_base   = 10
*                                       lead_char  = '#'
*
*                                       pstr       = "##-23456"
*
*
*                                       nbr        = -43981
*                                       nbr_dig    =  8
*                                       nbr_base   = 16
*                                       lead_char  = '#'
*                                       lower_case = DEF_YES
*
*                                       pstr       = "###-abcd"
*
*                   (c) (1) If the value of the number to format is     zero  ...
*                       (2) ... & the number of digits to format is non-zero, ...
*                       (3) ... but NO leading character available;           ...
*                       (4) ... then one digit of '0' value is formatted.
*
*                           This is NOT a leading character; but a single integer digit of '0' value.
*$PAGE*
*               (4) (a) NULL-character terminate option DISABLED prevents overwriting previous character
*                       array formatting.
*
*                   (b) WARNING: Unless 'pstr' character array is pre-/post-terminated, NULL-character
*                       terminate option DISABLED will cause character string run-on.
*
*               (5) (a) Format buffer size NOT validated; buffer overruns MUST be prevented by caller.
*
*                   (b) To prevent character buffer overrun :
*
*                           Character array size MUST be  >=  ('nbr_dig'          +
*                                                               1 negative sign   +
*                                                               1 'NUL' terminator)  characters
*
*               (6) For any unsuccessful string format or error(s), an invalid string of question marks 
*                   ('?') will be formatted, where the number of question marks is determined by the 
*                   number of digits to format ('nbr_dig') :
*
*                      Invalid string's     {  (a)   0 (NULL string)  ,  if 'nbr_dig' = 0
*                          number of     =  {
*                       question marks      {  (b)  'nbr_dig'         ,  if 'nbr_dig' > 0
*
*********************************************************************************************************
*/

CPU_CHAR  *Str_FmtNbr_Int32S (CPU_INT32S    nbr,
                              CPU_INT08U    nbr_dig,
                              CPU_INT08U    nbr_base,
                              CPU_CHAR      lead_char,
                              CPU_BOOLEAN   lower_case,
                              CPU_BOOLEAN   nul,
                              CPU_CHAR     *pstr)
{
    CPU_CHAR     *pstr_fmt;
    CPU_INT32S    nbr_fmt;
    CPU_BOOLEAN   nbr_neg;


    if (nbr < 0) {                                              /* If nbr neg, ...                                      */
        nbr_fmt = -nbr;                                         /* ... negate nbr.                                      */
        nbr_neg =  DEF_YES;
    } else {
        nbr_fmt =  nbr;
        nbr_neg =  DEF_NO;
    }

    pstr_fmt = Str_FmtNbr_Int32((CPU_INT32U)nbr_fmt,            /* Fmt signed int into str.                             */
                                            nbr_dig,
                                            nbr_base,
                                            nbr_neg,
                                            lead_char,
                                            lower_case,
                                            nul,
                                            pstr);

    return (pstr_fmt);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                           Str_FmtNbr_32()
*
* Description : Format number into a multi-digit character string.
*
* Argument(s) : nbr             Number                         to format (see Note #1).
*
*               nbr_dig         Number of decimal       digits to format (see Note #2).
*
*               nbr_dp          Number of decimal point digits to format.
*
*               lead_char       Prepend leading character (see Note #3) :
*
*                                   '\0'                    Do NOT prepend leading character to string.
*                                     Printable character          Prepend leading character to string.
*                                   Unprintable character   Format invalid string (see Note #6d).
*
*               nul             Append terminating NULL-character (see Note #4) :
*
*                                   DEF_NO          Do NOT append terminating NULL-character to string.
*                                   DEF_YES                Append terminating NULL-character to string.
*
*               pstr            Pointer to character array to return formatted number string (see Note #5).
*
* Return(s)   : Pointer to formatted string, if NO error(s) [see Note #6c].
*
*               Pointer to NULL,             otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) The maximum accuracy for 32-bit floating-point numbers :
*
*
*                                 Maximum Accuracy            log [Internal-Base ^ (Number-Internal-Base-Digits)]
*                           32-bit Floating-point Number  =  -----------------------------------------------------
*                                                                             log [External-Base]
*
*                                                             log [2 ^ 24]
*                                                         =  --------------
*                                                               log [10]
*
*                                                         <  7.225  Base-10 Digits
*
*                               where
*                                       Internal-Base                   Internal number base of floating-
*                                                                           point numbers (i.e.  2)
*                                       External-Base                   External number base of floating-
*                                                                           point numbers (i.e. 10)
*                                       Number-Internal-Base-Digits     Number of internal number base
*                                                                           significant digits (i.e. 24)
*
*                   (b) Some CPUs' &/or compilers' floating-point implementations MAY further reduce the 
*                       maximum accuracy.
*$PAGE*
*               (2) (a) If the total number of digits to format ('nbr_dig + nbr_dp') is zero; then NO 
*                       formatting is performed except possible NULL-termination of the string (see Note #4).
*
*                           Example :
*
*                               nbr     = -23456.789
*                               nbr_dig =  0
*                               nbr_dp  =  0
*
*                               pstr    = ""                        See Note #7a
*
*                   (b) (1) If the number of digits to format ('nbr_dig') is less than the number of 
*                           significant integer digits of the number to format ('nbr'); then an invalid 
*                           string is formatted instead of truncating any significant integer digits.
*
*                               Example :
*
*                                   nbr     = 23456.789
*                                   nbr_dig = 3
*                                   nbr_dp  = 2
*
*                                   pstr    = "??????"              See Note #7d
*
*                       (2) If the number to format ('nbr') is negative but the number of digits to format 
*                           ('nbr_dig') is equal to the number of significant integer digits of the number 
*                           to format ('nbr'); then an invalid string is formatted instead of truncating 
*                           the negative sign.
*
*                               Example :
*
*                                   nbr     = -23456.789
*                                   nbr_dig =  5
*                                   nbr_dp  =  2
*
*                                   pstr    = "????????"            See Note #7d
*
*                       (3) If the number to format ('nbr') is negative but the number of significant 
*                           integer digits is zero, & the number of digits to format ('nbr_dig') is one 
*                           but the number of decimal point digits to format ('nbr_dp') is zero; then 
*                           an invalid string is formatted instead of truncating the negative sign.
*
*                               Example :
*
*                                   nbr     = -0.7895
*                                   nbr_dig =  1
*                                   nbr_dp  =  0
*
*                                   pstr    = "?"                   See Note #7d
*
*                       (4) (A) If the number to format ('nbr') is negative but the number of significant 
*                               integer digits is zero, & the number of digits to format ('nbr_dig') is 
*                               zero but the number of decimal point digits to format ('nbr_dp') is non-
*                               zero; then the negative sign immediately prefixes the decimal point -- 
*                               with NO decimal digits formatted, NOT even a single decimal digit of '0'.
*
*                                   Example :
*
*                                       nbr     = -0.7895
*                                       nbr_dig =  0
*                                       nbr_dp  =  2
*
*                                       pstr    = "-.78"
*
*                           (B) If the number to format ('nbr') is positive but the number of significant 
*                               integer digits is zero, & the number of digits to format ('nbr_dig') is 
*                               zero but the number of decimal point digits to format ('nbr_dp') is non-
*                               zero; then a single decimal digit of '0' prefixes the decimal point.
*
*                               This '0' digit is used whenever a negative sign is not formatted (see 
*                               Note #2b4A) so that the formatted string's decimal point is not floating, 
*                               but fixed in the string as the 2nd character.
*
*                                   Example :
*
*                                       nbr     =  0.7895
*                                       nbr_dig =  0
*                                       nbr_dp  =  2
*
*                                       pstr    = "0.78"
*$PAGE*
*                   (c) (1) If the total number of digits to format ('nbr_dig + nbr_dp') is greater than ... :
*
*                           (A) ... the maximum accuracy of the CPU's &/or compiler's 32-bit floating-point 
*                               numbers, digits following all significantly-accurate digits of the number to 
*                               format ('nbr') will be inaccurate; ...
*                           (B) ... the configured maximum accuracy ('LIB_STR_CFG_FP_MAX_NBR_DIG_SIG'), all 
*                               digits or decimal places following all significantly-accurate digits of the 
*                               number to format ('nbr') will be replaced & formatted with zeros ('0').
*
*                                   Example :
*
*                                       nbr                            = 123456789.012345
*                                       nbr_dig                        = 9
*                                       nbr_dp                         = 6
*                                       LIB_STR_CFG_FP_MAX_NBR_DIG_SIG = 7
*
*                                       pstr                           = "123456700.000000"
*
*                       (2) Therefore, one or more least-significant digit(s) of the number to format ('nbr') 
*                           MAY be rounded & not necessarily truncated due to the inaccuracy of the CPU's 
*                           &/or compiler's floating-point implementation.
*
*                       See also Note #1.
*
*               (3) Leading character option prepends leading characters prior to the first non-zero digit.
*
*                   (a) (1) Leading character MUST be a printable ASCII character.
*
*                       (2) (A) Leading character MUST NOT be a base-10 digit, ...
*                           (B) with the exception of '0'.
*
*                   (b) (1) The number of leading characters is such that the total number of significant 
*                           integer digits plus the number of leading characters plus possible negative 
*                           sign character is equal to the requested number of integer digits to format 
*                           ('nbr_dig').
*
*                               Examples :
*
*                                   nbr       = 23456.789
*                                   nbr_dig   = 7
*                                   nbr_dp    = 2
*                                   lead_char = ' '
*
*                                   pstr      = "  23456.78"
*
*
*                                   nbr       = -23456.789
*                                   nbr_dig   =  7
*                                   nbr_dp    =  2
*                                   lead_char = ' '
*
*                                   pstr      = " -23456.78"
*
*                       (2) (A) If the number to format ('nbr') is negative AND the leading character 
*                               ('lead_char') is     a '0' digit; then the negative sign character 
*                               prefixes all leading characters prior to the formatted number.
*
*                                   Example :
*
*                                       nbr       = -23456.789
*                                       nbr_dig   =  8
*                                       nbr_dp    =  2
*                                       lead_char = '0'
*
*                                       pstr      = "-0023456.78"
*
*                           (B) If the number to format ('nbr') is negative AND the leading character 
*                               ('lead_char') is NOT a '0' digit; then the negative sign character 
*                               immediately prefixes the most significant digit of the formatted number.
*
*                                   Examples :
*
*                                       nbr       = -23456.789
*                                       nbr_dig   =  8
*                                       nbr_dp    =  2
*                                       lead_char = '#'
*
*                                       pstr      = "##-23456.78"
*
*                   (c) (1) If the integer value of the number to format is zero & ...
*                       (2) ... the number of digits to format is greater than one ...
*                       (3) ... OR  the number is NOT negative,                    ...
*                       (4) ... but NO leading character available;                ...
*                       (5) ... then one digit of '0' value is formatted.
*
*                           This is NOT a leading character; but a single integer digit of '0' value.
*
*                       See also Note #2b4B.
*$PAGE*
*               (4) (a) NULL-character terminate option DISABLED prevents overwriting previous character
*                       array formatting.
*
*                   (b) WARNING: Unless 'pstr' character array is pre-/post-terminated, NULL-character
*                       terminate option DISABLED will cause character string run-on.
*
*               (5) (a) Format buffer size NOT validated; buffer overruns MUST be prevented by caller.
*
*                   (b) To prevent character buffer overrun :
*
*                           Character array size MUST be  >=  ('nbr_dig'          +
*                                                              'nbr_dp'           +
*                                                               1 negative sign   +
*                                                               1 decimal point   +
*                                                               1 'NUL' terminator)  characters
*
*               (6) String format terminates when :
*
*                   (a) Format string pointer is passed a NULL pointer.
*                       (1) No      string formatted;                NULL pointer returned.
*
*                   (b) Total number of digits to format ('nbr_dig + nbr_dp') is zero.
*                       (1) NULL    string formatted (see Note #7a); NULL pointer returned.
*
*                   (c) Number of digits to format ('nbr_dig') is less than number of significant 
*                           integer digits of the number to format ('nbr'), including possible 
*                           negative sign.
*                       (1) Invalid string formatted (see Note #7);  NULL pointer returned.
*
*                   (d) Lead character is NOT a valid, printable character (see Note #3a).
*                       (1) Invalid string formatted (see Note #7);  NULL pointer returned.
*
*                   (e) Number successfully formatted into character string array.
*
*               (7) For any unsuccessful string format or error(s), an invalid string of question marks 
*                   ('?') will be formatted, where the number of question marks is determined by the 
*                   number of digits ('nbr_dig') & number of decimal point digits ('nbr_dp') to format :
*
*                                           {  (a)    0 (NULL string)          ,  if 'nbr_dig' = 0  AND
*                                           {                                        'nbr_dp'  = 0
*                                           {
*                                           {  (b)   'nbr_dig'                 ,  if 'nbr_dig' > 0  AND
*                                           {                                        'nbr_dp'  = 0
*                      Invalid string's     {
*                          number of     =  {  (c)  ['nbr_dp'               +  ,  if 'nbr_dig' = 0  AND
*                       question marks      {         1 (for decimal point) +        'nbr_dp'  > 0
*                                           {         1 (for negative sign) ]
*                                           {
*                                           {  (d)  ['nbr_dig'              +  ,  if 'nbr_dig' > 0  AND
*                                           {        'nbr_dp'               +        'nbr_dp'  > 0
*                                           {         1 (for decimal point) ]
*
*********************************************************************************************************
*/

#if (LIB_STR_CFG_FP_EN == DEF_ENABLED)
CPU_CHAR  *Str_FmtNbr_32 (CPU_FP32      nbr,
                          CPU_INT08U    nbr_dig,
                          CPU_INT08U    nbr_dp,
                          CPU_CHAR      lead_char,
                          CPU_BOOLEAN   nul,
                          CPU_CHAR     *pstr)
{
    CPU_CHAR     *pstr_fmt;
    CPU_DATA      i;
    CPU_FP32      nbr_fmt;
    CPU_FP32      nbr_log;
    CPU_INT32U    nbr_shiftd;
    CPU_INT16U    nbr_dig_max;
    CPU_INT16U    nbr_dig_sig;
    CPU_INT08U    nbr_neg_sign;
    CPU_INT08U    dig_val;
    CPU_FP32      dig_exp;
    CPU_FP32      dp_exp;
    CPU_BOOLEAN   lead_char_dig;
    CPU_BOOLEAN   lead_char_fmtd;
    CPU_BOOLEAN   lead_char_0;
    CPU_BOOLEAN   fmt_invalid;
    CPU_BOOLEAN   print_char;
    CPU_BOOLEAN   nbr_neg;
    CPU_BOOLEAN   nbr_neg_fmtd;


/*$PAGE*/
                                                                /* ---------------- VALIDATE FMT ARGS ----------------- */
    if (pstr == (CPU_CHAR *)0) {                                /* Rtn NULL if str ptr NULL (see Note #6a).             */
        return ((CPU_CHAR *)0);
    }

    fmt_invalid = DEF_NO;

    if ((nbr_dig < 1) && (nbr_dp < 1)) {                        /* If nbr digs/dps = 0, ...                             */
        fmt_invalid = DEF_YES;                                  /* ... fmt invalid str (see Note #6b).                  */
    }

    if (lead_char != (CPU_CHAR)'\0') {
        print_char =  ASCII_IsPrint(lead_char);
        if (print_char != DEF_YES) {                            /* If lead char non-printable  (see Note #3a1), ...     */
            fmt_invalid = DEF_YES;                              /* ... fmt invalid str         (see Note #6d).          */

        } else if (lead_char != '0') {                          /* Chk lead char for non-0 dig.                         */
            lead_char_dig = ASCII_IsDig(lead_char);
            if (lead_char_dig == DEF_YES) {                     /* If  lead char     non-0 dig (see Note #3a2A), ...    */
                fmt_invalid = DEF_YES;                          /* ... fmt invalid str         (see Note #6d).          */
            }
        }
    }


                                                                /* ----------------- PREPARE NBR FMT ------------------ */
    pstr_fmt = pstr;

    if (fmt_invalid == DEF_NO) {
        if (nbr < 0.0f) {                                       /* If nbr neg, ...                                      */
            nbr_fmt      = -nbr;                                /* ... negate nbr.                                      */
            nbr_neg_sign =  1u;
            nbr_neg      =  DEF_YES;
        } else {
            nbr_fmt      =  nbr;
            nbr_neg_sign =  0u;
            nbr_neg      =  DEF_NO;
        }

        nbr_log     = nbr_fmt;
        nbr_dig_max = 0u;
        while (nbr_log >= 1.0f) {                               /* While base-10 digs avail, ...                        */
            nbr_dig_max++;                                      /* ... calc max nbr digs.                               */
            nbr_log /= 10.0f;
        }

        if (((nbr_dig >= (nbr_dig_max + nbr_neg_sign)) ||       /* If req'd nbr digs >= (max nbr digs + neg sign)    .. */
             (nbr_dig_max < 1))                        &&       /* .. or NO nbr digs,                                .. */
            ((nbr_dig     > 1) ||                               /* .. but NOT [(req'd nbr dig = 1) AND               .. */
             (nbr_dp      > 0) ||                               /* ..          (req'd nbr dp  = 0) AND               .. */
             (nbr_neg == DEF_NO))) {                            /* ..          (      nbr neg    )]   (see Note #2b3).  */
                                                                /* .. prepare nbr digs to fmt.                          */
            dig_exp = 1.0f;
            for (i = 1u; i < nbr_dig; i++) {
                dig_exp *= 10.0f;
            }

            nbr_neg_fmtd   =  DEF_NO;
            nbr_dig_sig    =  0u;
            lead_char_fmtd =  DEF_NO;
            lead_char_0    = (lead_char == '0')                 /* Chk if lead char a '0' dig (see Note #3b2).          */
                           ?  DEF_YES : DEF_NO;

        } else {                                                /* Else if nbr trunc'd, ...                             */
            fmt_invalid = DEF_YES;                              /* ... fmt invalid str (see Note #6c).                  */
        }
    }


/*$PAGE*/
                                                                /* ------------------- FMT NBR STR -------------------- */
    for (i = nbr_dig; i > 0; i--) {                             /* Fmt str for desired nbr digs :                       */
        if (fmt_invalid == DEF_NO) {
            if (nbr_dig_sig < LIB_STR_CFG_FP_MAX_NBR_DIG_SIG) { /* If nbr sig digs < max, fmt str digs;           ...   */
                nbr_shiftd = (CPU_INT32U)(nbr_fmt / dig_exp);
                if ((nbr_shiftd > 0) ||                         /* If shifted nbr > 0                          ...      */
                    (i == 1u)) {                                /* ... OR on one's dig to fmt (see Note #3c1), ...      */
                                                                /* ... calc & fmt dig val;                     ...      */
                    if ((nbr_neg      == DEF_YES) &&            /* If  nbr neg                     ...                  */
                        (nbr_neg_fmtd == DEF_NO )) {            /* ... but neg sign NOT yet fmt'd; ...                  */

                        if (lead_char_fmtd == DEF_YES) {        /* ... & if lead char(s) fmt'd,    ...                  */
                            pstr_fmt--;                         /* ... replace last lead char w/   ...                  */
                        }
                       *pstr_fmt++   = '-';                     /* ... prepend neg sign (see Notes #2b & #3b).          */
                        nbr_neg_fmtd = DEF_YES;
                    }

                    if (nbr_shiftd > 0) {                       /* If shifted nbr > 0,        ...                       */
                        dig_val    = (CPU_INT08U)(nbr_shiftd % 10u);
                       *pstr_fmt++ = (CPU_CHAR  )(dig_val    + '0');

                        nbr_dig_sig++;                          /* ... inc nbr sig digs;      ...                       */

                    } else if ((nbr_dig > 1) ||                 /* ... else if req'd digs > 1 ...                       */
                               (nbr_neg == DEF_NO)) {           /* ... or non-neg nbr,        ...                       */
                       *pstr_fmt++ = '0';                       /* ... fmt one '0' char (see Note #3c5).                */
                    }

                } else if ((nbr_neg      == DEF_YES) &&         /* ... else if nbr neg                         ...      */
                           (lead_char_0  == DEF_YES) &&         /* ... & lead char a '0' dig                   ...      */
                           (nbr_neg_fmtd == DEF_NO )) {         /* ... but neg sign NOT yet fmt'd,             ...      */

                   *pstr_fmt++   = '-';                         /* ... prepend neg sign (see Note #3b);        ...      */
                    nbr_neg_fmtd = DEF_YES;

                } else if (lead_char != (CPU_CHAR)'\0') {       /* ... else if avail,                          ...      */
                   *pstr_fmt++     = lead_char;                 /* ... fmt lead char.                                   */
                    lead_char_fmtd = DEF_YES;
                }

                dig_exp /= 10.0f;                               /* Shift to next least-sig dig.                         */

            } else {                                            /* ... else append non-sig 0's (see Note #2c2).         */
               *pstr_fmt++ = '0';
            }

        } else {                                                /* Else fmt '?' for invalid str (see Note #7).          */
           *pstr_fmt++ = '?';
        }
    }


/*$PAGE*/
    if (nbr_dp > 0) {                                           /* Fmt str for desired nbr dp :                         */
        if (nbr_dig < 1) {                                      /* If NO digs fmt'd;                             ...    */
            if (fmt_invalid == DEF_NO) {                        /* ... nbr fmt valid,                            ...    */
                if ((nbr_neg      == DEF_YES) &&                /* ... nbr neg                                   ...    */
                    (nbr_neg_fmtd == DEF_NO )) {                /* ... but neg sign NOT yet fmt'd,               ...    */
                    *pstr_fmt++ = '-';                          /* ... prepend neg sign (see Notes #2b & #3b);   ...    */
                } else {                                        /* ... else prepend 1 dig of '0' (see Note #3c5) ...    */
                    *pstr_fmt++ = '0';
                }
            } else {                                            /* ... else fmt '?' for invalid str (see Note #7).      */
                *pstr_fmt++ = '?';
            }
        }

        if (fmt_invalid == DEF_NO) {                            /* If nbr fmt valid, ...                                */
           *pstr_fmt++ = '.';                                   /* ... append dp prior to dp conversion.                */
        } else {                                                /* Else fmt '?' for invalid str (see Note #7).          */
           *pstr_fmt++ = '?';
        }

        dp_exp = 10.0f;
        for (i = 0u; i < nbr_dp; i++) {
            if (fmt_invalid == DEF_NO) {
                                                                /* If nbr sig digs < max, fmt str dps;    ...           */
                if (nbr_dig_sig <  LIB_STR_CFG_FP_MAX_NBR_DIG_SIG) {
                    nbr_shiftd  = (CPU_INT32U)(nbr_fmt * dp_exp);
                    dig_val     = (CPU_INT32U)(nbr_shiftd % 10u);
                   *pstr_fmt++  = (CPU_CHAR  )(dig_val    + '0');
                    dp_exp     *=  10.0f;                       /* Shift to next least-sig dp.                          */

                    if ((nbr_shiftd  > 0) ||                    /* If shifted nbr > 0                  ...              */
                        (nbr_dig_sig > 0)) {                    /* ... OR  > 0 sig digs already fmt'd, ...              */
                         nbr_dig_sig++;                         /* ... inc nbr sig digs.                                */
                    }

                } else {                                        /* ... else append non-sig 0's (see Note #2c2).         */
                   *pstr_fmt++ = '0';
                }

            } else {                                            /* Else fmt '?' for invalid str (see Note #7).          */
               *pstr_fmt++ = '?';
            }
        }
    }


    if (nul != DEF_NO) {                                        /* If NOT DISABLED, append NULL char (see Note #4).     */
       *pstr_fmt = (CPU_CHAR)'\0';
    }


    if (fmt_invalid != DEF_NO) {                                /* Rtn NULL for invalid str fmt (see Notes #6a - #6d).  */
        return ((CPU_CHAR *)0);
    }


    return (pstr);                                              /* Rtn ptr to fmt'd str (see Note #6e).                 */
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        Str_ParseNbr_Int32U()
*
* Description : Parse 32-bit unsigned integer from string.
*
* Argument(s) : pstr        Pointer to string (see Notes #1 & #2a).
*
*               pstr_next   Optional pointer to a variable to ... :
*
*                               (a) Return a pointer to first character following the integer string,
*                                       if NO error(s) [see Note #2a2B2];
*                               (b) Return a pointer to 'pstr',
*                                       otherwise      (see Note #2a2A2).
*
*               nbr_base    Base of number to parse (see Notes #2a1B1 & #2a2B1).
*
* Return(s)   : Parsed integer,      if integer parsed with NO overflow   (see Note #2a3A).
*
*               DEF_INT_32U_MAX_VAL, if integer parsed but     overflowed (see Note #2a3A1).
*
*               0,                   otherwise                            (see Note #2a3B).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffer NOT modified.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'strtoul() : DESCRIPTION' states that "these
*                       functions shall convert the initial portion of the string pointed to by 'str' ('pstr') 
*                       to a type unsigned long ... representation" :
*
*                       (1) "First, they decompose the input string into three parts" :
*
*                           (A) "An initial, possibly empty, sequence of white-space characters [as specified
*                                by isspace()]."
*
*                               (1) "The subject sequence is defined as the longest initial subsequence of the
*                                    input string, starting with the first non-white-space character that is of
*                                    the expected form.  The subject sequence shall contain no characters if the
*                                    input string is empty or consists entirely of white-space characters."
*
*                           (B) (1) "A subject sequence interpreted as an integer represented in some radix
*                                    determined by the value of 'base' ('nbr_base')" :
*
*                                   (a) "If the value of 'base' ('nbr_base') is 0, the expected form of the 
*                                        subject sequence is that of a decimal constant, octal constant, or 
*                                        hexadecimal constant" :
*
*                                       (1) "A decimal constant begins with a non-zero digit, and consists of a
*                                            sequence of decimal digits."
*
*                                       (2) "An octal constant consists of the prefix '0' optionally followed by
*                                            a sequence of the digits '0' to '7' only."
*
*                                       (3) "A hexadecimal constant consists of the prefix '0x' or '0X' followed
*                                            by a sequence of the decimal digits and letters 'a' (or 'A') to 'f'
*                                            (or 'F') with values 10 to 15 respectively."
*
*                                   (b) "If the value of 'base' ('nbr_base') is between 2 and 36, the expected form 
*                                        of the subject sequence is a sequence of letters and digits representing 
*                                        an integer with the radix specified by 'base' ('nbr_base')" :
*
*                                       (1) (A) "The letters from 'a' (or 'A') to 'z' (or 'Z') inclusive are
*                                                ascribed the values 10 to 35"; ...
*                                           (B) "only letters whose ascribed values are less than that of base
*                                                are permitted."
*
*                                       (2) (A) "If the value of 'base' ('nbr_base') is 16, the characters '0x' or 
*                                                '0X' may optionally precede the sequence of letters and digits."
*
*                                           (B) Although NO specification states that "if the value of 'base' 
*                                               ('nbr_base') is" 8, the '0' character "may optionally precede 
*                                               the sequence of letters and digits"; it seems reasonable to 
*                                               allow the '0' character to be optionally parsed.
*
*                               (2) "A subject sequence .... may be preceded by a '+' or '-' sign."
*
*                                   (a) However, it does NOT seem reasonable to parse & convert a negative number
*                                       integer string into an unsigned integer.
*
*                           (C) (1) (a) "A final string of one or more unrecognized characters,"  ...
*                                   (b) "including the terminating null byte of the input string" ...
*                               (2) "other than a sign or a permissible letter or digit."
*$PAGE*
*                       (2) Second, "they shall attempt to convert the subject sequence to an unsigned integer" :
*
*                           (A) "If the subject sequence is empty or does not have the expected form" :
*
*                               (1) "no conversion [is] performed"; ...
*                               (2) "the value of 'str' ('pstr') [is] stored in the object pointed to by 'endptr' 
*                                    ('pstr_next'), provided that 'endptr' ('pstr_next') is not a null pointer."
*
*                           (B) "If the subject sequence has the expected form" :
*
*                               (1) (a) "and the value of 'base' ('nbr_base') is 0, the sequence of characters 
*                                        starting with the first digit shall be interpreted as an integer constant."
*
*                                   (b) "and the value of 'base' ('nbr_base') is between 2 and 36, it shall be 
*                                        used as the base for conversion, ascribing to each letter its value as 
*                                        given above" (see Note #2a1B1b1A).
*
*                               (2) "A pointer to the final string shall be stored in the object pointed to by
*                                   'endptr' ('pstr_next'), provided that 'endptr' ('pstr_next') is not a null 
*                                   pointer."
*
*                       (3) Lastly, IEEE Std 1003.1, 2004 Edition, Section 'strtoul() : RETURN VALUE' states that :
*
*                           (A) "Upon successful completion, these functions shall return the converted value."
*                               (1) "If the correct value is outside the range of representable values, {ULONG_MAX}
*                                    ... shall be returned."
*
*                           (B) "If no conversion could be performed, 0 shall be returned."
*
*                   (b) (1) IEEE Std 1003.1, 2004 Edition, Section 'strtoul() : ERRORS' states that "these functions
*                           shall fail if" :
*
*                           (A) "[EINVAL] - The value of 'base' ('nbr_base') is not supported."
*
*                           (B) "[ERANGE] - The value to be returned is not representable."
*
*                       (2) IEEE Std 1003.1, 2004 Edition, Section 'strtoul() : ERRORS' states that "these functions
*                           may fail if" :
*
*                           (A) "[EINVAL] - No conversion could be performed."
*
*               (3) Return integer value & next string pointer should be used to diagnose parse success or failure :
*
*                   (a) Valid parse string integer :
*
*                           pstr      = "     ABCDE xyz"
*                           nbr_base  = 16
*
*                           nbr       = 703710
*                           pstr_next = " xyz"
*
*
*                   (b) Invalid parse string integer :
*
*                           pstr      = "     ABCDE"
*                           nbr_base  = 10
*
*                           nbr       =  0
*                           pstr_next = pstr = "     ABCDE"
*
*
*                   (c) Valid hexadecimal parse string integer :
*
*                           pstr      = "     0xGABCDE"
*                           nbr_base  = 16
*
*                           nbr       =  0
*                           pstr_next = "xGABCDE"
*
*
*                   (d) Valid decimal parse string integer ('0x' prefix ignored
*                               following invalid hexadecimal characters) :
*
*                           pstr      = "     0xGABCDE"
*                           nbr_base  =  0
*
*                           nbr       =  0
*                           pstr_next = "xGABCDE"
*
*
*                   (e) Valid decimal parse string integer ('0'  prefix ignored
*                               following invalid octal       characters) :
*
*                           pstr      = "     0GABCDE"
*                           nbr_base  =  0
*
*                           nbr       =  0
*                           pstr_next = "GABCDE"
*
*$PAGE*
*                   (f) Parse string integer overflow :
*
*                           pstr      = "   12345678901234567890*123456"
*                           nbr_base  = 10
*
*                           nbr       = DEF_INT_32U_MAX_VAL
*                           pstr_next = "*123456"
*
*
*                   (g) Invalid negative unsigned parse string :
*
*                           pstr      = "  -12345678901234567890*123456"
*                           nbr_base  = 10
*
*                           nbr       = 0
*                           pstr_next = pstr = "  -12345678901234567890*123456"
*
*********************************************************************************************************
*/

CPU_INT32U  Str_ParseNbr_Int32U (const  CPU_CHAR     *pstr,
                                        CPU_CHAR    **pstr_next,
                                        CPU_INT08U    nbr_base)
{
    CPU_INT32U  nbr;


    nbr = Str_ParseNbr_Int32(               pstr,               /* Parse/convert str ...                                */
                                            pstr_next,
                                            nbr_base,
                                            DEF_NO,             /* ... as unsigned int (see Note #2a2).                 */
                             (CPU_BOOLEAN *)0);

    return (nbr);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                        Str_ParseNbr_Int32S()
*
* Description : Parse 32-bit signed integer from string.
*
* Argument(s) : pstr        Pointer to string (see Notes #1 & #2a).
*
*               pstr_next   Optional pointer to a variable to ... :
*
*                               (a) Return a pointer to first character following the integer string,
*                                       if NO error(s) [see Note #2a2B2];
*                               (b) Return a pointer to 'pstr',
*                                       otherwise      (see Note #2a2A2).
*
*               nbr_base    Base of number to parse (see Notes #2a1B1 & #2a2B1).
*
* Return(s)   : Parsed integer,      if integer parsed with NO over- or underflow (see Note #2a3A).
*
*               DEF_INT_32S_MIN_VAL, if integer parsed but negatively underflowed (see Note #2a3A1a).
*
*               DEF_INT_32U_MAX_VAL, if integer parsed but positively overflowed  (see Note #2a3A1b).
*
*               0,                   otherwise                                    (see Note #2a3B).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) String buffer NOT modified.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'strtol() : DESCRIPTION' states that "these
*                       functions shall convert the initial portion of the string pointed to by 'str' ('pstr') 
*                       to a type long ... representation" :
*
*                       (1) "First, they decompose the input string into three parts" :
*
*                           (A) "An initial, possibly empty, sequence of white-space characters [as specified
*                                by isspace()]."
*
*                               (1) "The subject sequence is defined as the longest initial subsequence of the
*                                    input string, starting with the first non-white-space character that is of
*                                    the expected form.  The subject sequence shall contain no characters if the
*                                    input string is empty or consists entirely of white-space characters."
*
*                           (B) (1) "A subject sequence interpreted as an integer represented in some radix
*                                    determined by the value of 'base' ('nbr_base')" :
*
*                                   (a) "If the value of 'base' ('nbr_base') is 0, the expected form of the 
*                                        subject sequence is that of a decimal constant, octal constant, or 
*                                        hexadecimal constant" :
*
*                                       (1) "A decimal constant begins with a non-zero digit, and consists of a
*                                            sequence of decimal digits."
*
*                                       (2) "An octal constant consists of the prefix '0' optionally followed by
*                                            a sequence of the digits '0' to '7' only."
*
*                                       (3) "A hexadecimal constant consists of the prefix '0x' or '0X' followed
*                                            by a sequence of the decimal digits and letters 'a' (or 'A') to 'f'
*                                            (or 'F') with values 10 to 15 respectively."
*
*                                   (b) "If the value of 'base' ('nbr_base') is between 2 and 36, the expected form 
*                                        of the subject sequence is a sequence of letters and digits representing 
*                                        an integer with the radix specified by 'base' ('nbr_base')" :
*
*                                       (1) (A) "The letters from 'a' (or 'A') to 'z' (or 'Z') inclusive are
*                                                ascribed the values 10 to 35"; ...
*                                           (B) "only letters whose ascribed values are less than that of base
*                                                are permitted."
*
*                                       (2) (A) "If the value of 'base' ('nbr_base') is 16, the characters '0x' or 
*                                                '0X' may optionally precede the sequence of letters and digits."
*
*                                           (B) Although NO specification states that "if the value of 'base' 
*                                               ('nbr_base') is" 8, the '0' character "may optionally precede 
*                                               the sequence of letters and digits"; it seems reasonable to 
*                                               allow the '0' character to be optionally parsed.
*
*                               (2) "A subject sequence .... may be preceded by a '+' or '-' sign."
*
*                                   (a) However, it does NOT seem reasonable to parse & convert a negative number
*                                       integer string into an unsigned integer.
*
*                           (C) (1) (a) "A final string of one or more unrecognized characters,"  ...
*                                   (b) "including the terminating null byte of the input string" ...
*                               (2) "other than a sign or a permissible letter or digit."
*$PAGE*
*                       (2) Second, "they shall attempt to convert the subject sequence to an integer" :
*
*                           (A) "If the subject sequence is empty or does not have the expected form" :
*
*                               (1) "no conversion is performed"; ...
*                               (2) "the value of 'str' ('pstr') is stored in the object pointed to by 'endptr' 
*                                    ('pstr_next'), provided that 'endptr' ('pstr_next') is not a null pointer."
*
*                           (B) "If the subject sequence has the expected form" :
*
*                               (1) (a) "and the value of 'base' ('nbr_base') is 0, the sequence of characters 
*                                        starting with the first digit shall be interpreted as an integer constant."
*
*                                   (b) "and the value of 'base' ('nbr_base') is between 2 and 36, it shall be 
*                                        used as the base for conversion, ascribing to each letter its value as 
*                                        given above" (see Note #2a1B1b1A).
*
*                               (2) "A pointer to the final string shall be stored in the object pointed to by
*                                   'endptr' ('pstr_next'), provided that 'endptr' ('pstr_next') is not a null 
*                                   pointer."
*
*                       (3) Lastly, IEEE Std 1003.1, 2004 Edition, Section 'strtol() : RETURN VALUE' states that :
*
*                           (A) "Upon successful completion, these functions shall return the converted value."
*
*                               (1) "If the correct value is outside the range of representable values", either
*                                    of the following "shall be returned" :
*                                   (a) "{LONG_MIN}" or ...
*                                   (b) "{LONG_MAX}"
*
*                           (B) "If no conversion could be performed, 0 shall be returned."
*
*                   (b) (1) IEEE Std 1003.1, 2004 Edition, Section 'strtoul() : ERRORS' states that "these functions
*                           shall fail if" :
*
*                           (A) "[EINVAL] - The value of 'base' ('nbr_base') is not supported."
*
*                           (B) "[ERANGE] - The value to be returned is not representable."
*
*                       (2) IEEE Std 1003.1, 2004 Edition, Section 'strtoul() : ERRORS' states that "these functions
*                           may fail if" :
*
*                           (A) "[EINVAL] - No conversion could be performed."
*
*               (3) Return integer value & next string pointer should be used to diagnose parse success or failure :
*
*                   (a) Valid parse string integer :
*
*                           pstr      = "     ABCDE xyz"
*                           nbr_base  = 16
*
*                           nbr       = 703710
*                           pstr_next = " xyz"
*
*
*                   (b) Invalid parse string integer :
*
*                           pstr      = "     ABCDE"
*                           nbr_base  = 10
*
*                           nbr       =  0
*                           pstr_next = pstr = "     ABCDE"
*
*
*                   (c) Valid hexadecimal parse string integer :
*
*                           pstr      = "     0xGABCDE"
*                           nbr_base  = 16
*
*                           nbr       =  0
*                           pstr_next = "xGABCDE"
*
*
*                   (d) Valid decimal parse string integer ('0x' prefix ignored
*                               following invalid hexadecimal characters) :
*
*                           pstr      = "     0xGABCDE"
*                           nbr_base  =  0
*
*                           nbr       =  0
*                           pstr_next = "xGABCDE"
*
*
*                   (e) Valid decimal parse string integer ('0'  prefix ignored
*                               following invalid octal       characters) :
*
*                           pstr      = "     0GABCDE"
*                           nbr_base  =  0
*
*                           nbr       =  0
*                           pstr_next = "GABCDE"
*
*$PAGE*
*                   (f) Parse string integer overflow :
*
*                           pstr      = "   12345678901234567890*123456"
*                           nbr_base  = 10
*
*                           nbr       = DEF_INT_32S_MAX_VAL
*                           pstr_next = "*123456"
*
*
*                   (g) Parse string integer underflow :
*
*                           pstr      = "  -12345678901234567890*123456"
*                           nbr_base  = 10
*
*                           nbr       = DEF_INT_32S_MIN_VAL
*                           pstr_next = "*123456"
*
*********************************************************************************************************
*/

CPU_INT32S  Str_ParseNbr_Int32S (const  CPU_CHAR     *pstr,
                                        CPU_CHAR    **pstr_next,
                                        CPU_INT08U    nbr_base)
{
    CPU_INT32S   nbr;
    CPU_INT32U   nbr_abs;
    CPU_BOOLEAN  nbr_neg;


    nbr_abs = Str_ParseNbr_Int32(pstr,                          /* Parse/convert str ...                                */
                                 pstr_next,
                                 nbr_base,
                                 DEF_YES,                       /* ... as signed int (see Note #2a2).                   */
                                &nbr_neg);

    if (nbr_neg == DEF_NO) {                                    /* Chk for neg nbr & ovf/undf (see Note #2a3A1).        */
        nbr = (nbr_abs > (CPU_INT32U) DEF_INT_32S_MAX_VAL)          ?  (CPU_INT32S)DEF_INT_32S_MAX_VAL
                                                                    :  (CPU_INT32S)nbr_abs;
    } else {
        nbr = (nbr_abs > (CPU_INT32U)-DEF_INT_32S_MIN_VAL_ONES_CPL) ?  (CPU_INT32S)DEF_INT_32S_MIN_VAL
                                                                    : -(CPU_INT32S)nbr_abs;
    }

    return (nbr);
}


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
*                                         Str_FmtNbr_Int32()
*
* Description : Format 32-bit integer into a multi-digit character string.
*
* Argument(s) : nbr             Number           to format.
*
*               nbr_dig         Number of digits to format (see Note #1).
*
*               nbr_base        Base   of number to format (see Note #2).
*
*               nbr_neg         Indicates whether number to format is negative :
*               -------
*                                   DEF_NO          Number is non-negative.
*                                   DEF_YES         Number is     negative.
*
*                               Argument validated in Str_FmtNbr_Int32U(),
*                                                     Str_FmtNbr_Int32S().
*
*               lead_char       Prepend leading character  (see Note #3) :
*
*                                   '\0'                    Do NOT prepend leading character to string.
*                                     Printable character          Prepend leading character to string.
*                                   Unprintable character   Format invalid string (see Note #6e).
*
*               lower_case      Format alphabetic characters (if any) in lower case :
*
*                                   DEF_NO          Format alphabetic characters in upper case.
*                                   DEF_YES         Format alphabetic characters in lower case.
*
*               nul             Append terminating NULL-character (see Note #4) :
*
*                                   DEF_NO          Do NOT append terminating NULL-character to string.
*                                   DEF_YES                Append terminating NULL-character to string.
*
*               pstr            Pointer to character array to return formatted number string (see Note #5).
*
* Return(s)   : Pointer to formatted string, if NO error(s) [see Note #6f].
*
*               Pointer to NULL,             otherwise.
*
* Caller(s)   : Str_FmtNbr_Int32U(),
*               Str_FmtNbr_Int32S().
*$PAGE*
* Note(s)     : (1) (a) The maximum number of digits to format for 32-bit integer numbers :
*
*
*                               Maximum Number of             [  log (Number)      ]
*                             32-bit Integer Digits  =  floor [ -------------- + 1 ]
*                                   to Format                 [   log (Base)       ]
*
*                               where
*                                       Number                  Number to format
*                                       Base            Base of number to format
*
*                   (b) (1) If the number of digits to format ('nbr_dig') is zero; then NO formatting 
*                           is performed except possible NULL-termination of the string (see Note #4).
*
*                               Example :
*
*                                   nbr      = -23456
*                                   nbr_dig  =  0
*                                   nbr_base = 10
*
*                                   pstr     = ""                   See Note #7a
*
*                       (2) If the number of digits to format ('nbr_dig') is less than the number of 
*                           significant integer digits of the number to format ('nbr'); then an invalid 
*                           string is formatted instead of truncating any significant integer digits.
*
*                               Example :
*
*                                   nbr      = 23456
*                                   nbr_dig  = 3
*                                   nbr_base = 10
*
*                                   pstr     = "???"                See Note #7b
*
*                       (3) If the number to format ('nbr') is negative but the number of digits to format 
*                           ('nbr_dig') is equal to the number of significant integer digits of the number 
*                           to format ('nbr'); then an invalid string is formatted instead of truncating 
*                           the negative sign.
*
*                               Example :
*
*                                   nbr      = -23456
*                                   nbr_dig  =  5
*                                   nbr_base = 10
*
*                                   pstr     = "?????"              See Note #7b
*
*               (2) The number's base MUST be between 2 & 36, inclusive.
*$PAGE*
*               (3) Leading character option prepends leading characters prior to the first non-zero digit.
*
*                   (a) (1) Leading character MUST be a printable ASCII character.
*
*                       (2) (A) Leading character MUST NOT be a number base digit, ...
*                           (B) with the exception of '0'.
*
*                   (b) (1) The number of leading characters is such that the total number of significant 
*                           integer digits plus the number of leading characters plus possible negative 
*                           sign character is equal to the requested number of integer digits to format 
*                           ('nbr_dig').
*
*                               Examples :
*
*                                   nbr       = 23456
*                                   nbr_dig   = 7
*                                   nbr_base  = 10
*                                   lead_char = ' '
*
*                                   pstr      = "  23456"
*
*
*                                   nbr       = -23456
*                                   nbr_dig   = 7
*                                   nbr_base  = 10
*                                   lead_char = ' '
*
*                                   pstr      = " -23456"
*
*                       (2) (A) If the number to format ('nbr') is negative AND the leading character 
*                               ('lead_char') is     a '0' digit; then the negative sign character 
*                               prefixes all leading characters prior to the formatted number.
*
*                                   Examples :
*
*                                       nbr        = -23456
*                                       nbr_dig    =  8
*                                       nbr_base   = 10
*                                       lead_char  = '0'
*
*                                       pstr       = "-0023456"
*
*
*                                       nbr        = -43981
*                                       nbr_dig    =  8
*                                       nbr_base   = 16
*                                       lead_char  = '0'
*                                       lower_case = DEF_NO
*
*                                       pstr       = "-000ABCD"
*
*                           (B) If the number to format ('nbr') is negative AND the leading character 
*                               ('lead_char') is NOT a '0' digit; then the negative sign character 
*                               immediately prefixes the most significant digit of the formatted number.
*
*                                   Examples :
*
*                                       nbr        = -23456
*                                       nbr_dig    =  8
*                                       nbr_base   = 10
*                                       lead_char  = '#'
*
*                                       pstr       = "##-23456"
*
*
*                                       nbr        = -43981
*                                       nbr_dig    =  8
*                                       nbr_base   = 16
*                                       lead_char  = '#'
*                                       lower_case = DEF_YES
*
*                                       pstr       = "###-abcd"
*
*                   (c) (1) If the value of the number to format is     zero  ...
*                       (2) ... & the number of digits to format is non-zero, ...
*                       (3) ... but NO leading character available;           ...
*                       (4) ... then one digit of '0' value is formatted.
*
*                           This is NOT a leading character; but a single integer digit of '0' value.
*$PAGE*
*               (4) (a) NULL-character terminate option DISABLED prevents overwriting previous character
*                       array formatting.
*
*                   (b) WARNING: Unless 'pstr' character array is pre-/post-terminated, NULL-character
*                       terminate option DISABLED will cause character string run-on.
*
*               (5) (a) Format buffer size NOT validated; buffer overruns MUST be prevented by caller.
*
*                   (b) To prevent character buffer overrun :
*
*                           Character array size MUST be  >=  ('nbr_dig'          +
*                                                               1 negative sign   +
*                                                               1 'NUL' terminator)  characters
*
*               (6) String format terminates when :
*
*                   (a) Format string pointer is passed a NULL pointer.
*                       (1) No      string formatted;                NULL pointer returned.
*
*                   (b) Number of digits to format ('nbr_dig') is zero.
*                       (1) NULL    string formatted (see Note #7a); NULL pointer returned.
*
*                   (c) Number of digits to format ('nbr_dig') is less than number of significant 
*                           integer digits of the number to format ('nbr'), including possible 
*                           negative sign.
*                       (1) Invalid string formatted (see Note #7);  NULL pointer returned.
*
*                   (d) Base is passed an invalid base (see Note #2).
*                       (1) Invalid string format performed; NULL pointer returned.
*
*                   (e) Lead character is NOT a valid, printable character (see Note #3a).
*                       (1) Invalid string formatted (see Note #7);  NULL pointer returned.
*
*                   (f) Number successfully formatted into character string array.
*
*               (7) For any unsuccessful string format or error(s), an invalid string of question marks 
*                   ('?') will be formatted, where the number of question marks is determined by the 
*                   number of digits to format ('nbr_dig') :
*
*                      Invalid string's     {  (a)   0 (NULL string)  ,  if 'nbr_dig' = 0
*                          number of     =  {
*                       question marks      {  (b)  'nbr_dig'         ,  if 'nbr_dig' > 0
*
*********************************************************************************************************
*/

static  CPU_CHAR  *Str_FmtNbr_Int32 (CPU_INT32U    nbr,
                                     CPU_INT08U    nbr_dig,
                                     CPU_INT08U    nbr_base,
                                     CPU_BOOLEAN   nbr_neg,
                                     CPU_CHAR      lead_char,
                                     CPU_BOOLEAN   lower_case,
                                     CPU_BOOLEAN   nul,
                                     CPU_CHAR     *pstr)
{
    CPU_CHAR     *pstr_fmt;
    CPU_DATA      i;
    CPU_INT32U    nbr_fmt;
    CPU_INT32U    nbr_log;
    CPU_INT08U    nbr_dig_max;
    CPU_INT08U    nbr_dig_min;
    CPU_INT08U    nbr_dig_fmtd;
    CPU_INT08U    nbr_neg_sign;
    CPU_INT08U    nbr_lead_char;
    CPU_INT08U    dig_val;
    CPU_INT08U    lead_char_delta_0;
    CPU_INT08U    lead_char_delta_a;
    CPU_BOOLEAN   lead_char_dig;
    CPU_BOOLEAN   lead_char_0;
    CPU_BOOLEAN   fmt_invalid;
    CPU_BOOLEAN   print_char;
    CPU_BOOLEAN   nbr_neg_fmtd;


/*$PAGE*/
                                                                /* ---------------- VALIDATE FMT ARGS ----------------- */
    if (pstr == (CPU_CHAR *)0) {                                /* Rtn NULL if str ptr NULL (see Note #6a).             */
        return ((CPU_CHAR *)0);
    }

    fmt_invalid = DEF_NO;

    if (nbr_dig < 1) {                                          /* If nbr digs = 0, ...                                 */
        fmt_invalid = DEF_YES;                                  /* ... fmt invalid str (see Note #6b).                  */
    }
                                                                /* If invalid base, ...                                 */
    if ((nbr_base <  2u) ||
        (nbr_base > 36u)) {
        fmt_invalid = DEF_YES;                                  /* ... fmt invalid str (see Note #6d).                  */
    }

    if (lead_char != (CPU_CHAR)'\0') {
        print_char =  ASCII_IsPrint(lead_char);
        if (print_char != DEF_YES) {                            /* If lead char non-printable (see Note #3a1), ...      */
            fmt_invalid = DEF_YES;                              /* ... fmt invalid str        (see Note #6e).           */

        } else if (lead_char != '0') {                          /* Chk lead char for non-0 nbr base dig.                */
            lead_char_delta_0 = (CPU_INT08U)(lead_char - '0');
            if (lower_case != DEF_YES) {
                lead_char_delta_a = (CPU_INT08U)(lead_char - 'A');
            } else {
                lead_char_delta_a = (CPU_INT08U)(lead_char - 'a');
            }

            lead_char_dig = (((nbr_base <= 10u) &&  (lead_char_delta_0 <  nbr_base))      ||
                             ((nbr_base >  10u) && ((lead_char_delta_0 <             10u) ||
                                                    (lead_char_delta_a < (nbr_base - 10u))))) ? DEF_YES : DEF_NO;

            if (lead_char_dig == DEF_YES) {                     /* If lead char non-0 nbr base dig (see Note #3a2A), ...*/
                fmt_invalid = DEF_YES;                          /* ... fmt invalid str             (see Note #6e).      */
            }
        }
    }


                                                                /* ----------------- PREPARE NBR FMT ------------------ */
    pstr_fmt = pstr;

    if (fmt_invalid == DEF_NO) {
        nbr_fmt     = nbr;
        nbr_log     = nbr;
        nbr_dig_max = 1u;
        while (nbr_log >= nbr_base) {                           /* While nbr base digs avail, ...                       */
            nbr_dig_max++;                                      /* ... calc max nbr digs.                               */
            nbr_log /= nbr_base;
        }

        nbr_neg_sign = (nbr_neg == DEF_YES) ? 1u : 0u;
        if (nbr_dig >= (nbr_dig_max + nbr_neg_sign)) {          /* If req'd nbr digs >= (max nbr digs + neg sign), ...  */
            nbr_neg_fmtd = DEF_NO;
            nbr_dig_min  = DEF_MIN(nbr_dig_max, nbr_dig);
                                                                /* ... calc nbr digs to fmt & nbr lead chars.           */
            if (lead_char != (CPU_CHAR)'\0') {
                nbr_dig_fmtd  = nbr_dig;
                nbr_lead_char = nbr_dig     -
                                nbr_dig_min - nbr_neg_sign;
            } else {
                nbr_dig_fmtd  = nbr_dig_min + nbr_neg_sign;
                nbr_lead_char = 0u;
            }

            if (nbr_lead_char > 0) {                            /* If lead chars to fmt, ...                            */
                lead_char_0 = (lead_char == '0')                /* ... chk if lead char a '0' dig (see Note #3a2B).     */
                            ?  DEF_YES : DEF_NO;
            } else {
                lead_char_0 =  DEF_NO;
            }

        } else {                                                /* Else if nbr trunc'd, ...                             */
            fmt_invalid = DEF_YES;                              /* ... fmt invalid str (see Note #6c).                  */
        }
    }

    if (fmt_invalid != DEF_NO) {
        nbr_dig_fmtd = nbr_dig;
    }


/*$PAGE*/
                                                                /* ------------------- FMT NBR STR -------------------- */
    pstr_fmt += nbr_dig_fmtd;                                   /* Start fmt @ least-sig dig.                           */

    if (nul != DEF_NO) {                                        /* If NOT DISABLED, append NULL char (see Note #4).     */
       *pstr_fmt = (CPU_CHAR)'\0';
    }
    pstr_fmt--;


    for (i = 0u; i < nbr_dig_fmtd; i++) {                       /* Fmt str for desired nbr digs :                       */
        if (fmt_invalid == DEF_NO) {
            if ((nbr_fmt > 0) ||                                /* If fmt nbr > 0                               ...     */
                (i == 0u)) {                                    /* ... OR on one's  dig to fmt (see Note #3c1), ...     */
                                                                /* ... calc & fmt dig val;                      ...     */
                dig_val = (CPU_INT08U)(nbr_fmt % nbr_base);
                if (dig_val < 10u) {
                   *pstr_fmt-- = (CPU_CHAR)(dig_val + '0');
                } else {
                    if (lower_case !=  DEF_YES) {
                       *pstr_fmt--  = (CPU_CHAR)((dig_val - 10u) + 'A');
                    } else {
                       *pstr_fmt--  = (CPU_CHAR)((dig_val - 10u) + 'a');
                    }
                }

                nbr_fmt /= nbr_base;                            /* Shift to next more-sig dig.                          */

            } else if ((nbr_neg      == DEF_YES)  &&            /* ... else if nbr neg             AND          ...     */
                     (((lead_char_0  == DEF_NO )  &&            /* ... lead char NOT a '0' dig                  ...     */
                       (nbr_neg_fmtd == DEF_NO )) ||            /* ... but neg sign NOT yet fmt'd  OR           ...     */
                      ((lead_char_0  != DEF_NO )  &&            /* ... lead char is  a '0' dig                  ...     */
                       (i == (nbr_dig_fmtd - 1u))))) {          /* ... & on most-sig dig to fmt,                ...     */

               *pstr_fmt--   = '-';                             /* ... prepend neg sign (see Note #3b);         ...     */
                nbr_neg_fmtd = DEF_YES;

            } else if (lead_char != (CPU_CHAR)'\0') {           /* ... else if avail,                           ...     */
               *pstr_fmt-- = lead_char;                         /* ... fmt lead char.                                   */
            }

        } else {                                                /* Else fmt '?' for invalid str (see Note #7).          */
           *pstr_fmt-- = '?';
        }
    }


    if (fmt_invalid != DEF_NO) {                                /* Rtn NULL for invalid str fmt (see Notes #6a - #6e).  */
        return ((CPU_CHAR *)0);
    }


    return (pstr);                                              /* Rtn ptr to fmt'd str (see Note #6f).                 */
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                        Str_ParseNbr_Int32()
*
* Description : Parse 32-bit integer from string.
*
* Argument(s) : pstr            Pointer to string (see Notes #1 & #2a).
*
*               pstr_next       Optional pointer to a variable to ... :
*
*                                   (a) Return a pointer to first character following the integer string,
*                                           if NO error(s) [see Note #2a2B2];
*                                   (b) Return a pointer to 'pstr',
*                                           otherwise      (see Note #2a2A2).
*
*               nbr_base        Base of number to parse (see Notes #2a1B1 & #2a2B1).
*
*               nbr_signed      Indicates whether number to parse is signed :
*
*                                   DEF_NO                  Number is unsigned.
*                                   DEF_YES                 Number is   signed.
*
*               pnbr_neg        Pointer to a variable to return if the parsed (signed) number is negative :
*
*                                   DEF_NO                  Number is non-negative.
*                                   DEF_YES                 Number is     negative.
*
* Return(s)   : Parsed integer,      if integer parsed with NO overflow   (see Note #2a3A).
*
*               DEF_INT_32U_MAX_VAL, if integer parsed but     overflowed (see Note #2a3A1).
*
*               0,                   otherwise                            (see Note #2a3B).
*
* Caller(s)   : Str_ParseNbr_Int32U(),
*               Str_ParseNbr_Int32S().
*
* Note(s)     : (1) String buffer NOT modified.
*
*               (2) (a) IEEE Std 1003.1, 2004 Edition, Section 'strtol() : DESCRIPTION' states that "these
*                       functions shall convert the initial portion of the string pointed to by 'str' ('pstr') 
*                       to a type long ... representation" :
*
*                       (1) "First, they decompose the input string into three parts" :
*
*                           (A) "An initial, possibly empty, sequence of white-space characters [as specified
*                                by isspace()]."
*
*                               (1) "The subject sequence is defined as the longest initial subsequence of the
*                                    input string, starting with the first non-white-space character that is of
*                                    the expected form.  The subject sequence shall contain no characters if the
*                                    input string is empty or consists entirely of white-space characters."
*
*                           (B) (1) "A subject sequence interpreted as an integer represented in some radix
*                                    determined by the value of 'base' ('nbr_base')" :
*
*                                   (a) "If the value of 'base' ('nbr_base') is 0, the expected form of the 
*                                        subject sequence is that of a decimal constant, octal constant, or 
*                                        hexadecimal constant" :
*
*                                       (1) "A decimal constant begins with a non-zero digit, and consists of a
*                                            sequence of decimal digits."
*
*                                       (2) "An octal constant consists of the prefix '0' optionally followed by
*                                            a sequence of the digits '0' to '7' only."
*
*                                       (3) "A hexadecimal constant consists of the prefix '0x' or '0X' followed
*                                            by a sequence of the decimal digits and letters 'a' (or 'A') to 'f'
*                                            (or 'F') with values 10 to 15 respectively."
*
*                                   (b) "If the value of 'base' ('nbr_base') is between 2 and 36, the expected form 
*                                        of the subject sequence is a sequence of letters and digits representing 
*                                        an integer with the radix specified by 'base' ('nbr_base')" :
*
*                                       (1) (A) "The letters from 'a' (or 'A') to 'z' (or 'Z') inclusive are
*                                                ascribed the values 10 to 35"; ...
*                                           (B) "only letters whose ascribed values are less than that of base
*                                                are permitted."
*
*                                       (2) (A) "If the value of 'base' ('nbr_base') is 16, the characters '0x' or 
*                                               '0X' may optionally precede the sequence of letters and digits."
*
*                                           (B) Although NO specification states that "if the value of 'base' 
*                                               ('nbr_base') is" 8, the '0' character "may optionally precede 
*                                               the sequence of letters and digits"; it seems reasonable to 
*                                               allow the '0' character to be optionally parsed.
*$PAGE*
*                               (2) "A subject sequence .... may be preceded by a '+' or '-' sign."
*
*                                   (a) It does NOT seem reasonable to parse & convert a negative number
*                                       integer string into an unsigned integer.  However, a negative sign
*                                       for an unsigned integer will automatically be parsed as an invalid
*                                       character (see Note #2aC1).
*
*                           (C) (1) (a) "A final string of one or more unrecognized characters,"  ...
*                                   (b) "including the terminating null byte of the input string" ...
*                               (2) "other than a sign or a permissible letter or digit."
*
*                       (2) Second, "they shall attempt to convert the subject sequence to an integer" :
*
*                           (A) "If the subject sequence is empty or does not have the expected form" :
*
*                               (1) "no conversion is performed"; ...
*                               (2) "the value of 'str' ('pstr') is stored in the object pointed to by 'endptr' 
*                                    ('pstr_next'), provided that 'endptr' ('pstr_next') is not a null pointer."
*
*                           (B) "If the subject sequence has the expected form" :
*
*                               (1) (a) "and the value of 'base' ('nbr_base') is 0, the sequence of characters 
*                                        starting with the first digit shall be interpreted as an integer constant."
*
*                                   (b) "and the value of 'base' ('nbr_base') is between 2 and 36, it shall be 
*                                        used as the base for conversion, ascribing to each letter its value as 
*                                        given above" (see Note #2a1B1b1A).
*
*                               (2) "A pointer to the final string shall be stored in the object pointed to by
*                                   'endptr' ('pstr_next'), provided that 'endptr' ('pstr_next') is not a null 
*                                   pointer."
*
*                       (3) Lastly, IEEE Std 1003.1, 2004 Edition, Section 'strtol() : RETURN VALUE' states that :
*
*                           (A) "Upon successful completion, these functions shall return the converted value."
*                               (1) "If the correct value is outside the range of representable values, {LONG_MIN}
*                                    [or] {LONG_MAX} ... shall be returned."
*
*                           (B) "If no conversion could be performed, 0 shall be returned."
*
*                   (b) (1) IEEE Std 1003.1, 2004 Edition, Section 'strtoul() : ERRORS' states that "these functions
*                           shall fail if" :
*
*                           (A) "[EINVAL] - The value of 'base' ('nbr_base') is not supported."
*
*                           (B) "[ERANGE] - The value to be returned is not representable."
*
*                       (2) IEEE Std 1003.1, 2004 Edition, Section 'strtoul() : ERRORS' states that "these functions
*                           may fail if" :
*
*                           (A) "[EINVAL] - No conversion could be performed."
*$PAGE*
*               (3) Return integer value & next string pointer should be used to diagnose parse success or failure :
*
*                   (a) Valid parse string integer :
*
*                           pstr      = "     ABCDE xyz"
*                           nbr_base  = 16
*
*                           nbr       = 703710
*                           pstr_next = " xyz"
*
*
*                   (b) Invalid parse string integer :
*
*                           pstr      = "     ABCDE"
*                           nbr_base  = 10
*
*                           nbr       =  0
*                           pstr_next = pstr = "     ABCDE"
*
*
*                   (c) Valid hexadecimal parse string integer :
*
*                           pstr      = "     0xGABCDE"
*                           nbr_base  = 16
*
*                           nbr       =  0
*                           pstr_next = "xGABCDE"
*
*
*                   (d) Valid decimal parse string integer ('0x' prefix ignored
*                               following invalid hexadecimal characters) :
*
*                           pstr      = "     0xGABCDE"
*                           nbr_base  =  0
*
*                           nbr       =  0
*                           pstr_next = "xGABCDE"
*
*
*                   (e) Valid decimal parse string integer ('0'  prefix ignored
*                               following invalid octal       characters) :
*
*                           pstr      = "     0GABCDE"
*                           nbr_base  =  0
*
*                           nbr       =  0
*                           pstr_next = "GABCDE"
*
*
*                   (f) Parse string integer overflow :
*
*                           pstr      = "   12345678901234567890*123456"
*                           nbr_base  = 10
*
*                           nbr       = DEF_INT_32U_MAX_VAL
*                           pstr_next = "*123456"
*
*
*                   (g) Parse string integer underflow :
*
*                           pstr      = "  -12345678901234567890*123456"
*                           nbr_base  = 10
*
*                           nbr       = DEF_INT_32S_MIN_VAL
*                           pstr_next = "*123456"
*
*
*               (4) String parse terminates when :
*
*                   (a) Base passed an invalid base (see Note #2a1B1b).
*                       (1) No conversion performed; 0 returned.
*
*                   (b) (1) Parse string passed a NULL pointer OR empty integer sequence (see Note #2a2A).
*                           (A) No conversion performed; 0 returned.
*
*                       (2) Invalid parse string character found (see Note #2a1C).
*                           (A) Parsed integer returned.
*                           (B) 'pstr_next' points to invalid character.
*
*                       (3) Entire  parse string converted (see Note #2a2B).
*                           (A) Parsed integer returned.
*                           (B) 'pstr_next' points to terminating NULL character.
*
*               (5) Pointers to variables that return values MUST be initialized PRIOR to all other
*                   validation or function handling in case of any error(s).
*********************************************************************************************************
*/
/*$PAGE*/
static  CPU_INT32U  Str_ParseNbr_Int32 (const  CPU_CHAR      *pstr,
                                               CPU_CHAR     **pstr_next,
                                               CPU_INT08U     nbr_base,
                                               CPU_BOOLEAN    nbr_signed,
                                               CPU_BOOLEAN   *pnbr_neg)
{
    const  CPU_CHAR     *pstr_parse;
    const  CPU_CHAR     *pstr_parse_nbr;
           CPU_CHAR     *pstr_parse_unused;
           CPU_CHAR      parse_char;
           CPU_INT08U    parse_dig;
           CPU_INT32U    nbr;
           CPU_BOOLEAN   nbr_neg_unused;
           CPU_BOOLEAN   nbr_dig;
           CPU_BOOLEAN   nbr_alpha;
           CPU_BOOLEAN   nbr_hex;
           CPU_BOOLEAN   nbr_hex_lower;
           CPU_BOOLEAN   whitespace;
           CPU_BOOLEAN   neg;
           CPU_BOOLEAN   ovf;
           CPU_BOOLEAN   done;

                                                                /* --------------- VALIDATE PARSE ARGS ---------------- */
    if (pstr_next == (CPU_CHAR **) 0) {                         /* If NOT avail, ...                                    */
        pstr_next  = (CPU_CHAR **)&pstr_parse_unused;           /* ... re-cfg NULL rtn ptr to unused local var.         */
       (void)&pstr_parse_unused;                                /* Prevent possible 'variable unused' warning.          */
    }
   *pstr_next = (CPU_CHAR *)pstr;                               /* Init rtn str for err (see Note #5).                  */

    if (pnbr_neg == (CPU_BOOLEAN *) 0) {                        /* If NOT avail, ...                                    */
        pnbr_neg  = (CPU_BOOLEAN *)&nbr_neg_unused;             /* ... re-cfg NULL rtn ptr to unused local var.         */
       (void)&nbr_neg_unused;                                   /* Prevent possible 'variable unused' warning.          */
    }
   *pnbr_neg = DEF_NO;                                          /* Init nbr neg for err (see Note #5).                  */


    if (pstr == (CPU_CHAR *)0) {                                /* Rtn zero if str ptr NULL (see Note #4b1).            */
        return (0u);
    }
                                                                /* Rtn zero if invalid base (see Note #4a).             */
    if ((nbr_base == 1u) ||
        (nbr_base > 36u)) {
        return (0u);
    }


                                                                /* ------------- IGNORE PRECEDING CHAR(S) ------------- */
    pstr_parse = pstr;                                          /* Save ptr to init'l str for err (see Note #2a2A2).    */

    whitespace = ASCII_IsSpace(*pstr_parse);
    while (whitespace == DEF_YES) {                             /* Ignore initial white-space char(s) [see Note #2a1A]. */
        pstr_parse++;
        whitespace = ASCII_IsSpace(*pstr_parse);
    }

    switch (*pstr_parse) {
        case '+':                                               /* Ignore   pos sign (see Note #2a1B2).                 */
             pstr_parse++;
             neg = DEF_NO;
             break;


        case '-':                                               /* Validate neg sign (see Note #2a1B2a).                */
             if (nbr_signed == DEF_YES) {
                 pstr_parse++;
             }
             neg = DEF_YES;
             break;


        default:
             neg = DEF_NO;
             break;
    }


/*$PAGE*/
                                                                /* --------- IGNORE NBR BASE PRECEDING CHAR(S) -------- */
    pstr_parse_nbr = pstr_parse;                                /* Save ptr to str's nbr (see Note #2a1A1).             */

    switch (nbr_base) {
        case  0u:                                               /* Determine unspecified nbr base (see Notes #2a1B1a).  */
             if (*pstr_parse == '0') {                          /* If avail, ...                                        */
                  pstr_parse++;                                 /* ... adv past '0'  prefix (see Note #2a1B1b2).        */
                  switch (*pstr_parse) {
                      case 'x':                                 /* For '0x' prefix, ...                                 */
                      case 'X':
                           nbr_base   = 16u;                    /* ... set nbr base = 16    (see Note #2a1B1a3).        */
                           parse_char = (CPU_CHAR)(*(pstr_parse + 1));
                           nbr_hex    =  ASCII_IsDigHex(parse_char);
                           if (nbr_hex == DEF_YES) {            /* If next char is valid hex dig, ...                   */
                               pstr_parse++;                    /* ... adv past '0x' prefix (see Note #2a1B1b2A).       */
                           }
                           break;


                      default:                                  /* For '0'  prefix, ...                                 */
                           nbr_base =  8u;                      /* ... set nbr base =  8    (see Note #2a1B1a2).        */
                           break;
                  }

             } else {                                           /* For non-'0' prefix, ...                              */
                 nbr_base = 10u;                                /* ... set nbr base = 10    (see Note #2a1B1a1).        */
             }
             break;


        case  8u:                                               /* See Note #2a1B1a2.                                   */
             if (*pstr_parse == '0') {                          /* If avail, ...                                        */
                  pstr_parse++;                                 /* ... adv past '0'  prefix (see Note #2a1B1b2B).       */
             }
             break;


        case 16u:                                               /* See Note #2a1B1a3.                                   */
             if (*pstr_parse == '0') {                          /* If avail, ...                                        */
                  pstr_parse++;                                 /* ... adv past '0'  prefix (see Note #2a1B1b2).        */
                  switch (*pstr_parse) {
                      case 'x':
                      case 'X':
                           parse_char = (CPU_CHAR)(*(pstr_parse + 1));
                           nbr_hex    =  ASCII_IsDigHex(parse_char);
                           if (nbr_hex == DEF_YES) {            /* If next char is valid hex dig, ...                   */
                               pstr_parse++;                    /* ... adv past '0x' prefix (see Note #2a1B1b2A).       */
                           }
                           break;


                      default:
                           break;
                  }
             }
             break;


        default:                                                /* See Note #2a1B1b.                                    */
             break;
    }


/*$PAGE*/
                                                                /* ------------------ PARSE INT STR ------------------- */
    nbr  = 0u;
    ovf  = DEF_NO;
    done = DEF_NO;

    while (done == DEF_NO) {                                    /* Parse str for desired nbr base digs (see Note #2a2). */
        parse_char = (CPU_CHAR)*pstr_parse;
        nbr_alpha  =  ASCII_IsAlphaNum(parse_char);
        if (nbr_alpha == DEF_YES) {                             /* If valid alpha num nbr dig avail, ...                */
                                                                /* ... convert parse char into nbr dig.                 */
            nbr_dig = ASCII_IsDig(parse_char);
            if (nbr_dig == DEF_YES) {
                parse_dig = (CPU_INT08U)(parse_char - '0');
            } else {
                nbr_hex_lower = ASCII_IsLower(parse_char);
                if (nbr_hex_lower == DEF_YES) {
                    parse_dig = (CPU_INT08U)((parse_char - 'a') + 10u);
                } else {
                    parse_dig = (CPU_INT08U)((parse_char - 'A') + 10u);
                }
            }

            if (parse_dig < nbr_base) {                         /* If parse char valid for nbr base ...                 */
                if (ovf == DEF_NO) {                            /* ... & nbr NOT yet ovf'd,         ...                 */
                    if (nbr <= Str_MultOvfThTbl_Int32U[nbr_base]) {
                                                                /* ... merge parse char dig into nbr.                   */
                        nbr *= nbr_base;
                        nbr += parse_dig;
                        if (nbr < parse_dig) {
                            ovf = DEF_YES;
                        }
                    } else {
                        ovf = DEF_YES;
                    }
                }
                pstr_parse++;

            } else {                                            /* Invalid         char parsed (see Note #2a1C1a).      */
                done = DEF_YES;
            }

        } else {                                                /* Invalid OR NULL char parsed (see Note #2a1C1).       */
            done = DEF_YES;
        }
    }

    if (ovf == DEF_YES) {                                       /* If nbr ovf'd, ...                                    */
        nbr  = DEF_INT_32U_MAX_VAL;                             /* ... rtn max int val (see Note #2a3A1).               */
    }


    if (pstr_parse !=             pstr_parse_nbr) {             /* If final parse str != init'l parse nbr str,       .. */
       *pstr_next   = (CPU_CHAR *)pstr_parse;                   /* .. rtn   parse str's next char (see Note #2a2B2); .. */
    } else {
       *pstr_next   = (CPU_CHAR *)pstr;                         /* .. else rtn initial parse str  (see Note #2a2A2).    */
    }

   *pnbr_neg = neg;                                             /* Rtn neg nbr status.                                  */


    return (nbr);
}

