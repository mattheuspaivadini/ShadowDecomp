/* KERNEL.XFF @ 0x011A48 (92 B) - iosGetASinfExact
 * Evidence: returns pi/2 (0x3FC90FDA) for x >= 1, -pi/2 for x <= -1, else sibling asinf(x).
 */
float asinf(float x);

float iosGetASinfExact(float x) {
    if (1.0f <= x) {
        return 1.5707963f;
    }
    if (x <= -1.0f) {
        return -1.5707963f;
    }
    return asinf(x);
}
