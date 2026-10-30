/* KERNEL.XFF @ 0x01E300 (60 B) - sndSepSetVol
 * Evidence: f1 = 127.0f (0x42FE0000); `f12 * 127.0f * lwc1 0x1C(a0)` is
 * truncated by `cvt.w.s`; the clamp is branchless (slti 0x80 / slti 0 /
 * movn v0,zero / xori / movz v0,0x7F), which the source spells as
 * `if (v >= 0x80) v = 0x7F; else if (v < 0) v = 0;`, and the result is stored
 * as a halfword at 0x28.
 * UNCONFIRMED: struct name and field names.
 */
typedef struct Sep {
    int pad[7];      /* 0x00 .. 0x1B */
    float scale;     /* 0x1C */
    int pad2[2];     /* 0x20 .. 0x27 */
    short vol;       /* 0x28 */
} Sep;

void sndSepSetVol(Sep *p, float f) {
    int v = (int)(f * 127.0f * p->scale);

    if (v >= 0x80) {
        v = 0x7F;
    } else if (v < 0) {
        v = 0;
    }
    p->vol = v;
}
