/* GAMECORE.XFF @ 0x07BC10 (12 B) - player_IsHorseCtrlOff
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x15dc - returns that object as `int`.
 */
extern int D_kernel_data_15DC;

int player_IsHorseCtrlOff(void) {
    return D_kernel_data_15DC;
}
