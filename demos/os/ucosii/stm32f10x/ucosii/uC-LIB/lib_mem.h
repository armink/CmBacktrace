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
*                                     STANDARD MEMORY OPERATIONS
*
* Filename      : lib_mem.h
* Version       : V1.37.01
* Programmer(s) : ITJ
*                 FBJ
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
*                 (2) Assumes the following versions (or more recent) of software modules are included in
*                     the project build :
*
*                     (a) uC/CPU V1.27
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This memory library header file is protected from multiple pre-processor inclusion through
*               use of the memory library module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  LIB_MEM_MODULE_PRESENT                                 /* See Note #1.                                         */
#define  LIB_MEM_MODULE_PRESENT


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
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <cpu_core.h>

#include  <lib_def.h>
#include  <lib_cfg.h>


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   LIB_MEM_MODULE
#define  LIB_MEM_EXT
#else
#define  LIB_MEM_EXT  extern
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        DEFAULT CONFIGURATION
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                             MEMORY LIBRARY ARGUMENT CHECK CONFIGURATION
*
* Note(s) : (1) Configure LIB_MEM_CFG_ARG_CHK_EXT_EN to enable/disable the memory library suite external
*               argument check feature :
*
*               (a) When ENABLED,      arguments received from any port interface provided by the developer
*                   or application are checked/validated.
*
*               (b) When DISABLED, NO  arguments received from any port interface provided by the developer
*                   or application are checked/validated.
*********************************************************************************************************
*/

                                                        /* Configure external argument check feature (see Note #1) :    */
#ifndef  LIB_MEM_CFG_ARG_CHK_EXT_EN
#define  LIB_MEM_CFG_ARG_CHK_EXT_EN     DEF_DISABLED
                                                        /*   DEF_DISABLED     Argument check DISABLED                   */
                                                        /*   DEF_ENABLED      Argument check ENABLED                    */
#endif


/*
*********************************************************************************************************
*                         MEMORY LIBRARY ASSEMBLY OPTIMIZATION CONFIGURATION
*
* Note(s) : (1) Configure LIB_MEM_CFG_OPTIMIZE_ASM_EN to enable/disable assembly-optimized memory functions.
*********************************************************************************************************
*/

                                                        /* Configure assembly-optimized function(s) [see Note #1] :     */
#ifndef  LIB_MEM_CFG_OPTIMIZE_ASM_EN
#define  LIB_MEM_CFG_OPTIMIZE_ASM_EN    DEF_DISABLED
                                                        /*   DEF_DISABLED     Assembly-optimized function(s) DISABLED   */
                                                        /*   DEF_ENABLED      Assembly-optimized function(s) ENABLED    */
#endif


/*
*********************************************************************************************************
*                                   MEMORY ALLOCATION CONFIGURATION
*
* Note(s) : (1) Configure LIB_MEM_CFG_ALLOC_EN to enable/disable memory allocation functions.
*********************************************************************************************************
*/

                                                        /* Configure memory allocation feature (see Note #1) :          */
#ifndef  LIB_MEM_CFG_ALLOC_EN
#define  LIB_MEM_CFG_ALLOC_EN           DEF_DISABLED
                                                        /*   DEF_DISABLED     Memory allocation DISABLED                */
                                                        /*   DEF_ENABLED      Memory allocation ENABLED                 */
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                     MEMORY LIBRARY TYPE DEFINES
*
* Note(s) : (1) LIB_MEM_TYPE_&&& #define values specifically chosen as ASCII representations of the memory
*               library types.  Memory displays of memory library objects will display the library TYPEs
*               with their chosen ASCII names.
*********************************************************************************************************
*/

#define  LIB_MEM_TYPE_NONE                        CPU_TYPE_CREATE('N', 'O', 'N', 'E')
#define  LIB_MEM_TYPE_HEAP                        CPU_TYPE_CREATE('H', 'E', 'A', 'P')
#define  LIB_MEM_TYPE_POOL                        CPU_TYPE_CREATE('P', 'O', 'O', 'L')


/*$PAGE*/
/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            LIB MEM TYPE
*
* Note(s) : (1) 'LIB_MEM_TYPE' declared as 'CPU_INT32U' & all 'LIB_MEM_TYPE's #define'd with large, non-trivial
*               values to trap & discard invalid/corrupted library memory objects based on 'LIB_MEM_TYPE'.
*********************************************************************************************************
*/

typedef  CPU_INT32U  LIB_MEM_TYPE;


/*
*********************************************************************************************************
*                                MEMORY POOL BLOCK QUANTITY DATA TYPE
*********************************************************************************************************
*/

typedef  CPU_SIZE_T  MEM_POOL_BLK_QTY;


/*
*********************************************************************************************************
*                                      MEMORY POOL TABLE IX TYPE
*********************************************************************************************************
*/

typedef  MEM_POOL_BLK_QTY  MEM_POOL_IX;


/*$PAGE*/
/*
*********************************************************************************************************
*                                        MEMORY POOL DATA TYPES
*
*                                                                      MEMORY SEGMENT
*                                                                     ----------------
*                                            MEMORY POOL'S            |              | <----
*                                             POINTERS TO             |    MEMORY    |     |
*                    MEM_POOL                MEMORY BLOCKS            |    BLOCKS    |     |
*               |----------------|            |---------|             |   --------   |     |
*               |        O------------------> |    O--------------------> |      |   |     |
*               |----------------|            |---------|             |   |      |   |     |
*               | Pool Addr Ptrs |            |    O-------------     |   --------   |     |
*               | Pool Size      |            |---------|       |     |              |     |
*               |----------------|            |         |       |     |   --------   |     |
*               |    Blk Size    |            |         |       --------> |      |   |     |
*               |    Blk Nbr     |            |         |             |   |      |   |     |
*               |    Blk Ix      |            |    .    |             |   --------   |     |
*               |----------------|            |    .    |             |              |     |
*               |----------------|            |    .    |             |      .       |     |
*               |        O-----------------   |         |             |      .       |     |
*               |----------------|        |   |         |             |      .       |     |
*               |        O------------    |   |         |             |              |     |
*               |----------------|   |    |   |---------|             |   --------   |     |
*               |  Seg Size Tot  |   |    |   |    O--------------------> |      |   |     |
*               |  Seg Size Rem  |   |    |   |---------|             |   |      |   |     |
*               |----------------|   |    |   |         |             |   --------   |     |
*               | Seg List Ptrs  |   |    |   |---------|             |              |     |
*               |----------------|   |    |                           | ------------ |     |
*                                    |    |                           |              | <--------
*                                    |    |                           |              |     |   |
*                                    |    |                           |              |     |   |
*                                    |    |                           |              |     |   |
*                                    |    |                           |              |     |   |
*                                    |    |                           |              |     |   |
*                                    |    |                           ----------------     |   |
*                                    |    |                                                |   |
*                                    |    --------------------------------------------------   |
*                                    |                                                         |
*                                    -----------------------------------------------------------
*
*********************************************************************************************************
*/

typedef  struct  mem_pool  MEM_POOL;

                                                                /* --------------------- MEM POOL --------------------- */
struct  mem_pool {
    LIB_MEM_TYPE        Type;                                   /* Pool type : LIB_TYPE_POOL or LIB_TYPE_HEAP.          */

    MEM_POOL           *SegHeadPtr;                             /* Ptr to head mem seg.                                 */
    MEM_POOL           *SegPrevPtr;                             /* Ptr to PREV mem seg.                                 */
    MEM_POOL           *SegNextPtr;                             /* Ptr to NEXT mem seg.                                 */
    MEM_POOL           *PoolPrevPtr;                            /* Ptr to PREV mem pool.                                */
    MEM_POOL           *PoolNextPtr;                            /* Ptr to NEXT mem pool.                                */

    void               *PoolAddrStart;                          /* Ptr   to start of mem seg for mem pool blks.         */
    void               *PoolAddrEnd;                            /* Ptr   to end   of mem seg for mem pool blks.         */
    void              **PoolPtrs;                               /* Ptr   to mem pool's array of blk ptrs.               */
    MEM_POOL_IX         BlkIx;                                  /* Ix  into mem pool's array of blk ptrs.               */
    CPU_SIZE_T          PoolSize;                               /* Size  of mem pool        (in octets).                */
    MEM_POOL_BLK_QTY    BlkNbr;                                 /* Nbr   of mem pool   blks.                            */
    CPU_SIZE_T          BlkSize;                                /* Size  of mem pool   blks (in octets).                */
    CPU_SIZE_T          BlkAlign;                               /* Align of mem pool   blks (in octets).                */

