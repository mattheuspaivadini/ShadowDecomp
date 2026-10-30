/* GAMECORE.XFF @ 0x0ADE60 (20 B) - Kite_SetPathOfs
 * Evidence: ops lq sq
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
typedef unsigned int u_long128 __attribute__((mode(TI)));

void Kite_SetPathOfs(char *p, u_long128 *v) {
    F(p, u_long128, 0xD0) = *v;
    F(p, u_long128, 0x1A0) = *v;
}
