/* KERNEL.XFF @ 0x02DDF8 (188 B) - func_02DDF8 (static, no symbol in the shipped .symtab)
 * Evidence: 16-bit source (+0 + position +0x10) to the stereo float mix buffer: per 256-sample block, left = v * lvol / 100 and right (+0x100 floats) = v * rvol / 100, then both pointers skip the other half; position advances by n and resets to 0 at the length (+8). UNCONFIRMED: names.
 */
struct PcmMix {
    short *src;
    float *tbl;
    int num;
    int unkC;
    int pos;
};

void func_02DDF8(struct PcmMix *m, int n, int lvol, int rvol) {
    int pos = m->pos;
    float *l = m->tbl;
    float *r = l + 0x100;
    short *src = m->src + pos;
    int i;
    int j;
    int v;

    for (i = 0; i < n;) {
        for (j = 0; j < 256; j++) {
            v = src[i];
            i++;
            *l++ = v * lvol / 100;
            *r++ = v * rvol / 100;
        }
        l += 0x100;
        r += 0x100;
    }
    m->pos = pos + n;
    if (m->pos >= m->num) {
        m->pos = 0;
    }
}
