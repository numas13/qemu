/*
 * QEMU RISC-V CPU QOM header (target agnostic)
 *
 * Copyright (c) 2023 Ventana Micro Systems Inc.
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

#ifndef RISCV_CPU_QOM_H
#define RISCV_CPU_QOM_H

#include "hw/core/cpu.h"

#define TYPE_GF_CPU "gf-cpu"
#define TYPE_GF_DYNAMIC_CPU "gf-dynamic-cpu"

#define GF_CPU_TYPE_SUFFIX "-" TYPE_GF_CPU
#define GF_CPU_TYPE_NAME(name) (name GF_CPU_TYPE_SUFFIX)

#define TYPE_GF_CPU_ANY              GF_CPU_TYPE_NAME("any")
#define TYPE_GF_CPU_MAX              GF_CPU_TYPE_NAME("max")
#if defined(TARGET_GFRISCV32)
# define TYPE_GF_CPU_BASE32           GF_CPU_TYPE_NAME("rv32")
#elif defined(TARGET_GFMIPSEL)
# define TYPE_GF_CPU_BASE32           GF_CPU_TYPE_NAME("mipsel")
#else
# error "unsupported target"
#endif

OBJECT_DECLARE_CPU_TYPE(GFCPU, GFCPUClass, GF_CPU)

#endif /* RISCV_CPU_QOM_H */
