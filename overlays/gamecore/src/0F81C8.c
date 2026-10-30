/* GAMECORE.XFF @ 0x0F81C8 (28 B) - setAttainRangeData
 * Evidence: ops lq sq swc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
typedef unsigned int u_long128 __attribute__((mode(TI)));

void setAttainRangeData(char *p, u_long128 *v, float a, float b, float c, float d) {
    F(p, u_long128, 0x3E0) = *v;
    F(p, float, 0x3F0) = a;
    F(p, float, 0x3F4) = b;
    F(p, float, 0x3F8) = c;
    F(p, float, 0x3FC) = d;
}
