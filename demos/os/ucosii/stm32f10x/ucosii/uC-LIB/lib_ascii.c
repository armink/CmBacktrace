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
*                                     ASCII CHARACTER OPERATIONS
*
* Filename      : lib_ascii.c
* Version       : V1.37.01
* Programmer(s) : BAN
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
*
*                 (2) (a) ECMA-6 '7-Bit coded Character Set' (6th edition), which corresponds to the
*                         3rd edition of ISO 646, specifies several versions of a 7-bit character set :
*
*                         (1) THE GENERAL VERSION, which allows characters at 0x23 and 0x24 to be given a
*                             set alternate form and allows the characters 0x40, 0x5B, 0x5D, 0x60, 0x7B &
*                             0x7D to be assigned a "unique graphic character" or to be declared as unused.
*                             All other characters are explicitly specified.
*
*                         (2) THE INTERNATIONAL REFERENCE VERSION, which explicitly specifies all characters
*                             in the 7-bit character set.
*
*                         (3) NATIONAL & APPLICATION-ORIENTED VERSIONS, which may be derived from the
*                             standard in specified ways.
*
*                     (b) The character set represented in this file reproduces the Internation Reference
*                         Version.  This is identical to the 7-bit character set which occupies Unicode
*                         characters 0x0000 through 0x007F.  The character names are taken from v5.0 of the
*                         Unicode specification, with certain abbreviations so that the resulting #define
*                         names will not violate ANSI C naming restriction :
*
*                         (1) For the Latin capital & lowercase letters, the name components 'LETTER_CAPITAL'
*                             & 'LETTER_SMALL' are replaced by 'UPPER' & 'LOWER', respectively.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#define    MICRIUM_SOURCE
#define    LIB_ASCII_MODULE
#include  <lib_ascii.h>


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
*                                           ASCII_IsAlpha()
*
* Description : Determine whether a character is an alphabetic character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     an alphabetic character.
*
*               DEF_NO,	 if character is NOT an alphabetic character.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) ISO/IEC 9899:TC2, Section 7.4.1.2.(2) states that "isalpha() returns true only for the
*                   characters for which isupper() or islower() is true".
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsAlpha (CPU_CHAR  c)
{
    CPU_BOOLEAN  alpha;


    alpha = ASCII_IS_ALPHA(c);

    return (alpha);
}