                                                                /* --------------------- MEM SEG ---------------------- */
    void               *SegAddr;                                /* Ptr      to mem seg's base/start addr.               */
    void               *SegAddrNextAvail;                       /* Ptr      to mem seg's next avail addr.               */
    CPU_SIZE_T          SegSizeTot;                             /* Tot size of mem seg (in octets).                     */
    CPU_SIZE_T          SegSizeRem;                             /* Rem size of mem seg (in octets).                     */
};


/*$PAGE*/
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
*                                      MEMORY DATA VALUE MACRO'S
*
* Note(s) : (1) (a) Some variables & variable buffers to pass & receive data values MUST start on appropriate
*                   CPU word-aligned addresses.  This is required because most word-aligned processors are more
*                   efficient & may even REQUIRE that multi-octet words start on CPU word-aligned addresses.
*
*                   (1) For 16-bit word-aligned processors, this means that
*
*                           all 16- & 32-bit words MUST start on addresses that are multiples of 2 octets
*
*                   (2) For 32-bit word-aligned processors, this means that
*
*                           all 16-bit       words MUST start on addresses that are multiples of 2 octets
*                           all 32-bit       words MUST start on addresses that are multiples of 4 octets
*
*               (b) However, some data values macro's appropriately access data values from any CPU addresses,
*                   word-aligned or not.  Thus for processors that require data word alignment, data words can
*                   be accessed to/from any CPU address, word-aligned or not, without generating data-word-
*                   alignment exceptions/faults.
*********************************************************************************************************
*/


/*$PAGE*/
/*
*********************************************************************************************************
*                                      ENDIAN WORD ORDER MACRO'S
*
* Description : Convert data values to & from big-, little, or host-endian CPU word order.
*
* Argument(s) : val       Data value to convert (see Notes #1 & #2).
*
* Return(s)   : Converted data value (see Notes #1 & #2).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Convert data values to the desired data-word order :
*
*                       MEM_VAL_BIG_TO_LITTLE_xx()      Convert big-        endian data values
*                                                            to little-     endian data values
*                       MEM_VAL_LITTLE_TO_BIG_xx()      Convert little-     endian data values
*                                                            to big-        endian data values
*                       MEM_VAL_xxx_TO_HOST_xx()        Convert big-/little-endian data values
*                                                            to host-       endian data values
*                       MEM_VAL_HOST_TO_xxx_xx()        Convert host-       endian data values
*                                                            to big-/little-endian data values
*
*                   See also 'cpu.h  CPU WORD CONFIGURATION  Note #2'.
*
*               (2) 'val' data value to convert & any variable to receive the returned conversion MUST
*                   start on appropriate CPU word-aligned addresses.
*
*                   See also 'MEMORY DATA VALUE MACRO'S  Note #1a'.
*
*               (3) MEM_VAL_COPY_xxx() macro's are more efficient than generic endian word order macro's &
*                   are also independent of CPU data-word-alignment & SHOULD be used whenever possible.
*
*                   See also 'MEM_VAL_COPY_GET_xxx()  Note #4'
*                          & 'MEM_VAL_COPY_SET_xxx()  Note #4'.
*
*               (4) Generic endian word order macro's are NOT atomic operations & MUST NOT be used on any
*                   non-static (i.e. volatile) variables, registers, hardware, etc.; without the caller of
*                   the macro's providing some form of additional protection (e.g. mutual exclusion).
*
*               (5) The 'CPU_CFG_ENDIAN_TYPE' pre-processor 'else'-conditional code SHOULD never be compiled/
*                   linked since each 'cpu.h' SHOULD ensure that the CPU data-word-memory order configuration
*                   constant (CPU_CFG_ENDIAN_TYPE) is configured with an appropriate data-word-memory order
*                   value (see 'cpu.h  CPU WORD CONFIGURATION  Note #2').  The 'else'-conditional code is
*                   included as an extra precaution in case 'cpu.h' is incorrectly configured.
*********************************************************************************************************
*/
/*$PAGE*/

#if    ((CPU_CFG_DATA_SIZE == CPU_WORD_SIZE_64) || \
        (CPU_CFG_DATA_SIZE == CPU_WORD_SIZE_32))

#define  MEM_VAL_BIG_TO_LITTLE_16(val)        ((CPU_INT16U)(((CPU_INT16U)((((CPU_INT16U)(val)) & (CPU_INT16U)    0xFF00u) >> (1u * DEF_OCTET_NBR_BITS))) | \
                                                            ((CPU_INT16U)((((CPU_INT16U)(val)) & (CPU_INT16U)    0x00FFu) << (1u * DEF_OCTET_NBR_BITS)))))

#define  MEM_VAL_BIG_TO_LITTLE_32(val)        ((CPU_INT32U)(((CPU_INT32U)((((CPU_INT32U)(val)) & (CPU_INT32U)0xFF000000u) >> (3u * DEF_OCTET_NBR_BITS))) | \
                                                            ((CPU_INT32U)((((CPU_INT32U)(val)) & (CPU_INT32U)0x00FF0000u) >> (1u * DEF_OCTET_NBR_BITS))) | \
                                                            ((CPU_INT32U)((((CPU_INT32U)(val)) & (CPU_INT32U)0x0000FF00u) << (1u * DEF_OCTET_NBR_BITS))) | \
                                                            ((CPU_INT32U)((((CPU_INT32U)(val)) & (CPU_INT32U)0x000000FFu) << (3u * DEF_OCTET_NBR_BITS)))))

#elif   (CPU_CFG_DATA_SIZE == CPU_WORD_SIZE_16)

#define  MEM_VAL_BIG_TO_LITTLE_16(val)        ((CPU_INT16U)(((CPU_INT16U)((((CPU_INT16U)(val)) & (CPU_INT16U)    0xFF00u) >> (1u * DEF_OCTET_NBR_BITS))) | \
                                                            ((CPU_INT16U)((((CPU_INT16U)(val)) & (CPU_INT16U)    0x00FFu) << (1u * DEF_OCTET_NBR_BITS)))))

#define  MEM_VAL_BIG_TO_LITTLE_32(val)        ((CPU_INT32U)(((CPU_INT32U)((((CPU_INT32U)(val)) & (CPU_INT32U)0xFF000000u) >> (1u * DEF_OCTET_NBR_BITS))) | \
                                                            ((CPU_INT32U)((((CPU_INT32U)(val)) & (CPU_INT32U)0x00FF0000u) << (1u * DEF_OCTET_NBR_BITS))) | \
                                                            ((CPU_INT32U)((((CPU_INT32U)(val)) & (CPU_INT32U)0x0000FF00u) >> (1u * DEF_OCTET_NBR_BITS))) | \
                                                            ((CPU_INT32U)((((CPU_INT32U)(val)) & (CPU_INT32U)0x000000FFu) << (1u * DEF_OCTET_NBR_BITS)))))

#else

#define  MEM_VAL_BIG_TO_LITTLE_16(val)                                                  (val)
#define  MEM_VAL_BIG_TO_LITTLE_32(val)                                                  (val)

#endif


#define  MEM_VAL_LITTLE_TO_BIG_16(val)                          MEM_VAL_BIG_TO_LITTLE_16(val)
#define  MEM_VAL_LITTLE_TO_BIG_32(val)                          MEM_VAL_BIG_TO_LITTLE_32(val)



#if     (CPU_CFG_ENDIAN_TYPE == CPU_ENDIAN_TYPE_BIG)

#define  MEM_VAL_BIG_TO_HOST_16(val)                                                    (val)
#define  MEM_VAL_BIG_TO_HOST_32(val)                                                    (val)
#define  MEM_VAL_LITTLE_TO_HOST_16(val)                         MEM_VAL_LITTLE_TO_BIG_16(val)
#define  MEM_VAL_LITTLE_TO_HOST_32(val)                         MEM_VAL_LITTLE_TO_BIG_32(val)

#elif   (CPU_CFG_ENDIAN_TYPE == CPU_ENDIAN_TYPE_LITTLE)

