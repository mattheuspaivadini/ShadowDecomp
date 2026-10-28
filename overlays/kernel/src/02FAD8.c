/* KERNEL.XFF @ 0x02FAD8 (256 B) - func_02FAD8 (static, no symbol in the shipped .symtab)
 * Evidence: RBJ high-pass sibling of the static at .text+0x2F9D8: b0 = b2 = (1 + cosf(w)) / 2, b1 = -(1 + cosf(w)), same a0/a1/a2. UNCONFIRMED: names.
 */
struct Biquad {
    float unk0;
    float a0;
    float a1;
    float a2;
    float b0;
    float b1;
    float b2;
    char pad1C[0x14];
    float freq;
};
float sinf(float x);
float cosf(float x);

void func_02FAD8(struct Biquad *f) {
    float w;
    float alpha;

    w = f->freq / 48000.0f * 2.0f * 3.1415926f;
    alpha = sinf(w) / 6.0f;
    f->b0 = (cosf(w) + 1.0f) * 0.5f;
    f->b1 = -(cosf(w) + 1.0f);
    f->b2 = (cosf(w) + 1.0f) * 0.5f;
    f->a0 = 1.0f + alpha;
    f->a1 = -2.0f * cosf(w);
    f->a2 = 1.0f - alpha;
}
