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
* Filename      : lib_ascii.h
* Version       : V1.37.01
* Programmer(s) : BAN
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
*                                               MODULE
*
* Note(s) : (1) This ASCII library header file is protected from multiple pre-processor inclusion through 
*               use of the ASCII library module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  LIB_ASCII_MODULE_PRESENT                               /* See Note #1.                                         */
#define  LIB_ASCII_MODULE_PRESENT


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
#include  <lib_def.h>


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   LIB_ASCII_MODULE
#define  LIB_ASCII_EXT
#else
#define  LIB_ASCII_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         ASCII CHARACTER DEFINES
*********************************************************************************************************
*/

                                                                /* -------------------- C0 CONTROLS ------------------- */
#define  ASCII_CHAR_NULL                                0x00    /* '\0'                                                 */
#define  ASCII_CHAR_START_OF_HEADING                    0x01
#define  ASCII_CHAR_START_OF_TEXT                       0x02
#define  ASCII_CHAR_END_OF_TEXT                         0x03
#define  ASCII_CHAR_END_OF_TRANSMISSION                 0x04
#define  ASCII_CHAR_ENQUIRY                             0x05
#define  ASCII_CHAR_ACKNOWLEDGE                         0x06
#define  ASCII_CHAR_BELL                                0x07    /* '\a'                                                 */
#define  ASCII_CHAR_BACKSPACE                           0x08    /* '\b'                                                 */
#define  ASCII_CHAR_CHARACTER_TABULATION                0x09    /* '\t'                                                 */
#define  ASCII_CHAR_LINE_FEED                           0x0A    /* '\n'                                                 */
#define  ASCII_CHAR_LINE_TABULATION                     0x0B    /* '\v'                                                 */
#define  ASCII_CHAR_FORM_FEED                           0x0C    /* '\f'                                                 */
#define  ASCII_CHAR_CARRIAGE_RETURN                     0x0D    /* '\r'                                                 */
#define  ASCII_CHAR_SHIFT_OUT                           0x0E
#define  ASCII_CHAR_SHIFT_IN                            0x0F
#define  ASCII_CHAR_DATA_LINK_ESCAPE                    0x10
#define  ASCII_CHAR_DEVICE_CONTROL_ONE                  0x11
#define  ASCII_CHAR_DEVICE_CONTROL_TWO                  0x12
#define  ASCII_CHAR_DEVICE_CONTROL_THREE                0x13
#define  ASCII_CHAR_DEVICE_CONTROL_FOUR                 0x14
#define  ASCII_CHAR_NEGATIVE_ACKNOWLEDGE                0x15
#define  ASCII_CHAR_SYNCHRONOUS_IDLE                    0x16
#define  ASCII_CHAR_END_OF_TRANSMISSION_BLOCK           0x17
#define  ASCII_CHAR_CANCEL                              0x18
#define  ASCII_CHAR_END_OF_MEDIUM                       0x19
#define  ASCII_CHAR_SUBSITUTE                           0x1A
#define  ASCII_CHAR_ESCAPE                              0x1B
#define  ASCII_CHAR_INFO_SEPARATOR_FOUR                 0x1C
#define  ASCII_CHAR_INFO_SEPARATOR_THREE                0x1D
#define  ASCII_CHAR_INFO_SEPARATOR_TWO                  0x1E
#define  ASCII_CHAR_INFO_SEPARATOR_ONE                  0x1F

