/* GAMECORE.XFF @ 0x0C8270 (12 B) - SetTimeAttackTimeFlag
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x1950.
 */
extern int D_kernel_data_1950;

void SetTimeAttackTimeFlag(int a0) {
    D_kernel_data_1950 = a0;
}
