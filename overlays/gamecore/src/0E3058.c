/* GAMECORE.XFF @ 0x0E3058 (60 B) - change_to_player_camera_target
 * Evidence: `jal DebugFindPlayer` with `$a0 = [s0+8]`, `beql $v1,$zero` to the epilogue with
 * the found object still in `$v0`, `sw $v1 -> +0x1C` on the non-null path.
 * UNCONFIRMED: struct field meanings and callee argument/return types
 
 */
void *DebugFindPlayer(void *p);

int change_to_player_camera_target(char *p) {
    void *obj = DebugFindPlayer(*(void **)(p + 8));
    if (obj != 0) {
        *(void **)(p + 0x1C) = obj;
        return 1;
    }
    return 0;
}
