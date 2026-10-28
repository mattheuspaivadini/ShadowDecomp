/* GAMECORE.XFF @ 0x0CD4A8 (12 B) - getSelectWeapon
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x1a80 - returns that object as `int`.
 */
extern int D_kernel_data_1A80;

int getSelectWeapon(void) {
    return D_kernel_data_1A80;
}
