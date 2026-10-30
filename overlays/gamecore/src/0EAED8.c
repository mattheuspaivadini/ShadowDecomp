/* GAMECORE.XFF @ 0x0EAED8 (24 B) - flush_game_camera
 * Evidence: ops ld sd; calls j <.text>; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
void func_000EBC98(char *p);
void flush_game_camera(char *p) {
    func_000EBC98(p + 0x1370);
}
