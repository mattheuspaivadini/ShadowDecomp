/* GAMECORE.XFF @ 0x00D180 (64 B) - set_base_yaw_parameter_nico_yaw_pitch_cntrl
 * Evidence: `$f0 = 0x3C8EFA35` (0x1.1DF46Ap-6, the degree->radian factor) then
 * `swc1 $f17, 0xE4($a0)`, `sw $a1, 0xCC($a0)`, `mul.s` of $f16/$f12/$f13/$f14/
 * $f15 by the factor, and `swc1` to +0xE0, +0xD0, +0xD4, +0xD8, +0xDC (the last
 * in the `jr` delay slot). Six float args arrive in $f12-$f17, the int in $a1.
 * UNCONFIRMED: the field roles; the struct below mirrors the two parallel
 * 0x1C-byte groups the yaw/pitch pair touches.
 */
struct YawPitchCtrl {
    char pad0[0xCC];
    int yawFlag;                    /* +0xCC */
    float yaw0;                     /* +0xD0 */
    float yaw1;                     /* +0xD4 */
    float yaw2;                     /* +0xD8 */
    float yaw3;                     /* +0xDC */
    float yaw4;                     /* +0xE0 */
    float yaw5;                     /* +0xE4 */
    int pitchFlag;                  /* +0xE8 */
    float pitch0;                   /* +0xEC */
    float pitch1;                   /* +0xF0 */
    float pitch2;                   /* +0xF4 */
    float pitch3;                   /* +0xF8 */
    float pitch4;                   /* +0xFC */
    float pitch5;                   /* +0x100 */
};

void set_base_yaw_parameter_nico_yaw_pitch_cntrl(struct YawPitchCtrl *c,
                                                 int flag, float a, float b,
                                                 float d, float e, float f,
                                                 float g) {
    c->yaw5 = g;
    c->yawFlag = flag;
    c->yaw4 = f * 0x1.1DF46Ap-6f;
    c->yaw0 = a * 0x1.1DF46Ap-6f;
    c->yaw1 = b * 0x1.1DF46Ap-6f;
    c->yaw2 = d * 0x1.1DF46Ap-6f;
    c->yaw3 = e * 0x1.1DF46Ap-6f;
}
