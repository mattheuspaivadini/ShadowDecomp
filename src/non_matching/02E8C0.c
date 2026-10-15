/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 24 [cc=296].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/02E8C0.s); this C
 * draft (Session 9) is kept for the record. */
int *func_0012E7E8(int a0, int a1);
int  func_0012821C(int dst, int src, int n);
void func_0012E890(int a0, int *b);

int *func_0012E8C0(int a0, int *b, int m, int carry) {
    int n;
    int i;
    int v;
    int lo;
    int hi;
    int u;
    int *p;

    n = b[4];
    i = 0;
    p = b + 5;
    do {
        v = *p;
        i++;
        lo = v & 0xFFFF;
        hi = (int)((unsigned int)v >> 16);
        u = hi * m + (int)((unsigned int)(lo * m + carry) >> 16);
        *p = (u << 16) + (int)((unsigned int)(lo * m + carry) & 0xFFFF);
        carry = (int)((unsigned int)u >> 16);
        p++;
    } while (i < n);
    if (carry != 0) {
        if (n >= b[2]) {
            p = func_0012E7E8(a0, b[1] + 1);
            func_0012821C((int)p + 0xC, (int)(b + 3), (b[4] << 2) + 8);
            func_0012E890(a0, b);
            b = p;
        }
        b[n + 5] = carry;
        b[4] = n + 1;
    }
    return b;
}
