/* GAMECORE.XFF @ 0x0B5120 (24 B) - gextailStartColProc
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void gextailStartColProc(int arg0) {
    SetCharacterObjCollisionProcFlag(arg0, 1);
}
