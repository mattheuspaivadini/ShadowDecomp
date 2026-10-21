/* asm/cod/002500.s -> LoaderSysDeleteAllExternalSema.
 * loader: delete every external sema, list clear, then sema sweep with the loader-attribute search inline and found = 1 jumping past found = 0 (Session 41)
 * MATCHED. */
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

void LoaderSysDeleteAllExternalSema(void) {
    int info[8];
    int i;
    int j;
    int found;

    for (i = 0; i < 256; i++) {
        if (D_0013BB90[i] >= 0) {
            DeleteSema(D_0013BB90[i]);
            D_0013BB90[i] = -1;
        }
    }
    clear_list();
    for (i = 0; i < 256; i++) {
        if (ReferSemaStatus(i, info) == i) {
            for (j = 0; j < 3; j++) {
                if (D_00131F80[j] == info[4]) {
                    found = 1;
                    goto hit;
                }
            }
        }
        found = 0;
    hit:
        if (found)
            DeleteSema(i);
    }
}
