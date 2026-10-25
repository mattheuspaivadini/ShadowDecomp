/* KERNEL.XFF @ 0x000B90 (36 B) - iosGetTCountExtension
 * Evidence: reads the 32-bit Timer-0 counter at 0x10000000 (T0_COUNT), zero-
 * extends it (`dsll32/dsrl32`) and ORs it into the volatile 64-bit T-count
 * at .bss+0x90A0 (same object as iosGetTCount).
 * UNCONFIRMED: the object name.
 */
extern volatile unsigned long D_kernel_bss_90A0;
unsigned long iosGetTCountExtension(void) {
    return D_kernel_bss_90A0 | (unsigned int)*(volatile int *)0x10000000;
}
