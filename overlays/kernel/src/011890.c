/* KERNEL.XFF @ 0x011890 (52 B) - iosGetTan
 * Evidence: iosGetSinCos(tmp, angle) then t[1] / t[0].
 */
void iosGetSinCos(float *sc, int angle);
float iosGetTan(int angle) {
    float t[2];

    iosGetSinCos(t, angle);
    return t[1] / t[0];
}
