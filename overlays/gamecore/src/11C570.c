/* GAMECORE.XFF @ 0x11C570 (20 B) - SCRConditionAttacked
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void SCRConditionAttacked(void) {
    nico_GetCharacterAttackedFlag();
}
