/* KERNEL.XFF @ 0x01fea0 (96 B) - Sg2ExStAdpcmInit
 * Evidence: the loop zeroes 48 words downwards from .bss+0x7F6BC (pointer starts
 * at the symbol +0xBC and the counter runs 0x2F..0 with `bgez`), which is the
 * 48-word table at .bss+0x7F600; the three nops are real.  Then
 * Sg2StAdpcmInit(0), then two flags: .bss+0x7F5F8 = 1 and .bss+0x7F5FC = 0.
 * The first store is the split `lui/addiu` + `sw 0(reg)` form (an address value,
 * not a folded displacement) => that object is volatile; the second store keeps
 * the LO16 in the `sw` displacement.  The shipped code keeps the flag address
 * in $3 and the constant 1 in $2; forcing the two locals with
 * `register ... asm` is what reproduces that (otherwise $2/$3 swap and 4 words
 * differ).
 * UNCONFIRMED: the meaning of the two flags and the Sg2StAdpcmInit prototype.
 */
extern int D_kernel_bss_7F600[48];
extern volatile int D_kernel_bss_7F5F8;
extern int D_kernel_bss_7F5FC;
void Sg2StAdpcmInit(int ch);

void Sg2ExStAdpcmInit(void) {
    register volatile int *q asm("$3");
    register int one asm("$2");
    int i;

    for (i = 0x2F; i >= 0; i--) {
        D_kernel_bss_7F600[i] = 0;
    }
    Sg2StAdpcmInit(0);
    q = &D_kernel_bss_7F5F8;
    one = 1;
    *q = one;
    D_kernel_bss_7F5FC = 0;
}
