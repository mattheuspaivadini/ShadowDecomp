/* KERNEL.XFF @ 0x0007C0 (8 B) - iosGetCnt0Pc
 * Evidence: `jr $ra` with the delay slot filled by `daddu $v0,$zero,$zero`
 * (the reorg pass moved the zero-return move into the slot). Return type is
 * int-sized: the callers use it as a counter value.
 */
int iosGetCnt0Pc(void) {
    return 0;
}
