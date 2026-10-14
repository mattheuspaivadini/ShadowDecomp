/* STATUS (Session 5, step 2): NON_MATCHING - best attempt [cc=29] is not byte-exact.
 * 2 instructions: `a2=a1` copy vs the callback `lui` are transposed (arg evaluation order).
 * See docs/progress.md for the family classification. */
/* func_00108E08 @ 0x00108E08 (0x38 bytes): stack buffer + callback
 * func_00108D10 forwarded to func_00107FF8. */
int func_00107FF8(int (*cb)(void), int *p, int a1, int a2, int a3);
int func_00108D10(void);

void func_00108E08(int a0, int a1, int a2, int a3) {
    int buf;

    buf = a0;
    func_00107FF8(func_00108D10, &buf, a1, a2, a3);
}
