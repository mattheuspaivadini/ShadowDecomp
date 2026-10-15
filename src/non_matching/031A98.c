/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 21 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/031A98.s); this C
 * draft (Session 9) is kept for the record. */
extern int func_00125768(long long a0, long long a1);
extern int func_00125338(long long a0, long long a1);
extern long long func_00124C78(long long a0, long long a1);

long long func_00131A98(long long a0) {
    long long z;

    z = 0;
    if (func_00125768(a0, z) >= 0)
        return func_00124C78(a0, a0);
    return -func_00124C78(func_00125338(z, a0), a0);
}
