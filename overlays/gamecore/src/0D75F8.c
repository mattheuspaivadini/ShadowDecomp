/* GAMECORE.XFF @ 0x0D75F8 (16 B) - begin_time_interp_camera_dist_to_look_at
 * Evidence: ops sw swc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void begin_time_interp_camera_dist_to_look_at(char *p, float a, float b) {
    F(p, float, 0x78) = b;
    F(p, float, 0x70) = a;
    F(p, int, 0x74) = 0;
}
