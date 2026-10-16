/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 51 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/0146B8.s); this C
 * draft (Session 9) is kept for the record. */
struct P146B8 {
    long long q[12];
};

int sceGsSetDefClear(struct P146B8 *p, short a1, short a2, short a3, short a4,
                  short a5, unsigned char a6, unsigned char a7,
                  unsigned char a8, unsigned char a9, unsigned int a10) {
    p->q[2] = 6;
    p->q[5] = 1;
    p->q[4] = (long long)(a6 & 0xFF)
            | (0xFE00LL << 46)
            | ((long long)(a7 & 0xFF) << 8)
            | ((long long)a8 << 16)
            | ((long long)a9 << 24);
    p->q[6] = ((long long)((short)a2 + (short)a3) << 4) << 16
            | ((long long)a10 << 32);
    p->q[9] = 5;
    p->q[8] = (((long long)((short)a2 + (short)a4) << 4) << 16)
            | ((((long long)((short)a3 + (short)a5)) << 4) << 16)
            | ((long long)a10 << 32);
    p->q[11] = 0x47;
    p->q[1] = 0x47;
    p->q[0] = 0x30000;
    p->q[3] = 0;
    p->q[7] = 5;
    if (a1 != 0)
        p->q[10] = ((long long)(a1 & 3) << 17) | 0x10000;
    else
        p->q[10] = 0x30000;
    __asm__ __volatile__("sync" ::: "memory");
    return 6;
}
/* func_001146B8 */
