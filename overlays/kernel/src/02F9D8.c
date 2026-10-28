/* KERNEL.XFF @ 0x02F9D8 (252 B) - func_02F9D8 (static, no symbol in the shipped .symtab)
 * Evidence: RBJ low-pass biquad for the EQ record: w = freq (+0x30) / 48000 * 2 * pi, alpha = sinf(w) / 6 (Q 3); b0 = b2 = (1 - cosf(w)) / 2 (+0x10/+0x18), b1 = 1 - cosf(w) (+0x14), a0 = 1 + alpha (+4), a1 = -2 cosf(w) (+8), a2 = 1 - alpha (+0xC); cosf re-called for every coefficient. Body is 0xFC bytes (one nop of padding follows). UNCONFIRMED: names.
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

void func_02F9D8(struct Biquad *f) {
    float w;
    float alpha;

    w = f->freq / 48000.0f * 2.0f * 3.1415926f;
    alpha = sinf(w) / 6.0f;
    f->b0 = (1.0f - cosf(w)) * 0.5f;
    f->b1 = 1.0f - cosf(w);
    f->b2 = (1.0f - cosf(w)) * 0.5f;
    f->a0 = 1.0f + alpha;
    f->a1 = -2.0f * cosf(w);
    f->a2 = 1.0f - alpha;
}
