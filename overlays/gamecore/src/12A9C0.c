/* GAMECORE.XFF @ 0x12A9C0 (20 B) - setWormIKAttainXVector
 * Evidence: li 1 -> sw 0xA00, lq (a1) -> sq 0xA10
 * UNCONFIRMED: constant 1 pinned live across an empty asm to get the original lq-after-sw order and v1 allocation (compiler artifact)
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
void setWormIKAttainXVector(char *p, u_long128 *v) {
    int one = 1;
    *(int *)(p + 0xA00) = one;
    asm volatile("" : : "r"(one));
    *(u_long128 *)(p + 0xA10) = *v;
}
