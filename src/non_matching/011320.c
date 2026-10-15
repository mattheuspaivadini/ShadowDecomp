/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 13 [cc=29].
 * R1 wave3d: ld speculation into beqz delay + shared return -1
 * The original .s stays in the build (asm/cod/011320.s); this C
 * draft (Session 8) is kept for the record. */
unsigned long long func_00110C78(void);

unsigned long long func_00111320(int a0) {
    char *rec;
    unsigned long long v;

    if (a0 < 0)
        return (unsigned long long)-1;
    rec = (char *)(((unsigned int)a0 >> 10) << 6);
    if ((a0 & 0x3FF) != *(int *)(rec + 0x8))
        return (unsigned long long)-1;
    v = *(unsigned long long *)(rec + 0x18);
    if ((*(int *)(rec + 0xC) & 1) != 0)
        v += func_00110C78() - *(unsigned long long *)(rec + 0x10);
    return v;
}
