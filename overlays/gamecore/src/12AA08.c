/* GAMECORE.XFF @ 0x12AA08 (44 B) - nico_restartWormGenealogicalNodeFromDemo
 * Evidence: stores $ra, 0x0($sp), $zero, 0x1298($v0); loads $a0, 0x0($a0), $ra, 0x0($sp); calls GetSCRCharaAIWorkPtr; frame
 
 */
char *GetSCRCharaAIWorkPtr(int obj);

void nico_restartWormGenealogicalNodeFromDemo(int *p) {
    char *w = (char *)(((int)GetSCRCharaAIWorkPtr(*p) + 0x41B3) & ~0xF);
    w[0x1298] = 0;
}
