/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 32 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/013F10.s); this C
 * draft (Session 9) is kept for the record. */
struct P13F10 {
    long long q[8];
};

int sceGsSetDefTexEnv(struct P13F10 *p, short a1, short a2, short a3, short a4,
                  short a5, short a6, short a7, short t0, short t1, short t2,
                  short t3) {
    if (a1 != 0)
        p->q[1] = 0x3F;
    else
        p->q[1] = 0x7F;
    p->q[5] = 6;
    p->q[6] = 5;
    p->q[4] = ((long long)a2)
            | ((long long)t0 << 37)
            | ((long long)a5 << 26)
            | 0x400000000LL
            | ((long long)a3 << 14)
            | ((long long)a4 << 20)
            | ((long long)a6 << 30)
            | ((long long)a7 << 35)
            | ((long long)t1 << 51)
            | ((long long)t2 << 61);
    p->q[3] = 0x14;
    p->q[2] = ((long long)(t3 & 1) << 5) | ((long long)t3 << 6);
    p->q[7] = 8;
    p->q[0] = 0;
    __asm__ __volatile__("sync" ::: "memory");
    return 4;
}
/* func_00113F10 */
