/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 11 [cc=29].
 * R2 w45a_2: scheduling (bnel delay + mult in the call delay)
 * The original .s stays in the build (asm/cod/00A228.s); this C
 * draft (Session 8) is kept for the record. */
int func_00109980(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
int func_00107A08(int usec);

int func_0010A228(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9) {
    int tries = 0;
    int delay = 1;
    int r;
    int neg;

    do {
        r = func_00109980(a0, a1, a2, a3, a4, a5, a6, a7, a8);
        neg = (unsigned int)r >> 31;
        if (!neg || a9 != 0)
            break;
        func_00107A08(delay * 1000);
        if (delay < 0x7F)
            delay <<= 1;
        tries++;
    } while (tries < 0x65);
    return neg;
}
