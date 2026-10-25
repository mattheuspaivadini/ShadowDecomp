/* KERNEL.XFF @ 0x00C910 (36 B) - iosInverseMatrixPerfect
 * Evidence: forwards (dst, src) to the stripped static at .text+0xB400 with a
 * leading constant 4 (sibling `j`, arguments shuffled through $v0).
 * UNCONFIRMED: func_00B400's meaning (4 = matrix order?) and prototype.
 */
void func_00B400(int n, float *d, float *s);
void iosInverseMatrixPerfect(float *d, float *s) {
    func_00B400(4, d, s);
}
