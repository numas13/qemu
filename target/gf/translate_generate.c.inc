
/*
* QEMU GF CPU
*/
static void set_gpri(DisasContext *ctx, int reg, uint32_t val)
{
    if (reg) {
        tcg_gen_movi_tl(cpu_gpr[reg], val);
    }
}


/*
* QEMU GF CPU
*/


static bool tcg_trans_Lui(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Lui_515_0 = gen_new_label();
	TCGLabel *l_Lui_329_1 = gen_new_label();
	TCGLabel *exit_Lui_310_2 = gen_new_label();
	TCGLabel *l_Lui_310_3 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Lui_329_1);
	} else {
		tcg_gen_br(l_Lui_515_0);
	}
	gen_set_label(l_Lui_515_0);
	tcg_gen_br(l_Lui_310_3);
	gen_set_label(l_Lui_310_3);
	tcg_gen_br(exit_Lui_310_2);
	gen_set_label(l_Lui_329_1);
	set_gpri(ctx, arg_0 / 4, arg_1);
	tcg_gen_br(l_Lui_310_3);
	gen_set_label(exit_Lui_310_2);
	return true;
}

static bool trans_Lui(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1)
{
	uint64_t tmp_2 = arg_1 * 0x0004;
	uint64_t tmp_3 = 0x0000 + tmp_2;
	uint64_t tmp_4 = (arg_0 << 12) | 0x000;
	tcg_trans_Lui(ctx, tmp_3, tmp_4);
	return true;
}

static bool tcg_trans_Auipc(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGv tmp_2 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_2, ctx->base.pc_next);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_addi_tl(tmp_3, tmp_2, arg_1);
	TCGLabel *l_Auipc_515_0 = gen_new_label();
	TCGLabel *l_Auipc_329_1 = gen_new_label();
	TCGLabel *exit_Auipc_310_2 = gen_new_label();
	TCGLabel *l_Auipc_310_3 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Auipc_329_1);
	} else {
		tcg_gen_br(l_Auipc_515_0);
	}
	gen_set_label(l_Auipc_515_0);
	tcg_gen_br(l_Auipc_310_3);
	gen_set_label(l_Auipc_310_3);
	tcg_gen_br(exit_Auipc_310_2);
	gen_set_label(l_Auipc_329_1);
	set_gpr(ctx, arg_0 / 4, tmp_3);
	tcg_gen_br(l_Auipc_310_3);
	gen_set_label(exit_Auipc_310_2);
	return true;
}

static bool trans_Auipc(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1)
{
	uint64_t tmp_2 = arg_1 * 0x0004;
	uint64_t tmp_3 = 0x0000 + tmp_2;
	uint64_t tmp_4 = (arg_0 << 12) | 0x000;
	tcg_trans_Auipc(ctx, tmp_3, tmp_4);
	return true;
}

static bool tcg_trans_Jal(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGv tmp_2 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_2, cpu_pc);
	TCGLabel *l_Jal_515_0 = gen_new_label();
	TCGLabel *l_Jal_329_1 = gen_new_label();
	TCGLabel *exit_Jal_310_2 = gen_new_label();
	TCGLabel *l_Jal_310_3 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Jal_329_1);
	} else {
		tcg_gen_br(l_Jal_515_0);
	}
	gen_set_label(l_Jal_515_0);
	tcg_gen_br(l_Jal_310_3);
	gen_set_label(l_Jal_310_3);
	tcg_gen_br(exit_Jal_310_2);
	gen_set_label(l_Jal_329_1);
	set_gpr(ctx, arg_0 / 4, tmp_2);
	tcg_gen_br(l_Jal_310_3);
	gen_set_label(exit_Jal_310_2);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, ctx->base.pc_next);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_addi_tl(tmp_4, tmp_3, arg_1);
	tcg_gen_mov_tl(pc_val, tmp_4);
	ctx->base.is_jmp = DISAS_NORETURN;
	tcg_gen_mov_tl(cpu_pc, pc_val);
	tcg_gen_lookup_and_goto_ptr(); // FIXME: because developer is too lazy to update ctx->base.pc_next manually
	return true;
}

static bool trans_Jal(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1)
{
	uint64_t tmp_2 = arg_1 * 0x0004;
	uint64_t tmp_3 = 0x0000 + tmp_2;
	uint64_t tmp_4 = extract32(arg_0, 19, 1);
	uint64_t tmp_5 = extract32(arg_0, 0, 8);
	uint64_t tmp_6 = (tmp_4 << 8) | tmp_5;
	uint64_t tmp_7 = extract32(arg_0, 8, 1);
	uint64_t tmp_8 = (tmp_6 << 1) | tmp_7;
	uint64_t tmp_9 = extract32(arg_0, 9, 10);
	uint64_t tmp_10 = (tmp_8 << 10) | tmp_9;
	uint64_t tmp_11 = (tmp_10 << 1) | 0b0;
	uint64_t tmp_12 = sextract64(tmp_11, 0, 21);
	tcg_trans_Jal(ctx, tmp_3, tmp_12);
	return true;
}

static bool tcg_trans_Jalr(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_3, cpu_pc);
	TCGLabel *l_Jalr_515_0 = gen_new_label();
	TCGLabel *l_Jalr_329_1 = gen_new_label();
	TCGLabel *exit_Jalr_310_2 = gen_new_label();
	TCGLabel *l_Jalr_310_3 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Jalr_329_1);
	} else {
		tcg_gen_br(l_Jalr_515_0);
	}
	gen_set_label(l_Jalr_515_0);
	tcg_gen_br(l_Jalr_310_3);
	gen_set_label(l_Jalr_310_3);
	tcg_gen_br(exit_Jalr_310_2);
	gen_set_label(l_Jalr_329_1);
	set_gpr(ctx, arg_0 / 4, tmp_3);
	tcg_gen_br(l_Jalr_310_3);
	gen_set_label(exit_Jalr_310_2);
	TCGLabel *l_Jalr_30_4 = gen_new_label();
	TCGLabel *l_Jalr_304_5 = gen_new_label();
	TCGLabel *exit_Jalr_373_6 = gen_new_label();
	TCGLabel *l_Jalr_373_7 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Jalr_304_5);
	} else {
		tcg_gen_br(l_Jalr_30_4);
	}
	gen_set_label(l_Jalr_30_4);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_4, 0x00000000);
	tcg_gen_br(l_Jalr_373_7);
	gen_set_label(l_Jalr_373_7);
	tcg_gen_br(exit_Jalr_373_6);
	gen_set_label(l_Jalr_304_5);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_5, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_4, tmp_5);
	tcg_gen_br(l_Jalr_373_7);
	gen_set_label(exit_Jalr_373_6);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_addi_tl(tmp_6, tmp_4, arg_2);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_andi_tl(tmp_7, tmp_6, 0xFFFFFFFE);
	tcg_gen_mov_tl(pc_val, tmp_7);
	ctx->base.is_jmp = DISAS_NORETURN;
	tcg_gen_mov_tl(cpu_pc, pc_val);
	tcg_gen_lookup_and_goto_ptr(); // FIXME: because developer is too lazy to update ctx->base.pc_next manually
	return true;
}

static bool trans_Jalr(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_2 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_1 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = sextract64(arg_0, 0, 12);
	tcg_trans_Jalr(ctx, tmp_4, tmp_6, tmp_7);
	return true;
}

static bool tcg_trans_Beq(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Beq_527_0 = gen_new_label();
	TCGLabel *l_Beq_140_1 = gen_new_label();
	TCGLabel *exit_Beq_322_2 = gen_new_label();
	TCGLabel *l_Beq_322_3 = gen_new_label();
	TCGLabel *l_Beq_30_4 = gen_new_label();
	TCGLabel *l_Beq_304_5 = gen_new_label();
	TCGLabel *exit_Beq_373_6 = gen_new_label();
	TCGLabel *l_Beq_373_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Beq_304_5);
	} else {
		tcg_gen_br(l_Beq_30_4);
	}
	gen_set_label(l_Beq_30_4);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Beq_373_7);
	gen_set_label(l_Beq_373_7);
	tcg_gen_br(exit_Beq_373_6);
	gen_set_label(l_Beq_304_5);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_0 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Beq_373_7);
	gen_set_label(exit_Beq_373_6);
	TCGLabel *l_Beq_30_8 = gen_new_label();
	TCGLabel *l_Beq_304_9 = gen_new_label();
	TCGLabel *exit_Beq_373_10 = gen_new_label();
	TCGLabel *l_Beq_373_11 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Beq_304_9);
	} else {
		tcg_gen_br(l_Beq_30_8);
	}
	gen_set_label(l_Beq_30_8);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_Beq_373_11);
	gen_set_label(l_Beq_373_11);
	tcg_gen_br(exit_Beq_373_10);
	gen_set_label(l_Beq_304_9);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_Beq_373_11);
	gen_set_label(exit_Beq_373_10);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_setcond_tl(TCG_COND_EQ, tmp_7, tmp_3, tmp_5);
	TCGLabel *branch_l_Beq_478_12 = gen_new_label();
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp_7, 0, branch_l_Beq_478_12);
	tcg_gen_br(l_Beq_140_1);
	gen_set_label(branch_l_Beq_478_12);
	tcg_gen_br(l_Beq_527_0);
	gen_set_label(l_Beq_527_0);
	tcg_gen_br(l_Beq_322_3);
	gen_set_label(l_Beq_322_3);
	tcg_gen_br(exit_Beq_322_2);
	gen_set_label(l_Beq_140_1);
	TCGv tmp_8 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_8, ctx->base.pc_next);
	TCGv tmp_9 = tcg_temp_new();
	tcg_gen_addi_tl(tmp_9, tmp_8, arg_2);
	tcg_gen_mov_tl(pc_val, tmp_9);
	tcg_gen_br(l_Beq_322_3);
	gen_set_label(exit_Beq_322_2);
	ctx->base.is_jmp = DISAS_NORETURN;
	tcg_gen_mov_tl(cpu_pc, pc_val);
	tcg_gen_lookup_and_goto_ptr(); // FIXME: because developer is too lazy to update ctx->base.pc_next manually
	return true;
}

static bool trans_Beq(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_0 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_1 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = extract32(arg_2, 11, 1);
	uint64_t tmp_8 = extract32(arg_2, 0, 1);
	uint64_t tmp_9 = (tmp_7 << 1) | tmp_8;
	uint64_t tmp_10 = extract32(arg_2, 1, 10);
	uint64_t tmp_11 = (tmp_9 << 10) | tmp_10;
	uint64_t tmp_12 = (tmp_11 << 1) | 0b0;
	uint64_t tmp_13 = sextract64(tmp_12, 0, 13);
	tcg_trans_Beq(ctx, tmp_4, tmp_6, tmp_13);
	return true;
}

