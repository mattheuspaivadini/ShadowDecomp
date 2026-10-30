/* GAMECORE.XFF @ 0x009CC0 (12 B) - GAMEUTIL_set_auto_get_flag_boss_interest_position
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x238.
 */
extern int D_kernel_data_0238;

void GAMEUTIL_set_auto_get_flag_boss_interest_position(int a0) {
    D_kernel_data_0238 = a0;
}
