/* KERNEL.XFF @ 0x00D5D8 (132 B) - iosCalcIcolorToBrightness
 * Evidence: splits the 32-bit colour into four int channels on the stack, multiplies them by the .rodata+0x10B0 weight vector with iosMulMvec(v, v, &w), and returns ((r+g+b) >> 23) & 0xFF. UNCONFIRMED: names.
 */
typedef struct { long lo, hi; } Mvec;
extern Mvec D_kernel_rodata_10B0;
void iosMulMvec(void *d, void *a, void *b);

int iosCalcIcolorToBrightness(unsigned int c) {
    int v[4];
    Mvec m;

    v[0] = c & 0xFF;
    v[1] = (c >> 8) & 0xFF;
    v[2] = (c >> 16) & 0xFF;
    v[3] = c >> 24;
    m = D_kernel_rodata_10B0;
    iosMulMvec(v, v, &m);
    return ((v[0] + v[1] + v[2]) >> 23) & 0xFF;
}
