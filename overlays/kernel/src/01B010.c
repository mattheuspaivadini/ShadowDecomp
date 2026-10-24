/* KERNEL.XFF @ 0x01B010 (8 B) - isysGetLinkMax
 * Evidence: `jr $ra` with `addiu $v0,$zero,0x36b0` in the delay slot: the
 * constant 0x36B0 (13,488) is returned directly.
 */
int isysGetLinkMax(void) {
    return 0x36B0;
}
