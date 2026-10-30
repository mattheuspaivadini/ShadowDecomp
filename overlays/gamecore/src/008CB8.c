/* GAMECORE.XFF @ 0x008CB8 (12 B) - GAMEUTIL_set_sight_on_reverse_cntrlLR
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x220.
 */
extern int D_kernel_data_0220;

void GAMEUTIL_set_sight_on_reverse_cntrlLR(int a0) {
    D_kernel_data_0220 = a0;
}
