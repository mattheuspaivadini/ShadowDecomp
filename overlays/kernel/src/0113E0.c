/* KERNEL.XFF @ 0x0113E0 (56 B) - iosGetAlignSinCosf
 * Evidence: the static sin/cos routine at .text+0x11418 fills a 2-float stack
 * buffer; the two results are written back swapped (t[1] to d[0], t[0] to
 * d[1]). UNCONFIRMED: which slot is sin and which is cos.
 */
void func_011418(float *sc, float angle);
void iosGetAlignSinCosf(float *d, float angle) {
    float t[2];

    func_011418(t, angle);
    d[0] = t[1];
    d[1] = t[0];
}
