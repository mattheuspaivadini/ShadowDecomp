/* GAMECORE.XFF @ 0x0E3648 (12 B) - get_main_cameraman_id
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .bss+0x2c200 - returns that object as `int`.
 */
extern int D_kernel_bss_2C200;

int get_main_cameraman_id(void) {
    return D_kernel_bss_2C200;
}
