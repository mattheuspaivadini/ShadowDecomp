/* GAMECORE.XFF @ 0x01C7B0 (20 B) - unloadObj
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void unloadObj(void) {
    isysRequestDeleteObj();
}