#define  MEM_VAL_BIG_TO_HOST_16(val)                            MEM_VAL_BIG_TO_LITTLE_16(val)
#define  MEM_VAL_BIG_TO_HOST_32(val)                            MEM_VAL_BIG_TO_LITTLE_32(val)
#define  MEM_VAL_LITTLE_TO_HOST_16(val)                                                 (val)
#define  MEM_VAL_LITTLE_TO_HOST_32(val)                                                 (val)

#else                                                               /* See Note #5.                                     */

#error  "CPU_CFG_ENDIAN_TYPE  illegally #defined in 'cpu.h'      "
#error  "                     [See 'cpu.h  CONFIGURATION ERRORS']"

#endif


#define  MEM_VAL_HOST_TO_BIG_16(val)                            MEM_VAL_BIG_TO_HOST_16(val)
#define  MEM_VAL_HOST_TO_BIG_32(val)                            MEM_VAL_BIG_TO_HOST_32(val)
#define  MEM_VAL_HOST_TO_LITTLE_16(val)                         MEM_VAL_LITTLE_TO_HOST_16(val)
#define  MEM_VAL_HOST_TO_LITTLE_32(val)                         MEM_VAL_LITTLE_TO_HOST_32(val)


/*$PAGE*/
/*
*********************************************************************************************************
*                                          MEM_VAL_GET_xxx()
*
* Description : Decode data values from any CPU memory address.
*
* Argument(s) : addr        Lowest CPU memory address of data value to decode (see Notes #2 & #3a).
*
* Return(s)   : Decoded data value from CPU memory address (see Notes #1 & #3b).
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Decode data values based on the values' data-word order in CPU memory :
*
*                       MEM_VAL_GET_xxx_BIG()           Decode big-   endian data values -- data words' most
*                                                           significant octet @ lowest memory address
*                       MEM_VAL_GET_xxx_LITTLE()        Decode little-endian data values -- data words' least
*                                                           significant octet @ lowest memory address
*                       MEM_VAL_GET_xxx()               Decode data values using CPU's native or configured
*                                                           data-word order
*
*                   See also 'cpu.h  CPU WORD CONFIGURATION  Note #2'.
*
*               (2) CPU memory addresses/pointers NOT checked for NULL.
*
*               (3) (a) MEM_VAL_GET_xxx() macro's decode data values without regard to CPU word-aligned addresses.
*                       Thus for processors that require data word alignment, data words can be decoded from any
*                       CPU address, word-aligned or not, without generating data-word-alignment exceptions/faults.
*
*                   (b) However, any variable to receive the returned data value MUST start on an appropriate CPU
*                       word-aligned address.
*
*                   See also 'MEMORY DATA VALUE MACRO'S  Note #1'.
*
*               (4) MEM_VAL_COPY_GET_xxx() macro's are more efficient than MEM_VAL_GET_xxx() macro's & are
*                   also independent of CPU data-word-alignment & SHOULD be used whenever possible.
*
*                   See also 'MEM_VAL_COPY_GET_xxx()  Note #4'.
*
*               (5) MEM_VAL_GET_xxx() macro's are NOT atomic operations & MUST NOT be used on any non-static
*                   (i.e. volatile) variables, registers, hardware, etc.; without the caller of the macro's
*                   providing some form of additional protection (e.g. mutual exclusion).
*
*               (6) The 'CPU_CFG_ENDIAN_TYPE' pre-processor 'else'-conditional code SHOULD never be compiled/
*                   linked since each 'cpu.h' SHOULD ensure that the CPU data-word-memory order configuration
*                   constant (CPU_CFG_ENDIAN_TYPE) is configured with an appropriate data-word-memory order
*                   value (see 'cpu.h  CPU WORD CONFIGURATION  Note #2').  The 'else'-conditional code is
*                   included as an extra precaution in case 'cpu.h' is incorrectly configured.
*********************************************************************************************************
*/
/*$PAGE*/

#define  MEM_VAL_GET_INT08U_BIG(addr)           ((CPU_INT08U) ((CPU_INT08U)(((CPU_INT08U)(*(((CPU_INT08U *)(addr)) + 0))) << (0u * DEF_OCTET_NBR_BITS))))

#define  MEM_VAL_GET_INT16U_BIG(addr)           ((CPU_INT16U)(((CPU_INT16U)(((CPU_INT16U)(*(((CPU_INT08U *)(addr)) + 0))) << (1u * DEF_OCTET_NBR_BITS))) + \
                                                              ((CPU_INT16U)(((CPU_INT16U)(*(((CPU_INT08U *)(addr)) + 1))) << (0u * DEF_OCTET_NBR_BITS)))))

#define  MEM_VAL_GET_INT32U_BIG(addr)           ((CPU_INT32U)(((CPU_INT32U)(((CPU_INT32U)(*(((CPU_INT08U *)(addr)) + 0))) << (3u * DEF_OCTET_NBR_BITS))) + \
                                                              ((CPU_INT32U)(((CPU_INT32U)(*(((CPU_INT08U *)(addr)) + 1))) << (2u * DEF_OCTET_NBR_BITS))) + \
                                                              ((CPU_INT32U)(((CPU_INT32U)(*(((CPU_INT08U *)(addr)) + 2))) << (1u * DEF_OCTET_NBR_BITS))) + \
                                                              ((CPU_INT32U)(((CPU_INT32U)(*(((CPU_INT08U *)(addr)) + 3))) << (0u * DEF_OCTET_NBR_BITS)))))



#define  MEM_VAL_GET_INT08U_LITTLE(addr)        ((CPU_INT08U) ((CPU_INT08U)(((CPU_INT08U)(*(((CPU_INT08U *)(addr)) + 0))) << (0u * DEF_OCTET_NBR_BITS))))

#define  MEM_VAL_GET_INT16U_LITTLE(addr)        ((CPU_INT16U)(((CPU_INT16U)(((CPU_INT16U)(*(((CPU_INT08U *)(addr)) + 0))) << (0u * DEF_OCTET_NBR_BITS))) + \
                                                              ((CPU_INT16U)(((CPU_INT16U)(*(((CPU_INT08U *)(addr)) + 1))) << (1u * DEF_OCTET_NBR_BITS)))))

#define  MEM_VAL_GET_INT32U_LITTLE(addr)        ((CPU_INT32U)(((CPU_INT32U)(((CPU_INT32U)(*(((CPU_INT08U *)(addr)) + 0))) << (0u * DEF_OCTET_NBR_BITS))) + \
                                                              ((CPU_INT32U)(((CPU_INT32U)(*(((CPU_INT08U *)(addr)) + 1))) << (1u * DEF_OCTET_NBR_BITS))) + \
                                                              ((CPU_INT32U)(((CPU_INT32U)(*(((CPU_INT08U *)(addr)) + 2))) << (2u * DEF_OCTET_NBR_BITS))) + \
                                                              ((CPU_INT32U)(((CPU_INT32U)(*(((CPU_INT08U *)(addr)) + 3))) << (3u * DEF_OCTET_NBR_BITS)))))



#if     (CPU_CFG_ENDIAN_TYPE == CPU_ENDIAN_TYPE_BIG)

#define  MEM_VAL_GET_INT08U(addr)                               MEM_VAL_GET_INT08U_BIG(addr)
#define  MEM_VAL_GET_INT16U(addr)                               MEM_VAL_GET_INT16U_BIG(addr)
#define  MEM_VAL_GET_INT32U(addr)                               MEM_VAL_GET_INT32U_BIG(addr)

#elif   (CPU_CFG_ENDIAN_TYPE == CPU_ENDIAN_TYPE_LITTLE)

#define  MEM_VAL_GET_INT08U(addr)                               MEM_VAL_GET_INT08U_LITTLE(addr)
#define  MEM_VAL_GET_INT16U(addr)                               MEM_VAL_GET_INT16U_LITTLE(addr)
#define  MEM_VAL_GET_INT32U(addr)                               MEM_VAL_GET_INT32U_LITTLE(addr)

#else                                                               /* See Note #6.                                     */

#error  "CPU_CFG_ENDIAN_TYPE  illegally #defined in 'cpu.h'      "
#error  "                     [See 'cpu.h  CONFIGURATION ERRORS']"

