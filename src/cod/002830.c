/* asm/cod/002830.s -> find_free.
 * loader external IOP memory list: inline free-slot search (Session 19)
 * MATCHED. */
extern int D_0013C790[256];

static inline int find_free(void) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013C790[i] == 0)
            return i;
    }
    return -1;
}

int LoaderSysEntryExternalIopMemoryList(int value) {
    int i;

    if (value != 0) {
        i = find_free();
        if (i >= 0) {
            D_0013C790[i] = value;
            return i;
        }
    }
    return -1;
}