/*
*********************************************************************************************************
*                                         ASCII_IsAlphaNum()
*
* Description : Determine whether a character is an alphanumeric character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     an alphanumeric character.
*
*               DEF_NO,	 if character is NOT an alphanumeric character.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) ISO/IEC 9899:TC2, Section 7.4.1.1.(2) states that "isalnum() ... tests for any character
*                   for which isalpha() or isdigit() is true".
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsAlphaNum (CPU_CHAR  c)
{
    CPU_BOOLEAN  alpha_num;


    alpha_num = ASCII_IS_ALPHA_NUM(c);

    return (alpha_num);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                           ASCII_IsLower()
*
* Description : Determine whether a character is a lowercase alphabetic character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     a lowercase alphabetic character.
*
*               DEF_NO,	 if character is NOT a lowercase alphabetic character.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) ISO/IEC 9899:TC2, Section 7.4.1.7.(2)  states that "islower() returns true only for
*                   the lowercase letters".
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsLower (CPU_CHAR  c)
{
    CPU_BOOLEAN  lower;


    lower = ASCII_IS_LOWER(c);

    return (lower);
}


/*
*********************************************************************************************************
*                                           ASCII_IsUpper()
*
* Description : Determine whether a character is an uppercase alphabetic character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     an uppercase alphabetic character.
*
*               DEF_NO,	 if character is NOT an uppercase alphabetic character.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) ISO/IEC 9899:TC2, Section 7.4.1.11.(2) states that "isupper() returns true only for
*                   the uppercase letters".
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsUpper (CPU_CHAR  c)
{
    CPU_BOOLEAN  upper;


    upper = ASCII_IS_UPPER(c);

    return (upper);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                            ASCII_IsDig()
*
* Description : Determine whether a character is a decimal-digit character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     a decimal-digit character.
*
*               DEF_NO,	 if character is NOT a decimal-digit character.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) ISO/IEC 9899:TC2, Section 7.4.1.5.(2)  states that "isdigit()  ... tests for any
*                   decimal-digit character".
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsDig (CPU_CHAR  c)
{
    CPU_BOOLEAN  dig;


    dig = ASCII_IS_DIG(c);

    return (dig);
}


/*
*********************************************************************************************************
*                                          ASCII_IsDigOct()
*
* Description : Determine whether a character is an octal-digit character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     an octal-digit character.
*
*               DEF_NO,	 if character is NOT an octal-digit character.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsDigOct (CPU_CHAR  c)
{
    CPU_BOOLEAN  dig_oct;


    dig_oct = ASCII_IS_DIG_OCT(c);

    return (dig_oct);
}


/*
*********************************************************************************************************
*                                          ASCII_IsDigHex()
*
* Description : Determine whether a character is a hexadecimal-digit character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     a hexadecimal-digit character.
*
*               DEF_NO,	 if character is NOT a hexadecimal-digit character.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) ISO/IEC 9899:TC2, Section 7.4.1.12.(2) states that "isxdigit() ... tests for any
*                   hexadecimal-digit character".
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsDigHex (CPU_CHAR  c)
{
    CPU_BOOLEAN  dig_hex;


    dig_hex = ASCII_IS_DIG_HEX(c);

    return (dig_hex);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                           ASCII_IsBlank()
*
* Description : Determine whether a character is a standard blank character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     a standard blank character.
*
*               DEF_NO,	 if character is NOT a standard blank character.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) ISO/IEC 9899:TC2, Section 7.4.1.3.(2) states that "isblank() returns true only for
*                       the standard blank characters".
*
*                   (b) ISO/IEC 9899:TC2, Section 7.4.1.3.(2) defines "the standard blank characters" as
*                       the "space (' '), and horizontal tab ('\t')".
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsBlank (CPU_CHAR  c)
{
    CPU_BOOLEAN  blank;


    blank = ASCII_IS_BLANK(c);

    return (blank);
}


/*
*********************************************************************************************************
*                                           ASCII_IsSpace()
*
* Description : Determine whether a character is a white-space character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     a white-space character.
*
*               DEF_NO,	 if character is NOT a white-space character.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) ISO/IEC 9899:TC2, Section 7.4.1.10.(2) states that "isspace() returns true only
*                       for the standard white-space characters".
*
*                   (b) ISO/IEC 9899:TC2, Section 7.4.1.10.(2) defines "the standard white-space characters"
*                       as the "space (' '), form feed ('\f'), new-line ('\n'), carriage return ('\r'),
*                       horizontal tab ('\t'), and vertical tab ('\v')".
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsSpace (CPU_CHAR  c)
{
    CPU_BOOLEAN  space;


    space = ASCII_IS_SPACE(c);

    return (space);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                           ASCII_IsPrint()
*
* Description : Determine whether a character is a printing character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     a printing character.
*
*               DEF_NO,	 if character is NOT a printing character.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) ISO/IEC 9899:TC2, Section 7.4.1.8.(2) states that "isprint() ... tests for any
*                       printing character including space (' ')".
*
*                   (b) ISO/IEC 9899:TC2, Section 7.4.(3), Note 169, states that in "the seven-bit US
*                       ASCII character set, the printing characters are those whose values lie from
*                       0x20 (space) through 0x7E (tilde)".
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsPrint (CPU_CHAR  c)
{
    CPU_BOOLEAN  print;


    print = ASCII_IS_PRINT(c);

    return (print);
}


/*
*********************************************************************************************************
*                                           ASCII_IsGraph()
*
* Description : Determine whether a character is any printing character except a space character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     a graphic character.
*
*               DEF_NO,	 if character is NOT a graphic character.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) ISO/IEC 9899:TC2, Section 7.4.1.6.(2) states that "isgraph() ... tests for any
*                       printing character except space (' ')".
*
*                   (b) ISO/IEC 9899:TC2, Section 7.4.(3), Note 169, states that in "the seven-bit US
*                       ASCII character set, the printing characters are those whose values lie from
*                       0x20 (space) through 0x7E (tilde)".
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsGraph (CPU_CHAR  c)
{
    CPU_BOOLEAN  graph;


    graph = ASCII_IS_GRAPH(c);

    return (graph);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                           ASCII_IsPunct()
*
* Description : Determine whether a character is a punctuation character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     a punctuation character.
*
*               DEF_NO,	 if character is NOT a punctuation character.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) ISO/IEC 9899:TC2, Section 7.4.1.9.(2) states that "ispunct() returns true for every
*                   printing character for which neither isspace() nor isalnum() is true".
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsPunct (CPU_CHAR  c)
{
    CPU_BOOLEAN  punct;


    punct = ASCII_IS_PUNCT(c);

    return (punct);
}


/*
*********************************************************************************************************
*                                           ASCII_IsCtrl()
*
* Description : Determine whether a character is a control character.
*
* Argument(s) : c           Character to examine.
*
* Return(s)   : DEF_YES, if character is     a control character.
*
*               DEF_NO,	 if character is NOT a control character.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) ISO/IEC 9899:TC2, Section 7.4.1.4.(2) states that "iscntrl() ... tests for any
*                       control character".
*
*                   (b) ISO/IEC 9899:TC2, Section 7.4.(3), Note 169, states that in "the seven-bit US
*                       ASCII character set, ... the control characters are those whose values lie from
*                       0 (NUL) through 0x1F (US), and the character 0x7F (DEL)".
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsCtrl (CPU_CHAR  c)
{
    CPU_BOOLEAN  ctrl;


    ctrl = ASCII_IS_CTRL(c);

    return (ctrl);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                           ASCII_ToLower()
*
* Description : Convert uppercase alphabetic character to its corresponding lowercase alphabetic character.
*
* Argument(s) : c           Character to convert.
*
* Return(s)   : Lowercase equivalent of 'c', if character 'c' is an uppercase character (see Note #1b1).
*
*               Character 'c',               otherwise                                  (see Note #1b2).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) ISO/IEC 9899:TC2, Section 7.4.2.1.(2) states that "tolower() ... converts an
*                       uppercase letter to a corresponding lowercase letter".
*
*                   (b) ISO/IEC 9899:TC2, Section 7.4.2.1.(3) states that :
*
*                       (1) (A) "if the argument is a character for which isupper() is true and there are
*                                one or more corresponding characters ... for which islower() is true," ...
*                           (B) "tolower() ... returns one of the corresponding characters;" ...
*
*                       (2) "otherwise, the argument is returned unchanged."
*********************************************************************************************************
*/

