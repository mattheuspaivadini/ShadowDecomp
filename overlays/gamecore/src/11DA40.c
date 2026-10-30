/* GAMECORE.XFF @ 0x11DA40 (36 B) - SCRConditionAPFinish
 * Evidence: stores $ra, 0x0($sp); loads $ra, 0x0($sp); calls getSCRDataCtrlWork, j getPathExFinish; frame
 
 */
/* UNCONFIRMED: path type 2 is the attack path. */
char *getSCRDataCtrlWork(void);
int getPathExFinish(char *work, int pathType);

int SCRConditionAPFinish(void) {
    return getPathExFinish(getSCRDataCtrlWork(), 2);
}
