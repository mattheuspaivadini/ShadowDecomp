/* KERNEL.XFF @ 0x02DEB8 (164 B) - func_02DEB8 (static, no symbol in the shipped .symtab)
 * Evidence: as func_02DDF8 for a looping source: the read position (+0x10) wraps to loop once it passes end (5th/6th arguments) and is written back. UNCONFIRMED: names, argument meaning.
 */
struct PcmMix {
    short *src;
    float *tbl;
    int num;
    int unkC;
    int pos;
};

void func_02DEB8(struct PcmMix *m, int n, int lvol, int rvol, int loop, int end) {
    float *l = m->tbl;
    float *r = l + 0x100;
    short *src = m->src;
    int pos = m->pos;
    int i;
    int j;
    int v;

    for (i = 0; i < n; i += 256) {
        for (j = 0; j < 256; j++) {
            v = src[pos];
            pos++;
            if (pos > end) {
                pos = loop;
            }
            *l++ = v * lvol / 100;
            *r++ = v * rvol / 100;
        }
        l += 0x100;
        r += 0x100;
    }
    m->pos = pos;
}
