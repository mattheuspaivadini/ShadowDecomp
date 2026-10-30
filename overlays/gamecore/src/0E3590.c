/* GAMECORE.XFF @ 0x0E3590 (52 B) - get_cameraman_camera_obj
 * Evidence: `jal <.text>+0xE3688`, `lw [0x1C208 + index*4]`, tail `j get_camera_obj`.
 * UNCONFIRMED: struct field meanings and callee argument/return types
 
 */
extern char D_kernel_bss_1C208[];

void func_000E3688(int index);
void *get_camera_obj(void *p);

void *get_cameraman_camera_obj(int index) {
    func_000E3688(index);
    return get_camera_obj(*(void **)(D_kernel_bss_1C208 + index * 4));
}
