/* asm/cod/011288.s -> iGetTimerBaseTime.
 * timer iGetTimerBaseTime; record pointer before the id checks (Session 19)
 * MATCHED. */
struct S011288 {
    char      pad00[0x08];
    int       field08;   /* 0x08 tag */
    int       field0C;   /* 0x0C flags */
    long long field10;   /* 0x10 */
    long long field18;   /* 0x18 */
};

long long iGetTimerBaseTime(int index) {
    struct S011288 *p = (struct S011288 *)(((unsigned int)index >> 10) << 6);

    if (index < 0 || (index & 0x3FF) != p->field08)
        return -1;
    if (p->field0C & 1)
        return p->field10 - p->field18;
    return 0;
}
