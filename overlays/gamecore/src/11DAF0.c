/* GAMECORE.XFF @ 0x11DAF0 (48 B) - SCRConditionGPChanged
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $ra, 0x8($sp), $s0, 0x0($sp), $a2, 0x4078($a1); calls getSCRDataCtrlWork, j changedGPIndex; frame
 
 */
/* UNCONFIRMED: +0x4078 is the player object. */
char *getSCRDataCtrlWork(void);
int changedGPIndex(char *p, char *work, void *player);

int SCRConditionGPChanged(char *p) {
    char *work = getSCRDataCtrlWork();
    return changedGPIndex(p, work, *(void **)(work + 0x4078));
}
