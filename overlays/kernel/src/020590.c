/* KERNEL.XFF @ 0x020590 (8 B) - Sg2ExStAdpcmGetUserParam
 * Evidence: `jr $ra` with `lw $v0,0x2dc($a0)` in the delay slot: a one-field
 * accessor over the object passed in $a0. The pointed-to layout is NOT
 * confirmed beyond this offset (UNCONFIRMED field name), so the byte offset is
 * kept explicit instead of inventing a struct.
 */
int Sg2ExStAdpcmGetUserParam(unsigned char *p) {
    return *(int *)(p + 0x2dc);
}
