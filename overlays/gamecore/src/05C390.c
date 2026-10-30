/* GAMECORE.XFF @ 0x05C390 (32 B) - getHorseInterpSpeed
 * Evidence: jal GetSCRCharaAIWorkPtr; load [v0+0x3E10]
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

float getHorseInterpSpeed(void) {
    return *(float *)(GetSCRCharaAIWorkPtr() + 0x3E10);
}
