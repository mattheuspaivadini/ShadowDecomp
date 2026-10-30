/* GAMECORE.XFF @ 0x009118 (36 B) - GAMEUTIL_get_1p_left_analog_input
 * Evidence: frame 0x10, forwards arguments in $a0 and $a1, passes constant 1
 * in $a2 and 0.4f (0x3ECCCCCC) in $f12, then tail-calls
 * GAMEUTIL_get_1p_left_analog_input_extend.
 */
int GAMEUTIL_get_1p_left_analog_input_extend(void *a0, void *a1, int a2, float f12);

int GAMEUTIL_get_1p_left_analog_input(void *a0, void *a1) {
    return GAMEUTIL_get_1p_left_analog_input_extend(a0, a1, 1, 0.4f);
}
