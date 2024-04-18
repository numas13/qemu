/*
 * riscv TCG cpu class initialization
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
#include "exec/exec-all.h"
#include "tcg-cpu.h"
#include "cpu.h"
#include "qapi/error.h"
#include "qapi/visitor.h"
#include "qemu/accel.h"
#include "qemu/error-report.h"
#include "qemu/log.h"
#include "hw/core/accel-cpu.h"
#include "hw/core/tcg-cpu-ops.h"
#include "tcg/tcg.h"

static void gf_cpu_synchronize_from_tb(CPUState *cs,
                                          const TranslationBlock *tb)
{
    GFCPU *cpu = GF_CPU(cs);
    CPUGFState *env = &cpu->env;

    tcg_debug_assert(!(cs->tcg_cflags & CF_PCREL));
    env->pc = (int32_t) tb->pc;
}

static void gf_restore_state_to_opc(CPUState *cs,
                                    const TranslationBlock *tb,
                                    const uint64_t *data)
{
    GFCPU *cpu = GF_CPU(cs);
    CPUGFState *env = &cpu->env;
    target_ulong pc;

    pc = data[0];
    env->pc = (int32_t)pc;
}

static const struct TCGCPUOps gf_tcg_ops = {
    .initialize = gf_translate_init,
    .synchronize_from_tb = gf_cpu_synchronize_from_tb,
    .restore_state_to_opc = gf_restore_state_to_opc,
};

/*
 * We'll get here via the following path:
 *
 * riscv_cpu_realize()
 *   -> cpu_exec_realizefn()
 *      -> tcg_cpu_realize() (via accel_cpu_common_realize())
 */
static bool tcg_cpu_realize(CPUState *cs, Error **errp)
{
    return true;
}

static void tcg_cpu_instance_init(CPUState *cs)
{
}

static void tcg_cpu_init_ops(AccelCPUClass *accel_cpu, CPUClass *cc)
{
    /*
     * All cpus use the same set of operations.
     */
    cc->tcg_ops = &gf_tcg_ops;
}

static void tcg_cpu_class_init(CPUClass *cc)
{
    cc->init_accel_cpu = tcg_cpu_init_ops;
}

static void tcg_cpu_accel_class_init(ObjectClass *oc, void *data)
{
    AccelCPUClass *acc = ACCEL_CPU_CLASS(oc);

    acc->cpu_class_init = tcg_cpu_class_init;
    acc->cpu_instance_init = tcg_cpu_instance_init;
    acc->cpu_target_realize = tcg_cpu_realize;
}

static const TypeInfo tcg_cpu_accel_type_info = {
    .name = ACCEL_CPU_NAME("tcg"),

    .parent = TYPE_ACCEL_CPU,
    .class_init = tcg_cpu_accel_class_init,
    .abstract = true,
};

static void tcg_cpu_accel_register_types(void)
{
    type_register_static(&tcg_cpu_accel_type_info);
}
type_init(tcg_cpu_accel_register_types);
