/* KERNEL.XFF @ 0x02FBD8 (296 B) - func_02FBD8 (static, no symbol in the shipped .symtab)
 * Evidence: RBJ peaking EQ sibling: A = powf(10, gain (+0x2C) / 40); b0/b2 = 1 +/- alpha * A, a0/a2 = 1 +/- alpha / A, b1 = a1 = -2 cosf(w). UNCONFIRMED: names.
 */
struct Biquad {
    float unk0;
    float a0;
    float a1;
    float a2;
    float b0;
    float b1;
    float b2;
    char pad1C[0x10];
    float gain;
    float freq;
};
float sinf(float x);
float cosf(float x);
float powf(float x, float y);

void func_02FBD8(struct Biquad *f) {
    float A;
    float w;
    float alpha;

    A = powf(10.0f, f->gain / 40.0f);
    w = f->freq / 48000.0f * 2.0f * 3.1415926f;
    alpha = sinf(w) / 6.0f;
    f->b0 = 1.0f + alpha * A;
    f->b1 = -2.0f * cosf(w);
    f->b2 = 1.0f - alpha * A;
    f->a0 = 1.0f + alpha / A;
    f->a1 = -2.0f * cosf(w);
    f->a2 = 1.0f - alpha / A;
}
