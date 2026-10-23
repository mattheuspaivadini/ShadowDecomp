/* asm/cod/0000C8.s -> func_001000C8 @ 0x001000C8 (0x8 bytes)
 * SCE syscall 0x23 handler stub (no return; address passed to syscall 0x3C by entry).
 * UNCONFIRMED: syscall name.
 * MATCHED. */
void func_001000C8(void) __attribute__((noreturn));
void func_001000C8(void) {
    __asm__ __volatile__ ("addiu $3, $0, 0x23\n\tsyscall" : : : "$3");
    for (;;);
}
