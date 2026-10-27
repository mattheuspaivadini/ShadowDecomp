/* KERNEL.XFF @ 0x000B78 (20 B) - iosGetTCount
 * Evidence: `lui/addiu` of .bss+0x90A0 then `ld $v0,0($v1)` with the `jr $ra` delay
 * slot left as a nop: a 64-bit load GCC refuses to move into the slot, i.e. a
 * volatile object (the T-count is advanced by the interrupt handler).
 * UNCONFIRMED: the object name (.bss is unnamed in the shipped symtab).
 */
extern volatile unsigned long D_kernel_bss_90A0;
unsigned long iosGetTCount(void) { return D_kernel_bss_90A0; }
