/* GAMECORE.XFF @ 0x00A380 (28 B) - GAMEUTIL_reset_position_filter
 * Evidence: two lq from a1 copied to +0 and +0x10, sw 1 -> +0x20
 * UNCONFIRMED: none
 * (needs -fno-strict-aliasing so the second lq is reloaded after the flag store)
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

void GAMEUTIL_reset_position_filter(u_long128 *p, u_long128 *q) {
    p[0] = *q;
    p[1] = *q;
    *(int *)(p + 2) = 1;
}
