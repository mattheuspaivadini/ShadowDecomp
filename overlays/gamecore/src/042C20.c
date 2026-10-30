/* GAMECORE.XFF @ 0x042C20 (20 B) - SCRGetLocalDirZ
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void SCRGetLocalDirZ(void) {
    GAMEUTIL_get_local_directionZ();
}
