/* KERNEL.XFF @ 0x00DA90 (44 B) - iosIColToMvecSl
 * Evidence: splits a packed RGBA word into four ints (bytes 0..3 to v[0..3]);
 * srl 8/16/24 + andi 0xFF, scheduled from source order v[0]..v[3].
 */
void iosIColToMvecSl(int *v, unsigned int col) {
    v[0] = col & 0xFF;
    v[1] = (col >> 8) & 0xFF;
    v[2] = (col >> 16) & 0xFF;
    v[3] = col >> 24;
}
