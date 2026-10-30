/* GAMECORE.XFF @ 0x1036F0 (12 B) - getLandMotionOffset
 * Evidence: ops lq sq
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
typedef unsigned int u_long128 __attribute__((mode(TI)));

void getLandMotionOffset(char *p, u_long128 *out) {
    *out = F(p, u_long128, 0xF0);
}