static bool tcg_trans_Bne(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Bne_471_0 = gen_new_label();
	TCGLabel *l_Bne_62_1 = gen_new_label();
	TCGLabel *exit_Bne_81_2 = gen_new_label();
	TCGLabel *l_Bne_81_3 = gen_new_label();
	TCGLabel *l_Bne_30_4 = gen_new_label();
	TCGLabel *l_Bne_304_5 = gen_new_label();
	TCGLabel *exit_Bne_373_6 = gen_new_label();
	TCGLabel *l_Bne_373_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Bne_304_5);
	} else {
		tcg_gen_br(l_Bne_30_4);
	}
	gen_set_label(l_Bne_30_4);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Bne_373_7);
	gen_set_label(l_Bne_373_7);
	tcg_gen_br(exit_Bne_373_6);
	gen_set_label(l_Bne_304_5);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_0 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Bne_373_7);
	gen_set_label(exit_Bne_373_6);
	TCGLabel *l_Bne_30_8 = gen_new_label();
	TCGLabel *l_Bne_304_9 = gen_new_label();
	TCGLabel *exit_Bne_373_10 = gen_new_label();
	TCGLabel *l_Bne_373_11 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Bne_304_9);
	} else {
		tcg_gen_br(l_Bne_30_8);
	}
	gen_set_label(l_Bne_30_8);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_Bne_373_11);
	gen_set_label(l_Bne_373_11);
	tcg_gen_br(exit_Bne_373_10);
	gen_set_label(l_Bne_304_9);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_Bne_373_11);
	gen_set_label(exit_Bne_373_10);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_setcond_tl(TCG_COND_NE, tmp_7, tmp_3, tmp_5);
	TCGLabel *branch_l_Bne_169_12 = gen_new_label();
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp_7, 0, branch_l_Bne_169_12);
	tcg_gen_br(l_Bne_62_1);
	gen_set_label(branch_l_Bne_169_12);
	tcg_gen_br(l_Bne_471_0);
	gen_set_label(l_Bne_471_0);
	tcg_gen_br(l_Bne_81_3);
	gen_set_label(l_Bne_81_3);
	tcg_gen_br(exit_Bne_81_2);
	gen_set_label(l_Bne_62_1);
	TCGv tmp_8 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_8, ctx->base.pc_next);
	TCGv tmp_9 = tcg_temp_new();
	tcg_gen_addi_tl(tmp_9, tmp_8, arg_2);
	tcg_gen_mov_tl(pc_val, tmp_9);
	tcg_gen_br(l_Bne_81_3);
	gen_set_label(exit_Bne_81_2);
	ctx->base.is_jmp = DISAS_NORETURN;
	tcg_gen_mov_tl(cpu_pc, pc_val);
	tcg_gen_lookup_and_goto_ptr(); // FIXME: because developer is too lazy to update ctx->base.pc_next manually
	return true;
}

static bool trans_Bne(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_0 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_2 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = extract32(arg_1, 11, 1);
	uint64_t tmp_8 = extract32(arg_1, 0, 1);
	uint64_t tmp_9 = (tmp_7 << 1) | tmp_8;
	uint64_t tmp_10 = extract32(arg_1, 1, 10);
	uint64_t tmp_11 = (tmp_9 << 10) | tmp_10;
	uint64_t tmp_12 = (tmp_11 << 1) | 0b0;
	uint64_t tmp_13 = sextract64(tmp_12, 0, 13);
	tcg_trans_Bne(ctx, tmp_4, tmp_6, tmp_13);
	return true;
}

static bool tcg_trans_Blt(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Blt_94_0 = gen_new_label();
	TCGLabel *l_Blt_82_1 = gen_new_label();
	TCGLabel *exit_Blt_361_2 = gen_new_label();
	TCGLabel *l_Blt_361_3 = gen_new_label();
	TCGLabel *l_Blt_30_4 = gen_new_label();
	TCGLabel *l_Blt_304_5 = gen_new_label();
	TCGLabel *exit_Blt_373_6 = gen_new_label();
	TCGLabel *l_Blt_373_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Blt_304_5);
	} else {
		tcg_gen_br(l_Blt_30_4);
	}
	gen_set_label(l_Blt_30_4);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Blt_373_7);
	gen_set_label(l_Blt_373_7);
	tcg_gen_br(exit_Blt_373_6);
	gen_set_label(l_Blt_304_5);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_0 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Blt_373_7);
	gen_set_label(exit_Blt_373_6);
	TCGLabel *l_Blt_30_8 = gen_new_label();
	TCGLabel *l_Blt_304_9 = gen_new_label();
	TCGLabel *exit_Blt_373_10 = gen_new_label();
	TCGLabel *l_Blt_373_11 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Blt_304_9);
	} else {
		tcg_gen_br(l_Blt_30_8);
	}
	gen_set_label(l_Blt_30_8);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_Blt_373_11);
	gen_set_label(l_Blt_373_11);
	tcg_gen_br(exit_Blt_373_10);
	gen_set_label(l_Blt_304_9);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_Blt_373_11);
	gen_set_label(exit_Blt_373_10);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_setcond_tl(TCG_COND_LT, tmp_7, tmp_3, tmp_5);
	TCGLabel *branch_l_Blt_240_12 = gen_new_label();
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp_7, 0, branch_l_Blt_240_12);
	tcg_gen_br(l_Blt_82_1);
	gen_set_label(branch_l_Blt_240_12);
	tcg_gen_br(l_Blt_94_0);
	gen_set_label(l_Blt_94_0);
	tcg_gen_br(l_Blt_361_3);
	gen_set_label(l_Blt_361_3);
	tcg_gen_br(exit_Blt_361_2);
	gen_set_label(l_Blt_82_1);
	TCGv tmp_8 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_8, ctx->base.pc_next);
	TCGv tmp_9 = tcg_temp_new();
	tcg_gen_addi_tl(tmp_9, tmp_8, arg_2);
	tcg_gen_mov_tl(pc_val, tmp_9);
	tcg_gen_br(l_Blt_361_3);
	gen_set_label(exit_Blt_361_2);
	ctx->base.is_jmp = DISAS_NORETURN;
	tcg_gen_mov_tl(cpu_pc, pc_val);
	tcg_gen_lookup_and_goto_ptr(); // FIXME: because developer is too lazy to update ctx->base.pc_next manually
	return true;
}

static bool trans_Blt(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_0 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_1 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = extract32(arg_2, 11, 1);
	uint64_t tmp_8 = extract32(arg_2, 0, 1);
	uint64_t tmp_9 = (tmp_7 << 1) | tmp_8;
	uint64_t tmp_10 = extract32(arg_2, 1, 10);
	uint64_t tmp_11 = (tmp_9 << 10) | tmp_10;
	uint64_t tmp_12 = (tmp_11 << 1) | 0b0;
	uint64_t tmp_13 = sextract64(tmp_12, 0, 13);
	tcg_trans_Blt(ctx, tmp_4, tmp_6, tmp_13);
	return true;
}

static bool tcg_trans_Bge(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Bge_475_0 = gen_new_label();
	TCGLabel *l_Bge_205_1 = gen_new_label();
	TCGLabel *exit_Bge_228_2 = gen_new_label();
	TCGLabel *l_Bge_228_3 = gen_new_label();
	TCGLabel *l_Bge_30_4 = gen_new_label();
	TCGLabel *l_Bge_304_5 = gen_new_label();
	TCGLabel *exit_Bge_373_6 = gen_new_label();
	TCGLabel *l_Bge_373_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Bge_304_5);
	} else {
		tcg_gen_br(l_Bge_30_4);
	}
	gen_set_label(l_Bge_30_4);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Bge_373_7);
	gen_set_label(l_Bge_373_7);
	tcg_gen_br(exit_Bge_373_6);
	gen_set_label(l_Bge_304_5);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_0 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Bge_373_7);
	gen_set_label(exit_Bge_373_6);
	TCGLabel *l_Bge_30_8 = gen_new_label();
	TCGLabel *l_Bge_304_9 = gen_new_label();
	TCGLabel *exit_Bge_373_10 = gen_new_label();
	TCGLabel *l_Bge_373_11 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Bge_304_9);
	} else {
		tcg_gen_br(l_Bge_30_8);
	}
	gen_set_label(l_Bge_30_8);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_Bge_373_11);
	gen_set_label(l_Bge_373_11);
	tcg_gen_br(exit_Bge_373_10);
	gen_set_label(l_Bge_304_9);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_Bge_373_11);
	gen_set_label(exit_Bge_373_10);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_setcond_tl(TCG_COND_GE, tmp_7, tmp_3, tmp_5);
	TCGLabel *branch_l_Bge_539_12 = gen_new_label();
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp_7, 0, branch_l_Bge_539_12);
	tcg_gen_br(l_Bge_205_1);
	gen_set_label(branch_l_Bge_539_12);
	tcg_gen_br(l_Bge_475_0);
	gen_set_label(l_Bge_475_0);
	tcg_gen_br(l_Bge_228_3);
	gen_set_label(l_Bge_228_3);
	tcg_gen_br(exit_Bge_228_2);
	gen_set_label(l_Bge_205_1);
	TCGv tmp_8 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_8, ctx->base.pc_next);
	TCGv tmp_9 = tcg_temp_new();
	tcg_gen_addi_tl(tmp_9, tmp_8, arg_2);
	tcg_gen_mov_tl(pc_val, tmp_9);
	tcg_gen_br(l_Bge_228_3);
	gen_set_label(exit_Bge_228_2);
	ctx->base.is_jmp = DISAS_NORETURN;
	tcg_gen_mov_tl(cpu_pc, pc_val);
	tcg_gen_lookup_and_goto_ptr(); // FIXME: because developer is too lazy to update ctx->base.pc_next manually
	return true;
}

static bool trans_Bge(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_1 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_0 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = extract32(arg_2, 11, 1);
	uint64_t tmp_8 = extract32(arg_2, 0, 1);
	uint64_t tmp_9 = (tmp_7 << 1) | tmp_8;
	uint64_t tmp_10 = extract32(arg_2, 1, 10);
	uint64_t tmp_11 = (tmp_9 << 10) | tmp_10;
	uint64_t tmp_12 = (tmp_11 << 1) | 0b0;
	uint64_t tmp_13 = sextract64(tmp_12, 0, 13);
	tcg_trans_Bge(ctx, tmp_4, tmp_6, tmp_13);
	return true;
}

static bool tcg_trans_Bltu(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Bltu_282_0 = gen_new_label();
	TCGLabel *l_Bltu_251_1 = gen_new_label();
	TCGLabel *exit_Bltu_308_2 = gen_new_label();
	TCGLabel *l_Bltu_308_3 = gen_new_label();
	TCGLabel *l_Bltu_30_4 = gen_new_label();
	TCGLabel *l_Bltu_304_5 = gen_new_label();
	TCGLabel *exit_Bltu_373_6 = gen_new_label();
	TCGLabel *l_Bltu_373_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Bltu_304_5);
	} else {
		tcg_gen_br(l_Bltu_30_4);
	}
	gen_set_label(l_Bltu_30_4);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Bltu_373_7);
	gen_set_label(l_Bltu_373_7);
	tcg_gen_br(exit_Bltu_373_6);
	gen_set_label(l_Bltu_304_5);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_0 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Bltu_373_7);
	gen_set_label(exit_Bltu_373_6);
	TCGLabel *l_Bltu_30_8 = gen_new_label();
	TCGLabel *l_Bltu_304_9 = gen_new_label();
	TCGLabel *exit_Bltu_373_10 = gen_new_label();
	TCGLabel *l_Bltu_373_11 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Bltu_304_9);
	} else {
		tcg_gen_br(l_Bltu_30_8);
	}
	gen_set_label(l_Bltu_30_8);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_Bltu_373_11);
	gen_set_label(l_Bltu_373_11);
	tcg_gen_br(exit_Bltu_373_10);
	gen_set_label(l_Bltu_304_9);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_Bltu_373_11);
	gen_set_label(exit_Bltu_373_10);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_setcond_tl(TCG_COND_LTU, tmp_7, tmp_3, tmp_5);
	TCGLabel *branch_l_Bltu_167_12 = gen_new_label();
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp_7, 0, branch_l_Bltu_167_12);
	tcg_gen_br(l_Bltu_251_1);
	gen_set_label(branch_l_Bltu_167_12);
	tcg_gen_br(l_Bltu_282_0);
	gen_set_label(l_Bltu_282_0);
	tcg_gen_br(l_Bltu_308_3);
	gen_set_label(l_Bltu_308_3);
	tcg_gen_br(exit_Bltu_308_2);
	gen_set_label(l_Bltu_251_1);
	TCGv tmp_8 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_8, ctx->base.pc_next);
	TCGv tmp_9 = tcg_temp_new();
	tcg_gen_addi_tl(tmp_9, tmp_8, arg_2);
	tcg_gen_mov_tl(pc_val, tmp_9);
	tcg_gen_br(l_Bltu_308_3);
	gen_set_label(exit_Bltu_308_2);
	ctx->base.is_jmp = DISAS_NORETURN;
	tcg_gen_mov_tl(cpu_pc, pc_val);
	tcg_gen_lookup_and_goto_ptr(); // FIXME: because developer is too lazy to update ctx->base.pc_next manually
	return true;
}

