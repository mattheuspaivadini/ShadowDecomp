/* GAMECORE.XFF @ 0x11C118 (40 B) - getSCRDataCtrlWork
 * Evidence: stores $ra, 0x0($sp); loads $ra, 0x0($sp); calls GetSCRCharaAIWorkPtr; frame
 
 */
/* UNCONFIRMED: the script work pointer follows the AI work pointer, rounded up
 * to a 16-byte boundary with 0x13 added first.
 */
void *GetSCRCharaAIWorkPtr(void);

char *getSCRDataCtrlWork(void) {
    return (char *)(((unsigned int)GetSCRCharaAIWorkPtr() + 0x13) & ~0xFU);
}
