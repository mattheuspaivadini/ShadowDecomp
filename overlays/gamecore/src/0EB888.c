/* GAMECORE.XFF @ 0x0EB888 (12 B) - setZoomKey
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x1e88.
 */
extern int D_kernel_data_1E88;

void setZoomKey(int a0) {
    D_kernel_data_1E88 = a0;
}
