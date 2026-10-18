/* asm/cod/0171B8.s -> func_001171B8.
 * callback trampoline: saves $gp and loads the callback's $gp in one asm, call, restore (Session 22)
 * MATCHED. */
extern void (*D_00150E08)(int) __attribute__((section(".bss")));
extern int D_00150E0C __attribute__((section(".bss")));
extern int D_00150E10 __attribute__((section(".bss")));
extern int D_00133A64 __attribute__((section(".data")));

void func_001171B8(void) {
    int saved;

    if (D_00150E08 == 0)
        return;
    if (D_00133A64 != 0)
        return;
    __asm__ volatile ("move %0, $gp
	lw $gp, %1" : "=&r"(saved) : "m"(D_00150E0C));
    D_00150E08(D_00150E10);
    __asm__ volatile ("move $gp, %0" : : "r"(saved));
}
