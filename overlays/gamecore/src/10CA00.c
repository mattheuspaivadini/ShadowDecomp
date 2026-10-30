/* GAMECORE.XFF @ 0x10CA00 (36 B) - adjustAngleForLimit
 * Evidence: no memory access
 
 */
/* UNCONFIRMED: clamps the angle to [-limit, limit]. */
float adjustAngleForLimit(float angle, float limit) {
    if (angle > limit)
        return limit;
    if (angle < -limit)
        return -limit;
    return angle;
}
