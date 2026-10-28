/* GAMECORE.XFF @ 0x0E47F8 (12 B) - is_disp_game_camera_model_ok_pointer
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1e64) - returns the object address.
 */
extern char D_kernel_data_1E64[];

int is_disp_game_camera_model_ok_pointer(void) {
    return (int)D_kernel_data_1E64;
}
