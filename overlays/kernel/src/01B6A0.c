/* KERNEL.XFF @ 0x01B6A0 (12 B) - iosSetIVSyncMode
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x7e0.
 */
extern int D_kernel_data_07E0;

void iosSetIVSyncMode(int a0) {
    D_kernel_data_07E0 = a0;
}
