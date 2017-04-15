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
* Filename      : lib_mem.c
* Version       : V1.37.01
* Programmer(s) : ITJ
*                 FGK
*                 JFD
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
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#define    MICRIUM_SOURCE
#define    LIB_MEM_MODULE
#include  <lib_mem.h>


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

#if     (LIB_MEM_CFG_ALLOC_EN == DEF_ENABLED)
MEM_POOL    *Mem_PoolTbl;                                               /* Mem      pool/seg tbl.                       */
MEM_POOL     Mem_PoolHeap;                                              /* Mem heap pool/seg.                           */

#ifndef  LIB_MEM_CFG_HEAP_BASE_ADDR
CPU_INT08U   Mem_Heap[LIB_MEM_CFG_HEAP_SIZE];                           /* Mem heap.                                    */
#endif
#endif


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

#if (LIB_MEM_CFG_ALLOC_EN == DEF_ENABLED)                               /* -------------- MEM POOL FNCTS -------------- */

#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
static  CPU_BOOLEAN   Mem_PoolBlkIsValidAddr(MEM_POOL          *pmem_pool,
                                             void              *pmem_blk);
#endif


static  CPU_SIZE_T    Mem_SegCalcTotSize    (void              *pmem_addr,
                                             MEM_POOL_BLK_QTY   blk_nbr,
                                             CPU_SIZE_T         blk_size,
                                             CPU_SIZE_T         blk_align);

static  void         *Mem_SegAlloc          (MEM_POOL          *pmem_pool,
                                             CPU_SIZE_T         size,
                                             CPU_SIZE_T         align);

#endif


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*$PAGE*/
/*
*********************************************************************************************************
*                                             Mem_Init()
*
* Description : (1) Initialize Memory Management Module :
*
*                   (a) Initialize heap memory pool
*                   (b) Initialize      memory pool table
*
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (2) Mem_Init() MUST be called ... :
*
*                   (a) ONLY ONCE from a product's application; ...
*                   (b) BEFORE product's application calls any memory library module function(s)
*********************************************************************************************************
*/

