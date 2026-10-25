/* KERNEL.XFF @ 0x00B288 (100 B) - iosFourthBezier
 * Evidence: cubic Bernstein: s = 1 - t; s^2*s*p[0] + s^2*3*t*p[1] + s*3*t^2*p[2] + t^2*t*p[3] (multiplication order as in the image).
 */
float iosFourthBezier(float *p, float t) {
    float s = 1.0f - t;
    float t2 = t * t;
    float s2 = s * s;

    return s2 * s * p[0] + s2 * 3.0f * t * p[1] + s * 3.0f * t2 * p[2] + t2 * t * p[3];
}
