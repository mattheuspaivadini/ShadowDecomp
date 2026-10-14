/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 7 [cc=29, default].
 * 0x24-stride record + tail call; allocation differs.
 * The original .s stays in the build (asm/cod/021A70.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/021A70.s -> func_00121A70 @ 0x00121A70 (0x1C bytes, 7 insns)
 *   addiu $v1, $zero, 0x24
 *   lui   $v0, %hi(D_00163CC8)
 *   mult  $v1, $a0, $v1              ; v1 = a0 * 0x24   (R5900 3-operand mult)
 *   addiu $v0, $v0, %lo(D_00163CC8)
 *   addu  $v0, $v0, $v1
 *   j     func_001218D8              ; tail call, a0-a3 unchanged
 *    lw   $a4, 0x14($v0)             ; a4 = D_00163CC8[a0].field14
 *
 * Forward the first four arguments to func_001218D8 (which tail-calls
 * func_001161A0 and then uses a1-a4 as s7/s6/s4/s5) plus the record field at
 * +0x14 as the fifth argument.
 *
 * The `mult $v1,$a0,$v1` literal stride (0x24) is the 2.9 generation shape
 * (docs/compiler.md 4.2), same as the matched 022018/0220B0/021E88 family.
 * MATCH GUESS: cc=29 */
struct R021A70 {
    char pad00[0x14];
    int  field14;             /* 0x14 */
    char rest[0x24 - 0x18];   /* stride 0x24 */
};

extern struct R021A70 D_00163CC8[];

int func_001218D8(int a0, int a1, int a2, int a3, int a4);

int func_00121A70(int a0, int a1, int a2, int a3) {
    return func_001218D8(a0, a1, a2, a3, D_00163CC8[a0].field14);
}
