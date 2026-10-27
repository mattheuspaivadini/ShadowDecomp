/* KERNEL.XFF @ 0x0117D0 (60 B) - iosGetSinCos
 * Evidence: int angle -> float, scaled by 4.6566e-10 (0x2FFFFFF5, ~2^-31) and
 * pi (0x40490FDA), forwarded to func_011418 with the output pointer: a full
 * 32-bit turn maps to +-pi.
 */
void func_011418(float *sc, float angle);
void iosGetSinCos(float *sc, int angle) {
    func_011418(sc, (float)angle * 4.65660982e-10f * 3.1415926f);
}
