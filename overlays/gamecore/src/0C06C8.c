/* GAMECORE.XFF @ 0x0C06C8 (12 B) - setPlayerStatusSwitch
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x1738.
 */
extern int D_kernel_data_1738;

void setPlayerStatusSwitch(int a0) {
    D_kernel_data_1738 = a0;
}
