/*
 * GF cpu parameters for qemu.
 *
 * SPDX-License-Identifier: GPL-2.0+
 */

#ifndef TARGET_GF_CPU_PARAM_H
#define TARGET_GF_CPU_PARAM_H

#if defined(TARGET_GFRISCV32)
# define TARGET_LONG_BITS 32
# define TARGET_PHYS_ADDR_SPACE_BITS 34 /* 22-bit PPN */
# define TARGET_VIRT_ADDR_SPACE_BITS 32 /* sv32 */
#elif defined(TARGET_GFMIPSEL)
# define TARGET_LONG_BITS 32
# define TARGET_PHYS_ADDR_SPACE_BITS 32
# define TARGET_VIRT_ADDR_SPACE_BITS 32
#else
# error "unsupported target"
#endif
#define TARGET_PAGE_BITS 12 /* 4 KiB Pages */

#endif
