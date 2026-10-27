/* KERNEL.XFF @ 0x0119F0 (84 B) - iosGetACosfExact
 * Evidence: returns 0 for x >= 1, pi (0x40490FDA) for x <= -1, else sibling acosf(x).
 */
float acosf(float x);

float iosGetACosfExact(float x) {
    if (1.0f <= x) {
        return 0.0f;
    }
    if (x <= -1.0f) {
        return 3.1415926f;
    }
    return acosf(x);
}
