/*
 * RISC-V emulation for qemu: main translation routines.
 *
 * Copyright (c) 2016-2017 Sagar Karandikar, sagark@eecs.berkeley.edu
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
#include "cpu.h"
#include "tcg/tcg-op.h"
#include "disas/disas.h"
#include "exec/cpu_ldst.h"
#include "exec/exec-all.h"
#include "exec/helper-proto.h"
#include "exec/helper-gen.h"

#include "exec/translator.h"
#include "exec/log.h"

#define HELPER_H "helper.h"
#include "exec/helper-info.c.inc"
#undef  HELPER_H

#define MAX_INSN_LEN 4

/* global register indices */
static TCGv cpu_gpr[32], cpu_pc;

typedef struct DisasContext {
    DisasContextBase base;
    target_ulong cur_insn_len;
    target_ulong pc_save;
} DisasContext;

#ifdef TARGET_GF32
#define get_xl(ctx)    MXL_RV32
#elif defined(CONFIG_USER_ONLY)
#define get_xl(ctx)    MXL_RV64
#else
#define get_xl(ctx)    ((ctx)->xl)
#endif

static void gen_pc_plus_diff(TCGv target, DisasContext *ctx,
                             target_long diff)
{
    target_ulong dest = ctx->base.pc_next + diff;

    assert(ctx->pc_save != -1);
    if (tb_cflags(ctx->base.tb) & CF_PCREL) {
        tcg_gen_addi_tl(target, cpu_pc, dest - ctx->pc_save);
        if (get_xl(ctx) == MXL_RV32) {
            tcg_gen_ext32s_tl(target, target);
        }
    } else {
        if (get_xl(ctx) == MXL_RV32) {
            dest = (int32_t)dest;
        }
        tcg_gen_movi_tl(target, dest);
    }
}

static void gen_update_pc(DisasContext *ctx, target_long diff)
{
    gen_pc_plus_diff(cpu_pc, ctx, diff);
    ctx->pc_save = ctx->base.pc_next + diff;
}

static void generate_exception(DisasContext *ctx, int excp)
{
    gen_update_pc(ctx, 0);
    gen_helper_raise_exception(tcg_env, tcg_constant_i32(excp));
    ctx->base.is_jmp = DISAS_NORETURN;
}

static void gen_exception_illegal(DisasContext *ctx)
{
    generate_exception(ctx, RISCV_EXCP_ILLEGAL_INST);
}

static void lookup_and_goto_ptr(DisasContext *ctx)
{
#ifndef CONFIG_USER_ONLY
    if (ctx->itrigger) {
        gen_helper_itrigger_match(tcg_env);
    }
#endif
    tcg_gen_lookup_and_goto_ptr();
}

static void gen_goto_tb(DisasContext *ctx, int n, target_long diff)
{
    target_ulong dest = ctx->base.pc_next + diff;

     /*
      * Under itrigger, instruction executes one by one like singlestep,
      * direct block chain benefits will be small.
      */
    if (translator_use_goto_tb(&ctx->base, dest)/* && !ctx->itrigger */) {
        /*
         * For pcrel, the pc must always be up-to-date on entry to
         * the linked TB, so that it can use simple additions for all
         * further adjustments.  For !pcrel, the linked TB is compiled
         * to know its full virtual address, so we can delay the
         * update to pc to the unlinked path.  A long chain of links
         * can thus avoid many updates to the PC.
         */
        if (tb_cflags(ctx->base.tb) & CF_PCREL) {
            gen_update_pc(ctx, diff);
            tcg_gen_goto_tb(n);
        } else {
            tcg_gen_goto_tb(n);
            gen_update_pc(ctx, diff);
        }
        tcg_gen_exit_tb(ctx->base.tb, n);
    } else {
        gen_update_pc(ctx, diff);
        lookup_and_goto_ptr(ctx);
    }
}

static TCGv get_gpr(DisasContext *ctx, int reg)
{
    return reg == 0 ? tcg_constant_tl(0) : cpu_gpr[reg];
}

static void set_gpr(DisasContext *ctx, int reg, TCGv val)
{
    if (reg) {
        tcg_gen_mov_tl(cpu_gpr[reg], val);
    }
}

#include "translate_generate.c.inc"
#include "decode_generate.c.inc"

