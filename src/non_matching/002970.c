/* STATUS (Session 4, 2026-10-14): NON_MATCHING. same pipelined table-scan family (search + clear).
 * The original .s stays in the build (asm/cod/002970.s); this C
 * attempt is kept for the record. */
/* asm/cod/002970.s -> func_00102970 @ 0x00102970 (0x54 bytes)
 * Find `key` in the 256-int table D_0013C790; on a hit clear the entry and
 * return the index, otherwise -1.
 */
extern int D_0013C790[256];

int func_00102970(int key) {
    int i = 0;

    do {
        if (D_0013C790[i] == key)
            break;
        i++;
    } while (i < 256);
    if (i == 256)
        return -1;
    D_0013C790[i] = 0;
    return i;
}
