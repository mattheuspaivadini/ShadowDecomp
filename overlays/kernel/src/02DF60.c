/* KERNEL.XFF @ 0x02DF60 (204 B) - func_02DF60 (static, no symbol in the shipped .symtab)
 * Evidence: 16-bit source with block-interleaved channels (+0 + position +0x10) to the float mix buffer: per 0x200 samples, 256 left samples * lvol / 100 then 256 right samples * rvol / 100; position advances by n and resets at the length (+8). UNCONFIRMED: names.
 */
struct PcmMix {
    short *src;
    float *tbl;
    int num;
    int unkC;
    int pos;
};

void func_02DF60(struct PcmMix *m, int n, int lvol, int rvol) {
    int pos = m->pos;
    short *src = m->src + pos;
    float *d = m->tbl;
    int i;
    int j;

    for (i = 0; i < n; i += 0x200) {
        for (j = 0; j < 256; j++) {
            *d++ = *src++ * lvol / 100;
        }
        for (j = 0; j < 256; j++) {
            *d++ = *src++ * rvol / 100;
        }
    }
    m->pos = pos + n;
    if (m->pos >= m->num) {
        m->pos = 0;
    }
}
