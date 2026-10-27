/* KERNEL.XFF @ 0x00F220 (80 B) - PushQuaternionWithNoCopy
 * Evidence: InitQuaternionDrive() when top < 0, then ++top clamped to 0x3F (store, then conditional overwrite). The quaternion stack is the 16-byte array at .bss+0xE2C0 indexed by .data+0x420 (see GetCurrentQuaternion).
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern int D_kernel_data_0420;
extern u_long128 D_kernel_bss_E2C0[];
void InitQuaternionDrive(void);

void PushQuaternionWithNoCopy(void) {
    if (D_kernel_data_0420 < 0) {
        InitQuaternionDrive();
    }
    if (++D_kernel_data_0420 >= 0x40) {
        D_kernel_data_0420 = 0x3F;
    }
}
