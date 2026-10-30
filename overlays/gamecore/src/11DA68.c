/* GAMECORE.XFF @ 0x11DA68 (36 B) - SCRConditionGPFinish
 * Evidence: stores $ra, 0x0($sp); loads $ra, 0x0($sp); calls getSCRDataCtrlWork, j getPathExFinish; frame
 
 */
/* UNCONFIRMED: path type 5 is the goal path. */
char *getSCRDataCtrlWork(void);
int getPathExFinish(char *work, int pathType);

int SCRConditionGPFinish(void) {
    return getPathExFinish(getSCRDataCtrlWork(), 5);
}
