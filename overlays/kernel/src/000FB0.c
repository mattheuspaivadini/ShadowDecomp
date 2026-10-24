/* KERNEL.XFF @ 0x000FB0 (8 B) - iosEE2IopEndChk
 * Evidence: `jr $ra` with `li $v0,1` (addiu $v0,$zero,1) in the delay slot.
 * UNCONFIRMED: the return is a plain int flag; no caller in this module
 * contradicts an int-sized result.
 */
int iosEE2IopEndChk(void) {
    return 1;
}
