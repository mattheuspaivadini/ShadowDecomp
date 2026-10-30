/* GAMECORE.XFF @ 0x009520 (44 B) - GAMEUTIL_is_sign_change
 * Evidence: checks if float args `a == b` (returns 0), then checks if
 * `a * b <= 0.0f` (returns 1), otherwise returns 0.
 */
int GAMEUTIL_is_sign_change(float a, float b) {
    if (a == b)
        return 0;
    if (a * b <= 0.0f)
        return 1;
    return 0;
}
