/* STATUS (10, 2026-10-16): NON_MATCHING. best score 8 [cc=29].
 * 
 * The original .s stays in the build (asm/cod/011288.s); this C
 * draft (10) is kept for the record. */
struct S011288 {
    char      pad00[0x08];
    int       field08;   /* 0x08 tag */
    int       field0C;   /* 0x0C flags */
    long long field10;   /* 0x10 */
    long long field18;   /* 0x18 */
};

long long iGetTimerBaseTime(int index) {
    if (index >= 0) {
        struct S011288 *p = (struct S011288 *)((index >> 10) << 6);

        if ((index & 0x3FF) == p->field08) {
            if (p->field0C & 1)
                return p->field10 - p->field18;
            return 0;
        }
    }
    return -1;
}
