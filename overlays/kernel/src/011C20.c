/* KERNEL.XFF @ 0x011C20 (280 B) - InitTableSinCos
 * Evidence: one-shot initialiser guarded by .data+0x444 (set to 1 at the end):
 * fills 0x4001 floats at .bss+0xE6C0 (the quarter-turn cos table that
 * iosGetTableSin (0x011B88) and iosGetTableCos (0x011BD8) index with the same
 * `-0x1940` addend, 0x4000 entries per quarter turn).  i walks 0..0x4000,
 * f = i * 2^-14 (`lui $at,0x3880`), and the branch `0.5 < f`
 * (`c.lt.s $f22,$f0` with 0x3F000000) selects either
 * sqrtf(1 - sinf(f*pi/2)^2) (pi/2 = 0x3FC90FDA, built `lui 0x3FC9`/`ori 0xFDA`)
 * or cosf(f*pi/2).  GCC expands sqrtf as `sqrt.s` + `c.eq.s $f1,$f1` +
 * `bc1t` + a sqrtf libcall fallback, which is what ships.
 * LEVER: the step literal must be spelled 0.00006103515625f - this compiler
 * truncates decimal float literals, so 0.000061035156f becomes 0x387FFFFF and
 * costs an extra `lui/ori`.
 * LEVER: the array form `D[i]` in both arms is required; it makes loop.c
 * strength-reduce two separate induction pointers (s1/s2 from the same base,
 * both +4 per iteration), where a single `float *p` gives 264 B.
 * UNCONFIRMED: table/flag names, the reason the table is shared with sin/cos.
 */
extern int D_kernel_data_444;
extern float D_kernel_bss_E6C0[];
float sinf(float);
float cosf(float);
float sqrtf(float);

void InitTableSinCos(void) {
    int i;
    float f;
    float s;

    if (D_kernel_data_444 != 0)
        return;
    for (i = 0; i < 0x4001; i++) {
        f = (float)i * 0.00006103515625f;
        if (f > 0.5f) {
            s = sinf(f * 1.5707963f);
            D_kernel_bss_E6C0[i] = sqrtf(1.0f - s * s);
        } else {
            D_kernel_bss_E6C0[i] = cosf(f * 1.5707963f);
        }
    }
    D_kernel_data_444 = 1;
}
