/* GAMECORE.XFF @ 0x0D7B58 (40 B) - constructor_camera_etc_condition
 * Evidence: `jal <.text>+0xD7C68` with `$s0 = $a0`, then `sw $zero -> 0x8($s0)`.
 * UNCONFIRMED: callee func_000D7C68 (unnamed static, .text reloc)
 
 */
void func_000D7C68(void *p);

void constructor_camera_etc_condition(void *p) {
    func_000D7C68(p);
    *(int *)((char *)p + 8) = 0;
}
