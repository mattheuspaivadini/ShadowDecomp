/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 31 [cc=29].
 * R1 wave4c: R5900 MMI lq/pxor/pcpyud 128-bit compare
 * The original .s stays in the build (asm/cod/028188.s); this C
 * draft (Session 8) is kept for the record. */
struct S028188 {
    unsigned long long lo;      /* 0x0 */
    unsigned long long hi;      /* 0x8 */
};

int func_00128188(unsigned int a0, unsigned int a1, unsigned int n) {
    struct S028188 x;
    struct S028188 y;

    if (n >= 0x10 && ((a0 | a1) & 0xF) == 0) {
        while (n >= 0x20) {
            x = *(struct S028188 *)a0;
            y = *(struct S028188 *)a1;
            a0 += 0x10;
            if (x.lo != y.lo || x.hi != y.hi) {
                a0 -= 0x10;
                break;
            }
            a1 += 0x10;
            n -= 0x10;
        }
    }
    n = n - 1;
    if (n != 0xFFFFFFFFu) {
        do {
            unsigned char p = *(unsigned char *)a0;
            unsigned char q = *(unsigned char *)a1;

            a0 = a0 + 1;
            if (p != q)
                return (int)p - (int)q;
            n = n - 1;
            a1 = a1 + 1;
        } while (n != 0xFFFFFFFFu);
    }
    return 0;
}
