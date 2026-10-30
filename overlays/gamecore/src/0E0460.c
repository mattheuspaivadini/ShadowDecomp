/* GAMECORE.XFF @ 0x0E0460 (44 B) - CAM_is_inside_of_region_aim_angle_rot
 * Evidence: `lw [a2]` + `bnez` selecting the two tail calls
 * GAMEUTIL_is_inside_of_region_yaw / _pitch.
 * UNCONFIRMED: struct field meanings and callee argument/return types
 
 */
int GAMEUTIL_is_inside_of_region_yaw(void *a, void *b, int *c);
int GAMEUTIL_is_inside_of_region_pitch(void *a, void *b, int *c);

int CAM_is_inside_of_region_aim_angle_rot(void *a, void *b, int *c) {
    if (*c == 0)
        return GAMEUTIL_is_inside_of_region_yaw(a, b, c);
    return GAMEUTIL_is_inside_of_region_pitch(a, b, c);
}
