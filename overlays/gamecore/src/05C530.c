/* GAMECORE.XFF @ 0x05C530 (40 B) - SCRFuncHorseEscapeCounterInit
 * Evidence: the float argument is kept in `$f20` across `jal
 * GetSCRCharaAIWorkPtr` (frame slot 0x8, `mov.s` in the delay slot) and stored
 * into AI work +0x422C.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);

void SCRFuncHorseEscapeCounterInit(float value) {
    *(float *)((char *)GetSCRCharaAIWorkPtr() + 0x422C) = value;
}
