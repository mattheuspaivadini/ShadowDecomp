/* KERNEL.XFF @ 0x01BB50 (8 B) - get_letter_contents_data
 * Evidence: `jr $ra` with `lw $v0,0x1c($a0)` in the delay slot: a one-field
 * accessor over the object passed in $a0. The pointed-to layout is NOT
 * confirmed beyond this offset (UNCONFIRMED field name), so the byte offset is
 * kept explicit instead of inventing a struct.
 */
int get_letter_contents_data(unsigned char *p) {
    return *(int *)(p + 0x1c);
}
