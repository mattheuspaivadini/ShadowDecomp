/* GAMECORE.XFF @ 0x0247A0 (12 B) - isSeamlessStage
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0xa90 - returns that object as `int`.
 */
extern int D_kernel_data_0A90;

int isSeamlessStage(void) {
    return D_kernel_data_0A90;
}
