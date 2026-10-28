/* GAMECORE.XFF @ 0x014100 (24 B) - scrSetFadeColorWhite
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void scrSetFadeColorWhite(void) {
    setFadeColor(1);
}
