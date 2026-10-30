/* GAMECORE.XFF @ 0x06BCC0 (40 B) - SCRFuncMinoCAddAtkCount
 * Evidence: `jal GetSCRCharaAIWorkPtr`, `lw 0x41E8`, `addiu 1`, `sw 0x41E8`:
 * the attack counter is incremented.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);

void SCRFuncMinoCAddAtkCount(void) {
    *(int *)((char *)GetSCRCharaAIWorkPtr() + 0x41E8) += 1;
}
