/* KERNEL.XFF @ 0x014C60 (152 B) - iosGsSetMode
 * Evidence: `lui $2,0x2 / addiu $11,$2,-0xFF0` names .bss base 0x1F010; the
 * guard is `lw $3,0xA4($11)` (mode) and each arm writes the 4 dimensions at
 * +0x00/+0x04/+0x08/+0x0C plus the selector at +0xA0 of the same context.  The
 * three image-state ints are at .data+0x5A0/0x5A4/0x5A8 and are plain
 * (non-volatile) objects: each store is `lui $n,%hi` + `sw $x,%lo($n)` with the
 * low half folded into the store immediate, one lui per object, no CSE.  Each
 * arm also uses the *same* source statement order (select/f08/f0C/f00/f04 then
 * the three .data words); the scheduler then emits f04, 05A4, 05A8, f08, f0C,
 * f00, 05A0 with the selector store moved into the `jr $ra` delay slot.
 * UNCONFIRMED: context/field names, the two screen modes' meaning.
 */
struct DcCtx {
    int f00;
    int f04;
    int f08;
    int f0C;
    char pad10[0x90];
    int sel;                    /* 0xA0 */
    int mode;                   /* 0xA4 */
};
extern struct DcCtx D_kernel_bss_1F010;
extern int D_kernel_data_05A0;
extern int D_kernel_data_05A4;
extern int D_kernel_data_05A8;

void iosGsSetMode(void) {
    if (D_kernel_bss_1F010.mode != 0) {
        D_kernel_bss_1F010.sel = 0;
        D_kernel_bss_1F010.f08 = 0x200;
        D_kernel_bss_1F010.f0C = 0x1A0;
        D_kernel_bss_1F010.f00 = 0x280;
        D_kernel_bss_1F010.f04 = 0x1C0;
        D_kernel_data_05A0 = 0;
        D_kernel_data_05A4 = 0x50;
        D_kernel_data_05A8 = 1;
    } else {
        D_kernel_bss_1F010.sel = 1;
        D_kernel_bss_1F010.f08 = 0x200;
        D_kernel_bss_1F010.f0C = 0x1C0;
        D_kernel_bss_1F010.f00 = 0x200;
        D_kernel_bss_1F010.f04 = 0x1C0;
        D_kernel_data_05A0 = 1;
        D_kernel_data_05A4 = 2;
        D_kernel_data_05A8 = 0;
    }
}
