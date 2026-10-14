/* asm/cod/0188E0.s -> func_001188E0 @ 0x001188E0
 * Store the argument(s) into the caller's block, forward to
 * func_00118380(a0, 0x2, p, 0x8, 4) and return the stored value on
 * success, or -0x21E on failure. The `int r = call(...); if (r < 0) ...;
 * return p[0];` shape is the one that produces the original's 0x20 frame and
 * `bgezl` + load-in-delay-slot (same as the matched func_001190F8). */
int func_00118380(int a0, int a1, int *p, int a3, int a4);

int func_001188E0(int a0, int *p, int a2, int a3) {
    int r;

    p[0] = a2;
    p[1] = a3;
    r = func_00118380(a0, 0x2, p, 0x8, 4);
    if (r < 0)
        return -0x21E;
    return p[0];
}
