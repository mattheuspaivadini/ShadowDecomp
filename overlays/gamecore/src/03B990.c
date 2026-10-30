/* GAMECORE.XFF @ 0x03B990 (28 B) - nico_IK_idDetect
 * Evidence: [a0+0x14] & 0xFFFEFFFF -> bss+0x6A40
 * UNCONFIRMED: none
 */
extern unsigned int D_kernel_bss_6A40[];

void nico_IK_idDetect(unsigned int *p) {
    D_kernel_bss_6A40[0] = p[5] & ~0x10000;
}
