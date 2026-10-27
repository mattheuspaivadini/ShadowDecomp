/* KERNEL.XFF @ 0x01CD70 (20 B) - iosGet2ByteCharCode
 * Evidence: little-endian 16-bit read from two bytes.
 */
int iosGet2ByteCharCode(unsigned char *s) {
    return (s[1] << 8) | s[0];
}
