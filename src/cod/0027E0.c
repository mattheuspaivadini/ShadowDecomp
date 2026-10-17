/* asm/cod/0027E0.s -> find_free.
 * loader external sema list: inline free-slot search (Session 19)
 * MATCHED. */
extern int D_0013BB90[256];

static inline int find_free(void) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013BB90[i] < 0)
            return i;
    }
    return -1;
}

void LoaderSysEntryExternalSemaList(int value) {
    D_0013BB90[find_free()] = value;
}
