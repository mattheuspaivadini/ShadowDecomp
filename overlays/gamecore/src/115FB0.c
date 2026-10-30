/* GAMECORE.XFF @ 0x115FB0 (48 B) - SCRFuncUpdatePathSystem
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $ra, 0x8($sp), $s0, 0x0($sp), $a2, 0x4078($a1); calls getSCRDataCtrlWork, j updateUserPathWorkEx; frame
 
 */
/* UNCONFIRMED: +0x4078 is the player object handed to the user path update. */
char *getSCRDataCtrlWork(void);
void updateUserPathWorkEx(char *p, char *work, void *player);

void SCRFuncUpdatePathSystem(char *p) {
    char *work = getSCRDataCtrlWork();
    updateUserPathWorkEx(p, work, *(void **)(work + 0x4078));
}
