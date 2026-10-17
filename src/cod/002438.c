/* asm/cod/002438.s -> clear_list.
 * loader: remove every external INTC handler, then inline list clear (Session 19)
 * MATCHED. */
struct intc_entry {
    int cause;      /* 0x0 */
    int id;         /* 0x4: handler id, < 0 = free slot */
};

extern struct intc_entry D_0013BF90[256];

void DisableIntc(int cause);
void RemoveIntcHandler(int cause, int id);

static inline void clear_list(void) {
    int i;

    for (i = 0; i < 256; i++) {
        D_0013BF90[i].id = -1;
        D_0013BF90[i].cause = -1;
    }
}

void LoaderSysDeleteAllExternalIntcHandler(void) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013BF90[i].id >= 0) {
            DisableIntc(D_0013BF90[i].cause);
            RemoveIntcHandler(D_0013BF90[i].cause, D_0013BF90[i].id);
            D_0013BF90[i].id = -1;
            D_0013BF90[i].cause = -1;
        }
    }
    clear_list();
}
