/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 21 [cc=29, default].
 * variadic print-into-buffer; $v0 routing.
 * The original .s stays in the build (asm/cod/005268.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/005268.s -> func_00105268 @ 0x00105268 (0x6C bytes, 27 insns)
 *
 * Variadic print-into-buffer helper (the sibling of the 008EF8 shape):
 *   func_0012C048(buf, fmt, __builtin_saveregs());  ; build the 0x60 ctx + vsprintf
 *   func_001050B8(buf);                             ; process/emit the text
 * The EE-GCC varargs prologue spills a1..a7 to 0x138/0x140/../0x168 and
 * f12..f19 to 0x118../0x134, so the register save area base is sp+0x138 - the
 * same value the third call argument carries (see asm/cod/008EF8.s, where
 * `addiu $a4,$sp,0x88` is the a1 slot of that frame). $ra is at 0x100, frame
 * 0x170, and the formatting buffer is at sp+0 (0x100 bytes).
 * The local buffer is passed both to func_0012C048 (ctx pointer, field 0x00/0x10)
 * and to func_001050B8 (the text it consumes).
 * Residual: the original materialises a0 through $v0 before the call
 * (`daddu $v0,$a0,$zero; daddu $a1,$v0,$zero`); the plain form below should
 * emit a single `daddu $a1,$a0,$zero` - one instruction's worth of allocation
 * difference not reproduced here.
 * MATCH GUESS: cc=296 (0x0050B8/02C048 print family; both jal delay slots filled)
 */
void func_0012C048(void *ctx, int fmt, void *ap);
void func_001050B8(char *buf);

void func_00105268(int fmt, ...) {
    char buf[0x100];

    func_0012C048(buf, fmt, __builtin_saveregs());
    func_001050B8(buf);
}