#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                          MEM_VAL_SET_xxx()
*
* Description : Encode data values to any CPU memory address.
*
* Argument(s) : addr        Lowest CPU memory address to encode data value (see Notes #2 & #3a).
*
*               val         Data value to encode (see Notes #1 & #3b).
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Encode data values into CPU memory based on the values' data-word order :
*
*                       MEM_VAL_SET_xxx_BIG()           Encode big-   endian data values -- data words' most
*                                                           significant octet @ lowest memory address
*                       MEM_VAL_SET_xxx_LITTLE()        Encode little-endian data values -- data words' least
*                                                           significant octet @ lowest memory address
*                       MEM_VAL_SET_xxx()               Encode data values using CPU's native or configured
*                                                           data-word order
*
*                   See also 'cpu.h  CPU WORD CONFIGURATION  Note #2'.
*
*               (2) CPU memory addresses/pointers NOT checked for NULL.
*
*               (3) (a) MEM_VAL_SET_xxx() macro's encode data values without regard to CPU word-aligned addresses.
*                       Thus for processors that require data word alignment, data words can be encoded to any
*                       CPU address, word-aligned or not, without generating data-word-alignment exceptions/faults.
*
*                   (b) However, 'val' data value to encode MUST start on an appropriate CPU word-aligned address.
*
*                   See also 'MEMORY DATA VALUE MACRO'S  Note #1'.
*
*               (4) MEM_VAL_COPY_SET_xxx() macro's are more efficient than MEM_VAL_SET_xxx() macro's & are
*                   also independent of CPU data-word-alignment & SHOULD be used whenever possible.
*
*                   See also 'MEM_VAL_COPY_SET_xxx()  Note #4'.
*
*               (5) MEM_VAL_SET_xxx() macro's are NOT atomic operations & MUST NOT be used on any non-static
*                   (i.e. volatile) variables, registers, hardware, etc.; without the caller of the macro's
*                   providing some form of additional protection (e.g. mutual exclusion).
*
*               (6) The 'CPU_CFG_ENDIAN_TYPE' pre-processor 'else'-conditional code SHOULD never be compiled/
*                   linked since each 'cpu.h' SHOULD ensure that the CPU data-word-memory order configuration
*                   constant (CPU_CFG_ENDIAN_TYPE) is configured with an appropriate data-word-memory order
*                   value (see 'cpu.h  CPU WORD CONFIGURATION  Note #2').  The 'else'-conditional code is
*                   included as an extra precaution in case 'cpu.h' is incorrectly configured.
*********************************************************************************************************
*/
/*$PAGE*/

#define  MEM_VAL_SET_INT08U_BIG(addr, val)                     do { (*(((CPU_INT08U *)(addr)) + 0)) = ((CPU_INT08U)((((CPU_INT08U)(val)) & (CPU_INT08U)      0xFFu) >> (0u * DEF_OCTET_NBR_BITS))); } while (0)

#define  MEM_VAL_SET_INT16U_BIG(addr, val)                     do { (*(((CPU_INT08U *)(addr)) + 0)) = ((CPU_INT08U)((((CPU_INT16U)(val)) & (CPU_INT16U)    0xFF00u) >> (1u * DEF_OCTET_NBR_BITS))); \
                                                                    (*(((CPU_INT08U *)(addr)) + 1)) = ((CPU_INT08U)((((CPU_INT16U)(val)) & (CPU_INT16U)    0x00FFu) >> (0u * DEF_OCTET_NBR_BITS))); } while (0)

#define  MEM_VAL_SET_INT32U_BIG(addr, val)                     do { (*(((CPU_INT08U *)(addr)) + 0)) = ((CPU_INT08U)((((CPU_INT32U)(val)) & (CPU_INT32U)0xFF000000u) >> (3u * DEF_OCTET_NBR_BITS))); \
                                                                    (*(((CPU_INT08U *)(addr)) + 1)) = ((CPU_INT08U)((((CPU_INT32U)(val)) & (CPU_INT32U)0x00FF0000u) >> (2u * DEF_OCTET_NBR_BITS))); \
                                                                    (*(((CPU_INT08U *)(addr)) + 2)) = ((CPU_INT08U)((((CPU_INT32U)(val)) & (CPU_INT32U)0x0000FF00u) >> (1u * DEF_OCTET_NBR_BITS))); \
                                                                    (*(((CPU_INT08U *)(addr)) + 3)) = ((CPU_INT08U)((((CPU_INT32U)(val)) & (CPU_INT32U)0x000000FFu) >> (0u * DEF_OCTET_NBR_BITS))); } while (0)



#define  MEM_VAL_SET_INT08U_LITTLE(addr, val)                  do { (*(((CPU_INT08U *)(addr)) + 0)) = ((CPU_INT08U)((((CPU_INT08U)(val)) & (CPU_INT08U)      0xFFu) >> (0u * DEF_OCTET_NBR_BITS))); } while (0)

#define  MEM_VAL_SET_INT16U_LITTLE(addr, val)                  do { (*(((CPU_INT08U *)(addr)) + 0)) = ((CPU_INT08U)((((CPU_INT16U)(val)) & (CPU_INT16U)    0x00FFu) >> (0u * DEF_OCTET_NBR_BITS))); \
                                                                    (*(((CPU_INT08U *)(addr)) + 1)) = ((CPU_INT08U)((((CPU_INT16U)(val)) & (CPU_INT16U)    0xFF00u) >> (1u * DEF_OCTET_NBR_BITS))); } while (0)

#define  MEM_VAL_SET_INT32U_LITTLE(addr, val)                  do { (*(((CPU_INT08U *)(addr)) + 0)) = ((CPU_INT08U)((((CPU_INT32U)(val)) & (CPU_INT32U)0x000000FFu) >> (0u * DEF_OCTET_NBR_BITS))); \
                                                                    (*(((CPU_INT08U *)(addr)) + 1)) = ((CPU_INT08U)((((CPU_INT32U)(val)) & (CPU_INT32U)0x0000FF00u) >> (1u * DEF_OCTET_NBR_BITS))); \
                                                                    (*(((CPU_INT08U *)(addr)) + 2)) = ((CPU_INT08U)((((CPU_INT32U)(val)) & (CPU_INT32U)0x00FF0000u) >> (2u * DEF_OCTET_NBR_BITS))); \
                                                                    (*(((CPU_INT08U *)(addr)) + 3)) = ((CPU_INT08U)((((CPU_INT32U)(val)) & (CPU_INT32U)0xFF000000u) >> (3u * DEF_OCTET_NBR_BITS))); } while (0)



#if     (CPU_CFG_ENDIAN_TYPE == CPU_ENDIAN_TYPE_BIG)

#define  MEM_VAL_SET_INT08U(addr, val)                          MEM_VAL_SET_INT08U_BIG(addr, val)
#define  MEM_VAL_SET_INT16U(addr, val)                          MEM_VAL_SET_INT16U_BIG(addr, val)
#define  MEM_VAL_SET_INT32U(addr, val)                          MEM_VAL_SET_INT32U_BIG(addr, val)

#elif   (CPU_CFG_ENDIAN_TYPE == CPU_ENDIAN_TYPE_LITTLE)

#define  MEM_VAL_SET_INT08U(addr, val)                          MEM_VAL_SET_INT08U_LITTLE(addr, val)
#define  MEM_VAL_SET_INT16U(addr, val)                          MEM_VAL_SET_INT16U_LITTLE(addr, val)
#define  MEM_VAL_SET_INT32U(addr, val)                          MEM_VAL_SET_INT32U_LITTLE(addr, val)

#else                                                               /* See Note #6.                                     */

#error  "CPU_CFG_ENDIAN_TYPE  illegally #defined in 'cpu.h'      "
#error  "                     [See 'cpu.h  CONFIGURATION ERRORS']"

