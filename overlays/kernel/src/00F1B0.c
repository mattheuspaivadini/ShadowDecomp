/* KERNEL.XFF @ 0x00F1B0 (112 B) - PushQuaternion
 * Evidence: the head is PushQuaternionWithNoCopy (00F220) verbatim: top =
 * .data+0x420, InitQuaternionDrive() when it is negative, then ++top clamped at
 * 0x3F. The tail is one 128-bit stack copy, stack[top] = stack[top-1], of the
 * 16-byte array at .bss+0xE2C0 (`sll a0,4`, `addu a1,v1,a0` + `lq -0x10(a1)`,
 * `addu a0,a0,v1` + `sq 0(a0)`; the two adds keep the swapped operand order,
 * which is why the copy is spelled with byte offsets instead of two
 * `D_kernel_bss_E2C0[i]` subscripts, which GCC CSEs into one copy).
 * UNCONFIRMED: object names.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern int D_kernel_data_0420;
extern u_long128 D_kernel_bss_E2C0[];
void InitQuaternionDrive(void);

void PushQuaternion(void) {
    if (D_kernel_data_0420 < 0) {
        InitQuaternionDrive();
    }
    if (++D_kernel_data_0420 >= 0x40) {
        D_kernel_data_0420 = 0x3F;
    }
    *(u_long128 *)((char *)D_kernel_bss_E2C0 + D_kernel_data_0420 * 16) =
        *(u_long128 *)((char *)D_kernel_bss_E2C0 + D_kernel_data_0420 * 16 - 16);
}
