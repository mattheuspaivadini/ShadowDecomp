/* GAMECORE.XFF @ 0x011C88 (12 B) - SetCaptionPauseFlag
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x73c.
 */
extern int D_kernel_data_073C;

void SetCaptionPauseFlag(int a0) {
    D_kernel_data_073C = a0;
}
