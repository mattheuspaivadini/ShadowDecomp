/* STATUS (Session 29, 2026-10-18): NON_MATCHING. best score 5 [cc=29].
 * volatile counter in section(".data") (lui/%lo, not $gp) + a[0x20] vs b[0] split reproduce all loads; residual = original
 * fills the shared-target `lw v1,0(s3)` into beqzl slots and tail-merges `daddu v0,s1`, we emit plain beqz+nop and duplicate the move.
 * Tried: single-exit/result-variable forms (worse), 400 permute_gen variants (none < 5). */
/* asm/cod/020F30.s -> func_00120F30 @ 0x00120F30
 * Wait on the D_00163CC0 semaphore, sync the 0x100-byte D_00165DC0 pair of records and
 * pick the one whose leading word advances the last-seen counter D_00135940. */
extern int D_00163CC0[];
extern volatile int D_00135940 __attribute__((section(".data")));
extern int D_00165DC0[];
extern int D_00165E40[];

int WaitSema(int sema);
void SyncDCache(void *start, void *end);

int *func_00120F30(void) {
    int *a = D_00165DC0;
    int *b = a + 0x20;
    int av, bv;

    D_00135940 = 0;
    WaitSema(D_00163CC0[0]);
    SyncDCache(a, (char *)a + 0xFF);
    av = a[0];
    if (D_00135940 < av && a[0x20] < av) {
        D_00135940 = av;
    } else {
        bv = b[0];
        if (D_00135940 < bv) {
            if (a[0] < bv) {
                D_00135940 = bv;
                return D_00165E40;
            }
        }
        a[2] = 0;
    }
    return a;
}
