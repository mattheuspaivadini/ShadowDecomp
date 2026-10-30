/* GAMECORE.XFF @ 0x0104F0 (12 B) - bossStatGetDeadBoss
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x6e8 - returns that object as `int`.
 */
extern int D_kernel_data_06E8;

int bossStatGetDeadBoss(void) {
    return D_kernel_data_06E8;
}
