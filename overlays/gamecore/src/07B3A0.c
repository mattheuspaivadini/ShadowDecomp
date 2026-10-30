/* GAMECORE.XFF @ 0x07B3A0 (20 B) - player_IsSwiming
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void player_IsSwiming(void) {
    GAMEUTIL_is_swimming_now();
}
