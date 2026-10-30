/* GAMECORE.XFF @ 0x0D9638 (20 B) - get_cam_region_col_attr_camera_place_status
 * Evidence: addiu a1+0xD0 kept, ld 0x10 -> sd (a0), lw 8; needs -fno-schedule-insns
 * UNCONFIRMED: pointer pinned with empty asm; types of fields (long/int) guessed
 */
int get_cam_region_col_attr_camera_place_status(long *out, char *p) {
    char *q = p + 0xD0;
    asm("" : "+r"(q));
    *out = *(long *)(q + 0x10);
    return *(int *)(q + 8);
}