#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                       MEM_VAL_COPY_GET_xxx()
*
* Description : Copy & decode data values from any CPU memory address to any CPU memory address.
*
* Argument(s) : addr_dest       Lowest CPU memory address to copy/decode source address's data value
*                                   (see Notes #2 & #3).
*
*               addr_src        Lowest CPU memory address of data value to copy/decode
*                                   (see Notes #2 & #3).
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Copy/decode data values based on the values' data-word order :
*
*                       MEM_VAL_COPY_GET_xxx_BIG()      Decode big-   endian data values -- data words' most
*                                                           significant octet @ lowest memory address
*                       MEM_VAL_COPY_GET_xxx_LITTLE()   Decode little-endian data values -- data words' least
*                                                           significant octet @ lowest memory address
*                       MEM_VAL_COPY_GET_xxx()          Decode data values using CPU's native or configured
*                                                           data-word order
*
*                   See also 'cpu.h  CPU WORD CONFIGURATION  Note #2'.
*
*               (2) (a) CPU memory addresses/pointers NOT checked for NULL.
*
*                   (b) CPU memory addresses/buffers  NOT checked for overlapping.
*
*                       (1) IEEE Std 1003.1, 2004 Edition, Section 'memcpy() : DESCRIPTION' states that
*                           "copying ... between objects that overlap ... is undefined".
*
*               (3) MEM_VAL_COPY_GET_xxx() macro's copy/decode data values without regard to CPU word-aligned
*                   addresses.  Thus for processors that require data word alignment, data words can be copied/
*                   decoded to/from any CPU address, word-aligned or not, without generating data-word-alignment
*                   exceptions/faults.
*
*               (4) MEM_VAL_COPY_GET_xxx() macro's are more efficient than MEM_VAL_GET_xxx() macro's & are
*                   also independent of CPU data-word-alignment & SHOULD be used whenever possible.
*
*                   See also 'MEM_VAL_GET_xxx()  Note #4'.
*
*               (5) Since octet-order copy/conversion are inverse operations, MEM_VAL_COPY_GET_xxx() &
*                   MEM_VAL_COPY_SET_xxx() macros are inverse, but identical, operations & are provided
*                   in both forms for semantics & consistency.
*
*                   See also 'MEM_VAL_COPY_SET_xxx()  Note #5'.
*
*               (6) MEM_VAL_COPY_GET_xxx() macro's are NOT atomic operations & MUST NOT be used on any non-
*                   static (i.e. volatile) variables, registers, hardware, etc.; without the caller of the
*                   macro's providing some form of additional protection (e.g. mutual exclusion).
*
*               (7) The 'CPU_CFG_ENDIAN_TYPE' pre-processor 'else'-conditional code SHOULD never be compiled/
*                   linked since each 'cpu.h' SHOULD ensure that the CPU data-word-memory order configuration
*                   constant (CPU_CFG_ENDIAN_TYPE) is configured with an appropriate data-word-memory order
*                   value (see 'cpu.h  CPU WORD CONFIGURATION  Note #2').  The 'else'-conditional code is
*                   included as an extra precaution in case 'cpu.h' is incorrectly configured.
*********************************************************************************************************
*/
/*$PAGE*/

#if     (CPU_CFG_ENDIAN_TYPE == CPU_ENDIAN_TYPE_BIG)


#define  MEM_VAL_COPY_GET_INT08U_BIG(addr_dest, addr_src)      do { (*(((CPU_INT08U *)(addr_dest)) + 0)) = (*(((CPU_INT08U *)(addr_src)) + 0)); } while (0)

#define  MEM_VAL_COPY_GET_INT16U_BIG(addr_dest, addr_src)      do { (*(((CPU_INT08U *)(addr_dest)) + 0)) = (*(((CPU_INT08U *)(addr_src)) + 0)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 1)) = (*(((CPU_INT08U *)(addr_src)) + 1)); } while (0)

#define  MEM_VAL_COPY_GET_INT32U_BIG(addr_dest, addr_src)      do { (*(((CPU_INT08U *)(addr_dest)) + 0)) = (*(((CPU_INT08U *)(addr_src)) + 0)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 1)) = (*(((CPU_INT08U *)(addr_src)) + 1)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 2)) = (*(((CPU_INT08U *)(addr_src)) + 2)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 3)) = (*(((CPU_INT08U *)(addr_src)) + 3)); } while (0)



#define  MEM_VAL_COPY_GET_INT08U_LITTLE(addr_dest, addr_src)   do { (*(((CPU_INT08U *)(addr_dest)) + 0)) = (*(((CPU_INT08U *)(addr_src)) + 0)); } while (0)

#define  MEM_VAL_COPY_GET_INT16U_LITTLE(addr_dest, addr_src)   do { (*(((CPU_INT08U *)(addr_dest)) + 0)) = (*(((CPU_INT08U *)(addr_src)) + 1)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 1)) = (*(((CPU_INT08U *)(addr_src)) + 0)); } while (0)

#define  MEM_VAL_COPY_GET_INT32U_LITTLE(addr_dest, addr_src)   do { (*(((CPU_INT08U *)(addr_dest)) + 0)) = (*(((CPU_INT08U *)(addr_src)) + 3)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 1)) = (*(((CPU_INT08U *)(addr_src)) + 2)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 2)) = (*(((CPU_INT08U *)(addr_src)) + 1)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 3)) = (*(((CPU_INT08U *)(addr_src)) + 0)); } while (0)



#define  MEM_VAL_COPY_GET_INT08U(addr_dest, addr_src)               MEM_VAL_COPY_GET_INT08U_BIG(addr_dest, addr_src)
#define  MEM_VAL_COPY_GET_INT16U(addr_dest, addr_src)               MEM_VAL_COPY_GET_INT16U_BIG(addr_dest, addr_src)
#define  MEM_VAL_COPY_GET_INT32U(addr_dest, addr_src)               MEM_VAL_COPY_GET_INT32U_BIG(addr_dest, addr_src)




#elif   (CPU_CFG_ENDIAN_TYPE == CPU_ENDIAN_TYPE_LITTLE)


#define  MEM_VAL_COPY_GET_INT08U_BIG(addr_dest, addr_src)      do { (*(((CPU_INT08U *)(addr_dest)) + 0)) = (*(((CPU_INT08U *)(addr_src)) + 0)); } while (0)

#define  MEM_VAL_COPY_GET_INT16U_BIG(addr_dest, addr_src)      do { (*(((CPU_INT08U *)(addr_dest)) + 0)) = (*(((CPU_INT08U *)(addr_src)) + 1)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 1)) = (*(((CPU_INT08U *)(addr_src)) + 0)); } while (0)

#define  MEM_VAL_COPY_GET_INT32U_BIG(addr_dest, addr_src)      do { (*(((CPU_INT08U *)(addr_dest)) + 0)) = (*(((CPU_INT08U *)(addr_src)) + 3)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 1)) = (*(((CPU_INT08U *)(addr_src)) + 2)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 2)) = (*(((CPU_INT08U *)(addr_src)) + 1)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 3)) = (*(((CPU_INT08U *)(addr_src)) + 0)); } while (0)



#define  MEM_VAL_COPY_GET_INT08U_LITTLE(addr_dest, addr_src)   do { (*(((CPU_INT08U *)(addr_dest)) + 0)) = (*(((CPU_INT08U *)(addr_src)) + 0)); } while (0)

#define  MEM_VAL_COPY_GET_INT16U_LITTLE(addr_dest, addr_src)   do { (*(((CPU_INT08U *)(addr_dest)) + 0)) = (*(((CPU_INT08U *)(addr_src)) + 0)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 1)) = (*(((CPU_INT08U *)(addr_src)) + 1)); } while (0)

#define  MEM_VAL_COPY_GET_INT32U_LITTLE(addr_dest, addr_src)   do { (*(((CPU_INT08U *)(addr_dest)) + 0)) = (*(((CPU_INT08U *)(addr_src)) + 0)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 1)) = (*(((CPU_INT08U *)(addr_src)) + 1)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 2)) = (*(((CPU_INT08U *)(addr_src)) + 2)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 3)) = (*(((CPU_INT08U *)(addr_src)) + 3)); } while (0)



#define  MEM_VAL_COPY_GET_INT08U(addr_dest, addr_src)               MEM_VAL_COPY_GET_INT08U_LITTLE(addr_dest, addr_src)
#define  MEM_VAL_COPY_GET_INT16U(addr_dest, addr_src)               MEM_VAL_COPY_GET_INT16U_LITTLE(addr_dest, addr_src)
#define  MEM_VAL_COPY_GET_INT32U(addr_dest, addr_src)               MEM_VAL_COPY_GET_INT32U_LITTLE(addr_dest, addr_src)




#else                                                               /* See Note #7.                                     */

#error  "CPU_CFG_ENDIAN_TYPE  illegally #defined in 'cpu.h'      "
#error  "                     [See 'cpu.h  CONFIGURATION ERRORS']"

#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                     MEM_VAL_COPY_GET_INTU_xxx()
*
* Description : Copy & decode data values from any CPU memory address to any CPU memory address for
*                   any sized data values.
*
* Argument(s) : addr_dest       Lowest CPU memory address to copy/decode source address's data value
*                                   (see Notes #2 & #3).
*
*               addr_src        Lowest CPU memory address of data value to copy/decode
*                                   (see Notes #2 & #3).
*
*               val_size        Number of data value octets to copy/decode.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Copy/decode data values based on the values' data-word order :
*
*                       MEM_VAL_COPY_GET_INTU_BIG()     Decode big-   endian data values -- data words' most
*                                                           significant octet @ lowest memory address
*                       MEM_VAL_COPY_GET_INTU_LITTLE()  Decode little-endian data values -- data words' least
*                                                           significant octet @ lowest memory address
*                       MEM_VAL_COPY_GET_INTU()         Decode data values using CPU's native or configured
*                                                           data-word order
*
*                   See also 'cpu.h  CPU WORD CONFIGURATION  Note #2'.
*
*               (2) (a) CPU memory addresses/pointers NOT checked for NULL.
*
*                   (b) CPU memory addresses/buffers  NOT checked for overlapping.
*
*                       (1) IEEE Std 1003.1, 2004 Edition, Section 'memcpy() : DESCRIPTION' states that
*                           "copying ... between objects that overlap ... is undefined".
*
*               (3) MEM_VAL_COPY_GET_INTU_xxx() macro's copy/decode data values without regard to CPU word-
*                   aligned addresses.  Thus for processors that require data word alignment, data words
*                   can be copied/decoded to/from any CPU address, word-aligned or not, without generating
*                   data-word-alignment exceptions/faults.
*
*               (4) MEM_VAL_COPY_GET_xxx() macro's are more efficient than MEM_VAL_COPY_GET_INTU_xxx()
*                   macro's & SHOULD be used whenever possible.
*
*                   See also 'MEM_VAL_COPY_GET_xxx()  Note #4'.
*
*               (5) Since octet-order copy/conversion are inverse operations, MEM_VAL_COPY_GET_INTU_xxx() &
*                   MEM_VAL_COPY_SET_INTU_xxx() macros are inverse, but identical, operations & are provided
*                   in both forms for semantics & consistency.
*
*                   See also 'MEM_VAL_COPY_SET_INTU_xxx()  Note #5'.
*
*               (6) MEM_VAL_COPY_GET_INTU_xxx() macro's are NOT atomic operations & MUST NOT be used on any
*                   non-static (i.e. volatile) variables, registers, hardware, etc.; without the caller of
*                   the macro's providing some form of additional protection (e.g. mutual exclusion).
*
*               (7) MISRA-C 2004 Rule 5.2 states that "identifiers in an inner scope shall not use the same
*                   name as an indentifier in an outer scope, and therefore hide that identifier".
*
*                   Therefore, to avoid possible redeclaration of commonly-used loop counter identifier names,
*                   'i' & 'j', MEM_VAL_COPY_GET_INTU_xxx() loop counter identifier names are prefixed with a
*                   single underscore.
*
*               (8) The 'CPU_CFG_ENDIAN_TYPE' pre-processor 'else'-conditional code SHOULD never be compiled/
*                   linked since each 'cpu.h' SHOULD ensure that the CPU data-word-memory order configuration
*                   constant (CPU_CFG_ENDIAN_TYPE) is configured with an appropriate data-word-memory order
*                   value (see 'cpu.h  CPU WORD CONFIGURATION  Note #2').  The 'else'-conditional code is
*                   included as an extra precaution in case 'cpu.h' is incorrectly configured.
*********************************************************************************************************
*/
/*$PAGE*/

#if     (CPU_CFG_ENDIAN_TYPE == CPU_ENDIAN_TYPE_BIG)


#define  MEM_VAL_COPY_GET_INTU_BIG(addr_dest, addr_src, val_size)       do {                                                                                  \
                                                                            CPU_SIZE_T  _i;                                                                   \
                                                                                                                                                              \
                                                                            for (_i = 0; _i < (val_size); _i++) {                                             \
                                                                                (*(((CPU_INT08U *)(addr_dest)) + _i)) = (*(((CPU_INT08U *)(addr_src)) + _i)); \
                                                                            }                                                                                 \
                                                                        } while (0)


#define  MEM_VAL_COPY_GET_INTU_LITTLE(addr_dest, addr_src, val_size)    do {                                                                                  \
                                                                            CPU_SIZE_T  _i;                                                                   \
                                                                            CPU_SIZE_T  _j;                                                                   \
                                                                                                                                                              \
                                                                                                                                                              \
                                                                            _j = (val_size) - 1;                                                              \
                                                                                                                                                              \
                                                                            for (_i = 0; _i < (val_size); _i++) {                                             \
                                                                                (*(((CPU_INT08U *)(addr_dest)) + _i)) = (*(((CPU_INT08U *)(addr_src)) + _j)); \
                                                                                _j--;                                                                         \
                                                                            }                                                                                 \
                                                                        } while (0)


#define  MEM_VAL_COPY_GET_INTU(addr_dest, addr_src, val_size)           MEM_VAL_COPY_GET_INTU_BIG(addr_dest, addr_src, val_size)




#elif   (CPU_CFG_ENDIAN_TYPE == CPU_ENDIAN_TYPE_LITTLE)


#define  MEM_VAL_COPY_GET_INTU_BIG(addr_dest, addr_src, val_size)       do {                                                                                  \
                                                                            CPU_SIZE_T  _i;                                                                   \
                                                                            CPU_SIZE_T  _j;                                                                   \
                                                                                                                                                              \
                                                                                                                                                              \
                                                                            _j = (val_size) - 1;                                                              \
                                                                                                                                                              \
                                                                            for (_i = 0; _i < (val_size); _i++) {                                             \
                                                                                (*(((CPU_INT08U *)(addr_dest)) + _i)) = (*(((CPU_INT08U *)(addr_src)) + _j)); \
                                                                                _j--;                                                                         \
                                                                            }                                                                                 \
                                                                        } while (0)


#define  MEM_VAL_COPY_GET_INTU_LITTLE(addr_dest, addr_src, val_size)    do {                                                                                  \
                                                                            CPU_SIZE_T  _i;                                                                   \
                                                                                                                                                              \
                                                                            for (_i = 0; _i < (val_size); _i++) {                                             \
                                                                                (*(((CPU_INT08U *)(addr_dest)) + _i)) = (*(((CPU_INT08U *)(addr_src)) + _i)); \
                                                                            }                                                                                 \
                                                                        } while (0)


