/* KERNEL.XFF @ 0x00EEF0 (32 B) - GetLastQuaternion
 * Evidence: returns &stack[top - 1] (base - 0x10 + top*16). The quaternion stack is a 16-byte array at .bss+0xE2C0 indexed by the
 * word at .data+0x420 (`sll 4`; the `lui $at/addiu/addu` triple is GAS's
 * expansion of a symbol+register address, so its delay slot stays a nop).
 * UNCONFIRMED: object names.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern int D_kernel_data_0420;
extern u_long128 D_kernel_bss_E2C0[];

u_long128 *GetLastQuaternion(void) {
    return &D_kernel_bss_E2C0[D_kernel_data_0420 - 1];
}
