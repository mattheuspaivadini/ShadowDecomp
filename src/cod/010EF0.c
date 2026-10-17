/* asm/cod/010EF0.s -> iGetTimerUsedUnusedCounters.
 * timer TU: ee-gcc2.9-991111-01-dtls13010 -g0 -fno-delayed-branch -G0 (Session 19)
 * MATCHED. */
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