#define  MEM_VAL_COPY_GET_INTU(addr_dest, addr_src, val_size)           MEM_VAL_COPY_GET_INTU_LITTLE(addr_dest, addr_src, val_size)




#else                                                                   /* See Note #8.                                 */

#error  "CPU_CFG_ENDIAN_TYPE  illegally #defined in 'cpu.h'      "
#error  "                     [See 'cpu.h  CONFIGURATION ERRORS']"

#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                       MEM_VAL_COPY_SET_xxx()
*
* Description : Copy & encode data values from any CPU memory address to any CPU memory address.
*
* Argument(s) : addr_dest       Lowest CPU memory address to copy/encode source address's data value
*                                   (see Notes #2 & #3).
*
*               addr_src        Lowest CPU memory address of data value to copy/encode
*                                   (see Notes #2 & #3).
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Copy/encode data values based on the values' data-word order :
*
*                       MEM_VAL_COPY_SET_xxx_BIG()      Encode big-   endian data values -- data words' most
*                                                           significant octet @ lowest memory address
*                       MEM_VAL_COPY_SET_xxx_LITTLE()   Encode little-endian data values -- data words' least
*                                                           significant octet @ lowest memory address
*                       MEM_VAL_COPY_SET_xxx()          Encode data values using CPU's native or configured
*                                                           data-word order
*
*                   See also 'cpu.h  CPU WORD CONFIGURATION  Note #2'.
*
*               (2) (a) CPU memory addresses/pointers NOT checked for NULL.
*
*                   (b) CPU memory addresses/buffers  NOT checked for overlapping.
*
*                       (1) IEEE Std 1003.1, 2004 Edition, Section 'memcpy() : DESCRIPTION' states that
*                           "copying ... between objects that overlap ... is undefined".
*
*               (3) MEM_VAL_COPY_SET_xxx() macro's copy/encode data values without regard to CPU word-aligned
*                   addresses.  Thus for processors that require data word alignment, data words can be copied/
*                   encoded to/from any CPU address, word-aligned or not, without generating data-word-alignment
*                   exceptions/faults.
*
*               (4) MEM_VAL_COPY_SET_xxx() macro's are more efficient than MEM_VAL_SET_xxx() macro's & are
*                   also independent of CPU data-word-alignment & SHOULD be used whenever possible.
*
*                   See also 'MEM_VAL_SET_xxx()  Note #4'.
*
*               (5) Since octet-order copy/conversion are inverse operations, MEM_VAL_COPY_GET_xxx() &
*                   MEM_VAL_COPY_SET_xxx() macros are inverse, but identical, operations & are provided
*                   in both forms for semantics & consistency.
*
*                   See also 'MEM_VAL_COPY_GET_xxx()  Note #5'.
*
*               (6) MEM_VAL_COPY_SET_xxx() macro's are NOT atomic operations & MUST NOT be used on any
*                   non-static (i.e. volatile) variables, registers, hardware, etc.; without the caller
*                   of the  macro's providing some form of additional protection (e.g. mutual exclusion).
*********************************************************************************************************
*/

                                                                        /* See Note #5.                                 */
#define  MEM_VAL_COPY_SET_INT08U_BIG(addr_dest, addr_src)               MEM_VAL_COPY_GET_INT08U_BIG(addr_dest, addr_src)
#define  MEM_VAL_COPY_SET_INT16U_BIG(addr_dest, addr_src)               MEM_VAL_COPY_GET_INT16U_BIG(addr_dest, addr_src)
#define  MEM_VAL_COPY_SET_INT32U_BIG(addr_dest, addr_src)               MEM_VAL_COPY_GET_INT32U_BIG(addr_dest, addr_src)

#define  MEM_VAL_COPY_SET_INT08U_LITTLE(addr_dest, addr_src)            MEM_VAL_COPY_GET_INT08U_LITTLE(addr_dest, addr_src)
#define  MEM_VAL_COPY_SET_INT16U_LITTLE(addr_dest, addr_src)            MEM_VAL_COPY_GET_INT16U_LITTLE(addr_dest, addr_src)
#define  MEM_VAL_COPY_SET_INT32U_LITTLE(addr_dest, addr_src)            MEM_VAL_COPY_GET_INT32U_LITTLE(addr_dest, addr_src)


#define  MEM_VAL_COPY_SET_INT08U(addr_dest, addr_src)                   MEM_VAL_COPY_GET_INT08U(addr_dest, addr_src)
#define  MEM_VAL_COPY_SET_INT16U(addr_dest, addr_src)                   MEM_VAL_COPY_GET_INT16U(addr_dest, addr_src)
#define  MEM_VAL_COPY_SET_INT32U(addr_dest, addr_src)                   MEM_VAL_COPY_GET_INT32U(addr_dest, addr_src)


/*$PAGE*/
/*
*********************************************************************************************************
*                                     MEM_VAL_COPY_SET_INTU_xxx()
*
* Description : Copy & encode data values from any CPU memory address to any CPU memory address for
*                   any sized data values.
*
* Argument(s) : addr_dest       Lowest CPU memory address to copy/encode source address's data value
*                                   (see Notes #2 & #3).
*
*               addr_src        Lowest CPU memory address of data value to copy/encode
*                                   (see Notes #2 & #3).
*
*               val_size        Number of data value octets to copy/encode.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Copy/encode data values based on the values' data-word order :
*
*                       MEM_VAL_COPY_SET_INTU_BIG()     Encode big-   endian data values -- data words' most
*                                                           significant octet @ lowest memory address
*                       MEM_VAL_COPY_SET_INTU_LITTLE()  Encode little-endian data values -- data words' least
*                                                           significant octet @ lowest memory address
*                       MEM_VAL_COPY_SET_INTU()         Encode data values using CPU's native or configured
*                                                           data-word order
*
*                   See also 'cpu.h  CPU WORD CONFIGURATION  Note #2'.
*
*               (2) (a) CPU memory addresses/pointers NOT checked for NULL.
*
*                   (b) CPU memory addresses/buffers  NOT checked for overlapping.
*
*                       (1) IEEE Std 1003.1, 2004 Edition, Section 'memcpy() : DESCRIPTION' states that
*                           "copying ... between objects that overlap ... is undefined".
*
*               (3) MEM_VAL_COPY_SET_INTU_xxx() macro's copy/encode data values without regard to CPU word-
*                   aligned addresses.  Thus for processors that require data word alignment, data words
*                   can be copied/encoded to/from any CPU address, word-aligned or not, without generating
*                   data-word-alignment exceptions/faults.
*
*               (4) MEM_VAL_COPY_SET_xxx() macro's are more efficient than MEM_VAL_COPY_SET_INTU_xxx()
*                   macro's & SHOULD be used whenever possible.
*
*                   See also 'MEM_VAL_COPY_SET_xxx()  Note #4'.
*
*               (5) Since octet-order copy/conversion are inverse operations, MEM_VAL_COPY_GET_INTU_xxx() &
*                   MEM_VAL_COPY_SET_INTU_xxx() macros are inverse, but identical, operations & are provided
*                   in both forms for semantics & consistency.
*
*                   See also 'MEM_VAL_COPY_GET_INTU_xxx()  Note #5'.
*
*               (6) MEM_VAL_COPY_SET_INTU_xxx() macro's are NOT atomic operations & MUST NOT be used on any
*                   non-static (i.e. volatile) variables, registers, hardware, etc.; without the caller of
*                   the macro's providing some form of additional protection (e.g. mutual exclusion).
*********************************************************************************************************
*/

                                                                        /* See Note #5.                                 */
#define  MEM_VAL_COPY_SET_INTU_BIG(addr_dest, addr_src, val_size)       MEM_VAL_COPY_GET_INTU_BIG(addr_dest, addr_src, val_size)
#define  MEM_VAL_COPY_SET_INTU_LITTLE(addr_dest, addr_src, val_size)    MEM_VAL_COPY_GET_INTU_LITTLE(addr_dest, addr_src, val_size)
#define  MEM_VAL_COPY_SET_INTU(addr_dest, addr_src, val_size)           MEM_VAL_COPY_GET_INTU(addr_dest, addr_src, val_size)


/*$PAGE*/
/*
*********************************************************************************************************
*                                         MEM_VAL_COPY_xxx()
*
* Description : Copy data values from any CPU memory address to any CPU memory address.
*
* Argument(s) : addr_dest       Lowest CPU memory address to copy source address's data value
*                                   (see Notes #2 & #3).
*
*               addr_src        Lowest CPU memory address of data value to copy
*                                   (see Notes #2 & #3).
*
*               val_size        Number of data value octets to copy.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) MEM_VAL_COPY_xxx() macro's copy data values based on CPU's native data-word order.
*
*                   See also 'cpu.h  CPU WORD CONFIGURATION  Note #2'.
*
*               (2) (a) CPU memory addresses/pointers NOT checked for NULL.
*
*                   (b) CPU memory addresses/buffers  NOT checked for overlapping.
*
*                       (1) IEEE Std 1003.1, 2004 Edition, Section 'memcpy() : DESCRIPTION' states that
*                           "copying ... between objects that overlap ... is undefined".
*
*               (3) MEM_VAL_COPY_xxx() macro's copy data values without regard to CPU word-aligned addresses.
*                   Thus for processors that require data word alignment, data words can be copied to/from any
*                   CPU address, word-aligned or not, without generating data-word-alignment exceptions/faults.
*
*               (4) MEM_VAL_COPY_xxx() macro's are more efficient than MEM_VAL_COPY() macro & SHOULD be
*                   used whenever possible.
*
*               (5) MEM_VAL_COPY_xxx() macro's are NOT atomic operations & MUST NOT be used on any non-static
*                   (i.e. volatile) variables, registers, hardware, etc.; without the caller of the macro's
*                   providing some form of additional protection (e.g. mutual exclusion).
*
*               (6) MISRA-C 2004 Rule 5.2 states that "identifiers in an inner scope shall not use the same
*                   name as an indentifier in an outer scope, and therefore hide that identifier".
*
*                   Therefore, to avoid possible redeclaration of commonly-used loop counter identifier name,
*                   'i', MEM_VAL_COPY() loop counter identifier name is prefixed with a single underscore.
*********************************************************************************************************
*/

#define  MEM_VAL_COPY_08(addr_dest, addr_src)                  do { (*(((CPU_INT08U *)(addr_dest)) + 0)) = (*(((CPU_INT08U *)(addr_src)) + 0)); } while (0)

#define  MEM_VAL_COPY_16(addr_dest, addr_src)                  do { (*(((CPU_INT08U *)(addr_dest)) + 0)) = (*(((CPU_INT08U *)(addr_src)) + 0)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 1)) = (*(((CPU_INT08U *)(addr_src)) + 1)); } while (0)

#define  MEM_VAL_COPY_32(addr_dest, addr_src)                  do { (*(((CPU_INT08U *)(addr_dest)) + 0)) = (*(((CPU_INT08U *)(addr_src)) + 0)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 1)) = (*(((CPU_INT08U *)(addr_src)) + 1)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 2)) = (*(((CPU_INT08U *)(addr_src)) + 2)); \
                                                                    (*(((CPU_INT08U *)(addr_dest)) + 3)) = (*(((CPU_INT08U *)(addr_src)) + 3)); } while (0)


#define  MEM_VAL_COPY(addr_dest, addr_src, val_size)        do {                                                                                \
                                                                CPU_SIZE_T  _i;                                                                 \
                                                                                                                                                \
                                                                for (_i = 0; _i < (val_size); _i++) {                                           \
                                                                    (*(((CPU_INT08U *)(addr_dest)) +_i)) = (*(((CPU_INT08U *)(addr_src)) +_i)); \
                                                                }                                                                               \
                                                            } while (0)


