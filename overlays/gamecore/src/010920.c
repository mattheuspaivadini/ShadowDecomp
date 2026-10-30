/* GAMECORE.XFF @ 0x010920 (12 B) - SetCamFinalizerReady
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x6f0.
 */
extern int D_kernel_data_06F0;

void SetCamFinalizerReady(int a0) {
    D_kernel_data_06F0 = a0;
}
