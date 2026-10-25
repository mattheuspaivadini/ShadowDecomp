/* KERNEL.XFF @ 0x015F18 (36 B) - iosGetField
 * Evidence: bit 13 (FIELD) of the 64-bit GS CSR at 0x12001000, volatile load.
 */
int iosGetField(void) {
    return (*(volatile unsigned long *)0x12001000 >> 13) & 1;
}
