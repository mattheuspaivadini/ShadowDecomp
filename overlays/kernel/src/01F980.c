/* KERNEL.XFF @ 0x01F980 (8 B) - Sg2DmaInit
 * Evidence: `jr $ra` with `daddu $v0,$zero,$zero` in the delay slot (reorg
 * moved the zero-return move into the slot). UNCONFIRMED: the value is used as
 * an address/flags word by the callers; the width is int-sized either way.
 */
int Sg2DmaInit(void) {
    return 0;
}
