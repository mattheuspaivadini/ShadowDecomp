/* GAMECORE.XFF @ 0x0D55B0 (48 B) - get_camera_collision_data_base_filter_radius
 * Evidence: `c.lt.s $f13,$f14` + `bc1tl` with `mov.s $f13,$f14` in the delay slot,
 * `$f13 += 0.1f` (lui/ori 0x3DCCCCCC), `c.lt.s $f12,$f13` + `bc1tl` with
 * `mov.s $f12,$f13`, then `mov.s $f0,$f12`.
 * UNCONFIRMED: parameter meanings
 
 */
float get_camera_collision_data_base_filter_radius(float radius, float a, float b) {
    if (a < b) {
        a = b;
    }
    a = a + 0.1f;
    if (radius < a) {
        radius = a;
    }
    return radius;
}
