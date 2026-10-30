/* GAMECORE.XFF @ 0x099B38 (20 B) - AI_SetAnimalLayout
 * Evidence: ops lq sq swc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
typedef unsigned int u_long128 __attribute__((mode(TI)));

void AI_SetAnimalLayout(char *p, u_long128 *v, float a, float b) {
    F(p, float, 0x14) = b;
    F(p, float, 0x10) = a;
    *(u_long128 *)p = *v;
}
