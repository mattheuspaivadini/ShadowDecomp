/* GAMECORE.XFF @ 0x00DA88 (48 B) - get_merge_pitch_nico_yaw_pitch_cntrl
 * Evidence: two zero integer arguments (`$a0`, `$a1`) then four floats loaded
 * from +0x68 -> `$f12`, +0x50 -> `$f13`, +0x120 -> `$f14`, +0x124 -> `$f15`,
 * and a sibling `j` to `GAMEUTIL_increase_pitch`.
 * UNCONFIRMED: the struct field meanings and the callee prototype.
 
 */
struct MergePitchCtrl {
    char pad50[0x50];
    float f50;
    char pad68[0x14];
    float f68;
    char pad120[0xB4];
    float f120;
    float f124;
};

void GAMEUTIL_increase_pitch(int a, int b, float c, float d, float e, float f);

void get_merge_pitch_nico_yaw_pitch_cntrl(struct MergePitchCtrl *p) {
    GAMEUTIL_increase_pitch(0, 0, p->f68, p->f50, p->f120, p->f124);
}