static bool trans_Bltu(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_2 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_1 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = extract32(arg_0, 11, 1);
	uint64_t tmp_8 = extract32(arg_0, 0, 1);
	uint64_t tmp_9 = (tmp_7 << 1) | tmp_8;
	uint64_t tmp_10 = extract32(arg_0, 1, 10);
	uint64_t tmp_11 = (tmp_9 << 10) | tmp_10;
	uint64_t tmp_12 = (tmp_11 << 1) | 0b0;
	uint64_t tmp_13 = sextract64(tmp_12, 0, 13);
	tcg_trans_Bltu(ctx, tmp_4, tmp_6, tmp_13);
	return true;
}

static bool tcg_trans_Bgeu(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Bgeu_424_0 = gen_new_label();
	TCGLabel *l_Bgeu_197_1 = gen_new_label();
	TCGLabel *exit_Bgeu_469_2 = gen_new_label();
	TCGLabel *l_Bgeu_469_3 = gen_new_label();
	TCGLabel *l_Bgeu_30_4 = gen_new_label();
	TCGLabel *l_Bgeu_304_5 = gen_new_label();
	TCGLabel *exit_Bgeu_373_6 = gen_new_label();
	TCGLabel *l_Bgeu_373_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Bgeu_304_5);
	} else {
		tcg_gen_br(l_Bgeu_30_4);
	}
	gen_set_label(l_Bgeu_30_4);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Bgeu_373_7);
	gen_set_label(l_Bgeu_373_7);
	tcg_gen_br(exit_Bgeu_373_6);
	gen_set_label(l_Bgeu_304_5);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_0 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Bgeu_373_7);
	gen_set_label(exit_Bgeu_373_6);
	TCGLabel *l_Bgeu_30_8 = gen_new_label();
	TCGLabel *l_Bgeu_304_9 = gen_new_label();
	TCGLabel *exit_Bgeu_373_10 = gen_new_label();
	TCGLabel *l_Bgeu_373_11 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Bgeu_304_9);
	} else {
		tcg_gen_br(l_Bgeu_30_8);
	}
	gen_set_label(l_Bgeu_30_8);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_Bgeu_373_11);
	gen_set_label(l_Bgeu_373_11);
	tcg_gen_br(exit_Bgeu_373_10);
	gen_set_label(l_Bgeu_304_9);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_Bgeu_373_11);
	gen_set_label(exit_Bgeu_373_10);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_setcond_tl(TCG_COND_GEU, tmp_7, tmp_3, tmp_5);
	TCGLabel *branch_l_Bgeu_506_12 = gen_new_label();
	tcg_gen_brcondi_tl(TCG_COND_EQ, tmp_7, 0, branch_l_Bgeu_506_12);
	tcg_gen_br(l_Bgeu_197_1);
	gen_set_label(branch_l_Bgeu_506_12);
	tcg_gen_br(l_Bgeu_424_0);
	gen_set_label(l_Bgeu_424_0);
	tcg_gen_br(l_Bgeu_469_3);
	gen_set_label(l_Bgeu_469_3);
	tcg_gen_br(exit_Bgeu_469_2);
	gen_set_label(l_Bgeu_197_1);
	TCGv tmp_8 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_8, ctx->base.pc_next);
	TCGv tmp_9 = tcg_temp_new();
	tcg_gen_addi_tl(tmp_9, tmp_8, arg_2);
	tcg_gen_mov_tl(pc_val, tmp_9);
	tcg_gen_br(l_Bgeu_469_3);
	gen_set_label(exit_Bgeu_469_2);
	ctx->base.is_jmp = DISAS_NORETURN;
	tcg_gen_mov_tl(cpu_pc, pc_val);
	tcg_gen_lookup_and_goto_ptr(); // FIXME: because developer is too lazy to update ctx->base.pc_next manually
	return true;
}

static bool trans_Bgeu(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_2 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_1 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = extract32(arg_0, 11, 1);
	uint64_t tmp_8 = extract32(arg_0, 0, 1);
	uint64_t tmp_9 = (tmp_7 << 1) | tmp_8;
	uint64_t tmp_10 = extract32(arg_0, 1, 10);
	uint64_t tmp_11 = (tmp_9 << 10) | tmp_10;
	uint64_t tmp_12 = (tmp_11 << 1) | 0b0;
	uint64_t tmp_13 = sextract64(tmp_12, 0, 13);
	tcg_trans_Bgeu(ctx, tmp_4, tmp_6, tmp_13);
	return true;
}

static bool tcg_trans_Lb(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Lb_30_0 = gen_new_label();
	TCGLabel *l_Lb_304_1 = gen_new_label();
	TCGLabel *exit_Lb_373_2 = gen_new_label();
	TCGLabel *l_Lb_373_3 = gen_new_label();
	if (((((arg_1 & 0x00000000FFFF) >> 0) != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Lb_304_1);
	} else {
		tcg_gen_br(l_Lb_30_0);
	}
	gen_set_label(l_Lb_30_0);
	TCGv tmp_2 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_2, 0x00000000);
	tcg_gen_br(l_Lb_373_3);
	gen_set_label(l_Lb_373_3);
	tcg_gen_br(exit_Lb_373_2);
	gen_set_label(l_Lb_304_1);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_3, get_gpr(ctx, ((arg_1 & 0x00000000FFFF) >> 0) / 4));
	tcg_gen_mov_tl(tmp_2, tmp_3);
	tcg_gen_br(l_Lb_373_3);
	gen_set_label(exit_Lb_373_2);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_addi_tl(tmp_4, tmp_2, ((arg_1 & 0xFFFFFFFF0000) >> 16));
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_qemu_ld_tl(tmp_5, tmp_4, 0, MO_8); // FIXME: developer was too lazy to think about sign
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_ext8s_tl(tmp_6, tmp_5);
	TCGLabel *l_Lb_515_4 = gen_new_label();
	TCGLabel *l_Lb_329_5 = gen_new_label();
	TCGLabel *exit_Lb_310_6 = gen_new_label();
	TCGLabel *l_Lb_310_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Lb_329_5);
	} else {
		tcg_gen_br(l_Lb_515_4);
	}
	gen_set_label(l_Lb_515_4);
	tcg_gen_br(l_Lb_310_7);
	gen_set_label(l_Lb_310_7);
	tcg_gen_br(exit_Lb_310_6);
	gen_set_label(l_Lb_329_5);
	set_gpr(ctx, arg_0 / 4, tmp_6);
	tcg_gen_br(l_Lb_310_7);
	gen_set_label(exit_Lb_310_6);
	return true;
}

static bool trans_Lb(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_0 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = sextract64(arg_2, 0, 12);
	uint64_t tmp_6 = arg_1 * 0x0004;
	uint64_t tmp_7 = 0x0000 + tmp_6;
	uint64_t tmp_8 = (tmp_5 << 16) | tmp_7;
	tcg_trans_Lb(ctx, tmp_4, tmp_8);
	return true;
}

static bool tcg_trans_Lh(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Lh_30_0 = gen_new_label();
	TCGLabel *l_Lh_304_1 = gen_new_label();
	TCGLabel *exit_Lh_373_2 = gen_new_label();
	TCGLabel *l_Lh_373_3 = gen_new_label();
	if (((((arg_1 & 0x00000000FFFF) >> 0) != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Lh_304_1);
	} else {
		tcg_gen_br(l_Lh_30_0);
	}
	gen_set_label(l_Lh_30_0);
	TCGv tmp_2 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_2, 0x00000000);
	tcg_gen_br(l_Lh_373_3);
	gen_set_label(l_Lh_373_3);
	tcg_gen_br(exit_Lh_373_2);
	gen_set_label(l_Lh_304_1);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_3, get_gpr(ctx, ((arg_1 & 0x00000000FFFF) >> 0) / 4));
	tcg_gen_mov_tl(tmp_2, tmp_3);
	tcg_gen_br(l_Lh_373_3);
	gen_set_label(exit_Lh_373_2);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_addi_tl(tmp_4, tmp_2, ((arg_1 & 0xFFFFFFFF0000) >> 16));
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_qemu_ld_tl(tmp_5, tmp_4, 0, MO_16); // FIXME: developer was too lazy to think about sign
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_ext16s_tl(tmp_6, tmp_5);
	TCGLabel *l_Lh_515_4 = gen_new_label();
	TCGLabel *l_Lh_329_5 = gen_new_label();
	TCGLabel *exit_Lh_310_6 = gen_new_label();
	TCGLabel *l_Lh_310_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Lh_329_5);
	} else {
		tcg_gen_br(l_Lh_515_4);
	}
	gen_set_label(l_Lh_515_4);
	tcg_gen_br(l_Lh_310_7);
	gen_set_label(l_Lh_310_7);
	tcg_gen_br(exit_Lh_310_6);
	gen_set_label(l_Lh_329_5);
	set_gpr(ctx, arg_0 / 4, tmp_6);
	tcg_gen_br(l_Lh_310_7);
	gen_set_label(exit_Lh_310_6);
	return true;
}

static bool trans_Lh(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_2 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = sextract64(arg_1, 0, 12);
	uint64_t tmp_6 = arg_0 * 0x0004;
	uint64_t tmp_7 = 0x0000 + tmp_6;
	uint64_t tmp_8 = (tmp_5 << 16) | tmp_7;
	tcg_trans_Lh(ctx, tmp_4, tmp_8);
	return true;
}

