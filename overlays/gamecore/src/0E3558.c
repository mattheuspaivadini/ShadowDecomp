/* GAMECORE.XFF @ 0x0E3558 (52 B) - get_cameraman
 * Evidence: `jal <.text>+0xE3688` with `$s0 = $a0`, then `lw [0x1C208 + index*4]`.
 * UNCONFIRMED: struct field meanings and callee argument/return types
 
 */
extern char D_kernel_bss_1C208[];

void func_000E3688(int index);

void *get_cameraman(int index) {
    func_000E3688(index);
    return *(void **)(D_kernel_bss_1C208 + index * 4);
}
