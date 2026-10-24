/* GAMECORE.XFF @ 0x0D95A0 (8 B) - get_hit_camera_region_camera_place_status
 * Evidence: `jr $ra` with `8c82000c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int get_hit_camera_region_camera_place_status(unsigned char *p) {
    return *(int *)(p + 0xc);
}
