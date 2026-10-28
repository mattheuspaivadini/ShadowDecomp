/* KERNEL.XFF @ 0x02E118 (92 B) - func_02E118 (static, no symbol in the shipped .symtab)
 * Evidence: mono fold of the float mix buffer: b[i] and b[i + 0x100] both become (b[i] + b[i + 0x100]) * 0.5 for n samples, skipping the second half of every 0x200 block (i += 0x100 when bit 8 sets). UNCONFIRMED: name.
 */
struct PcmMix {
    int num;
    float *tbl;
};

void func_02E118(struct PcmMix *m, int n) {
    float *b = m->tbl;
    int i;

    for (i = 0; i < n;) {
        b[i] = b[i + 0x100] = (b[i] + b[i + 0x100]) * 0.5f;
        i++;
        if (i & 0x100) {
            i += 0x100;
        }
    }
}
