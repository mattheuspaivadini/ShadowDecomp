/* GAMECORE.XFF @ 0x1184F0 (44 B) - SCRFuncForceSetPerceptionWork
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $ra, 0x8($sp), $s0, 0x0($sp); calls getSCRDataCtrlWork, j forceSetPerceptionWork; frame
 
 */
/* UNCONFIRMED: +0x4030 is the perception work handed to the force setter. */
char *getSCRDataCtrlWork(void);
void forceSetPerceptionWork(char *p, char *perception);

void SCRFuncForceSetPerceptionWork(char *p) {
    forceSetPerceptionWork(p, getSCRDataCtrlWork() + 0x4030);
}
