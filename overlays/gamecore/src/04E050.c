/* GAMECORE.XFF @ 0x04E050 (20 B) - effect_blood_free
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void effect_blood_free(void) {
    iosFree();
}
