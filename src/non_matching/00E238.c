/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 17 [cc=29].
 * R2 w45a_2: rotated-loop (~1M-iteration busy-wait)
 * The original .s stays in the build (asm/cod/00E238.s); this C
 * draft (Session 8) is kept for the record. */
extern int D_00132330 __attribute__((section(".data")));
extern int D_00147580[];
extern unsigned char D_00147380[];
extern unsigned char D_001475A8[];

int sceSifBindRpc(int a0, int a1, int a2);
int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

int func_0010E238(void) {
    int i;
    int r;

    if (D_00132330 >= 0)
        return 0;
    for (;;) {
        if (sceSifBindRpc((int)D_00147580, 0x80000006, 0) < 0)
            return -1;
        if (D_00147580[9] != 0) {
            D_00132330 = 0;
            r = sceSifCallRpc((int)D_00147580, 0xFF, 0, 0, 0,
                              (int)D_00147380, 4, 0, 0);
            if (r < 0)
                return 0xFFFEFFFF;
            *(int *)D_001475A8 = *(int *)D_00147380;
            return 0;
        }
        for (i = 0x100000; --i != -1; )
            ;
    }
}
