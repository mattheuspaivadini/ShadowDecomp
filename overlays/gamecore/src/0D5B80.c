/* GAMECORE.XFF @ 0x0D5B80 (60 B) - constructor_camera_collision_data
 * Evidence: `jal <.text>+0xD5BC0` with `$s0 = $a0`, then `swc1 -1.0f -> 0x40($s0)` and
 * `swc1 1.0f -> 0x44($s0)`.
 * UNCONFIRMED: callee func_000D5BC0 (unnamed static, .text reloc) and the field meanings
 
 */
void func_000D5BC0(void *p);

void constructor_camera_collision_data(void *p) {
    func_000D5BC0(p);
    *(float *)((char *)p + 0x40) = -1.0f;
    *(float *)((char *)p + 0x44) = 1.0f;
}
