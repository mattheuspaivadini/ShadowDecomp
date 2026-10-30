/* GAMECORE.XFF @ 0x0424E0 (20 B) - SCRGetFirstObj
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void SCRGetFirstObj(void) {
    GAMEUTIL_get_first_obj();
}
