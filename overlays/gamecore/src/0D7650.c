/* GAMECORE.XFF @ 0x0D7650 (20 B) - is_leave_camera_dist_to_look_at
 * Evidence: ops lw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int is_leave_camera_dist_to_look_at(char *p) {
    return F(F(p, char *, 0), int, 0x140) == 2;
}
