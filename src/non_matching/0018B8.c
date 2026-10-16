/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 23 [cc=296].
 * R1 wave4c: unreachable 2nd range test (slti/bltz)
 * The original .s stays in the build (asm/cod/0018B8.s); this C
 * draft (Session 8) is kept for the record. */
int RelocateSelfSymbol(int *a0, int a1) {
    int n = a0[0x24 / 4] - 1;
    int *e = (int *)a0[0x28 / 4];
    int *tab = (int *)a0[0x30 / 4];
    int *src = (int *)a0[0x34 / 4];

    if (n == -1)
        return 1;
    do {
        unsigned short c = *(unsigned short *)((char *)e + 0x0E);

        if (c == 0) {
            *(int *)((char *)e + 0x04) = a1;
        } else if (c == 0xFFF1) {
            *(int *)((char *)e + 0x04) = *src;
        } else if (c <= 0xFEFF) {
            int t = (int)(*(unsigned char *)((char *)e + 0x0C) & 0xF);

            if (t < 4 && t >= 0)
                *(int *)((char *)e + 0x04) = *src + tab[c * 8];
        }
        e = (int *)((char *)e + 0x10);
        src++;
        n--;
    } while (n != -1);
    return 1;
}
/* func_001018B8 */
