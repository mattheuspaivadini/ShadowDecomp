/* GAMECORE.XFF @ 0x00C358 (12 B) - setLayerFade
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x664.
 */
extern int D_kernel_data_0664;

void setLayerFade(int a0) {
    D_kernel_data_0664 = a0;
}
