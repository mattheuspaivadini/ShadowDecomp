/* KERNEL.XFF @ 0x0005A8 (32 B) - iosCdStSkip
 * Evidence:
 *   lui/addiu   -> &D_bss_8050 (relocation against .bss + 0x8050)
 *   dsll32/dsrl32 $a0 -> zero-extend the 32-bit argument to 64 bits
 *   ld v0,0($v1) / daddu v0,v0,$a0 / sd v0,0($v1)
 * i.e. `u64 += (unsigned int)n` on a 64-bit counter. UNCONFIRMED name.
 */
extern unsigned long D_kernel_bss_8050;

void iosCdStSkip(unsigned int n) {
    D_kernel_bss_8050 += n;
}
