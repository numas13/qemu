#ifndef TARGET_GF_CPU_USER_H
#define TARGET_GF_CPU_USER_H

#if defined(TARGET_GFRISCV32)
#define xRA 1   /* return address (aka link register) */
#define xSP 2   /* stack pointer */
#define xGP 3   /* global pointer */
#define xTP 4   /* thread pointer */

#define xA0 10  /* gpr[10-17] are syscall arguments */
#define xA1 11
#define xA2 12
#define xA3 13
#define xA4 14
#define xA5 15
#define xA6 16
#define xA7 17  /* syscall number for RVI ABI */
#define xT0 5   /* syscall number for RVE ABI */
#elif defined(TARGET_GFMIPSEL)
#define xRA 31  /* return address (aka link register) */
#define xSP 29  /* stack pointer */
#define xGP 28  /* global pointer */

#define xA0 4   /* gpr[4-7] are syscall arguments */
#define xA1 5 
#define xA2 6 
#define xA3 7 
#define xV0 2   /* syscall number */
#define xV1 3
#endif

#endif
