/* GAMECORE.XFF @ 0x0E02D8 (32 B) - CAM_set_all_camera_base_data
 * Evidence: two lq/sq vector copies (a1->a0, a2->a0+0x10) and float stores at 0x20/0x24/0x28 from f12/f13/f14
 * UNCONFIRMED: types guessed; empty asm pin of first vector temp is a compiler artifact
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
void CAM_set_all_camera_base_data(char *p, u_long128 *a, u_long128 *b, float x, float y, float z) {
    u_long128 ta, tb;
    ta = *a;
    *(u_long128 *)p = ta;
    tb = *b;
    asm volatile("" : : "r"(ta));
    *(u_long128 *)(p + 0x10) = tb;
    *(float *)(p + 0x20) = x;
    *(float *)(p + 0x24) = y;
    *(float *)(p + 0x28) = z;
}
