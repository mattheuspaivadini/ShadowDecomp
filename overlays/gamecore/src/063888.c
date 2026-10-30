/* GAMECORE.XFF @ 0x063888 (40 B) - SCRFuncKnightSetStand
 * Evidence: `jal GetSCRCharaAIWorkPtr`, `lw 0x41B0`, `ori 1`, `sw 0x41B0`: the
 * low bit of the flag word is set.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);

void SCRFuncKnightSetStand(void) {
    *(int *)((char *)GetSCRCharaAIWorkPtr() + 0x41B0) |= 1;
}
