/* asm/cod/01C4C8.s -> func_0011C4C8 @ 0x0011C4C8 (0x44 bytes, 17 insns)
 * Error-code fix-up of the func_0011C3B0(a0, a1, a2) family: the result is
 * compared against 0x7FFFFFFF (materialised in $v0, `bne` = inverted test) and
 * on a match the third argument's object gets the sibling error code
 * 0x81019002 (func_0011C3B0 itself writes 0x8101006F on its own error paths);
 * the result is then re-loaded into $v0 from $v1 and returned.
 * MATCH GUESS: cc=29 (0x01B7xx error-fix-up family + 0x01C1xx) */
extern int func_0011C3B0(int a0, int a1, int a2);

int func_0011C4C8(int a0, int a1, int *a2) {
    int r;

    r = func_0011C3B0(a0, a1, a2);
    if (r == 0x7FFFFFFF)
        *a2 = 0x81019002;
    return r;
}