CPU_CHAR  ASCII_ToLower (CPU_CHAR  c)
{
    CPU_CHAR  lower;


    lower = ASCII_TO_LOWER(c);

    return (lower);
}


/*
*********************************************************************************************************
*                                           ASCII_ToUpper()
*
* Description : Convert lowercase alphabetic character to its corresponding uppercase alphabetic character.
*
* Argument(s) : c           Character to convert.
*
* Return(s)   : Uppercase equivalent of 'c', if character 'c' is a lowercase character (see Note #1b1).
*
*               Character 'c',               otherwise                                 (see Note #1b2).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) ISO/IEC 9899:TC2, Section 7.4.2.2.(2) states that "toupper() ... converts a
*                       lowercase letter to a corresponding uppercase letter".
*
*                   (b) ISO/IEC 9899:TC2, Section 7.4.2.2.(3) states that :
*
*                       (1) (A) "if the argument is a character for which islower() is true and there are
*                                one or more corresponding characters ... for which isupper() is true," ...
*                           (B) "toupper() ... returns one of the corresponding characters;" ...
*
*                       (2) "otherwise, the argument is returned unchanged."
*********************************************************************************************************
*/

CPU_CHAR  ASCII_ToUpper (CPU_CHAR  c)
{
    CPU_CHAR  upper;


    upper = ASCII_TO_UPPER(c);

    return (upper);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                             ASCII_Cmp()
*
* Description : Determine if two characters are identical (case-insensitive).
*
* Argument(s) : c1          First  character.
*
*               c2          Second character.
*
* Return(s)   : DEF_YES, if the characters are     identical.
*
*               DEF_NO,  if the characters are NOT identical.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_Cmp (CPU_CHAR  c1,
                        CPU_CHAR  c2)
{
    CPU_CHAR     c1_upper;
    CPU_CHAR     c2_upper;
    CPU_BOOLEAN  cmp;


    c1_upper =  ASCII_ToUpper(c1);
    c2_upper =  ASCII_ToUpper(c2);
    cmp      = (c1_upper == c2_upper) ? (DEF_YES) : (DEF_NO);

    return (cmp);
}

