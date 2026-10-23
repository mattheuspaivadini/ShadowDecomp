/* asm/cod/0000C8.s -> func_001000C8 @ 0x001000C8 (0x8 bytes)
 * SCE syscall 0x23 handler stub (no return; address passed to syscall 0x3C by entry).
 * UNCONFIRMED: syscall name.
 * Frameless and falls through, so the body is file-scope asm; a C function
 * body would add a prologue/epilogue (36 bytes). */
__asm__ (
    ".text\n"
    ".globl func_001000C8\n"
    ".ent func_001000C8\n"
    "func_001000C8:\n"
    "\taddiu $3, $0, 0x23\n"
    "\tsyscall\n"
    ".end func_001000C8\n"
);