static bool tcg_trans_Lw(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Lw_30_0 = gen_new_label();
	TCGLabel *l_Lw_304_1 = gen_new_label();
	TCGLabel *exit_Lw_373_2 = gen_new_label();
	TCGLabel *l_Lw_373_3 = gen_new_label();
	if (((((arg_1 & 0x00000000FFFF) >> 0) != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Lw_304_1);
	} else {
		tcg_gen_br(l_Lw_30_0);
	}
	gen_set_label(l_Lw_30_0);
	TCGv tmp_2 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_2, 0x00000000);
	tcg_gen_br(l_Lw_373_3);
	gen_set_label(l_Lw_373_3);
	tcg_gen_br(exit_Lw_373_2);
	gen_set_label(l_Lw_304_1);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_3, get_gpr(ctx, ((arg_1 & 0x00000000FFFF) >> 0) / 4));
	tcg_gen_mov_tl(tmp_2, tmp_3);
	tcg_gen_br(l_Lw_373_3);
	gen_set_label(exit_Lw_373_2);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_addi_tl(tmp_4, tmp_2, ((arg_1 & 0xFFFFFFFF0000) >> 16));
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_qemu_ld_tl(tmp_5, tmp_4, 0, MO_32);
	TCGLabel *l_Lw_515_4 = gen_new_label();
	TCGLabel *l_Lw_329_5 = gen_new_label();
	TCGLabel *exit_Lw_310_6 = gen_new_label();
	TCGLabel *l_Lw_310_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Lw_329_5);
	} else {
		tcg_gen_br(l_Lw_515_4);
	}
	gen_set_label(l_Lw_515_4);
	tcg_gen_br(l_Lw_310_7);
	gen_set_label(l_Lw_310_7);
	tcg_gen_br(exit_Lw_310_6);
	gen_set_label(l_Lw_329_5);
	set_gpr(ctx, arg_0 / 4, tmp_5);
	tcg_gen_br(l_Lw_310_7);
	gen_set_label(exit_Lw_310_6);
	return true;
}

static bool trans_Lw(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_1 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = sextract64(arg_2, 0, 12);
	uint64_t tmp_6 = arg_0 * 0x0004;
	uint64_t tmp_7 = 0x0000 + tmp_6;
	uint64_t tmp_8 = (tmp_5 << 16) | tmp_7;
	tcg_trans_Lw(ctx, tmp_4, tmp_8);
	return true;
}

static bool tcg_trans_Lbu(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Lbu_30_0 = gen_new_label();
	TCGLabel *l_Lbu_304_1 = gen_new_label();
	TCGLabel *exit_Lbu_373_2 = gen_new_label();
	TCGLabel *l_Lbu_373_3 = gen_new_label();
	if (((((arg_1 & 0x00000000FFFF) >> 0) != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Lbu_304_1);
	} else {
		tcg_gen_br(l_Lbu_30_0);
	}
	gen_set_label(l_Lbu_30_0);
	TCGv tmp_2 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_2, 0x00000000);
	tcg_gen_br(l_Lbu_373_3);
	gen_set_label(l_Lbu_373_3);
	tcg_gen_br(exit_Lbu_373_2);
	gen_set_label(l_Lbu_304_1);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_3, get_gpr(ctx, ((arg_1 & 0x00000000FFFF) >> 0) / 4));
	tcg_gen_mov_tl(tmp_2, tmp_3);
	tcg_gen_br(l_Lbu_373_3);
	gen_set_label(exit_Lbu_373_2);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_addi_tl(tmp_4, tmp_2, ((arg_1 & 0xFFFFFFFF0000) >> 16));
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_qemu_ld_tl(tmp_5, tmp_4, 0, MO_8); // FIXME: developer was too lazy to think about sign
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_ext8u_tl(tmp_6, tmp_5);
	TCGLabel *l_Lbu_515_4 = gen_new_label();
	TCGLabel *l_Lbu_329_5 = gen_new_label();
	TCGLabel *exit_Lbu_310_6 = gen_new_label();
	TCGLabel *l_Lbu_310_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Lbu_329_5);
	} else {
		tcg_gen_br(l_Lbu_515_4);
	}
	gen_set_label(l_Lbu_515_4);
	tcg_gen_br(l_Lbu_310_7);
	gen_set_label(l_Lbu_310_7);
	tcg_gen_br(exit_Lbu_310_6);
	gen_set_label(l_Lbu_329_5);
	set_gpr(ctx, arg_0 / 4, tmp_6);
	tcg_gen_br(l_Lbu_310_7);
	gen_set_label(exit_Lbu_310_6);
	return true;
}

static bool trans_Lbu(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_0 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = sextract64(arg_1, 0, 12);
	uint64_t tmp_6 = arg_2 * 0x0004;
	uint64_t tmp_7 = 0x0000 + tmp_6;
	uint64_t tmp_8 = (tmp_5 << 16) | tmp_7;
	tcg_trans_Lbu(ctx, tmp_4, tmp_8);
	return true;
}

static bool tcg_trans_Lhu(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Lhu_30_0 = gen_new_label();
	TCGLabel *l_Lhu_304_1 = gen_new_label();
	TCGLabel *exit_Lhu_373_2 = gen_new_label();
	TCGLabel *l_Lhu_373_3 = gen_new_label();
	if (((((arg_1 & 0x00000000FFFF) >> 0) != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Lhu_304_1);
	} else {
		tcg_gen_br(l_Lhu_30_0);
	}
	gen_set_label(l_Lhu_30_0);
	TCGv tmp_2 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_2, 0x00000000);
	tcg_gen_br(l_Lhu_373_3);
	gen_set_label(l_Lhu_373_3);
	tcg_gen_br(exit_Lhu_373_2);
	gen_set_label(l_Lhu_304_1);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_3, get_gpr(ctx, ((arg_1 & 0x00000000FFFF) >> 0) / 4));
	tcg_gen_mov_tl(tmp_2, tmp_3);
	tcg_gen_br(l_Lhu_373_3);
	gen_set_label(exit_Lhu_373_2);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_addi_tl(tmp_4, tmp_2, ((arg_1 & 0xFFFFFFFF0000) >> 16));
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_qemu_ld_tl(tmp_5, tmp_4, 0, MO_16); // FIXME: developer was too lazy to think about sign
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_ext16u_tl(tmp_6, tmp_5);
	TCGLabel *l_Lhu_515_4 = gen_new_label();
	TCGLabel *l_Lhu_329_5 = gen_new_label();
	TCGLabel *exit_Lhu_310_6 = gen_new_label();
	TCGLabel *l_Lhu_310_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Lhu_329_5);
	} else {
		tcg_gen_br(l_Lhu_515_4);
	}
	gen_set_label(l_Lhu_515_4);
	tcg_gen_br(l_Lhu_310_7);
	gen_set_label(l_Lhu_310_7);
	tcg_gen_br(exit_Lhu_310_6);
	gen_set_label(l_Lhu_329_5);
	set_gpr(ctx, arg_0 / 4, tmp_6);
	tcg_gen_br(l_Lhu_310_7);
	gen_set_label(exit_Lhu_310_6);
	return true;
}

static bool trans_Lhu(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_0 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = sextract64(arg_2, 0, 12);
	uint64_t tmp_6 = arg_1 * 0x0004;
	uint64_t tmp_7 = 0x0000 + tmp_6;
	uint64_t tmp_8 = (tmp_5 << 16) | tmp_7;
	tcg_trans_Lhu(ctx, tmp_4, tmp_8);
	return true;
}

static bool tcg_trans_Sb(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Sb_30_0 = gen_new_label();
	TCGLabel *l_Sb_304_1 = gen_new_label();
	TCGLabel *exit_Sb_373_2 = gen_new_label();
	TCGLabel *l_Sb_373_3 = gen_new_label();
	if (((((arg_1 & 0x00000000FFFF) >> 0) != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sb_304_1);
	} else {
		tcg_gen_br(l_Sb_30_0);
	}
	gen_set_label(l_Sb_30_0);
	TCGv tmp_2 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_2, 0x00000000);
	tcg_gen_br(l_Sb_373_3);
	gen_set_label(l_Sb_373_3);
	tcg_gen_br(exit_Sb_373_2);
	gen_set_label(l_Sb_304_1);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_3, get_gpr(ctx, ((arg_1 & 0x00000000FFFF) >> 0) / 4));
	tcg_gen_mov_tl(tmp_2, tmp_3);
	tcg_gen_br(l_Sb_373_3);
	gen_set_label(exit_Sb_373_2);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_addi_tl(tmp_4, tmp_2, ((arg_1 & 0xFFFFFFFF0000) >> 16));
	TCGLabel *l_Sb_30_4 = gen_new_label();
	TCGLabel *l_Sb_304_5 = gen_new_label();
	TCGLabel *exit_Sb_373_6 = gen_new_label();
	TCGLabel *l_Sb_373_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sb_304_5);
	} else {
		tcg_gen_br(l_Sb_30_4);
	}
	gen_set_label(l_Sb_30_4);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_Sb_373_7);
	gen_set_label(l_Sb_373_7);
	tcg_gen_br(exit_Sb_373_6);
	gen_set_label(l_Sb_304_5);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_0 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_Sb_373_7);
	gen_set_label(exit_Sb_373_6);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_andi_tl(tmp_7, tmp_5, 0x000000FF);
	tcg_gen_qemu_st_tl(tmp_7, tmp_4, 0, MO_8);
	return true;
}

static bool trans_Sb(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_2 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = sextract64(arg_0, 0, 12);
	uint64_t tmp_6 = arg_1 * 0x0004;
	uint64_t tmp_7 = 0x0000 + tmp_6;
	uint64_t tmp_8 = (tmp_5 << 16) | tmp_7;
	tcg_trans_Sb(ctx, tmp_4, tmp_8);
	return true;
}

static bool tcg_trans_Sh(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Sh_30_0 = gen_new_label();
	TCGLabel *l_Sh_304_1 = gen_new_label();
	TCGLabel *exit_Sh_373_2 = gen_new_label();
	TCGLabel *l_Sh_373_3 = gen_new_label();
	if (((((arg_1 & 0x00000000FFFF) >> 0) != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sh_304_1);
	} else {
		tcg_gen_br(l_Sh_30_0);
	}
	gen_set_label(l_Sh_30_0);
	TCGv tmp_2 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_2, 0x00000000);
	tcg_gen_br(l_Sh_373_3);
	gen_set_label(l_Sh_373_3);
	tcg_gen_br(exit_Sh_373_2);
	gen_set_label(l_Sh_304_1);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_3, get_gpr(ctx, ((arg_1 & 0x00000000FFFF) >> 0) / 4));
	tcg_gen_mov_tl(tmp_2, tmp_3);
	tcg_gen_br(l_Sh_373_3);
	gen_set_label(exit_Sh_373_2);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_addi_tl(tmp_4, tmp_2, ((arg_1 & 0xFFFFFFFF0000) >> 16));
	TCGLabel *l_Sh_30_4 = gen_new_label();
	TCGLabel *l_Sh_304_5 = gen_new_label();
	TCGLabel *exit_Sh_373_6 = gen_new_label();
	TCGLabel *l_Sh_373_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sh_304_5);
	} else {
		tcg_gen_br(l_Sh_30_4);
	}
	gen_set_label(l_Sh_30_4);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_Sh_373_7);
	gen_set_label(l_Sh_373_7);
	tcg_gen_br(exit_Sh_373_6);
	gen_set_label(l_Sh_304_5);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_0 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_Sh_373_7);
	gen_set_label(exit_Sh_373_6);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_andi_tl(tmp_7, tmp_5, 0x0000FFFF);
	tcg_gen_qemu_st_tl(tmp_7, tmp_4, 0, MO_16);
	return true;
}