#define  ASCII_CHAR_NUL                                 ASCII_CHAR_NULL
#define  ASCII_CHAR_SOH                                 ASCII_CHAR_START_OF_HEADING
#define  ASCII_CHAR_START_HEADING                       ASCII_CHAR_START_OF_HEADING
#define  ASCII_CHAR_STX                                 ASCII_CHAR_START_OF_TEXT
#define  ASCII_CHAR_START_TEXT                          ASCII_CHAR_START_OF_TEXT
#define  ASCII_CHAR_ETX                                 ASCII_CHAR_END_OF_TEXT
#define  ASCII_CHAR_END_TEXT                            ASCII_CHAR_END_OF_TEXT
#define  ASCII_CHAR_EOT                                 ASCII_CHAR_END_OF_TRANSMISSION
#define  ASCII_CHAR_END_TRANSMISSION                    ASCII_CHAR_END_OF_TRANSMISSION
#define  ASCII_CHAR_ENQ                                 ASCII_CHAR_ENQUIRY
#define  ASCII_CHAR_ACK                                 ASCII_CHAR_ACKNOWLEDGE
#define  ASCII_CHAR_BEL                                 ASCII_CHAR_BELL
#define  ASCII_CHAR_BS                                  ASCII_CHAR_BACKSPACE
#define  ASCII_CHAR_HT                                  ASCII_CHAR_CHARACTER_TABULATION
#define  ASCII_CHAR_TAB                                 ASCII_CHAR_CHARACTER_TABULATION
#define  ASCII_CHAR_LF                                  ASCII_CHAR_LINE_FEED
#define  ASCII_CHAR_VT                                  ASCII_CHAR_LINE_TABULATION
#define  ASCII_CHAR_FF                                  ASCII_CHAR_FORM_FEED
#define  ASCII_CHAR_CR                                  ASCII_CHAR_CARRIAGE_RETURN
#define  ASCII_CHAR_SO                                  ASCII_CHAR_SHIFT_OUT
#define  ASCII_CHAR_SI                                  ASCII_CHAR_SHIFT_IN
#define  ASCII_CHAR_DLE                                 ASCII_CHAR_DATA_LINK_ESCAPE
#define  ASCII_CHAR_DC1                                 ASCII_CHAR_DEVICE_CONTROL_ONE
#define  ASCII_CHAR_DC2                                 ASCII_CHAR_DEVICE_CONTROL_TWO
#define  ASCII_CHAR_DC3                                 ASCII_CHAR_DEVICE_CONTROL_THREE
#define  ASCII_CHAR_DC4                                 ASCII_CHAR_DEVICE_CONTROL_FOUR
#define  ASCII_CHAR_DEV_CTRL_ONE                        ASCII_CHAR_DEVICE_CONTROL_ONE
#define  ASCII_CHAR_DEV_CTRL_TWO                        ASCII_CHAR_DEVICE_CONTROL_TWO
#define  ASCII_CHAR_DEV_CTRL_THREE                      ASCII_CHAR_DEVICE_CONTROL_THREE
#define  ASCII_CHAR_DEV_CTRL_FOUR                       ASCII_CHAR_DEVICE_CONTROL_FOUR
#define  ASCII_CHAR_NAK                                 ASCII_CHAR_NEGATIVE_ACKNOWLEDGE
#define  ASCII_CHAR_NEG_ACK                             ASCII_CHAR_NEGATIVE_ACKNOWLEDGE
#define  ASCII_CHAR_SYN                                 ASCII_CHAR_SYNCHRONOUS_IDLE
#define  ASCII_CHAR_SYNC_IDLE                           ASCII_CHAR_SYNCHRONOUS_IDLE
#define  ASCII_CHAR_ETB                                 ASCII_CHAR_END_OF_TRANSMISSION_BLOCK
#define  ASCII_CHAR_END_TRANSMISSION_BLK                ASCII_CHAR_END_OF_TRANSMISSION_BLOCK
#define  ASCII_CHAR_CAN                                 ASCII_CHAR_CANCEL
#define  ASCII_CHAR_EM                                  ASCII_CHAR_END_OF_MEDIUM
#define  ASCII_CHAR_END_MEDIUM                          ASCII_CHAR_END_OF_MEDIUM
#define  ASCII_CHAR_SUB                                 ASCII_CHAR_SUBSITUTE
#define  ASCII_CHAR_ESC                                 ASCII_CHAR_ESCAPE
#define  ASCII_CHAR_IS1                                 ASCII_CHAR_INFO_SEPARATOR_ONE
#define  ASCII_CHAR_IS2                                 ASCII_CHAR_INFO_SEPARATOR_TWO
#define  ASCII_CHAR_IS3                                 ASCII_CHAR_INFO_SEPARATOR_THREE
#define  ASCII_CHAR_IS4                                 ASCII_CHAR_INFO_SEPARATOR_FOUR


