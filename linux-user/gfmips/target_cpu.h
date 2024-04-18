#ifndef RISCV_TARGET_CPU_H
#define RISCV_TARGET_CPU_H

static inline void cpu_clone_regs_child(CPUGFState *env, target_ulong newsp,
                                        unsigned flags)
{
    if (newsp) {
        env->gpr[xSP] = newsp;
    }

    env->gpr[xA0] = 0;
}

static inline void cpu_clone_regs_parent(CPUGFState *env, unsigned flags)
{
}

static inline void cpu_set_tls(CPUGFState *env, target_ulong newtls)
{
    // TODO:
}

static inline abi_ulong get_sp_from_cpustate(CPUGFState *state)
{
   return state->gpr[xSP];
}
#endif