/* asm/cod/002970.s -> find_entry.
 * loader external IOP memory delete: inline search, returns the index (Session 19)
 * MATCHED. */
extern int D_0013C790[256];

static inline int find_entry(int key) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013C790[i] == key)
            return i;
    }
    return -1;
}

int LoaderSysDeleteExternalIopMemoryList(int key) {
    int i = find_entry(key);

    if (i >= 0)
        D_0013C790[i] = 0;
    return i;
}
