/* KERNEL.XFF @ 0x00D660 (176 B) - iosIColScale
 * Evidence: the packed colour argument is unpacked into four int slots at
 * sp+0..0xC with `srl`+`andi` (0, 8, 16, 24), the float scale is multiplied by
 * 4096.0f (lui 0x4580 -> $f0, mul.s) and truncated once (cvt.w.s/mfc1) into
 * three slots at sp+0x10..0x18 - a reverse chained assignment
 * `s[2] = s[1] = s[0] = (int)(scale * 4096.0f)` is what reproduces the shipped
 * store order (0x18 last-assigned first emitted). iosMulMvec(00D510) is then
 * called with d = a = sp and b = sp+0x10, the product is shifted right 12 with
 * `lq/psrlw/sq` on the same quad and iosSwClip255Mvec(00D740) clamps it in
 * place. The four output bytes are the clamped bytes 0/1/2 plus a literal -1 in
 * byte 3 (`li v0,-1; sb`). c[3] is written after the scale block, which is why
 * its `sw 0xc(sp)` interleaves with the scale stores in the image.
 * Verified byte-exact with -G0 and -G0 -fno-strict-aliasing.
 * UNCONFIRMED: parameter names; the callee prototypes (inferred from 00D510 /
 * 00D740 in this lane).
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef union { long long l[2]; u_long128 q; } MV;

void iosMulMvec(u_long128 *d, MV *a, MV *b);
void iosSwClip255Mvec(u_long128 *d);

void iosIColScale(unsigned char *dst, unsigned int col, float scale) {
    int c[4];
    int s[4];
    u_long128 t;

    c[0] = col & 0xFF;
    c[1] = (col >> 8) & 0xFF;
    c[2] = (col >> 16) & 0xFF;
    s[2] = s[1] = s[0] = (int)(scale * 4096.0f);
    c[3] = col >> 24;
    iosMulMvec((u_long128 *)c, (MV *)c, (MV *)s);
    t = *(u_long128 *)c;
    __asm__ __volatile__("psrlw %0, %0, 12" : "+r"(t));
    *(u_long128 *)c = t;
    iosSwClip255Mvec((u_long128 *)c);
    dst[0] = ((unsigned char *)c)[0];
    dst[1] = ((unsigned char *)c)[4];
    dst[2] = ((unsigned char *)c)[8];
    dst[3] = -1;
}
