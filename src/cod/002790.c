/* asm/cod/002790.s -> find_free.
 * loader external thread list: inline free-slot search used as the index (Session 19)
 * MATCHED. */
extern int D_0013B790[256];

static inline int find_free(void) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013B790[i] < 0)
            return i;
    }
    return -1;
}

void LoaderSysEntryExternalThreadList(int value) {
    D_0013B790[find_free()] = value;
}
