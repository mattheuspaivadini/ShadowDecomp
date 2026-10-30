/* GAMECORE.XFF @ 0x0EB868 (12 B) - setBossInterestKey
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x1e7c.
 */
extern int D_kernel_data_1E7C;

void setBossInterestKey(int a0) {
    D_kernel_data_1E7C = a0;
}
