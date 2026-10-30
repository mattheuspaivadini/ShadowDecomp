/* GAMECORE.XFF @ 0x0D8C08 (12 B) - is_end_camera_pause_rise
 * Evidence: ops lw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int is_end_camera_pause_rise(char *p) {
    return F(p, int, 0) == 0;
}
