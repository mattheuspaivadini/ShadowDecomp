/* GAMECORE.XFF @ 0x11DC60 (32 B) - SCRConditionPathStatus
 * Evidence: ops ld sd; calls getSCRDataCtrlWork, j getPathStatus; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
char *getSCRDataCtrlWork(void);
int getPathStatus(char *w);

int SCRConditionPathStatus(void) {
    return getPathStatus(getSCRDataCtrlWork());
}
