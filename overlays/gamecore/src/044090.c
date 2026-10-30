/* GAMECORE.XFF @ 0x044090 (16 B) - getexpressiondatapoint
 * Evidence: lwc1 [a0 + a1*16 + 4]
 * UNCONFIRMED: none
 */
float getexpressiondatapoint(char *p, int i) {
    return *(float *)(p + i * 16 + 4);
}
