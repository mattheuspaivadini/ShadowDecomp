/* STATUS (Session 8, 2026-10-16): NON_MATCHING. best score 8 [cc=296].
 * reg-alloc in v0 vs v1 counter decr
 * The original .s stays in the build (asm/cod/028510.s); this C
 * draft (Session 8) is kept for the record. */
extern int D_001360C4 __attribute__((section(".data")));
extern int D_001360C0 __attribute__((section(".data")));
extern int __sce_sema_id __attribute__((section(".data")));

int SignalSema(int a0);

int __malloc_unlock(void) {
    int *p = &D_001360C4;
    int v = *p - 1;
    *p = v;
    if (v == 0) {
        D_001360C0 = -1;
        return SignalSema(__sce_sema_id);
    }
    return v;
}