/*$PAGE*/
                                                                /* ------------ ASCII PUNCTUATION & SYMBOLS ----------- */
#define  ASCII_CHAR_SPACE                               0x20    /* ' '                                                  */
#define  ASCII_CHAR_EXCLAMATION_MARK                    0x21    /* '!'                                                  */
#define  ASCII_CHAR_QUOTATION_MARK                      0x22    /* '\"'                                                 */
#define  ASCII_CHAR_NUMBER_SIGN                         0x23    /* '#'                                                  */
#define  ASCII_CHAR_DOLLAR_SIGN                         0x24    /* '$'                                                  */
#define  ASCII_CHAR_PERCENTAGE_SIGN                     0x25    /* '%'                                                  */
#define  ASCII_CHAR_AMPERSAND                           0x26    /* '&'                                                  */
#define  ASCII_CHAR_APOSTROPHE                          0x27    /* '\''                                                 */
#define  ASCII_CHAR_LEFT_PARENTHESIS                    0x28    /* '('                                                  */
#define  ASCII_CHAR_RIGHT_PARENTHESIS                   0x29    /* ')'                                                  */
#define  ASCII_CHAR_ASTERISK                            0x2A    /* '*'                                                  */
#define  ASCII_CHAR_PLUS_SIGN                           0x2B    /* '+'                                                  */
#define  ASCII_CHAR_COMMA                               0x2C    /* ','                                                  */
#define  ASCII_CHAR_HYPHEN_MINUS                        0x2D    /* '-'                                                  */
#define  ASCII_CHAR_FULL_STOP                           0x2E    /* '.'                                                  */
#define  ASCII_CHAR_SOLIDUS                             0x2F    /* '/'                                                  */

#define  ASCII_CHAR_PAREN_LEFT                          ASCII_CHAR_LEFT_PARENTHESIS
#define  ASCII_CHAR_PAREN_RIGHT                         ASCII_CHAR_RIGHT_PARENTHESIS


                                                                /* ------------------- ASCII DIGITS ------------------- */
#define  ASCII_CHAR_DIGIT_ZERO                          0x30    /* '0'                                                  */
#define  ASCII_CHAR_DIGIT_ONE                           0x31    /* '1'                                                  */
#define  ASCII_CHAR_DIGIT_TWO                           0x32    /* '2'                                                  */
#define  ASCII_CHAR_DIGIT_THREE                         0x33    /* '3'                                                  */
#define  ASCII_CHAR_DIGIT_FOUR                          0x34    /* '4'                                                  */
#define  ASCII_CHAR_DIGIT_FIVE                          0x35    /* '5'                                                  */
#define  ASCII_CHAR_DIGIT_SIX                           0x36    /* '6'                                                  */
#define  ASCII_CHAR_DIGIT_SEVEN                         0x37    /* '7'                                                  */
#define  ASCII_CHAR_DIGIT_EIGHT                         0x38    /* '8'                                                  */
#define  ASCII_CHAR_DIGIT_NINE                          0x39    /* '9'                                                  */

#define  ASCII_CHAR_DIG_ZERO                            ASCII_CHAR_DIGIT_ZERO
#define  ASCII_CHAR_DIG_ONE                             ASCII_CHAR_DIGIT_ONE
#define  ASCII_CHAR_DIG_TWO                             ASCII_CHAR_DIGIT_TWO
#define  ASCII_CHAR_DIG_THREE                           ASCII_CHAR_DIGIT_THREE
#define  ASCII_CHAR_DIG_FOUR                            ASCII_CHAR_DIGIT_FOUR
#define  ASCII_CHAR_DIG_FIVE                            ASCII_CHAR_DIGIT_FIVE
#define  ASCII_CHAR_DIG_SIX                             ASCII_CHAR_DIGIT_SIX
#define  ASCII_CHAR_DIG_SEVEN                           ASCII_CHAR_DIGIT_SEVEN
#define  ASCII_CHAR_DIG_EIGHT                           ASCII_CHAR_DIGIT_EIGHT
#define  ASCII_CHAR_DIG_NINE                            ASCII_CHAR_DIGIT_NINE


                                                                /* ------------ ASCII PUNCTUATION & SYMBOLS ----------- */
