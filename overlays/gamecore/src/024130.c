/* GAMECORE.XFF @ 0x024130 (12 B) - SetSeamlessStageControlObject
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0xab4.
 */
extern int D_kernel_data_0AB4;

void SetSeamlessStageControlObject(int a0) {
    D_kernel_data_0AB4 = a0;
}
