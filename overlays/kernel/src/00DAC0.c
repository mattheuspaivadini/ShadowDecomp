/* KERNEL.XFF @ 0x00DAC0 (72 B) - iosIColToFvec
 * Evidence: the packed colour is split into four ints (bytes 0..3) on the stack and passed to iosITOF0Vector(v, tmp).
 */
void iosITOF0Vector(float *d, int *s);

void iosIColToFvec(float *v, unsigned int col) {
    int t[4];

    t[0] = col & 0xFF;
    t[1] = (col >> 8) & 0xFF;
    t[2] = (col >> 16) & 0xFF;
    t[3] = col >> 24;
    iosITOF0Vector(v, t);
}
