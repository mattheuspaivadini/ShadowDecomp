/* GAMECORE.XFF @ 0x118520 (44 B) - SCRFuncForceRenewLastPos
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $ra, 0x8($sp), $s0, 0x0($sp); calls getSCRDataCtrlWork, j forceRenewLastPosPerceptionWork; frame
 
 */
/* UNCONFIRMED: same perception work block as SCRFuncForceSetPerceptionWork. */
char *getSCRDataCtrlWork(void);
void forceRenewLastPosPerceptionWork(char *p, char *perception);

void SCRFuncForceRenewLastPos(char *p) {
    forceRenewLastPosPerceptionWork(p, getSCRDataCtrlWork() + 0x4030);
}