static bool trans_Sh(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_1 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = sextract64(arg_0, 0, 12);
	uint64_t tmp_6 = arg_2 * 0x0004;
	uint64_t tmp_7 = 0x0000 + tmp_6;
	uint64_t tmp_8 = (tmp_5 << 16) | tmp_7;
	tcg_trans_Sh(ctx, tmp_4, tmp_8);
	return true;
}

static bool tcg_trans_Sw(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Sw_30_0 = gen_new_label();
	TCGLabel *l_Sw_304_1 = gen_new_label();
	TCGLabel *exit_Sw_373_2 = gen_new_label();
	TCGLabel *l_Sw_373_3 = gen_new_label();
	if (((((arg_1 & 0x00000000FFFF) >> 0) != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sw_304_1);
	} else {
		tcg_gen_br(l_Sw_30_0);
	}
	gen_set_label(l_Sw_30_0);
	TCGv tmp_2 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_2, 0x00000000);
	tcg_gen_br(l_Sw_373_3);
	gen_set_label(l_Sw_373_3);
	tcg_gen_br(exit_Sw_373_2);
	gen_set_label(l_Sw_304_1);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_3, get_gpr(ctx, ((arg_1 & 0x00000000FFFF) >> 0) / 4));
	tcg_gen_mov_tl(tmp_2, tmp_3);
	tcg_gen_br(l_Sw_373_3);
	gen_set_label(exit_Sw_373_2);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_addi_tl(tmp_4, tmp_2, ((arg_1 & 0xFFFFFFFF0000) >> 16));
	TCGLabel *l_Sw_30_4 = gen_new_label();
	TCGLabel *l_Sw_304_5 = gen_new_label();
	TCGLabel *exit_Sw_373_6 = gen_new_label();
	TCGLabel *l_Sw_373_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sw_304_5);
	} else {
		tcg_gen_br(l_Sw_30_4);
	}
	gen_set_label(l_Sw_30_4);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_Sw_373_7);
	gen_set_label(l_Sw_373_7);
	tcg_gen_br(exit_Sw_373_6);
	gen_set_label(l_Sw_304_5);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_0 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_Sw_373_7);
	gen_set_label(exit_Sw_373_6);
	tcg_gen_qemu_st_tl(tmp_5, tmp_4, 0, MO_32);
	return true;
}

static bool trans_Sw(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_1 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = sextract64(arg_0, 0, 12);
	uint64_t tmp_6 = arg_2 * 0x0004;
	uint64_t tmp_7 = 0x0000 + tmp_6;
	uint64_t tmp_8 = (tmp_5 << 16) | tmp_7;
	tcg_trans_Sw(ctx, tmp_4, tmp_8);
	return true;
}

static bool tcg_trans_Addi(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Addi_30_0 = gen_new_label();
	TCGLabel *l_Addi_304_1 = gen_new_label();
	TCGLabel *exit_Addi_373_2 = gen_new_label();
	TCGLabel *l_Addi_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Addi_304_1);
	} else {
		tcg_gen_br(l_Addi_30_0);
	}
	gen_set_label(l_Addi_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Addi_373_3);
	gen_set_label(l_Addi_373_3);
	tcg_gen_br(exit_Addi_373_2);
	gen_set_label(l_Addi_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Addi_373_3);
	gen_set_label(exit_Addi_373_2);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_addi_tl(tmp_5, tmp_3, arg_2);
	TCGLabel *l_Addi_515_4 = gen_new_label();
	TCGLabel *l_Addi_329_5 = gen_new_label();
	TCGLabel *exit_Addi_310_6 = gen_new_label();
	TCGLabel *l_Addi_310_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Addi_329_5);
	} else {
		tcg_gen_br(l_Addi_515_4);
	}
	gen_set_label(l_Addi_515_4);
	tcg_gen_br(l_Addi_310_7);
	gen_set_label(l_Addi_310_7);
	tcg_gen_br(exit_Addi_310_6);
	gen_set_label(l_Addi_329_5);
	set_gpr(ctx, arg_0 / 4, tmp_5);
	tcg_gen_br(l_Addi_310_7);
	gen_set_label(exit_Addi_310_6);
	return true;
}

static bool trans_Addi(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_0 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_2 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = sextract64(arg_1, 0, 12);
	tcg_trans_Addi(ctx, tmp_4, tmp_6, tmp_7);
	return true;
}

static bool tcg_trans_Slti(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Slti_30_0 = gen_new_label();
	TCGLabel *l_Slti_304_1 = gen_new_label();
	TCGLabel *exit_Slti_373_2 = gen_new_label();
	TCGLabel *l_Slti_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Slti_304_1);
	} else {
		tcg_gen_br(l_Slti_30_0);
	}
	gen_set_label(l_Slti_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Slti_373_3);
	gen_set_label(l_Slti_373_3);
	tcg_gen_br(exit_Slti_373_2);
	gen_set_label(l_Slti_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Slti_373_3);
	gen_set_label(exit_Slti_373_2);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_setcondi_tl(TCG_COND_LT, tmp_5, tmp_3, arg_2);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_ext32u_i64 /* FIXME to 63 */ (tmp_6, tmp_5);
	TCGLabel *l_Slti_515_4 = gen_new_label();
	TCGLabel *l_Slti_329_5 = gen_new_label();
	TCGLabel *exit_Slti_310_6 = gen_new_label();
	TCGLabel *l_Slti_310_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Slti_329_5);
	} else {
		tcg_gen_br(l_Slti_515_4);
	}
	gen_set_label(l_Slti_515_4);
	tcg_gen_br(l_Slti_310_7);
	gen_set_label(l_Slti_310_7);
	tcg_gen_br(exit_Slti_310_6);
	gen_set_label(l_Slti_329_5);
	set_gpr(ctx, arg_0 / 4, tmp_6);
	tcg_gen_br(l_Slti_310_7);
	gen_set_label(exit_Slti_310_6);
	return true;
}

static bool trans_Slti(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_2 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_1 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = sextract64(arg_0, 0, 12);
	tcg_trans_Slti(ctx, tmp_4, tmp_6, tmp_7);
	return true;
}

static bool tcg_trans_Sltiu(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Sltiu_30_0 = gen_new_label();
	TCGLabel *l_Sltiu_304_1 = gen_new_label();
	TCGLabel *exit_Sltiu_373_2 = gen_new_label();
	TCGLabel *l_Sltiu_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sltiu_304_1);
	} else {
		tcg_gen_br(l_Sltiu_30_0);
	}
	gen_set_label(l_Sltiu_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Sltiu_373_3);
	gen_set_label(l_Sltiu_373_3);
	tcg_gen_br(exit_Sltiu_373_2);
	gen_set_label(l_Sltiu_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Sltiu_373_3);
	gen_set_label(exit_Sltiu_373_2);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_setcondi_tl(TCG_COND_LTU, tmp_5, tmp_3, arg_2);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_ext32u_i64 /* FIXME to 63 */ (tmp_6, tmp_5);
	TCGLabel *l_Sltiu_515_4 = gen_new_label();
	TCGLabel *l_Sltiu_329_5 = gen_new_label();
	TCGLabel *exit_Sltiu_310_6 = gen_new_label();
	TCGLabel *l_Sltiu_310_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sltiu_329_5);
	} else {
		tcg_gen_br(l_Sltiu_515_4);
	}
	gen_set_label(l_Sltiu_515_4);
	tcg_gen_br(l_Sltiu_310_7);
	gen_set_label(l_Sltiu_310_7);
	tcg_gen_br(exit_Sltiu_310_6);
	gen_set_label(l_Sltiu_329_5);
	set_gpr(ctx, arg_0 / 4, tmp_6);
	tcg_gen_br(l_Sltiu_310_7);
	gen_set_label(exit_Sltiu_310_6);
	return true;
}

static bool trans_Sltiu(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_2 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_1 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = sextract64(arg_0, 0, 12);
	tcg_trans_Sltiu(ctx, tmp_4, tmp_6, tmp_7);
	return true;
}

static bool tcg_trans_Xori(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Xori_30_0 = gen_new_label();
	TCGLabel *l_Xori_304_1 = gen_new_label();
	TCGLabel *exit_Xori_373_2 = gen_new_label();
	TCGLabel *l_Xori_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Xori_304_1);
	} else {
		tcg_gen_br(l_Xori_30_0);
	}
	gen_set_label(l_Xori_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Xori_373_3);
	gen_set_label(l_Xori_373_3);
	tcg_gen_br(exit_Xori_373_2);
	gen_set_label(l_Xori_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Xori_373_3);
	gen_set_label(exit_Xori_373_2);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_xori_tl(tmp_5, tmp_3, arg_2);
	TCGLabel *l_Xori_515_4 = gen_new_label();
	TCGLabel *l_Xori_329_5 = gen_new_label();
	TCGLabel *exit_Xori_310_6 = gen_new_label();
	TCGLabel *l_Xori_310_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Xori_329_5);
	} else {
		tcg_gen_br(l_Xori_515_4);
	}
	gen_set_label(l_Xori_515_4);
	tcg_gen_br(l_Xori_310_7);
	gen_set_label(l_Xori_310_7);
	tcg_gen_br(exit_Xori_310_6);
	gen_set_label(l_Xori_329_5);
	set_gpr(ctx, arg_0 / 4, tmp_5);
	tcg_gen_br(l_Xori_310_7);
	gen_set_label(exit_Xori_310_6);
	return true;
}

static bool trans_Xori(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_0 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_2 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = sextract64(arg_1, 0, 12);
	tcg_trans_Xori(ctx, tmp_4, tmp_6, tmp_7);
	return true;
}

static bool tcg_trans_Ori(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Ori_30_0 = gen_new_label();
	TCGLabel *l_Ori_304_1 = gen_new_label();
	TCGLabel *exit_Ori_373_2 = gen_new_label();
	TCGLabel *l_Ori_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Ori_304_1);
	} else {
		tcg_gen_br(l_Ori_30_0);
	}
	gen_set_label(l_Ori_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Ori_373_3);
	gen_set_label(l_Ori_373_3);
	tcg_gen_br(exit_Ori_373_2);
	gen_set_label(l_Ori_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Ori_373_3);
	gen_set_label(exit_Ori_373_2);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_ori_tl(tmp_5, tmp_3, arg_2);
	TCGLabel *l_Ori_515_4 = gen_new_label();
	TCGLabel *l_Ori_329_5 = gen_new_label();
	TCGLabel *exit_Ori_310_6 = gen_new_label();
	TCGLabel *l_Ori_310_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Ori_329_5);
	} else {
		tcg_gen_br(l_Ori_515_4);
	}
	gen_set_label(l_Ori_515_4);
	tcg_gen_br(l_Ori_310_7);
	gen_set_label(l_Ori_310_7);
	tcg_gen_br(exit_Ori_310_6);
	gen_set_label(l_Ori_329_5);
	set_gpr(ctx, arg_0 / 4, tmp_5);
	tcg_gen_br(l_Ori_310_7);
	gen_set_label(exit_Ori_310_6);
	return true;
}

static bool trans_Ori(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_2 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_1 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = sextract64(arg_0, 0, 12);
	tcg_trans_Ori(ctx, tmp_4, tmp_6, tmp_7);
	return true;
}

