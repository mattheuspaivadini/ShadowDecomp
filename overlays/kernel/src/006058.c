/* KERNEL.XFF @ 0x006058 (12 B) - iosGetPrintfMode
 * Evidence: `lui $v0,%hi` / `jr $ra` / `addiu $v0,%lo` against .data +0x360:
 * returns the address of that object (observed with no further load at the
 * call sites in this module). UNCONFIRMED width; the address is the evidence.
 */
extern int D_kernel_000360;

void *iosGetPrintfMode(void) {
    return &D_kernel_000360;
}
