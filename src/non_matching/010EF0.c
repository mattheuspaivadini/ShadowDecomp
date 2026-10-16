/* STATUS (Session 12, 2026-10-16): NON_MATCHING. best score 3 [cc=29].
 * iGetTimerUsedUnusedCounters: lw v1, 0x10(v1) before addiu v0, 0x80 load delay scheduling
 * The original .s stays in the build (asm/cod/010EF0.s); this C
 * draft (Session 12) is kept for the record. */
struct S00133918 {
    char pad00[0x08];
    int  field08;   /* 0x08 */
    int  field0C;   /* 0x0C */
    int  field10;   /* 0x10 */
};

extern struct S00133918 D_00133918;

int iGetTimerUsedUnusedCounters(int *out0, int *out1) {
    if (D_00133918.field08 < 0)
        return 0x80008001;

    if (out0)
        *out0 = D_00133918.field10;
    if (out1) {
        int v = D_00133918.field10;
        *out1 = 0x80 - v;
    }
    return 0;
}
