/* GAMECORE.XFF @ 0x009E70 (60 B) - GAMEUTIL_set_parameter_move_angle
 * Evidence: six float args in `$f12`..`$f17`; all but the one stored at +0x10
 * are multiplied by 0x3C8EFA35 (~0.0174532925) and stored at +0x4, +0x8, +0xC,
 * +0x14, +0x18; the +0x10 value is stored unscaled.
 * UNCONFIRMED: the parameter block layout.
 
 */
struct MoveAngleParam {
    int pad;
    float f04;
    float f08;
    float f0c;
    float angle;
    float f14;
    float f18;
};

void GAMEUTIL_set_parameter_move_angle(struct MoveAngleParam *p, float a, float b,
                                       float c, float angle, float e, float f) {
    p->angle = angle;
    p->f04 = a * 0.0174532925f;
    p->f08 = b * 0.0174532925f;
    p->f0c = c * 0.0174532925f;
    p->f14 = e * 0.0174532925f;
    p->f18 = f * 0.0174532925f;
}