static void gf_tr_init_disas_context(DisasContextBase *dcbase, CPUState *cs)
{
    DisasContext *ctx = container_of(dcbase, DisasContext, base);

    ctx->pc_save = ctx->base.pc_first;
}

static void gf_tr_tb_start(DisasContextBase *db, CPUState *cpu)
{
}

static void gf_tr_insn_start(DisasContextBase *dcbase, CPUState *cpu)
{
    DisasContext *ctx = container_of(dcbase, DisasContext, base);
    target_ulong pc_next = ctx->base.pc_next;

    if (tb_cflags(dcbase->tb) & CF_PCREL) {
        pc_next &= ~TARGET_PAGE_MASK;
    }

    tcg_gen_insn_start(pc_next);
}

static void gf_tr_translate_insn(DisasContextBase *dcbase, CPUState *cpu)
{
    DisasContext *ctx = container_of(dcbase, DisasContext, base);
    CPUGFState *env = cpu_env(cpu);
    uint32_t insn = translator_ldl(env, &ctx->base, ctx->base.pc_next);

    ctx->cur_insn_len = 4;
    printf("before decode\n");
    if (!decode(ctx, insn)){;       
        if (insn == 0x73) {
            // ecall
            generate_exception(ctx, RISCV_EXCP_U_ECALL);
        } else {
            gen_exception_illegal(ctx);
        }
    }
    printf("after decode\n");
    ctx->base.pc_next += ctx->cur_insn_len;

    /* Only the first insn within a TB is allowed to cross a page boundary. */
    if (ctx->base.is_jmp == DISAS_NEXT) {
        if (!is_same_page(&ctx->base, ctx->base.pc_next)) {
            ctx->base.is_jmp = DISAS_TOO_MANY;
        } else {
            unsigned page_ofs = ctx->base.pc_next & ~TARGET_PAGE_MASK;

            if (page_ofs > TARGET_PAGE_SIZE - MAX_INSN_LEN) {
                int len = 4;

                if (!is_same_page(&ctx->base, ctx->base.pc_next + len - 1)) {
                    ctx->base.is_jmp = DISAS_TOO_MANY;
                }
            }
        }
    }
   
}

static void gf_tr_tb_stop(DisasContextBase *dcbase, CPUState *cpu)
{
    DisasContext *ctx = container_of(dcbase, DisasContext, base);

    switch (ctx->base.is_jmp) {
    case DISAS_TOO_MANY:
        gen_goto_tb(ctx, 0, 0);
        break;
    case DISAS_NORETURN:
        break;
    default:
        g_assert_not_reached();
    }
}

static void gf_tr_disas_log(const DisasContextBase *dcbase,
                               CPUState *cpu, FILE *logfile)
{
    fprintf(logfile, "IN: %s\n", lookup_symbol(dcbase->pc_first));
    target_disas(logfile, cpu, dcbase->pc_first, dcbase->tb->size);
}

static const TranslatorOps gf_tr_ops = {
    .init_disas_context = gf_tr_init_disas_context,
    .tb_start           = gf_tr_tb_start,
    .insn_start         = gf_tr_insn_start,
    .translate_insn     = gf_tr_translate_insn,
    .tb_stop            = gf_tr_tb_stop,
    .disas_log          = gf_tr_disas_log,
};

void gen_intermediate_code(CPUState *cs, TranslationBlock *tb, int *max_insns,
                           target_ulong pc, void *host_pc)
{
    DisasContext ctx;

    translator_loop(cs, tb, max_insns, pc, host_pc, &gf_tr_ops, &ctx.base);
}

void gf_translate_init(void)
{
    int i;

    /*
     * cpu_gpr[0] is a placeholder for the zero register. Do not use it.
     * Use the gen_set_gpr and get_gpr helper functions when accessing regs,
     * unless you specifically block reads/writes to reg 0.
     */
    cpu_gpr[0] = NULL;

    for (i = 1; i < 32; i++) {
        cpu_gpr[i] = tcg_global_mem_new(tcg_env,
            offsetof(CPUGFState, gpr[i]), gf_int_regnames[i]);
    }

    cpu_pc = tcg_global_mem_new(tcg_env, offsetof(CPUGFState, pc), "pc");
}
