/* GAMECORE.XFF @ 0x07B328 (32 B) - IsHorseAutoControlled
 * Evidence: jal GetSCRCharaAIWorkPtr; load [v0+0xD9D]
 * UNCONFIRMED: none
 */
char *GetSCRCharaAIWorkPtr(void);

int IsHorseAutoControlled(void) {
    return *(unsigned char *)(GetSCRCharaAIWorkPtr() + 0xD9D);
}
