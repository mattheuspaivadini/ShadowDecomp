/* STATUS (Session 4, 2026-10-14): NON_MATCHING. same pipelined table-scan family as func_00102790 (on D_0013BB90).
 * The original .s stays in the build (asm/cod/0027E0.s); this C
 * attempt is kept for the record. */
/* asm/cod/0027E0.s -> func_001027E0 @ 0x001027E0 (0x4C bytes)
 * Identical shape to func_00102790, on the table D_0013BB90.
 */
extern int D_0013BB90[256];

void LoaderSysEntryExternalSemaList(int value) {
    int i = 0;

    while (D_0013BB90[i] >= 0) {
        i++;
        if (i >= 256) {
            i = -1;
            break;
        }
    }
    D_0013BB90[i] = value;
}
