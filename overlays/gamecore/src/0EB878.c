/* GAMECORE.XFF @ 0x0EB878 (12 B) - setInterestKey
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x1e84.
 */
extern int D_kernel_data_1E84;

void setInterestKey(int a0) {
    D_kernel_data_1E84 = a0;
}
