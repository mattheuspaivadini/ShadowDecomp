/* GAMECORE.XFF @ 0x0D8BF8 (16 B) - request_end_camera_pause_rise
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void request_end_camera_pause_rise(char *p) {
    F(p, int, 4) = 0;
    F(p, int, 0) = 2;
}
