/* GAMECORE.XFF @ 0x117958 (20 B) - SCRFuncSetMyselfMotionSpeedRatio
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void SCRFuncSetMyselfMotionSpeedRatio(void) {
    SCRSetCharaMotionPlaySpeedRatio();
}
