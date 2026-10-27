/* KERNEL.XFF @ 0x011950 (156 B) - iosGetACos
 * Evidence: x = (float)a * 4.65661e-10 (0x2FFFFFF5, a 1.31 fixed-point argument), then pi/2 - x - x^3/6 - 3x^5/40 - 15x^7/336 - 105x^9/3456 (arcsin Taylor terms); the constants are the decimal literals as this compiler truncates them (0x3FC90FDA, 0x3E2AAAAA, 0x3D999999, 0x3D36DB6D, 0x3CF8E38D). UNCONFIRMED: parameter meaning.
 */
float iosGetACos(int a) {
    float x = (float)a * 4.65661e-10f;
    float x3 = x * x * x;
    float x5 = x3 * x * x;
    float x7 = x5 * x * x;
    float x9 = x7 * x * x;

    return 1.5707963f - x - x3 * 0.16666666f - x5 * 0.075f - x7 * 0.044642857f - x9 * 0.030381944f;
}
