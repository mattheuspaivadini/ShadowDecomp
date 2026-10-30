/* GAMECORE.XFF @ 0x11DB20 (44 B) - SCRConditionAPChanged
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $ra, 0x8($sp), $s0, 0x0($sp); calls getSCRDataCtrlWork, j changedAPIndex; frame
 
 */
/* UNCONFIRMED: no player object is needed for the attack path check. */
char *getSCRDataCtrlWork(void);
int changedAPIndex(char *p, char *work);

int SCRConditionAPChanged(char *p) {
    return changedAPIndex(p, getSCRDataCtrlWork());
}