void  Mem_Init (void)
{
#if (LIB_MEM_CFG_ALLOC_EN == DEF_ENABLED)
    MEM_POOL  *pmem_pool;

                                                                        /* --------- INIT MEM HEAP SEG / POOL --------- */
    pmem_pool                   = (MEM_POOL   *)&Mem_PoolHeap;
    pmem_pool->Type             = (LIB_MEM_TYPE) LIB_MEM_TYPE_HEAP;
    pmem_pool->SegHeadPtr       = (MEM_POOL   *)&Mem_PoolHeap;          /* Heap seg head = heap seg.                    */
    pmem_pool->SegPrevPtr       = (MEM_POOL   *) 0;
    pmem_pool->SegNextPtr       = (MEM_POOL   *) 0;
    pmem_pool->PoolPrevPtr      = (MEM_POOL   *) 0;
    pmem_pool->PoolNextPtr      = (MEM_POOL   *) 0;
    pmem_pool->PoolAddrStart    = (void       *) 0;
    pmem_pool->PoolAddrEnd      = (void       *) 0;
    pmem_pool->PoolPtrs         = (void      **) 0;
    pmem_pool->BlkSize          = (CPU_SIZE_T  ) 0u;
    pmem_pool->BlkNbr           = (CPU_SIZE_T  ) 0u;
    pmem_pool->BlkIx            = (MEM_POOL_IX ) 0u;

#ifdef  LIB_MEM_CFG_HEAP_BASE_ADDR
    pmem_pool->SegAddr          = (void       *) LIB_MEM_CFG_HEAP_BASE_ADDR;
    pmem_pool->SegAddrNextAvail = (void       *) LIB_MEM_CFG_HEAP_BASE_ADDR;
#else
    pmem_pool->SegAddr          = (void       *)&Mem_Heap[0];
    pmem_pool->SegAddrNextAvail = (void       *)&Mem_Heap[0];
#endif

    pmem_pool->SegSizeTot       = (CPU_SIZE_T  ) LIB_MEM_CFG_HEAP_SIZE;
    pmem_pool->SegSizeRem       = (CPU_SIZE_T  ) LIB_MEM_CFG_HEAP_SIZE;

                                                                        /* ------------ INIT MEM POOL TBL ------------- */
    Mem_PoolTbl = &Mem_PoolHeap;
#endif
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                              Mem_Clr()
*
* Description : Clear data buffer (see Note #2).
*
* Argument(s) : pmem        Pointer to memory buffer to clear.
*
*               size        Number of data buffer octets to clear (see Note #1).
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Null clears allowed (i.e. zero-length clears).
*
*                   See also 'Mem_Set()  Note #1'.
*
*               (2) Clear data by setting each data octet to 0.
*********************************************************************************************************
*/

void  Mem_Clr (void        *pmem,
               CPU_SIZE_T   size)
{
    Mem_Set(pmem,
            0u,                                                 /* See Note #2.                                         */
            size);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                              Mem_Set()
*
* Description : Fill data buffer with specified data octet.
*
* Argument(s) : pmem        Pointer to memory buffer to fill with specified data octet.
*
*               data_val    Data fill octet value.
*
*               size        Number of data buffer octets to fill (see Note #1).
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Null sets allowed (i.e. zero-length sets).
*
*               (2) For best CPU performance, optimized to fill data buffer using 'CPU_ALIGN'-sized data
*                   words.
*
*                   (a) Since many word-aligned processors REQUIRE that multi-octet words be accessed on
*                       word-aligned addresses, 'CPU_ALIGN'-sized words MUST be accessed on 'CPU_ALIGN'd
*                       addresses.
*
*               (3) Modulo arithmetic is used to determine whether a memory buffer starts on a 'CPU_ALIGN'
*                   address boundary.
*
*                   Modulo arithmetic in ANSI-C REQUIREs operations performed on integer values.  Thus
*                   address values MUST be cast to an appropriately-sized integer value PRIOR to any
*                  'mem_align_mod' arithmetic operation.
*********************************************************************************************************
*/

void  Mem_Set (void        *pmem,
               CPU_INT08U   data_val,
               CPU_SIZE_T   size)
{
    CPU_SIZE_T   size_rem;
    CPU_ALIGN    data_align;
    CPU_ALIGN   *pmem_align;
    CPU_INT08U  *pmem_08;
    CPU_DATA     mem_align_mod;
    CPU_DATA     i;


#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
    if (size < 1) {                                             /* See Note #1.                                         */
        return;
    }
    if (pmem == (void *)0) {
        return;
    }
#endif


    data_align = 0u;
    for (i = 0u; i < sizeof(CPU_ALIGN); i++) {                  /* Fill each data_align octet with data val.            */
        data_align <<=  DEF_OCTET_NBR_BITS;
        data_align  |= (CPU_ALIGN)data_val;
    }

    size_rem      =  size;
    mem_align_mod = (CPU_INT08U)((CPU_ADDR)pmem % sizeof(CPU_ALIGN));   /* See Note #3.                                 */

    pmem_08 = (CPU_INT08U *)pmem;
    if (mem_align_mod != 0u) {                                  /* If leading octets avail,                   ...       */
        i = mem_align_mod;
        while ((size_rem > 0) &&                                /* ... start mem buf fill with leading octets ...       */
               (i        < sizeof(CPU_ALIGN ))) {               /* ... until next CPU_ALIGN word boundary.              */
           *pmem_08++ = data_val;
            size_rem -= sizeof(CPU_INT08U);
            i++;
        }
    }

    pmem_align = (CPU_ALIGN *)pmem_08;                          /* See Note #2a.                                        */
    while (size_rem >= sizeof(CPU_ALIGN)) {                     /* While mem buf aligned on CPU_ALIGN word boundaries,  */
       *pmem_align++ = data_align;                              /* ... fill mem buf with    CPU_ALIGN-sized data.       */
        size_rem    -= sizeof(CPU_ALIGN);
    }

    pmem_08 = (CPU_INT08U *)pmem_align;
    while (size_rem > 0) {                                      /* Finish mem buf fill with trailing octets.            */
       *pmem_08++   = data_val;
        size_rem   -= sizeof(CPU_INT08U);
    }
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                             Mem_Copy()
*
* Description : Copy data octets from one memory buffer to another memory buffer.
*
* Argument(s) : pdest       Pointer to destination memory buffer.
*
*               psrc        Pointer to source      memory buffer.
*
*               size        Number of octets to copy (see Note #1).
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Null copies allowed (i.e. zero-length copies).
*
*               (2) Memory buffers NOT checked for overlapping.
*
*                   (a) IEEE Std 1003.1, 2004 Edition, Section 'memcpy() : DESCRIPTION' states that "if
*                       copying takes place between objects that overlap, the behavior is undefined".
*
*                   (b) However, data octets from a source memory buffer at a higher address value SHOULD
*                       successfully copy to a destination memory buffer at a lower  address value even
*                       if any octets of the memory buffers overlap as long as no individual, atomic CPU
*                       word copy overlaps.
*
*                       Since Mem_Copy() performs the data octet copy via 'CPU_ALIGN'-sized words &/or
*                       octets; & since 'CPU_ALIGN'-sized words MUST be accessed on word-aligned addresses
*                       (see Note #3b), neither 'CPU_ALIGN'-sized words nor octets at unique addresses can
*                       ever overlap.
*
*                       Therefore, Mem_Copy() SHOULD be able to successfully copy overlapping memory
*                       buffers as long as the source memory buffer is at a higher address value than the
*                       destination memory buffer.
*
*               (3) For best CPU performance, optimized to copy data buffer using 'CPU_ALIGN'-sized data
*                   words.
*
*                   (a) Since many word-aligned processors REQUIRE that multi-octet words be accessed on
*                       word-aligned addresses, 'CPU_ALIGN'-sized words MUST be accessed on 'CPU_ALIGN'd
*                       addresses.
*
*               (4) Modulo arithmetic is used to determine whether a memory buffer starts on a 'CPU_ALIGN'
*                   address boundary.
*
*                   Modulo arithmetic in ANSI-C REQUIREs operations performed on integer values.  Thus
*                   address values MUST be cast to an appropriately-sized integer value PRIOR to any
*                  'mem_align_mod' arithmetic operation.
*********************************************************************************************************
*/
/*$PAGE*/
#if (LIB_MEM_CFG_OPTIMIZE_ASM_EN != DEF_ENABLED)
void  Mem_Copy (       void        *pdest,
                const  void        *psrc,
                       CPU_SIZE_T   size)
{
           CPU_SIZE_T    size_rem;
           CPU_SIZE_T    mem_gap_octets;
           CPU_ALIGN    *pmem_align_dest;
    const  CPU_ALIGN    *pmem_align_src;
           CPU_INT08U   *pmem_08_dest;
    const  CPU_INT08U   *pmem_08_src;
           CPU_DATA      i;
           CPU_DATA      mem_align_mod_dest;
           CPU_DATA      mem_align_mod_src;
           CPU_BOOLEAN   mem_aligned;


#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
    if (size < 1) {                                             /* See Note #1.                                         */
        return;
    }
    if (pdest == (void *)0) {
        return;
    }
    if (psrc  == (void *)0) {
        return;
    }
#endif


    size_rem           =  size;

    pmem_08_dest       = (      CPU_INT08U *)pdest;
    pmem_08_src        = (const CPU_INT08U *)psrc;

    mem_gap_octets     = pmem_08_src - pmem_08_dest;


    if (mem_gap_octets >= sizeof(CPU_ALIGN)) {                  /* Avoid bufs overlap.                                  */
                                                                /* See Note #4.                                         */
        mem_align_mod_dest = (CPU_INT08U)((CPU_ADDR)pmem_08_dest % sizeof(CPU_ALIGN));
        mem_align_mod_src  = (CPU_INT08U)((CPU_ADDR)pmem_08_src  % sizeof(CPU_ALIGN));

        mem_aligned        = (mem_align_mod_dest == mem_align_mod_src) ? DEF_YES : DEF_NO;

        if (mem_aligned == DEF_YES) {                           /* If mem bufs' alignment offset equal, ...             */
                                                                /* ... optimize copy for mem buf alignment.             */
            if (mem_align_mod_dest != 0u) {                     /* If leading octets avail,                   ...       */
                i = mem_align_mod_dest;
                while ((size_rem   >  0) &&                     /* ... start mem buf copy with leading octets ...       */
                       (i          <  sizeof(CPU_ALIGN ))) {    /* ... until next CPU_ALIGN word boundary.              */
                   *pmem_08_dest++ = *pmem_08_src++;
                    size_rem      -=  sizeof(CPU_INT08U);
                    i++;
                }
            }

            pmem_align_dest = (      CPU_ALIGN *)pmem_08_dest;  /* See Note #3a.                                        */
            pmem_align_src  = (const CPU_ALIGN *)pmem_08_src;
            while (size_rem      >=  sizeof(CPU_ALIGN)) {       /* While mem bufs aligned on CPU_ALIGN word boundaries, */
               *pmem_align_dest++ = *pmem_align_src++;          /* ... copy psrc to pdest with CPU_ALIGN-sized words.   */
                size_rem         -=  sizeof(CPU_ALIGN);
            }

            pmem_08_dest = (      CPU_INT08U *)pmem_align_dest;
            pmem_08_src  = (const CPU_INT08U *)pmem_align_src;
        }
    }

    while (size_rem > 0) {                                      /* For unaligned mem bufs or trailing octets, ...       */
       *pmem_08_dest++ = *pmem_08_src++;                        /* ... copy psrc to pdest by octets.                    */
        size_rem      -=  sizeof(CPU_INT08U);
    }
}
#endif


/*
*********************************************************************************************************
*                                             Mem_Move()
*
* Description : Move data octets from one memory buffer to another memory buffer, or within the same
*               memory buffer. Overlapping is correctly handled for all move operations.
*
* Argument(s) : pdest       Pointer to destination memory buffer.
*
*               psrc        Pointer to source      memory buffer.
*
*               size        Number of octets to move (see Note #1).
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Null move operations allowed (i.e. zero-length).
*
*               (2) Memory buffers checked for overlapping.
*
*               (3) For best CPU performance, optimized to copy data buffer using 'CPU_ALIGN'-sized data
*                   words.
*
*                   (a) Since many word-aligned processors REQUIRE that multi-octet words be accessed on
*                       word-aligned addresses, 'CPU_ALIGN'-sized words MUST be accessed on 'CPU_ALIGN'd
*                       addresses.
*
*               (4) Modulo arithmetic is used to determine whether a memory buffer starts on a 'CPU_ALIGN'
*                   address boundary.
*
*                   Modulo arithmetic in ANSI-C REQUIREs operations performed on integer values.  Thus
*                   address values MUST be cast to an appropriately-sized integer value PRIOR to any
*                  'mem_align_mod' arithmetic operation.
*********************************************************************************************************
*/
/*$PAGE*/

void  Mem_Move (       void        *pdest,
                const  void        *psrc,
                       CPU_SIZE_T   size)
{
           CPU_SIZE_T    size_rem;
           CPU_SIZE_T    mem_gap_octets;
           CPU_ALIGN    *pmem_align_dest;
    const  CPU_ALIGN    *pmem_align_src;
           CPU_INT08U   *pmem_08_dest;
    const  CPU_INT08U   *pmem_08_src;
           CPU_INT08S    i;
           CPU_DATA      mem_align_mod_dest;
           CPU_DATA      mem_align_mod_src;
           CPU_BOOLEAN   mem_aligned;


#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
    if (size < 1) {
        return;
    }
    if (pdest == (void *)0) {
        return;
    }
    if (psrc  == (void *)0) {
        return;
    }
#endif

    pmem_08_src  = (const CPU_INT08U *)psrc;
    pmem_08_dest = (      CPU_INT08U *)pdest;
    if (pmem_08_src > pmem_08_dest) {
        Mem_Copy(pdest, psrc, size);
        return;
    }

    size_rem           =  size;

    pmem_08_dest       = (      CPU_INT08U *)pdest + size - 1;
    pmem_08_src        = (const CPU_INT08U *)psrc  + size - 1;
    
    mem_gap_octets     = pmem_08_dest - pmem_08_src;
    

    if (mem_gap_octets >= sizeof(CPU_ALIGN)) {                  /* Avoid bufs overlap.                                  */
    
                                                                /* See Note #4.                                         */
        mem_align_mod_dest = (CPU_INT08U)((CPU_ADDR)pmem_08_dest % sizeof(CPU_ALIGN));
        mem_align_mod_src  = (CPU_INT08U)((CPU_ADDR)pmem_08_src  % sizeof(CPU_ALIGN));

        mem_aligned        = (mem_align_mod_dest == mem_align_mod_src) ? DEF_YES : DEF_NO;

        if (mem_aligned == DEF_YES) {                           /* If mem bufs' alignment offset equal, ...             */
                                                                /* ... optimize copy for mem buf alignment.             */
            if (mem_align_mod_dest != (sizeof(CPU_ALIGN) - 1)) {/* If leading octets avail,                   ...       */
                i = mem_align_mod_dest;
                while ((size_rem   >  0) &&                     /* ... start mem buf copy with leading octets ...       */
                       (i          >= 0)) {                     /* ... until next CPU_ALIGN word boundary.              */
                   *pmem_08_dest-- = *pmem_08_src--;
                    size_rem      -=  sizeof(CPU_INT08U);
                    i--;
                }
            }

                                                                /* See Note #3a.                                        */
            pmem_align_dest = (      CPU_ALIGN *)((CPU_INT08U *)pmem_08_dest - sizeof(CPU_ALIGN) + 1);
            pmem_align_src  = (const CPU_ALIGN *)((CPU_INT08U *)pmem_08_src  - sizeof(CPU_ALIGN) + 1);
            while (size_rem      >=  sizeof(CPU_ALIGN)) {       /* While mem bufs aligned on CPU_ALIGN word boundaries, */
               *pmem_align_dest-- = *pmem_align_src--;          /* ... copy psrc to pdest with CPU_ALIGN-sized words.   */
                size_rem         -=  sizeof(CPU_ALIGN);
            }

            pmem_08_dest = (      CPU_INT08U *)pmem_align_dest + sizeof(CPU_ALIGN) - 1;
            pmem_08_src  = (const CPU_INT08U *)pmem_align_src  + sizeof(CPU_ALIGN) - 1;

        }
    }

    while (size_rem > 0) {                                      /* For unaligned mem bufs or trailing octets, ...       */
       *pmem_08_dest-- = *pmem_08_src--;                        /* ... copy psrc to pdest by octets.                    */
        size_rem      -=  sizeof(CPU_INT08U);
    }
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                              Mem_Cmp()
*
* Description : Verify that ALL data octets in two memory buffers are identical in sequence.
*
* Argument(s) : p1_mem      Pointer to first  memory buffer.
*
*               p2_mem      Pointer to second memory buffer.
*
*               size        Number of data buffer octets to compare (see Note #1).
*
* Return(s)   : DEF_YES, if 'size' number of data octets are identical in both memory buffers.
*
*               DEF_NO,  otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Null compares allowed (i.e. zero-length compares); 'DEF_YES' returned to indicate
*                   identical null compare.
*
*               (2) Many memory buffer comparisons vary ONLY in the least significant octets -- e.g.
*                   network address buffers.  Consequently, memory buffer comparison is more efficient
*                   if the comparison starts from the end of the memory buffers which will abort sooner
*                   on dissimilar memory buffers that vary only in the least significant octets.
*
*               (3) For best CPU performance, optimized to compare data buffers using 'CPU_ALIGN'-sized
*                   data words.
*
*                   (a) Since many word-aligned processors REQUIRE that multi-octet words be accessed on
*                       word-aligned addresses, 'CPU_ALIGN'-sized words MUST be accessed on 'CPU_ALIGN'd
*                       addresses.
*
*               (4) Modulo arithmetic is used to determine whether a memory buffer starts on a 'CPU_ALIGN'
*                   address boundary.
*
*                   Modulo arithmetic in ANSI-C REQUIREs operations performed on integer values.  Thus
*                   address values MUST be cast to an appropriately-sized integer value PRIOR to any
*                  'mem_align_mod' arithmetic operation.
*********************************************************************************************************
*/
/*$PAGE*/
CPU_BOOLEAN  Mem_Cmp (const  void        *p1_mem,
                      const  void        *p2_mem,
                             CPU_SIZE_T   size)
{
           CPU_SIZE_T    size_rem;
           CPU_ALIGN    *p1_mem_align;
           CPU_ALIGN    *p2_mem_align;
    const  CPU_INT08U   *p1_mem_08;
    const  CPU_INT08U   *p2_mem_08;
           CPU_DATA      i;
           CPU_DATA      mem_align_mod_1;
           CPU_DATA      mem_align_mod_2;
           CPU_BOOLEAN   mem_aligned;
           CPU_BOOLEAN   mem_cmp;


    if (size < 1) {                                             /* See Note #1.                                         */
        return (DEF_YES);
    }
    if (p1_mem == (void *)0) {
        return (DEF_NO);
    }
    if (p2_mem == (void *)0) {
        return (DEF_NO);
    }


    mem_cmp         =  DEF_YES;                                 /* Assume mem bufs are identical until cmp fails.       */
    size_rem        =  size;
                                                                /* Start @ end of mem bufs (see Note #2).               */
    p1_mem_08       = (const CPU_INT08U *)p1_mem + size;
    p2_mem_08       = (const CPU_INT08U *)p2_mem + size;
                                                                /* See Note #4.                                         */
    mem_align_mod_1 = (CPU_INT08U)((CPU_ADDR)p1_mem_08 % sizeof(CPU_ALIGN));
    mem_align_mod_2 = (CPU_INT08U)((CPU_ADDR)p2_mem_08 % sizeof(CPU_ALIGN));

    mem_aligned     = (mem_align_mod_1 == mem_align_mod_2) ? DEF_YES : DEF_NO;

    if (mem_aligned == DEF_YES) {                               /* If mem bufs' alignment offset equal, ...             */
                                                                /* ... optimize cmp for mem buf alignment.              */
        if (mem_align_mod_1 != 0u) {                            /* If trailing octets avail,                  ...       */
            i = mem_align_mod_1;
            while ((mem_cmp == DEF_YES) &&                      /* ... cmp mem bufs while identical &         ...       */
                   (size_rem > 0)       &&                      /* ... start mem buf cmp with trailing octets ...       */
                   (i        > 0)) {                            /* ... until next CPU_ALIGN word boundary.              */
                p1_mem_08--;
                p2_mem_08--;
                if (*p1_mem_08 != *p2_mem_08) {                 /* If ANY data octet(s) NOT identical, cmp fails.       */
                     mem_cmp = DEF_NO;
                }
                size_rem -= sizeof(CPU_INT08U);
                i--;
            }
        }

        if (mem_cmp == DEF_YES) {                               /* If cmp still identical, cmp aligned mem bufs.        */
            p1_mem_align = (CPU_ALIGN *)p1_mem_08;              /* See Note #3a.                                        */
            p2_mem_align = (CPU_ALIGN *)p2_mem_08;

            while ((mem_cmp  == DEF_YES) &&                     /* Cmp mem bufs while identical & ...                   */
                   (size_rem >= sizeof(CPU_ALIGN))) {           /* ... mem bufs aligned on CPU_ALIGN word boundaries.   */
                p1_mem_align--;
                p2_mem_align--;
                if (*p1_mem_align != *p2_mem_align) {           /* If ANY data octet(s) NOT identical, cmp fails.       */
                     mem_cmp = DEF_NO;
                }
                size_rem -= sizeof(CPU_ALIGN);
            }

            p1_mem_08 = (CPU_INT08U *)p1_mem_align;
            p2_mem_08 = (CPU_INT08U *)p2_mem_align;
        }
    }

    while ((mem_cmp == DEF_YES) &&                              /* Cmp mem bufs while identical ...                     */
           (size_rem > 0)) {                                    /* ... for unaligned mem bufs or trailing octets.       */
        p1_mem_08--;
        p2_mem_08--;
        if (*p1_mem_08 != *p2_mem_08) {                         /* If ANY data octet(s) NOT identical, cmp fails.       */
             mem_cmp = DEF_NO;
        }
        size_rem -= sizeof(CPU_INT08U);
    }

    return (mem_cmp);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                           Mem_HeapAlloc()
*
* Description : Allocate a memory block from the heap memory pool.
*
* Argument(s) : size            Size      of memory block to allocate (in octets).
*
*               align           Alignment of memory block to specific word boundary (in octets).
*
*               poctets_reqd    Optional pointer to a variable to ... :
*
*                                   (a) Return the number of octets required to successfully
*                                           allocate the memory block, if any error(s);
*                                   (b) Return 0, otherwise.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               LIB_MEM_ERR_NONE                Memory block successfully returned.
*                               LIB_MEM_ERR_INVALID_MEM_SIZE    Invalid memory size.
*                               LIB_MEM_ERR_INVALID_MEM_ALIGN   Invalid memory alignment.
*                               LIB_MEM_ERR_HEAP_EMPTY          Heap segment empty; NOT enough available
*                                                                   memory from heap.
*                               LIB_MEM_ERR_HEAP_OVF            Requested memory overflows heap memory.
*
* Return(s)   : Pointer to memory block, if NO error(s).
*
*               Pointer to NULL,         otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Pointers to variables that return values MUST be initialized PRIOR to all other
*                   validation or function handling in case of any error(s).
*
*               (2) 'pmem_pool' variables MUST ALWAYS be accessed exclusively in critical sections.
*********************************************************************************************************
*/
/*$PAGE*/
#if (LIB_MEM_CFG_ALLOC_EN == DEF_ENABLED)
void  *Mem_HeapAlloc (CPU_SIZE_T   size,
                      CPU_SIZE_T   align,
                      CPU_SIZE_T  *poctets_reqd,
                      LIB_ERR     *perr)
{
    MEM_POOL    *pmem_pool_heap;
    void        *pmem_addr;
    void        *pmem_blk;
    CPU_SIZE_T   octets_reqd_unused;
    CPU_SIZE_T   size_rem;
    CPU_SIZE_T   size_req;
    CPU_SR_ALLOC();


#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)                     /* ------------- VALIDATE RTN ERR PTR ------------- */
    if (perr == (LIB_ERR *)0) {
        CPU_SW_EXCEPTION((void *)0);
    }
#endif

                                                                    /* ------------ VALIDATE RTN OCTETS PTR ----------- */
    if (poctets_reqd == (CPU_SIZE_T *) 0) {                         /* If NOT avail, ...                                */
        poctets_reqd  = (CPU_SIZE_T *)&octets_reqd_unused;          /* ... re-cfg NULL rtn ptr to unused local var.     */
       (void)&octets_reqd_unused;                                   /* Prevent possible 'variable unused' warning.      */
    }
   *poctets_reqd = 0u;                                              /* Init octets req'd for err (see Note #1).         */


#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)                     /* ------------ VALIDATE HEAP MEM ALLOC ----------- */
    if (size < 1) {
       *perr = LIB_MEM_ERR_INVALID_MEM_SIZE;
        return ((void *)0);
    }

    if (align < 1) {
       *perr = LIB_MEM_ERR_INVALID_MEM_ALIGN;
        return ((void *)0);
    }
#endif

                                                                    /* -------------- ALLOC HEAP MEM BLK -------------- */
    pmem_pool_heap = &Mem_PoolHeap;

    CPU_CRITICAL_ENTER();

    pmem_addr = pmem_pool_heap->SegAddrNextAvail;
    size_rem  = pmem_pool_heap->SegSizeRem;
    size_req  = Mem_SegCalcTotSize(pmem_addr,
                                   1u,                              /* Calc alloc for single mem blk from heap.         */
                                   size,
                                   align);
#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
    if (size_req < 1) {                                             /* If req'd size ovf, ...                           */
        CPU_CRITICAL_EXIT();
       *poctets_reqd = size;                                        /* ... rtn add'l heap size needed.                  */
       *perr         = LIB_MEM_ERR_HEAP_OVF;
        return ((void *)0);
    }
#endif

    if (size_req > size_rem) {                                      /* If req'd size > rem heap size, ...               */
        CPU_CRITICAL_EXIT();
       *poctets_reqd = size_req - size_rem;                         /* ... rtn add'l heap size needed.                  */
       *perr         = LIB_MEM_ERR_HEAP_EMPTY;
        return ((void *)0);
    }

    pmem_blk = Mem_SegAlloc(pmem_pool_heap, size, align);
    if (pmem_blk == (void *)0) {                                    /* If mem blk NOT avail from heap, ...              */
        CPU_CRITICAL_EXIT();
       *poctets_reqd = size_req;                                    /* ... rtn add'l heap size needed.                  */
       *perr         = LIB_MEM_ERR_HEAP_EMPTY;
        return ((void *)0);
    }

    CPU_CRITICAL_EXIT();

   *perr =  LIB_MEM_ERR_NONE;

    return (pmem_blk);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        Mem_HeapGetSizeRem()
*
* Description : Get remaining heap memory size available to allocate.
*
* Argument(s) : align       Desired word boundary alignment (in octets) to return remaining memory size from.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                                                               ---- RETURNED BY Mem_PoolGetSizeRem() : ----
*                               LIB_MEM_ERR_NONE                Heap memory pool remaining size successfully
*                                                                   returned.
*                               LIB_MEM_ERR_NULL_PTR            Argument 'pmem_pool' passed a NULL pointer.
*                               LIB_MEM_ERR_INVALID_POOL        Invalid memory pool type.
*                               LIB_MEM_ERR_INVALID_MEM_ALIGN   Invalid memory alignment.
*
* Return(s)   : Remaining heap memory size (in octets), if NO error(s).
*
*               0,                                      otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (LIB_MEM_CFG_ALLOC_EN == DEF_ENABLED)
CPU_SIZE_T  Mem_HeapGetSizeRem (CPU_SIZE_T   align,
                                LIB_ERR     *perr)
{
    CPU_SIZE_T  size_rem;


    size_rem = Mem_SegGetSizeRem(&Mem_PoolHeap, align, perr);

    return (size_rem);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                         Mem_SegGetSizeRem()
*
* Description : Get memory pool's remaining segment size available to allocate.
*
* Argument(s) : pmem_pool   Pointer to a memory pool structure.
*
*               align       Desired word boundary alignment (in octets) to return remaining memory size from.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               LIB_MEM_ERR_NONE                Memory segment remaining size successfully
*                                                                   returned.
*                               LIB_MEM_ERR_NULL_PTR            Argument 'pmem_pool' passed a NULL pointer.
*                               LIB_MEM_ERR_INVALID_POOL        Invalid memory pool type.
*                               LIB_MEM_ERR_INVALID_MEM_ALIGN   Invalid memory alignment.
*
* Return(s)   : Remaining memory segment size (in octets) [see Note #1], if NO error(s).
*
*               0,                                                       otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Remaining size of memory segment returned from either :
*
*                   (a) Segment's configured dedicated memory, if any
*                   (b) Heap memory pool,                      otherwise
*
*               (2) 'pmem_pool' variables MUST ALWAYS be accessed exclusively in critical sections.
*********************************************************************************************************
*/
/*$PAGE*/
#if (LIB_MEM_CFG_ALLOC_EN == DEF_ENABLED)
CPU_SIZE_T  Mem_SegGetSizeRem (MEM_POOL    *pmem_pool,
                               CPU_SIZE_T   align,
                               LIB_ERR     *perr)
{
    MEM_POOL    *pmem_seg;
    MEM_POOL    *pmem_seg_size;
    CPU_SIZE_T   size_rem;
    CPU_SIZE_T   size_rem_mod;
    CPU_SIZE_T   seg_addr_mod;
    CPU_ADDR     seg_addr;
    CPU_SR_ALLOC();


#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
                                                                /* --------------- VALIDATE RTN ERR PTR --------------- */
    if (perr == (LIB_ERR *)0) {
        CPU_SW_EXCEPTION(0u);
    }
                                                                /* ---------------- VALIDATE MEM ALIGN ---------------- */
    if (align < 1) {
       *perr =  LIB_MEM_ERR_INVALID_MEM_ALIGN;
        return (0u);
    }
	if (align > DEF_ALIGN_MAX_NBR_OCTETS) {
	   *perr =  LIB_MEM_ERR_INVALID_MEM_ALIGN;
        return (0u);
    }
                                                                /* ---------------- VALIDATE MEM POOL ----------------- */
    if (pmem_pool == (MEM_POOL *)0) {                           /* Validate mem ptr.                                    */
       *perr =  LIB_MEM_ERR_NULL_PTR;
        return (0u);
    }
#endif

    CPU_CRITICAL_ENTER();

#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
    switch (pmem_pool->Type) {                                  /* Validate mem pool type.                              */
        case LIB_MEM_TYPE_HEAP:
        case LIB_MEM_TYPE_POOL:
             break;


        case LIB_MEM_TYPE_NONE:
        default:
             CPU_CRITICAL_EXIT();
            *perr =  LIB_MEM_ERR_INVALID_POOL;
             return (0u);                                       /* Prevent 'break NOT reachable' compiler warning.      */
    }
#endif

                                                                /* ------------- GET REM'ING MEM SEG SIZE ------------- */
    pmem_seg      =  pmem_pool->SegHeadPtr;                     /* Get mem pool's head seg.                             */
    pmem_seg_size = (pmem_seg->SegAddr != (void *)0)
                  ?  pmem_seg : &Mem_PoolHeap;                  /* See Note #1.                                         */
    size_rem      =  pmem_seg_size->SegSizeRem;                 /* Get mem seg's rem'ing mem size.                      */
    seg_addr      = (CPU_ADDR)pmem_seg_size->SegAddrNextAvail;

    CPU_CRITICAL_EXIT();

    if (align > 1) {                                            /* If align > 1 octet, ...                              */
        seg_addr_mod  =  seg_addr % align;
        size_rem_mod  = (seg_addr_mod > 0u) ? (align - seg_addr_mod) : 0u;
        size_rem     -=  size_rem_mod;                          /* ... adj rem'ing size by offset to align'd seg addr.  */
    }


   *perr =  LIB_MEM_ERR_NONE;

    return (size_rem);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                            Mem_PoolClr()
*
* Description : Clear a memory pool (see Note #1).
*
* Argument(s) : pmem_pool   Pointer to a memory pool structure to clear (see Note #2).
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               LIB_MEM_ERR_NONE                Memory pool successfully cleared.
*                               LIB_MEM_ERR_NULL_PTR            Argument 'pmem_pool' passed a NULL pointer.
*
* Return(s)   : none.
*
* Caller(s)   : Application,
*               Mem_PoolCreate().
*
* Note(s)     : (1) (a) Mem_PoolClr() ONLY clears a memory pool structure's variables & should ONLY be
*                       called to initialize a memory pool structure prior to calling Mem_PoolCreate().
*
*                   (b) Mem_PoolClr() does NOT deallocate memory from the memory pool or deallocate the
*                       memory pool itself & MUST NOT be called after calling Mem_PoolCreate() since
*                       this will likely corrupt the memory pool management.
*
*               (2) Assumes 'pmem_pool' points to a valid memory pool (if non-NULL).
*********************************************************************************************************
*/

#if (LIB_MEM_CFG_ALLOC_EN == DEF_ENABLED)
void  Mem_PoolClr (MEM_POOL  *pmem_pool,
                   LIB_ERR   *perr)
{

#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)                 /* -------------- VALIDATE RTN ERR  PTR --------------- */
    if (perr == (LIB_ERR *)0) {
        CPU_SW_EXCEPTION(;);
    }
#endif

                                                                /* -------------- VALIDATE MEM POOL PTR --------------- */
    if (pmem_pool == (MEM_POOL *)0) {
       *perr = LIB_MEM_ERR_NULL_PTR;
        return;
    }


    pmem_pool->Type             = (LIB_MEM_TYPE)LIB_MEM_TYPE_NONE;
    pmem_pool->SegHeadPtr       = (MEM_POOL   *)0;
    pmem_pool->SegPrevPtr       = (MEM_POOL   *)0;
    pmem_pool->SegNextPtr       = (MEM_POOL   *)0;
    pmem_pool->PoolPrevPtr      = (MEM_POOL   *)0;
    pmem_pool->PoolNextPtr      = (MEM_POOL   *)0;
    pmem_pool->PoolAddrStart    = (void       *)0;
    pmem_pool->PoolAddrEnd      = (void       *)0;
    pmem_pool->PoolPtrs         = (void      **)0;
    pmem_pool->PoolSize         = (CPU_SIZE_T  )0u;
    pmem_pool->BlkAlign         = (CPU_SIZE_T  )0u;
    pmem_pool->BlkSize          = (CPU_SIZE_T  )0u;
    pmem_pool->BlkNbr           = (CPU_SIZE_T  )0u;
    pmem_pool->BlkIx            = (MEM_POOL_IX )0u;
    pmem_pool->SegAddr          = (void       *)0;
    pmem_pool->SegAddrNextAvail = (void       *)0;
    pmem_pool->SegSizeTot       = (CPU_SIZE_T  )0u;
    pmem_pool->SegSizeRem       = (CPU_SIZE_T  )0u;


   *perr = LIB_MEM_ERR_NONE;
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                          Mem_PoolCreate()
*
* Description : (1) Create a memory pool :
*
*                   (a) Create    memory pool from heap or dedicated memory
*                   (b) Allocate  memory pool memory blocks
*                   (c) Update    memory pool table
*                   (d) Configure memory pool
*
*
*               (2) Memory pools are indexed by the Memory Segments they use.
*
*                   (a) The memory pool table is composed by a two-dimensional list :
*
*                       (1) Memory segments manage the following memory segment/pool information :
*
*                           (A) Memory segment base           address
*                           (B) Memory segment next available address
*                           (C) Memory segment total     size
*                           (D) Memory segment remaining size
*
*                       (2) Memory pools share memory from memory segments but do NOT manage any memory
*                           segment information.  To access the memory segment information, the head
*                           memory segment must be accessed via each memory pool's 'SegHeadPtr'.
*
*                   (b) In the diagram below, memory pools in vertical columns represent they share the same
*                       memory segment for the memory blocks they have.  The heads of the memory pool are
*                       linked horizontally to form a memory pool table.
*
*                       (1) 'Mem_PoolTbl' points to the head of the Memory Pool table.
*
*                       (2) Memory Pools' 'SegPrevPtr'  & 'SegNextPtr'  doubly-link each memory segment to
*                           form the list of memory segments.
*
*                       (3) Memory Pools' 'PoolPrevPtr' & 'PoolNextPtr' doubly-link the  memory pools of
*                           each memory segment.
*
*                   (c) New memory pools, which do not share a memory segment, are inserted in the Memory
*                       Segments Primary List.  The point of insertion is such to keep ascended order by
*                       memory segment base address.
*
*                   (d) Memory pool pointers to memory blocks 'PoolPtrs' must be allocated for each created
*                       memory pool.  These pointers are stored in the memory pool heap segment 'Mem_PoolHeap'.
*
*                       (1) A memory pool can also have its memory blocks allocated from the memory pool heap.
*                           'pmem_base_addr' must be set to NULL & 'mem_size' must be set to (0) to create the
*                           memory pool.
*
*
*                                        |                                                                 |
*                                        |<----------------------- Memory Segments ----------------------->|
*                                        |                         (see Note #2a1)                         |
*
*                                 Lowest Memory Segment                                      Highest Memory Segment
*                                     Base Address                                                Base Address
*                                    (see Note #2c)                                              (see Note #2c)
*
*                                           |             SegNextPtr             Heap Memory Pool       |
*                                           |          (see Note #2b2)            (see Note #2d)        |
*                                           |                     |                                     |
*                                           v                     |                      |              v
*                                                                 |                      v
*        ---          Head of Memory     -------        -------   v    -------        -------        -------
*         ^             Pool Table   --->|     |------->|     |------->|     |------->|     |------->|     |
*         |          (see Note #2b1)     |     |        |     |        |     |        |  H  |        |     |
*         |                              |     |<-------|     |<-------|     |<-------|  E  |<-------|     |
*         |                              |     |        |     |   ^    |     |        |  A  |        |     |
*         |                              |     |        |     |   |    |     |        |  P  |        |     |
*         |                              |     |        |     |   |    |     |        |     |        |     |
*         |                              -------        -------   |    -------        -------        -------
*         |                                | ^                    |      | ^
*         |                                | |            SegPrevPtr     | |
*         |                                v |         (see Note #2b2)   v |
*         |                              -------                       -------
*                                        |     |                       |     |
*    Memory Pools                        |     |                       |     |
*  (see Note #2a2)                       |     |                       |     |
*                                        |     |                       |     |
*         |                              |     |                       |     |
*         |                              -------                       -------
*         |                                | ^
*         |               PoolNextPtr ---> | | <--- PoolPrevPtr
*         |             (see Note #2b3)    v |    (see Note #2b3)
*         |                              -------
*         |                              |     |
*         |                              |     |
*         |                              |     |
*         |                              |     |
*         v                              |     |
*        ---                             -------
*
*$PAGE*
* Argument(s) : pmem_pool           Pointer to a memory pool structure to create (see Note #3).
*
*               pmem_base_addr      Memory pool base address :
*
*                                       (a)     Null address    Memory pool allocated from general-purpose heap.
*                                       (b) Non-null address    Memory pool allocated from dedicated memory
*                                                                   specified by its base address.
*
*               mem_size            Size      of memory pool segment          (in octets).
*
*               blk_nbr             Number    of memory pool blocks to create.
*
*               blk_size            Size      of memory pool blocks to create (in octets).
*
*               blk_align           Alignment of memory pool blocks to specific word boundary (in octets).
*
*               poctets_reqd        Optional pointer to a variable to ... :
*
*                                       (a) Return the number of octets required to successfully
*                                               allocate the memory pool, if any error(s);
*                                       (b) Return 0, otherwise.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               LIB_MEM_ERR_NONE                    Memory pool successfully created.
*
*                               LIB_MEM_ERR_HEAP_NOT_FOUND          Heap   segment NOT found.
*                               LIB_MEM_ERR_HEAP_EMPTY              Heap   segment empty; NOT enough available
*                                                                       memory from heap.
*                               LIB_MEM_ERR_HEAP_OVF                Requested memory overflows heap    memory.
*                               LIB_MEM_ERR_SEG_EMPTY               Memory segment empty; NOT enough available
*                                                                       memory from segment for memory pools.
*                               LIB_MEM_ERR_SEG_OVF                 Requested memory overflows segment memory.
*
*                               LIB_MEM_ERR_INVALID_SEG_SIZE        Invalid memory segment size.
*                               LIB_MEM_ERR_INVALID_SEG_OVERLAP     Memory segment overlaps other memory
*                                                                       segment(s) in memory pool table.
*                               LIB_MEM_ERR_INVALID_BLK_NBR         Invalid memory pool number of blocks.
*                               LIB_MEM_ERR_INVALID_BLK_SIZE        Invalid memory pool block size.
*                               LIB_MEM_ERR_INVALID_BLK_ALIGN       Invalid memory pool block alignment.
*
*                                                                   ------- RETURNED BY Mem_PoolClr() : -------
*                               LIB_MEM_ERR_NULL_PTR                Argument 'pmem_pool' passed a NULL pointer.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (3) Assumes 'pmem_pool' points to a valid memory pool (if non-NULL).
*
*               (4) Pointers to variables that return values MUST be initialized PRIOR to all other
*                   validation or function handling in case of any error(s).
*
*               (5) 'pmem_pool' variables MUST ALWAYS be accessed exclusively in critical sections.
*********************************************************************************************************
*/
/*$PAGE*/
#if (LIB_MEM_CFG_ALLOC_EN == DEF_ENABLED)
void  Mem_PoolCreate (MEM_POOL          *pmem_pool,
                      void              *pmem_base_addr,
                      CPU_SIZE_T         mem_size,
                      MEM_POOL_BLK_QTY   blk_nbr,
                      CPU_SIZE_T         blk_size,
                      CPU_SIZE_T         blk_align,
                      CPU_SIZE_T        *poctets_reqd,
                      LIB_ERR           *perr)
{
    MEM_POOL           *pmem_pool_heap;
    MEM_POOL           *pmem_pool_next;
    MEM_POOL           *pmem_seg;
    MEM_POOL           *pmem_seg_prev;
    MEM_POOL           *pmem_seg_next;
    void              **ppool_ptr;
    void               *pmem_blk;
    CPU_INT08U         *pmem_addr_ptrs;
    CPU_INT08U         *pmem_addr_pool;
    CPU_INT08U         *pmem_base_addr_start;
    CPU_INT08U         *pmem_base_addr_end;
    CPU_INT08U         *pmem_seg_addr_start;
    CPU_INT08U         *pmem_seg_addr_end;
    MEM_POOL_BLK_QTY    blk_rem;
    CPU_SIZE_T          octets_reqd_unused;
    CPU_SIZE_T          size_tot;
    CPU_SIZE_T          size_tot_ptrs;
    CPU_SIZE_T          size_tot_pool;
    CPU_SIZE_T          size_rem;
    CPU_SIZE_T          size_pool_ptrs;
    CPU_SIZE_T          i;
    CPU_SR_ALLOC();


#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)                     /* ------------- VALIDATE RTN ERR PTR ------------- */
    if (perr == (LIB_ERR *)0) {
        CPU_SW_EXCEPTION(;);
    }
#endif

                                                                    /* ------------ VALIDATE RTN OCTETS PTR ----------- */
    if (poctets_reqd == (CPU_SIZE_T *) 0) {                         /* If NOT avail, ...                                */
        poctets_reqd  = (CPU_SIZE_T *)&octets_reqd_unused;          /* ... re-cfg NULL rtn ptr to unused local var.     */
       (void)&octets_reqd_unused;                                   /* Prevent possible 'variable unused' warning.      */
    }
   *poctets_reqd = 0u;                                              /* Init octets req'd for err (see Note #4).         */



    Mem_PoolClr(pmem_pool, perr);                                   /* Init mem pool     for err (see Note #4).         */
    if (*perr != LIB_MEM_ERR_NONE) {
         return;
    }


                                                                    /* ----------- VALIDATE MEM POOL CREATE ----------- */
#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
    if (pmem_base_addr != (void *)0) {
        if (mem_size < 1) {
           *perr = LIB_MEM_ERR_INVALID_SEG_SIZE;
            return;
        }
    }

    if (blk_nbr < 1) {
       *perr = LIB_MEM_ERR_INVALID_BLK_NBR;
        return;
    }

    if (blk_size < 1) {
       *perr = LIB_MEM_ERR_INVALID_BLK_SIZE;
        return;
    }

    if (blk_align < 1) {
       *perr = LIB_MEM_ERR_INVALID_BLK_ALIGN;
        return;
    }
#endif


                                                                    /* ------------ VALIDATE MEM POOL TBL ------------- */
    if (Mem_PoolTbl == (MEM_POOL *)0) {
       *perr = LIB_MEM_ERR_HEAP_NOT_FOUND;
        return;
    }



/*$PAGE*/
                                                                    /* ---------------- CREATE MEM POOL --------------- */
    pmem_pool_heap = (MEM_POOL *)&Mem_PoolHeap;
    size_tot       = (CPU_SIZE_T) 0u;

    CPU_CRITICAL_ENTER();

    if (pmem_base_addr == (void *)0) {                              /* If no base addr, cfg mem pool from heap.         */
        pmem_seg        =  pmem_pool_heap;
        pmem_seg_prev   =  pmem_pool_heap;
        pmem_seg_next   =  pmem_pool_heap;

                                                                    /* --------------- VALIDATE MEM SEG --------------- */
                                                                    /* Calc tot mem   size for mem pool ptrs.           */
        pmem_addr_ptrs  = (CPU_INT08U *)pmem_pool_heap->SegAddrNextAvail;
        size_tot_ptrs   =  Mem_SegCalcTotSize((void     *)pmem_addr_ptrs,
                                              (CPU_SIZE_T)blk_nbr,
                                              (CPU_SIZE_T)sizeof(void *),
                                              (CPU_SIZE_T)sizeof(void *));
#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
        if (size_tot_ptrs < 1) {                                    /* If heap ovf, ...                                 */
            CPU_CRITICAL_EXIT();
           *perr = LIB_MEM_ERR_HEAP_OVF;                            /* ... rtn err but add'l heap size NOT avail.       */
            return;
        }
#endif
                                                                    /* Calc tot mem   size for mem blks.                */
        pmem_addr_pool  =  pmem_addr_ptrs + size_tot_ptrs;          /* Adj next avail addr for mem pool blks.           */
        size_tot_pool   =  Mem_SegCalcTotSize((void     *)pmem_addr_pool,
                                              (CPU_SIZE_T)blk_nbr,
                                              (CPU_SIZE_T)blk_size,
                                              (CPU_SIZE_T)blk_align);
#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
        if (size_tot_pool < 1) {                                    /* If heap ovf, ...                                 */
            CPU_CRITICAL_EXIT();
           *perr = LIB_MEM_ERR_HEAP_OVF;                            /* ... rtn err but add'l heap size NOT avail.       */
            return;
        }
#endif

        size_tot = size_tot_ptrs + size_tot_pool;

#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
        if ((size_tot < size_tot_ptrs) ||                           /* If heap ovf, ...                                 */
            (size_tot < size_tot_pool)) {
            CPU_CRITICAL_EXIT();
           *perr = LIB_MEM_ERR_HEAP_OVF;                            /* ... rtn err but add'l heap size NOT avail.       */
            return;
        }
#endif

        size_rem = pmem_pool_heap->SegSizeRem;
        if (size_tot > size_rem) {                                  /* If tot size > rem  size, ...                     */
            CPU_CRITICAL_EXIT();
           *poctets_reqd = size_tot - size_rem;                     /* ... rtn add'l heap size needed.                  */
           *perr         = LIB_MEM_ERR_HEAP_EMPTY;
            return;
        }

/*$PAGE*/
    } else {                                                        /* Else cfg mem pool from dedicated mem.            */
                                                                    /* -------- SRCH ALL MEM SEGS FOR MEM POOL -------- */
        pmem_base_addr_start = (CPU_INT08U *)pmem_base_addr;
        pmem_base_addr_end   = (CPU_INT08U *)pmem_base_addr + mem_size - 1;

#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
        if (pmem_base_addr_end < pmem_base_addr_start) {            /* Chk ovf of end addr.                             */
            CPU_CRITICAL_EXIT();
           *perr = LIB_MEM_ERR_INVALID_BLK_ADDR;
            return;
        }
#endif

        pmem_seg      = (MEM_POOL *)0;
        pmem_seg_prev = (MEM_POOL *)0;
        pmem_seg_next =  Mem_PoolTbl;

        while (pmem_seg_next != (MEM_POOL *)0) {                    /* Srch tbl for mem seg with same base addr/size.   */

            if ((pmem_base_addr == pmem_seg_next->SegAddr) &&       /* If same base addr/size found, ...                */
                (mem_size       == pmem_seg_next->SegSizeTot)) {

                 pmem_seg        = pmem_seg_next;                   /* ... mem seg already avail in tbl.                */
                 break;

            } else {
                pmem_seg_addr_start = (CPU_INT08U *)pmem_seg_next->SegAddr;
                pmem_seg_addr_end   = (CPU_INT08U *)pmem_seg_next->SegAddr + pmem_seg_next->SegSizeTot - 1;


                if (pmem_base_addr_end < pmem_seg_addr_start) {     /* If mem seg addr/size prior to next mem seg, ...  */
                    break;                                          /* ... new mem seg NOT avail in tbl.                */

                                                                    /* If mem seg overlaps prev mem seg(s) in tbl, ...  */
                } else if (((pmem_base_addr_start <= pmem_seg_addr_start)  &&
                            (pmem_base_addr_end   >= pmem_seg_addr_start)) ||
                           ((pmem_base_addr_start >= pmem_seg_addr_start)  &&
                            (pmem_base_addr_end   <= pmem_seg_addr_end  )) ||
                           ((pmem_base_addr_start <= pmem_seg_addr_end  )  &&
                            (pmem_base_addr_end   >= pmem_seg_addr_end  ))) {
                    CPU_CRITICAL_EXIT();
                   *perr = LIB_MEM_ERR_INVALID_SEG_OVERLAP;         /* ... rtn err.                                     */
                    return;
                }
            }
                                                                    /* If mem seg NOT found, adv to next mem seg.       */
            pmem_seg_prev = pmem_seg_next;
            pmem_seg_next = pmem_seg_next->SegNextPtr;
        }

        if (pmem_seg == (MEM_POOL *)0) {                            /* If mem seg NOT found, add    new  mem seg.       */
            pmem_seg                    = pmem_pool;
            pmem_pool->SegAddr          = pmem_base_addr;
            pmem_pool->SegAddrNextAvail = pmem_base_addr;
            pmem_pool->SegSizeTot       = mem_size;
            pmem_pool->SegSizeRem       = mem_size;
        }

/*$PAGE*/
                                                                    /* --------------- VALIDATE MEM SEG --------------- */
                                                                    /* Calc tot mem size for mem pool ptrs.             */
        pmem_addr_ptrs = (CPU_INT08U *)pmem_pool_heap->SegAddrNextAvail;
        size_tot_ptrs  =  Mem_SegCalcTotSize((void     *)pmem_addr_ptrs,
                                             (CPU_SIZE_T)blk_nbr,
                                             (CPU_SIZE_T)sizeof(void *),
                                             (CPU_SIZE_T)sizeof(void *));
#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
        if (size_tot_ptrs < 1) {                                    /* If heap ovf, ...                                 */
            CPU_CRITICAL_EXIT();
           *perr = LIB_MEM_ERR_HEAP_OVF;                            /* ... rtn err but add'l heap size NOT avail.       */
            return;
        }
#endif

        size_rem = pmem_pool_heap->SegSizeRem;
        if (size_tot_ptrs > size_rem) {                             /* If ptr size > rem  size, ...                     */
            CPU_CRITICAL_EXIT();
           *poctets_reqd = size_tot_ptrs - size_rem;                /* ... rtn add'l heap size needed.                  */
           *perr         = LIB_MEM_ERR_HEAP_EMPTY;
            return;
        }

                                                                    /* Calc tot mem size for mem blks.                  */
        pmem_addr_pool = (CPU_INT08U *)pmem_seg->SegAddrNextAvail;
        size_tot_pool  =  Mem_SegCalcTotSize((void     *)pmem_addr_pool,
                                             (CPU_SIZE_T)blk_nbr,
                                             (CPU_SIZE_T)blk_size,
                                             (CPU_SIZE_T)blk_align);
#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
        if (size_tot_pool < 1) {                                    /* If seg  ovf, ...                                 */
            CPU_CRITICAL_EXIT();
           *perr = LIB_MEM_ERR_SEG_OVF;                             /* ... rtn err but add'l seg  size NOT avail.       */
            return;
        }
#endif

        size_rem = pmem_seg->SegSizeRem;
        if (size_tot_pool > size_rem) {                             /* If tot size > rem  size, ...                     */
            CPU_CRITICAL_EXIT();
           *poctets_reqd = size_tot_pool - size_rem;                /* ... rtn add'l seg  size needed.                  */
           *perr         = LIB_MEM_ERR_SEG_EMPTY;
            return;
        }
    }


/*$PAGE*/
                                                                    /* ---------------- ALLOC MEM BLKs ---------------- */
    size_pool_ptrs = (CPU_SIZE_T)(blk_nbr * sizeof(void *));
                                                                    /* Alloc stk of ptrs for mem blks from heap.        */
    ppool_ptr      = (void **)Mem_SegAlloc((MEM_POOL *)pmem_pool_heap,
                                           (CPU_SIZE_T)size_pool_ptrs,
                                           (CPU_SIZE_T)sizeof(void *));
    if (ppool_ptr == (void **)0) {                                  /* If mem pool ptrs alloc failed, ...               */
        size_rem = pmem_pool_heap->SegSizeRem;
        CPU_CRITICAL_EXIT();
                                                                    /* ... rtn add'l heap size needed.                  */
        if (pmem_base_addr == (void *)0) {
            if (size_tot > size_rem) {
               *poctets_reqd = size_tot - size_rem;
            } else {
               *poctets_reqd = size_tot;
            }
        } else {
            if (size_pool_ptrs > size_rem) {
               *poctets_reqd = size_pool_ptrs - size_rem;
            } else {
               *poctets_reqd = size_pool_ptrs;
            }
        }
       *perr = LIB_MEM_ERR_HEAP_EMPTY;
        return;
    }

    for (i = 0u; i < (CPU_SIZE_T)blk_nbr; i++) {                    /* Alloc mem blks from mem seg.                     */
        pmem_blk = (void *)Mem_SegAlloc(pmem_seg, blk_size, blk_align);
        if (pmem_blk == (void *)0) {                                /* If    mem blks alloc failed, ...                 */
            pmem_addr_pool = (CPU_INT08U *)pmem_seg->SegAddrNextAvail;
            size_rem       = (CPU_SIZE_T  )pmem_seg->SegSizeRem;
            CPU_CRITICAL_EXIT();
            blk_rem        =  blk_nbr - (MEM_POOL_BLK_QTY)i;
            size_tot       =  Mem_SegCalcTotSize((void           *)pmem_addr_pool,
                                                 (MEM_POOL_BLK_QTY)blk_rem,
                                                 (CPU_SIZE_T      )blk_size,
                                                 (CPU_SIZE_T      )blk_align);
                                                                    /* ... rtn add'l seg  size needed.                  */
            if (size_tot > size_rem) {
               *poctets_reqd = size_tot - size_rem;
            } else {
               *poctets_reqd = size_tot;
            }
           *perr = LIB_MEM_ERR_SEG_EMPTY;
            return;
        }
        ppool_ptr[i] = pmem_blk;
    }


/*$PAGE*/
                                                                    /* ------------- UPDATE MEM POOL TBL -------------- */
    if (pmem_seg == pmem_pool) {                                    /* Add mem pool as new  mem pool tbl seg.           */
                                                                    /* Update cur  mem seg  links.                      */
        pmem_pool->SegPrevPtr = pmem_seg_prev;
        pmem_pool->SegNextPtr = pmem_seg_next;

        if (pmem_seg_prev != (MEM_POOL *)0) {                       /* Update prev mem seg  link.                       */
            pmem_seg_prev->SegNextPtr = pmem_pool;
        } else {
            Mem_PoolTbl               = pmem_pool;                  /* Update      mem tbl.                             */
        }

        if (pmem_seg_next != (MEM_POOL *)0) {                       /* Update next mem seg  link.                       */
            pmem_seg_next->SegPrevPtr = pmem_pool;
        }

    } else {                                                        /* Add mem pool into mem seg.                       */
                                                                    /* Update cur  mem pool links.                      */
        pmem_pool_next         = pmem_seg->PoolNextPtr;
        pmem_pool->PoolPrevPtr = pmem_seg;
        pmem_pool->PoolNextPtr = pmem_pool_next;

        pmem_seg->PoolNextPtr  = pmem_pool;                         /* Update prev mem pool link.                       */

        if (pmem_pool_next != (MEM_POOL *)0) {                      /* Update next mem pool link.                       */
            pmem_pool_next->PoolPrevPtr = pmem_pool;
        }
    }



                                                                    /* ----------------- CFG MEM POOL ----------------- */
    pmem_pool->Type          = (LIB_MEM_TYPE    ) LIB_MEM_TYPE_POOL;
    pmem_pool->SegHeadPtr    = (MEM_POOL       *) pmem_seg;
    pmem_pool->PoolAddrStart = (void           *) pmem_addr_pool;
    pmem_pool->PoolAddrEnd   = (void           *)(pmem_addr_pool + size_tot_pool - 1);
    pmem_pool->PoolPtrs      = (void          **) ppool_ptr;
    pmem_pool->PoolSize      = (CPU_SIZE_T      ) size_tot_pool;
    pmem_pool->BlkAlign      = (CPU_SIZE_T      ) blk_align;
    pmem_pool->BlkSize       = (CPU_SIZE_T      ) blk_size;
    pmem_pool->BlkNbr        = (MEM_POOL_BLK_QTY) blk_nbr;
    pmem_pool->BlkIx         = (MEM_POOL_IX     ) blk_nbr;


    CPU_CRITICAL_EXIT();

   *perr = LIB_MEM_ERR_NONE;
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                      Mem_PoolBlkGetNbrAvail()
*
* Description : Get memory pool’s remaining number of blocks available to allocate.
*
* Argument(s) : pmem_pool   Pointer to a memory pool structure.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               LIB_MEM_ERR_NONE                Memory pool available number of blocks
*                                                                   successfully returned.
*                               LIB_MEM_ERR_NULL_PTR            Argument 'pmem_pool' passed a NULL pointer.
*                               LIB_MEM_ERR_INVALID_POOL        Invalid memory pool type.
*
* Return(s)   : Remaining memory pool blocks (see Note #1), if NO error(s).
*
*               0,                                          otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) (a) Mem_PoolBlkGetNbrAvail() ONLY supports non-heap memory pools.
*                   (b) Mem_HeapGetSizeRem()/Mem_SegGetSizeRem() should be used for heap memory pool/segment.
*
*               (2) 'pmem_pool' variables MUST ALWAYS be accessed exclusively in critical sections.
*********************************************************************************************************
*/
/*$PAGE*/
#if (LIB_MEM_CFG_ALLOC_EN == DEF_ENABLED)
MEM_POOL_BLK_QTY  Mem_PoolBlkGetNbrAvail (MEM_POOL  *pmem_pool,
                                          LIB_ERR   *perr)
{
    MEM_POOL_BLK_QTY  nbr_blk_rem;
    CPU_SR_ALLOC();


#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
                                                                /* --------------- VALIDATE RTN ERR PTR --------------- */
    if (perr == (LIB_ERR *)0) {
        CPU_SW_EXCEPTION(0u);
    }
                                                                /* ---------------- VALIDATE MEM POOL ----------------- */
    if (pmem_pool == (MEM_POOL *)0) {                           /* Validate mem ptr.                                    */
       *perr =  LIB_MEM_ERR_NULL_PTR;
        return (0u);
    }
#endif

    CPU_CRITICAL_ENTER();

#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
    switch (pmem_pool->Type) {                                  /* Validate mem pool type.                              */
        case LIB_MEM_TYPE_POOL:
             break;


        case LIB_MEM_TYPE_NONE:
        case LIB_MEM_TYPE_HEAP:
        default:
             CPU_CRITICAL_EXIT();
            *perr =  LIB_MEM_ERR_INVALID_POOL;
             return (0u);                                       /* Prevent 'break NOT reachable' compiler warning.      */
    }
#endif

                                                                /* --------- GET REM'ING MEM POOL NBR BLK(S) ---------- */
    nbr_blk_rem = pmem_pool->BlkIx;

    CPU_CRITICAL_EXIT();


   *perr =  LIB_MEM_ERR_NONE;

    return (nbr_blk_rem);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                          Mem_PoolBlkGet()
*
* Description : Get a memory block from memory pool.
*
* Argument(s) : pmem_pool   Pointer to  memory pool to get memory block from.
*
*               size        Size of requested memory (in octets).
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               LIB_MEM_ERR_NONE                   Memory block successfully returned.
*                               LIB_MEM_ERR_POOL_EMPTY          NO memory blocks available in memory pool.
*
*                               LIB_MEM_ERR_NULL_PTR            Argument 'pmem_pool' passed a NULL pointer.
*                               LIB_MEM_ERR_INVALID_POOL        Invalid memory pool type.
*                               LIB_MEM_ERR_INVALID_BLK_SIZE    Invalid memory pool block size requested.
*                               LIB_MEM_ERR_INVALID_BLK_IX      Invalid memory pool block index.
*
* Return(s)   : Pointer to memory block, if NO error(s).
*
*               Pointer to NULL,         otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) 'pmem_pool' variables MUST ALWAYS be accessed exclusively in critical sections.
*********************************************************************************************************
*/
/*$PAGE*/
#if (LIB_MEM_CFG_ALLOC_EN == DEF_ENABLED)
void  *Mem_PoolBlkGet (MEM_POOL    *pmem_pool,
                       CPU_SIZE_T   size,
                       LIB_ERR     *perr)
{
    void  *pmem_blk;
    CPU_SR_ALLOC();


#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)                     /* ------------- VALIDATE RTN ERR PTR ------------- */
    if (perr == (LIB_ERR *)0) {
        CPU_SW_EXCEPTION((void *)0);
    }
#endif

                                                                    /* ------------ VALIDATE MEM POOL GET ------------- */
#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
    if (pmem_pool == (MEM_POOL *)0) {                               /* Validate mem ptr.                                */
       *perr = LIB_MEM_ERR_NULL_PTR;
        return ((void *)0);
    }

    if (size < 1) {                                                 /* Validate req'd size as non-NULL.                 */
       *perr = LIB_MEM_ERR_INVALID_BLK_SIZE;
        return ((void *)0);
    }
#endif

    CPU_CRITICAL_ENTER();

#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
    if (pmem_pool->Type != LIB_MEM_TYPE_POOL) {                     /* Validate mem pool type.                          */
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_INVALID_POOL;
        return ((void *)0);
    }

    if (size > pmem_pool->BlkSize) {                                /* Validate req'd size <= mem pool blk size.        */
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_INVALID_BLK_SIZE;
        return ((void *)0);
    }
#endif

   (void)&size;                                                     /* Prevent possible 'variable unused' warning.      */

    if (pmem_pool->BlkIx < 1) {                                     /* Validate mem pool as NOT empty.                  */
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_POOL_EMPTY;
        return ((void *)0);
    }

    if (pmem_pool->BlkIx > pmem_pool->BlkNbr) {                     /* Validate mem pool ix NOT corrupt.                */
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_INVALID_BLK_IX;
        return ((void *)0);
    }

                                                                    /* ------------ GET MEM BLK FROM POOL ------------- */
    pmem_pool->BlkIx--;
    pmem_blk = pmem_pool->PoolPtrs[pmem_pool->BlkIx];

    CPU_CRITICAL_EXIT();

   *perr =  LIB_MEM_ERR_NONE;

    return (pmem_blk);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                      Mem_PoolBlkGetUsedAtIx()
*
* Description : Get a used memory block from memory pool, by index.
*
* Argument(s) : pmem_pool   Pointer to memory pool to get memory block from.
*
*               used_ix     Index of the used memory block to get.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               LIB_MEM_ERR_NONE                    Memory block successfully returned.
*                               LIB_MEM_ERR_POOL_FULL           All memory blocks available in memory pool.
*
*                               LIB_MEM_ERR_NULL_PTR            Argument 'pmem_pool' passed a NULL pointer.
*                               LIB_MEM_ERR_INVALID_POOL        Invalid memory pool type.
*                               LIB_MEM_ERR_INVALID_BLK_IX      Invalid memory pool block index.
*
* Return(s)   : Pointer to memory block, if NO error(s).
*
*               Pointer to NULL,         otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) 'pmem_pool' variables MUST ALWAYS be accessed exclusively in critical sections.
*
*               (2) The returned index can be altered when Mem_PoolBlkFree() is called. This index must
*                   only be used in conjunction with Mem_PoolBlkGetUsedAtIx() if holding a proper
*                   lock to avoid the index to be modified.
*********************************************************************************************************
*/
/*$PAGE*/
#if (LIB_MEM_CFG_ALLOC_EN == DEF_ENABLED)
void  *Mem_PoolBlkGetUsedAtIx (MEM_POOL          *pmem_pool,
                               MEM_POOL_IX        used_ix,
                               LIB_ERR           *perr)
{
    MEM_POOL_IX   blk_ix;
    void         *pmem_blk;
    CPU_SR_ALLOC();


#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)                     /* ------------- VALIDATE RTN ERR PTR ------------- */
    if (perr == (LIB_ERR *)0) {
        CPU_SW_EXCEPTION((void *)0);
    }
#endif

                                                                    /* ------------ VALIDATE MEM POOL GET ------------- */
#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
    if (pmem_pool == (MEM_POOL *)0) {                               /* Validate mem ptr.                                */
       *perr = LIB_MEM_ERR_NULL_PTR;
        return ((void *)0);
    }
#endif

    CPU_CRITICAL_ENTER();

#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
    if (pmem_pool->Type != LIB_MEM_TYPE_POOL) {                     /* Validate mem pool type.                          */
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_INVALID_POOL;
        return ((void *)0);
    }

    if (pmem_pool->BlkIx >= pmem_pool->BlkNbr) {                    /* Validate mem pool as NOT full.                   */
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_INVALID_BLK_IX;
        return ((void *)0);
    }
#endif

    blk_ix = pmem_pool->BlkNbr - used_ix - 1u;

    if (blk_ix >= pmem_pool->BlkNbr) {                              /* Validate ix range.                               */
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_INVALID_BLK_IX;
        return ((void *)0);
    }

    if (blk_ix < pmem_pool->BlkIx) {
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_INVALID_BLK_IX;
        return ((void *)0);
    }
                                                                    /* ------------ GET MEM BLK FROM POOL ------------- */
    pmem_blk = pmem_pool->PoolPtrs[blk_ix];

    CPU_CRITICAL_EXIT();

   *perr =  LIB_MEM_ERR_NONE;

    return (pmem_blk);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                          Mem_PoolBlkFree()
*
* Description : Free a memory block to memory pool.
*
* Argument(s) : pmem_pool   Pointer to memory pool to free memory block.
*
*               pmem_blk    Pointer to memory block address to free.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               LIB_MEM_ERR_NONE                            Memory block successfully freed.
*                               LIB_MEM_ERR_POOL_FULL                   ALL memory blocks already available in
*                                                                           memory pool.
*
*                               LIB_MEM_ERR_NULL_PTR                    Argument 'pmem_pool'/'pmem_blk' passed
*                                                                           a NULL pointer.
*                               LIB_MEM_ERR_INVALID_POOL                Invalid memory pool  type.
*                               LIB_MEM_ERR_INVALID_BLK_ADDR            Invalid memory block address.
*                               LIB_MEM_ERR_INVALID_BLK_ADDR_IN_POOL            Memory block address already
*                                                                            in memory pool.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) 'pmem_pool' variables MUST ALWAYS be accessed exclusively in critical sections.
*********************************************************************************************************
*/
/*$PAGE*/
#if (LIB_MEM_CFG_ALLOC_EN == DEF_ENABLED)
void  Mem_PoolBlkFree (MEM_POOL  *pmem_pool,
                       void      *pmem_blk,
                       LIB_ERR   *perr)
{
    void         *p_addr;
    CPU_BOOLEAN   addr_valid;
    MEM_POOL_IX   i;
    CPU_SR_ALLOC();


#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)                     /* ------------- VALIDATE RTN ERR PTR ------------- */
    if (perr == (LIB_ERR *)0) {
        CPU_SW_EXCEPTION(;);
    }
#endif

                                                                    /* ------------ VALIDATE MEM POOL FREE ------------ */
#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)                     /* Validate mem ptrs.                               */
    if (pmem_pool == (MEM_POOL *)0) {
       *perr = LIB_MEM_ERR_NULL_PTR;
        return;
    }

    if (pmem_blk == (void *)0) {
       *perr = LIB_MEM_ERR_NULL_PTR;
        return;
    }
#endif

    CPU_CRITICAL_ENTER();

#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
    if (pmem_pool->Type != LIB_MEM_TYPE_POOL) {                     /* Validate mem pool type.                          */
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_INVALID_POOL;
        return;
    }

    addr_valid = Mem_PoolBlkIsValidAddr(pmem_pool, pmem_blk);       /* Validate mem blk as valid pool blk addr.         */
    if (addr_valid != DEF_OK) {
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_INVALID_BLK_ADDR;
        return;
    }

    for (i = 0u; i < pmem_pool->BlkIx; i++) {                       /* Validate mem blk  NOT already in pool.           */
        if (pmem_blk == pmem_pool->PoolPtrs[i]) {
            CPU_CRITICAL_EXIT();
           *perr = LIB_MEM_ERR_INVALID_BLK_ADDR_IN_POOL;
            return;
        }
    }
#endif

    if (pmem_pool->BlkIx >= pmem_pool->BlkNbr) {                    /* Validate mem pool NOT already full.              */
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_POOL_FULL;
        return;
    }

                                                                    /* ------------- FREE MEM BLK TO POOL ------------- */
    addr_valid = DEF_NO;
    for (i = pmem_pool->BlkIx; i < pmem_pool->BlkNbr; i++) {        /* Find ix of mem blk to free.                      */
        p_addr = pmem_pool->PoolPtrs[i];
        if (p_addr == pmem_blk) {
            addr_valid = DEF_YES;
            break;
        }
    }
                                                                    /* Swap addr of mem blk to free in tbl.             */
    if (addr_valid == DEF_YES) {
        pmem_pool->PoolPtrs[i] = pmem_pool->PoolPtrs[pmem_pool->BlkIx];
    } else {
#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_INVALID_POOL;
        return;
#endif
    }

                                                                    /* Free mem blk.                                    */
    pmem_pool->PoolPtrs[pmem_pool->BlkIx] = pmem_blk;
    pmem_pool->BlkIx++;

    CPU_CRITICAL_EXIT();

   *perr = LIB_MEM_ERR_NONE;
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                          Mem_PoolBlkIxGet()
*
* Description : Get temporary index of a memory block in a memory pool.
*
* Argument(s) : pmem_pool   Pointer to memory pool.
*
*               pmem_blk    Pointer to memory block to get index for.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               LIB_MEM_ERR_NONE                        Memory block successfully freed.
*                               LIB_MEM_ERR_POOL_FULL                   ALL memory blocks already available in
*                                                                           memory pool.
*
*                               LIB_MEM_ERR_NULL_PTR                    Argument 'pmem_pool'/'pmem_blk' passed
*                                                                           a NULL pointer.
*                               LIB_MEM_ERR_INVALID_POOL                Invalid memory pool  type.
*                               LIB_MEM_ERR_INVALID_BLK_ADDR            Invalid memory block address.
*                               LIB_MEM_ERR_INVALID_BLK_ADDR_IN_POOL            Memory block address already
*                                                                            in memory pool.
*
* Return(s)   : Index of the memory block.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) 'pmem_pool' variables MUST ALWAYS be accessed exclusively in critical sections.
*
*               (2) The returned index can be altered when Mem_PoolBlkFree() is called. This index must
*                   only be used in conjunction with Mem_PoolBlkGetUsedAtIx() if holding a proper
*                   lock to avoid the index to be modified.
*********************************************************************************************************
*/
/*$PAGE*/
#if (LIB_MEM_CFG_ALLOC_EN == DEF_ENABLED)
MEM_POOL_IX  Mem_PoolBlkIxGet (MEM_POOL  *pmem_pool,
                               void      *pmem_blk,
                               LIB_ERR   *perr)
{
    void         *p_addr;
    CPU_BOOLEAN   addr_valid;
    MEM_POOL_IX   i;
    MEM_POOL_IX   pool_ix;
    MEM_POOL_IX   invalid_ix;
    CPU_SR_ALLOC();


    invalid_ix = DEF_GET_U_MAX_VAL(MEM_POOL_IX);
#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)                     /* ------------- VALIDATE RTN ERR PTR ------------- */
    if (perr == (LIB_ERR *)0) {
        CPU_SW_EXCEPTION(invalid_ix);
    }
#endif

                                                                    /* ------------ VALIDATE MEM POOL FREE ------------ */
#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)                     /* Validate mem ptrs.                               */
    if (pmem_pool == (MEM_POOL *)0) {
       *perr = LIB_MEM_ERR_NULL_PTR;
        return (invalid_ix);
    }

    if (pmem_blk == (void *)0) {
       *perr = LIB_MEM_ERR_NULL_PTR;
        return (invalid_ix);
    }
#endif

    CPU_CRITICAL_ENTER();

#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
    if (pmem_pool->Type != LIB_MEM_TYPE_POOL) {                     /* Validate mem pool type.                          */
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_INVALID_POOL;
        return(invalid_ix);
    }

    addr_valid = Mem_PoolBlkIsValidAddr(pmem_pool, pmem_blk);       /* Validate mem blk as valid pool blk addr.         */
    if (addr_valid != DEF_OK) {
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_INVALID_BLK_ADDR;
        return (invalid_ix);
    }

    for (i = 0u; i < pmem_pool->BlkIx; i++) {                       /* Validate mem blk  NOT already in pool.           */
        if (pmem_blk == pmem_pool->PoolPtrs[i]) {
            CPU_CRITICAL_EXIT();
           *perr = LIB_MEM_ERR_INVALID_BLK_ADDR_IN_POOL;
            return (invalid_ix);
        }
    }
#endif

    if (pmem_pool->BlkIx >= pmem_pool->BlkNbr) {                    /* Validate mem pool NOT full.                      */
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_POOL_FULL;
        return (invalid_ix);
    }

    addr_valid = DEF_NO;
    for (i = pmem_pool->BlkIx; i < pmem_pool->BlkNbr; i++) {        /* Find ix of mem blk.                              */
        p_addr = pmem_pool->PoolPtrs[i];
        if (p_addr == pmem_blk) {
            addr_valid = DEF_YES;
            break;
        }
    }
                                                                    /* Return ix of mem blk in tbl.                     */
    if (addr_valid == DEF_YES) {
        pool_ix = pmem_pool->BlkNbr - 1 - i;
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_NONE;
        return (pool_ix);
    } else {
        CPU_CRITICAL_EXIT();
       *perr = LIB_MEM_ERR_INVALID_POOL;
        return (invalid_ix);
    }

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
*                                      Mem_PoolBlkIsValidAddr()
*
* Description : Calculates if a given memory block address is valid for the memory pool.
*
* Argument(s) : pmem_pool   Pointer to memory pool structure to validate memory block address.
*               ---------   Argument validated in Mem_PoolBlkFree().
*
*               pmem_blk    Pointer to memory block address to validate.
*               --------    Argument validated in Mem_PoolBlkFree().
*
* Return(s)   : DEF_YES, if valid memory pool block address.
*
*               DEF_NO,  otherwise.
*
* Caller(s)   : Mem_PoolBlkFree().
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if ((LIB_MEM_CFG_ALLOC_EN       == DEF_ENABLED) && \
     (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED))
static  CPU_BOOLEAN  Mem_PoolBlkIsValidAddr (MEM_POOL  *pmem_pool,
                                             void      *pmem_blk)
{
    CPU_INT08U   *ppool_addr_first;
    void         *ppool_addr_start;
    void         *ppool_addr_end;
    CPU_SIZE_T    align_offset;
    CPU_SIZE_T    blk_align;
    CPU_SIZE_T    blk_align_offset;
    CPU_SIZE_T    blk_size;
    CPU_SIZE_T    mem_align;
    CPU_SIZE_T    mem_align_offset;
    CPU_SIZE_T    mem_diff;
    CPU_BOOLEAN   addr_valid;


    ppool_addr_start = pmem_pool->PoolAddrStart;
    ppool_addr_end   = pmem_pool->PoolAddrEnd;

    if ((pmem_blk < ppool_addr_start) ||
        (pmem_blk > ppool_addr_end)) {
        return (DEF_NO);
    }

    blk_align      = (CPU_SIZE_T)pmem_pool->BlkAlign;
    align_offset   = (CPU_SIZE_T)((CPU_ADDR)ppool_addr_start % blk_align);
    if (align_offset != 0u) {
        mem_align_offset = blk_align - align_offset;
    } else {
        mem_align_offset = 0u;
    }

    blk_size     = pmem_pool->BlkSize;
    align_offset = blk_size % blk_align;
    if (align_offset != 0u) {
        blk_align_offset = blk_align - align_offset;
    } else {
        blk_align_offset = 0u;
    }

    ppool_addr_first = (CPU_INT08U *)((CPU_INT08U *)ppool_addr_start + mem_align_offset);
    mem_diff         = (CPU_SIZE_T  )((CPU_INT08U *)pmem_blk         - ppool_addr_first);
    mem_align        = (CPU_SIZE_T  )(              blk_size         + blk_align_offset);

    addr_valid       = ((mem_diff % mem_align) == 0u) ? DEF_YES : DEF_NO;

    return (addr_valid);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                        Mem_SegCalcTotSize()
*
* Description : (1) Calculates total memory segment size for number of blocks with specific size & alignment :
*
*
*                       -----                     ======================  ---
*                         ^       Mem Addr  --->  |  /  /  /  /  /  /  |   ^
*                         |    (see Note #1a)     | /  /  /  /  /  /  /|   |    Mem Align Offset
*                         |                       |/  /  /  /  /  /  / |   |  (see Notes #1e & #2a)
*                         |                       |  /  /  /  /  /  /  |   v
*                         |                       ======================  ---
*                         |                       |                    |   ^
*                         |                       |                    |   |
*                         |                       |     Mem Blk #1     |   |        Blk Size
*                         |                       |                    |   |     (see Note #1c)
*                         |                       |                    |   v
*                         |                       ----------------------  ---
*                         |                       |  /  /  /  /  /  /  |   ^
*                         |                       | /  /  /  /  /  /  /|   |    Blk Align Offset
*                         |                       |/  /  /  /  /  /  / |   |  (see Notes #1f & #2b)
*                         |                       |  /  /  /  /  /  /  |   v
*                         |                       ======================  ---
*                                                 |         .          |
*                     Total Size                  |         .          |
*                   (see Note #2c)                |         .          |
*                                                 ======================  ---
*                         |                       |                    |   ^
*                         |                       |                    |   |
*                         |                       |   Mem Blk #N - 1   |   |        Blk Size
*                         |                       |                    |   |     (see Note #1c)
*                         |                       |                    |   v
*                         |                       ----------------------  ---
*                         |                       |  /  /  /  /  /  /  |   ^
*                         |                       | /  /  /  /  /  /  /|   |    Blk Align Offset
*                         |                       |/  /  /  /  /  /  / |   |  (see Notes #1f & #2b)
*                         |                       |  /  /  /  /  /  /  |   v
*                         |                       ======================  ---
*                         |                       |                    |   ^
*                         |                       |                    |   |
*                         |                       |     Mem Blk #N     |   |        Blk Size
*                         |                       |                    |   |     (see Note #1c)
*                         v                       |                    |   v
*                       -----                     ======================  ---
*
*               where
*
*                   (a) Mem Addr            Memory address of the beginning of the memory block ('pmem_addr')
*
*                   (b) N                   Number of memory blocks to allocate ('blk_nbr')
*
*                   (c) Blk Size            Size   of memory block  to allocate ('blk_size')
*
*                   (d) Align               Required block memory alignment     ('blk_align')
*
*                   (e) Mem Align Offset    Offset required to align first memory block
*
*                   (f) Blk Align Offset    Offset required to align every memory block
*
*
*               (2) The total size is calculated based on the following equations :
*
*                                            { (1) Align - (Mem Addr % Align) , if memory address is not aligned
*                   (a) Mem Align Offset  =  {
*                                            { (2) 0                          , if memory address is     aligned
*
*
*                                            { (1) Align - (Size     % Align) , if memory block   is not aligned
*                   (b) Blk Align Offset  =  {
*                                            { (2) 0                          , if memory block   is     aligned
*
*
*                   (c) Total Size        =   Mem Align Offset
*                                         + ((Blk Size + Blk Align Offset) * (N - 1))
*                                         +   Blk Size
*
*
* Argument(s) : pmem_addr   Memory address of the beginning of the memory block.
*
*               blk_nbr     Number of memory blocks to allocate.
*               -------     Argument checked in Mem_HeapAlloc(),
*                                               Mem_PoolCreate().
*
*               blk_size    Size   of memory block  to allocate.
*               --------    Argument checked in Mem_HeapAlloc(),
*                                               Mem_PoolCreate().
*
*               blk_align   Required block word-boundary memory alignment (in octets).
*               ---------   Argument checked in Mem_HeapAlloc(),
*                                               Mem_PoolCreate().
*
* Return(s)   : Total size of memory segment used to allocate the number of blocks, if NO error(s).
*
*               0,                                                                  otherwise.
*$PAGE*
* Caller(s)   : Mem_HeapAlloc(),
*               Mem_PoolCreate().
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (LIB_MEM_CFG_ALLOC_EN == DEF_ENABLED)
static  CPU_SIZE_T  Mem_SegCalcTotSize (void              *pmem_addr,
                                        MEM_POOL_BLK_QTY   blk_nbr,
                                        CPU_SIZE_T         blk_size,
                                        CPU_SIZE_T         blk_align)
{
#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
    CPU_SIZE_T  blk_size_mem_aligned;
    CPU_SIZE_T  blk_size_aligned;
    CPU_SIZE_T  blk_size_aligned_nbr;
    CPU_SIZE_T  blk_size_tot;
#endif
    CPU_SIZE_T  align_offset;
    CPU_SIZE_T  mem_align_offset;
    CPU_SIZE_T  blk_align_offset;
    CPU_SIZE_T  size_tot;

                                                                    /* Calc mem align (see Note #2a).                   */
    align_offset = (CPU_ADDR)pmem_addr % blk_align;
    if (align_offset != 0u) {
        mem_align_offset = blk_align - align_offset;
    } else {
        mem_align_offset = 0u;
    }
                                                                    /* Calc blk align (see Note #2b).                   */
    align_offset = blk_size % blk_align;
    if (align_offset != 0u) {
        blk_align_offset = blk_align - align_offset;
    } else {
        blk_align_offset = 0u;
    }
                                                                    /* Calc tot size  (see Note #2c).                   */
    size_tot = mem_align_offset + ((blk_size + blk_align_offset) * ((CPU_SIZE_T)blk_nbr - 1)) + blk_size;

#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)                     /* Chk ovf of tot size = A + [(B + C) * D] + E      */
    blk_size_mem_aligned = mem_align_offset + blk_size;             /* Chk ovf of A + E :                               */
    if ((blk_size_mem_aligned < mem_align_offset) ||
        (blk_size_mem_aligned < blk_size)) {
        return (0u);
    }

    if (blk_nbr > 1) {
        blk_size_aligned = blk_size + blk_align_offset;
        if ((blk_size_aligned < blk_align_offset) ||                /* Chk ovf of      (B + C) :                        */
            (blk_size_aligned < blk_size)) {
            return (0u);
        }

        blk_size_aligned_nbr = blk_size_aligned * ((CPU_SIZE_T)blk_nbr - 1);
        if ((blk_size_aligned_nbr < blk_size_aligned) ||            /* Chk ovf of     [(B + C) * D] :                   */
            (blk_size_aligned_nbr < blk_align_offset) ||
            (blk_size_aligned_nbr < blk_size)) {
            return (0u);
        }

        blk_size_tot = blk_size_aligned_nbr + blk_size;
        if ((blk_size_tot < blk_size_aligned_nbr) ||                /* Chk ovf of     [(B + C) * D] + E :               */
            (blk_size_tot < blk_size)) {
            return (0u);
        }

        if ((size_tot < blk_size_mem_aligned) ||                    /* Chk ovf of A + [(B + C) * D] + E :               */
            (size_tot < blk_size_aligned_nbr) ||
            (size_tot < blk_size_tot)) {
            return (0u);
        }
    }
#endif

    return (size_tot);
}
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                           Mem_SegAlloc()
*
* Description : Allocates memory from specific segment.
*
* Argument(s) : pmem_pool   Pointer to memory pool structure containing segment information.
*               ---------   Argument validated in Mem_HeapAlloc(),
*                                                 Mem_PoolCreate().
*
*               size        Size of memory to allocate.
*               ----        Argument validated in Mem_HeapAlloc(),
*                                                 Mem_PoolCreate().
*
*               align       Required starting word-boundary memory alignment (in octets).
*               -----       Argument validated in Mem_HeapAlloc(),
*                                                 Mem_PoolCreate().
*
* Return(s)   : Pointer to allocated memory, if NO error(s).
*
*               Pointer to NULL,             otherwise.
*
* Caller(s)   : Mem_HeapAlloc(),
*               Mem_PoolCreate().
*
* Note(s)     : (1) Allocated memory from the specific segment is NEVER freed after allocation.
*
*               (2) 'pmem_pool' variables MUST ALWAYS be accessed exclusively in critical sections.
*
*                   (a) However, this function is already called within critical sections.
*********************************************************************************************************
*/

#if (LIB_MEM_CFG_ALLOC_EN == DEF_ENABLED)
static  void  *Mem_SegAlloc (MEM_POOL    *pmem_pool,
                             CPU_SIZE_T   size,
                             CPU_SIZE_T   align)
{
    CPU_INT08U  *pmem_addr;
    CPU_INT08U  *pmem_addr_next;
    CPU_SIZE_T   mem_align;
    CPU_SIZE_T   align_offset;
    CPU_SIZE_T   size_tot;


    pmem_addr = (CPU_INT08U *)pmem_pool->SegAddrNextAvail;

    mem_align = (CPU_SIZE_T)((CPU_ADDR)pmem_addr % align);          /* Calc mem align.                                  */

    if (mem_align != 0u) {
        align_offset = align - mem_align;
    } else {
        align_offset = 0u;
    }

    size_tot = align_offset + size;
    if (size_tot > pmem_pool->SegSizeRem) {                         /* If insufficient mem seg size rem, ...            */
        return ((void *)0);                                         /* ... rtn NULL.                                    */
    }

#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
    if ((size_tot < align_offset) ||                                /* If size ovf, ...                                 */
        (size_tot < size)) {
        return ((void *)0);                                         /* ... rtn NULL.                                    */
    }
#endif

    pmem_addr_next = pmem_addr + size_tot;

#if (LIB_MEM_CFG_ARG_CHK_EXT_EN == DEF_ENABLED)
    if (pmem_addr_next < pmem_addr) {                               /* If addr ovf, ...                                 */
        return ((void *)0);                                         /* ... rtn NULL.                                    */
    }
#endif

    pmem_addr += align_offset;                                      /* Align mem addr.                                  */

    pmem_pool->SegAddrNextAvail  = (void     *)pmem_addr_next;      /* Adv next avail addr.                             */
    pmem_pool->SegSizeRem       -= (CPU_SIZE_T)size_tot;            /* Adj rem mem seg size.                            */

    return ((void *)pmem_addr);
}
#endif

