/* GAMECORE.XFF @ 0x0F89C0 (40 B) - setRouteMinAngle
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp), $f0, 0x3B0($s0); loads $ra, 0x8($sp), $s0, 0x0($sp); calls iosGetCosf; frame
 
 */
/* UNCONFIRMED: +0x3B0 caches cos(angle) for the route minimum angle test. */
float iosGetCosf(float angle);

void setRouteMinAngle(char *p, float angle) {
    *(float *)(p + 0x3B0) = iosGetCosf(angle);
}
