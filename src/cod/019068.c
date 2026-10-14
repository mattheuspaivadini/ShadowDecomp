/* asm/cod/019068.s -> func_00119068 @ 0x00119068 (0x8C bytes, 35 insns)
 * Block store + two-call forward: p[1] = a4, p[0] = a3, then
 * func_00118380(a0, 0x11, p, 8, a3 + 4) (failure -> -0x21E), then
 * func_00118490(a0, a2, p, 1, a3) whose negative result is returned while the
 * success path returns p[0] (`bgezl` + load in the delay slot, the same shape
 * as the matched 019138/0188E0 family; the second call's args are set up by
 * `daddu $a0,$s2` in the first branch's delay slot).
 * MATCH GUESS: cc=29 (the 0188E0/0191xx func_00118380 block-store family) */
int func_00118380(int a0, int a1, int *p, int a3, int a4);
int func_00118490(int a0, int a1, int *p, int a3, int a4);

int func_00119068(int a0, int *p, int a2, int a3, int a4) {
    int r;

    p[1] = a4;
    p[0] = a3;
    r = func_00118380(a0, 0x11, p, 8, a3 + 4);
    if (r < 0)
        return -0x21E;
    r = func_00118490(a0, a2, p, 1, a3);
    if (r < 0)
        return r;
    return p[0];
}
