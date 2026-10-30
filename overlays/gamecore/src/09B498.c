/* GAMECORE.XFF @ 0x09B498 (48 B) - AI_GetNegaVector
 * Evidence: stores $f0, 0x0($a0), $f1, 0x4($a0), $f0, 0x8($a0), $f1, 0xC($a0); loads $f0, 0x0($a1), $f1, 0x4($a1), $f0, 0x8($a1), $f1, 0xC($a1)
 
 */
void AI_GetNegaVector(float *dst, float *src) {
    dst[0] = -src[0];
    dst[1] = -src[1];
    dst[2] = -src[2];
    dst[3] = src[3];
}
