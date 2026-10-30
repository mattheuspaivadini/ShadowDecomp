/* GAMECORE.XFF @ 0x1184D8 (24 B) - SCRFuncSetAutoBossGazePos
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void SCRFuncSetAutoBossGazePos(void) {
    GAMEUTIL_set_auto_get_flag_boss_interest_position(1);
}
