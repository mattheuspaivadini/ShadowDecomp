/* KERNEL.XFF @ 0x00A710 (24 B) - func_00A710 (static, no symbol in the shipped .symtab)
 * Evidence: tail call iosFreeParts(a0, a1, 0) (third argument cleared, first two forwarded). UNCONFIRMED: name, argument meaning; Ghidra FUN_0020a710.
 */
void iosFreeParts(void *ptn, void *p, int mode);

void func_00A710(void *ptn, void *p) {
    iosFreeParts(ptn, p, 0);
}
