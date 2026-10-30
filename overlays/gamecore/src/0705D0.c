/* GAMECORE.XFF @ 0x0705D0 (60 B) - get_merge_pitch_nico_sight_on
 * Evidence: `$a1 = 0`, `$f13 = mtc1 $zero (0.0f)`, `$f14 = 0x3FBDE44E`,
 * `$f12 = lwc1 0x284($a0)`, `$a0 = 0`, `$f15 = 0xBFBDE44E`, then a tail
 * `j GAMEUTIL_increase_pitch`. The two int args are explicit zeros and the
 * four float args are (obj+0x284, 0.0f, +K, -K).
 * 0x3FBDE44E is 1.4835300445556641f, written as an exact hex float because
 * EE-GCC's decimal parser rounds `1.48353f` up to 0x3FBDE44F.
 * UNCONFIRMED: the field at +0x284 and the meaning of K.
 
 */
struct MergePitchObj {
    char pad[0x284];
    float value;
};

void GAMEUTIL_increase_pitch(int a, int b, float value, float base, float hi,
                             float lo);
extern char D_kernel_data_0000[];

void get_merge_pitch_nico_sight_on(struct MergePitchObj *obj) {
    GAMEUTIL_increase_pitch(0, 0, obj->value, 0.0f, 0x1.7BC89Cp0f,
                            -0x1.7BC89Cp0f);
}
