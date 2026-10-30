/* GAMECORE.XFF @ 0x0ADE10 (60 B) - Kite_SetAnimalLayout
 * Evidence: build/s79/b/dis_all.txt (authority).
 * bc1t at 0xade24 is the non-likely form, so its delay slot (b = y - z) runs
 * unconditionally: the first branch only guards `a = x`. `z` is reused for
 * `b` (the image keeps it in $f14). Built with -O1 -fschedule-insns: -O2
 * global-allocates the 0.0f pseudo into $f2 and emits a single mtc1, while
 * the image rematerialises it into $f0 in both blocks.
 * FLAGS: -G0 -O1 -fschedule-insns
 
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

void Kite_SetAnimalLayout(char *p, char *q, float x, float y, float z) {
    float a = x - z;
    z = y - z;
    *(u_long128 *)p = *(u_long128 *)q;
    if (a > 0.0f) ; else a = x;
    if (z > 0.0f) ; else z = y;
    *(float *)(p + 0x10) = a;
    *(float *)(p + 0x14) = z;
}
