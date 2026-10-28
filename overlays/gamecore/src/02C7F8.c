/* GAMECORE.XFF @ 0x02C7F8 (12 B) - stagemanager_GetStageAlignParam
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0xfb8 - returns that object as `int`.
 */
extern int D_kernel_data_0FB8;

int stagemanager_GetStageAlignParam(void) {
    return D_kernel_data_0FB8;
}
