/* KERNEL.XFF @ 0x0058B8 (484 B) - iosPadGetXZInputLwithThreshold
 * Evidence: same as 0056C0 (iosPadGetXZInputL) with the dead-zone radius t*t and per-axis threshold t*|n| taken from the float argument f12.
 */
static __inline__ float vsqrtf(float x) {
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}
#define DZ(i, th, n) out[i] = (((out[i] < 0.0f) ? -out[i] : out[i]) < (th)) ? 0.0f : (out[i] < 0.0f ? -1.0f : 1.0f) * (((out[i] < 0.0f) ? -out[i] - (th) : out[i] - (th)) * ((n) / ((n) - (th))))
void iosPadGetXZInputLwithThreshold(float *out, unsigned char *pad, float t)
{
    float x, y, len2, len, inv, nx, ny, ax, ay, tx, ty;
    x = pad[0x54] * 0.007843137f - 1.0f;
    out[1] = 0;
    out[0] = x;
    y = pad[0x55] * 0.007843137f - 1.0f;
    out[3] = 0;
    out[2] = y;
    len2 = x * x + y * y;
    if (len2 < t * t) {
        out[0] = out[2] = out[1];
        return;
    }
    len = vsqrtf(len2);
    inv = 1.0f / len;
    ny = y * inv;
    nx = x * inv;
    if (1.0f < len) {
        out[0] = nx;
        out[2] = ny;
        return;
    }
    ax = nx < out[1] ? -nx : nx;
    ay = ny < out[1] ? -ny : ny;
    tx = t * ax;
    ty = t * ay;
    DZ(0, tx, ax);
    DZ(2, ty, ay);
}
