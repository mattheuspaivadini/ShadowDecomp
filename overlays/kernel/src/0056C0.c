/* KERNEL.XFF @ 0x0056C0 (500 B) - iosPadGetXZInputL
 * Evidence: x/y = pad[0x54]/pad[0x55] * 0.007843137f - 1.0f -> out[0]/out[2], out[1] = out[3] = 0; len2 < 0.16f (0x3E23D708, written 0.15999997f
 * because this compiler truncates decimals) -> dead zone out[0] = out[2] = out[1]; else len via volatile sqrt.s, inv = 1/len,
 * len > 1 -> out = n (stores out[2] then out[0], so the shared return is not merged); else per-axis dead zone (0.4f * |n|) re-reading out[i].
 * Levers: head statement order (x, out[1], out[0], y, out[3], out[2]) found by a permutation grid; DZ macro (not an inline function).
 */
static __inline__ float vsqrtf(float x) {
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}
#define DZ(i, th, n) out[i] = (((out[i] < 0.0f) ? -out[i] : out[i]) < (th)) ? 0.0f : (out[i] < 0.0f ? -1.0f : 1.0f) * (((out[i] < 0.0f) ? -out[i] - (th) : out[i] - (th)) * ((n) / ((n) - (th))))
void iosPadGetXZInputL(float *out, unsigned char *pad)
{
    float x, y, len2, len, inv, nx, ny, ax, ay, tx, ty;
    x = pad[0x54] * 0.007843137f - 1.0f;
    out[1] = 0;
    out[0] = x;
    y = pad[0x55] * 0.007843137f - 1.0f;
    out[3] = 0;
    out[2] = y;
    len2 = x * x + y * y;
    if (len2 < 0.15999997f) {
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
    tx = ax * 0.4f;
    ty = ay * 0.4f;
    DZ(0, tx, ax);
    DZ(2, ty, ay);
}
