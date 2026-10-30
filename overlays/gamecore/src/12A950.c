/* GAMECORE.XFF @ 0x12A950 (40 B) - getWormIKWork
 * Evidence: stores $ra, 0x0($sp); loads $ra, 0x0($sp); calls GetSCRCharaAIWorkPtr; frame
 
 */
char *GetSCRCharaAIWorkPtr(void);

char *getWormIKWork(void) {
    return (char *)(((int)GetSCRCharaAIWorkPtr() + 0x41B3) & ~0xF);
}
