/* GAMECORE.XFF @ 0x11DA90 (36 B) - SCRConditionPPFinish
 * Evidence: stores $ra, 0x0($sp); loads $ra, 0x0($sp); calls getSCRDataCtrlWork, j getPathExFinish; frame
 
 */
/* UNCONFIRMED: path type 9 is the passage point path. */
char *getSCRDataCtrlWork(void);
int getPathExFinish(char *work, int pathType);

int SCRConditionPPFinish(void) {
    return getPathExFinish(getSCRDataCtrlWork(), 9);
}
