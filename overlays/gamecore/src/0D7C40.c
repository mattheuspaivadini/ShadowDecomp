/* GAMECORE.XFF @ 0x0D7C40 (40 B) - set_post_boss_dead_playable_flag_camera_etc_condition
 * Evidence: `$s0 = $a1`, `jal get_game_camera` (argument forwarded), `sw $s0 -> 0x18($v0)`.
 * UNCONFIRMED: field meaning
 
 */
char *get_game_camera(char *p);

void set_post_boss_dead_playable_flag_camera_etc_condition(char *cam, int flag) {
    *(int *)(get_game_camera(cam) + 0x18) = flag;
}
