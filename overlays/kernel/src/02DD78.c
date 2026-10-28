/* KERNEL.XFF @ 0x02DD78 (128 B) - func_02DD78 (static, no symbol in the shipped .symtab)
 * Evidence: float mix buffer (+4) to 16-bit output (+0 + position +0x10) for n samples, clamped to [-32768, 32767] before cvt.w.s. UNCONFIRMED: names.
 */
struct PcmMix {
    short *out;
    float *tbl;
    char pad8[8];
    int pos;
};

void func_02DD78(struct PcmMix *m, int n) {
    short *d = m->out + m->pos;
    float *s = m->tbl;
    float f;
    int i;

    for (i = 0; i < n; i++) {
        f = *s++;
        if (f > 32767.0f) {
            f = 32767.0f;
        }
        if (f < -32768.0f) {
            f = -32768.0f;
        }
        *d++ = (int)f;
    }
}
