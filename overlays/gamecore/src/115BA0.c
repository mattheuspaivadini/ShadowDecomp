/* GAMECORE.XFF @ 0x115BA0 (32 B) - SCRFuncLineAllReset
 * Evidence: ops ld sd; calls getSCRDataCtrlWork, j allResetLineAttr; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
char *getSCRDataCtrlWork(void);
void allResetLineAttr(char *w);

void SCRFuncLineAllReset(void) {
    allResetLineAttr(getSCRDataCtrlWork());
}
