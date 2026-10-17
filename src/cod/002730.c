/* asm/cod/002730.s -> find_free.
 * loader external INTC handler list: inline free-slot search (Session 19)
 * MATCHED. */
struct intc_entry {
    int cause;      /* 0x0 */
    int id;         /* 0x4: handler id, < 0 = free slot */
};

extern struct intc_entry D_0013BF90[256];

static inline int find_free(void) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013BF90[i].id < 0)
            return i;
    }
    return -1;
}

void LoaderSysEntryExternalIntcHandlerList(int id, int cause) {
    int i = find_free();

    D_0013BF90[i].id = id;
    D_0013BF90[i].cause = cause;
}
