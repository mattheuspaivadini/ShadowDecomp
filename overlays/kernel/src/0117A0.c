/* KERNEL.XFF @ 0x0117A0 (48 B) - iosGetTanf
 * Evidence: same 2-float buffer from func_011418, returns t[1] / t[0] (div.s;
 * the two nops are the R5900 FPU hazard padding).
 */
void func_011418(float *sc, float angle);
float iosGetTanf(float angle) {
    float t[2];

    func_011418(t, angle);
    return t[1] / t[0];
}
