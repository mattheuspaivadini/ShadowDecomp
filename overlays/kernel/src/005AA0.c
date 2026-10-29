/* KERNEL.XFF @ 0x005AA0 (364 B) - iosPadGetXZInputLwithThresholdIndepAxis
 * Evidence: out[0]/out[2] = pad[0x54]/pad[0x55] * (1/127.5, truncated 0.007843137f) - 1.0f, out[1] = out[3] = 0;
 * each axis alone: |v| < t -> 0, else sign(v) * (|v| - t) * (1 / (1 - t)). The macro re-reads out[i]
 * (the image reloads 0(a0) after the first test), stores one merged result per axis.
 * Levers: statement order out[0], out[1], out[2], out[3] = out[1] (found by permuting the 4 head stores).
 */
#define DZ(i) out[i] = (((out[i] < 0.0f) ? -out[i] : out[i]) < t) ? 0.0f : (out[i] < 0.0f ? -1.0f : 1.0f) * (((out[i] < 0.0f) ? -out[i] - t : out[i] - t) * (1.0f / (1.0f - t)))

void iosPadGetXZInputLwithThresholdIndepAxis(float *out, unsigned char *pad, float t)
{
    out[0] = pad[0x54] * 0.007843137f - 1.0f;
    out[1] = 0;
    out[2] = pad[0x55] * 0.007843137f - 1.0f;
    out[3] = out[1];
    DZ(0);
    DZ(2);
}
