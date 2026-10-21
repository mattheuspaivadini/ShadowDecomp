/* asm/cod/016D88.s -> _sceCd_cbLoop.
 * SCE libcdvd _sceCd_cbLoop; $gp swap asm, volatile cb_sem, volatile read of sceCdCbfunc_number in the call test, empty asm fence after the exit-path semaphore store (Session 41)
 * MATCHED. */
/* libcdvd callback thread: wait for the callback semaphore, exit on the -1
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
            __asm__ __volatile__ ("");     /* keeps the D_00133A54 lui below the semaphore store */
            sceCdCbfunc_num = 0;
            D_00133A54 = 0;
            D_00150E14 = 0;
            ExitDeleteThread();
        }
        if (SCE_CD_debug > 0)
            scePrintf(D_00138868, D_00150E00, sceCdCbfunc_number);
        func = D_00150E00;
        if (func && *(volatile int *)&sceCdCbfunc_number) {   /* volatile read: no delay-slot fill */
            asm volatile ("move %0, $gp" : "=r" (gp));
            asm volatile ("lw $gp, %0" : : "m" (D_00150E04) : "memory");
            func(sceCdCbfunc_number);
            asm volatile ("move $gp, %0" : : "r" (gp));
        }
        _sceCd_c_cb_sem = 0;
    }
}
