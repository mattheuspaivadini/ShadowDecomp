/* GAMECORE.XFF @ 0x0140E8 (24 B) - scrSetFadeColorBlack
 * Evidence: frame, `$a0 = 0` before the sibling `j setFadeColor`.
 */
int setFadeColor(int color);

void scrSetFadeColorBlack(void) {
    setFadeColor(0);
}
