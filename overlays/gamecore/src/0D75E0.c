/* GAMECORE.XFF @ 0x0D75E0 (24 B) - reset_time_interp_param_camera_dist_to_look_at
 * Evidence: ops sw swc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void reset_time_interp_param_camera_dist_to_look_at(char *p) {
    F(p, int, 0x74) = 0;
    F(p, float, 0x78) = 1.0f;
    F(p, int, 0x70) = 0;
}
