/* GAMECORE.XFF @ 0x0DBA58 (60 B) - constructor_camera_target_visible_angle_manager
 * Evidence: `jal <.text>+0xDBB08` with `$s0 = $a0`, then tail `j <.text>+0xDBA98` with `$a0 = $s0`,
 * `$a1 = 0xF`, `$f12 = 0x43340000` (180.0f), `$f13 = 0x40000000` (2.0f).
 * UNCONFIRMED: struct field meanings and callee argument/return types
 
 */
void func_000DBB08(void *p);
void func_000DBA98(void *p, int count, float a, float b);

void constructor_camera_target_visible_angle_manager(char *p) {
    func_000DBB08(p);
    func_000DBA98(p, 0xF, 180.0f, 2.0f);
}
