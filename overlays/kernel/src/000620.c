/* KERNEL.XFF @ 0x000620 (20 B) - iosCdSetErrorCallback
 * Evidence: two independent HI16/LO16 pairs against .data +0x0 and +0x4
 * (different base registers $v0/$v1, `jr $ra` between the stores), i.e. two
 * separate one-word globals rather than one array. Field names UNCONFIRMED.
 */
extern int D_kernel_0000;
extern int D_kernel_0004;

void iosCdSetErrorCallback(int callback, int arg) {
    D_kernel_0000 = callback;
    D_kernel_0004 = arg;
}
