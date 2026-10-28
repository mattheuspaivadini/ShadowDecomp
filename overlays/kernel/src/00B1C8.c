/* KERNEL.XFF @ 0x00B1C8 (24 B) - func_00B1C8 (static, no symbol in the shipped .symtab)
 * Evidence: tail call to the static at .text+0xAE00 with the caller's call site (return address - 8, `register $31` read). UNCONFIRMED: name; Ghidra FUN_0020b1c8.
 */
void func_00AE00(void *pc);

void func_00B1C8(void) {
    register char *ra __asm__("$31");

    func_00AE00(ra - 8);
}
