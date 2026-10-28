/* GAMECORE.XFF @ 0x11FC80 (20 B) - SCRConditionHardMode
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void SCRConditionHardMode(void) {
    getGameHardMode();
}
