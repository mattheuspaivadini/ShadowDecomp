/* GAMECORE.XFF @ 0x0DABE0 (20 B) - get_status_camera_target_approach
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void get_status_camera_target_approach(void) {
    GAMEUTIL_get_cur_status_status_manager();
}
