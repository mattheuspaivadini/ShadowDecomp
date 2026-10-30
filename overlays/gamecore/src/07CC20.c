/* GAMECORE.XFF @ 0x07CC20 (32 B) - nico_playeGripholdOff
 * Evidence: jal GetSCRCharaAIWorkPtr, sw zero to field
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
char *GetSCRCharaAIWorkPtr(void);

void nico_playeGripholdOff(void) {
    F(GetSCRCharaAIWorkPtr(), int, 0x130) = 0;
}
