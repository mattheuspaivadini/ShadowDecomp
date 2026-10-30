/* GAMECORE.XFF @ 0x11DC40 (32 B) - SCRConditionWayFinish
 * Evidence: ops ld sd; calls getSCRDataCtrlWork, j getWayFinish; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
char *getSCRDataCtrlWork(void);
int getWayFinish(char *w);

int SCRConditionWayFinish(void) {
    return getWayFinish(getSCRDataCtrlWork());
}
