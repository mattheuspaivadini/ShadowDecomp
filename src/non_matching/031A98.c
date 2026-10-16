/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 21 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/031A98.s); this C
 * draft (Session 9) is kept for the record. */
extern int dpcmp(long long a0, long long a1);
extern int dpsub(long long a0, long long a1);
extern long long __fixunsdfdi(long long a0, long long a1);

long long __fixdfdi(long long a0) {
    long long z;

    z = 0;
    if (dpcmp(a0, z) >= 0)
        return __fixunsdfdi(a0, a0);
    return -__fixunsdfdi(dpsub(z, a0), a0);
}
/* func_00131A98 */
