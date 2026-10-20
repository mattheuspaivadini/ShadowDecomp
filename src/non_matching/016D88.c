/* STATUS (Session 38, 2026-10-20): NON_MATCHING. best score 3 [cc=29].
 * libcdvd callback thread; $gp swap as inline asm (move/lw/move). Only _sceCd_c_cb_sem volatile
 * scores best (64 volatile combinations of the six globals tried). Residuals: (1) in the -1 exit
 * block the lui of D_00133A54 is scheduled above the volatile cb_sem store (original: after); (2)
 * dbr fills the beqz func slot with the sceCdCbfunc_number load, the original leaves a nop. Tried:
 * local vs global function pointer, nested ifs, memory clobbers on each asm, static inline gp
 * helpers, -fno-schedule-insns{,2}, -fno-strict-aliasing, void * / array declarations of
 * D_00133A54.
 * The original .s stays in the build (asm/cod/016D88.s); this C
 * draft (Session 38) is kept for the record. */
/* asm/cod/016D88.s -> _sceCd_cbLoop.
 * libcdvd callback thread: wait for the callback semaphore, exit on the -1
 * request, optionally trace, then run the user callback on the $gp saved by
 * sceCdCallback (016C80) and restore ours.
 */
extern __attribute__((section(".data"))) int D_00133A60;      /* callback semaphore */
extern __attribute__((section(".data"))) int D_00133A54;
extern __attribute__((section(".data"))) int SCE_CD_debug;
extern __attribute__((section(".data"))) volatile int _sceCd_c_cb_sem;
extern __attribute__((section(".data"))) int sceCdCbfunc_num;
extern __attribute__((section(".data"))) int sceCdCbfunc_number;
extern __attribute__((section(".data"))) void (*D_00150E00)(int);   /* the user callback */
extern __attribute__((section(".data"))) int D_00150E04;            /* its $gp */
extern __attribute__((section(".data"))) int D_00150E14;
extern char D_00138868[];

int WaitSema(int sema);
void ExitDeleteThread(void);
int scePrintf(const char *fmt, ...);

void _sceCd_cbLoop(void) {
    void (*func)(int);
    int gp;

    for (;;) {
        WaitSema(D_00133A60);
        if (sceCdCbfunc_num == -1) {
            _sceCd_c_cb_sem = 0;
            sceCdCbfunc_num = 0;
            D_00133A54 = 0;
            D_00150E14 = 0;
            ExitDeleteThread();
        }
        if (SCE_CD_debug > 0)
            scePrintf(D_00138868, D_00150E00, sceCdCbfunc_number);
        func = D_00150E00;
        if (func && sceCdCbfunc_number) {
            asm volatile ("move %0, $gp" : "=r" (gp));
            asm volatile ("lw $gp, %0" : : "m" (D_00150E04) : "memory");
            func(sceCdCbfunc_number);
            asm volatile ("move $gp, %0" : : "r" (gp));
        }
        _sceCd_c_cb_sem = 0;
    }
}
