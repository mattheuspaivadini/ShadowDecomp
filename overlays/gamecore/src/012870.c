/* GAMECORE.XFF @ 0x012870 (12 B) - SetDefaultStageLoad
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x74c.
 */
extern int D_kernel_data_074C;

void SetDefaultStageLoad(int a0) {
    D_kernel_data_074C = a0;
}
