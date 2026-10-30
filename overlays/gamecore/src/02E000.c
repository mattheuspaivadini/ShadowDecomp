/* GAMECORE.XFF @ 0x02E000 (12 B) - time_attack_get_boss_status
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x107c - returns that object as `int`.
 */
extern int D_kernel_data_107C;

int time_attack_get_boss_status(void) {
    return D_kernel_data_107C;
}
