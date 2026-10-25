/* KERNEL.XFF @ 0x011FE8 (92 B) - iosGetScaleInverseVector
 * Evidence: d[i] = 1.0f / s[i] for the four components (div.s with the R5900 FPU hazard nops).
 */
void iosGetScaleInverseVector(float *d, float *s) {
    d[0] = 1.0f / s[0];
    d[1] = 1.0f / s[1];
    d[2] = 1.0f / s[2];
    d[3] = 1.0f / s[3];
}
