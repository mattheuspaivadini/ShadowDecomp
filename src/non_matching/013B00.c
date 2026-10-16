/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 9 [cc=29, default].
 * sceGsPutDrawEnv per sub-record; mult stride.
 * The original .s stays in the build (asm/cod/013B00.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/013B00.s -> func_00113B00 @ 0x00113B00 (0x5C bytes, 23 insns)
 *
 * Per-index draw-environment upload. The frame loop in asm/cod/005BC8.s calls
 * it as func_00113B00(base, index) with index = a counter bit, and 005BC8.s
 * itself uploads the same base+0x140 / base+0x50 pair through sceGsPutDrawEnv:
 *
 *   f = flag & 1;                       ; andi $s0,$a1,0x1
 *   func_00114530(p + f * 0x28);        ; 0x28-byte env record (3-operand mult)
 *   if (f) sceGsPutDrawEnv(p + 0x140);
 *   else   sceGsPutDrawEnv(p + 0x50);
 *
 * Both calls keep `jal` + a branch to the shared epilogue (no sibling call),
 * and the f * 0x28 stride is the R5900 3-operand `mult rd,rs,rt` shape - both
 * point at cc=29. The frame is 0x30 with $s0/$s1/$ra 16 bytes apart (the 2.9
 * slot layout). $v0 is never set by this function (it is left as the last
 * callee's result), so it returns nothing.
 * MATCH GUESS: cc=29 */
void sceGsPutDispEnv(int env);
void sceGsPutDrawEnv(int env);

void sceGsSwapDBuff(int p, int flag) {
    int f = flag & 1;

    sceGsPutDispEnv(p + f * 0x28);
    if (f != 0)
        sceGsPutDrawEnv(p + 0x140);
    else
        sceGsPutDrawEnv(p + 0x50);
}
