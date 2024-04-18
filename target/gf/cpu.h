/*
 * QEMU GF CPU
 */

#ifndef TARGET_GF_CPU_H
#define TARGET_GF_CPU_H

#include "hw/core/cpu.h"
#include "hw/registerfields.h"
#include "exec/cpu-defs.h"
#include "qom/object.h"
#include "qemu/int128.h"
#include "cpu_bits.h"
#include "qapi/qapi-types-common.h"
#include "cpu-qom.h"

typedef struct CPUArchState CPUGFState;

#define CPU_RESOLVING_TYPE TYPE_GF_CPU

#define TYPE_GF_CPU_BASE            TYPE_GF_CPU_BASE32

#define TCG_GUEST_DEFAULT_MO 0

struct CPUArchState {
    target_ulong gpr[32];
    target_ulong pc;
};

/*
 * GFCPU:
 * @env: #CPUGFState
 *
 * A GF CPU.
 */
struct ArchCPU {
    CPUState parent_obj;

    CPUGFState env;
};

/**
 * GFCPUClass:
 * @parent_realize: The parent class' realize handler.
 * @parent_phases: The parent class' reset phase handlers.
 *
 * A GF CPU model.
 */
struct GFCPUClass {
    CPUClass parent_class;

    DeviceRealize parent_realize;
    ResettablePhases parent_phases;
};

#include "cpu_user.h"

extern const char * const gf_int_regnames[];

int gf_cpu_mmu_index(CPUGFState *env, bool ifetch);

#define cpu_mmu_index gf_cpu_mmu_index

void gf_translate_init(void);

#include "exec/cpu-all.h"

void cpu_get_tb_cpu_state(CPUGFState *env, vaddr *pc,
                          uint64_t *cs_base, uint32_t *pflags);

G_NORETURN void gf_raise_exception(CPUGFState *env,
                                   uint32_t exception, uintptr_t pc);

#endif /* RISCV_CPU_H */
