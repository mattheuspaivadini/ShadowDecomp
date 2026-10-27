/* KERNEL.XFF @ 0x011810 (60 B) - iosGetSin
 * Evidence: same 2^-31 * pi angle scaling as iosGetSinCos, sibling call to the
 * static at .text+0x11568. UNCONFIRMED: callee name.
 */
float func_011568(float angle);
float iosGetSin(int angle) {
    return func_011568((float)angle * 4.65660982e-10f * 3.1415926f);
}
