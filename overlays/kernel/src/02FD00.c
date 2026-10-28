/* KERNEL.XFF @ 0x02FD00 (452 B) - func_02FD00 (static, no symbol in the shipped .symtab)
 * Evidence: RBJ low-shelf biquad for the EQ record (IirParam case 2): A =
 * powf(10, gain (+0x2C) / 40), w = freq (+0x30) / 48000 * 2 * pi, q = sqrt(2A)
 * spelled as A*A + 1 - (A-1)*(A-1) through the double sqrt (fptodp/sqrt/dptofp);
 * b0/b2 (+0x10/+0x18) = A * ((A+1) - (A-1)cos w -/+ q sin w), b1 (+0x14) =
 * 2A * ((A-1) - (A+1)cos w), a0 (+0x04) = (A+1) + (A-1)cos w + q sin w, a1 (+0x08)
 * = -2 * ((A-1) + (A+1)cos w), a2 (+0x0C) = (A+1) + (A-1)cos w - q sin w; cosf
 * and sinf are re-called for every coefficient (7 cosf + 3 sinf). UNCONFIRMED:
 * name, field names.
 */
typedef struct IirParam_s {
    int type;        /* 0x00 */
    float f04;       /* 0x04 */
    float f08;       /* 0x08 */
    float f0C;       /* 0x0C */
    float f10;       /* 0x10 */
    float f14;       /* 0x14 */
    float f18;       /* 0x18 */
    int pad[4];      /* 0x1C .. 0x2B */
    float f2C;       /* 0x2C */
    float f30;       /* 0x30 */
    float f34;
    float f38;
    float f3C;
    float f40;
    float f44;
} IirParam_s;
float powf(float x, float y);
float sinf(float x);
float cosf(float x);
double sqrt(double x);

void func_02FD00(IirParam_s *p) {
    float A;
    float w;
    float q;

    A = powf(10.0f, p->f2C / 40.0f);
    w = p->f30 / 48000.0f * 2.0f * 3.1415926f;
    q = sqrt(A * A + 1.0f - (A - 1.0f) * (A - 1.0f));
    p->f10 = A * ((A + 1.0f) - (A - 1.0f) * cosf(w) + q * sinf(w));
    p->f14 = 2.0f * A * ((A - 1.0f) - (A + 1.0f) * cosf(w));
    p->f18 = A * ((A + 1.0f) - (A - 1.0f) * cosf(w) - q * sinf(w));
    p->f04 = (A + 1.0f) + (A - 1.0f) * cosf(w) + q * sinf(w);
    p->f08 = -2.0f * ((A - 1.0f) + (A + 1.0f) * cosf(w));
    p->f0C = (A + 1.0f) + (A - 1.0f) * cosf(w) - q * sinf(w);
}
