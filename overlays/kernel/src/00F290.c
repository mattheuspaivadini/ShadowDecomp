/* KERNEL.XFF @ 0x00F290 (28 B) - InitQuaternionDrive
 * Evidence: top = 0, then a volatile asm stores $vf0 (0,0,0,1 = identity) into stack[0]. The quaternion stack is a 16-byte array at .bss+0xE2C0 indexed by the
 * word at .data+0x420 (`sll 4`; the `lui $at/addiu/addu` triple is GAS's
 * expansion of a symbol+register address, so its delay slot stays a nop).
 * UNCONFIRMED: object names.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern int D_kernel_data_0420;
extern u_long128 D_kernel_bss_E2C0[];

void InitQuaternionDrive(void) {
    D_kernel_data_0420 = 0;
    __asm__ __volatile__("sqc2 $vf0, 0x0(%0)" : : "r"(D_kernel_bss_E2C0) : "memory");
}
