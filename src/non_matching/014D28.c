/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 8 [cc=29].
 * R1 wave3e: twin of 014CB0 (ori 0x109)
 * The original .s stays in the build (asm/cod/014D28.s); this C
 * draft (Session 8) is kept for the record. */
unsigned int func_001148B8(unsigned int x);
int func_001147C0(unsigned *p);

int sceDmaSendI(int *p, unsigned int x, int v) {
    int r;
    int w;

    r = func_001148B8(x);
    func_001147C0((unsigned *)p);
    if (p[4] != -1)
        p[4] = r;
    w = p[0];
    p[8] = v;
    w = (w & -13) | 0x109;
    p[0] = w;
    return w;
}
