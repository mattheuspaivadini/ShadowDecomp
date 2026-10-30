/* GAMECORE.XFF @ 0x0E3018 (20 B) - is_camera_target_change
 * Evidence: ops lw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int is_camera_target_change(char *p) {
    return F(p, int, 0x1C) != F(p, int, 0x18);
}
