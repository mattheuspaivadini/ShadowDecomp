/* asm/cod/00F0F0.s -> func_0010F0F0 @ 0x0010F0F0 (0x28 bytes, 10 insns)
 *
 * Tests bit 16 of func_001073F0(4)'s return value. The original materialises
 * the 0x10000 mask as a named local (`int lit = 0x10000;`) declared *before*
 * the call, and combines with `and` + `sltu` (unsigned compare against zero):
 * ee-gcc keeps the mask in a register (`lui v1,0x10000` after the jal) instead
 * of folding it into an `andi`.
 *
 * MATCHED (Session 6, step 1) with cc=29 via the permuter pair mutation
 * `const_local 0x10000 + swap_stmt`: the mask becomes a named local declared
 * *after* the call. The baseline (mask inline) is 4 bytes short at both
 * revisions; declaring the local *before* the call also fails (it needs $s0
 * and a 0x20 stack frame).
 */
int sceSifGetReg(int x);

int sceSifIsAliveIop(void) {
    int r = sceSifGetReg(4);
    int lit = 0x10000;

    return (r & lit) != 0;
}
