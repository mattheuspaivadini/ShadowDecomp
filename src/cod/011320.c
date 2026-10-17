/* asm/cod/011320.s -> iGetTimerCount.
 * timer iGetTimerCount; record pointer computed before the id checks (Session 19)
 * MATCHED. */
unsigned long long iGetTimerSystemTime(void);

unsigned long long iGetTimerCount(int a0) {
    char *rec;
    unsigned long long v;

    rec = (char *)(((unsigned int)a0 >> 10) << 6);
    if (a0 < 0 || (a0 & 0x3FF) != *(int *)(rec + 0x8))
        return (unsigned long long)-1;
    v = *(unsigned long long *)(rec + 0x18);
    if ((*(int *)(rec + 0xC) & 1) != 0)
        v += iGetTimerSystemTime() - *(unsigned long long *)(rec + 0x10);
    return v;
}
/* iGetTimerCount */
