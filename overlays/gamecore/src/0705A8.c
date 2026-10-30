/* GAMECORE.XFF @ 0x0705A8 (36 B) - get_merge_yaw_nico_sight_on
 * Evidence: `$a0 -> $v0`, `$a0 = 0`, `lwc1 $f13, 0x248($v0)`,
 * `lwc1 $f12, 0x280($v0)`, sibling `j` to `GAMEUTIL_increase_yaw`: the int
 * argument is the constant 0 and the two floats are passed in order
 * (0x280 then 0x248).
 * UNCONFIRMED: field meanings and the callee prototype.
 
 */
float GAMEUTIL_increase_yaw(int arg, float a, float b);

float get_merge_yaw_nico_sight_on(char *p) {
    return GAMEUTIL_increase_yaw(0, *(float *)(p + 0x280), *(float *)(p + 0x248));
}
