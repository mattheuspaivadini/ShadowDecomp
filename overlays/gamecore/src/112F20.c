/* GAMECORE.XFF @ 0x112F20 (44 B) - setWorldPitchLimitWormCtrlWork
 * Evidence: stores $f13, 0x78($a0), $f12, 0x74($a0)
 
 */
/* UNCONFIRMED: converts both angles from degrees to radians; +0x74 stores the
 * negated pitch, +0x78 the world pitch limit.
 */
float fabsf(float x);

void setWorldPitchLimitWormCtrlWork(char *p, float pitch, float limit) {
    *(float *)(p + 0x78) = fabsf(limit * 0.0174532925f);
    *(float *)(p + 0x74) = -fabsf(pitch * 0.0174532925f);
}
