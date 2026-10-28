/* GAMECORE.XFF @ 0x01A090 (12 B) - gstatBootMcSetExistIcoData
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x9f0.
 */
extern int D_kernel_data_09F0;

void gstatBootMcSetExistIcoData(int a0) {
    D_kernel_data_09F0 = a0;
}
