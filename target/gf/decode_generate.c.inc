#include <stdio.h>
#include <inttypes.h>

bool decode(DisasContext *ctx, uint32_t insn);

bool decode(DisasContext *ctx, uint32_t insn)
{
	if ((insn & 0x0000007F) == 0x00000037 && trans_Lui(ctx, (insn & 0xFFFFF000) >> 12, (insn & 0xF80) >> 7)) {
		return true;
	}
	if ((insn & 0x0000007F) == 0x00000017 && trans_Auipc(ctx, (insn & 0xFFFFF000) >> 12, (insn & 0xF80) >> 7)) {
		return true;
	}
	if ((insn & 0x0000007F) == 0x0000006F && trans_Jal(ctx, (insn & 0xFFFFF000) >> 12, (insn & 0xF80) >> 7)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00000067 && trans_Jalr(ctx, (insn & 0xFFF00000) >> 20, (insn & 0xF8000) >> 15, (insn & 0xF80) >> 7)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00000063 && trans_Beq(ctx, (insn & 0xF8000) >> 15, (insn & 0x1F00000) >> 20, (insn & 0xFE000F80) >> 7)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00001063 && trans_Bne(ctx, (insn & 0xF8000) >> 15, (insn & 0xFE000F80) >> 7, (insn & 0x1F00000) >> 20)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00004063 && trans_Blt(ctx, (insn & 0xF8000) >> 15, (insn & 0x1F00000) >> 20, (insn & 0xFE000F80) >> 7)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00005063 && trans_Bge(ctx, (insn & 0x1F00000) >> 20, (insn & 0xF8000) >> 15, (insn & 0xFE000F80) >> 7)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00006063 && trans_Bltu(ctx, (insn & 0xFE000F80) >> 7, (insn & 0x1F00000) >> 20, (insn & 0xF8000) >> 15)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00007063 && trans_Bgeu(ctx, (insn & 0xFE000F80) >> 7, (insn & 0x1F00000) >> 20, (insn & 0xF8000) >> 15)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00000003 && trans_Lb(ctx, (insn & 0xF80) >> 7, (insn & 0xF8000) >> 15, (insn & 0xFFF00000) >> 20)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00001003 && trans_Lh(ctx, (insn & 0xF8000) >> 15, (insn & 0xFFF00000) >> 20, (insn & 0xF80) >> 7)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00002003 && trans_Lw(ctx, (insn & 0xF8000) >> 15, (insn & 0xF80) >> 7, (insn & 0xFFF00000) >> 20)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00004003 && trans_Lbu(ctx, (insn & 0xF80) >> 7, (insn & 0xFFF00000) >> 20, (insn & 0xF8000) >> 15)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00005003 && trans_Lhu(ctx, (insn & 0xF80) >> 7, (insn & 0xF8000) >> 15, (insn & 0xFFF00000) >> 20)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00000023 && trans_Sb(ctx, (insn & 0xFE000F80) >> 7, (insn & 0xF8000) >> 15, (insn & 0x1F00000) >> 20)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00001023 && trans_Sh(ctx, (insn & 0xFE000F80) >> 7, (insn & 0x1F00000) >> 20, (insn & 0xF8000) >> 15)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00002023 && trans_Sw(ctx, (insn & 0xFE000F80) >> 7, (insn & 0x1F00000) >> 20, (insn & 0xF8000) >> 15)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00000013 && trans_Addi(ctx, (insn & 0xF80) >> 7, (insn & 0xFFF00000) >> 20, (insn & 0xF8000) >> 15)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00002013 && trans_Slti(ctx, (insn & 0xFFF00000) >> 20, (insn & 0xF8000) >> 15, (insn & 0xF80) >> 7)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00003013 && trans_Sltiu(ctx, (insn & 0xFFF00000) >> 20, (insn & 0xF8000) >> 15, (insn & 0xF80) >> 7)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00004013 && trans_Xori(ctx, (insn & 0xF80) >> 7, (insn & 0xFFF00000) >> 20, (insn & 0xF8000) >> 15)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00006013 && trans_Ori(ctx, (insn & 0xFFF00000) >> 20, (insn & 0xF8000) >> 15, (insn & 0xF80) >> 7)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x00007013 && trans_Andi(ctx, (insn & 0xF80) >> 7, (insn & 0xFFF00000) >> 20, (insn & 0xF8000) >> 15)) {
		return true;
	}
	if ((insn & 0xFE00707F) == 0x00001013 && trans_Slli(ctx, (insn & 0xF8000) >> 15, (insn & 0x1F00000) >> 20, (insn & 0xF80) >> 7)) {
		return true;
	}
	if ((insn & 0xFE00707F) == 0x00005013 && trans_Srli(ctx, (insn & 0xF80) >> 7, (insn & 0x1F00000) >> 20, (insn & 0xF8000) >> 15)) {
		return true;
	}
	if ((insn & 0xFE00707F) == 0x40005013 && trans_Srai(ctx, (insn & 0xF80) >> 7, (insn & 0x1F00000) >> 20, (insn & 0xF8000) >> 15)) {
		return true;
	}
	if ((insn & 0xFE00707F) == 0x00000033 && trans_Add(ctx, (insn & 0x1F00000) >> 20, (insn & 0xF80) >> 7, (insn & 0xF8000) >> 15)) {
		return true;
	}
	if ((insn & 0xFE00707F) == 0x40000033 && trans_Sub(ctx, (insn & 0xF80) >> 7, (insn & 0x1F00000) >> 20, (insn & 0xF8000) >> 15)) {
		return true;
	}
	if ((insn & 0xFE00707F) == 0x00001033 && trans_Sll(ctx, (insn & 0x1F00000) >> 20, (insn & 0xF80) >> 7, (insn & 0xF8000) >> 15)) {
		return true;
	}
	if ((insn & 0xFE00707F) == 0x00005033 && trans_Srl(ctx, (insn & 0xF8000) >> 15, (insn & 0xF80) >> 7, (insn & 0x1F00000) >> 20)) {
		return true;
	}
	if ((insn & 0xFE00707F) == 0x00002033 && trans_Slt(ctx, (insn & 0xF8000) >> 15, (insn & 0xF80) >> 7, (insn & 0x1F00000) >> 20)) {
		return true;
	}
	if ((insn & 0xFE00707F) == 0x00003033 && trans_Sltu(ctx, (insn & 0x1F00000) >> 20, (insn & 0xF8000) >> 15, (insn & 0xF80) >> 7)) {
		return true;
	}
	if ((insn & 0xFE00707F) == 0x00004033 && trans_Xor(ctx, (insn & 0xF80) >> 7, (insn & 0x1F00000) >> 20, (insn & 0xF8000) >> 15)) {
		return true;
	}
	if ((insn & 0xFE00707F) == 0x00005033 && trans_Sra(ctx, (insn & 0xF8000) >> 15, (insn & 0xF80) >> 7, (insn & 0x1F00000) >> 20)) {
		return true;
	}
	if ((insn & 0xFE00707F) == 0x00006033 && trans_Or(ctx, (insn & 0x1F00000) >> 20, (insn & 0xF8000) >> 15, (insn & 0xF80) >> 7)) {
		return true;
	}
	if ((insn & 0xFE00707F) == 0x00007033 && trans_And(ctx, (insn & 0xF8000) >> 15, (insn & 0xF80) >> 7, (insn & 0x1F00000) >> 20)) {
		return true;
	}
	if ((insn & 0x0000707F) == 0x0000000F && trans_Fence(ctx, (insn & 0xF8000) >> 15, (insn & 0xFFF00000) >> 20, (insn & 0xF80) >> 7)) {
		return true;
	}
	return false;
}
