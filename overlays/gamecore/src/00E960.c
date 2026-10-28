/* GAMECORE.XFF @ 0x00E960 (12 B) - getActivedemoStage
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x6d8 - returns that object as `int`.
 */
extern int D_kernel_data_06D8;

int getActivedemoStage(void) {
    return D_kernel_data_06D8;
}
