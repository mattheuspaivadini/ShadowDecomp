/* GAMECORE.XFF @ 0x0D9650 (20 B) - get_on_boss_camera_col_attr_camera_place_status
 * Evidence: same as 0d9638 with a1+0x150
 * UNCONFIRMED: same
 */
int get_on_boss_camera_col_attr_camera_place_status(long *out, char *p) {
    char *q = p + 0x150;
    asm("" : "+r"(q));
    *out = *(long *)(q + 0x10);
    return *(int *)(q + 8);
}
