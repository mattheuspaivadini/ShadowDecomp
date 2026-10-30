/* GAMECORE.XFF @ 0x0E47D8 (12 B) - get_debug_camera_view_angle_pointer
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1e60) - returns the object address.
 */
extern char D_kernel_data_1E60[];

int get_debug_camera_view_angle_pointer(void) {
    return (int)D_kernel_data_1E60;
}
