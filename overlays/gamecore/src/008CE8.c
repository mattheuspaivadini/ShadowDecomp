/* GAMECORE.XFF @ 0x008CE8 (12 B) - GAMEUTIL_set_sight_on_reverse_cntrlUD
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x224.
 */
extern int D_kernel_data_0224;

void GAMEUTIL_set_sight_on_reverse_cntrlUD(int a0) {
    D_kernel_data_0224 = a0;
}