#define  ASCII_CHAR_COLON                               0x3A    /* ':'                                                  */
#define  ASCII_CHAR_SEMICOLON                           0x3B    /* ';'                                                  */
#define  ASCII_CHAR_LESS_THAN_SIGN                      0x3C    /* '<'                                                  */
#define  ASCII_CHAR_EQUALS_SIGN                         0x3D    /* '='                                                  */
#define  ASCII_CHAR_GREATER_THAN_SIGN                   0x3E    /* '>'                                                  */
#define  ASCII_CHAR_QUESTION_MARK                       0x3F    /* '\?'                                                 */
#define  ASCII_CHAR_COMMERCIAL_AT                       0x40    /* '@'                                                  */

#define  ASCII_CHAR_AT_SIGN                             ASCII_CHAR_COMMERCIAL_AT


/*$PAGE*/
                                                                /* ------------- UPPERCASE LATIN ALPHABET ------------- */
#define  ASCII_CHAR_LATIN_UPPER_A                       0x41    /* 'A'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_B                       0x42    /* 'B'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_C                       0x43    /* 'C'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_D                       0x44    /* 'D'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_E                       0x45    /* 'E'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_F                       0x46    /* 'F'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_G                       0x47    /* 'G'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_H                       0x48    /* 'H'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_I                       0x49    /* 'I'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_J                       0x4A    /* 'J'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_K                       0x4B    /* 'K'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_L                       0x4C    /* 'L'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_M                       0x4D    /* 'M'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_N                       0x4E    /* 'N'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_O                       0x4F    /* 'O'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_P                       0x50    /* 'P'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_Q                       0x51    /* 'Q'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_R                       0x52    /* 'R'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_S                       0x53    /* 'S'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_T                       0x54    /* 'T'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_U                       0x55    /* 'U'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_V                       0x56    /* 'V'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_W                       0x57    /* 'W'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_X                       0x58    /* 'X'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_Y                       0x59    /* 'Y'                                                  */
#define  ASCII_CHAR_LATIN_UPPER_Z                       0x5A    /* 'Z'                                                  */


                                                                /* ------------ ASCII PUNCTUATION & SYMBOLS ----------- */
#define  ASCII_CHAR_LEFT_SQUARE_BRACKET                 0x5B    /* '['                                                  */
#define  ASCII_CHAR_REVERSE_SOLIDUS                     0x5C    /* '\\'                                                 */
#define  ASCII_CHAR_RIGHT_SQUARE_BRACKET                0x5D    /* ']'                                                  */
#define  ASCII_CHAR_CIRCUMFLEX_ACCENT                   0x5E    /* '^'                                                  */
#define  ASCII_CHAR_LOW_LINE                            0x5F    /* '_'                                                  */
#define  ASCII_CHAR_GRAVE_ACCENT                        0x60    /* '`'                                                  */

#define  ASCII_CHAR_BRACKET_SQUARE_LEFT                 ASCII_CHAR_LEFT_SQUARE_BRACKET
#define  ASCII_CHAR_BRACKET_SQUARE_RIGHT                ASCII_CHAR_RIGHT_SQUARE_BRACKET


                                                                /* ------------- LOWERCASE LATIN ALPHABET ------------- */
#define  ASCII_CHAR_LATIN_LOWER_A                       0x61    /* 'a'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_B                       0x62    /* 'b'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_C                       0x63    /* 'c'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_D                       0x64    /* 'd'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_E                       0x65    /* 'e'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_F                       0x66    /* 'f'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_G                       0x67    /* 'g'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_H                       0x68    /* 'h'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_I                       0x69    /* 'i'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_J                       0x6A    /* 'j'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_K                       0x6B    /* 'k'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_L                       0x6C    /* 'l'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_M                       0x6D    /* 'm'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_N                       0x6E    /* 'n'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_O                       0x6F    /* 'o'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_P                       0x70    /* 'p'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_Q                       0x71    /* 'q'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_R                       0x72    /* 'r'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_S                       0x73    /* 's'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_T                       0x74    /* 't'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_U                       0x75    /* 'u'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_V                       0x76    /* 'v'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_W                       0x77    /* 'w'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_X                       0x78    /* 'x'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_Y                       0x79    /* 'y'                                                  */
#define  ASCII_CHAR_LATIN_LOWER_Z                       0x7A    /* 'z'                                                  */


                                                                /* ------------ ASCII PUNCTUATION & SYMBOLS ----------- */
