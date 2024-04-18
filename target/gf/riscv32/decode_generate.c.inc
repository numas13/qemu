#define I12(insn)   sextract32(insn, 20, 12)
#define RD(insn)    extract32(insn, 7, 5)
#define RS1(insn)   extract32(insn, 15, 5)
#define RS2(insn)   extract32(insn, 20, 5)

static bool decode(DisasContext *ctx, uint32_t insn)
{
    if ((insn & 0x0000707f) == 0x00000013) {
        // addi rd, rs1, imm12
        TCGv t0 = tcg_temp_new();
        tcg_gen_addi_tl(t0, get_gpr(ctx, RS1(insn)), I12(insn));
        set_gpr(ctx, RD(insn), t0);
        return true;
    }

    return false;
}
