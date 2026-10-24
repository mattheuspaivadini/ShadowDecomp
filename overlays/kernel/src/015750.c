/* KERNEL.XFF @ 0x015750 (8 B) - getDispBufferAddressTBP
 * Evidence: `jr $ra` with `daddu $v0,$zero,$zero` in the delay slot (reorg
 * moved the zero-return move into the slot). UNCONFIRMED: the value is used as
 * an address/flags word by the callers; the width is int-sized either way.
 */
int getDispBufferAddressTBP(void) {
    return 0;
}