static bool tcg_trans_Andi(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Andi_30_0 = gen_new_label();
	TCGLabel *l_Andi_304_1 = gen_new_label();
	TCGLabel *exit_Andi_373_2 = gen_new_label();
	TCGLabel *l_Andi_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Andi_304_1);
	} else {
		tcg_gen_br(l_Andi_30_0);
	}
	gen_set_label(l_Andi_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Andi_373_3);
	gen_set_label(l_Andi_373_3);
	tcg_gen_br(exit_Andi_373_2);
	gen_set_label(l_Andi_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Andi_373_3);
	gen_set_label(exit_Andi_373_2);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_andi_tl(tmp_5, tmp_3, arg_2);
	TCGLabel *l_Andi_515_4 = gen_new_label();
	TCGLabel *l_Andi_329_5 = gen_new_label();
	TCGLabel *exit_Andi_310_6 = gen_new_label();
	TCGLabel *l_Andi_310_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Andi_329_5);
	} else {
		tcg_gen_br(l_Andi_515_4);
	}
	gen_set_label(l_Andi_515_4);
	tcg_gen_br(l_Andi_310_7);
	gen_set_label(l_Andi_310_7);
	tcg_gen_br(exit_Andi_310_6);
	gen_set_label(l_Andi_329_5);
	set_gpr(ctx, arg_0 / 4, tmp_5);
	tcg_gen_br(l_Andi_310_7);
	gen_set_label(exit_Andi_310_6);
	return true;
}

static bool trans_Andi(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_0 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_2 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = sextract64(arg_1, 0, 12);
	tcg_trans_Andi(ctx, tmp_4, tmp_6, tmp_7);
	return true;
}

static bool tcg_trans_Slli(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Slli_30_0 = gen_new_label();
	TCGLabel *l_Slli_304_1 = gen_new_label();
	TCGLabel *exit_Slli_373_2 = gen_new_label();
	TCGLabel *l_Slli_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Slli_304_1);
	} else {
		tcg_gen_br(l_Slli_30_0);
	}
	gen_set_label(l_Slli_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Slli_373_3);
	gen_set_label(l_Slli_373_3);
	tcg_gen_br(exit_Slli_373_2);
	gen_set_label(l_Slli_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Slli_373_3);
	gen_set_label(exit_Slli_373_2);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_shli_tl(tmp_6, tmp_3, ((arg_2 & 0x0000001F) ? 1 : 0));
	TCGLabel *l_Slli_515_4 = gen_new_label();
	TCGLabel *l_Slli_329_5 = gen_new_label();
	TCGLabel *exit_Slli_310_6 = gen_new_label();
	TCGLabel *l_Slli_310_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Slli_329_5);
	} else {
		tcg_gen_br(l_Slli_515_4);
	}
	gen_set_label(l_Slli_515_4);
	tcg_gen_br(l_Slli_310_7);
	gen_set_label(l_Slli_310_7);
	tcg_gen_br(exit_Slli_310_6);
	gen_set_label(l_Slli_329_5);
	set_gpr(ctx, arg_0 / 4, tmp_6);
	tcg_gen_br(l_Slli_310_7);
	gen_set_label(exit_Slli_310_6);
	return true;
}

static bool trans_Slli(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_2 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_0 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = sextract64(arg_1, 0, 5);
	tcg_trans_Slli(ctx, tmp_4, tmp_6, tmp_7);
	return true;
}

static bool tcg_trans_Srli(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Srli_30_0 = gen_new_label();
	TCGLabel *l_Srli_304_1 = gen_new_label();
	TCGLabel *exit_Srli_373_2 = gen_new_label();
	TCGLabel *l_Srli_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Srli_304_1);
	} else {
		tcg_gen_br(l_Srli_30_0);
	}
	gen_set_label(l_Srli_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Srli_373_3);
	gen_set_label(l_Srli_373_3);
	tcg_gen_br(exit_Srli_373_2);
	gen_set_label(l_Srli_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Srli_373_3);
	gen_set_label(exit_Srli_373_2);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_shri_tl(tmp_6, tmp_3, ((arg_2 & 0x0000001F) ? 1 : 0));
	TCGLabel *l_Srli_515_4 = gen_new_label();
	TCGLabel *l_Srli_329_5 = gen_new_label();
	TCGLabel *exit_Srli_310_6 = gen_new_label();
	TCGLabel *l_Srli_310_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Srli_329_5);
	} else {
		tcg_gen_br(l_Srli_515_4);
	}
	gen_set_label(l_Srli_515_4);
	tcg_gen_br(l_Srli_310_7);
	gen_set_label(l_Srli_310_7);
	tcg_gen_br(exit_Srli_310_6);
	gen_set_label(l_Srli_329_5);
	set_gpr(ctx, arg_0 / 4, tmp_6);
	tcg_gen_br(l_Srli_310_7);
	gen_set_label(exit_Srli_310_6);
	return true;
}

static bool trans_Srli(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_0 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_2 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = sextract64(arg_1, 0, 5);
	tcg_trans_Srli(ctx, tmp_4, tmp_6, tmp_7);
	return true;
}

static bool tcg_trans_Srai(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Srai_30_0 = gen_new_label();
	TCGLabel *l_Srai_304_1 = gen_new_label();
	TCGLabel *exit_Srai_373_2 = gen_new_label();
	TCGLabel *l_Srai_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Srai_304_1);
	} else {
		tcg_gen_br(l_Srai_30_0);
	}
	gen_set_label(l_Srai_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Srai_373_3);
	gen_set_label(l_Srai_373_3);
	tcg_gen_br(exit_Srai_373_2);
	gen_set_label(l_Srai_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Srai_373_3);
	gen_set_label(exit_Srai_373_2);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_sari_tl(tmp_6, tmp_3, ((arg_2 & 0x0000001F) ? 1 : 0));
	TCGLabel *l_Srai_515_4 = gen_new_label();
	TCGLabel *l_Srai_329_5 = gen_new_label();
	TCGLabel *exit_Srai_310_6 = gen_new_label();
	TCGLabel *l_Srai_310_7 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Srai_329_5);
	} else {
		tcg_gen_br(l_Srai_515_4);
	}
	gen_set_label(l_Srai_515_4);
	tcg_gen_br(l_Srai_310_7);
	gen_set_label(l_Srai_310_7);
	tcg_gen_br(exit_Srai_310_6);
	gen_set_label(l_Srai_329_5);
	set_gpr(ctx, arg_0 / 4, tmp_6);
	tcg_gen_br(l_Srai_310_7);
	gen_set_label(exit_Srai_310_6);
	return true;
}

static bool trans_Srai(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_0 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_2 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = sextract64(arg_1, 0, 5);
	tcg_trans_Srai(ctx, tmp_4, tmp_6, tmp_7);
	return true;
}

static bool tcg_trans_Add(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Add_30_0 = gen_new_label();
	TCGLabel *l_Add_304_1 = gen_new_label();
	TCGLabel *exit_Add_373_2 = gen_new_label();
	TCGLabel *l_Add_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Add_304_1);
	} else {
		tcg_gen_br(l_Add_30_0);
	}
	gen_set_label(l_Add_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Add_373_3);
	gen_set_label(l_Add_373_3);
	tcg_gen_br(exit_Add_373_2);
	gen_set_label(l_Add_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Add_373_3);
	gen_set_label(exit_Add_373_2);
	TCGLabel *l_Add_30_4 = gen_new_label();
	TCGLabel *l_Add_304_5 = gen_new_label();
	TCGLabel *exit_Add_373_6 = gen_new_label();
	TCGLabel *l_Add_373_7 = gen_new_label();
	if (((arg_2 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Add_304_5);
	} else {
		tcg_gen_br(l_Add_30_4);
	}
	gen_set_label(l_Add_30_4);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_Add_373_7);
	gen_set_label(l_Add_373_7);
	tcg_gen_br(exit_Add_373_6);
	gen_set_label(l_Add_304_5);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_2 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_Add_373_7);
	gen_set_label(exit_Add_373_6);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_add_tl(tmp_7, tmp_3, tmp_5);
	TCGLabel *l_Add_515_8 = gen_new_label();
	TCGLabel *l_Add_329_9 = gen_new_label();
	TCGLabel *exit_Add_310_10 = gen_new_label();
	TCGLabel *l_Add_310_11 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Add_329_9);
	} else {
		tcg_gen_br(l_Add_515_8);
	}
	gen_set_label(l_Add_515_8);
	tcg_gen_br(l_Add_310_11);
	gen_set_label(l_Add_310_11);
	tcg_gen_br(exit_Add_310_10);
	gen_set_label(l_Add_329_9);
	set_gpr(ctx, arg_0 / 4, tmp_7);
	tcg_gen_br(l_Add_310_11);
	gen_set_label(exit_Add_310_10);
	return true;
}

static bool trans_Add(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_1 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_2 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = arg_0 * 0x0004;
	uint64_t tmp_8 = 0x0000 + tmp_7;
	tcg_trans_Add(ctx, tmp_4, tmp_6, tmp_8);
	return true;
}

static bool tcg_trans_Sub(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Sub_30_0 = gen_new_label();
	TCGLabel *l_Sub_304_1 = gen_new_label();
	TCGLabel *exit_Sub_373_2 = gen_new_label();
	TCGLabel *l_Sub_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sub_304_1);
	} else {
		tcg_gen_br(l_Sub_30_0);
	}
	gen_set_label(l_Sub_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Sub_373_3);
	gen_set_label(l_Sub_373_3);
	tcg_gen_br(exit_Sub_373_2);
	gen_set_label(l_Sub_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Sub_373_3);
	gen_set_label(exit_Sub_373_2);
	TCGLabel *l_Sub_30_4 = gen_new_label();
	TCGLabel *l_Sub_304_5 = gen_new_label();
	TCGLabel *exit_Sub_373_6 = gen_new_label();
	TCGLabel *l_Sub_373_7 = gen_new_label();
	if (((arg_2 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sub_304_5);
	} else {
		tcg_gen_br(l_Sub_30_4);
	}
	gen_set_label(l_Sub_30_4);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_Sub_373_7);
	gen_set_label(l_Sub_373_7);
	tcg_gen_br(exit_Sub_373_6);
	gen_set_label(l_Sub_304_5);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_2 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_Sub_373_7);
	gen_set_label(exit_Sub_373_6);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_sub_tl(tmp_7, tmp_3, tmp_5);
	TCGLabel *l_Sub_515_8 = gen_new_label();
	TCGLabel *l_Sub_329_9 = gen_new_label();
	TCGLabel *exit_Sub_310_10 = gen_new_label();
	TCGLabel *l_Sub_310_11 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sub_329_9);
	} else {
		tcg_gen_br(l_Sub_515_8);
	}
	gen_set_label(l_Sub_515_8);
	tcg_gen_br(l_Sub_310_11);
	gen_set_label(l_Sub_310_11);
	tcg_gen_br(exit_Sub_310_10);
	gen_set_label(l_Sub_329_9);
	set_gpr(ctx, arg_0 / 4, tmp_7);
	tcg_gen_br(l_Sub_310_11);
	gen_set_label(exit_Sub_310_10);
	return true;
}

static bool trans_Sub(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_0 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_2 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = arg_1 * 0x0004;
	uint64_t tmp_8 = 0x0000 + tmp_7;
	tcg_trans_Sub(ctx, tmp_4, tmp_6, tmp_8);
	return true;
}

