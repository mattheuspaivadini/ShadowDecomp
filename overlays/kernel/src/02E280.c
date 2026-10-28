/* KERNEL.XFF @ 0x02E280 (56 B) - func_02E280 (static, no symbol in the shipped .symtab)
 * Evidence: adds n floats of the input voice buffer (+4) into the mix buffer (+4). UNCONFIRMED: names.
 */
struct PcmMix {
    int num;
    float *tbl;
};
struct PcmInputVoice {
    int unk0;
    float *buf;
};

void func_02E280(struct PcmMix *m, struct PcmInputVoice *v, int n) {
    float *d = m->tbl;
    float *s = v->buf;
    int i;

    for (i = 0; i < n; i++) {
        *d++ += *s++;
    }
}
