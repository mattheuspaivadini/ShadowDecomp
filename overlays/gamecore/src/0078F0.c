/* GAMECORE.XFF @ 0x0078F0 (12 B) - is_disp_debug_object_info
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x18) - returns the object address.
 */
extern char D_kernel_data_0018[];

int is_disp_debug_object_info(void) {
    return (int)D_kernel_data_0018;
}