static bool tcg_trans_Sll(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Sll_30_0 = gen_new_label();
	TCGLabel *l_Sll_304_1 = gen_new_label();
	TCGLabel *exit_Sll_373_2 = gen_new_label();
	TCGLabel *l_Sll_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sll_304_1);
	} else {
		tcg_gen_br(l_Sll_30_0);
	}
	gen_set_label(l_Sll_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Sll_373_3);
	gen_set_label(l_Sll_373_3);
	tcg_gen_br(exit_Sll_373_2);
	gen_set_label(l_Sll_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Sll_373_3);
	gen_set_label(exit_Sll_373_2);
	TCGLabel *l_Sll_30_4 = gen_new_label();
	TCGLabel *l_Sll_304_5 = gen_new_label();
	TCGLabel *exit_Sll_373_6 = gen_new_label();
	TCGLabel *l_Sll_373_7 = gen_new_label();
	if (((arg_2 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sll_304_5);
	} else {
		tcg_gen_br(l_Sll_30_4);
	}
	gen_set_label(l_Sll_30_4);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_Sll_373_7);
	gen_set_label(l_Sll_373_7);
	tcg_gen_br(exit_Sll_373_6);
	gen_set_label(l_Sll_304_5);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_2 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_Sll_373_7);
	gen_set_label(exit_Sll_373_6);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_andi_tl(tmp_7, tmp_5, 0x0000001F);
	TCGv tmp_8 = tcg_temp_new();
	tcg_gen_shl_tl(tmp_8, tmp_3, tmp_7);
	TCGLabel *l_Sll_515_8 = gen_new_label();
	TCGLabel *l_Sll_329_9 = gen_new_label();
	TCGLabel *exit_Sll_310_10 = gen_new_label();
	TCGLabel *l_Sll_310_11 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sll_329_9);
	} else {
		tcg_gen_br(l_Sll_515_8);
	}
	gen_set_label(l_Sll_515_8);
	tcg_gen_br(l_Sll_310_11);
	gen_set_label(l_Sll_310_11);
	tcg_gen_br(exit_Sll_310_10);
	gen_set_label(l_Sll_329_9);
	set_gpr(ctx, arg_0 / 4, tmp_8);
	tcg_gen_br(l_Sll_310_11);
	gen_set_label(exit_Sll_310_10);
	return true;
}

static bool trans_Sll(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_1 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_2 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = arg_0 * 0x0004;
	uint64_t tmp_8 = 0x0000 + tmp_7;
	tcg_trans_Sll(ctx, tmp_4, tmp_6, tmp_8);
	return true;
}

static bool tcg_trans_Srl(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Srl_30_0 = gen_new_label();
	TCGLabel *l_Srl_304_1 = gen_new_label();
	TCGLabel *exit_Srl_373_2 = gen_new_label();
	TCGLabel *l_Srl_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Srl_304_1);
	} else {
		tcg_gen_br(l_Srl_30_0);
	}
	gen_set_label(l_Srl_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Srl_373_3);
	gen_set_label(l_Srl_373_3);
	tcg_gen_br(exit_Srl_373_2);
	gen_set_label(l_Srl_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Srl_373_3);
	gen_set_label(exit_Srl_373_2);
	TCGLabel *l_Srl_30_4 = gen_new_label();
	TCGLabel *l_Srl_304_5 = gen_new_label();
	TCGLabel *exit_Srl_373_6 = gen_new_label();
	TCGLabel *l_Srl_373_7 = gen_new_label();
	if (((arg_2 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Srl_304_5);
	} else {
		tcg_gen_br(l_Srl_30_4);
	}
	gen_set_label(l_Srl_30_4);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_Srl_373_7);
	gen_set_label(l_Srl_373_7);
	tcg_gen_br(exit_Srl_373_6);
	gen_set_label(l_Srl_304_5);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_2 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_Srl_373_7);
	gen_set_label(exit_Srl_373_6);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_andi_tl(tmp_7, tmp_5, 0x0000001F);
	TCGv tmp_8 = tcg_temp_new();
	tcg_gen_shr_tl(tmp_8, tmp_3, tmp_7);
	TCGLabel *l_Srl_515_8 = gen_new_label();
	TCGLabel *l_Srl_329_9 = gen_new_label();
	TCGLabel *exit_Srl_310_10 = gen_new_label();
	TCGLabel *l_Srl_310_11 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Srl_329_9);
	} else {
		tcg_gen_br(l_Srl_515_8);
	}
	gen_set_label(l_Srl_515_8);
	tcg_gen_br(l_Srl_310_11);
	gen_set_label(l_Srl_310_11);
	tcg_gen_br(exit_Srl_310_10);
	gen_set_label(l_Srl_329_9);
	set_gpr(ctx, arg_0 / 4, tmp_8);
	tcg_gen_br(l_Srl_310_11);
	gen_set_label(exit_Srl_310_10);
	return true;
}

static bool trans_Srl(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_1 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_0 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = arg_2 * 0x0004;
	uint64_t tmp_8 = 0x0000 + tmp_7;
	tcg_trans_Srl(ctx, tmp_4, tmp_6, tmp_8);
	return true;
}

static bool tcg_trans_Slt(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Slt_30_0 = gen_new_label();
	TCGLabel *l_Slt_304_1 = gen_new_label();
	TCGLabel *exit_Slt_373_2 = gen_new_label();
	TCGLabel *l_Slt_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Slt_304_1);
	} else {
		tcg_gen_br(l_Slt_30_0);
	}
	gen_set_label(l_Slt_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Slt_373_3);
	gen_set_label(l_Slt_373_3);
	tcg_gen_br(exit_Slt_373_2);
	gen_set_label(l_Slt_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Slt_373_3);
	gen_set_label(exit_Slt_373_2);
	TCGLabel *l_Slt_30_4 = gen_new_label();
	TCGLabel *l_Slt_304_5 = gen_new_label();
	TCGLabel *exit_Slt_373_6 = gen_new_label();
	TCGLabel *l_Slt_373_7 = gen_new_label();
	if (((arg_2 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Slt_304_5);
	} else {
		tcg_gen_br(l_Slt_30_4);
	}
	gen_set_label(l_Slt_30_4);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_Slt_373_7);
	gen_set_label(l_Slt_373_7);
	tcg_gen_br(exit_Slt_373_6);
	gen_set_label(l_Slt_304_5);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_2 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_Slt_373_7);
	gen_set_label(exit_Slt_373_6);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_setcond_tl(TCG_COND_LT, tmp_7, tmp_3, tmp_5);
	TCGv tmp_8 = tcg_temp_new();
	tcg_gen_ext32u_i64 /* FIXME to 63 */ (tmp_8, tmp_7);
	TCGLabel *l_Slt_515_8 = gen_new_label();
	TCGLabel *l_Slt_329_9 = gen_new_label();
	TCGLabel *exit_Slt_310_10 = gen_new_label();
	TCGLabel *l_Slt_310_11 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Slt_329_9);
	} else {
		tcg_gen_br(l_Slt_515_8);
	}
	gen_set_label(l_Slt_515_8);
	tcg_gen_br(l_Slt_310_11);
	gen_set_label(l_Slt_310_11);
	tcg_gen_br(exit_Slt_310_10);
	gen_set_label(l_Slt_329_9);
	set_gpr(ctx, arg_0 / 4, tmp_8);
	tcg_gen_br(l_Slt_310_11);
	gen_set_label(exit_Slt_310_10);
	return true;
}

static bool trans_Slt(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_1 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_0 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = arg_2 * 0x0004;
	uint64_t tmp_8 = 0x0000 + tmp_7;
	tcg_trans_Slt(ctx, tmp_4, tmp_6, tmp_8);
	return true;
}

static bool tcg_trans_Sltu(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Sltu_30_0 = gen_new_label();
	TCGLabel *l_Sltu_304_1 = gen_new_label();
	TCGLabel *exit_Sltu_373_2 = gen_new_label();
	TCGLabel *l_Sltu_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sltu_304_1);
	} else {
		tcg_gen_br(l_Sltu_30_0);
	}
	gen_set_label(l_Sltu_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Sltu_373_3);
	gen_set_label(l_Sltu_373_3);
	tcg_gen_br(exit_Sltu_373_2);
	gen_set_label(l_Sltu_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Sltu_373_3);
	gen_set_label(exit_Sltu_373_2);
	TCGLabel *l_Sltu_30_4 = gen_new_label();
	TCGLabel *l_Sltu_304_5 = gen_new_label();
	TCGLabel *exit_Sltu_373_6 = gen_new_label();
	TCGLabel *l_Sltu_373_7 = gen_new_label();
	if (((arg_2 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sltu_304_5);
	} else {
		tcg_gen_br(l_Sltu_30_4);
	}
	gen_set_label(l_Sltu_30_4);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_Sltu_373_7);
	gen_set_label(l_Sltu_373_7);
	tcg_gen_br(exit_Sltu_373_6);
	gen_set_label(l_Sltu_304_5);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_2 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_Sltu_373_7);
	gen_set_label(exit_Sltu_373_6);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_setcond_tl(TCG_COND_LTU, tmp_7, tmp_3, tmp_5);
	TCGv tmp_8 = tcg_temp_new();
	tcg_gen_ext32u_i64 /* FIXME to 63 */ (tmp_8, tmp_7);
	TCGLabel *l_Sltu_515_8 = gen_new_label();
	TCGLabel *l_Sltu_329_9 = gen_new_label();
	TCGLabel *exit_Sltu_310_10 = gen_new_label();
	TCGLabel *l_Sltu_310_11 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sltu_329_9);
	} else {
		tcg_gen_br(l_Sltu_515_8);
	}
	gen_set_label(l_Sltu_515_8);
	tcg_gen_br(l_Sltu_310_11);
	gen_set_label(l_Sltu_310_11);
	tcg_gen_br(exit_Sltu_310_10);
	gen_set_label(l_Sltu_329_9);
	set_gpr(ctx, arg_0 / 4, tmp_8);
	tcg_gen_br(l_Sltu_310_11);
	gen_set_label(exit_Sltu_310_10);
	return true;
}

static bool trans_Sltu(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_2 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_1 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = arg_0 * 0x0004;
	uint64_t tmp_8 = 0x0000 + tmp_7;
	tcg_trans_Sltu(ctx, tmp_4, tmp_6, tmp_8);
	return true;
}

