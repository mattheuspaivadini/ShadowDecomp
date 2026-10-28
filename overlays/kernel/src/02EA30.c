/* KERNEL.XFF @ 0x02EA30 (80 B) - func_02EA30 (static, no symbol in the shipped .symtab)
 * Evidence: -1 unless the header starts with 'EQAT'; then the count at +4. UNCONFIRMED: name.
 */
int func_02EA30(unsigned char *h) {
    if (h[0] != 'E' || h[1] != 'Q' || h[2] != 'A' || h[3] != 'T') {
        return -1;
    }
    return *(int *)(h + 4);
}
