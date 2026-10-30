/* GAMECORE.XFF @ 0x04FC08 (20 B) - demo_PlayerDeathEffectEnd
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void demo_PlayerDeathEffectEnd(void) {
    endBossDeathEffect();
}
