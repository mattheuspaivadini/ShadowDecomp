/* GAMECORE.XFF @ 0x0E47E8 (12 B) - is_disp_game_camera_model_ok
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x1e64 - returns that object as `int`.
 */
extern int D_kernel_data_1E64;

int is_disp_game_camera_model_ok(void) {
    return D_kernel_data_1E64;
}
