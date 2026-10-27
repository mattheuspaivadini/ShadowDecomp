/* KERNEL.XFF @ 0x01F320 (24 B) - GetStrHashWorkBuffer
 * Evidence: (4 << bits) + count * 16 + 0x66.
 */
int GetStrHashWorkBuffer(int bits, int count) {
    return (4 << bits) + count * 16 + 0x66;
}
