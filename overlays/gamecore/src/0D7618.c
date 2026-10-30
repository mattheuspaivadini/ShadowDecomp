/* GAMECORE.XFF @ 0x0D7618 (16 B) - is_acting_rewind_camera_dist_to_look_at
 * Evidence: ops lw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int is_acting_rewind_camera_dist_to_look_at(char *p) {
    return F(p, int, 0x30) == 2;
}
