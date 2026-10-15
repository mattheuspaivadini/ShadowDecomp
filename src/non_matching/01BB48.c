/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 12 [cc=29].
 * R1 wave3d: shared a0=$s0 copy in the beqz delay
 * The original .s stays in the build (asm/cod/01BB48.s); this C
 * draft (Session 8) is kept for the record. */
int func_00128CDC(int a0, int a1);
char *func_00129578(const char *s, int arg);
unsigned int func_001290C4(char *s);

int func_0011BB48(int a0) {
    unsigned int n;

    if (func_00128CDC(a0, 0x2F) != 0) {
        n = func_001290C4(func_00129578((char *)a0, 0x2F) + 1);
        if (n < 0x20)
            return 1;
        return 0;
    }
    n = func_001290C4((char *)a0);
    if (n < 0x20)
        return 1;
    return 0;
}
