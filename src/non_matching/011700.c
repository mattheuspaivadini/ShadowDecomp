/* STATUS (Session 12, 2026-10-16): NON_MATCHING. best score 14 [cc=29].
 * _InitAlarm: descending 16-byte record loop alignment
 * The original .s stays in the build (asm/cod/011700.s); this C
 * draft (Session 12) is kept for the record. */
/* func_00111700 @ 0x00111700 (0x4C bytes): build a descending chain of 64
 * 16-byte records from D_0014A880 + 0x400 and store the base pointer in
 * D_0014AC80; clear the last slot; return 0. */
extern char D_0014A880[];
extern int D_0014AC80 __attribute__((section(".data")));

int _InitAlarm(void) {
    int *p = (int *)(D_0014A880 + 0x3F0);
    int *q = (int *)(D_0014A880 + 0x400);
    int i;

    D_0014AC80 = (int)D_0014A880;
    for (i = 0x3F; i >= 0; i--) {
        *p = (int)q;
        p = (int *)((char *)p - 0x10);
        q = (int *)((char *)q - 0x10);
    }
    *(int *)(D_0014A880 + 0x3F0) = 0;
    return 0;
}
