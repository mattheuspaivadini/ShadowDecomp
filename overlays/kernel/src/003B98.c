/* KERNEL.XFF @ 0x003B98 (40 B) - iosGetMallocPtn
 * Evidence: loads the block header pointer stored just before the user pointer
 * (`lw $v1,-4($a0)`), assembles bytes 11/7/3 of it as a 24-bit value and
 * scales it by 4 (`sll 2`). UNCONFIRMED: the header layout (bytes 3/7/11 are
 * the low bytes of three consecutive little-endian words).
 */
int iosGetMallocPtn(void *p) {
    unsigned char *h = ((unsigned char **)p)[-1];
    return ((h[11] << 16) | (h[7] << 8) | h[3]) << 2;
}
