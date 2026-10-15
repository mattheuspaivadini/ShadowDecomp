/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 41 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/012710.s); this C
 * draft (Session 9) is kept for the record. */
struct Q012710 {
    int            w0;      /* 0x00 */
    int            w4;      /* 0x04 */
    unsigned char *cur;     /* 0x08 */
};

struct S012710A {
    int             pad00[6];   /* 0x00 .. 0x17 */
    struct Q012710 *q;          /* 0x18 */
};

extern struct S012710A D_0014AFD0;   /* non-small (lui/addiu) */
extern int D_0014AFE8[];             /* non-small; [0] = queue pointer */
int func_001123C0(struct Q012710 *q);

int func_00112710(char *dst, int n) {
    int i;
    int c;

    i = 0;
    if (n <= 0)
        return 0;
    do {
        struct Q012710 *q;

        while (*(volatile int *)(D_0014AFE8[0] + 4) == 0)
            ;
        q = D_0014AFD0.q;
        c = *q->cur;
        dst[i] = (char)c;
        func_001123C0(q);
        c = dst[i];
        if (c == '\n' || c == '\r')
            return i + 1;
        i++;
    } while (i < n);
    return i;
}
