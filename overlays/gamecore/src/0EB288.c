/* GAMECORE.XFF @ 0x0EB288 (12 B) - get_look_lws_anime_camera_flag
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x1e74) - returns the object address.
 */
extern char D_kernel_data_1E74[];

int get_look_lws_anime_camera_flag(void) {
    return (int)D_kernel_data_1E74;
}
