/* GAMECORE.XFF @ 0x00A050 (48 B) - GAMEUTIL_set_parameter_look_at_vs_offset
 * Evidence: stores $f16, 0x4C($a0), $f15, 0x48($a0), $f14, 0x44($a0), $f12, 0x3C($a0), $f13, 0x40($a0)
 */
/* variant: source order 3C,40,44,48,4C */
struct LookAtVs {
    char pad[0x3C];
    float angle3C;
    float angle40;
    float angle44;
    float angle48;
    float offset4C;
};

void GAMEUTIL_set_parameter_look_at_vs_offset(struct LookAtVs *p, float a,
                                              float b, float c, float d,
                                              float e) {
    p->angle3C = a * 0.0174532925f;
    p->angle40 = b * 0.0174532925f;
    p->angle44 = c * 0.0174532925f;
    p->angle48 = d;
    p->offset4C = e;
}