static bool tcg_trans_Xor(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Xor_30_0 = gen_new_label();
	TCGLabel *l_Xor_304_1 = gen_new_label();
	TCGLabel *exit_Xor_373_2 = gen_new_label();
	TCGLabel *l_Xor_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Xor_304_1);
	} else {
		tcg_gen_br(l_Xor_30_0);
	}
	gen_set_label(l_Xor_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Xor_373_3);
	gen_set_label(l_Xor_373_3);
	tcg_gen_br(exit_Xor_373_2);
	gen_set_label(l_Xor_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Xor_373_3);
	gen_set_label(exit_Xor_373_2);
	TCGLabel *l_Xor_30_4 = gen_new_label();
	TCGLabel *l_Xor_304_5 = gen_new_label();
	TCGLabel *exit_Xor_373_6 = gen_new_label();
	TCGLabel *l_Xor_373_7 = gen_new_label();
	if (((arg_2 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Xor_304_5);
	} else {
		tcg_gen_br(l_Xor_30_4);
	}
	gen_set_label(l_Xor_30_4);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_Xor_373_7);
	gen_set_label(l_Xor_373_7);
	tcg_gen_br(exit_Xor_373_6);
	gen_set_label(l_Xor_304_5);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_2 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_Xor_373_7);
	gen_set_label(exit_Xor_373_6);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_xor_tl(tmp_7, tmp_3, tmp_5);
	TCGLabel *l_Xor_515_8 = gen_new_label();
	TCGLabel *l_Xor_329_9 = gen_new_label();
	TCGLabel *exit_Xor_310_10 = gen_new_label();
	TCGLabel *l_Xor_310_11 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Xor_329_9);
	} else {
		tcg_gen_br(l_Xor_515_8);
	}
	gen_set_label(l_Xor_515_8);
	tcg_gen_br(l_Xor_310_11);
	gen_set_label(l_Xor_310_11);
	tcg_gen_br(exit_Xor_310_10);
	gen_set_label(l_Xor_329_9);
	set_gpr(ctx, arg_0 / 4, tmp_7);
	tcg_gen_br(l_Xor_310_11);
	gen_set_label(exit_Xor_310_10);
	return true;
}

static bool trans_Xor(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_0 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_2 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = arg_1 * 0x0004;
	uint64_t tmp_8 = 0x0000 + tmp_7;
	tcg_trans_Xor(ctx, tmp_4, tmp_6, tmp_8);
	return true;
}

static bool tcg_trans_Sra(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Sra_30_0 = gen_new_label();
	TCGLabel *l_Sra_304_1 = gen_new_label();
	TCGLabel *exit_Sra_373_2 = gen_new_label();
	TCGLabel *l_Sra_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sra_304_1);
	} else {
		tcg_gen_br(l_Sra_30_0);
	}
	gen_set_label(l_Sra_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Sra_373_3);
	gen_set_label(l_Sra_373_3);
	tcg_gen_br(exit_Sra_373_2);
	gen_set_label(l_Sra_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Sra_373_3);
	gen_set_label(exit_Sra_373_2);
	TCGLabel *l_Sra_30_4 = gen_new_label();
	TCGLabel *l_Sra_304_5 = gen_new_label();
	TCGLabel *exit_Sra_373_6 = gen_new_label();
	TCGLabel *l_Sra_373_7 = gen_new_label();
	if (((arg_2 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sra_304_5);
	} else {
		tcg_gen_br(l_Sra_30_4);
	}
	gen_set_label(l_Sra_30_4);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_Sra_373_7);
	gen_set_label(l_Sra_373_7);
	tcg_gen_br(exit_Sra_373_6);
	gen_set_label(l_Sra_304_5);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_2 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_Sra_373_7);
	gen_set_label(exit_Sra_373_6);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_andi_tl(tmp_7, tmp_5, 0x0000001F);
	TCGv tmp_8 = tcg_temp_new();
	tcg_gen_shr_tl(tmp_8, tmp_3, tmp_7);
	TCGLabel *l_Sra_515_8 = gen_new_label();
	TCGLabel *l_Sra_329_9 = gen_new_label();
	TCGLabel *exit_Sra_310_10 = gen_new_label();
	TCGLabel *l_Sra_310_11 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Sra_329_9);
	} else {
		tcg_gen_br(l_Sra_515_8);
	}
	gen_set_label(l_Sra_515_8);
	tcg_gen_br(l_Sra_310_11);
	gen_set_label(l_Sra_310_11);
	tcg_gen_br(exit_Sra_310_10);
	gen_set_label(l_Sra_329_9);
	set_gpr(ctx, arg_0 / 4, tmp_8);
	tcg_gen_br(l_Sra_310_11);
	gen_set_label(exit_Sra_310_10);
	return true;
}

static bool trans_Sra(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_1 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_0 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = arg_2 * 0x0004;
	uint64_t tmp_8 = 0x0000 + tmp_7;
	tcg_trans_Sra(ctx, tmp_4, tmp_6, tmp_8);
	return true;
}

static bool tcg_trans_Or(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_Or_30_0 = gen_new_label();
	TCGLabel *l_Or_304_1 = gen_new_label();
	TCGLabel *exit_Or_373_2 = gen_new_label();
	TCGLabel *l_Or_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Or_304_1);
	} else {
		tcg_gen_br(l_Or_30_0);
	}
	gen_set_label(l_Or_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_Or_373_3);
	gen_set_label(l_Or_373_3);
	tcg_gen_br(exit_Or_373_2);
	gen_set_label(l_Or_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_Or_373_3);
	gen_set_label(exit_Or_373_2);
	TCGLabel *l_Or_30_4 = gen_new_label();
	TCGLabel *l_Or_304_5 = gen_new_label();
	TCGLabel *exit_Or_373_6 = gen_new_label();
	TCGLabel *l_Or_373_7 = gen_new_label();
	if (((arg_2 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Or_304_5);
	} else {
		tcg_gen_br(l_Or_30_4);
	}
	gen_set_label(l_Or_30_4);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_Or_373_7);
	gen_set_label(l_Or_373_7);
	tcg_gen_br(exit_Or_373_6);
	gen_set_label(l_Or_304_5);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_2 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_Or_373_7);
	gen_set_label(exit_Or_373_6);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_or_tl(tmp_7, tmp_3, tmp_5);
	TCGLabel *l_Or_515_8 = gen_new_label();
	TCGLabel *l_Or_329_9 = gen_new_label();
	TCGLabel *exit_Or_310_10 = gen_new_label();
	TCGLabel *l_Or_310_11 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_Or_329_9);
	} else {
		tcg_gen_br(l_Or_515_8);
	}
	gen_set_label(l_Or_515_8);
	tcg_gen_br(l_Or_310_11);
	gen_set_label(l_Or_310_11);
	tcg_gen_br(exit_Or_310_10);
	gen_set_label(l_Or_329_9);
	set_gpr(ctx, arg_0 / 4, tmp_7);
	tcg_gen_br(l_Or_310_11);
	gen_set_label(exit_Or_310_10);
	return true;
}

static bool trans_Or(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_2 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_1 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = arg_0 * 0x0004;
	uint64_t tmp_8 = 0x0000 + tmp_7;
	tcg_trans_Or(ctx, tmp_4, tmp_6, tmp_8);
	return true;
}

static bool tcg_trans_And(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	TCGLabel *l_And_30_0 = gen_new_label();
	TCGLabel *l_And_304_1 = gen_new_label();
	TCGLabel *exit_And_373_2 = gen_new_label();
	TCGLabel *l_And_373_3 = gen_new_label();
	if (((arg_1 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_And_304_1);
	} else {
		tcg_gen_br(l_And_30_0);
	}
	gen_set_label(l_And_30_0);
	TCGv tmp_3 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_3, 0x00000000);
	tcg_gen_br(l_And_373_3);
	gen_set_label(l_And_373_3);
	tcg_gen_br(exit_And_373_2);
	gen_set_label(l_And_304_1);
	TCGv tmp_4 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_4, get_gpr(ctx, arg_1 / 4));
	tcg_gen_mov_tl(tmp_3, tmp_4);
	tcg_gen_br(l_And_373_3);
	gen_set_label(exit_And_373_2);
	TCGLabel *l_And_30_4 = gen_new_label();
	TCGLabel *l_And_304_5 = gen_new_label();
	TCGLabel *exit_And_373_6 = gen_new_label();
	TCGLabel *l_And_373_7 = gen_new_label();
	if (((arg_2 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_And_304_5);
	} else {
		tcg_gen_br(l_And_30_4);
	}
	gen_set_label(l_And_30_4);
	TCGv tmp_5 = tcg_temp_new();
	tcg_gen_movi_tl(tmp_5, 0x00000000);
	tcg_gen_br(l_And_373_7);
	gen_set_label(l_And_373_7);
	tcg_gen_br(exit_And_373_6);
	gen_set_label(l_And_304_5);
	TCGv tmp_6 = tcg_temp_new();
	tcg_gen_mov_tl(tmp_6, get_gpr(ctx, arg_2 / 4));
	tcg_gen_mov_tl(tmp_5, tmp_6);
	tcg_gen_br(l_And_373_7);
	gen_set_label(exit_And_373_6);
	TCGv tmp_7 = tcg_temp_new();
	tcg_gen_and_tl(tmp_7, tmp_3, tmp_5);
	TCGLabel *l_And_515_8 = gen_new_label();
	TCGLabel *l_And_329_9 = gen_new_label();
	TCGLabel *exit_And_310_10 = gen_new_label();
	TCGLabel *l_And_310_11 = gen_new_label();
	if (((arg_0 != 0x0000) ? 1 : 0)) {
		tcg_gen_br(l_And_329_9);
	} else {
		tcg_gen_br(l_And_515_8);
	}
	gen_set_label(l_And_515_8);
	tcg_gen_br(l_And_310_11);
	gen_set_label(l_And_310_11);
	tcg_gen_br(exit_And_310_10);
	gen_set_label(l_And_329_9);
	set_gpr(ctx, arg_0 / 4, tmp_7);
	tcg_gen_br(l_And_310_11);
	gen_set_label(exit_And_310_10);
	return true;
}

static bool trans_And(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_1 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_0 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = arg_2 * 0x0004;
	uint64_t tmp_8 = 0x0000 + tmp_7;
	tcg_trans_And(ctx, tmp_4, tmp_6, tmp_8);
	return true;
}

static bool tcg_trans_Fence(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1)
{
	TCGv pc_val = tcg_temp_new();
	tcg_gen_movi_tl(pc_val, ctx->base.pc_next + ctx->cur_insn_len);
	return true;
}

static bool trans_Fence(DisasContext *ctx, uint64_t arg_0, uint64_t arg_1, uint64_t arg_2)
{
	uint64_t tmp_3 = arg_2 * 0x0004;
	uint64_t tmp_4 = 0x0000 + tmp_3;
	uint64_t tmp_5 = arg_0 * 0x0004;
	uint64_t tmp_6 = 0x0000 + tmp_5;
	uint64_t tmp_7 = extract32(arg_1, 0, 1);
	uint64_t tmp_8 = extract32(arg_1, 1, 1);
	uint64_t tmp_9 = (tmp_7 << 1) | tmp_8;
	uint64_t tmp_10 = extract32(arg_1, 2, 1);
	uint64_t tmp_11 = (tmp_9 << 1) | tmp_10;
	uint64_t tmp_12 = extract32(arg_1, 3, 1);
	uint64_t tmp_13 = (tmp_11 << 1) | tmp_12;
	uint64_t tmp_14 = extract32(arg_1, 4, 1);
	uint64_t tmp_15 = (tmp_13 << 1) | tmp_14;
	uint64_t tmp_16 = extract32(arg_1, 5, 1);
	uint64_t tmp_17 = (tmp_15 << 1) | tmp_16;
	uint64_t tmp_18 = extract32(arg_1, 6, 1);
	uint64_t tmp_19 = (tmp_17 << 1) | tmp_18;
	uint64_t tmp_20 = extract32(arg_1, 7, 1);
	uint64_t tmp_21 = (tmp_19 << 1) | tmp_20;
	uint64_t tmp_22 = extract32(arg_1, 8, 4);
	uint64_t tmp_23 = (tmp_21 << 4) | tmp_22;
	tcg_trans_Fence(ctx, tmp_4, tmp_6);
	return true;
}
