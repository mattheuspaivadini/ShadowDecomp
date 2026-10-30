/* GAMECORE.XFF @ 0x064B20 (12 B) - inInNowLoadingEffect
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x1320 - returns that object as `int`.
 */
extern int D_kernel_data_1320;

int inInNowLoadingEffect(void) {
    return D_kernel_data_1320;
}
