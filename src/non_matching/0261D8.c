/* STATUS (10, 2026-10-16): NON_MATCHING. best score 6 [cc=296].
 * 
 * The original .s stays in the build (asm/cod/0261D8.s); this C
 * draft (10) is kept for the record. */
struct N0261D8 {
    int f00;                  /* 0x00 */
    int f04;                  /* 0x04 */
    int f08;                  /* 0x08 key */
    int f0C;                  /* 0x0C */
    int f10;                  /* 0x10 */
    struct N0261D8 *f14;      /* 0x14 next */
};

extern int D_00169F90[];    /* list head (absolute: lui/%lo + lw) */
extern __attribute__((section(".data"))) int __sce_eh_sema_id;   /* pool semaphore */

int WaitSema(int sema);
int SignalSema(int sema);
int free(int node);
int func_00127448(void);

int __deregister_frame_info(int key) {
    struct N0261D8 *n;
    struct N0261D8 **pp;

    WaitSema(__sce_eh_sema_id);
    pp = (struct N0261D8 **)&D_00169F90[0];
    n = *pp;
    if (n != 0) {
        do {
            if (n->f08 == key) {
                *pp = n->f14;
                if (n->f0C != 0 && n->f0C != key)
                    free(n->f0C);
                SignalSema(__sce_eh_sema_id);
                return n;
            }
            pp = &n->f14;
            n = *pp;
        } while (n != 0);
    }
    SignalSema(__sce_eh_sema_id);
    return func_00127448();
}
