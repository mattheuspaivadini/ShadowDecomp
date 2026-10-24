/* KERNEL.XFF @ 0x020548 (8 B) - Sg2ExStAdpcmGetFd
 * Evidence: `jr $ra` with `lw $v0,0x2d8($a0)` in the delay slot: a one-field
 * accessor over the object passed in $a0. The pointed-to layout is NOT
 * confirmed beyond this offset (UNCONFIRMED field name), so the byte offset is
 * kept explicit instead of inventing a struct.
 */
int Sg2ExStAdpcmGetFd(unsigned char *p) {
    return *(int *)(p + 0x2d8);
}
