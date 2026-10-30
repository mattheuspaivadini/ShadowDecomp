/* GAMECORE.XFF @ 0x0129F0 (20 B) - setDefaultFsEffect
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void setDefaultFsEffect(void) {
    fsEffectManagerInit();
}
