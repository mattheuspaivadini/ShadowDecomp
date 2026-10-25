/* KERNEL.XFF @ 0x011850 (60 B) - iosGetCos
 * Evidence: same 2^-31 * pi angle scaling as iosGetSinCos, sibling call to the
 * static at .text+0x11688. UNCONFIRMED: callee name.
 */
float func_011688(float angle);
float iosGetCos(int angle) {
    return func_011688((float)angle * 4.65660982e-10f * 3.1415926f);
}
