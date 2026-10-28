/* GAMECORE.XFF @ 0x02CE98 (12 B) - initWorldLayout
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0xfd4.
 */
extern int D_kernel_data_0FD4;

void initWorldLayout(int a0) {
    D_kernel_data_0FD4 = a0;
}
