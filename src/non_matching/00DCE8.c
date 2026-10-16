/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 30 [cc=29].
 * R4 w25a_1: entry jumps over the wait block (4 literal nops)
 * The original .s stays in the build (asm/cod/00DCE8.s); this C
 * draft (Session 8) is kept for the record. */
int sceSifBindRpc(int *a0, int a1, int a2);
int DIntr(void);

extern int D_001471C0[];
extern int D_0013232C[];

int sceSifInitIopHeap(void) {
    int r;
    int i;

    for (;;) {
        r = sceSifBindRpc(D_001471C0, 0x80000003, 0);
        if (r < 0)
            return -1;
        if (D_001471C0[9] != 0) {
            D_0013232C[0] = 0;
            return 0;
        }
        i = 0x100000;
        while (i != -1) {
            i--;
            __asm__ __volatile__("nop\nnop\nnop\nnop");
        }
    }
}
