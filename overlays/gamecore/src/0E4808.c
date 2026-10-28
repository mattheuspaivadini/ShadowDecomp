/* GAMECORE.XFF @ 0x0E4808 (12 B) - get_debug_camera_dist_to_look_at_pointer
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1e68) - returns the object address.
 */
extern char D_kernel_data_1E68[];

int get_debug_camera_dist_to_look_at_pointer(void) {
    return (int)D_kernel_data_1E68;
}
