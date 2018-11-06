/* 
 *   MIRACL compiler/hardware definitions - mirdef.h
 *   This version suitable for use with most 32-bit computers
 *   e.g. 80386+ PC, VAX, ARM etc. Assembly language versions of muldiv,
 *   muldvm, muldvd and muldvd2 will be necessary. See mrmuldv.any 
 *
 *   Also suitable for DJGPP GNU C Compiler
 *   ... but change __int64 to long long
 *   Copyright (c) 1988-2006 Shamus Software Ltd.
 */

#define MIRACL 32
#ifdef WIN32
#define MR_LITTLE_ENDIAN    /* This may need to be changed        */
#else
#define MR_BIG_ENDIAN
#endif
#define mr_utype int
                            /* the underlying type is usually int *
                             * but see mrmuldv.any                */

#define MR_IBITS      32    /* bits in int  */
#define MR_LBITS      32    /* bits in long */
#define MR_FLASH      52      
                            /* delete this definition if integer  *
                             * only version of MIRACL required    */
                            /* Number of bits per double mantissa */

#define mr_unsign32 unsigned int
                            /* 32 bit unsigned type               */
#ifdef WIN32
#define mr_unsign64 unsigned __int64
#define mr_dltype __int64   /* ... or long long for Unix/Linux */
#else
#define mr_unsign64 unsigned long long
#define mr_dltype long long
#endif


#define MAXBASE ((mr_small)1<<(MIRACL-1))

#ifdef WIN32
// Windows¶àÏß³Ì
#define MR_WINDOWS_MT
#else
#define MR_NOASM
#endif