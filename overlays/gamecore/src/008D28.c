/* GAMECORE.XFF @ 0x008D28 (12 B) - GAMEUTIL_get_sight_on_angle_vel_ratio_int
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x228 - returns that object as `int`.
 */
extern int D_kernel_data_0228;

int GAMEUTIL_get_sight_on_angle_vel_ratio_int(void) {
    return D_kernel_data_0228;
}
