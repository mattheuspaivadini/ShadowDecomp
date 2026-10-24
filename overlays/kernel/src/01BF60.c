/* KERNEL.XFF @ 0x01BF60 (8 B) - get_total_letter_in_post
 * Evidence: `jr $ra` with `lw $v0,0x0($a0)` in the delay slot: a one-field
 * accessor over the object passed in $a0. The pointed-to layout is NOT
 * confirmed beyond this offset (UNCONFIRMED field name), so the byte offset is
 * kept explicit instead of inventing a struct.
 */
int get_total_letter_in_post(unsigned char *p) {
    return *(int *)(p + 0x0);
}
