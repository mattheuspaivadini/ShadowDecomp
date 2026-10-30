/* GAMECORE.XFF @ 0x07CBF8 (36 B) - nico_playeGripholdOn
 * Evidence: `jal GetSCRCharaAIWorkPtr`, then `sw 1` into the result +0x130.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);

void nico_playeGripholdOn(void) {
    *(int *)((char *)GetSCRCharaAIWorkPtr() + 0x130) = 1;
}
