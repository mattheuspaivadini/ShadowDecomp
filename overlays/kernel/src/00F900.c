/* KERNEL.XFF @ 0x00F900 (52 B) - GetQuaternionFromMatrix
 * Evidence: 0x40-byte stack matrix: iosTransposeMatrix(tmp, m) then the stripped
 * static at .text+0xDCF8 (q, tmp), q kept in $s0. UNCONFIRMED: func_00DCF8's
 * prototype.
 */
void iosTransposeMatrix(float *d, float *s);
void func_00DCF8(float *q, float *m);

void GetQuaternionFromMatrix(float *q, float *m) {
    float t[16];

    iosTransposeMatrix(t, m);
    func_00DCF8(q, t);
}
