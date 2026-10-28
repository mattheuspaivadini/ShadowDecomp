/* GAMECORE.XFF @ 0x010958 (12 B) - PauseCamFinalizer
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x730.
 */
extern int D_kernel_data_0730;

void PauseCamFinalizer(int a0) {
    D_kernel_data_0730 = a0;
}
