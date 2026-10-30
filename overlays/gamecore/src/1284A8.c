/* GAMECORE.XFF @ 0x1284A8 (48 B) - ReflectIK_initWormDynamics
 * Evidence: stores $v0, 0x10($a0), $v0, 0x20($a0), $v1, 0x0($a0), $f12, 0x40($a0), $v0, 0x30($a0); loads $v0, 0x0($a1), $v0, 0x0($v1), $v1, 0x0($a2), $v0, 0x0($a3); relocs ZeroVector
 
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern char ZeroVector[];

void ReflectIK_initWormDynamics(char *p, u_long128 *a, u_long128 *b,
                                u_long128 *c, float f) {
    *(u_long128 *)(p + 0x10) = *a;
    *(u_long128 *)(p + 0x20) = *(u_long128 *)ZeroVector;
    *(u_long128 *)(p + 0x00) = *b;
    *(u_long128 *)(p + 0x30) = *c;
    *(float *)(p + 0x40) = f;
}
