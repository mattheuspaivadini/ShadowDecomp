/* GAMECORE.XFF @ 0x10C2B8 (44 B) - chkMoveAngle2
 * Evidence: no memory access
 
 */
/* UNCONFIRMED: 0.0174532925f (1 degree in radians) is the tolerance. */
float fabsf(float x);

int chkMoveAngle2(float a, float b) {
    if (fabsf(a + b) <= 0.0174532925f)
        return 1;
    return 0;
}
