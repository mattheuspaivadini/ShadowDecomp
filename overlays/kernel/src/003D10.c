/* KERNEL.XFF @ 0x003D10 (12 B) - addMemoryDebugCallback
 * Evidence: `lui $v0,%hi(X)` / `jr $ra` / `sw $a0,%lo(X)($v0)` with an
 * R_MIPS_HI16+LO16 pair against the module's own .data (+0xB8): a one-word
 * global setter. The variable has no name in the shipped symbol table, so it
 * stays numbered; UNCONFIRMED beyond "one int-sized word in .data".
 */
extern int D_kernel_0000B8;

void addMemoryDebugCallback(int callback) {
    D_kernel_0000B8 = callback;
}
