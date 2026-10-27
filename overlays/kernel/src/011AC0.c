/* KERNEL.XFF @ 0x011AC0 (104 B) - iosGetATan2fExact
 * Evidence: both arguments clamped to [-1, 1] (else-if pairs, bc1tl slot moves), then sibling atan2f(y, x).
 */
float atan2f(float y, float x);

float iosGetATan2fExact(float y, float x) {
    if (1.0f < y) {
        y = 1.0f;
    } else if (y < -1.0f) {
        y = -1.0f;
    }
    if (1.0f < x) {
        x = 1.0f;
    } else if (x < -1.0f) {
        x = -1.0f;
    }
    return atan2f(y, x);
}
