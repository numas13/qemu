/*
 * RISC-V CPU helpers for qemu.
 *
 * Copyright (c) 2016-2017 Sagar Karandikar, sagark@eecs.berkeley.edu
 * Copyright (c) 2017-2018 SiFive, Inc.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2 or later, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qemu/osdep.h"
#include "qemu/log.h"
#include "qemu/main-loop.h"
#include "cpu.h"
#include "exec/exec-all.h"
#include "tcg/tcg-op.h"
#include "trace.h"
#include "cpu_bits.h"

int gf_cpu_mmu_index(CPUGFState *env, bool ifetch)
{
#ifdef CONFIG_USER_ONLY
    return 0;
#else
# error implement me
#endif
}

void cpu_get_tb_cpu_state(CPUGFState *env, vaddr *pc,
                          uint64_t *cs_base, uint32_t *pflags)
{
    *pc = env->pc & UINT32_MAX;
    *cs_base = 0;
    *pflags = 0;
}
