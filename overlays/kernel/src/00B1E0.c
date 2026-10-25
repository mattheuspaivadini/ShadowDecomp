/* KERNEL.XFF @ 0x00B1E0 (64 B) - iosCubicBezier
 * Evidence: s = 1.0f - t; returns s*s*p[0] + (s+s)*t*p[1] + t*t*p[2] (quadratic
 * Bernstein form, despite the name); single-precision ops only.
 */
float iosCubicBezier(float *p, float t) {
    float s = 1.0f - t;
    return s * s * p[0] + (s + s) * t * p[1] + t * t * p[2];
}
