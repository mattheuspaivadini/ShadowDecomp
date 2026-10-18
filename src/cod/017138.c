/* asm/cod/017138.s -> sceCdPOffCallback.
 * $gp saved with a volatile asm store (same idiom as sceCdCallback 016C80); the asm keeps dbr from filling the beqz slot from above, so it takes the target's move v0 as in the original (Session 28).
 * MATCHED. */
extern __attribute__((section(".data"))) int D_00133A88;
extern __attribute__((section(".data"))) void *D_00150E08;
extern __attribute__((section(".data"))) void *D_00150E0C;
extern __attribute__((section(".data"))) void *D_00150E10;
int func_00117210(void);
int DIntr(void);
int EIntr(void);

void *sceCdPOffCallback(void *func, void *addr) {
    int intr;
    void *old;

    if (D_00133A88 < 0)
        func_00117210();
    intr = DIntr();
    old = D_00150E08;
    D_00150E10 = addr;
    D_00150E08 = func;
    /* $gp store as in sceCdCallback (016C80); the volatile asm also keeps
     * dbr from hoisting it into the beqz slot. */
    asm volatile ("sw $gp, %0" : "=m" (D_00150E0C));
    if (intr != 0)
        EIntr();
    return old;
}
