/* GAMECORE.XFF @ 0x070630 (16 B) - get_predict_hit_position_nico_sight_on
 * Evidence: lq [a1+0x1D0] -> sq [a0]; return [a1+0x1E0]
 * UNCONFIRMED: none
 * (needs -fno-strict-aliasing: keeps the lw after the sq)
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

int get_predict_hit_position_nico_sight_on(u_long128 *out, char *src) {
    *out = *(u_long128 *)(src + 0x1D0);
    return *(int *)(src + 0x1E0);
}
