/*
 * QEMU RISC-V CPU
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
#include "qemu/qemu-print.h"
#include "qemu/ctype.h"
#include "qemu/log.h"
#include "cpu.h"
#include "exec/exec-all.h"
#include "qapi/error.h"
#include "qapi/visitor.h"
#include "qemu/error-report.h"
// TODO: #include "tcg/tcg-cpu.h"
#include "tcg/tcg.h"

#define NUMBER_OF_CPU_REGISTERS 32
const char * const gf_int_regnames[] = {
    "x0/zero", "x1/ra",  "x2/sp",  "x3/gp",  "x4/tp",  "x5/t0",   "x6/t1",
    "x7/t2",   "x8/s0",  "x9/s1",  "x10/a0", "x11/a1", "x12/a2",  "x13/a3",
    "x14/a4",  "x15/a5", "x16/a6", "x17/a7", "x18/s2", "x19/s3",  "x20/s4",
    "x21/s5",  "x22/s6", "x23/s7", "x24/s8", "x25/s9", "x26/s10", "x27/s11",
    "x28/t3",  "x29/t4", "x30/t5", "x31/t6"
};

static void gf_cpu_realize(DeviceState *dev, Error **errp)
{
    CPUState *cs = CPU(dev);
    GFCPUClass *mcc = GF_CPU_GET_CLASS(dev);
    Error *local_err = NULL;

    if (object_dynamic_cast(OBJECT(dev), TYPE_GF_CPU_ANY) != NULL) {
        warn_report("The 'any' CPU is deprecated and will be "
                    "removed in the future.");
    }

    cpu_exec_realizefn(cs, &local_err);
    if (local_err != NULL) {
        error_propagate(errp, local_err);
        return;
    }

    qemu_init_vcpu(cs);
    cpu_reset(cs);

    mcc->parent_realize(dev, errp);
}

static void gf_cpu_reset_hold(Object *obj)
{
    CPUState *cs = CPU(obj);
    GFCPU *cpu = GF_CPU(cs);
    GFCPUClass *mcc = GF_CPU_GET_CLASS(cpu);

    if (mcc->parent_phases.hold) {
        mcc->parent_phases.hold(obj);
    }
    cs->exception_index = RISCV_EXCP_NONE;
}

static ObjectClass *gf_cpu_class_by_name(const char *cpu_model)
{
    ObjectClass *oc;
    char *typename;
    char **cpuname;

    cpuname = g_strsplit(cpu_model, ",", 1);
    typename = g_strdup_printf(GF_CPU_TYPE_NAME("%s"), cpuname[0]);
    oc = object_class_by_name(typename);
    g_strfreev(cpuname);
    g_free(typename);
    if (!oc || !object_class_dynamic_cast(oc, TYPE_GF_CPU)) {
        return NULL;
    }
    return oc;
}

static void gf_cpu_set_pc(CPUState *cs, vaddr value)
{
    GFCPU *cpu = GF_CPU(cs);
    CPUGFState *env = &cpu->env;

    env->pc = (int32_t)value;
}

static vaddr gf_cpu_get_pc(CPUState *cs)
{
    GFCPU *cpu = GF_CPU(cs);
    CPUGFState *env = &cpu->env;

    /* Match cpu_get_tb_cpu_state. */
    return env->pc & UINT32_MAX;
}

static bool gf_cpu_has_work(CPUState *cs)
{
#ifndef CONFIG_USER_ONLY
# error implement me
#else
    return true;
#endif
}

static void gf_cpu_disas_set_info(CPUState *s, disassemble_info *info)
{
#if defined(TARGET_GFRISCV32)
    info->print_insn = print_insn_riscv32;
#elif defined(TARGET_GFMIPSEL)
    info->print_insn = print_insn_little_mips;
#endif
}

static void gf_cpu_class_init(ObjectClass *c, void *data)
{
    GFCPUClass *mcc = GF_CPU_CLASS(c);
    CPUClass *cc = CPU_CLASS(c);
    DeviceClass *dc = DEVICE_CLASS(c);
    ResettableClass *rc = RESETTABLE_CLASS(c);

    device_class_set_parent_realize(dc, gf_cpu_realize,
                                    &mcc->parent_realize);

    resettable_class_set_parent_phases(rc, NULL, gf_cpu_reset_hold, NULL,
                                       &mcc->parent_phases);

    cc->class_by_name = gf_cpu_class_by_name;
    cc->has_work = gf_cpu_has_work;
    // TODO: cc->dump_state = gf_cpu_dump_state;
    cc->set_pc = gf_cpu_set_pc;
    cc->get_pc = gf_cpu_get_pc;
    // TODO: cc->gdb_read_register = riscv_cpu_gdb_read_register;
    // TODO: cc->gdb_write_register = riscv_cpu_gdb_write_register;
    cc->gdb_num_core_regs = 33;
    cc->gdb_stop_before_watchpoint = true;
    cc->disas_set_info = gf_cpu_disas_set_info;
    // TODO: cc->gdb_arch_name = riscv_gdb_arch_name;
    // TODO: cc->gdb_get_dynamic_xml = riscv_gdb_get_dynamic_xml;
}

static void gf_cpu_init(Object *obj)
{
}

#define DEFINE_DYNAMIC_CPU(type_name, initfn) \
    {                                         \
        .name = type_name,                    \
        .parent = TYPE_GF_DYNAMIC_CPU,        \
        .instance_init = initfn               \
    }

static const TypeInfo gf_cpu_type_infos[] = {
    {
        .name = TYPE_GF_CPU,
        .parent = TYPE_CPU,
        .instance_size = sizeof(GFCPU),
        .instance_align = __alignof(GFCPU),
        .instance_init = gf_cpu_init,
        .abstract = true,
        .class_size = sizeof(GFCPUClass),
        .class_init = gf_cpu_class_init,
    },
    {
        .name = TYPE_GF_DYNAMIC_CPU,
        .parent = TYPE_GF_CPU,
        .abstract = true,
    },
    DEFINE_DYNAMIC_CPU(TYPE_GF_CPU_ANY,      gf_cpu_init),
    DEFINE_DYNAMIC_CPU(TYPE_GF_CPU_MAX,      gf_cpu_init),
#if defined(TARGET_GFRISCV32)
    DEFINE_DYNAMIC_CPU(TYPE_GF_CPU_BASE32,   gf_cpu_init),
#endif
};

DEFINE_TYPES(gf_cpu_type_infos)