/*$PAGE*/
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void               Mem_Init              (       void);

                                                                    /* ---------------- MEM API  FNCTS ---------------- */
void               Mem_Clr               (       void              *pmem,
                                                 CPU_SIZE_T         size);

void               Mem_Set               (       void              *pmem,
                                                 CPU_INT08U         data_val,
                                                 CPU_SIZE_T         size);

void               Mem_Copy              (       void              *pdest,
                                          const  void              *psrc,
                                                 CPU_SIZE_T         size);

void               Mem_Move              (       void              *pdest,
                                          const  void              *psrc,
                                                 CPU_SIZE_T         size);

CPU_BOOLEAN        Mem_Cmp               (const  void              *p1_mem,
                                          const  void              *p2_mem,
                                                 CPU_SIZE_T         size);



#if (LIB_MEM_CFG_ALLOC_EN == DEF_ENABLED)                           /* ---------------- MEM POOL FNCTS ---------------- */

void              *Mem_HeapAlloc         (       CPU_SIZE_T         size,
                                                 CPU_SIZE_T         align,
                                                 CPU_SIZE_T        *poctets_reqd,
                                                 LIB_ERR           *perr);

CPU_SIZE_T         Mem_HeapGetSizeRem    (       CPU_SIZE_T         align,
                                                 LIB_ERR           *perr);


