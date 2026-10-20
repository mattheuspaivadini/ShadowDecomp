/* asm/cod/00A878.s -> func_0010A878.
 * Power-off callback dispatcher (installed by scePowerOffHandler 00A7D8): run
 * the user callback on the $gp saved there, then sync + ei. The save and the
 * load of $gp are one asm, so the %hi of the saved slot is materialised first.
 * MATCHED. */
struct PwrCb { void (*func)(void *); void *addr; };

extern void *D_00147180 __attribute__((section(".bss")));   /* the caller's $gp */

void func_0010A878(int a0, struct PwrCb *cb) {
    void (*func)(void *) = cb->func;
    void *gp;

    if (func) {
        __asm__ __volatile__ ("move %0, $gp\n\tlw $gp, %1" : "=&r" (gp) : "m" (D_00147180) : "memory");
        func(cb->addr);
        __asm__ __volatile__ ("move $gp, %0" : : "r" (gp));
    }
    __asm__ __volatile__ ("sync" ::: "memory");
    __asm__ __volatile__ ("ei");
}
