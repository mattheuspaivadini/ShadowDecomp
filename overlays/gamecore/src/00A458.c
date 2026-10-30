/* GAMECORE.XFF @ 0x00A458 (56 B) - GAMEUTIL_set_data_by_point_collision_info
 * Evidence: frame 0x40 with `$s0` at 0x30 and `$ra` at 0x38, `$a0 = $sp` for
 * `jal ConvertFromCollisionPointToDynamics`, then `func_00A490(arg, $sp, 0)`.
 * UNCONFIRMED: the local buffer layout and the callee prototypes.
 
 */
void ConvertFromCollisionPointToDynamics(void *out);
void func_00A490(void *arg, void *data, int index);

void GAMEUTIL_set_data_by_point_collision_info(void *arg) {
    char data[0x30];

    ConvertFromCollisionPointToDynamics(data);
    func_00A490(arg, data, 0);
}
