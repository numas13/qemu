#define I16(insn)   sextract32(insn, 0, 16)
#define RT(insn)    extract32(insn, 16, 5)
#define RS(insn)    extract32(insn, 21, 5)

static bool decode(DisasContext *ctx, uint32_t insn)
{
    if ((insn & 0xfc000000) == 0x24000000) {
        // addiu rt, rs, imm16
        TCGv t0 = tcg_temp_new();
        tcg_gen_addi_tl(t0, get_gpr(ctx, RS(insn)), I16(insn));
        set_gpr(ctx, RT(insn), t0);
        return true;
    }

    return false;
}