CPU_SIZE_T         Mem_SegGetSizeRem     (       MEM_POOL          *pmem_pool,
                                                 CPU_SIZE_T         align,
                                                 LIB_ERR           *perr);


void               Mem_PoolClr           (       MEM_POOL          *pmem_pool,
                                                 LIB_ERR           *perr);

void               Mem_PoolCreate        (       MEM_POOL          *pmem_pool,
                                                 void              *pmem_base_addr,
                                                 CPU_SIZE_T         mem_size,
                                                 MEM_POOL_BLK_QTY   blk_nbr,
                                                 CPU_SIZE_T         blk_size,
                                                 CPU_SIZE_T         blk_align,
                                                 CPU_SIZE_T        *poctets_reqd,
                                                 LIB_ERR           *perr);


MEM_POOL_BLK_QTY   Mem_PoolBlkGetNbrAvail(       MEM_POOL          *pmem_pool,
                                                 LIB_ERR           *perr);

void              *Mem_PoolBlkGet        (       MEM_POOL          *pmem_pool,
                                                 CPU_SIZE_T         size,
                                                 LIB_ERR           *perr);

void              *Mem_PoolBlkGetUsedAtIx(       MEM_POOL          *pmem_pool,
                                                 MEM_POOL_IX        used_ix,
                                                 LIB_ERR           *perr);

void               Mem_PoolBlkFree       (       MEM_POOL          *pmem_pool,
                                                 void              *pmem_blk,
                                                 LIB_ERR           *perr);

MEM_POOL_IX        Mem_PoolBlkIxGet      (       MEM_POOL          *pmem_pool,
                                                 void              *pmem_blk,
                                                 LIB_ERR           *perr);

#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  LIB_MEM_CFG_ARG_CHK_EXT_EN
#error  "LIB_MEM_CFG_ARG_CHK_EXT_EN         not #define'd in 'lib_cfg.h'"
#error  "                             [MUST be  DEF_DISABLED]           "
#error  "                             [     ||  DEF_ENABLED ]           "

#elif  ((LIB_MEM_CFG_ARG_CHK_EXT_EN != DEF_DISABLED) && \
        (LIB_MEM_CFG_ARG_CHK_EXT_EN != DEF_ENABLED ))
#error  "LIB_MEM_CFG_ARG_CHK_EXT_EN   illegally #define'd in 'lib_cfg.h'"
#error  "                             [MUST be  DEF_DISABLED]           "
#error  "                             [     ||  DEF_ENABLED ]           "
#endif



#ifndef  LIB_MEM_CFG_OPTIMIZE_ASM_EN
#error  "LIB_MEM_CFG_OPTIMIZE_ASM_EN        not #define'd in 'lib_cfg.h'"
#error  "                             [MUST be  DEF_DISABLED]           "
#error  "                             [     ||  DEF_ENABLED ]           "

#elif  ((LIB_MEM_CFG_OPTIMIZE_ASM_EN != DEF_DISABLED) && \
        (LIB_MEM_CFG_OPTIMIZE_ASM_EN != DEF_ENABLED ))
#error  "LIB_MEM_CFG_OPTIMIZE_ASM_EN  illegally #define'd in 'lib_cfg.h'"
#error  "                             [MUST be  DEF_DISABLED]           "
#error  "                             [     ||  DEF_ENABLED ]           "
#endif




#ifndef  LIB_MEM_CFG_ALLOC_EN
#error  "LIB_MEM_CFG_ALLOC_EN               not #define'd in 'lib_cfg.h'"
#error  "                             [MUST be  DEF_DISABLED]           "
#error  "                             [     ||  DEF_ENABLED ]           "

#elif  ((LIB_MEM_CFG_ALLOC_EN != DEF_DISABLED) && \
        (LIB_MEM_CFG_ALLOC_EN != DEF_ENABLED ))
#error  "LIB_MEM_CFG_ALLOC_EN         illegally #define'd in 'lib_cfg.h'"
#error  "                             [MUST be  DEF_DISABLED]           "
#error  "                             [     ||  DEF_ENABLED ]           "


#elif   (LIB_MEM_CFG_ALLOC_EN == DEF_ENABLED)


#ifndef  LIB_MEM_CFG_HEAP_SIZE
#error  "LIB_MEM_CFG_HEAP_SIZE              not #define'd in 'lib_cfg.h'"
#error  "                             [MUST be  > 0]                    "

#elif   (DEF_CHK_VAL_MIN(LIB_MEM_CFG_HEAP_SIZE, 1) != DEF_OK)
#error  "LIB_MEM_CFG_HEAP_SIZE        illegally #define'd in 'lib_cfg.h'"
#error  "                             [MUST be  > 0]                    "
#endif


#ifdef   LIB_MEM_CFG_HEAP_BASE_ADDR
#if     (LIB_MEM_CFG_HEAP_BASE_ADDR == 0x0)
#error  "LIB_MEM_CFG_HEAP_BASE_ADDR   illegally #define'd in 'lib_cfg.h'"
#error  "                             [MUST be  > 0x0]                  "
#endif
#endif


#endif


/*
*********************************************************************************************************
*                                    LIBRARY CONFIGURATION ERRORS
*********************************************************************************************************
*/

                                                                /* See 'lib_mem.h  Note #2a'.                           */
#if     (CPU_CORE_VERSION < 127u)
#error  "CPU_CORE_VERSION  [SHOULD be >= V1.27]"
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                             MODULE END
*
* Note(s) : (1) See 'lib_mem.h  MODULE'.
*********************************************************************************************************
*/

#endif                                                          /* End of lib mem module include.                       */