#define  ASCII_CHAR_LEFT_CURLY_BRACKET                  0x7B    /* '{'                                                  */
#define  ASCII_CHAR_VERTICAL_LINE                       0x7C    /* '|'                                                  */
#define  ASCII_CHAR_RIGHT_CURLY_BRACKET                 0x7D    /* '}'                                                  */
#define  ASCII_CHAR_TILDE                               0x7E    /* '~'                                                  */

#define  ASCII_CHAR_BRACKET_CURLY_LEFT                  ASCII_CHAR_LEFT_CURLY_BRACKET
#define  ASCII_CHAR_BRACKET_CURLY_RIGHT                 ASCII_CHAR_RIGHT_CURLY_BRACKET


                                                                /* ---------------- CONTROL CHARACTERS ---------------- */
#define  ASCII_CHAR_DELETE                              0x7F

#define  ASCII_CHAR_DEL                                 ASCII_CHAR_DELETE


/*$PAGE*/
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
*                               ASCII CHARACTER CLASSIFICATION MACRO's
*
* Note(s) : (1) ISO/IEC 9899:TC2, Section 7.4.1.(1) states that "character classification functions ...
*               return nonzero (true) if and only if the value of the argument 'c' conforms to ... the
*               description of the function."
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           ASCII_IS_DIG()
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

#define  ASCII_IS_DIG(c)               ((((c) >= ASCII_CHAR_DIG_ZERO) && ((c) <= ASCII_CHAR_DIG_NINE)) ? (DEF_YES) : (DEF_NO))


