/* GAMECORE.XFF @ 0x010968 (28 B) - SetCamFinalizerGeometry
 * Evidence: lq a0 -> sq gcGlobalVar+0x340; lq a1 -> sq +0x360
 * UNCONFIRMED: none
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern char gcGlobalVar[];

void SetCamFinalizerGeometry(u_long128 *a, u_long128 *b) {
    *(u_long128 *)(gcGlobalVar + 0x340) = *a;
    *(u_long128 *)(gcGlobalVar + 0x360) = *b;
}
