/* GAMECORE.XFF @ 0x0E3618 (44 B) - change_main_cameraman
 * Evidence: `jal <.text>+0xE3688` with `$s0 = $a0`, `sw $s0 -> .bss+0x1C200`.
 * UNCONFIRMED: struct field meanings and callee argument/return types
 
 */
extern int D_kernel_bss_1C200;

void func_000E3688(int index);

void change_main_cameraman(int index) {
    func_000E3688(index);
    D_kernel_bss_1C200 = index;
}
