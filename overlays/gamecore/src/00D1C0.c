/* GAMECORE.XFF @ 0x00D1C0 (64 B) - set_base_pitch_parameter_nico_yaw_pitch_cntrl
 * Evidence: identical to 00D180 shifted by 0x1C: `swc1 $f17, 0x100($a0)`,
 * `sw $a1, 0xE8($a0)`, `swc1` to +0xFC, +0xEC, +0xF0, +0xF4, +0xF8.
 * UNCONFIRMED: the field roles.
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

void set_base_pitch_parameter_nico_yaw_pitch_cntrl(struct YawPitchCtrl *c,
                                                   int flag, float a, float b,
                                                   float d, float e, float f,
                                                   float g) {
    c->pitch5 = g;
    c->pitchFlag = flag;
    c->pitch4 = f * 0x1.1DF46Ap-6f;
    c->pitch0 = a * 0x1.1DF46Ap-6f;
    c->pitch1 = b * 0x1.1DF46Ap-6f;
    c->pitch2 = d * 0x1.1DF46Ap-6f;
    c->pitch3 = e * 0x1.1DF46Ap-6f;
}
