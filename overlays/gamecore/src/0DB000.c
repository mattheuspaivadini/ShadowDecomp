/* GAMECORE.XFF @ 0x0DB000 (12 B) - is_exist_camera_target_lost_angle
 * Evidence: ops lw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int is_exist_camera_target_lost_angle(char *p) {
    return F(p, int, 0) != 0;
}
