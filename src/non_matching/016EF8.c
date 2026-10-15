/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 39 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/016EF8.s); this C
 * draft (Session 9) is kept for the record. */
extern int D_00133AA0[];   /* lui/%lo: the address is what is passed */

void func_00116CE8(int *a0);

void func_00116EF8(int a0) {
    int *p;
    int i;
    int src;
    unsigned char c;

    p = (int *)(a0 | 0x20000000);
    if (p[0] > 0) {
        src = p[2];
        for (i = 0; i < p[0]; i++) {
            c = *((unsigned char *)p + 0x10 + i);
            *((unsigned char *)(src | 0x20000000) + i) = c;
            *((unsigned char *)src + i) = c;
        }
    }
    if (p[1] > 0) {
        src = p[3];
        for (i = 0; i < p[1]; i++) {
            c = *((unsigned char *)p + 0x50 + i);
            *((unsigned char *)(src | 0x20000000) + i) = c;
            *((unsigned char *)src + i) = c;
        }
    }
    func_00116CE8(D_00133AA0);
}
