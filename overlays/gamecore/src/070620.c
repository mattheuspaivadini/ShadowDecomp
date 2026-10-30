/* GAMECORE.XFF @ 0x070620 (12 B) - get_snipe_position_nico_sight_on
 * Evidence: lq [a1+0x1C0] -> sq [a0]
 * UNCONFIRMED: none
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
void get_snipe_position_nico_sight_on(u_long128 *out, char *src) {
    *out = *(u_long128 *)(src + 0x1C0);
}