/*
*********************************************************************************************************
*                                         ASCII_IS_DIG_OCT()
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

#define  ASCII_IS_DIG_OCT(c)          ((((c) >= ASCII_CHAR_DIG_ZERO) && ((c) <= ASCII_CHAR_DIG_SEVEN)) ? (DEF_YES) : (DEF_NO))


/*
*********************************************************************************************************
*                                         ASCII_IS_DIG_HEX()
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

#define  ASCII_IS_DIG_HEX(c)          (((((c) >= ASCII_CHAR_DIG_ZERO     ) && ((c) <= ASCII_CHAR_DIG_NINE     )) || \
                                        (((c) >= ASCII_CHAR_LATIN_UPPER_A) && ((c) <= ASCII_CHAR_LATIN_UPPER_F)) || \
                                        (((c) >= ASCII_CHAR_LATIN_LOWER_A) && ((c) <= ASCII_CHAR_LATIN_LOWER_F))) ? (DEF_YES) : (DEF_NO))


/*$PAGE*/
/*
*********************************************************************************************************
*                                          ASCII_IS_LOWER()
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

#define  ASCII_IS_LOWER(c)             ((((c) >= ASCII_CHAR_LATIN_LOWER_A) && ((c) <= ASCII_CHAR_LATIN_LOWER_Z)) ? (DEF_YES) : (DEF_NO))


/*
*********************************************************************************************************
*                                          ASCII_IS_UPPER()
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

#define  ASCII_IS_UPPER(c)             ((((c) >= ASCII_CHAR_LATIN_UPPER_A) && ((c) <= ASCII_CHAR_LATIN_UPPER_Z)) ? (DEF_YES) : (DEF_NO))


/*$PAGE*/
/*
*********************************************************************************************************
*                                          ASCII_IS_ALPHA()
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

#define  ASCII_IS_ALPHA(c)             ((((ASCII_IS_UPPER(c)) == DEF_YES) || \
                                         ((ASCII_IS_LOWER(c)) == DEF_YES)) ? (DEF_YES) : (DEF_NO))


/*
*********************************************************************************************************
*                                        ASCII_IS_ALPHA_NUM()
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

#define  ASCII_IS_ALPHA_NUM(c)         ((((ASCII_IS_ALPHA(c)) == DEF_YES) || \
                                         ((ASCII_IS_DIG  (c)) == DEF_YES)) ? (DEF_YES) : (DEF_NO))


/*$PAGE*/
/*
*********************************************************************************************************
*                                          ASCII_IS_BLANK()
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

#define  ASCII_IS_BLANK(c)             ((((c) == ASCII_CHAR_SPACE) || ((c) == ASCII_CHAR_HT)) ? (DEF_YES) : (DEF_NO))


/*
*********************************************************************************************************
*                                          ASCII_IS_SPACE()
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

#define  ASCII_IS_SPACE(c)             ((((c) == ASCII_CHAR_SPACE) || ((c) == ASCII_CHAR_CR) || \
                                         ((c) == ASCII_CHAR_LF   ) || ((c) == ASCII_CHAR_FF) || \
                                         ((c) == ASCII_CHAR_HT   ) || ((c) == ASCII_CHAR_VT)) ? (DEF_YES) : (DEF_NO))


/*$PAGE*/
/*
*********************************************************************************************************
*                                          ASCII_IS_PRINT()
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

#define  ASCII_IS_PRINT(c)             ((((c) >= ASCII_CHAR_SPACE) && ((c) <= ASCII_CHAR_TILDE)) ? (DEF_YES) : (DEF_NO))


/*
*********************************************************************************************************
*                                          ASCII_IS_GRAPH()
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

#define  ASCII_IS_GRAPH(c)             ((((c) >= ASCII_CHAR_EXCLAMATION_MARK) && ((c) <= ASCII_CHAR_TILDE)) ? (DEF_YES) : (DEF_NO))


/*$PAGE*/
/*
*********************************************************************************************************
*                                          ASCII_IS_PUNCT()
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

#define  ASCII_IS_PUNCT(c)             ((((ASCII_IS_PRINT(c)) == DEF_YES) && \
                                         ((ASCII_IS_SPACE(c)) == DEF_NO ) && \
                                         ((ASCII_IS_ALPHA_NUM(c)) == DEF_NO )) ? (DEF_YES) : (DEF_NO))


/*
*********************************************************************************************************
*                                           ASCII_IS_CTRL()
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

#define  ASCII_IS_CTRL(c)             (((((CPU_INT08S)(c) >= ASCII_CHAR_NULL  ) && ((c) <= ASCII_CHAR_IS1)) || \
                                                                                   ((c) == ASCII_CHAR_DEL))  ? (DEF_YES) : (DEF_NO))


/*$PAGE*/
/*
*********************************************************************************************************
*                                ASCII CHARACTER CASE MAPPING MACRO's
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          ASCII_TO_LOWER()
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

#define  ASCII_TO_LOWER(c)              (((ASCII_IS_UPPER(c)) == DEF_YES) ? ((c) + (ASCII_CHAR_LATIN_LOWER_A - ASCII_CHAR_LATIN_UPPER_A)) : (c))


/*
*********************************************************************************************************
*                                          ASCII_TO_UPPER()
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

#define  ASCII_TO_UPPER(c)              (((ASCII_IS_LOWER(c)) == DEF_YES) ? ((c) - (ASCII_CHAR_LATIN_LOWER_A - ASCII_CHAR_LATIN_UPPER_A)) : (c))


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

CPU_BOOLEAN  ASCII_IsAlpha   (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsAlphaNum(CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsLower   (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsUpper   (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsDig     (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsDigOct  (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsDigHex  (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsBlank   (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsSpace   (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsPrint   (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsGraph   (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsPunct   (CPU_CHAR  c);

CPU_BOOLEAN  ASCII_IsCtrl    (CPU_CHAR  c);


CPU_CHAR     ASCII_ToLower   (CPU_CHAR  c);

CPU_CHAR     ASCII_ToUpper   (CPU_CHAR  c);


CPU_BOOLEAN  ASCII_Cmp       (CPU_CHAR  c1,
                              CPU_CHAR  c2);


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
* Note(s) : (1) See 'lib_ascii.h  MODULE'.
*********************************************************************************************************
*/

#endif                                                          /* End of lib ascii module include.                     */

