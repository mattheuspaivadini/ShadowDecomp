/* STATUS (Session 22, 2026-10-17): NON_MATCHING. best score 2 [cc=296].
 * clear-list -1 kept in a local fixes the constant order; residual = 2.96 dbr threads the found=0 jump into the beql target (open class)
 * Session 23: found-variable rewrites (found=0 default, if/else, &&, helper with break) and empty-asm pins on found: the pin restores the plain bne (no jump threading) but perturbs the inlined helper (score 15+). Best stays the Session-19 ternary (score 2).
 * The original .s stays in the build (asm/cod/002500.s); this C
 * draft (Session 22) is kept for the record. */
extern int D_0013BB90[256];  /* external semaphore list, -1 = free */
extern int D_00131F80[3];    /* the loader's own semaphore attributes */

int DeleteSema(int sema);
int ReferSemaStatus(int sema, int *info);

static inline void clear_list(void) {
    int i;

    int v = -1;
    for (i = 255; i >= 0; i--)
        D_0013BB90[i] = v;
}

static inline int is_loader_sema(int attr) {
    int j;

    for (j = 0; j < 3; j++) {
        if (D_00131F80[j] == attr)
            return 1;
    }
    return 0;
}

void LoaderSysDeleteAllExternalSema(void) {
    int info[8];
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013BB90[i] >= 0) {
            DeleteSema(D_0013BB90[i]);
            D_0013BB90[i] = -1;
        }
    }
    clear_list();
    for (i = 0; i < 256; i++) {
        if ((ReferSemaStatus(i, info) == i ? is_loader_sema(info[4]) : 0) != 0)
            DeleteSema(i);
    }
}
