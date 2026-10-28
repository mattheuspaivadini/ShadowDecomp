/* GAMECORE.XFF @ 0x07B4F8 (12 B) - player_AutoHorseCtrlOff
 * Shape `store-arg` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `sw $a0,lo(...)` + `jr $ra` - writes the argument to .data+0x15dc.
 */
extern int D_kernel_data_15DC;

void player_AutoHorseCtrlOff(int a0) {
    D_kernel_data_15DC = a0;
}
