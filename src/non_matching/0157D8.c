/* STATUS (Session 12, 2026-10-16): NON_MATCHING. best score 10 [cc=29].
 * func_001157D8: beql branch likely on bit counter loop
 * The original .s stays in the build (asm/cod/0157D8.s); this C
 * draft (Session 12) is kept for the record. */
int func_001157D8(unsigned char *a0, int *a1) {
    unsigned char *p;
    int *r;
    int i;
    int bit;
    int n;
    int m;

    n = 0;
    m = 0;
    bit = 0;
    p = a0;
    r = a1;
    for (i = 0; i < 0x28; i++) {
        if ((*p >> bit) & 1) {
            r[0] = 1;
            r[2] = n;
            r[3] = m;
            if ((unsigned int)(i - 0x10) < 0x10 || (unsigned int)(i - 0x23) < 4) {
                r[1] = 8;
                n = n + 1;
            } else {
                m = m + 1;
                r[1] = 1;
                if ((m & 7) == 0) {
                    n = n + 1;
                    m = 0;
                }
            }
        } else {
            r[0] = 0;
            r[2] = 0;
            r[3] = 0;
        }
        bit++;
        if ((bit & 7) == 0) {
            p++;
            bit = 0;
        }
        r = r + 4;
    }
    return 1;
}
