/* KERNEL.XFF @ 0x016DB8 (20 B) - getIntrGpCount
 * Evidence: 64-bit load through `lui/addiu` + offset 0 with a nop slot: volatile u64 at .data+0x618. UNCONFIRMED: name.
 */
extern volatile unsigned long D_kernel_data_0618;
unsigned long getIntrGpCount(void) {
    return D_kernel_data_0618;
}
