/* KERNEL.XFF @ 0x00EFC0 (48 B) - InvertCurrentQuaternion
 * Evidence: &stack[top] then a volatile VU0 asm negates xyz (vsubw.x builds -1, vmulx.xyz) in place, i.e. the conjugate. The quaternion stack is a 16-byte array at .bss+0xE2C0 indexed by the
 * word at .data+0x420 (`sll 4`; the `lui $at/addiu/addu` triple is GAS's
 * expansion of a symbol+register address, so its delay slot stays a nop).
 * UNCONFIRMED: object names.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern int D_kernel_data_0420;
extern u_long128 D_kernel_bss_E2C0[];

void InvertCurrentQuaternion(void) {
    u_long128 *q = &D_kernel_bss_E2C0[D_kernel_data_0420];

    __asm__ __volatile__(
        "lqc2 $vf11, 0x0(%0)
"
        "vsubw.x $vf5, $vf0, $vf0w
"
        "vmulx.xyz $vf11, $vf11, $vf5x
"
        "sqc2 $vf11, 0x0(%0)
" : : "r"(q) : "memory");
}
