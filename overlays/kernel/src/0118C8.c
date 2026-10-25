/* KERNEL.XFF @ 0x0118C8 (132 B) - iosGetACosf
 * Evidence: Taylor series pi/2 - x - x^3/6 - 3x^5/40 - 15x^7/336 - 105x^9/3456 with powers built incrementally; the constants are the decimal literals 1.5707963, 0.16666666, 0.075, 0.044642857, 0.030381944 (this compiler truncates decimal to float, so the exact images 0x3FC90FDA/0x3E2AAAAA/... come from those spellings).
 */
float iosGetACosf(float x) {
    float x3 = x * x * x;
    float x5 = x3 * x * x;
    float x7 = x5 * x * x;
    float x9 = x7 * x * x;

    return 1.5707963f - x
        - x3 * 0.16666666f
        - x5 * 0.075f
        - x7 * 0.044642857f
        - x9 * 0.030381944f;
}
