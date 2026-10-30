/* GAMECORE.XFF @ 0x05BFA8 (12 B) - getHorseStandByMode
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x1318 - returns that object as `int`.
 */
extern int D_kernel_data_1318;

int getHorseStandByMode(void) {
    return D_kernel_data_1318;
}
