/* GAMECORE.XFF @ 0x0D7628 (28 B) - get_rewind_begin_dist_to_target_camera_dist_to_look_at
 * Evidence: lw field 0x30, xori 2 then branch; returns float field 0x38 or a0 float
 * UNCONFIRMED: field names/types guessed from offsets
 */
float get_rewind_begin_dist_to_target_camera_dist_to_look_at(char *p, float d) {
    float r = d;
    if ((*(int *)(p + 0x30) ^ 2) == 0)
        r = *(float *)(p + 0x38);
    return r;
}
