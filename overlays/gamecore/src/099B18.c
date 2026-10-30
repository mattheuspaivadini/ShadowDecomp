/* GAMECORE.XFF @ 0x099B18 (28 B) - AI_InitAnimalLayout
 * Evidence: lq from ZeroVector, sq to a0, zero words at 0x10/0x14.
 * UNCONFIRMED: field meaning
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern u_long128 ZeroVector;
void AI_InitAnimalLayout(char *p) {
    *(u_long128 *)p = ZeroVector;
    *(int *)(p + 0x10) = 0;
    *(int *)(p + 0x14) = 0;
}
