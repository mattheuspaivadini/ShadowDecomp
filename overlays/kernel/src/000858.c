/* KERNEL.XFF @ 0x000858 (16 B) - iosGetClock
 * Evidence: `lui $v0` (HI16) + `ld $v1,lo($v0)` reads a 64-bit counter from
 * .bss+0x9098, then the return slot stores it through the incoming `$a0`
 * (`jr $ra` / delay `sd $v1,0x0($a0)`). So the routine copies the counter into
 * a caller-supplied object; the 64-bit width is the `ld`/`sd` pair.
 * UNCONFIRMED: the object's name (.bss is unnamed in the shipped symtab); the
 * getter name comes from the module's own symbol table.
 */
extern unsigned long D_kernel_bss_9098;

void iosGetClock(unsigned long *clock) {
    *clock = D_kernel_bss_9098;
}
