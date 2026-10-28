/* GAMECORE.XFF @ 0x0D0FC0 (12 B) - SetMapLogDispMode
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x1acc.
 */
extern int D_kernel_data_1ACC;

void SetMapLogDispMode(int a0) {
    D_kernel_data_1ACC = a0;
}
