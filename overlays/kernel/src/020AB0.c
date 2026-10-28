/* KERNEL.XFF @ 0x020AB0 (80 B) - ____VolPerBackup
 * Evidence: copies 16 words between +0x24C and +0x28C of the passed block (restore != 0: 0x24C -> 0x28C, else 0x28C -> 0x24C), two words per iteration, the source walks through the parameter. UNCONFIRMED: struct layout, argument meaning.
 */
void ____VolPerBackup(int *p, int restore) {
    int *dst;
    int i;

    if (restore) {
        dst = p + 0xA3;
        p = p + 0x93;
    } else {
        dst = p + 0x93;
        p = p + 0xA3;
    }
    for (i = 0; i < 8; i++) {
        *dst++ = *p++;
        *dst++ = *p++;
    }
}
