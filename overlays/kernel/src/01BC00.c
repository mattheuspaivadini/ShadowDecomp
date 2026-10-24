/* KERNEL.XFF @ 0x01BC00 (8 B) - is_init_letter_called
 * Evidence: `jr $ra` with `lw $v0,0x20($a0)` in the delay slot: a one-field
 * accessor over the object passed in $a0. The pointed-to layout is NOT
 * confirmed beyond this offset (UNCONFIRMED field name), so the byte offset is
 * kept explicit instead of inventing a struct.
 */
int is_init_letter_called(unsigned char *p) {
    return *(int *)(p + 0x20);
}
